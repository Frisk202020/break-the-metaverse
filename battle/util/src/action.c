#include "action.h"

Action action_init(const char* name, const char* description) {
    return (Action) {
        name, description
    };
}

Action action_init_derek_shared() {
    return (Action){
        "Taser", "Stun an enemy for 3 turns"
    };
}

Action action_init_flavie_shared() {
    return (Action){
        "Hack", 
        "Hack the metaverse to inflict massive damage to one enemy"
    };
}

Action action_init_haloise_shared() {
    return (Action){
        "Encyclopidia", "Learn information about the enemy"
    };
}

Action action_init_clover_shared() {
    return (Action){
        "Clones", 
        "Create 2 clones, giving you a 66\% chance to dodge for 3 turns"
    };
}

Action action_init_xhara_shared() {
    return (Action){
        "Potion", 
        "Give a potion to one party member which allows to dodge the following attack"
    };
}