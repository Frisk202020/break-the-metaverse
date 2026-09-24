#include "game_manager.h"
#include "server.h"

GameManager* gm;
pthread_cond_t shutdown_signal;

int main() {
    Action derek[] = {
        action_init_derek_shared(), 
        action_init("", ""),
        action_init("", "")
    };

    Action flavie[] = {
        action_init_flavie_shared(),
        action_init("", ""),
        action_init("", "")
    };

    Action haloise[] = {
        action_init_haloise_shared(),
        action_init("", ""),
        action_init("", "")
    };

    Action clover[] = {
        action_init_clover_shared(),
        action_init("", ""),
        action_init("", "")
    };

    Action xhara[] = {
        action_init_xhara_shared(),
        action_init("", ""),
        action_init("", "")
    };

    Character party[] = {
        character_init("Derek", 80, 5, derek),
        character_init("Flavie", 80, 5, flavie),
        character_init("Haloise", 80, 5, haloise),
        character_init("CLover", 80, 5, clover),
        character_init("Xhara", 80, 5, xhara)
    };
;
    int reset_state[] = {[0 ... 4] -1};
    GameManager instance = {
        .party = party,
        .dragon = dragon_init(),
        .reset_state = reset_state,
    };
    pthread_mutex_init(&gm->mutex, NULL);
    pthread_mutex_lock(&gm->mutex);
    gm = &instance;

    start_server();

    pthread_cond_init(&shutdown_signal, NULL);
    pthread_cond_wait(&shutdown_signal, &gm->mutex);

    return 0;
}