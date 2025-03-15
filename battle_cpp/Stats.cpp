#include "battle.h"
#include <string>
#include <iostream>

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

    if (turn == ch.get_state().get_duration()) {ch.state_back_to_normal();}
}

void Stats::update_stats() {
    for (auto &kv: team) {update_task(kv.second);}
    for (auto &kv: enemies) {update_task(kv.second);}
}

void Stats::enemy_attack(Character &enemy){
    if (enemies.contains("Dragon") || enemies.contains("Sensei")) {
        this->dragon_or_sensei_attack();
        return;
    }
    if (enemies.contains("Virus")) {
        this->final_attack(enemy);
        return;
    }
    this->spirit_attack(enemy);
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

    Character* target = pick_random_target();
    bool did_attack = true;
    if (act.is_superguardable()) {
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

void Stats::execute_action(const Action &act, Character &thrower, Character &target){
    if (act.get_type() == 'r') {
        std::string prompt;
        std::cout << "Look at the battle book do check action's success condition. Should the action be executed ?\n";
        std::getline(std::cin, prompt);
        if (prompt[0] != 'y') {std::cout << "Action failed !\n"; return;}
    }

    int odd = act.get_odd();
    if (odd < 100) {
        if (!happening(odd)) {std::cout << "Action failed...\n"; return;}
    }

    int pow = act.get_pow();
    int heal = act.get_heal();
    State act_state = act.get_state();

    if (act_state.get_name() == "normal") {
        target.damage(pow);
        return;
    }

    if (act_state.get_name() == "stun"){
        target.set_state(State ("stun", turn + act_state.get_duration()));
        printf("\033[0;32m The enemy can't attack for the following turn \033[0;0m\n");
        return;
    } 
    
    if (act_state.get_name() == "provoke") {
        target.set_state(State ("Derek", turn + act_state.get_duration()));
        printf("\033[0;32m The enemy will focus Derek for 2 turns \033[0;0m\n");
        return;
    } 
    
    if (act_state.get_name() == "corrupt") {
        if (target.get_number_of_actions() < 4) { printf("The enemy has already drank the potion\n"); return; }

        target.remove_firebreath();        
        printf("The dragon can't breath fire anymore !\n");
        return;
    }

    if (act_state.get_name() == "danger") {
        thrower.damage(rand() % 100 * pow / 100); 
        printf("\033[0;31m %s hurts themselves from the action \033[0;0m\n", thrower.get_name().c_str());
        return;
    }

    if (act_state.get_name() == "defense") {
        if (act.get_range() == 'a') {
            for (auto &kv : team) {
                kv.second.set_def(heal);
            }
            printf("\033[0;32m The party has high defense for %d turns ! \033[0;0m\n", act_state.get_duration());
        }
        
        target.set_state(State("defense", turn + act_state.get_duration()));
        target.set_def(heal);
        printf("\033[0;32m %s has %d defense for %d turns ! \033[0;0m\n", target.get_name().c_str(), heal, act_state.get_duration());
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
        thrower.set_state(State("focus", -1)); // Assuming thrower is Xhara either in team or enemies
        return;
    }

    if (act_state.get_name() == "smell") {
        do {
            std::string prompt;
            std::cout << "Time to focus ?\n\t >";
            std::getline(std::cin, prompt);
            try {
                int time = parse_int(prompt);
                thrower.set_state(State::smell_scale(time));
            }
            catch (const std::invalid_argument &e) {
                std::cout << "Error parsing integer\n";
                continue;
            }
        } while (true);
    }

    /* Need to implement "magic" actions */
}

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
        virus->upgrade_action(0, 1.3, 1.2); // upgrade " " action
        virus->upgrade_action(3, 1.2, 1); // upgrade " " action
    }
}

void Stats::claim_souls() {
    for  (auto &kv: team) {
        claim_soul(kv.second);
    }
    if (!enemies.contains("Xhara")) {claim_soul(enemies["Xhara"]);}
}

