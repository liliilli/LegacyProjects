package Scenes;

import Game.Game;
import Game.Map.ContainerType;
import Game.Map.MapLoader;
import Game.Map.MapInfoContainer;
import Game.Objects.AbstractCharObject;

import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.Stack;

public abstract class AbstractScene implements InterfaceScene {
    protected Game mSuper = null;
    protected MapLoader mapper = new MapLoader();
    protected MapInfoContainer mContainer = new MapInfoContainer(this);
    protected String mapPath = null;
    protected Stack<SceneState> sceneState = new Stack<>();
    protected AbstractCharObject focusedObj = null;
    protected LocalSwitches localSwitches = new LocalSwitches();

    public AbstractScene(String path) {
        mapPath = path;
        mSuper = Game.getInstance();
        mapper.LoadFile(mapPath, mContainer);
    }

    @Override
    public abstract void activate();

    @Override
    public abstract void deactivate();

    @Override
    public abstract boolean input(KeyEvent e);

    @Override
    public abstract boolean refresh();

    @Override
    public abstract boolean draw();

    public final void addState(SceneState state) { sceneState.add(state); }
    public final void popState() {
        if (sceneState.size() > 0)
            sceneState.pop();
    }
    public final void endCommunication() {
        popState();
        setFocus(mContainer.getPlayerObject());
    }

    public final void setFocus(AbstractCharObject charObject) {
        focusedObj = charObject;
    }
    public final SceneState getState() { return sceneState.peek(); }

    public final MapInfoContainer getMapContainer() { return mContainer; }
    public final ArrayList<AbstractCharObject> getCharacterContainer(
            ContainerType type) {
        return mContainer.getCharacterContainer(type);
    }

    protected final class LocalSwitches {
        public boolean A = false;
        public boolean B = false;
        public boolean C = false;
        public boolean D = false;
    }
}
