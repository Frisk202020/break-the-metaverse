package entity;

import state.*;

abstract public class Entity {
    protected String name;
    protected int maxHP;
    protected int hp;   
    protected State st;

    protected Entity(String name, int maxHP){
        this.name = name;
        this. maxHP = maxHP;
        this.hp = maxHP;
        st = new State();
    }

    @Override
    abstract public String toString();

    public String getName(){
        return name;
    }

    public void damage(int damage){
        hp -= damage;
    }

    public void setCorrectHpValue(){
        if (hp > maxHP){
            hp = maxHP;
        }
        if (hp < 0){
            hp = 0;
        }
    }

    public void setCorrectState(int turn){
        // WARNING : method overwrote in PlayerDice
        if (turn == st.getEnd()){
            st = new State();
        }
        if (hp == 0 && !st.getName().equals("K-O")){
            st = StateLibrary.KO.get(Integer.MAX_VALUE);
        }
    }

    public boolean isAlive(){
        return !(hp <= 0);
    }

    public String lifeBar(){
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

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((name == null) ? 0 : name.hashCode());
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        Entity other = (Entity) obj;
        if (name == null) {
            if (other.name != null)
                return false;
        } else if (!name.equals(other.name))
            return false;
        return true;
    }
}
