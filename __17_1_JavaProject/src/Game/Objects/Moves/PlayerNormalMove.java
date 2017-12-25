package Game.Objects.Moves;

import Game.Game;
import Game.Objects.AbstractCharObject;
import Sound.SoundSystem;
import Sound.SoundsList;

public class PlayerNormalMove extends AbstractMoving {
    private static Byte[][] _movement = {
            {-1, 0}      // Left
            , {0, -1}    // Up
            , {1, 0}     // Right
            , {0, 1}};   // Down

    @Override
    public void move(AbstractCharObject inp) {
        inp.setPosition(_movement[dir.getValue()]);
        Game.getInstance().playSound(SoundsList.WALK);
    }
}
