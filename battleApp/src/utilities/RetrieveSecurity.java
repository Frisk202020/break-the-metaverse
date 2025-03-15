package utilities;

public class RetrieveSecurity {
    public static boolean ensureIntParseSecurity(String test){
        String authorized0 = "-0123456789";
        String authorized = "0123456789";
        if (!authorized0.contains(test.subSequence(0, 1))){
            return false;
        }
        for (int i = 1; i < test.length(); i++){
            if (!authorized.contains(test.subSequence(i, i + 1))){
                return false;
            }
        }
        return true;
    }
}
