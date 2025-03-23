#include "battle.h"
#include <string>
#include <iostream>

void Stats::__debug__revive(std::string ch) {
    if (team.contains(ch)) {team[ch].revive(); return;}
    if (enemies.contains(ch)) {enemies[ch].revive(); return;}
    std::cout << "Unrecognized character" << '\n';
}

void Stats::__debug__increment_turn() {turn++;}

void Stats::__debug__manage_hp(std::string ch, int hp) {
    if (team.contains(ch)) {team[ch].__debug__manage_hp(hp); return;}
    if (enemies.contains(ch)) {enemies[ch].__debug__manage_hp(hp); return;}
    std::cout << "Unrecognized character" << '\n';
}

void Stats::attack_dragon_battle(const std::string &attacker, const int dice_score) {
    if (team.contains(attacker)) {
        Character* ch = &team[attacker];
        if (ch->get_hp() <= 0) {printf("\033[0;31m You can't attack with a K-O character \033[0;0m\n"); return;}
        int pow = ch->attack_power(dice_score);
        enemies[default_enemy].damage(pow);
        return;
    }
    if (attacker == default_enemy) {
        default_enemy_attack();
        return;
    }
    std::cout << "Unrecognized attacker !\n";
}

void Stats::print_state() const {
    printf("\033[0;37m");
    printf("\n*** turn %d ***\n", turn);
    if (enemies.contains("Dragon")) {
        enemies.at("Dragon").print_character(true);
        for (auto &kv: team) {
            kv.second.print_character(false);
        }
    } 
    if (enemies.contains("Sensei")) {

    }
    else {

    }
}

bool Stats::is_team_done() const {
    for (auto &kv: team) {
        if (kv.second.get_hp() > 0) {return false;}
    }
    return true;
}

bool Stats::are_enemies_done() const {
    for (auto &kv: enemies) {
        if (kv.second.get_hp() > 0) {return false;}
    }
    return true;
}

bool Stats::is_end() const {return is_team_done() || are_enemies_done();}

void Stats::update_task(Character &ch) {
    if (ch.get_hp() < 0) {ch.set_hp_to_zero();}
    else if (ch.get_hp() > ch.get_max_hp()) {ch.set_hp_to_max();}

    if (turn == ch.get_state().get_duration()) {ch.state_back_to_normal(turn);}
}

void Stats::update_stats() {
    for (auto &kv: team) {update_task(kv.second);}
    for (auto &kv: enemies) {update_task(kv.second);}
}

void Stats::default_enemy_attack() {turn++; enemy_attack(default_enemy);}

void Stats::enemy_attack(const std::string &enemy){
    if (enemies.contains("Dragon") || enemies.contains("Sensei")) {
        this->dragon_or_sensei_attack();
        return;
    }

    if (!enemies.contains(enemy)) {std::cout << "Unrecognized enemy !\n"; return;}
    if (enemies.contains("Virus")) {
        this->final_attack(enemies[enemy]);
        return;
    }
    this->spirit_attack(enemies[enemy]);
}

void Stats::final_attack(Character &enemy) {} // To implement
void Stats::spirit_attack(Character &enemy) {} // To implement

void Stats::dragon_or_sensei_attack() {
    Character* enemy = &enemies["Dragon"];
    if (enemy->get_state().get_name() == "stun") {
        printf("\033[0;31m %s recovers \033[0;0m\n", enemy->get_name().c_str());
        return;
    }
    
    Action act = enemy->choose_enemy_action();
    std::cout << default_enemy << " attacks with " << act.get_name() << " !\n";
    int pow = act.get_pow();
    if (act.get_range() == 'a') {
        for (auto &kv: team) {
            switch (ask_for_superguard(kv.first)) {
                case -1: kv.second.damage(2 * pow);
                case 0: kv.second.damage(pow);
                case 1: continue;
            }
        }
        return;
    }

    
    Character* target;
    std::string provoker = enemy->get_state().get_name();

    if (team.contains(provoker)) {
        target = &team[provoker];
    } else {
        target = pick_random_target();
    }

    bool did_attack = true;
    std::string prompt = "";
    if (target->get_state().get_name() == "clone") {
        std::cout << "Ask Clover which clone is the real one (left, middle, right).\n";
        std::cout << "Then prompt 0 if he chose the left one, 1 for middle, 2 for right : ";
        std::getline(std::cin, prompt);
        int enemy_pick = 0;
        try {
            if (enemy_pick == parse_int(prompt)) { printf("\033[32mdodge successful\n"); }
            else { target->damage(pow); }
        } catch (std::invalid_argument &e) {
            printf("\n\033[31mFailed to parse prompt as int: assuming dodge failed\033[0m\n");
            std::cout << "Dragon picked clone located at " << enemy_pick;
            std::cout << ", use 'heal [picked_target] [hp]' to undo this attack if it should have been dodged !\n";
        }
    } else if (act.is_superguardable()) {
        switch (ask_for_superguard(target->get_name())) {
            case -1: target->damage(2 * pow);
            case 0: target->damage(pow);
            case 1: did_attack = false;
        }   
    } else {
        target->damage(pow);
    }
    
    if (did_attack) {
        enemy->damage(-act.get_heal()); // heal if action heals
    }
}

Character* Stats::pick_random_target() {
    std::vector<std::string> v; v.reserve(5);
    for (auto &kv: team) {
        if (kv.second.get_hp() > 0) {
            v.push_back(kv.first);
        }
    }

    v.shrink_to_fit();
    return &team[v[rand() % v.size()]];
}

void Stats::execute_action(const std::string &act_str, const std::string &thrower_str, const std::string &target_str){
    if (!team.contains(thrower_str)) { std::cout << "Thrower not found\n"; return; }
    Character* thrower = &team[thrower_str];
    Character* target = nullptr;

    Action act = Action();
    try {
        act = thrower->get_action(act_str);
    }    
    catch (std::invalid_argument &e) { std::cout << e.what() << '\n'; return; }
    int pow = act.get_pow();
    int heal = act.get_heal();
    State act_state = act.get_state();
    int odd = act.get_odd();
    if (odd < 100) {
        if (!happening(odd)) {std::cout << "Action failed...\n"; return;}
    }

    std::string prompt = "";
    switch (act.get_type()) {
        case 'r': 
            std::cout << "Look at the battle book do check action's success condition. Should the action be executed ?\n";
            std::getline(std::cin, prompt);
            if (prompt[0] != 'y') {std::cout << "Action failed !\n"; return;}
        case 'g': thrower->ban_action(act.get_name()); break;
    }

    if (target_str != "") {
        if (team.contains(target_str)) { target = &team[target_str]; }
        else if (enemies.contains(target_str)) { target = &enemies[target_str]; }
        else { std::cout << "Target not found\n"; return; }
    } else {
        switch (act.get_range()) {
            case 'i': std::cout << "No target specified : assuming self\n"; target = thrower; break;
            case 'e': target = &enemies[default_enemy]; target->damage(pow); break;
        }
    }

    if (act_state.get_name() == "normal") {
        return;
    }

    if (act_state.get_name() == "stun"){
        target->set_state(State ("stun", turn + act_state.get_duration()));
        printf("\033[0;32m The enemy can't attack for the following turn \033[0;0m\n");
        return;
    } 
    
    if (act_state.get_name() == "provoke") {
        target->set_state(State ("Derek", turn + act_state.get_duration()));
        printf("\033[0;32m The enemy will focus Derek for 2 turns \033[0;0m\n");
        return;
    } 
    
    if (act_state.get_name() == "corrupt") {
        if (target->get_number_of_actions() < 4) { printf("The enemy has already drank the potion\n"); return; }

        target->remove_firebreath();        
        printf("The dragon can't breath fire anymore !\n");
        return;
    }

    if (act_state.get_name() == "danger") {
        thrower->damage(rand() % 100 * pow / 100); 
        printf("\033[0;31m %s hurts themselves from the action \033[0;0m\n", thrower->get_name().c_str());
        return;
    }

    if (act_state.get_name() == "defense") {
        if (act.get_range() == 'a') {
            for (auto &kv : team) {
                kv.second.set_def(heal);
                kv.second.set_state(State("defense", turn + act_state.get_duration()));
            }
            printf("\033[0;32m The party has high defense for %d turns ! \033[0;0m\n", act_state.get_duration());
            return;
        }
        
        target->set_state(State("defense", turn + act_state.get_duration()));
        target->set_def(heal);
        printf("\033[0;32m %s has %d defense for %d turns ! \033[0;0m\n", target->get_name().c_str(), heal, act_state.get_duration());
        return;
    }

    if (act_state.get_name() == "clone") {
        team["Clover"].set_state(State("clone", turn + act_state.get_duration()));
        printf("\033[0;32m Clover creates 2 clones that stand for 3 turns \033[0;0m\n");
        return;
    }

    if (act_state.get_name() == "revive") {
        bool done = false;

        do {
            std::string prompt;
            std::cout << "Who should you revive ?\n";
            std::getline(std::cin, prompt);
            if (!team.contains(prompt)) {continue;}
            if (team[prompt].get_hp() > 0) {std::cout << "This character isn't knocked out !\n"; continue;}
            if (team[prompt].get_state().get_name() == "dead") {std::cout << "Cannot revive a character whose SOUL shattered\n"; continue;}
            if (prompt == "Xhara" && enemies.size() == 3) {std::cout << "Cannot revive Xhara whose betrayed the team !\n"; continue;}
            if (prompt == "cancel") {done = true; continue;}

            team[prompt].revive(); done = true;
        } while (!done);
        return;
    }

    if (act_state.get_name() == "boost") {
        team["Clover"].boost(1.5);
        std::cout << "Clover has now " << team["Clover"].get_pow() << " power !\n";
        return;
    }

    if (act_state.get_name() == "focus") {
        thrower->set_state(State("focus", turn + 1)); // Assuming thrower is Xhara either in team or enemies
        return;
    }

    if (act_state.get_name() == "protect") {
        target->set_state(State(thrower->get_name(), 1 + turn));
        thrower->set_state(State("vulnerable", 1 + turn));
        thrower->set_def(-100);
    }

    if (act_state.get_name() == "smell") {
        do {
            std::string prompt;
            std::cout << "Time to focus ?\n\t >";
            std::getline(std::cin, prompt);
            try {
                int time = parse_int(prompt);
                thrower->set_state(State::smell_scale(time));
            }
            catch (const std::invalid_argument &e) {
                std::cout << "Error parsing integer\n";
                continue;
            }
        } while (true);
    }

    /* Need to implement "magic" actions */
}

Stats::Stats() {}

Stats::Stats(const Character &derek, const Character &flavie, const Character &haloise, const Character &xhara, const Character &clover, const Character &dragon) {
    team["Derek"] = derek;
    team["Flavie"] = flavie;
    team["Haloise"] = haloise;
    team["Xhara"] = xhara;
    team["Clover"] = clover;
    enemies["Dragon"] = dragon;
    default_enemy = "Dragon";
    turn = 1;
    orb = nullptr;
    nb_spirit = 0;
    took = nullptr;
}

Stats Stats::dragon_initializer() {
    return Stats (
        Character::initialize_derek_dragon(),
        Character::initialize_flavie_dragon(),
        Character::initialize_haloise_dragon(),
        Character::initialize_xhara_dragon(),
        Character::initialize_clover_dragon(),
        Character::initialize_dragon()
    );
}

void Stats::claim_soul(Character &owner) {
    if (owner.get_hp() <= 0 && owner.get_state().get_name() != "dead") {
        Character* virus = &enemies["Virus"];
        printf("The Virus took %s's SOUL and became stronger !\n", owner.get_name().c_str());
        owner.set_state(State("dead", -1));
        virus->damage(-100);
        virus->upgrade_action("drain", 1.3, 1.2); // upgrade " " action
        virus->upgrade_action("claw", 1.2, 1); // upgrade " " action
    }
}

void Stats::claim_souls() {
    for  (auto &kv: team) {
        claim_soul(kv.second);
    }
    if (!enemies.contains("Xhara")) {claim_soul(enemies["Xhara"]);}
}

