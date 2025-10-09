package utilities;

import java.util.ArrayList;

class TupleHashTest{
    private TupleHash<String, Integer> test;

    private TupleHashTest(){
        test = new TupleHash<>(); 
    }

    private void containsKeytest(){
        test.reset();
        
        String[] key1 = {"1", "0"};
        String[] key2 = {"1"};
        String[] key1_bis = key1;
        String[] key1_bis_bis = {"1", "0"};
        String[] key3 = {"1", "1"};

        test.put(key1, 10);
        test.put(key2, 111);

        boolean pass = true;

        if (!test.containsKey(key1)){
            System.out.println(Color.RED.get() + "- containsKeyTest : test does not contain key1" + Color.DEFAULT.get());
            pass = false;
        }
        if (!test.containsKey(key2)){
            System.out.println(Color.RED.get() + "\t- containsKeyTest : test does not contain key2" + Color.DEFAULT.get());
            pass = false;
        }
        if (!test.containsKey(key1_bis)){
            System.out.println(Color.RED.get() + "\t- containsKeyTest : test does not contain key1_bis" + Color.DEFAULT.get());
            pass = false;
        }
        if (!test.containsKey(key1_bis_bis)){
            System.out.println(Color.RED.get() + "\t- containsKeyTest : test does not contain key1_bis_bis" + Color.DEFAULT.get());
            pass = false;
        }
        if (test.containsKey(key3)){
            System.out.println(Color.RED.get() + "\t- containsKeyTest : test contains key3" + Color.DEFAULT.get());
            pass = false;
        }
        if (pass){
            System.out.println(Color.GREEN.get() + "\t+ containsKeyTest : Success !" + Color.DEFAULT.get());
        }
    }

    private void putTest(){
        test.reset();

        String[] key1 = {"1", "0"};
        String[] key2 = {"1", "1", "1"};
        String[] key3 = {"1"};
        String[] key1_bis = {"1", "0"};
        String[] key1_bisbis = key1;

        test.put(key1, 10);
        test.put(key2, 111);
        test.put(key3, 1);
        test.put(key1_bis, -1);
        test.put(key1_bisbis, -2);

        ArrayList<String[]> goodKeys =  new ArrayList<>();
        ArrayList<Integer> goodValues = new ArrayList<>();
        
        String[] goodKey1 = new String[2];
        String[] goodKey2 = new String[3];
        String[] goodKey3 = new String[1];
        System.arraycopy(key1, 0, goodKey1, 0, 2);
        System.arraycopy(key2, 0, goodKey2, 0, 3);
        System.arraycopy(key3, 0, goodKey3, 0, 1);
        goodKeys.add(goodKey1);
        goodKeys.add(goodKey2);
        goodKeys.add(goodKey3);
        goodValues.add(10);
        goodValues.add(111);
        goodValues.add(1);

        if (test.keyEquals(goodKeys)){
            System.out.println(Color.GREEN.get() + "\t+ putTest : keys are correct !" + Color.DEFAULT.get());
            System.out.println("\t\t> " + test.keysToString());
        }
        else {
            System.out.println(Color.RED.get() + "\t- putTest : keys test failed !" + Color.DEFAULT.get());
            System.out.println("\t\t> " + test.keysToString());
        }
        if (goodValues.equals(test.getValues())){
            System.out.println(Color.GREEN.get() + "\t+ putTest : values are correct !" + Color.DEFAULT.get());
            System.out.println("\t\t> " + test.getValues().toString());
        }
        else {
            System.out.println(Color.RED.get() + "\t- putTest : values test failed !" + Color.DEFAULT.get());
            System.out.println("\t\t> " + test.getValues().toString());
        }
    }

    void getTest(){
        test.reset();

        String[] key1 = {"1", "0"};
        String[] key2 = {"1", "1", "1"};
        String[] key3 = {"0"};

        ArrayList<String[]> goodKeys =  new ArrayList<>();
        String[] goodKey1 = new String[2];
        String[] goodKey2 = new String[3];
        String[] goodKey3 = new String[1];
        System.arraycopy(key1, 0, goodKey1, 0, 2);
        System.arraycopy(key2, 0, goodKey2, 0, 3);
        System.arraycopy(key3, 0, goodKey3, 0, 1);
        goodKeys.add(goodKey1);
        goodKeys.add(goodKey2);
        goodKeys.add(goodKey3);

        test.put(key1, 10);
        test.put(key2, 111);
        test.put(key3, 10);

        boolean pass = true;
        if (!(test.get(key1) == 10)){
            System.out.println(Color.RED.get() + "\t- getTest : key1 does not refer to value 10 !" + Color.DEFAULT.get());
            pass = false;
        }
        if (!(test.get(goodKey1) == 10)){
            System.out.println(Color.RED.get() + "\t- getTest : goodKey1 does not refer to value 10 !" + Color.DEFAULT.get());
            pass = false;
        }
        if (!(test.get(key2) == 111)){
            System.out.println(Color.RED.get() + "\t- getTest : key2 does not refer to value 111 !" + Color.DEFAULT.get());
            pass = false;
        }
        if (!(test.get(goodKey2) == 111)){
            System.out.println(Color.RED.get() + "\t- getTest : goodKey2 does not refer to value 111 !" + Color.DEFAULT.get());
            pass = false;
        }
        if (!(test.get(key3) == 10)){
            System.out.println(Color.RED.get() + "\t- getTest : key3 does not refer to value 10 !" + Color.DEFAULT.get());
            pass = false;
        }
        if (!(test.get(goodKey3) == 10)){
            System.out.println(Color.RED.get() + "\t- getTest : goodKey3 does not refer to value 10 !" + Color.DEFAULT.get());
            pass = false;
        }
        if (!(test.get(null) == null)){
            System.out.println(Color.RED.get() + "\t- getTest : unknown key does not return null pointer !" + Color.DEFAULT.get());
            pass = false;
        }
        if (pass){
            System.out.println(Color.GREEN.get() + "\t+ getTest : Success !" + Color.DEFAULT.get());
        }
    }

    public static void main(String[] args) {
        TupleHashTest test = new TupleHashTest();

        System.out.println("*** Testing TupleHash Class... ***");
        test.containsKeytest();
        test.putTest();
        test.getTest();
    }
}