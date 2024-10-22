package action;

import state.StateLibrary;

public class ActionR extends Action {
    public ActionR(String name, int pow, int heal, char aim){
        super(name, pow, heal, aim);
    }
    public ActionR(String name, int pow, int heal, char aim, StateLibrary st){
        super(name, pow, heal, aim, st);
    }
}
