package entity;

import java.util.ArrayList;
import java.util.Random;

import action.ActionLibrary;
import state.*;
import utilities.Color;

public class Spirit extends Enemy{
    private State weakness;

    private static ArrayList<Spirit> spirits = SpiritLibrary.generateList();

    Spirit(String name, StateLibrary wk){
        super(name, 50);
        weakness = wk.get(Integer.MAX_VALUE);
        this.addActions(ActionLibrary.INDIV, ActionLibrary.MULTI);
    }

    public String getName(){
        return name;
    }

    public static Spirit chooseSpirit(Random seed){
        int r = seed.nextInt(spirits.size());
        Spirit s = spirits.get(r);
        spirits.remove(r);
        return s;
    }   

    @Override
    public String toString(){
        return name + " : " + Color.PURPLE.get() +" ♥ " + hp + " " + lifeBar() + Color.RED.get() + " " + st.toString() + "\n";
    }
}
