package state;

public class State {
    private String name;
    private int end;

    public State(){
        name = "normal";
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

    public State copy(){
        return new State(this);
    }

    public State getInfinityEnd(){
        State newState = this.copy();
        newState.end = Integer.MAX_VALUE;
        return newState;
    }

    @Override
    public String toString(){
        return  end > 0 && end < Integer.MAX_VALUE ?  "[ " + name + " (" + end + ") ]" : "[ " + name + " ]";
    }
}
