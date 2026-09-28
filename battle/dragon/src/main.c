#define _POSIX_C_SOURCE 200809L

#include <signal.h>

#include "dragon/include/game_manager.h"
#include "dragon/include/server.h"
#include "util/include/print.h"

GameManager* gm;

int main() {
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    pthread_sigmask(SIG_BLOCK, &sigset, NULL);

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

    Action dragon[] = {
        action_init("", ""),
        action_init("", ""),
        action_init("", ""),
        action_init("", "")
    };

    GameManager instance = {
        .party = {
            (Character) { character_base_init("", 80), 5, derek}, 
            (Character) { character_base_init("Flavie", 80), 5, flavie }, 
            (Character) { character_base_init("Haloise", 80), 5, haloise }, 
            (Character) { character_base_init("Clover", 80), 5, clover }, 
            (Character) { character_base_init("Xhara", 80), 5, xhara }
        }, 
        .dragon = (Character) { character_base_init("Dragon", 1000), 0, dragon },
        .reset_state = {[0 ... 4] -1},
    };
    pthread_mutex_init(&instance.mutex, NULL);
    pthread_mutex_lock(&instance.mutex);
    gm = &instance;

    pthread_t server;
    const char* err = start_server(&server);
    if (err != NULL) {
        println(LOG_ERR, err);
        return 0;
    }

    int sig;
    sigwait(&sigset, &sig);
    close_server();

    pthread_join(server, NULL);
    return 0;
}