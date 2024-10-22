package entity;

import utilities.*;

public class Enemy extends Entity {
    public Enemy(String name, int maxHP){
        super(name, maxHP);
    }

    @Override
    public String toString(){
        if (name.equals("Dragon")){
            return Color.RED.get() + " " + name + " : " + Color.PURPLE.get() +" ♥ " + hp + " " + lifeBar() + Color.RED.get() + " " + st.toString() + "\n";
        }
        return "";
    }

    public int attack(){
        return 0;
    }
}
