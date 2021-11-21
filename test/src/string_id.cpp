#include <catch2/catch_test_macros.hpp>

#include <core/str/string_id.hpp>
#include <core/lib/shared.hpp>

#include <interface.hpp>

using namespace core::str;
using namespace core::lib;
using namespace core::util;
using namespace test;

//*************************************************************************************************
TEST_CASE( "Default string ids are equal", "[StringId]" ) {
    const StringId string_one;
    const StringId string_two;
    REQUIRE( string_one == string_two );
}

//*************************************************************************************************
TEST_CASE( "Default string id equals empty string", "[StringId]" ) {
    const StringId string_one;
    REQUIRE( string_one.get() == std::string() );
}

//*************************************************************************************************
TEST_CASE( "Create from std::string", "[StringId]" ) {
    const std::string string = "test";
    StringId string_id = StringId(string);
    REQUIRE( string_id.get() == string );
}

//*************************************************************************************************
TEST_CASE( "Create from c string", "[StringId]" ) {
    const char* string = "test";
    StringId string_id = StringId(string);
    REQUIRE( string_id.get() == string );
}

//*************************************************************************************************
TEST_CASE( "Two StringIds created from the same string are equal", "[StringId]" ) {
    REQUIRE( StringId("testssss") == StringId("testssss") );
}

//*************************************************************************************************
TEST_CASE( "StringId created in dynamically loaded lib is registered properly", "[StringId]" ) {
    Shared lib = Shared::open("../../dist/libs4_core_test_lib.so").ok();
    ITestInterface* test_obj 
        = reinterpret_cast<ITestInterface*(*)()>(lib.symbol("create_test_interface").ok())();
    
    const std::string src = "tests string";
    const StringId id_from_exe = StringId(src);
    const StringId id_from_lib = test_obj->register_string(src);
    REQUIRE( id_from_exe == id_from_lib );
}

