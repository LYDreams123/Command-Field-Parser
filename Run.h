//--------------------------------------------------------------------
//  Run.h
//	11/1/2025.				created.
//  11/1/2025.				last modified.
//--------------------------------------------------------------------
#ifndef _RUN_H__
#define _RUN_H__

//--------------------------------------------------------------------
//  headers.
//--------------------------------------------------------------------
#include "DefaultCommandParser.h"
#include "FieldSpec.h"
#include <string>
#include <vector>
#include <tuple>                    


//--------------------------------------------------------------------
class RunParser
{
	//--------------------------------------------------------------------
	using ErrorMsgs = std::vector<std::u8string>;
	using WarnMsgs = std::vector<std::u8string>;
public:
	//--------------------------------------------------------------------
	std::tuple<CommandFields, ErrorMsgs, WarnMsgs> special_check(CommandFields const& parsered_fields, std::vector<std::u8string> run_need_fields) noexcept;

private:
	static const FieldSpec& run_spec_field(std::vector<std::u8string> run_fields) noexcept;
};


#endif // !_RUN_H__

