package action;

import state.*;

public class Action {
    protected String name;
    protected int pow;
    protected int heal;
    protected State st;
    protected char aim;

    public Action(String name, int pow, int heal, char aim) {
        this.name = name;
        this.pow = pow;
        this.heal = heal;
        this.st = new State();
        this.aim = aim;
    }

    public Action(String name, int pow, int heal, char aim, StateLibrary st) {
        this.name = name;
        this.pow = pow;
        this.heal = heal;
        this.st = st.get();
        this.aim = aim;
    }

    public String getName(){
        return name;
    }

    public void setPow(int pow2){
        pow = pow2;
    }

}
