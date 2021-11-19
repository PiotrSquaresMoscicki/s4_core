#pragma once

#include <memory>

namespace core {

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    class StringId {
    public:
        StringId();
        explicit StringId(const char* src);
        explicit StringId(const std::string& src);

        bool operator== (const StringId& other) const;
        const std::string& get() const { return *m_data; }

    private:
        std::shared_ptr<const std::string> m_data = nullptr;

    }; // class StringId

} // namespace core::strings
