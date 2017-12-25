package Game.Objects.Moves;

import Game.Objects.AbstractCharObject;

public abstract class AbstractMoving implements GMoving {
    public enum _moveDirection {
        LEFT(0), UP(1), RIGHT(2), DOWN(3);

        private final int value;
        _moveDirection(int value) { this.value = value; }
        public int getValue() { return value; }
    }

    @Override
    public abstract void move(AbstractCharObject inp);

    protected _moveDirection dir = null;
    public void setDirection(_moveDirection direction) {
        dir = direction;
    }
    public _moveDirection getDirection() { return dir; }
}
