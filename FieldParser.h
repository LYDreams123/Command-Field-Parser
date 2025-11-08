//--------------------------------------------------------------------
//  FieldParser.h
//	11/1/2025.				created.
//  11/2/2025.				last modified.
//--------------------------------------------------------------------
#ifndef _FIELD_PARSER_H__
#define _FIELD_PARSER_H__

//--------------------------------------------------------------------
//  headers.
//--------------------------------------------------------------------
#include <string>
#include <vector>
#include <tuple>
#include <optional>
#include "ISpecialParser.h"


//--------------------------------------------------------------------
class FieldParser
{
	using ErrorMsgs = std::vector<std::u8string>;
public:
	//--------------------------------------------------------------------
	auto field_parser(std::u8string const& raw_string) noexcept -> std::pair<std::optional<CommandFields>, ErrorMsgs>;

private:
	//--------------------------------------------------------------------
	// 从 raw_string 中找字段的函数
	//--------------------------------------------------------------------
	auto get_field(std::u8string const& raw_string, size_t const prev_index) noexcept -> std::optional<std::tuple<FieldName, FieldValue, size_t>>;

private:
	CommandFields		_fields{};
	ErrorMsgs			_error_msgs{};

};


//--------------------------------------------------------------------
#endif // !_FIELD_PARSER_H__

