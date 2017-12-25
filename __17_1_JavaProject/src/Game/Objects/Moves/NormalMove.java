package Game.Objects.Moves;

import Game.Objects.AbstractCharObject;

import java.util.*;

public class NormalMove extends AbstractMoving {
    private static Byte[][] _movement = {
            {-1, 0}      // Left
            , {0, -1}    // Up
            , {1, 0}     // Right
            , {0, 1}};   // Down

    @Override
    public void move(AbstractCharObject inp) {
        Random _rand = new Random();
        int value = _rand.nextInt(4);
        inp.setPosition(_movement[value]);
    }
}
