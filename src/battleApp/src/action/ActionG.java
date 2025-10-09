package action;

import state.*;

public class ActionG extends Action {
    public ActionG(String name, int pow, int heal, int aim){
        super(name, pow, heal, aim);
    }
    public ActionG(String name, int pow, int heal, int aim, State st){
        super(name, pow, heal, aim, st);
    }
}
