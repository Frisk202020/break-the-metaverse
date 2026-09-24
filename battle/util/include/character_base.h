#ifndef CHARACTER_BASE_H
#define CHARACTER_BASE_H

typedef struct character_base {
    const char* name;
    const unsigned int max_hp;
    unsigned int __hp;
} CharacterBase;

CharacterBase character_base_init(const char* name, const unsigned int hp);
void character_damage(CharacterBase* self, unsigned int damage);
void character_heal(CharacterBase* self, unsigned int heal);

#endif