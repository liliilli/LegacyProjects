package Game;

import Game.Map.MapListType;
import Sound.*;

import java.awt.*;
import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException, FontFormatException {
        Game game = Game.getInstance();
        //game.addNewScene(MapListType.newMap(MapListType.TESTSCENE_01));
        game.addNewScene(MapListType.newMap(MapListType.TITLE));
        game.sceneActivate();
        game.onLoopSafe();
        game.loop();
    }
}
