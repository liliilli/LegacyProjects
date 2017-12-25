package Game.Objects.Characters.Viliage;

import Custom.GlobalSwitch;
import Custom.Switch;
import Game.Game;
import Game.Map.MapInfoContainer;
import Game.Objects.AbstractNPCObject;
import Game.Objects.Armors.ArmorType;
import Game.Objects.Moves.MoveType;
import Game.Objects.Weapons.WeaponType;
import com.sun.xml.internal.bind.v2.TODO;

import java.awt.event.KeyEvent;

import static Custom.GlobalSwitch.GOT_KINGS_MESSAGE;
import static Custom.GlobalSwitch.KILLED_SATAN;
import static Custom.GlobalSwitch.SAVED_PRINCESS;

public class KingNPC_00 extends AbstractNPCObject {
    public KingNPC_00(int x, int y, String name, MapInfoContainer c) {
        super(x, y, c);
        mName = name;
    }

    @Override
    public void create() {
        setStatus(30, 50, 10, 8, 13);
        setWeapon(WeaponType.IRON);
        setArmor(ArmorType.IRON);
        setMoving(MoveType.NONE);
    }

    @Override
    protected final void doSelection(KeyEvent e) {
        switch (getState()) {
            case TALKING: { } break;
            case SELECTION: {
                selectSelection(e);
            } break;
            default: break;
        }
    }

    public void selectSelection(KeyEvent e) {
        switch (localSwitch.getSwitchStatus()) {
            case "0000":
            case "0001":
                switch (e.getKeyCode()) {
                    case KeyEvent.VK_C:
                        localSwitch.setSwitches("0010");
                        returnTalking();
                        break;
                    case KeyEvent.VK_Q:
                        localSwitch.setSwitches("1111");
                        returnTalking();
                        break;
                }
                break;
            case "0010":
                switch (e.getKeyCode()) {
                    case KeyEvent.VK_S:
                        // TODO
                        break;
                    case KeyEvent.VK_W:
                        break;
                    case KeyEvent.VK_Q:
                        localSwitch.setSwitches("0001");
                        returnTalking();
                        break;
                }
                break;
        }
    }

    @Override
    protected final void speakDialog() {
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

                    switch (localSwitch.getSwitchStatus()) {
                        default: assert false;
                        case "0000":
                            if (!GOT_KINGS_MESSAGE.get()) {
                                displayLog(this.getName() + ": "
                                        + "My daughter, Princess is kidnapped by Satan.",
                                        "And he is trying to destroy the world.",
                                        "Kill satan, and rescue my daughter.");
                                GOT_KINGS_MESSAGE.set(Switch.On);
                                endCommunication();
                            } else {
                                callSwitch0000Dialog();
                                setState(CommunicationState.SELECTION);
                            }
                            break;
                        case "0001":
                            displayLog("Else?");
                            displayLog(" <Communicate (C) / Quit (Q)>");
                            setState(CommunicationState.SELECTION);
                            break;
                        case "0010":
                            displayLog("What?");
                            displayLog(" <Who is Satan (S) / This world (W) / Quit (Q)");
                            setState(CommunicationState.SELECTION);
                            break;
                        case "1111": // End conversation
                            displayLog("Go, Brave man.");
                            localSwitch.resetAll();
                            endCommunication();
                            break;
                    }
                }
            break;
        }
    }

    private void callSwitch0000Dialog() {
        if (SAVED_PRINCESS.get() && KILLED_SATAN.get()) {
            displayLog(this.getName() + ": "
                    + "I heard you defeat satan, and also rescued princess.");
            displayLog(" <Communicate (C) / End game (E) / Quit (Q)>");
        }
        else if (SAVED_PRINCESS.get()) {
            displayLog(this.getName() + ": "
                    + "I heard you saved my princess. And?");
            displayLog(" <Communicate (C) / Princess (P) / Quit (Q)>");
        }
        else if (KILLED_SATAN.get()) {
            displayLog(this.getName() + ": "
                    + "How do you do.");
            displayLog(" <Communicate (C) / Satan (S) / Quit (Q)>");
        }
        else {
            displayLog(this.getName() + ": "
                    + "How do you do.");
            displayLog(" <Communicate (C) / Quit (Q)>");
        }
    }
}
