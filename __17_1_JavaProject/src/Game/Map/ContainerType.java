package Game.Map;

public enum ContainerType {
    PLAYER(0),
    NPC(1),
    ENEMY(2);

    private final int sort;
    ContainerType(int i) { sort = i; }

    public final int value() { return sort; }
    public static ContainerType newType(int i)
    throws ArrayIndexOutOfBoundsException {
        switch (i) {
            case 0: return PLAYER;
            case 1: return NPC;
            case 2: return ENEMY;
            default: return null;
        }
    }
}
