#include "util/include/character_base.h"

CharacterBase character_base_init(const char* name, const unsigned int hp) {
    return (CharacterBase) {
        name, hp, hp
    };
}

void character_damage(CharacterBase* self, unsigned int damage) {
    if (damage > self->__hp) self->__hp = 0;
    else self->__hp -= damage; 
}

void character_heal(CharacterBase* self, unsigned int heal) {
    self->__hp += heal;
    if (self->__hp > self->max_hp) self->__hp = self->max_hp;
}