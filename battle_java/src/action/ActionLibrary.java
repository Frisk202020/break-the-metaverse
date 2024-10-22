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
    KAMEHAMEHA (new ActionE("kamehameha", 10, 0, 'a', 20, true));

    private Action act;

    ActionLibrary(Action act){
        this.act = act;
    }

    public Action get(){
        return this.act;
    }

}
