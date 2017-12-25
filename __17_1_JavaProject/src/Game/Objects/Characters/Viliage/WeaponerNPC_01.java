package Game.Objects.Characters.Viliage;

import Custom.GlobalSwitch;
import Custom.Switch;
import Game.Game;
import Game.Map.MapInfoContainer;
import Game.Objects.AbstractNPCObject;
import Game.Objects.Armors.ArmorType;
import Game.Objects.Moves.MoveType;
import Game.Objects.Weapons.WeaponType;
import com.sun.org.apache.bcel.internal.generic.SWITCH;
import jdk.nashorn.internal.objects.Global;

import java.awt.event.KeyEvent;

public class WeaponerNPC_01 extends AbstractNPCObject {
    public WeaponerNPC_01(int x, int y, String name, MapInfoContainer c) {
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
                    case KeyEvent.VK_B:
                        if (GlobalSwitch.BOUGHT_IRON_SWORD.get()) {
                            localSwitch.setSwitches("1110");
                        } else {
                            localSwitch.setSwitches("1000");
                        }
                        returnTalking();
                        break;
                    case KeyEvent.VK_R:
                        if (GlobalSwitch.REQUEST_HOPGOBLIN_INPROGRESS.get()) {
                            if (GlobalSwitch.REQUEST_HOPGOBLIN_COMPLETE.get()) {
                                localSwitch.setSwitches("0011");
                            } else {
                                localSwitch.setSwitches("0111");
                            }
                        } else {
                            localSwitch.setSwitches("0100");
                        }
                        returnTalking();
                        break;
                    case KeyEvent.VK_Q:
                        localSwitch.setSwitches("1111");
                        returnTalking();
                        break;
                }
                break;
            case "1000":
                switch (e.getKeyCode()) {
                    case KeyEvent.VK_B:
                        // Dangerous Way *******************************
                        final int coin = Game.getInstance().recentScene().
                                getMapContainer().getPlayerObject().
                                getStatus().getCoin();
                        if (coin > 500) {
                            Game.getInstance().recentScene().
                                    getMapContainer().getPlayerObject().
                                    getStatus().decreaseCoin(500);
                            Game.getInstance().recentScene().
                                    getMapContainer().getPlayerObject().
                                    getStatus().setWeapon(WeaponType.IRON);
                            GlobalSwitch.BOUGHT_IRON_SWORD.set(Switch.On);
                            localSwitch.setSwitches("0001");
                        } else
                            localSwitch.setSwitches("1100");
                        returnTalking();
                        break;
                    case KeyEvent.VK_N:
                        localSwitch.setSwitches("0001");
                        returnTalking();
                        break;
                }
                break;
            case "0100":
                switch (e.getKeyCode()) {
                    case KeyEvent.VK_Y:
                        GlobalSwitch.REQUEST_HOPGOBLIN_INPROGRESS.set(Switch.On);
                        localSwitch.setSwitches("0111");
                        returnTalking();
                        break;
                    case KeyEvent.VK_N:
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
                        case "0000":
                            displayLog(
                                    this.getName() + ": " + "Welcome to My armory.");
                            displayLog("What can I do for you?");
                            displayLog(" <Buy Weapon (B) / Request (R) / Quit (Q)>");
                            setState(CommunicationState.SELECTION);
                            break;
                        case "1000":
                            displayLog(
                                    "I have Iron sword for you, It's 500 coin.");
                            displayLog("Do you wanna buy it?");
                            displayLog(" <Buy (B) / No, Thanks (N)>");
                            setState(CommunicationState.SELECTION);
                            break;
                        case "1100":
                            displayLog("You may have not enough money.");
                            localSwitch.setSwitches("0001");
                            returnTalking();
                            break;
                        case "1110":
                            displayLog("You have alerady bought my iron sword.");
                            localSwitch.setSwitches("0001");
                            returnTalking();
                            break;
                        case "0100":
                            displayLog("Could you please get 5 leathers of Hopgoblin?",
                                    "I need it for making better sword's grip.");
                            displayLog("If you give me these, I'll give you 4 point of Attack.");
                            displayLog(" <Yes (Y) / No (N)>");
                            setState(CommunicationState.SELECTION);
                            break;
                        case "0010":
                            displayLog("Thanks! I give you 4 point of Attack.",
                                    "It will be great help to you to defeat Satan.");
                            GlobalSwitch.REQUEST_HOPGOBLIN_COMPLETE.set(Switch.On);
                            localSwitch.setSwitches("0001");
                            returnTalking();
                            break;
                        case "0111":
                            displayLog("Get 5 leathers of Hopgoblin me as soon.");
                            localSwitch.setSwitches("0001");
                            returnTalking();
                            break;
                        case "0011":
                            displayLog("There is no request for you.");
                            localSwitch.setSwitches("0001");
                            returnTalking();
                            break;
                        case "0001":
                            displayLog("Anything else?");
                            displayLog(" <Buy Weapon (B) / Request (R) / Quit (Q)>");
                            setState(CommunicationState.SELECTION);
                            break;
                        case "1111":
                            displayLog("Buy, Solider.");
                            localSwitch.resetAll();
                            endCommunication();
                            break;
                    }
                }
            break;
        }
    }
}
