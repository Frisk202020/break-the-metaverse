package entity;

import java.util.Random;

import utilities.*;
import state.*;

public class PlayerDice extends Player {
    private int pow;
    private int def;
    private int[] diceRange;
    private Random diceSeed;

    public PlayerDice(String name, int maxHP, int pow, int[] diceRange){
        super(name, maxHP);
        this.pow = pow;
        this.def = 0;
        this.diceRange = diceRange;
        diceSeed = new Random();
    }

    @Override
    public void setCorrectState(int turn){
        if (turn == st.getEnd()){
            String n = st.getName();
            if (n.equals("defense")){
                def = 0;
            }
            // weaken and confuse can only be applied during spirit fight, hence only PlayerDice recognizes these
            else if (n.equals("weaken")){
                pow *= 5;
            }
            else if (n.equals("confuse")){
                pow /= 5;
            }
            st = new State();
        }
        if (hp == 0 && !st.getName().equals("K-O")){
            st = StateLibrary.KO.get(Integer.MAX_VALUE);
        }
    }

    @Override
    public String toString(){
        if (isAlive()){
            return name + " : " + Color.PURPLE.get() + "♥ " + hp + " " + lifeBar() + Color.CYAN.get() + " " + st.toString() + "\n";
        }
        return name + " : " + Color.PURPLE.get() + "♥ " + hp + " " + Color.CYAN.get() + " " + st.toString() + "\n";
    }

    private int dicePower(int diceValue){
        if (diceValue == diceRange[1]){
            return 3;
        }
        else if (diceValue == 1){
            return 0;
        }
        else if (diceValue > 1 && diceValue < diceRange[0]){
            return 1;
        }
        else if (diceValue >= diceRange[0] && diceValue < diceRange[1]){
            return 2;
        }
        else if (diceValue == 0){
            return -1;
        }

        System.out.println(ErrorMessage.INVALID_DICE.get());
        return 0;
    }

    public int attack(){
        System.out.println(ErrorMessage.WRONG_METHOD.get());
        return 0;
    }

    public int attack(String command){
        System.out.println(ErrorMessage.WRONG_METHOD.get());
        return 0;
    }

    public int attack(int diceValue){
        int range = dicePower(diceValue);
        switch(range){
            case 0:
                return Utility.entropy(pow, 0, 20, diceSeed);
            case 1:
                return Utility.entropy(pow, 20, 30, diceSeed);
            case 2:
                return Utility.entropy(pow, 50, 40, diceSeed);
            case 3:
                return pow;
            default:
                return 0;
        }
    }

}
