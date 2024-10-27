package state;

public enum StateLibrary{
    NORMAL (new State()),
    STUN (new State("stun", 1)),
    PROVOKE (new State("provoke", 2)),
    DEFENSE1 (new State("defense", 1)),
    DEFENSE3 (new State("defense", 3)),
    CORRUPT (new State("corrupt", Integer.MAX_VALUE)),
    DANGER (new State("danger", 1)),
    FOCUS (new State("focus", 1)),
    CLONE (new State("clone", 3)),
    BOOST (new State("boost", -1)),
    PROTECT (new State("protect", 1)),
    SMELL (new State("smell", 1)),
    NONE (new State("none", -1)),

    FIRE (new State("fire", 1)),
    ICE (new State("ice", 1)),
    WATER (new State("water", 1)),
    LIGHT (new State("light", 1)),
    VEGETAL (new State("vegetal", 1)),
    FUME (new State("fume", 1)),
    BURST (new State("burst", 1)),
    POISON (new State("poison", 1)),
    SCULPTURE (new State("sculpture", 1)),
    BEAM (new State("beam", 1)),
    DARKNESS (new State("darkness", 1)),
    PLANT (new State("plant", 1)),
    HEAL (new State("heal", 1)),
    LILA (new State("lila", 1)),

    GLUTTON (new State("glutton", 1)),
    DARK (new State("dark", 1)),
    HUMAN (new State("human", 1)),
    STONE (new State("stone", 1)),
    SHADOW (new State("shadow", 1)),
    CLIMATE (new State("climate", 1)),
    SENSEI (new State("sensei", 1)),

    WEAKEN (new State("weaken", 3)),
    CONFUSE (new State("confuse", 2)),
    VIRUS (new State("Virus", -1)),
    RAGE (new State("rage", 3)),
    TARGET (new State("target", 2)),
    REFLECT (new State("reflect", 5));
    

    private State st;

    StateLibrary(State st){
        this.st = st;
    }

    public State copy(){
        return get().copy();
    }

    public State get(){
        return st;
    }

    

    
}
