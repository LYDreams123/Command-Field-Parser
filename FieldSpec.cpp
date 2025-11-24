//--------------------------------------------------------------------
//  FieldSpec.cpp
//	11/2/2025.				created.
//  11/16/2025.				last modified.
//--------------------------------------------------------------------
#include "FieldSpec.h"


//--------------------------------------------------------------------
// 增加一个字段
//--------------------------------------------------------------------
void parser::details::FieldSpec::add_field(std::u8string name)
{
    _fs_fields.insert(std::move(name));
}


//--------------------------------------------------------------------
// 初始化 FieldSpec
//--------------------------------------------------------------------
parser::details::FieldSpec parser::details::FieldSpec::init_field_spec(std::vector<std::u8string> fields) noexcept
{
    FieldSpec fs;
    for (auto const& field : fields)
    {
        fs.add_field(field);
    }
    return fs;
}


//--------------------------------------------------------------------
// 删除一个字段
//--------------------------------------------------------------------
void parser::details::FieldSpec::del_field(std::u8string name)
{
    _fs_fields.erase(name);
}


//--------------------------------------------------------------------
// 检查字段是否正确
//--------------------------------------------------------------------
parser::details::Report parser::details::FieldSpec::check_presence(const CommandFields& fields, bool is_shared) const
{
    Report rep;

    // 缺少字段
    for (auto const& need : _fs_fields)
    {
        if (fields.find(need) == fields.end())
        {
            rep.errors.push_back(u8"Missing field:" + need);
        }
    }

    if (!is_shared)
    {
        // 多余字段
        for (auto const& kv : fields)
        {
            if (_fs_fields.find(kv.first) == _fs_fields.end())
            {
                rep.warnings.push_back(u8"Extra field:" + kv.first);
            }
        }
    }

    return rep;
}


//--------------------------------------------------------------------

