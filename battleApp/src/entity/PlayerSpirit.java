package entity;

import state.*;
import utilities.*;

public class PlayerSpirit extends Player{
    private State magic;
    private final static TupleHash<String, State> TABLE = TupleHash.initializeMagic();
    
    private static String[] orb = {"none", "none"};

    public PlayerSpirit(String name , String magic){
        super(name, 100);
        this.magic = giveMagic(magic);
    }

    private State giveMagic(String magic){
        if (magic.equals("fire")){
            return StateLibrary.FIRE.get(Integer.MAX_VALUE);
        }
        else if (magic.equals("ice")){
            return StateLibrary.ICE.get(Integer.MAX_VALUE);
        }
        else if (magic.equals("water")){
            return StateLibrary.WATER.get(Integer.MAX_VALUE);
        }
        else if (magic.equals("light")){
            return StateLibrary.LIGHT.get(Integer.MAX_VALUE);
        }
        else if (magic.equals("vegetal")){
            return StateLibrary.VEGETAL.get(Integer.MAX_VALUE);
        }
        else{
            System.out.println(Color.YELLOW.get() + "WARNING : unrecognized magic" + Color.DEFAULT.get());
        }
        return null;
    }

    @Override
    public String toString(){
        return name + " : " + Color.PURPLE.get() + "♥ " + hp + " " + lifeBar() + Color.CYAN.get() + " " + st.toString() + Color.YELLOW.get() + " " + magic.toString() + Color.CYAN.get() + "\n";
    }

    public int attack(){
        return 0;
    }
    
    public int attack(int value){
        return 0;
    }

    public int attack(String command){
        System.out.println(ErrorMessage.WRONG_METHOD.get());
        return 0;
    }

    public static String[] getOrb(){
        return orb;
    }

    public static void editOrb(int i, String magic){
        if (i < 0 || i > 2){
            System.out.println(Color.RED.get() + "Invalid Orb ID !!\n" + Color.DEFAULT.get());
            return;
        }
        orb[i] = magic;
    }
}
