package Game.Resources.Sounds;

import Custom.Pair;
import Sound.AbstractSound;
import Sound.Note;

public class SoundMonster extends AbstractSound {
    public SoundMonster() {
        mContainer.add(new Pair<>(Note.D4, 100));
    }
}

