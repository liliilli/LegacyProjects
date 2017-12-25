package Sound;

import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Vector;

import Custom.Pair;

public class SoundContainer implements InterfaceSound.Container {
    private ArrayList<Pair<Note, Integer>> mContainer = new ArrayList<>();

    SoundContainer() {
        mContainer.add(new Pair<>(Note.E4, 1000));
        mContainer.add(new Pair<>(Note.D4, 250));
        mContainer.add(new Pair<>(Note.C4, 500));
        mContainer.add(new Pair<>(Note.D4, 500));
        mContainer.add(new Pair<>(Note.E4, 500));
        mContainer.add(new Pair<>(Note.E4, 500));
        mContainer.add(new Pair<>(Note.E4, 500));
    }

    @Override
    public void readFile(FileInputStream file) {};

    @Override
    public void play(Vector<Pair<Note, Double>> container) {

    }

    @Override
    public ArrayList<Pair<Note, Integer>> getContainer() {
        return mContainer;
    }
}

