package utilities;

import java.util.Random;
import java.util.HashMap;
import java.io.Console;

import main.Battle;

public class Utility {
    public static int entropy(int value, int min, int var, Random seed){
        int ratio = (10 + seed.nextInt(var));
        return ratio * value / 100;
    }

    public static int retrieveIntValue(String command){
        while(true){
            try{
                int n = Integer.parseInt(command);
                return n;
            }
            catch(NumberFormatException ex){
                System.out.println(Color.RED.get() + "Invalid Number format : please prompt a new number or prompt 'break' to cancel your command." + Color.DEFAULT.get());
                Console cons = System.console();
                command = Battle.readWholeStream(Battle.askInput(cons));
                if (command.equals("break")){
                    return 0;
                }
            }
        }
    }

    private HashMap<String, int[]> diceRanges;

    public Utility(){
        diceRanges = new HashMap<>();

        diceRanges.put("Derek", new int[]{4, 6});
        diceRanges.put("Flavie", new int[]{16, 30});
        diceRanges.put("Haloise", new int[]{8, 10});
        diceRanges.put("Clover", new int[]{3, 4});
        diceRanges.put("Xhara", new int[]{7, 12});
    }

    public int[] get(String key) throws NullPointerException {
        if (diceRanges == null){
            throw new NullPointerException(ErrorMessage.NOT_INITIALIZED.get());
        }
        if (!diceRanges.containsKey(key)){
            throw new NullPointerException(ErrorMessage.CHARACTER.get());
        }
        return diceRanges.get(key);
    }


}
