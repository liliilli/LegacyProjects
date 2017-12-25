package Game.Resources.Sounds;

import Custom.Pair;
import Sound.AbstractSound;
import Sound.Note;

public class SoundSword extends AbstractSound {
    public SoundSword() {
        mContainer.add(new Pair<>(Note.C5, 100));
    }
}

