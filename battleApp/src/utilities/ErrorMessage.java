package utilities;

public enum ErrorMessage {
    PROMPT (Color.RED.get() + "Unrecognized prompt !" + Color.DEFAULT.get()),
    COMMAND (Color.RED.get() + "Unrecognized debug command !" + Color.DEFAULT.get()),
    INTEGER_VALUE (Color.YELLOW.get() + "Warning : Invalid integer value ! Taking 0 by default." + Color.DEFAULT.get()),
    CHARACTER (Color.RED.get() + "Unrecognized target character !" + Color.DEFAULT.get()),
    INVALID_ENEMY (Color.YELLOW.get() + "Warning : unrecognized target enemy ! Assuming default enemy." + Color.DEFAULT.get()),
    INVALID_DICE (Color.YELLOW.get() + "Warning : invalid dice value for this character. Assuming lowest score." + Color.DEFAULT.get()),
    NOT_INITIALIZED (Color.RED.get() + "Pointer not initialized : ABORT" + Color.DEFAULT.get()),
    WRONG_METHOD (Color.RED.get() + "Method not suited for this class : ABORT" + Color.DEFAULT.get());

    private String message;

    ErrorMessage(String message){
        this.message = message;
    }

    public String get(){
        return message;
    }
}
