//--------------------------------------------------------------------
//  Run.cpp
//	11/2/2025.				created.
//  11/16/2025.				last modified.
//--------------------------------------------------------------------
#include "Run.h"


//--------------------------------------------------------------------
std::tuple<parser::details::CommandFields, parser::details::RunParser::ErrorMsgs, parser::details::RunParser::WarnMsgs>
	parser::details::RunParser::special_check(CommandFields const& parsered_fields, std::vector<std::u8string> run_need_fields) noexcept
{
	FieldSpec const& fs = RunParser::run_spec_field(run_need_fields);
	Report report = fs.check_presence(parsered_fields);

	return { parsered_fields, report.errors, report.warnings };
}


//--------------------------------------------------------------------
const parser::details::FieldSpec& parser::details::RunParser::run_spec_field(std::vector<std::u8string> run_fields) noexcept
{
	static const FieldSpec fs = FieldSpec::init_field_spec(run_fields);
	return fs;
}


//--------------------------------------------------------------------

