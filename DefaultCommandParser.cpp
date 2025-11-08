//--------------------------------------------------------------------
//  DefaultCommandParser.cpp
//	10/17/2025.				created.
//  11/2/2025.				last modified.
//--------------------------------------------------------------------
#include "DefaultCommandParser.h"
#include "FieldParser.h"
#include "SharedParser.h"
#include "ISpecialParser.h"


//--------------------------------------------------------------------
ParseResult DefaultCommandParser::parser(std::u8string raw_string, bool shared_strict_flag /*= true*/, bool special_strict_flag /*= false*/) noexcept
{
    FieldParser fp;
    std::pair<std::optional<CommandFields>, ErrorMsgs> parser_result = fp.field_parser(raw_string);

    ErrorMsgs error_messages{};
    WarnMsgs  warning_messages{};

    try
    {
        warning_messages = check(parser_result, shared_strict_flag, special_strict_flag);
    }
    catch (ParserException const& pe)
    {
        error_messages = pe.error();
    }

    if (parser_result.first.has_value())
        return ParseResult{ *parser_result.first, error_messages, warning_messages };
    else
        return ParseResult{ CommandFields{}, error_messages, warning_messages };

    return ParseResult{};
}


//--------------------------------------------------------------------
WarnMsgs DefaultCommandParser::check(std::pair<std::optional<CommandFields>, ErrorMsgs> parser_result, bool shared_strict_flag /*= true*/, bool special_strict_flag /*= false*/)
{
    // 如果字段解析有问题，直接抛
    if (!parser_result.second.empty())
        throw ParserException{ parser_result.second };

    // 再看一眼解析出来的字段是否存在问题
    auto parser_result_fields = parser_result.first;
    if (!parser_result_fields.has_value())
        throw ParserException{ std::vector<std::u8string>{ u8"field parser error" } };

    // 检查公有字段是否都存在
    // shared_strict_falg 表示是否将 Warning 算作出错，默认为 true
    std::tuple<CommandFields, ErrorMsgs, WarnMsgs> shared_check_result = SharedParser::shared_check(*parser_result_fields);
    auto [shared_command_fields, shared_error_msgs, shared_warn_msgs] = shared_check_result;
    if (!shared_error_msgs.empty() || shared_strict_flag && !shared_warn_msgs.empty())
    {
        shared_error_msgs.insert(shared_error_msgs.end(), shared_warn_msgs.begin(), shared_warn_msgs.end());
        throw ParserException{ shared_error_msgs };
    }

    // 通过 Command，找到对应的私有字段校验函数
    auto it1 = shared_command_fields.find(u8"Command");
    if (it1 == shared_command_fields.end())
        throw ParserException{ {u8"not find command field"} };

    // compile
    auto command_type = it1->second;
    auto& parsers = special_parsers();

    auto it2 = parsers.find(command_type);
    if (it2 == parsers.end())
        throw ParserException{ {u8"don't have " + command_type + u8" type"} };
    auto special_check_func = it2->second;

    // 检测私有字段
    auto command_fields_copy = shared_command_fields;
    command_fields_copy.erase(u8"Version");
    command_fields_copy.erase(u8"Command");
    command_fields_copy.erase(u8"UserID");
    command_fields_copy.erase(u8"ReqID");

    std::tuple<CommandFields, ErrorMsgs, WarnMsgs> special_check_result = special_check_func(command_fields_copy);
    auto [special_command_fields, special_error_msgs, special_warn_msgs] = special_check_result;
    if (!special_error_msgs.empty() || special_strict_flag && !special_warn_msgs.empty())
    {
        special_error_msgs.insert(special_error_msgs.end(), special_warn_msgs.begin(), special_warn_msgs.end());
        throw ParserException{ special_error_msgs };
    }

    std::vector<std::u8string> warning_messages{ shared_warn_msgs };
    warning_messages.insert(warning_messages.end(), special_warn_msgs.begin(), special_warn_msgs.end());

    return WarnMsgs{ warning_messages };
}


//--------------------------------------------------------------------

