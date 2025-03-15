package main;
import java.util.HashMap;
import java.util.Random;
import java.util.Arrays;
import java.util.Scanner;
import java.io.Console;

import action.*;
import entity.*;
import utilities.*;

public class Battle {
    private String name;
    private int turn;
    private HashMap<String, Player> team;
    private HashMap<String, Enemy> enemies;
    private String defaultEnemy;
    private Random seed;

    public Battle(String name) throws NullPointerException {
        this.name = name;
        turn = 1;
        team = new HashMap<>();
        enemies = new HashMap<>();
        seed = new Random();

        if (name.equals("Dragon")){
            Utility u = new Utility();
            PlayerDice Derek = new PlayerDice("Derek", 250, 50, u.get("Derek"));
            Derek.addActions(ActionLibrary.TASER, ActionLibrary.SWORD, ActionLibrary.PROVOKE);
            
            PlayerDice Flavie = new PlayerDice("Flavie", 120, 20, u.get("Flavie"));
            Flavie.addActions(ActionLibrary.HACK, ActionLibrary.SHIELD, ActionLibrary.POTION);

            PlayerDice Haloise = new PlayerDice("Haloise", 350, 10, u.get("Haloise"));
            Haloise.addActions(ActionLibrary.ENCYCLOPEDIA, ActionLibrary.HAMMER, ActionLibrary.STONE);

            PlayerDice Clover = new PlayerDice("Clover", 80, 60, u.get("Clover"));
            Clover.addActions(ActionLibrary.CLONE, ActionLibrary.KNIFE, ActionLibrary.GOLD);

            PlayerDice Xhara = new PlayerDice("Xhara", 150, 30, u.get("Xhara"));
            Xhara.addActions(ActionLibrary.BETRAYAL, ActionLibrary.RETREAT, ActionLibrary.FOCUS);

            Enemy Dragon = new Enemy("Dragon", 1000);
            Dragon.addActions(ActionLibrary.FIREBREATH, ActionLibrary.STOMP, ActionLibrary.BITE, ActionLibrary.CLAW);

            addEntity(Derek, Flavie, Haloise, Clover, Xhara, Dragon);
            defaultEnemy = "Dragon";
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
            defaultEnemy = "Sensei";
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
                if (i == 0){
                    defaultEnemy = s.getName();
                }
            }
            addEntity(Derek, Flavie, Haloise, Clover, Xhara);
            defaultEnemy = "Spirit";
        }
        else if (name.equals("Final")){
            Utility u = new Utility();
            PlayerDice Derek = new PlayerDice("Derek", 250, 50, u.get("Derek"));
            Derek.addActions(ActionLibrary.TASER, ActionLibrary.SWORD, ActionLibrary.PROVOKE, ActionLibrary.PROTECT);
            
            PlayerDice Flavie = new PlayerDice("Flavie", 120, 20, u.get("Flavie"));
            Flavie.addActions(ActionLibrary.HACK, ActionLibrary.SHIELD, ActionLibrary.POTION, ActionLibrary.PROTECT);

            PlayerDice Haloise = new PlayerDice("Haloise", 350, 10, u.get("Haloise"));
            Haloise.addActions(ActionLibrary.ENCYCLOPEDIA, ActionLibrary.HAMMER, ActionLibrary.STONE, ActionLibrary.PROTECT);

            PlayerDice Clover = new PlayerDice("Clover", 80, 60, u.get("Clover"));
            Clover.addActions(ActionLibrary.CLONE, ActionLibrary.KNIFE, ActionLibrary.GOLD, ActionLibrary.PROTECT);

            PlayerDice Xhara = new PlayerDice("Xhara", 150, 30, u.get("Xhara"));
            Xhara.addActions(ActionLibrary.RETREAT, ActionLibrary.FOCUS, ActionLibrary.PROTECT);

            Enemy Virus = new Enemy("Virus", 1500);
            Virus.addActions(ActionLibrary.DRAIN, ActionLibrary.CONFUSE, ActionLibrary.REVOLUTION, ActionLibrary.CLAWVIRUS, ActionLibrary.SOUL);

            Enemy H0PE = new Enemy("H0PE", 300);
            H0PE.addActions(ActionLibrary.HEAL, ActionLibrary.ENRAGE, ActionLibrary.TARGET, ActionLibrary.REFLECT);
            
            addEntity(Derek, Flavie, Haloise, Clover, Xhara, Virus, H0PE);
            defaultEnemy = "Virus";
        }
        else{
            throw new IllegalArgumentException(Color.RED.get() + "Unrecognized battle : ABORT" + Color.DEFAULT.get());
        }
    }

    public static Scanner askInput(Console cons){
        System.out.printf("> ");
        return new Scanner(cons.reader());
    }

    public static Scanner askInput(Console cons, String message){
        System.out.println(message);
        System.out.printf("> ");
        return new Scanner(cons.reader());
    }

    public static String readWholeStream(Scanner s){
        return s.nextLine();
    }

    public static String[] readEachWord(Scanner s){
        return s.nextLine().split(" ");
    }

    public void assertEnemyStats() throws EnemyStatsException {
        for (Enemy e : enemies.values()) {
            if (e.sumOdds() != 100){
                throw new EnemyStatsException(Color.RED.get() + "ERROR for enemy : " + e.getName() + Color.YELLOW.get());
            }
        }
    }

    public boolean isOver(){
        boolean over = true;
        for (Player p : team.values()) {
            if (p.isAlive()){
                over = false;
                break;
            }
        }
        if (over){
            System.out.println(Color.RED.get() + "The team is defeated..." + Color.DEFAULT.get());
            return true;
        }
        over = false;
        for (Enemy e : enemies.values()){
            if (e.isAlive()){
                over = false;
                break;
            }
        }
        if (over){
            System.out.println(Color.GREEN.get() + "The team won !" + Color.DEFAULT.get());
        }
        return over;
    }

    public void resetState(){
        for (Player p : team.values()){
            p.setCorrectHpValue();
            p.setCorrectState(turn);
        }
        for (Enemy e : enemies.values()){
            e.setCorrectHpValue();
            e.setCorrectState(turn);
        }
    }

    public void enemyAttack(Enemy thisEnemy, ActionE attack){
        if  (attack.getHeal() > 0){
            if (attack.getAim() == 0){
                System.out.println(Color.RED.get() + thisEnemy.getName() + "heals himself " + attack.getHeal() + " ♥ !" + Color.DEFAULT.get());
                thisEnemy.damage(-attack.getHeal());
            }
            else {
                System.out.println("special action to implement");
            }
        }
        switch(attack.getAim()){
            case 1:
                System.out.println(Color.RED.get() + thisEnemy.getName() + " attacks the entire team with : " + attack.getName() + " !" + Color.DEFAULT.get());
                for (Player p : team.values()){
                    p.damage(attack.getPow());
                }
                break;
            case 0:
                Player target = Player.pickRandomPlayer(seed, team);
                System.out.println(Color.RED.get() + thisEnemy.getName() + " attacks " + target.getName() + " with : " + attack.getName() + " !" + Color.DEFAULT.get());
                target.damage(attack.getPow());
                break;
            default:
                System.out.println("special cases to develop");
        }
        return;
    }

    public void attack(String[] command){
        //need to add states varaiations
        if (team.containsKey(command[0])){
            int diceValue;
            int damage;
            if (enemies.size() == 1){
                diceValue = Utility.retrieveIntValue(command[1]);
                damage = team.get(command[0]).attack(diceValue);
                enemies.get(defaultEnemy).damage(damage);
            }
            else{
                diceValue = Utility.retrieveIntValue(command[3]);
                damage = team.get(command[0]).attack(diceValue);
                if (enemies.containsKey(command[2])){
                    enemies.get(command[2]).damage(damage);
                }
                else{
                    System.out.println(ErrorMessage.INVALID_ENEMY.get());
                    enemies.get(defaultEnemy).damage(damage);
                }
            }
        }
        else if (enemies.containsKey(command[0]) || command[0].equals(defaultEnemy)) {
            Enemy e = enemies.get(command[0]);
            ActionE a;
            boolean done = false;

            if (command.length > 1){
                boolean loop = true;
                while(loop){
                    try{
                        a = e.getActions().get(command[1]);
                        enemyAttack(e, a);
                        loop = false;
                        done = true;
                    }
                    catch (NullPointerException ex){
                        System.out.println(Color.RED.get() + "Unrecognized action : prompt again the desired action, or prompt 'break' to choose a random action instead" + Color.DEFAULT.get());
                        Console cons = System.console();
                        String ans = readWholeStream(askInput(cons));
                        if (ans.equals("break")){
                            loop = false;
                        }
                        else{
                            command[1] = ans;
                        }
                    }
                }
            }
            if (!done){
                a = ActionE.pickRandomAction(seed, e.getActions());
                enemyAttack(e, a);
            }
        }
        else{
            System.out.println(ErrorMessage.CHARACTER.get());
        }
    }

    public void damage(String[] command){
        if (team.containsKey(command[0])){
            int commandInt = Utility.retrieveIntValue(command[1]);
            team.get(command[0]).damage(commandInt);
            return;
        }
        if (enemies.containsKey(command[0])){
            int commandInt = Utility.retrieveIntValue(command[1]);
            enemies.get(command[0]).damage(commandInt);
            return;
        }
        System.out.println(ErrorMessage.CHARACTER.get());
    }

    private void addEntity(Entity... chs){
        for (Entity ch : chs) {
            if (ch instanceof Enemy){
                Enemy e = (Enemy) ch;
                enemies.put(ch.getName(), e);
            }
            else{
                Player p = (Player) ch;
                team.put(p.getName(), p);
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

        for (Player p : team.values()) {
            result += p.toString();
        }

        if (name == "Spirit"){
            result = result + Color.YELLOW.get() + "\nORB : " +  Arrays.toString(PlayerSpirit.getOrb()) + Color.DEFAULT.get() + "\n";
        }
        return result + Color.DEFAULT.get();
    }
}
