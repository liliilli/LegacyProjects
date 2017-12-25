package Game.Resources.Sounds;

import Custom.Pair;
import Sound.AbstractSound;
import Sound.Note;

public class SoundDead extends AbstractSound {
    public SoundDead() {
        mContainer.add(new Pair<>(Note.C4, 500));
    }
}

