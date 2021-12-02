#pragma once

#include <memory>
#include <string>

#include "core/core_fwd.hpp"
#include "core/util/res.hpp"

namespace core::lib {

    using namespace util;

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    class S4_CORE_EXPORT Shared {
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

#ifdef _WIN32
    #pragma warning( push )
    #pragma warning( disable : 4251 ) // will be fixed after custom UniquePtr will be implemented
#endif
        Shared(std::unique_ptr<Handle> handle);
        std::unique_ptr<Handle> m_handle;
#ifdef _WIN32
    #pragma warning( pop )
#endif

    }; // class SharedLib

} // namespace core