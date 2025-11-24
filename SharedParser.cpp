//--------------------------------------------------------------------
//  SharedParser.cpp
//	11/2/2025.				created.
//  11/16/2025.				last modified.
//--------------------------------------------------------------------
#include "SharedParser.h"


//--------------------------------------------------------------------
std::tuple<parser::details::CommandFields, parser::details::SharedParser::ErrorMsgs, parser::details::SharedParser::WarnMsgs> 
	parser::details::SharedParser::shared_check(CommandFields const& fields) noexcept
{
	FieldSpec const& fs = SharedParser::shared_field();
	Report report = fs.check_presence(fields, true);

	return { fields, report.errors, report.warnings };
}


//--------------------------------------------------------------------
const parser::details::FieldSpec& parser::details::SharedParser::shared_field()
{
	static const FieldSpec fs = FieldSpec::init_field_spec({ u8"Version", u8"Command", u8"UserID", u8"ReqID" });
	return fs;
}


//--------------------------------------------------------------------

