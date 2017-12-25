package Game.Map;

import Custom.Pair;
import Game.Objects.AbstractMapObject;
import Game.Objects.MapObjects.MapTransition;

public enum ObjectType {
    NONE(' '),
    BLOCK('.'),

    SEA('~'),
    GLASS('`'),
    VILLAGE('V'),
    MOUNTAIN('/'),
    DUNGEON('D'),
    FOREST('@'),

    SECRET('S'),
    WALL('W'),
    MOVEABLE('_'),

    TREASURE('T'),
    MOVE('E'),
    TRAP('+'),

    PLAYER('#'),
    NPC('O'),
    ENEMY('&'),

    CHAR_I('i'),
    CHAR_T('t'),
    CHAR_E('e'),
    CHAR_M('m'),

    CHAR_R('r'),
    CHAR_C('c'),
    CHAR_O('o'),
    CHAR_V('v'),
    CHAR_S('s'),

    CHAR_A('a'),
    CHAR_W('w'),
    CHAR_P('p'),
    CHAR_N('n');

    private final char value;
    ObjectType(char i) { value = i; }

    public final char value() { return value; }

    public static ObjectType newType(char input)
            throws ArrayIndexOutOfBoundsException {
        for (ObjectType elm : ObjectType.values()) {
            if (input == elm.value()) return elm;
        }

        throw new ArrayIndexOutOfBoundsException("Not found appropriate type");
    }

    public static AbstractMapObject create(ObjectType type,
                                           Pair<Integer, Integer> pos,
                                           MapInfoContainer container) {
        switch (type) {
            case MOVE: return new MapTransition(pos, container);
            case TRAP: return null;
            default: return null;
        }
    }
}
