#include "battle.h"
#include <string>
#include <iostream>

void Character::print_life_bar() const {
    int N = 20 * hp / max_hp;
    printf("\033[0;32m");
    for (int i = 0; i < N; i++){
        printf("|");
    }
    printf("\033[0;31m");
    for (int i = N; i < 20; i++){
        printf("|");
    }
}
void Character::print_character(const bool is_enemy) const {
    if (is_enemy) {
        printf("\033[0;31m \nBoss : \033[0;35m ♥ %d  ", hp); 
        this->print_life_bar();
        if (hp <= 0) {printf("\033[0;31m%s : DOWN \033[0;0m\n", name.c_str());}
        else {printf("\033[0;31m [%s] \033[0;0m\n\n", state.get_name().c_str());}
        return;
    }

    printf("\033[0;31m \nBoss : \033[0;35m ♥ %d  ", hp); 
    this->print_life_bar();
    if (hp <= 0 ) {
        if (state.get_name() == "dead") {printf("\033[0;31m%s : DEAD \033[0;0m\n", name.c_str());}
        else {printf("\033[0;31m%s : DOWN \033[0;0m\n", name.c_str());}
    } else {printf("\033[0;31m [%s] \033[0;0m\n\n", state.get_name().c_str());}
}
void Character::print_character_as_student() const {}
void Character::print_character_as_magician() const {}

std::string Character::get_name() const {return name;}
int Character::get_hp() const {return hp;}
int Character::get_max_hp() const {return max_hp;}
int Character::get_pow() const {return pow;}
State Character::get_state() const {return state;}
void Character::set_state(const State &state) {this->state = state;}
void Character::state_back_to_normal() {
    if (state.get_name() == "defense") {def = 0;}
    else if (state.get_name() == "weakened") {pow *= 5;}
    else if (state.get_name() == "confuse") {pow /= 5;}

    state = State();
}
void Character::set_def(const int def) {this->def = def;}
void Character::boost(const double multipier) {pow *= multipier;}
void Character::damage(const int damage) {hp -= damage;}
void Character::set_hp_to_zero() {hp = 0;}
void Character::set_hp_to_max() {hp = max_hp;}
void Character::revive() {hp = max_hp; state = State();}
int Character::get_number_of_actions() const {return actions.size();}
void Character::upgrade_action(const int id, const int pow_buff, const int heal_buff) {
    if (id < (int) actions.size()) {actions[id].upgrade(pow_buff, heal_buff);}
    else {std::cout << "Invalid action id";}
}
void Character::remove_firebreath() {
    if (name == "Dragon") {actions.pop_back();} // firebreath implemented to be the last element of the actions vector
    printf("033[0;32m Can't remove an action for this enemy \033[0;0m");
}

Action Character::choose_enemy_action() const {
    std::vector<int> v; v.reserve(100);
    for (int act_id = 0; act_id < (int) actions.size(); act_id++) {
        for (int i = 0; i < actions[act_id].get_odd(); i++){
            v.push_back(act_id);
        }    
    }

    if (v.size() > 100) {std::cout << "Warning: enemy may not have been initialized correctly (sum of act odds > 100%) !\n";}
    int ind = v[rand() % v.size()];
    return actions[ind];
}

int Character::dice_range(int result) const {
    switch (dice) {
        case 4 : return result - 1;
        case 6 :
            if (result == 1) {return 0;}
            else if (result == 6) {return 3;}
            else if (result == 2 || result == 3) {return 1;}
            return 2;
        case 8:
            if (result == 1) {return 0;}
            else if (result == 8) {return 3;}
            else if (result == 2 || result == 3) {return 1;}
            return 2;
        case 10:
            if (result == 1) {return 0;}
            else if (result == 10) {return 3;}
            else if (result == 8 || result == 9) {return 1;}
            return 2;
        case 12:
            if (result < 5) {return 0;}
            else if (result < 9) {return 1;}
            else if (result == 12) {return 3;}
            return 2;
        case 20:
            if (result == 20) {return 3;}
            else if (result < 8) {return 0;}
            else if (result < 16) {return 1;}
            return 2;
        case 30:
            if (result == 1) {return 0;}
            else if (result == 30) {return 3;}
            else if (result < 16) {return 1;}
            return 2;
    }
    return 0; // never reached
}

int Character::attack(int result) const {
    if (state.get_name() == "focus success") {return 3 * pow;}

    switch (this->dice_range(result)) {
        case 0: return entropy(pow, 10, 10);
        case 1: return entropy(pow, 20, 30);
        case 2: return entropy(pow, 50, 40);
        case 3: return pow;
        default: std::cout << "Default attack value: returning 0" << '\n'; return 0;
    }
}

Character::Character() {
    name = "";
    max_hp = 0;
    hp = 0;
    pow = 0;
    def = 0;
    state = State();
    smell = State();
    dice = 0;
    actions = std::vector<Action>();
}

Character::Character(const std::string &name, const int max_hp, const int pow, const int def, const State &state, const State &smell, const int dice, const std::vector<Action> &actions) {
    this->name = name;
    this->max_hp = max_hp;
    this->hp = max_hp;
    this->pow = pow;
    this->def = def;
    this->state = state;
    this->smell = smell;
    this->dice = dice;
    this->actions = actions;
}

Character Character::initialize_derek_dragon() {
    std::string name = "Derek";
    int max_hp = 250;
    int pow = 50;
    int def = 0;
    int dice = 6;
    std::vector<Action> actions = {Action::get_action_from_library("taser"), Action::get_action_from_library("sword"), Action::get_action_from_library("provoke")};

    return Character (name, max_hp, pow, def, State(), State(), dice, actions); 
}

Character Character::initialize_flavie_dragon() {
    std::string name = "Flavie";
    int max_hp = 120;
    int pow = 20;
    int def = 0;
    int dice = 30;
    std::vector<Action> actions = {Action::get_action_from_library("hack"), Action::get_action_from_library("shield"), Action::get_action_from_library("potion")};

    return Character (name, max_hp, pow, def, State(), State(), dice, actions); 
}

Character Character::initialize_haloise_dragon() {
    std::string name = "Haloïse";
    int max_hp = 350;
    int pow = 10;
    int def = 0;
    int dice = 10;
    std::vector<Action> actions = {Action::get_action_from_library("encyclopedia"), Action::get_action_from_library("stone"), Action::get_action_from_library("hammer")};

    return Character (name, max_hp, pow, def, State(), State(), dice, actions); 
}

Character Character::initialize_xhara_dragon() {
    std::string name = "Xhara";
    int max_hp = 150;
    int pow = 30;
    int def = 0;
    int dice = 20;
    std::vector<Action> actions = {Action::get_action_from_library("betrayal"), Action::get_action_from_library("retreat"), Action::get_action_from_library("focus")};

    return Character (name, max_hp, pow, def, State(), State(), dice, actions); 
}

Character Character::initialize_clover_dragon() {
    std::string name = "Clover";
    int max_hp = 80;
    int pow = 60;
    int def = 0;
    int dice = 4;
    std::vector<Action> actions = {Action::get_action_from_library("clone"), Action::get_action_from_library("knife"), Action::get_action_from_library("gold")};

    return Character (name, max_hp, pow, def, State(), State(), dice, actions); 
}

Character Character::initialize_dragon() {
    std::string name = "Dragon";
    int max_hp = 1000;
    int pow = 0;
    int def = 0;
    int dice = 0;
    std::vector<Action> actions = {Action::get_action_from_library("stomp"), Action::get_action_from_library("bite"), Action::get_action_from_library("claw"), Action::get_action_from_library("firebreath")};

    return Character (name, max_hp, pow, def, State(), State(), dice, actions); 
}

Character Character::initialize_derek_sensei() {
    std::string name = "Derek";
    int max_hp = 20;
    int pow = 1;
    int def = 0;
    int dice = 6;
    std::vector<Action> actions = {Action::get_action_from_library("taser"), Action::get_action_from_library("protect"), Action::get_action_from_library("smell")};

    return Character (name, max_hp, pow, def, State(), State(), dice, actions); 
}

Character Character::initialize_flavie_sensei() {
    std::string name = "Flavie";
    int max_hp = 20;
    int pow = 1;
    int def = 0;
    int dice = 6;
    std::vector<Action> actions = {Action::get_action_from_library("hack"), Action::get_action_from_library("protect"), Action::get_action_from_library("smell")};

    return Character (name, max_hp, pow, def, State(), State(), dice, actions); 
}

Character Character::initialize_haloise_sensei() {
    std::string name = "Haloise";
    int max_hp = 20;
    int pow = 1;
    int def = 0;
    int dice = 6;
    std::vector<Action> actions = {Action::get_action_from_library("encyclodia"), Action::get_action_from_library("protect"), Action::get_action_from_library("smell")};

    return Character (name, max_hp, pow, def, State(), State(), dice, actions); 
}

Character Character::initialize_clover_sensei() {
    std::string name = "Clover";
    int max_hp = 20;
    int pow = 1;
    int def = 0;
    int dice = 6;
    std::vector<Action> actions = {Action::get_action_from_library("clone"), Action::get_action_from_library("protect"), Action::get_action_from_library("smell")};

    return Character (name, max_hp, pow, def, State(), State(), dice, actions); 
}

Character Character::initialize_xhara_sensei() {
    std::string name = "Xhara";
    int max_hp = 20;
    int pow = 1;
    int def = 0;
    int dice = 6;
    std::vector<Action> actions = {Action::get_action_from_library("retreat"), Action::get_action_from_library("protect"), Action::get_action_from_library("smell")};

    return Character (name, max_hp, pow, def, State(), State(), dice, actions); 
}

Character Character::initialize_sensei() {
    std::string name = "Sensei";
    int max_hp = 20;
    int pow = 0;
    int def = 0;
    int dice = 0;
    std::vector<Action> actions = {Action::get_action_from_library("vertical"), Action::get_action_from_library("horizontal"), Action::get_action_from_library("kamehameha")};

    return Character (name, max_hp, pow, def, State(), State(), dice, actions); 
}

