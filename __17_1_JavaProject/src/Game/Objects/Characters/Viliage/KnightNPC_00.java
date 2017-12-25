package Game.Objects.Characters.Viliage;

import Custom.GlobalSwitch;
import Custom.Switch;
import Game.Map.MapInfoContainer;
import Game.Objects.AbstractNPCObject;
import Game.Objects.Armors.ArmorType;
import Game.Objects.Moves.MoveType;
import Game.Objects.Weapons.WeaponType;

import java.awt.event.KeyEvent;

import static Custom.GlobalSwitch.GOT_KINGS_MESSAGE;

public class KnightNPC_00 extends AbstractNPCObject {
    public KnightNPC_00(int x, int y, String name, MapInfoContainer c) {
        super(x, y, c);
        mName = name;
    }

    @Override
    public void create() {
        setStatus(60, 0, 15, 12, 10);
        setWeapon(WeaponType.IRON);
        setArmor(ArmorType.IRON);
        setMoving(MoveType.NONE);
    }

    @Override
    protected final void doSelection(KeyEvent e) {
        switch (getState()) {
            case TALKING: { } break;
            case SELECTION: { } break;
            default: break;
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
                            displayLog(getName() + ": " + "Hello.");
                            localSwitch.resetAll();
                            endCommunication();
                            break;
                    }
                }
            break;
        }
    }
}
