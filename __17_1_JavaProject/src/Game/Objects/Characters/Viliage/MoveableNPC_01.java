package Game.Objects.Characters.Viliage;

import Game.Map.MapInfoContainer;
import Game.Objects.AbstractNPCObject;
import Game.Objects.Armors.ArmorType;
import Game.Objects.Moves.MoveType;
import Game.Objects.Weapons.WeaponType;

import java.awt.event.KeyEvent;

public class MoveableNPC_01 extends AbstractNPCObject {
    public MoveableNPC_01(int x, int y, String name, MapInfoContainer c) {
        super(x, y, c);
        mName = name;
    }

    @Override
    public void create() {
        setStatus(40, 15, 10, 8, 6);
        setWeapon(WeaponType.HAND);
        setArmor(ArmorType.NUDE);
        setMoving(MoveType.NORMAL);
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
                    displayLog(
                            this.getName() + ": " + "Welcome to " +
                                    getMap().getMapName());
                    endCommunication();
                }
            break;
        }
    }
}
