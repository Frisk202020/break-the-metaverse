typedef struct action {
    const char* name;
    const char* description;
} Action;

Action action_init_derek_shared();
Action action_init_flavie_shared();
Action action_init_haloise_shared();
Action action_init_clover_shared();
Action action_init_xhara_shared();

Action action_init(const char* name, const char* description);