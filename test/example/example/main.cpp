#include <iostream>

#include <core/ctti/ctti.hpp>

using namespace std;

using namespace core::collections;
using namespace core::ctti;

namespace Game {
class Entity {
    CTTI_DECLARE_CLASS(Game::Entity)
    CTTI_END

}; // class Entity

} // namespace Game

using namespace Game;

int main() {
    std::cout << "Hello World!" << std::endl;

    constexpr auto entity_ti = get_type_info<Entity>();
    constexpr auto entity_ti_len = entity_ti.length();
    constexpr auto entity_ti_name = entity_ti.get_name();
    constexpr auto entity_ti_is_class = entity_ti.is_class();
    
    cout << "entity_ti_len = " << entity_ti_len << endl;
    cout << "entity_ti_name = " << entity_ti_name.get() << endl;
    cout << "entity_ti_is_class = " << entity_ti_is_class << endl;
}