package Game.Objects.Characters.Test;

import Game.ReaderWriter;
import Game.Map.MapInfoContainer;
import Game.Objects.AbstractNPCObject;
import Game.Objects.Armors.ArmorType;
import Game.Objects.Moves.MoveType;
import Game.Objects.Weapons.WeaponType;
import Screen.PanelHandler;

import java.awt.event.KeyEvent;

import static Screen.PanelHandler.PanelList.PLAY_LOG;

@Deprecated
public class TestSave extends AbstractNPCObject {
    public TestSave(int x, int y, String name, MapInfoContainer c) {
        super(x, y, c);
        mName = name;
    }

    @Override
    public void doSelection(KeyEvent e) {
        switch (getState()) {
            case TALKING: { }
            break;
            case SELECTION: {
                switch (e.getKeyCode()) {
                    case KeyEvent.VK_Y:
                        new ReaderWriter();
                        PanelHandler.handle(PLAY_LOG, "Save completed.");
                        returnTalking();
                        localSwitch.A = true;
                        // Call Save method
                        break;
                    case KeyEvent.VK_N:
                        PanelHandler.handle(PLAY_LOG, "Well, good bye.");
                        returnTalking();
                        localSwitch.A = true;
                        break;
                }
            }
            break;
            default: break;
        }
    }

    @Override
    public void create() {
        setStatus(40, 15, 10, 8, 6);
        setWeapon(WeaponType.HAND);
        setArmor(ArmorType.IRON);
        setMoving(MoveType.NONE);
    }

    @Override
    public void speakDialog() {
        switch (mMap._scene.getState()) {
            case NORMAL: {
                if (isRefreshed) return;

                move(this);
                isRefreshed = true;
            }
            break;
            case FOCUS_LOGPANEL:
                if (!isTalked) {
                    isTalked = true;
                    if (!localSwitch.A) {
                        PanelHandler.handle(PLAY_LOG,
                                this.getName() + ": I'm able to save your adventure.",
                                "Do you wanna save your log?"
                        );
                        PanelHandler.handle(PLAY_LOG, "<Y/N>?");
                        setState(CommunicationState.SELECTION);
                    }
                    else {
                        PanelHandler.handle(PLAY_LOG,
                                this.getName() + ": If you want to save again,",
                                "go back from viliage and tell me once more.");
                        endCommunication();
                    }
            }
            break;
        }
    }
}
