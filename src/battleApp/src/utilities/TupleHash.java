package utilities;

import java.util.ArrayList;
import java.util.Arrays;
import state.*;

public class TupleHash<T1, T2> {
    private ArrayList<T1[]> keys;
    private ArrayList<T2> values;
    private ArrayList<Integer> code;

    public TupleHash(){
        keys = new ArrayList<>();
        values = new ArrayList<>();
        code = new ArrayList<>();
    }

    public boolean containsKey(T1[] key){
        for (T1[] k : keys) {
            if (Arrays.equals(k, key)){
                return true;
            }
        }
        return false;
    }

    void put(T1[] key, T2 value){
        if (!containsKey(key)){
            keys.add(key);
            values.add(value);
            if (code.isEmpty()){
                code.add(0);
            }
            else{
                code.add(code.getLast() + 1);
            }
            return;
        }
        System.out.println(Color.RED.get() + "Key already in TupleHash : " + Arrays.toString(key) + " " + value.toString() + "; ABORTED" + Color.DEFAULT.get());
        return;
    }

    public T2 get(T1[] key){
        for (int i = 0; i < code.size(); i++){
            if (Arrays.equals(key, keys.get(i))){
                return values.get(i);
            }
        }

        System.out.println(Color.YELLOW.get() + "Warning : returning null pointer at : TupleHash(" + Arrays.toString(key) + ")" + Color.DEFAULT.get());
        return null;
    }

    public String keysToString(){
        String result = "{ ";
        for (T1[] key : keys) {
            result += Arrays.toString(key);
            result += " ";            
        }
        return result + "}";
    }

    public static TupleHash<String, State> initializeMagic(){
        TupleHash<String, State> t = new TupleHash<>();

        t.put(new String[] {"fire", "fire"}, StateLibrary.FIRE.get());
        t.put(new String[] {"fire", "ice"}, StateLibrary.WATER.get());
        t.put(new String[] {"fire", "water"}, StateLibrary.FUME.get());
        t.put(new String[] {"fire", "light"}, StateLibrary.BURST.get());
        t.put(new String[] {"fire", "vegetal"}, StateLibrary.POISON.get());
        t.put(new String[] {"ice", "fire"}, StateLibrary.WATER.get());
        t.put(new String[] {"ice", "ice"}, StateLibrary.ICE.get());
        t.put(new String[] {"ice", "water"}, StateLibrary.SCULPTURE.get());
        t.put(new String[] {"ice", "light"}, StateLibrary.BEAM.get());
        t.put(new String[] {"ice", "vegetal"}, StateLibrary.DARKNESS.get());
        t.put(new String[] {"water", "fire"}, StateLibrary.FUME.get());
        t.put(new String[] {"water", "ice"}, StateLibrary.SCULPTURE.get());
        t.put(new String[] {"water", "water"}, StateLibrary.WATER.get());
        t.put(new String[] {"water", "light"}, StateLibrary.HEAL.get());
        t.put(new String[] {"water", "vegetal"}, StateLibrary.PLANT.get());
        t.put(new String[] {"light", "fire"}, StateLibrary.BURST.get());
        t.put(new String[] {"light", "ice"}, StateLibrary.BEAM.get());
        t.put(new String[] {"light", "water"}, StateLibrary.HEAL.get());
        t.put(new String[] {"light", "light"}, StateLibrary.LIGHT.get());
        t.put(new String[] {"light", "vegetal"}, StateLibrary.LILA.get());
        t.put(new String[] {"vegetal", "fire"}, StateLibrary.POISON.get());
        t.put(new String[] {"vegetal", "ice"}, StateLibrary.DARKNESS.get());
        t.put(new String[] {"vegetal", "water"}, StateLibrary.PLANT.get());
        t.put(new String[] {"vegetal", "light"}, StateLibrary.LILA.get());
        t.put(new String[] {"vegetal", "vegetal"}, StateLibrary.VEGETAL.get());

        return t;
    }

    /* Methods used for testing */

    void reset(){
        keys.clear();
        values.clear();
        code.clear();
    }

    ArrayList<T1[]> getKeys(){
        return keys;
    }

    ArrayList<T2> getValues(){
        return values;
    }

    boolean keyEquals(ArrayList<T1[]> goodKeys){
        for (int i = 0; i < keys.size(); i++) {
            if (!Arrays.equals(keys.get(i), goodKeys.get(i))){
                return false;
            }
        }
        return true;
    }
}
