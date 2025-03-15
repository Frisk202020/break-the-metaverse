package main;
import java.util.Arrays;
import java.util.Scanner;
import java.io.Console;

import utilities.*;

/** Later-to-develop functionalities
 * Write/Read battle data from file
 * Retain last inputs
*/

public class BattleMain {
    public static void main(String[] args) throws EnemyStatsException, NullPointerException {
        Console cons = System.console();
        Battle battle = null;

        // Choose battle from user
        boolean loop = true;
        Scanner s = null;
        while(loop){
            try{
                s = Battle.askInput(cons, "Which Battle should be launched ?");
                String name = Battle.readWholeStream(s);
                if (name.equals("exit")){
                    return;
                }
                else{
                    battle = new Battle(name);
                }
                battle.assertEnemyStats();
                loop = false;
            }
            catch(IllegalArgumentException ex){
                System.out.println(ex.getMessage());
                System.out.println(Color.YELLOW.get() + "Prompt again the battle name, or prompt 'exit' to close the App." + Color.DEFAULT.get());
            }
        }
        
        while (!battle.isOver()){
            battle.resetState();
            System.out.println(battle.toString());
            Battle.askInput(cons);

            String[] prompt = Battle.readEachWord(s);
            if (prompt[0].equals("exit")){
                break;
            }
            else if (prompt[0].equals("attack")){
                battle.attack(Arrays.copyOfRange(prompt, 1, prompt.length));
            }
            else if (prompt[0].equals("action")){
                
            }
            else if (prompt[0].equals("betray")){
                
            }
            else if (prompt[0].equals("upgrade")){
                
            }
            else if (prompt[0].equals("debug")){
                if (prompt[1].equals("damage")){
                    battle.damage(Arrays.copyOfRange(prompt, 2, prompt.length));
                }
                else if (prompt[1].equals("heal")){
                    prompt[3] = "-" + prompt[3];
                    battle.damage(Arrays.copyOfRange(prompt, 2, prompt.length));
                }
                else{
                    System.out.println(ErrorMessage.COMMAND.get());
                }
            }
            else{
                System.out.println(ErrorMessage.PROMPT.get());
            }
        }
    }
}
