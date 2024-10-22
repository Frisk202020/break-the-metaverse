package action;

import state.StateLibrary;

public class ActionG extends Action {
    public ActionG(String name, int pow, int heal, char aim){
        super(name, pow, heal, aim);
    }
    public ActionG(String name, int pow, int heal, char aim, StateLibrary st){
        super(name, pow, heal, aim, st);
    }
}
