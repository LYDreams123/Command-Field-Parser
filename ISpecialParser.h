//--------------------------------------------------------------------
//  ISpecialParser.h
//	10/31/2025.				created.
//  11/2/2025.				last modified.
//--------------------------------------------------------------------
#ifndef _ISPECIAL_PARSER_H__
#define _ISPECIAL_PARSER_H__

//--------------------------------------------------------------------
//  headers.
//--------------------------------------------------------------------
#include <functional>
#include <tuple>
#include "DefaultCommandParser.h"
#include "run.h"
#include "compile.h"


//--------------------------------------------------------------------
using SpecialParserFn = std::function<std::tuple<CommandFields, ErrorMsgs, WarnMsgs>(CommandFields const&)>;


//--------------------------------------------------------------------
static const std::unordered_map<std::u8string, SpecialParserFn>& special_parsers()
{
	static const std::unordered_map<std::u8string, SpecialParserFn> _command_types{
		// If you want to add fields or commandtype, please follow this format:
		// { 
		//      u8"<command name>", [](CommandFields const& fields) {
		//          return <command name>Parser{}.special_check(fields, {
		//              {
		//                  u8"<validation field 1>", 
		//                  u8"<validation field 2>", 
		//                  u8"<validation field 3>"
		//              }
		//          }); 
		//      }
		// }
		{ u8"run", [](CommandFields const& fields) {return RunParser{}.special_check(fields, { u8"Path" }); }},
		{ u8"compile", [](CommandFields const& fields) {return CompileParser{}.special_check(fields, { u8"Project", u8"Lang", u8"Std", u8"File" }); }}
		
	};
	return _command_types;
}


#endif // !_ISPECIAL_PARSER_H__

