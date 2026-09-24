#include "character.h"

Character character_init(
    const char* name, const unsigned int hp,  
    const unsigned int pow, Action actions[3]
) {
    return (Character) {
        character_base_init(name, hp), pow, actions
    };
}

Character dragon_init() {
    Action* actions = malloc(4 * sizeof(Action));

    return (Character) {
        character_base_init("Dragon", 1000), 0, 4, actions
    };
}


