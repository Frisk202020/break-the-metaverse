package entity;

import utilities.*;

public class PlayerDice extends Entity {
    private int pow;
    private int def;
    private int dice;

    public PlayerDice(String name, int maxHP, int pow, int dice){
        super(name, maxHP);
        this.pow = pow;
        this.def = 0;
        this.dice = dice;
    }

    @Override
    public String toString(){
        return name + " : " + Color.PURPLE.get() + "♥ " + hp + " " + lifeBar() + Color.CYAN.get() + " " + st.toString() + "\n";
    }

    public int attack(){
        return 0;
    }
}
