package action;

import state.StateLibrary;

public enum ActionLibrary{
    /*
     * List of available actions. 
     * Parameters are declared regarding the Dragon fight by default !!
     */

    TASER (new ActionG("taser", 10, 0, 'i', StateLibrary.STUN)),
    SWORD (new ActionG("sword", 100, 0, 'i')),
    PROVOKE (new ActionL("porvoke", 0, 0, 'i', 80, StateLibrary.PROVOKE)),
    HACK (new ActionR("hack", 500, 0, 'i')),
    SHIELD (new ActionG("shield", 0, 100, 'a', StateLibrary.DEFENSE1)),
    POTION (new ActionR("potion", 0, 0, 'i', StateLibrary.CORRUPT)),
    ENCYCLOPEDIA (new ActionR("encyclopedia", 0, 0, 'i')),
    STONE (new ActionG("stone", 0, 50, 'i', StateLibrary.DEFENSE3)),
    HAMMER (new ActionG("hammer", 300, 0, 'i', StateLibrary.DANGER)),
    BETRAYAL (new ActionL("betrayal", 0, 0, 'i', 100)),
    RETREAT (new ActionG("retreat", 0, 100, 'i', StateLibrary.DEFENSE3)),
    FOCUS (new ActionL("focus", 0, 0, 'i', 100, StateLibrary.FOCUS)),
    CLONE (new ActionG("clone", 0, 0, 'i', StateLibrary.CLONE)),
    KNIFE (new ActionG("knife", 300, 0, 'i')),
    GOLD (new ActionL("gold", 40, 0, 'i', 60, StateLibrary.BOOST)),

    FIREBREATH (new ActionE("firebreath", 50, 0, 'a', 40)),
    STOMP (new ActionE("stomp", 70, 0, 'i', 35, true)),
    BITE (new ActionE("bite", 30, 100, 'i', 20)),
    CLAW (new ActionE("claw", Integer.MAX_VALUE, 0, 'i', 5)),

    PROTECT (new ActionL("protect", 0, 0, 'i', 100, StateLibrary.PROTECT)),
    SMELL (new ActionR("smell", 0, 0, 'i', StateLibrary.SMELL)),

    VERTICAL (new ActionE("vertical", 8, 0, 'i', 40, true)),
    HORIZONTAL (new ActionE("horizontal", 8, 0, 'i', 40, true)),
    KAMEHAMEHA (new ActionE("kamehameha", 10, 0, 'a', 20, true)),

    MAGIC (new ActionL("magic", 0, 0, 'e', 100)),
    INDIV (new ActionE("aim attack", 50, 0, 'i', 60, true)),
    MULTI (new ActionE("spread attack", 50, 0, 'i', 40, true)),

    DRAIN (new ActionE("drain", 30, 50, 'i', 20, StateLibrary.WEAKEN)),
    CONFUSE (new ActionE("confuse", 0, 0, 'i', 15, StateLibrary.CONFUSE)),
    REVOLUTION (new ActionE("revolution", -1, 0, 'a', 15)),
    CLAWVIRUS (new ActionE("claw", 50, 0, 'i', 50, true)),
    SOUL (new ActionE("SOUL", 0, 100, 'i', 0)),
    HEAL (new ActionE("heal", 0, 150, 'i', 25, StateLibrary.VIRUS)),
    ENRAGE (new ActionE("enrage", 0, 0, 'i', 25, StateLibrary.RAGE)),
    TARGET (new ActionE("target", 0, 0, 'i', 25, StateLibrary.TARGET)),
    REFLECT (new ActionE("reflect", 0, 0, 'i', 25, StateLibrary.REFLECT));

    private Action act;

    ActionLibrary(Action act){
        this.act = act;
    }

    public Action get(){
        return this.act;
    }

}
