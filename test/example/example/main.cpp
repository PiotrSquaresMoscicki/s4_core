#include <iostream>

#include <core/ctti/ctti.hpp>

using namespace std;

using namespace core::collections;
using namespace core::ctti;
using namespace core;

namespace Game {
class Entity {
    DECLARE_STRUCT(Game::Entity)
        DECLARE_PROPERTY(m_int, attr::Name("dupeaaaa"), attr::Name("asdasd"), attr::Name("adssssss"))
        DECLARE_PROPERTY(m_float)
    END_STRUCT

public:
    int m_int = 0;
    float m_float = 0;

}; // class Entity

} // namespace Game

using namespace Game;

int main() {
    std::cout << "Hello World!" << std::endl;

    constexpr auto entity_ti = get_type_info<Entity>();
    constexpr auto entity_ti_len = entity_ti.length();
    constexpr auto entity_ti_name = entity_ti.get_name();
    constexpr auto entity_ti_sizeof = entity_ti.get_sizeof();
    constexpr auto entity_ti_is_class = entity_ti.is_struct();
    constexpr auto entity_ti_is_fundamental = entity_ti.is_fundamental();

    constexpr auto entity_ti_properties = entity_ti.get_properties();
    constexpr auto entity_ti_properties_len = entity_ti_properties.length();
    constexpr auto first_property = entity_ti_properties.at<0>();
    constexpr auto first_property_name = first_property.get_name();
    constexpr auto first_property_names_len = first_property.get_all<attr::Name>().length();
    

    cout << "entity_ti_len = " << entity_ti_len << endl;
    cout << "entity_ti_name = " << entity_ti_name.get() << endl;
    cout << "entity_ti_sizeof = " << entity_ti_sizeof << endl;
    cout << "entity_ti_is_class = " << entity_ti_is_class << endl;
    cout << "entity_ti_is_fundamental = " << entity_ti_is_fundamental << endl;
    cout << "entity_ti_properties_len = " << entity_ti_properties_len << endl;
    cout << "first_property_name = " << first_property_name.get() << endl;
    cout << "first_property_names_len = " << first_property_names_len << endl;


}