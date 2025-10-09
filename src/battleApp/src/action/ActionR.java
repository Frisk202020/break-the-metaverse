package action;

import state.State;

public class ActionR extends Action {
    public ActionR(String name, int pow, int heal, int aim){
        super(name, pow, heal, aim);
    }
    public ActionR(String name, int pow, int heal, int aim, State st){
        super(name, pow, heal, aim, st);
    }
}
