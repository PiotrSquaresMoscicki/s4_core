#pragma once

#include <string>

#include <core/util/res.hpp>

namespace core::lib {

    using namespace util;

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    class Shared {
    public:
        enum class ErrOpen {
            UNDEFINED
        };

        enum class ErrSymbol {
            UNDEFINED
        };

        static Res<Shared, ErrOpen> open(std::string path);

        Res<void*, ErrSymbol> symbol(std::string symbol);

    private:
        Shared(void* handle) : m_handle(handle) {}

        void* m_handle = nullptr;
        //std::string 

    }; // class SharedLib

} // namespace core