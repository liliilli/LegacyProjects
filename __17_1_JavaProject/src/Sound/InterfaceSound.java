package Sound;

import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.Vector;
import Custom.Pair;

public class InterfaceSound {
    interface Instrument {
        int SAMPLE_RATE = 44000;
        byte[] createWave(double freq, int ms);
    }

    interface System {
        void play(AbstractSound sound);
    }

    interface Container {
        void readFile(FileInputStream file);
        void play(Vector<Pair<Note, Double>> container);

        ArrayList<Pair<Note, Integer>> getContainer();
    }
}
