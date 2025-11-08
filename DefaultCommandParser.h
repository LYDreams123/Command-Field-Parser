//--------------------------------------------------------------------
//  DefaultCommandParser.h
//	10/17/2025.				created.
//  11/2/2025.				last modified.
//--------------------------------------------------------------------
#ifndef _DEFAULT_COMMAND_PARSER_H__
#define _DEFAULT_COMMAND_PARSER_H__

//--------------------------------------------------------------------
//  headers.
//--------------------------------------------------------------------
#include <unordered_map>
#include <vector>
#include <string>
#include <optional>
#include <exception>


//--------------------------------------------------------------------
using ErrorMsgs = std::vector<std::u8string>;
using WarnMsgs = std::vector<std::u8string>;
using FieldName = std::u8string;
using FieldValue = std::u8string;
using CommandFields = std::unordered_map<FieldName, FieldValue>;


//--------------------------------------------------------------------
class ParserException : public std::exception
{
public:
	//--------------------------------------------------------------------
	ParserException(std::vector<std::u8string> const& parser_error) : _parser_error{ parser_error }
	{
		// ...
	}


	//--------------------------------------------------------------------
	std::vector<std::u8string> error() const noexcept
	{
		return _parser_error;
	}

private:
	std::vector<std::u8string> _parser_error;

};


//--------------------------------------------------------------------
struct ParseResult
{
	CommandFields command_fields;
	ErrorMsgs     error_messages;
	WarnMsgs      warning_messages;
};


//--------------------------------------------------------------------
class DefaultCommandParser
{
public:
	//--------------------------------------------------------------------
	static ParseResult parser(std::u8string raw_string, bool shared_strict_flag = true, bool special_strict_flag = false) noexcept;

private:
	//--------------------------------------------------------------------
	static WarnMsgs check(std::pair<std::optional<CommandFields>, ErrorMsgs> parser_result, bool shared_strict_flag, bool special_strict_flag);
};


#endif // !_DEFAULT_COMMAND_PARSER_H__

