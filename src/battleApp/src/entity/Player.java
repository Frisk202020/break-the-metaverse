package entity;

import action.*;
import utilities.Color;

import java.util.Random;
import java.util.HashMap;

public abstract class Player extends Entity {
    protected HashMap<String, Action> actions;

    protected Player(String name, int maxHP){
        super(name, maxHP);
        actions = new HashMap<>();
    }

    abstract public int attack();
    abstract public int attack(int diceValue);
    abstract public int attack(String command);

    public void addActions(Action... acts){
        for (Action act : acts) {
            actions.put(act.getName(), act);
        }
    }

    public void addActions(ActionLibrary... acts){
        for (ActionLibrary act : acts) {
            Action a = act.get();
            actions.put(a.getName(), a);
        }
    }

    public void setActPow(String actName, int pow2){
        if (actions.containsKey(actName)){
            actions.get(actName).setPow(pow2);
        }
        else{
            System.out.println(actName + " : " + Color.RED.get() + "Unknown action ! ||ABORTED||" + Color.DEFAULT.get());
        }
    }

    @Override
    abstract public String toString();


    public static Player pickRandomPlayer(Random seed, HashMap<String, Player> team){
        int pick = seed.nextInt(team.size());

        int i = 0;
        for (Player p : team.values()){
            if (i == pick){
                return p;
            }   
            i++;
        }
        return null;
    }
}
