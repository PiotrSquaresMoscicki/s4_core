#pragma once

#include <memory>

namespace core::str {

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    class StringId {
    public:
        StringId();
        explicit StringId(const char* src);
        explicit StringId(const std::string& src);
        ~StringId();

        bool operator== (const StringId& other) const;
        const std::string& get() const { return *m_data; }

    private:
        std::shared_ptr<const std::string> m_data = nullptr;

    }; // class StringId

} // namespace core::strings
