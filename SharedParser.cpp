//--------------------------------------------------------------------
//  SharedParser.cpp
//	11/2/2025.				created.
//  11/2/2025.				last modified.
//--------------------------------------------------------------------
#include "SharedParser.h"


//--------------------------------------------------------------------
std::tuple<CommandFields, SharedParser::ErrorMsgs, SharedParser::WarnMsgs> SharedParser::shared_check(CommandFields const& fields) noexcept
{
	FieldSpec const& fs = SharedParser::shared_field();
	Report report = fs.check_presence(fields, true);

	return { fields, report.errors, report.warnings };
}


//--------------------------------------------------------------------
const FieldSpec& SharedParser::shared_field()
{
	static const FieldSpec fs = FieldSpec::init_field_spec({ u8"Version", u8"Command", u8"UserID", u8"ReqID" });
	return fs;
}


//--------------------------------------------------------------------

