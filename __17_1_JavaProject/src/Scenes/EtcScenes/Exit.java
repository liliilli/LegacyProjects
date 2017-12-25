package Scenes.EtcScenes;

import Custom.Intent;
import Game.Objects.Characters.Controllable.Player;
import Scenes.AbstractScene;
import Scenes.SceneState;
import Screen.PanelHandler;

import java.awt.event.KeyEvent;

import static Screen.PanelHandler.PanelList.*;

public class Exit extends AbstractScene {
    public Exit(String path) {
        super("src\\Game\\Resources\\Maps\\MapFF.map");
        addState(SceneState.NORMAL);
    }

    @Override
    public void wrapInformationWithIntent() {

    }

    @Override
    public void wrapInformationWithIntent(String key, Object object) {}

    @Override
    public void resolveInformationWithIntent(Intent intent) {}

    @Override
    public void activate() {
        PanelHandler.getInstance().activatePane(SYS_INVENTORY);
        PanelHandler.getInstance().activatePane(PLAY_LOG);
        PanelHandler.getInstance().activatePane(PLAY_STATUS);
    }

    @Override
    public void deactivate() {
        PanelHandler.getInstance().deactivatePane(SYS_INVENTORY);
        PanelHandler.getInstance().deactivatePane(PLAY_LOG);
        PanelHandler.getInstance().deactivatePane(PLAY_STATUS);
    }

    @Override
    public boolean input(KeyEvent e) {

        return false;
    }

    @Override
    public boolean refresh() {
        return false;
    }

    @Override
    public boolean draw() {
        PanelHandler.getInstance().getPanel(SYS_INVENTORY).revalidate();
        PanelHandler.getInstance().getPanel(SYS_INVENTORY).repaint();
        return false;
    }
}
