package Screen;

import Game.Map.ObjectType;

import javax.swing.*;
import java.awt.*;

public enum SpriteManager {
    NONE(ObjectType.NONE, "Blank.png"),

    BLOCK(ObjectType.BLOCK, "Blank.png"),
    SECRET(ObjectType.SECRET, "Blank.png"),

    SEA(ObjectType.SEA, "Map_Sea.png"),
    GLASS(ObjectType.GLASS, "Map_Glass.png"),
    VILLAGE(ObjectType.VILLAGE, "Map_Village.png"),
    MOUNTAIN(ObjectType.MOUNTAIN, "Map_Mountain.png"),
    DUNGEON(ObjectType.DUNGEON, "Map_Dungeon.png"),
    FOREST(ObjectType.FOREST, "Map_Forest.png"),

    WALL(ObjectType.WALL, "Map_Wall.png"),
    MOVEABLE(ObjectType.MOVEABLE, "Blank.png"),

    MOVE(ObjectType.MOVE, "Map_Door.png"),

    PLAYER(ObjectType.PLAYER, "Player.png"),
    NPC(ObjectType.NPC, "NPC.png"),
    ENEMY(ObjectType.ENEMY, "Enemy.png"),

    CHAR_I(ObjectType.CHAR_I, "Char_I.png"),
    CHAR_T(ObjectType.CHAR_T, "Char_T.png"),
    CHAR_E(ObjectType.CHAR_E, "Char_E.png"),
    CHAR_M(ObjectType.CHAR_M, "Char_M.png"),

    CHAR_R(ObjectType.CHAR_R, "Char_R.png"),
    CHAR_C(ObjectType.CHAR_C, "Char_C.png"),
    CHAR_O(ObjectType.CHAR_O, "Char_O.png"),
    CHAR_V(ObjectType.CHAR_V, "Char_V.png"),
    CHAR_S(ObjectType.CHAR_S, "Char_S.png"),

    CHAR_A(ObjectType.CHAR_A, "Char_A.png"),
    CHAR_W(ObjectType.CHAR_W, "Char_W.png"),
    CHAR_P(ObjectType.CHAR_P, "Char_P.png"),
    CHAR_N(ObjectType.CHAR_N, "Char_N.png");

    private static final String basePath = "src\\Game\\Resources\\Images\\";

    private final ObjectType type;
    private final ImageIcon spriteChunk;

    SpriteManager(ObjectType type, String filePath) {
        this.type = type;
        this.spriteChunk = new ImageIcon(basePath + filePath);
    }

    private ObjectType getType() { return type; }

    public Image getImage() {
        return this.spriteChunk.getImage();
    }

    public static Image getImage(ObjectType type) {
        for (SpriteManager elm : SpriteManager.values()) {
            if (type == elm.getType())
                return elm.getImage();
        }

        return null;
    }
}
