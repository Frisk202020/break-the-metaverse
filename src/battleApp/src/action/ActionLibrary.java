package action;

import state.StateLibrary;

public enum ActionLibrary{
    /*
     * List of available actions. 
     * Parameters are declared regarding the Dragon fight by default !!
     */

    TASER (new ActionG("taser", 10, 0, 0, StateLibrary.STUN.get(1))),
    SWORD (new ActionG("sword", 100, 0, 0)),
    PROVOKE (new ActionL("porvoke", 0, 0, 0, 80, StateLibrary.PROVOKE.get(2))),
    HACK (new ActionR("hack", 500, 0, 0)),
    SHIELD (new ActionG("shield", 0, 100, 1, StateLibrary.DEFENSE.get(1))),
    POTION (new ActionR("potion", 0, 0, 0, StateLibrary.CORRUPT.get(Integer.MAX_VALUE))),
    ENCYCLOPEDIA (new ActionR("encyclopedia", 0, 0, 0)),
    STONE (new ActionG("stone", 0, 50, 0, StateLibrary.DEFENSE.get(3))),
    HAMMER (new ActionG("hammer", 300, 0, 0, StateLibrary.DANGER.get(1))),
    BETRAYAL (new ActionL("betrayal", 0, 0, 0, 100)),
    RETREAT (new ActionG("retreat", 0, 100, 0, StateLibrary.DEFENSE.get(3))),
    FOCUS (new ActionL("focus", 0, 0, 0, 100, StateLibrary.FOCUS.get(1))),
    CLONE (new ActionG("clone", 0, 0, 0, StateLibrary.CLONE.get(3))),
    KNIFE (new ActionG("knife", 300, 0, 0)),
    GOLD (new ActionL("gold", 40, 0, 0, 60, StateLibrary.BOOST.get(-1))),

    FIREBREATH (new ActionE("firebreath", 50, 0, 1, 40)),
    STOMP (new ActionE("stomp", 70, 0, 0, 35, true)),
    BITE (new ActionE("bite", 30, 100, 0, 20)),
    CLAW (new ActionE("claw", Integer.MAX_VALUE, 0, 0, 5)),

    PROTECT (new ActionL("protect", 0, 0, 0, 100, StateLibrary.PROTECT.get(1))),
    SMELL (new ActionR("smell", 0, 0, 0, StateLibrary.SMELL.get(1))),

    VERTICAL (new ActionE("vertical", 8, 0, 0, 40, true)),
    HORIZONTAL (new ActionE("horizontal", 8, 0, 0, 40, true)),
    KAMEHAMEHA (new ActionE("kamehameha", 10, 0, 1, 20, true)),

    MAGIC (new ActionL("magic", 0, 0, 'e', 100)),
    INDIV (new ActionE("aim attack", 50, 0, 0, 60, true)),
    MULTI (new ActionE("spread attack", 50, 0, 0, 40, true)),

    DRAIN (new ActionE("drain", 30, 50, 0, 20, StateLibrary.WEAKEN.get(3))),
    CONFUSE (new ActionE("confuse", 0, 0, 0, 15, StateLibrary.CONFUSE.get(2))),
    REVOLUTION (new ActionE("revolution", -1, 0, 1, 15)),
    CLAWVIRUS (new ActionE("claw", 50, 0, 0, 50, true)),
    SOUL (new ActionE("SOUL", 0, 100, 0, 0)),
    HEAL (new ActionE("heal", 0, 150, -1, 25, StateLibrary.VIRUS.get(-1))),
    ENRAGE (new ActionE("enrage", 0, 0, 0, 25, StateLibrary.RAGE.get(3))),
    TARGET (new ActionE("target", 0, 0, 0, 25, StateLibrary.TARGET.get(2))),
    REFLECT (new ActionE("reflect", 0, 0, 0, 25, StateLibrary.REFLECT.get(5)));

    private Action act;

    ActionLibrary(Action act){
        this.act = act;
    }

    public Action get(){
        return this.act;
    }

}
