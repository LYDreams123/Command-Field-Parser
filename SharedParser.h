//--------------------------------------------------------------------
//  SharedParser.h
//	10/17/2025.				created.
//  11/16/2025.				last modified.
//--------------------------------------------------------------------
#ifndef _SHARED_PARSER_H__
#define _SHARED_PARSER_H__

//--------------------------------------------------------------------
//  headers.
//--------------------------------------------------------------------
#include <string>
#include <vector>
#include "FieldSpec.h"


namespace parser::details
{
	//--------------------------------------------------------------------
	class SharedParser
	{
		//--------------------------------------------------------------------
		using ErrorMsgs = std::vector<std::u8string>;
		using WarnMsgs = std::vector<std::u8string>;
	public:
		//--------------------------------------------------------------------
		static std::tuple<CommandFields, ErrorMsgs, WarnMsgs> shared_check(CommandFields const& fields) noexcept;

	private:
		static const FieldSpec& shared_field();
	};
}


#endif // !_SHARED_PARSER_H__

