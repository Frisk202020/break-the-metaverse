#ifndef BATTLE_H_
#define BATTLE_H_

#include <string>
#include <array>
#include <vector>
#include <unordered_map>

class State {
    private:
        std::string name;
        int end;

    public:
        State();
        State(const std::string name, const int end);
        State(const State &state);

        std::string get_name() const;
        int get_duration() const;
        static State smell_scale(const int choice);
};

class Action {
    private:
        std::string name;
        int pow;
        int heal;
        State state;
        char aim;
        char type;
        bool superguard;
        int odd;
        static std::unordered_map<std::string, Action> action_library;

    public:
        Action();
        Action(const std::string name, const int pow, const int heal, const State &state, const char aim, const char type, const bool superguard, const int odd);
        Action(const Action &action);
        static Action get_action_from_library(const std::string request);
        bool is_successful() const;
        std::string get_name() const;
        State get_state() const;
        int get_pow() const;
        int get_heal() const;
        int get_odd() const;
        char get_range() const;
        char get_type() const;
        bool is_superguardable() const;
        void upgrade(const int pow_buff, const int heal_buff);
};

class Character {
    private:
        std::string name;
        int max_hp;
        int hp;
        int pow;
        int def;
        State state;
        State smell;
        int dice;
        std::vector<Action> actions;
        
        Character(const std::string &name, const int max_hp, const int pow, const int def, const State &state, const State &smell, const int dice, const std::vector<Action> &actions);
        int dice_range(const int result) const;

    public:
        Character();
        static Character initialize_derek_dragon();
        static Character initialize_flavie_dragon();
        static Character initialize_haloise_dragon();
        static Character initialize_xhara_dragon();
        static Character initialize_clover_dragon();
        static Character initialize_dragon();

        static Character initialize_derek_sensei();
        static Character initialize_flavie_sensei();
        static Character initialize_haloise_sensei();
        static Character initialize_xhara_sensei();
        static Character initialize_clover_sensei();
        static Character initialize_sensei();

        std::string get_name() const;
        int get_hp() const;
        int get_max_hp() const;
        int get_pow() const;
        State get_state() const;
        int attack(const int result) const;
        int get_number_of_actions() const;
        Action choose_enemy_action() const;
        void print_life_bar() const;
        void print_character(const bool is_enemy) const;
        void print_character_as_student() const;
        void print_character_as_magician() const;

        void set_state(const State &state);
        void state_back_to_normal();
        void boost(const double multiplier);
        void set_def(const int def);
        void damage(const int damage);
        void set_hp_to_zero();
        void set_hp_to_max();
        void revive();
        void remove_firebreath();
        void upgrade_action(const int id, const int pow_buff, const int heal_buff);
};

class Stats {
    private:
        std::unordered_map<std::string, Character> team;
        std::unordered_map<std::string, Character> enemies;
        std::string default_enemy;
        int turn;
        int* orb;
        int nb_spirit;
        int* took;

        Stats(const Character &derek, const Character &flavie, const Character &haloise, const Character &xhara, const Character &clover, const Character &enemy);
        bool is_team_done() const;
        bool are_enemies_done() const;
        Character* pick_random_target();
        void dragon_or_sensei_attack();
        void spirit_attack(Character &enemy);
        void final_attack(Character &enemy);
        void claim_soul(Character &owner);
        void update_task(Character &ch);

    public:
        bool is_end() const;
        void print_state() const;
        void update_stats();
        Stats dragon_initializer();
        void execute_action(const Action &act, Character &thrower, Character &target);
        void enemy_attack(Character &enemy);
        void claim_souls();
};

//from utilities.cpp
int entropy(const int value, const int min, const int var);
bool happening(const int odd);
int parse_int(const std::string &s);
int ask_for_superguard(const std::string &name);

/*
//from sensei.c
stats sensei_initialize();
state smell_scale(int choice);

//from spirit.c
state NULL_STATE();
char* merge_magic(int i, int j);
character create_spirit(char* name, int name_length, state st);
stats choose_spirit(stats s, char* name, int name_length, state st);
stats spirit_initialize(char* spirit, int name_length, state new_state);
stats check_weakness(stats s);

//from final.c
stats final_initialize();
*/

#endif