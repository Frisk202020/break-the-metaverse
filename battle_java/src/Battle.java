import java.util.HashMap;
import java.util.Random;

import action.ActionLibrary;
import entity.*;
import utilities.*;

public class Battle {
    private String name;
    private int turn;
    private HashMap<String, Entity> team;
    private HashMap<String, Enemy> enemies;
    private Random seed;

    public Battle(String name){
        this.name = name;
        turn = 1;
        team = new HashMap<>();
        enemies = new HashMap<>();
        seed = new Random();

        if (name.equals("Dragon")){
            PlayerDice Derek = new PlayerDice("Derek", 250, 50, 6);
            Derek.addActions(ActionLibrary.TASER, ActionLibrary.SWORD, ActionLibrary.PROVOKE);
            
            PlayerDice Flavie = new PlayerDice("Flavie", 120, 20, 30);
            Flavie.addActions(ActionLibrary.HACK, ActionLibrary.SHIELD, ActionLibrary.POTION);

            PlayerDice Haloise = new PlayerDice("Haloise", 350, 10, 10);
            Haloise.addActions(ActionLibrary.ENCYCLOPEDIA, ActionLibrary.HAMMER, ActionLibrary.STONE);

            PlayerDice Clover = new PlayerDice("Clover", 80, 60, 4);
            Clover.addActions(ActionLibrary.CLONE, ActionLibrary.KNIFE, ActionLibrary.GOLD);

            PlayerDice Xhara = new PlayerDice("Xhara", 150, 30, 20);
            Xhara.addActions(ActionLibrary.BETRAYAL, ActionLibrary.RETREAT, ActionLibrary.FOCUS);

            Enemy Dragon = new Enemy("Dragon", 1000);
            Dragon.addActions(ActionLibrary.FIREBREATH, ActionLibrary.STOMP, ActionLibrary.BITE, ActionLibrary.CLAW);

            addEntity(Derek, Flavie, Haloise, Clover, Xhara, Dragon);
        }
        else if (name.equals("Sensei")){
            PlayerSensei Derek = new PlayerSensei("Derek", 20, 1, 18, Color.WHITE.get());
            Derek.addActions(ActionLibrary.TASER, ActionLibrary.PROTECT, ActionLibrary.SMELL);
            Derek.setActPow("taser", 1);

            PlayerSensei Flavie = new PlayerSensei("flavie", 120, 1, 8, Color.GREEN.get());
            Flavie.addActions(ActionLibrary.HACK, ActionLibrary.PROTECT, ActionLibrary.SMELL);
            Flavie.setActPow("hack", 10);
            
            PlayerSensei Haloise = new PlayerSensei("Haloise", 80, 1, 12, Color.BLUE.get());
            Haloise.addActions(ActionLibrary.ENCYCLOPEDIA, ActionLibrary.PROTECT, ActionLibrary.SMELL);
            
            PlayerSensei Clover = new PlayerSensei("Clover", 100, 1, 16, Color.YELLOW.get());
            Clover.addActions(ActionLibrary.CLONE, ActionLibrary.PROTECT, ActionLibrary.SMELL);

            PlayerSensei Xhara = new PlayerSensei("Xhara", 40, 1, 10, Color.CYAN.get());
            Xhara.addActions(ActionLibrary.BETRAYAL, ActionLibrary.PROTECT, ActionLibrary.SMELL);

            Enemy Sensei = new Enemy("Sensei", 20);
            Sensei.addActions(ActionLibrary.VERTICAL, ActionLibrary.HORIZONTAL, ActionLibrary.KAMEHAMEHA);

            addEntity(Derek, Flavie, Haloise, Clover, Xhara, Sensei);
        }

        else if (name.equals("Spirit")){
            PlayerSpirit Derek = new PlayerSpirit("Derek", "fire");
            Derek.addActions(ActionLibrary.TASER, ActionLibrary.MAGIC);

            PlayerSpirit Flavie = new PlayerSpirit("Flavie", "ice");
            Flavie.addActions(ActionLibrary.HACK, ActionLibrary.MAGIC);

            PlayerSpirit Haloise = new PlayerSpirit("Haloise", "water");
            Haloise.addActions(ActionLibrary.ENCYCLOPEDIA, ActionLibrary.MAGIC);

            PlayerSpirit Clover = new PlayerSpirit("Clover", "light");
            Clover.addActions(ActionLibrary.CLONE, ActionLibrary.MAGIC);
            
            PlayerSpirit Xhara = new PlayerSpirit("Xhara", "vegetal");
            Xhara.addActions(ActionLibrary.BETRAYAL, ActionLibrary.MAGIC);
            
            for (int i = 0; i < 3; i++){
                Spirit s = Spirit.chooseSpirit(seed);
                enemies.put(s.getName(), s);
            }
            addEntity(Derek, Flavie, Haloise, Clover, Xhara);
        }
        else if (name.equals("Final")){
            PlayerDice Derek = new PlayerDice("Derek", 250, 50, 6);
            Derek.addActions(ActionLibrary.TASER, ActionLibrary.SWORD, ActionLibrary.PROVOKE, ActionLibrary.PROTECT);
            
            PlayerDice Flavie = new PlayerDice("Flavie", 120, 20, 30);
            Flavie.addActions(ActionLibrary.HACK, ActionLibrary.SHIELD, ActionLibrary.POTION, ActionLibrary.PROTECT);

            PlayerDice Haloise = new PlayerDice("Haloise", 350, 10, 10);
            Haloise.addActions(ActionLibrary.ENCYCLOPEDIA, ActionLibrary.HAMMER, ActionLibrary.STONE, ActionLibrary.PROTECT);

            PlayerDice Clover = new PlayerDice("Clover", 80, 60, 4);
            Clover.addActions(ActionLibrary.CLONE, ActionLibrary.KNIFE, ActionLibrary.GOLD, ActionLibrary.PROTECT);

            PlayerDice Xhara = new PlayerDice("Xhara", 150, 30, 20);
            Xhara.addActions(ActionLibrary.RETREAT, ActionLibrary.FOCUS, ActionLibrary.PROTECT);

            Enemy Virus = new Enemy("Virus", 1500);
            Virus.addActions(ActionLibrary.DRAIN, ActionLibrary.CONFUSE, ActionLibrary.REVOLUTION, ActionLibrary.CLAWVIRUS, ActionLibrary.SOUL);

            Enemy H0PE = new Enemy("H0PE", 300);
            H0PE.addActions(ActionLibrary.HEAL, ActionLibrary.ENRAGE, ActionLibrary.TARGET, ActionLibrary.REFLECT);
            
            addEntity(Derek, Flavie, Haloise, Clover, Xhara, Virus, H0PE);
        }
        else{
            throw new IllegalArgumentException(Color.RED.get() + "Unrecognized battle : ABORT" + Color.YELLOW.get());
        }
    }

    private void addEntity(Entity... chs){
        for (Entity ch : chs) {
            if (ch instanceof Enemy){
                Enemy e = (Enemy) ch;
                enemies.put(ch.getName(), e);
            }
            else{
                team.put(ch.getName(), ch);
            }
        }
    }

    @Override
    public String toString(){
        String result = Color.WHITE.get() + "***turn " + turn + " ***\n\n" + Color.RED.get() + "ENEMIES\n";
        for (Enemy e : enemies.values()){
            result += e.toString();
        }

        result = result + "\n" + Color.CYAN.get() + "TEAM\n";

        for (Entity e : team.values()) {
            result += e.toString();
        }
        return result;
    }
}
