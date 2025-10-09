package state;

public enum StateLibrary{
    NONE ("none"),
    KO ("K-O"),

    STUN ("stun"),
    PROVOKE ("provoke"),
    DEFENSE ("defense"),
    CORRUPT ("corrupt"),
    DANGER ("danger"),
    FOCUS ("focus"),
    CLONE ("clone"),
    BOOST ("boost"),
    PROTECT ("protect"),
    SMELL ("smell"),

    FIRE ("fire"),
    ICE ("ice"),
    WATER ("water"),
    LIGHT ("light"),
    VEGETAL ("vegetal"),
    FUME ("fume"),
    BURST ("burst"),
    POISON ("poison"),
    SCULPTURE ("sculpture"),
    BEAM ("beam"),
    DARKNESS ("darkness"),
    PLANT ("plant"),
    HEAL ("heal"),
    LILA ("lila"),

    GLUTTON ("glutton"),
    DARK ("dark"),
    HUMAN ("human"),
    STONE ("stone"),
    SHADOW ("shadow"),
    CLIMATE ("climate"),
    SENSEI ("sensei"),

    WEAKEN ("weaken"),
    CONFUSE ("confuse"),
    VIRUS ("Virus"),
    RAGE ("rage"),
    TARGET ("target"),
    REFLECT ("reflect");
    

    private String name;

    StateLibrary(String name){
        this.name = name;
    }

    public State get(){
        return new State(name, -1);
    }  

    public State get(int end){
        return new State(name, end);
    }    
}
