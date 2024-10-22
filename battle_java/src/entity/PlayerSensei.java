package entity;

import state.*;
import utilities.*;

public class PlayerSensei extends Entity{
    private int pow;
    private int def;
    private int grade;
    private String belt;
    private State smell;

    public PlayerSensei(String name, int maxHP, int pow, int grade, String belt){
        super(name, maxHP);
        this.pow = pow;
        this.def = 0;
        this.grade = grade;
        this.belt = belt;
        smell = StateLibrary.NONE.get();
    }

    @Override
    public String toString(){
        String result = belt + name + " : ";
        float actualGrade = grade + (20 - grade) * (float)hp/maxHP;
        result += Color.PURPLE.get() + "Grade : " + actualGrade + "/20 " + lifeBar() + belt + " " + st.toString() + " " + smell.toString() + "\n"; 

        return result;
    }

    public int attack(){
        return 0;
    }

    private void smellScale(){
        return;
    }
}
