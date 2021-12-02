#include "shared.hpp"

#if defined(__APPLE__) || defined(__linux__)
    #include <dlfcn.h>
#elif _WIN32
    #include <windows.h> 
#endif 

using namespace core::lib;
using namespace core::util;

class Shared::Handle {
public:
#if defined(__APPLE__) || defined(__linux__)
    Handle(void* handle) : m_handle(handle) {}
    void* m_handle = nullptr;
#elif _WIN32
    Handle(HINSTANCE handle) : m_handle(handle) {}
    HINSTANCE m_handle; 
#endif 
};

//*************************************************************************************************
//*************************************************************************************************
//*************************************************************************************************
Shared::Shared(Shared&& other)
    : m_handle(std::move(other.m_handle))
{}

Shared::Shared(std::unique_ptr<Handle> handle) 
    : m_handle(std::move(handle)) 
{}

//*************************************************************************************************
Shared::~Shared() = default;

//*************************************************************************************************
Res<Shared, Shared::ErrOpen> Shared::open(const std::string& path) {
#if defined(__APPLE__) || defined(__linux__)
    if (void* handle = dlopen(path.c_str(), RTLD_NOW | RTLD_LAZY))
#elif _WIN32
    if (HINSTANCE handle = LoadLibrary(path.c_str()))
#endif 
        return Ok(Shared(std::make_unique<Handle>(handle)));
    else
        return Err(ErrOpen::UNDEFINED);
}

//*************************************************************************************************
Res<void*, Shared::ErrSymbol> Shared::symbol(const std::string& symbol) {
#if defined(__APPLE__) || defined(__linux__)
    if (void* symbol_handle = dlsym(m_handle->m_handle, symbol.c_str()))
#elif _WIN32
    if (void* symbol_handle = GetProcAddress(m_handle->m_handle, symbol.c_str()))
#endif 
        return Ok(symbol_handle);
    else
        return Err(ErrSymbol::UNDEFINED);
}