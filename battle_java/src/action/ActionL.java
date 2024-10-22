package action;

import state.StateLibrary;

public class ActionL extends Action {
    private int odd;

    public ActionL(String name, int pow, int heal, char aim, int odd){
        super(name, pow, heal, aim);
        this.odd = odd;
    }
    public ActionL(String name, int pow, int heal, char aim, int odd, StateLibrary st){
        super(name, pow, heal, aim, st);
        this.odd = odd;
    }
}
