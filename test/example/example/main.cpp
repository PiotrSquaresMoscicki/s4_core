#include <iostream>

#include <core/ctti/ctti.hpp>

using namespace std;

using namespace core::collections;
using namespace core::ctti;

namespace Game {
class Entity {
    DECLARE_STRUCT(Game::Entity)
    END_STRUCT

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
    
    cout << "entity_ti_len = " << entity_ti_len << endl;
    cout << "entity_ti_name = " << entity_ti_name.get() << endl;
    cout << "entity_ti_sizeof = " << entity_ti_sizeof << endl;
    cout << "entity_ti_is_class = " << entity_ti_is_class << endl;
    cout << "entity_ti_is_fundamental = " << entity_ti_is_fundamental << endl;

    constexpr auto all = Tuple(12, 23/*, 34.34, 23, "sdfsdf", 3333*/);
    constexpr auto ints = all.get_all<int>();
    
    cout << "ints.length() = " << ints.length() << endl;
    cout << "ints.at<0>() = " << ints.at<0>() << endl;
    cout << "ints.at<1>() = " << ints.at<1>() << endl;
}