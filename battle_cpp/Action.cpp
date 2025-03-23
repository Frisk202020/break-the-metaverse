#include "battle.h"
#include <iostream>
#include <unordered_map>
#include <string>

bool Action::is_successful() const {return happening(this->odd);}
std::string Action::get_name() const {return name;}
State Action::get_state() const {return State(state);}
int Action::get_pow() const {return pow;}
int Action::get_heal() const {return heal;}
int Action::get_odd() const {return odd;}
char Action::get_range() const {return aim;}
char Action::get_type() const {return type;}
bool Action::is_superguardable() const {return superguard;}
void Action::upgrade(const int pow_buff, const int heal_buff) {pow *= pow_buff; heal *= heal_buff;} 
void Action::ban() { type = 'l'; odd = 0; }

Action::Action() {
    name = "default";
    pow = 0;
    heal = 0;
    state = State();
    aim = ' ';
    type = ' ';
    superguard = false;
    odd = 0;
}

Action::Action(const std::string name, const int pow, const int heal, const State &state, const char aim, const char type, const bool superguard, const int odd) {
    this->name = name;
    this->pow = pow;
    this->heal = heal;
    this->state = state;
    this->aim = aim;
    this->type = type;
    this->superguard = superguard;
    this->odd = odd;
}

Action::Action(const Action &action) {
    name = std::string (action.name);
    pow = action.pow;
    heal = action.heal;
    state = State (action.state);
    aim = action.aim;
    type = action.type;
    superguard = action.superguard;
    odd = action.odd;
}

std::unordered_map<std::string, Action> Action::action_library = {
    {"taser", Action("taser", 10, 0, State("stun", 1), 'e', 'g', false, 100)},
    {"sword", Action("sword", 100, 0, State(), 'e', 'g', false, 100)},
    {"provoke", Action("provoke", 0, 0, State("provoke", 2), 'e', 'l', false, 80)},
    {"hack", Action("hack", 500, 0, State(), 'e', 'r', false, 100)},
    {"shield", Action("shield", 0, 100, State("defense", 1), 'a', 'g', false, 100)},
    {"potion", Action("potion", 0, 0, State("corrupt", INT8_MAX), 'e', 'g', false, 100)},
    {"encyclopedia", Action("encyclopedia", 0, 0, State(), 'e', 'g', false, 100)},
    {"stone", Action("stone", 0, 50, State("defense", 3), 'i', 'g', false, 100)},
    {"hammer", Action("hammer", 300, 0, State("danger", 1), 'e', 'g', false, 100)},
    {"betrayal", Action("betrayal", 0, 0, State(), 'e', 'g', false, 100)},
    {"retreat", Action("retreat", 0, 100, State("defense", 3), 'i', 'g', false, 100)},
    {"focus", Action("focus", 0, 0, State("focus", 1), 'i', 'l', false, 100)},
    {"clone", Action("clone", 0, 0, State("clone", 3), 'i', 'g', false, 100)},
    {"knife", Action("knife", 300, 0, State(), 'e', 'r', false, 100)},
    {"gold", Action("gold", 40, 0, State("boost", -1), 'i', 'l', false, 60)},
    {"firebreath", Action("firebreath", 50, 0, State(), 'a', 'l', false, 40)},
    {"stomp", Action("stomp", 70, 0, State(), 'i', 'l', true, 35)},
    {"bite", Action("bite", 30, 100, State(), 'i', 'l', false, 20)},
    {"claw", Action("claw", 1000, 0, State(), 'i', 'l', false, 5)},
    {"protect", Action("protect", 0, 0, State("vulnerable", 1), 'i', 'l', false, 100)},
    {"smell", Action("smell", 0, 0, State("smell", 1), 'i', 'l', false, 100)},
    {"vertical", Action("vertical swing", 8, 0, State(), 'i', 'l', true, 40)},
    {"hoizontal", Action("horizontal swing", 8, 0, State(), 'i', 'l', true, 40)},
    {"smell", Action("kaméhaméha", 10, 0, State(), 'i', 'l', true, 20)},
};

Action Action::get_action_from_library(const std::string request){    
    if (action_library.contains(request)){
        return Action(action_library[request]);
    }

    std::cout << "Returned default action";
    return Action();
}


