//--------------------------------------------------------------------
//  FieldSpec.h
//	11/2/2025.				created.
//  11/2/2025.				last modified.
//--------------------------------------------------------------------
#ifndef _FIELD_SPEC_H__
#define _FIELD_SPEC_H__

//--------------------------------------------------------------------------
//	Headers...
//--------------------------------------------------------------------------
#include "DefaultCommandParser.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>


//--------------------------------------------------------------------
struct Report
{
    std::vector<std::u8string> errors;      // 需要但没给
    std::vector<std::u8string> warnings;    // 给了但未声明
};


//--------------------------------------------------------------------
class FieldSpec
{
    using ErrorMsgs = std::vector<std::u8string>;
public:
    void add_field(std::u8string name);
    static FieldSpec init_field_spec(std::vector<std::u8string> fields) noexcept;
    void del_field(std::u8string name);
    Report check_presence(const CommandFields& fields, bool is_shared = false) const;

private:
    std::unordered_set<std::u8string> _fs_fields;

};


//--------------------------------------------------------------------
#endif // !_FIELD_SPEC_H__

