package Game.Resources.Sounds;

import Custom.Pair;
import Sound.AbstractSound;
import Sound.InterfaceSound;
import Sound.Note;

import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.Vector;

public class SoundWalk extends AbstractSound {
    public SoundWalk() {
        mContainer.add(new Pair<>(Note.E4, 100));
    }
}

