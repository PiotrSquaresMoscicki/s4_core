#include "lib.hpp"

using namespace core::str;
using namespace test;

//*************************************************************************************************
//*************************************************************************************************
//*************************************************************************************************
class TestInterfaceImpl : public ITestInterface {
public:
    StringId register_string(const std::string& src) override;
    
}; // TestInterfaceImpl

//*************************************************************************************************
StringId TestInterfaceImpl::register_string(const std::string& src) {
    return StringId(src);
}

extern "C" test::ITestInterface* create_test_interface() {
    return new TestInterfaceImpl{};
}