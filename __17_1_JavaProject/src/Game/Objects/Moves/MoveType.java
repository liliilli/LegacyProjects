package Game.Objects.Moves;

import Game.Objects.Armors.ArmorType;

public enum MoveType {
    NONE,
    NORMAL,
    FOLLOWING,
    PLAYER_NORMAL;

    public static AbstractMoving newType(MoveType type) {
        switch (type) {
            case NONE: return new NoneMove();
            case NORMAL: return new NormalMove();
            case FOLLOWING: return new FollowingMove();
            case PLAYER_NORMAL: return new PlayerNormalMove();
            default: return null;
        }
    }
}
