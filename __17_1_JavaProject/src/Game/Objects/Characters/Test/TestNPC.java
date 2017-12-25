package Game.Objects.Characters.Test;

import Custom.GlobalSwitch;
import Custom.Switch;
import Game.Map.MapInfoContainer;
import Game.Objects.AbstractNPCObject;
import Game.Objects.Armors.ArmorType;
import Game.Objects.Moves.MoveType;
import Game.Objects.Weapons.WeaponType;

import java.awt.event.KeyEvent;

public class TestNPC extends AbstractNPCObject {
    public TestNPC(int x, int y, String name, MapInfoContainer c) {
        super(x, y, c);
        mName = name;
    }

    @Override
    public void create() {
        setStatus(40, 15, 10, 8, 6);
        setWeapon(WeaponType.HAND);
        setArmor(ArmorType.IRON);
        setMoving(MoveType.NORMAL);
    }

    @Override
    protected final void doSelection(KeyEvent e) {
        switch (getState()) {
            case TALKING: {

            }   break;
            case SELECTION: {
                // 선택지 분기
                if (GlobalSwitch.HELLO_WORLD.get()) {
                    switch (e.getKeyCode()) {
                        case KeyEvent.VK_Y:
                            GlobalSwitch.HELLO_WORLD.set(Switch.Off);
                            returnTalking();
                            break;
                        case KeyEvent.VK_N:
                            returnTalking();
                            break;
                    }
                }
            }   break;
            default: break;
        }
    }

    @Override
    protected final void speakDialog() {
        switch (mMap._scene.getState()) {
            case NORMAL: {
                if (isRefreshed)
                    return;

                move(this);
                isRefreshed = true;
            }
            break;
            case FOCUS_LOGPANEL:
                if (!isTalked) {
                    isTalked = true;
                    // 대화 분기
                    if (!GlobalSwitch.HELLO_WORLD.get()) {
                        displayLog(
                                this.getName() + ": " + "Hello World.",
                                "Yes or No? <Y/N>" );
                        GlobalSwitch.HELLO_WORLD.set(Switch.On);
                        setState(CommunicationState.SELECTION);
                    }
                    else {
                        displayLog( this.getName() + ": " + "Bye World." );
                        GlobalSwitch.HELLO_WORLD.set(Switch.Off);
                        endCommunication();
                    }
            }
            break;
        }
    }
}
