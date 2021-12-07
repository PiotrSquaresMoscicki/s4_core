#include <interface.hpp>

using namespace core::str;
using namespace test;

#ifdef _WIN64
    #define S4_TEST_LIB_EXPORT __declspec(dllexport)
#else
    #define S4_TEST_LIB_EXPORT
#endif

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

extern "C" S4_TEST_LIB_EXPORT test::ITestInterface* create_test_interface() {
    return new TestInterfaceImpl{};
}