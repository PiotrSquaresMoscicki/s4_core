#include <catch2/catch_test_macros.hpp>

#include <core/string_id.hpp>

//*************************************************************************************************
TEST_CASE( "Default string ids are equal", "[StringId]" ) {
    const core::StringId string_one;
    const core::StringId string_two;
    REQUIRE( string_one == string_two );
}

//*************************************************************************************************
TEST_CASE( "Default string id equals empty string", "[StringId]" ) {
    const core::StringId string_one;
    REQUIRE( string_one.get() == std::string() );
}

//*************************************************************************************************
TEST_CASE( "Create from std::string", "[StringId]" ) {
    const std::string string = "test";
    core::StringId string_id = core::StringId(string);
    REQUIRE( string_id.get() == string );
}

//*************************************************************************************************
TEST_CASE( "Create from c string", "[StringId]" ) {
    const char* string = "test";
    core::StringId string_id = core::StringId(string);
    REQUIRE( string_id.get() == string );
}