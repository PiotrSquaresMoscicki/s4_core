#include "string_id.hpp"

#include <string>
#include <unordered_map>

using namespace core::str;

namespace {
    std::unordered_map<std::string, std::shared_ptr<const std::string>> g_string_id_map;
    
    //*********************************************************************************************
    std::shared_ptr<const std::string> register_string(const std::string& string)
    {
        std::shared_ptr<const std::string>& result = g_string_id_map[string];
        
        if (result == nullptr)
            result = std::make_shared<std::string>(string);
        
        return result;
    }
    
    //*********************************************************************************************
    void unregister_string(std::shared_ptr<const std::string>&& string)
    {
        // function param and one in the map
        if (string.use_count() == 2)
            g_string_id_map.erase(*string);
    }

} // namespace

//*************************************************************************************************
//*************************************************************************************************
//*************************************************************************************************
StringId::StringId() 
    : m_data(register_string({}))
{}

//*************************************************************************************************
StringId::StringId(const char* src) 
    : m_data(register_string(src))
{}

//*************************************************************************************************
StringId::StringId(const std::string& src) 
    : m_data(register_string(src))
{}

//*************************************************************************************************
bool StringId::operator== (const StringId& other) const {
    return m_data == other.m_data;
}