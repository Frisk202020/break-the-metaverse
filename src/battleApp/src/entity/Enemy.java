package entity;

import utilities.*;

import java.util.HashMap;
import java.util.Random;

import action.*;

public class Enemy extends Entity {
    private HashMap<String, ActionE> actions;

    public Enemy(String name, int maxHP){
        super(name, maxHP);
        actions = new HashMap<>();
    }

    public void addActions(ActionE... acts){
        for (ActionE act : acts) {
            actions.put(act.getName(), act);
        }
    }

    public void addActions(ActionLibrary... acts){
        for (ActionLibrary act : acts) {
            Action a = act.get();
            ActionE aE = (ActionE) a;
            actions.put(aE.getName(), aE);
        }
    }

    public HashMap<String, ActionE> getActions(){
        return actions;
    }

    public int sumOdds(){
        int result = 0;
        for (Action a : actions.values()) {
            ActionE aE = (ActionE) a;
            result += aE.getOdd();
        }
        return result;
    }

    @Override
    public String toString(){
        if (isAlive()){
            return name + " : " + Color.PURPLE.get() +" ♥ " + hp + " " + lifeBar() + Color.RED.get() + " " + st.toString() + "\n";
        }
        return name + " : " + Color.PURPLE.get() +" ♥ " + hp + " " + Color.RED.get() + " " + st.toString() + "\n";
    }

    public ActionE chooseAction(Random seed){
        int n = seed.nextInt()%actions.size();
        int i = 0;
        for (ActionE a : actions.values()){
            if (i == n){
                return a;
            }
            else{
                i++;
            }
        }
        return null;
    }
}
