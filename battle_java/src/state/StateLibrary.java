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
    NONE (new State("none", -1));

    private State st;

    StateLibrary(State st){
        this.st = st;
    }

    public State get(){
        return st;
    }

    

    
}
