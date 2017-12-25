package Game.Map;

import Scenes.AbstractScene;
import Scenes.EtcScenes.Title;
import Scenes.GameMaps.M_00WorldMap;
import Scenes.GameMaps.M_10Village1;
import Scenes.GameMaps._TestScene;
import Scenes.GameMaps._TestScene2;

import java.awt.*;
import java.io.IOException;

public enum MapListType {
    WORLD_FIELD(0x00, "Map00.map"),

    VILLIAGE_01(0x10, "Map10.map"),
    VILLIAGE_02(0x20, "Map20.map"),

    DUNGEON_01(0x40, "Map40.map"),
    DUNGEON_02(0x41, "Map41.map"),

    TESTSCENE_01(0xF0, "MapF0.map"),
    TESTSCENE_02(0xF1, "MapF1.map"),

    INVENTORY(0xFA, "MapFF.map"),
    DEAD(0xFB, "MapFF.map"),
    ENDING(0xFC, "MapFF.map"),
    TITLE(0xFF, "MapFF.map");

    private final int mapId;
    private final String mapPath;

    MapListType(int mapId, String mapPath) {
        this.mapId = mapId;
        this.mapPath = "src\\Game\\Resources\\Maps\\" + mapPath;
    }

    public int getMapId() { return mapId; }
    public String getMapPath() { return mapPath; }

    public static AbstractScene newMap(MapListType type) {
        try {
            switch (type) {
                case WORLD_FIELD: return new M_00WorldMap(WORLD_FIELD.getMapPath());
                case TESTSCENE_01: return new _TestScene(TESTSCENE_01.getMapPath());
                case TESTSCENE_02: return new _TestScene2(TESTSCENE_02.getMapPath());
                case VILLIAGE_01: return new M_10Village1(VILLIAGE_01.getMapPath());
                case TITLE: return new Title(TITLE.getMapPath());
                default: return null;
            }
        } catch (IOException | FontFormatException err) {
            err.printStackTrace();
        }
        return null;
    }

    public static MapListType getMapType(int mapValue) {
        for (MapListType elm : MapListType.values()) {
            if (elm.getMapId() == mapValue)
                return elm;
        }

        return null;
    }
}
