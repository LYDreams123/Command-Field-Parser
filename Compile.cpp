//--------------------------------------------------------------------
//  compile.cpp
//	11/1/2025.				created.
//  11/1/2025.				last modified.
//--------------------------------------------------------------------
#include "Compile.h"


//--------------------------------------------------------------------
std::tuple<CommandFields, CompileParser::ErrorMsgs, CompileParser::WarnMsgs>
	CompileParser::special_check(CommandFields const& parsered_fields, std::vector<std::u8string> compile_need_fields) noexcept
{
	FieldSpec const& fs = CompileParser::compile_spec_field(compile_need_fields);
	Report report = fs.check_presence(parsered_fields);

	return { parsered_fields, report.errors, report.warnings };
}


//--------------------------------------------------------------------
const FieldSpec& CompileParser::compile_spec_field(std::vector<std::u8string> compile_fields) noexcept
{
	static const FieldSpec fs = FieldSpec::init_field_spec(compile_fields);
	return fs;
}


//--------------------------------------------------------------------

