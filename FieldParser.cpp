//--------------------------------------------------------------------
//  FieldParser.cpp
//	11/2/2025.				created.
//  11/2/2025.				last modified.
//--------------------------------------------------------------------
#include "FieldParser.h"


//--------------------------------------------------------------------
auto FieldParser::field_parser(std::u8string const& raw_string) noexcept -> std::pair<std::optional<CommandFields>, ErrorMsgs>
{
	_fields.clear();
	_error_msgs.clear();

	size_t now_index{ 0 };
	while (now_index < raw_string.size())
	{
		auto get_field_result = get_field(raw_string, now_index);
		if (!get_field_result.has_value())
		{
			return { std::nullopt, _error_msgs };
		}

		auto& [name, value, next_index] = *get_field_result;
		_fields[name] = value;
		now_index = next_index;
	}

	return { _fields, _error_msgs };
}

// "Version:3:1.0\r\nCommand:7:compile\r\nUserID:4:1534\r\nReqID:18:153420051016100725\r\n"
//--------------------------------------------------------------------
auto FieldParser::get_field(std::u8string const& raw_string, size_t const prev_index) noexcept -> std::optional<std::tuple<FieldName, FieldValue, size_t>>
{
	auto p1 = raw_string.find(u8':', prev_index);
	if (p1 == std::u8string::npos)
	{
		_error_msgs.emplace_back(u8"not find first colon");
		return std::nullopt;
	}

	auto p2 = raw_string.find(u8':', p1 + 1);

	auto p3 = raw_string.find(u8"\r\n", prev_index + 1);
	if (p3 == std::u8string::npos)
	{
		_error_msgs.emplace_back(u8"not find \r\n");
		return std::nullopt;
	}
	else if (p1 >= p3)
	{
		_error_msgs.emplace_back(u8"not find first colon");
		return std::nullopt;
	}
	else if (p2 == std::u8string::npos || p2 >= p3)
	{
		_error_msgs.emplace_back(u8"not find second colon");
		return std::nullopt;
	}

	// Command:7:compile\r\n
	size_t vlen = 0;
	{                                                 // 9 - 8 = 1 
		std::u8string digits = raw_string.substr(p1 + 1, p2 - (p1 + 1));

		if (digits.empty())
		{
			_error_msgs.emplace_back(u8"vlen empty");
			return std::nullopt;
		}

		for (char8_t ch : digits)
		{
			if (ch < u8'0' || ch > u8'9')
			{
				_error_msgs.emplace_back(u8"vlen not integer");
				return std::nullopt;
			}
			vlen = vlen * 10 + static_cast<size_t>(ch - u8'0');
		}
	}

	if (vlen >= 8 * 1024) // 8k
	{
		_error_msgs.emplace_back(u8"value is too long");
		return std::nullopt;
	}

	// ....Command:7:compile\r\n

	// prev_index 是上个字段 \r\n 的起点
	FieldName name = raw_string.substr(prev_index, p1 - prev_index);
	FieldValue value = raw_string.substr(p2 + 1, p3 - (p2 + 1));

	if (value.size() != vlen)
	{
		_error_msgs.emplace_back(u8"vlen is not equal to the length of value");
		return std::nullopt;
	}

    // Command:7 : compile\r\n
	return std::tuple<FieldName, FieldValue, size_t>{ name, value, p3 + 2 };
}


//--------------------------------------------------------------------

