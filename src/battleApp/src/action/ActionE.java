package action;

import java.util.HashMap;
import java.util.Random;

import state.*;

public class ActionE extends Action {
    private int odd;
    private boolean superguard;

    public ActionE(String name, int pow, int heal, int aim, int odd){
        super(name, pow, heal, aim);
        this.odd = odd;
        this.superguard = false;
    }
    public ActionE(String name, int pow, int heal, int aim, int odd, boolean superguard){
        super(name, pow, heal, aim);
        this.odd = odd;
        this.superguard = superguard;
    }

    public ActionE(String name, int pow, int heal, int aim, int odd, State st){
        super(name, pow, heal, aim, st);
        this.odd = odd;
        this.superguard = false;
    }

    public ActionE(String name, int pow, int heal, int aim, int odd, boolean superguard, State st){
        super(name, pow, heal, aim, st);
        this.odd = odd;
        this.superguard = superguard;
    }

    public int getPow(){
        return pow;
    }

    public int getHeal(){
        return heal;
    }

    public int getAim(){
        return aim;
    }

    public int getOdd(){
        return odd;
    }

    public static ActionE pickRandomAction(Random seed, HashMap<String, ActionE> actions){
        int pick = seed.nextInt(actions.size());

        int i = 0;
        for (ActionE p : actions.values()){
            if (i == pick){
                return p;
            }   
            i++;
        }
        return null;
    }
}
