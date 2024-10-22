package state;

public class State {
    private String name;
    private int end;

    public State(){
        name = "normal";
        end = -1;
    }

    public State(String name, int end){
        this.name = name;
        this.end  = end;
    }

    @Override
    public String toString(){
        return  end > 0 ?  "[ " + name + " (" + end + ") ]" : "[ " + name + " ]";
    }
}
