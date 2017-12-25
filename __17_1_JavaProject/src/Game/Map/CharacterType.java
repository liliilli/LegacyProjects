package Game.Map;

import Custom.Pair;
import Game.Objects.AbstractCharObject;
import Game.Objects.Characters.Controllable.Player;
import Game.Objects.Characters.Test.TestCharacter;
import Game.Objects.Characters.Test.TestEnemy;
import Game.Objects.Characters.Test.TestNPC;
import Game.Objects.Characters.Test.TestSave;
import Game.Objects.Characters.Viliage.*;

public enum CharacterType {
    PLAYER(0x00, ContainerType.PLAYER),
    SAVER(0x01, ContainerType.NPC),

    VILLAGE_NPC_01(0x40, ContainerType.NPC) ,
    WEAPONER_NPC_01(0x41, ContainerType.NPC) ,
    KING_NPC_00(0x42, ContainerType.NPC),
    KNIGHT_NPC_00(0x43, ContainerType.NPC),

    TEST_NAME(0xF0, ContainerType.PLAYER),
    TEST_ENEMY(0xF1, ContainerType.ENEMY),
    TEST_NPC(0xF2, ContainerType.NPC),
    TEST_SAVER(0xF3, ContainerType.NPC);

    private final int value;
    private final ContainerType sort;
    CharacterType(int i, ContainerType type) {
        value = i;
        sort = type;
    }

    public final int value() { return value; }
    public final int typeVal() { return sort.value(); }
    public final ContainerType sort() { return sort; }

    public static CharacterType newType(int i)
            throws ArrayIndexOutOfBoundsException {
        for (CharacterType elm : CharacterType.values()) {
            if (i == elm.value()) return elm;
        }

        throw new ArrayIndexOutOfBoundsException("Not found appropriate type");
    }

    public static AbstractCharObject create(CharacterType type,
                                            Pair<Integer, Integer> pos,
                                            String name,
                                            MapInfoContainer cont) {
        switch (type) {
            case PLAYER:
                return new Player(pos.getFirst(), pos.getSecond(), name, cont);
            case SAVER:
                return new SaveNPC_00(pos.getFirst(), pos.getSecond(), name,
                        cont);
            case VILLAGE_NPC_01:
                return new MoveableNPC_01(pos.getFirst(), pos.getSecond(), name, cont);
            case WEAPONER_NPC_01:
                return new WeaponerNPC_01(pos.getFirst(), pos.getSecond(), name, cont);
            case KING_NPC_00:
                return new KingNPC_00(pos.getFirst(), pos.getSecond(), name, cont);
            case KNIGHT_NPC_00:
                return new KnightNPC_00(pos.getFirst(), pos.getSecond(), name, cont);
            case TEST_NAME:
                return new TestCharacter(pos.getFirst(), pos.getSecond(), name, cont);
            case TEST_ENEMY:
                return new TestEnemy(pos.getFirst(), pos.getSecond(), name, cont);
            case TEST_SAVER:
                return new TestSave(pos.getFirst(), pos.getSecond(), name, cont);
            case TEST_NPC:
                return new TestNPC(pos.getFirst(), pos.getSecond(), name, cont);
            default: assert false;
        }

        return null;
    }
}
