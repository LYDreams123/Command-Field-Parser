//--------------------------------------------------------------------
//  Compile.h
//	10/31/2025.				created.
//  11/1/2025.				last modified.
//--------------------------------------------------------------------
#ifndef _COMPILE_H__
#define _COMPILE_H__

//--------------------------------------------------------------------
//  headers.
//--------------------------------------------------------------------
#include "DefaultCommandParser.h"   
#include "FieldSpec.h"           
#include <string>
#include <vector>
#include <tuple>            


//--------------------------------------------------------------------
class CompileParser
{
	//--------------------------------------------------------------------
	using ErrorMsgs = std::vector<std::u8string>;
	using WarnMsgs = std::vector<std::u8string>;
public:
	//--------------------------------------------------------------------
	std::tuple<CommandFields, ErrorMsgs, WarnMsgs> special_check(CommandFields const& parsered_fields, std::vector<std::u8string> compile_need_fields) noexcept;

private:
	static const FieldSpec& compile_spec_field(std::vector<std::u8string> compile_fields) noexcept;
};

#endif // !_COMPILE_H__

