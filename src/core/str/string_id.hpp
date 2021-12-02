#pragma once

#include <memory>
#include <string>

#include "core/core_fwd.hpp"

namespace core::str {

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    class S4_CORE_EXPORT StringId {
    public:
        StringId();
        explicit StringId(const char* src);
        explicit StringId(const std::string& src);
        ~StringId();

        bool operator== (const StringId& other) const;
        bool operator< (const StringId& other) const;
        const std::string& get() const { return *m_data; }

    private:
#ifdef _WIN32
    #pragma warning( push, C4251 ) // will be fixed after custom SharedPtr will be implemented
#endif
        std::shared_ptr<const std::string> m_data = nullptr;
#ifdef _WIN32
    #pragma warning( pop )
#endif
    }; // class StringId

} // namespace core::strings
