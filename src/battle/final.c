#include <stdlib.h>
#include "battle.h"

stats final_initialize(){
    character Derek = { 
        .name = "Derek",
        .name_length = 5,
        .maxHP = 250,
        .HP = 250,
        .POW = 10,
        .DEF = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .dice = 6,
        .actions = malloc(4*sizeof(action)),
        .NOA = 2,
    };
    action taser = {
        .name = "taser",
        .name_length = 5,
        .POW = 10,
        .heal = 0,
        .st = {
            .name = "stun",
            .end = 1,
        },
        .aim = 'e',
        .type = 'g',
        .superguard = false,
        .odd = 100,
        // effect : stuns the enemy for the current turn
    };
    action protect = {
        .name = "protect",
        .name_length = 7,
        .POW = 0,
        .heal = 0,
        .st = {
            .name = "vulnerable",
            .end = 1,
        },
        .aim = 'i',
        .type = 'l',
        .superguard = false,
        .odd = 100,
        // effect : protect a foe, but receive double damage
    };
    action sword = {
        .name = "sword",
        .name_length = 5,
        .POW = 100,
        .heal = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'e',
        .type = 'g',
        .superguard = false,
        .odd = 100,
        // effect : massive garanted damage output
    };
    action provoke = {
        .name = "provoke",
        .name_length = 7,
        .POW = 0,
        .heal = 0,
        .st = {
            .name = "provoke",
            .end = 2,
        },
        .aim = 'e',
        .type = 'l',
        .superguard = false,
        .odd = 80,
        // effect : the enemy will focus Derek for 2 turns
    }; 
    Derek.actions[0] = taser;
    Derek.actions[1] = protect;
    Derek.actions[2] = sword;
    Derek.actions[3] = provoke;

    character Flavie = {
        .name = "Flavie",
        .name_length = 6,
        .maxHP = 120,
        .HP = 120,
        .POW = 3,
        .DEF = 0,
        .dice = 30,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .actions = malloc(4*sizeof(action)),
        .NOA = 2,
    };
    action hack = { 
        .name = "hack",
        .name_length = 4,
        .POW = 500,
        .heal = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'e',
        .type = 'r',
        .superguard = false,
        .odd = 100,
        // effect : hack the code of the battle to do insane dammage. 
    };
    action shield = { 
        .name = "shield",
        .name_length = 6,
        .POW = 0,
        .heal = 100,
        .st = {
            .name = "defense",
            .end = 1,
        },
        .aim = 'a',
        .type = 'g',
        .superguard = false,
        .odd = 100,
        // effect : the action protects the crew from one attack
    };
    action potion = { 
        .name = "potion",
        .name_length = 6,
        .POW = 0,
        .heal = 0,
        .st = {
            .name = "revive",
            .end = -1,
        },
        .aim = 'i',
        .type = 'g',
        .superguard = false,
        .odd = 100,
    };
    Flavie.actions[0] = hack;
    Flavie.actions[1] = protect;
    Flavie.actions[2] = shield;
    Flavie.actions[3] = potion;

    character Haloise = { 
        .name = "Haloise",
        .name_length = 7,
        .maxHP = 350,
        .HP = 350,
        .POW = 1,
        .DEF = 0,
        .dice = 20,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .actions = malloc(4*sizeof(action)),
        .NOA = 2,
    };
    action encyclopedia = { 
        .name = "encyclopedia",
        .name_length = 12,
        .POW = 0,
        .heal = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'e',
        .type = 'r',
        .superguard = false,
        .odd = 100,
        // effect : retrieve information of the enemy 
    };
    action stone = { 
        .name = "stone",
        .name_length = 5,
        .POW = 0,
        .heal = 50,
        .st = {
            .name = "defense",
            .end = 3,
        },
        .aim = 'i',
        .type = 'g',
        .superguard = false,
        .odd = 100,
        // effect : high defense
    };
    action hammer = { 
        .name = "hammer",
        .name_length = 6,
        .POW = 300,
        .heal = 0,
        .st = {
            .name = "danger",
            .end = 1,
        },
        .aim = 'i',
        .type = 'g',
        .superguard = false,
        .odd = 100,
        // effect : high damage output, but the character may receive damage
    };
    Haloise.actions[0] = encyclopedia;
    Haloise.actions[1] = protect;
    Haloise.actions[2] = stone;
    Haloise.actions[3] = hammer;

    character Xhara = { 
        .name = "Xhara",
        .name_length = 5,
        .maxHP = 150,
        .HP = 150,
        .POW = 2,
        .DEF = 0,
        .dice = 10,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .actions = malloc(3*sizeof(action)),
        .NOA = 1,
    };
    action retreat = { 
        .name = "retreat",
        .name_length = 7,
        .POW = 0,
        .heal = 100,
        .st = {
            .name = "defense",
            .end = 3,
        },
        .aim = 'i',
        .type = 'g',
        .superguard = false,
        .odd = 100,
        // effect : backs from the arena : the character is protected but can only attack
    };
    action focus = { 
        .name = "focus",
        .name_length = 5,
        .POW = 0,
        .heal = 0,
        .st = {
            .name = "focus",
            .end = 1,
        },
        .aim = 'i',
        .type = 'l',
        .superguard = false,
        .odd = 100,
        // effect : if the character is not atttacked on the following turn, he'll do triple damage for 1 turn
    };
    Xhara.actions[2] = focus;
    Xhara.actions[1] = retreat;
    Xhara.actions[0] = protect;

    character Clover = {
        .name = "Clover",
        .name_length = 6,
        .maxHP = 80,
        .HP = 80,
        .POW = 6,
        .DEF = 0,
        .dice = 4,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .actions = malloc(4*sizeof(action)),
        .NOA = 2,
    };
    action fake = { 
        .name = "fake",
        .name_length = 4,
        .POW = 0,
        .heal = 0,
        .st = {
            .name = "clone",
            .end = 3,
        },
        .aim = 'i',
        .type = 'g',
        .superguard = false,
        .odd = 100,
        // effect : massive damage. Challenge -> throw shuttlecock in mug (or throw arrow if I have one)
    };
    action knife = { 
        .name = "knife",
        .name_length = 5,
        .POW = 300,
        .heal = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'e',
        .type = 'r',
        .superguard = false,
        .odd = 100,
    };
    action gold = { 
        .name = "gold",
        .name_length = 4,
        .POW = 40,
        .heal = 0,
        .st = {
            .name = "boost",
            .end = -1,
        },
        .aim = 'i',
        .type = 'l',
        .superguard = false,
        .odd = 60,
    };
    Clover.actions[0] = fake;
    Clover.actions[1] = protect;
    Clover.actions[2] = knife;
    Clover.actions[3] = gold;

    character* team = (character*)malloc(5*sizeof(character));
    team[0] = Derek;
    team[1] = Flavie;
    team[2] = Haloise;
    team[3] = Xhara;
    team[4] = Clover;

    character Virus = {
        .name = "Virus",
        .name_length = 5,
        .maxHP = 1500,
        .HP = 1500,
        .POW = 0,
        .DEF = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .actions = malloc(4*sizeof(action)),
        .NOA = 4,
    };

    action drain = {
        .name = "drain",
        .name_length = 5,
        .POW = 30,
        .heal = 50,
        .st = {
            .name = "weaken",
            .end = 3,
        },
        .aim = 'i',
        .superguard = false,
        .odd = 20,
    };
    action confuse = { //pierce defense
        .name = "confuse",
        .name_length = 7,
        .POW = 0,
        .heal = 0,
        .st = {
            .name = "confuse",
            .end = 2,
        },
        .aim = 'i',
        .superguard = false,
        .odd = 15,
    };
    action revolution = { //pierce defense
        .name = "revolution",
        .name_length = 10,
        .POW = -1, //means the power depends of the teamates HP
        .heal = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'a',
        .superguard = false,
        .odd = 15,
    };
    action claw = {
        .name = "claw",
        .name_length = 4,
        .POW = 50,
        .heal = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'i',
        .superguard = true,
        .odd = 50,
    };
    action SOUL = {
        .name = "SOUL",
        .name_length = 4,
        .POW = 0,
        .heal = 100,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'i',
        .superguard = false,
        .odd = 0,
    };
    Virus.actions[0] = drain;
    Virus.actions[1] = confuse;
    Virus.actions[2] = revolution;
    Virus.actions[3] = claw;

    character H0PE = {
        .name = "H0PE",
        .name_length = 4,
        .maxHP = 300,
        .HP = 300,
        .POW = 0,
        .DEF = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .actions = malloc(4*sizeof(action)),
        .NOA = 4,
    };
    action heal = {
        .name = "heal",
        .name_length = 4,
        .POW = 0,
        .heal = 150,
        .st = {
            .name = "Virus",
            .end = -1,
        },
        .aim = 'i',
        .superguard = false,
        .odd = 25,
    };
    action enrage = {
        .name = "enrage",
        .name_length = 6,
        .POW = 0,
        .heal = 0,
        .st = {
            .name = "rage",
            .end = 3,
        },
        .aim = 'i',
        .superguard = false,
        .odd = 25,
    };
    action target = {
        .name = "target",
        .name_length = 5,
        .POW = 0,
        .heal = 0,
        .st = {
            .name = "target",
            .end = 2,
        },
        .aim = 'i',
        .superguard = false,
        .odd = 25,
    };
    action reflect = {
        .name = "reflect",
        .name_length = 7,
        .POW = 0,
        .heal = 0,
        .st = {
            .name = "reflect",
            .end = 5,
        },
        .aim = 'i',
        .superguard = false,
        .odd = 25,
    };
    H0PE.actions[0] = heal;
    H0PE.actions[1] = enrage;
    H0PE.actions[2] = target;
    H0PE.actions[3] = reflect;

    stats s = {
        .team = team,
        .enemy = Virus,
        .turn = 1,
        .orb = NULL,
        .other = malloc(2*sizeof(character)),
        .nb_other = 1,
    };

    s.other[0] = H0PE;
    return s; 
}