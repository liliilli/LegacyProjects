package Sound;

import Game.Resources.Sounds.SoundDead;
import Game.Resources.Sounds.SoundMonster;
import Game.Resources.Sounds.SoundSword;
import Game.Resources.Sounds.SoundWalk;

public enum SoundsList {
    WALK(new SoundWalk()),
    SWORD(new SoundSword()),
    MONSTER_ATTACK(new SoundMonster()),
    MONSTER_DEAD(new SoundDead()),
    PLAYER_DEAD(new SoundDead());

    private final AbstractSound sound;
    SoundsList(AbstractSound sound) {
        this.sound = sound;
    }

    public AbstractSound getSound() { return sound; }
}
