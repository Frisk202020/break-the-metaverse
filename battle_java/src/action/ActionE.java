package action;

import state.StateLibrary;

public class ActionE extends Action {
    private int odd;
    private boolean superguard;

    public ActionE(String name, int pow, int heal, char aim, int odd){
        super(name, pow, heal, aim);
        this.odd = odd;
        this.superguard = false;
    }
    public ActionE(String name, int pow, int heal, char aim, int odd, boolean superguard){
        super(name, pow, heal, aim);
        this.odd = odd;
        this.superguard = superguard;
    }

    public ActionE(String name, int pow, int heal, char aim, int odd, StateLibrary st){
        super(name, pow, heal, aim, st);
        this.odd = odd;
        this.superguard = false;
    }

    public ActionE(String name, int pow, int heal, char aim, int odd, boolean superguard, StateLibrary st){
        super(name, pow, heal, aim, st);
        this.odd = odd;
        this.superguard = superguard;
    }
}
