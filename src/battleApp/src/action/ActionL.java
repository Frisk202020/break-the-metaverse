package action;

import state.*;

public class ActionL extends Action {
    private int odd;

    public ActionL(String name, int pow, int heal, int aim, int odd){
        super(name, pow, heal, aim);
        this.odd = odd;
    }
    public ActionL(String name, int pow, int heal, int aim, int odd, State st){
        super(name, pow, heal, aim, st);
        this.odd = odd;
    }
}
