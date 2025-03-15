#include "battle.h"
#include <string>
#include <unordered_map>

State State::smell_scale(const int choice){   
    if (choice < 6) {return State("strawberry", -1);}
    if (choice < 18) {return State("kiwi", -1);}
    if (choice < 38) {return State("rose", -1);}
    if (choice < 44) {return State("banana", -1);}
    if (choice < 49) {return State("coconut", -1);}
    if (choice < 53) {return State("lila", -1);}
    if (choice < 68) {return State("tomato", -1);}
    if (choice < 82) {return State("violet", -1);}
    if (choice < 87) {return State("mint", -1);}
    if (choice < 100) {return State("lemon", -1);}
    return State("rotten egg", -1);
}

State::State() {
    name = "normal";
    end = -1;
}

State::State(const std::string name, const int end){
    this->name = name;
    this->end = end;
}

State::State(const State &state){
    name = std::string (state.name);
    end = state.end;
}

std::string State::get_name() const {return name;}
int State::get_duration() const {return end;}
