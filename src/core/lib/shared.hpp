#pragma once

#include <memory>
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

        Shared(Shared&& other);
        ~Shared();

        static Res<Shared, ErrOpen> open(const std::string& path);

        Res<void*, ErrSymbol> symbol(const std::string& symbol);

    private:
        class Handle;

        Shared(std::unique_ptr<Handle> handle);
        std::unique_ptr<Handle> m_handle;

    }; // class SharedLib

} // namespace core