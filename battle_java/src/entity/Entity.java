package entity;

import action.*;
import state.*;
import utilities.*;
import java.util.HashMap;

abstract public class Entity {
    protected String name;
    protected int maxHP;
    protected int hp;
    protected State st;
    protected HashMap<String, Action> actions;

    protected Entity(String name, int maxHP){
        this.name = name;
        this. maxHP = maxHP;
        this.hp = maxHP;
        st = new State();
        actions = new HashMap<>();
    }

    @Override
    abstract public String toString();
    abstract public int attack();

    public String getName(){
        return name;
    }

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

    protected String lifeBar(){
        String result = "\033[0;32m";
        int N = 20*hp / maxHP;

        for (int i = 0; i < N; i++){
            result += "|";
        }
        result += "\033[0;31m";
        for (int i = N; i < 20; i++){
            result += "|";
        }

        return result;
    }
}
