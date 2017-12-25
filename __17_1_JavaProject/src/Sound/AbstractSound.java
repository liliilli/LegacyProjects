package Sound;

import Custom.Pair;

import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.Vector;

public class AbstractSound implements InterfaceSound.Container {
    protected ArrayList<Pair<Note, Integer>> mContainer = new ArrayList<>();

    @Override
    public void readFile(FileInputStream file) {};

    @Override
    public void play(Vector<Pair<Note, Double>> container) { }

    @Override
    public ArrayList<Pair<Note, Integer>> getContainer() {
        return mContainer;
    }
}

