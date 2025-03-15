package state;

public class State {
    private String name;
    private int end;

    public State(){
        name = "none";
        end = -1;
    }

    public State(State s){
        name = s.name;
        end = s.end;
    }

    public State(String name, int end){
        this.name = name;
        this.end  = end;
    }

    public String getName(){
        return name;
    }

    public int getEnd(){
        return end;
    }

    @Override
    public String toString(){
        return  end > 0 && end < Integer.MAX_VALUE ?  "[ " + name + " (" + end + ") ]" : "[ " + name + " ]";
    }
}
