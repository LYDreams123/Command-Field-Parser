//--------------------------------------------------------------------
//  CommandFieldParser.hpp
//	10/17/2025.				created.
//  11/16/2025.				last modified.
//--------------------------------------------------------------------
#ifndef _COMMAND_FIELD_PARSER_H__
#define _COMMAND_FIELD_PARSER_H__

//--------------------------------------------------------------------
//  headers.
//--------------------------------------------------------------------
#include <unordered_map>
#include <vector>
#include <string>
#include <optional>
#include <exception>


//--------------------------------------------------------------------
namespace parser::details
{
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
		std::vector<std::u8string> const& error() const noexcept
		{
			return _parser_error;
		}

	private:
		std::vector<std::u8string> _parser_error;

	};
}


//--------------------------------------------------------------------
namespace parser
{
	//--------------------------------------------------------------------
	struct ParseResult
	{
		details::CommandFields command_fields;
		details::ErrorMsgs     error_messages;
		details::WarnMsgs      warning_messages;
	};


	//--------------------------------------------------------------------
	class DefaultCommandParser
	{
	public:
		//--------------------------------------------------------------------
		static ParseResult parser(std::u8string raw_string, bool shared_strict_flag = true, bool special_strict_flag = false) noexcept;

	private:
		//--------------------------------------------------------------------
		static details::WarnMsgs check(std::pair<std::optional<details::CommandFields>, details::ErrorMsgs> parser_result, bool shared_strict_flag, bool special_strict_flag);
	};
}


#endif // !_COMMAND_FIELD_PARSER_H__

