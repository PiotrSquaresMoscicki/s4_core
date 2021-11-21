#include "shared.hpp"

#include <dlfcn.h>

using namespace core::lib;
using namespace core::util;

//*************************************************************************************************
//*************************************************************************************************
//*************************************************************************************************
Res<Shared, Shared::ErrOpen> Shared::open(std::string path) {
    if (void* handle = dlopen(path.c_str(), RTLD_NOW | RTLD_LAZY)) {
        return Ok(Shared(handle));
    } else
        return Err(ErrOpen::UNDEFINED);
}

//*************************************************************************************************
Res<void*, Shared::ErrSymbol> Shared::symbol(std::string symbol) {
    if (void* symbol_handle = dlsym(m_handle, symbol.c_str())) {
        return Ok(symbol_handle);
    } else
        return Err(ErrSymbol::UNDEFINED);
}