package entity;

import java.util.ArrayList;

import state.StateLibrary;

public enum SpiritLibrary {
    FIRE (new Spirit("Fire spirit", StateLibrary.WATER)),
    ICE (new Spirit("Ice spirit", StateLibrary.FIRE)),
    WATER (new Spirit("Water spirit", StateLibrary.FIRE)),
    LIGHT (new Spirit("Light spirit", StateLibrary.DARK)),
    VEGETAL (new Spirit("Vegetal spirit", StateLibrary.DARK)),
    GLUTTON (new Spirit("Glutton spirit", StateLibrary.VEGETAL)),
    DARKSHELL (new Spirit("Dark shell", StateLibrary.BURST)),
    KNIGHT (new Spirit("Knight", StateLibrary.POISON)),
    SOLID (new Spirit("Solid shell", StateLibrary.SCULPTURE)),
    DARK (new Spirit("Dark spirit", StateLibrary.BEAM)),
    CLIMATE (new Spirit("Climate spirit", StateLibrary.FUME)),
    SENSEI (new Spirit("Sensei's soul", StateLibrary.LILA));

    private Spirit spirit;
    
    SpiritLibrary(Spirit spirit){
        this.spirit = spirit;
    }

    Spirit get(){
        return spirit;
    }

    public static ArrayList<Spirit> generateList(){
        ArrayList<Spirit> result = new ArrayList<>();

        for (SpiritLibrary s : SpiritLibrary.values()) {
            result.add(s.get());
        }

        return result;
    }
}
