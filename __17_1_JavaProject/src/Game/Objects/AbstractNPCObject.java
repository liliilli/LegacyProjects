package Game.Objects;

import Game.Map.MapInfoContainer;
import Scenes.SceneState;

import java.awt.event.KeyEvent;

public abstract class AbstractNPCObject extends AbstractCharObject {
    private CommunicationState communicationState = CommunicationState.TALKING;
    protected boolean isTalked = false;

    public enum CommunicationState {
        TALKING,
        SELECTION;
    }

    public AbstractNPCObject(int x, int y, MapInfoContainer c) {
        super(x, y, c);
    }

    public abstract void create();
    protected abstract void speakDialog();
    protected abstract void doSelection(KeyEvent e);

    @Override
    public final void input(KeyEvent e) { doSelection(e); }

    @Override
    public final void refresh() { speakDialog(); }

    // Move 도 Strategy Pattern 방식으로 해야할 듯.
    @Override
    public void move(AbstractCharObject inp) { move.move(inp); }

    @Override
    public void destroy() {};

    protected final CommunicationState getState() {
        return communicationState;
    }

    protected final void setState(CommunicationState input) {
        communicationState = input;
    }

    protected final void returnTalking() {
        isTalked = false;
        setState(CommunicationState.TALKING);
    }

    public final void communicate() {
        mMap._scene.addState(SceneState.FOCUS_LOGPANEL);
        mMap._scene.setFocus(this);
    }

    protected final void endCommunication() {
        isTalked = false;
        mMap._scene.endCommunication();
    }
}
