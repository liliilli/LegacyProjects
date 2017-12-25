package Game.Objects.Characters.Viliage;

import Custom.Switch;
import Game.Map.MapInfoContainer;
import Game.Objects.AbstractNPCObject;
import Game.Objects.Armors.ArmorType;
import Game.Objects.Moves.MoveType;
import Game.Objects.Weapons.WeaponType;
import Game.ReaderWriter;

import java.awt.event.KeyEvent;

import static Custom.GlobalSwitch.*;

public class SaveNPC_00 extends AbstractNPCObject {
    public SaveNPC_00(int x, int y, String name, MapInfoContainer c) {
        super(x, y, c);
        mName = name;
    }

    @Override
    public void create() {
        setStatus(255, 255, 255, 255, 255);
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
                switch (e.getKeyCode()) {
                    case KeyEvent.VK_Y:
                        if (ReaderWriter.save())
                            localSwitch.setSwitches("0001");
                        else
                            localSwitch.setSwitches("0010");

                        returnTalking();
                        break;
                    case KeyEvent.VK_N:
                        localSwitch.setSwitches("1111");
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
                            displayLog(this.getName() + ": "
                                    + "I save your journey data. Save?");
                            displayLog(" <Yes (Y) / No (N)>");
                            GOT_KINGS_MESSAGE.set(Switch.On);
                            setState(CommunicationState.SELECTION);
                            break;
                        case "0001":
                            displayLog("Your data is saved.");
                            localSwitch.setSwitches("1111");
                            returnTalking();
                            break;
                        case "0010":
                            displayLog("Something happened, so I couldn't " +
                                    "save your data. Try again next time.");
                            localSwitch.setSwitches("1111");
                            returnTalking();
                            break;
                        case "1111": // End conversation
                            displayLog("Bye.");
                            localSwitch.resetAll();
                            endCommunication();
                            break;
                    }
                }
            break;
        }
    }
}
