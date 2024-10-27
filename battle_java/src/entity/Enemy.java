package entity;

import utilities.*;

public class Enemy extends Entity {
    public Enemy(String name, int maxHP){
        super(name, maxHP);
    }

    @Override
    public String toString(){
        return name + " : " + Color.PURPLE.get() +" ♥ " + hp + " " + lifeBar() + Color.RED.get() + " " + st.toString() + "\n";
    }

    public int attack(){
        return 0;
    }
}
