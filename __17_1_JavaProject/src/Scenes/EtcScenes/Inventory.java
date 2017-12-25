package Scenes.EtcScenes;

import Custom.Intent;
import Game.Game;
import Game.Objects.AbstractCharObject;
import Game.Objects.Characters.Controllable.Player;
import Scenes.AbstractScene;
import Scenes.SceneState;
import Screen.PanelHandler;

import java.awt.*;
import java.awt.event.KeyEvent;

import static Screen.PanelHandler.PanelList.PLAY_LOG;
import static Screen.PanelHandler.PanelList.PLAY_STATUS;
import static Screen.PanelHandler.PanelList.SYS_INVENTORY;

public class Inventory extends AbstractScene {
    public Inventory(String path) {
        super("src\\Game\\Resources\\Maps\\MapFF.map");
        addState(SceneState.NORMAL);
    }

    private Player player = null;

    @Override
    public void wrapInformationWithIntent() {

    }

    @Override
    public void wrapInformationWithIntent(String key, Object object) {
        Intent.getIntent().add(key, object);
    }

    @Override
    public void resolveInformationWithIntent(Intent intent) {
        Object player = Intent.getIntent().get("PlayerObject");
        if (player instanceof Player) {
            this.player = (Player)player;
        }
    }

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
        switch (getState()) {
            case NORMAL: // In selecting item list
                selectOneofItem(e);
                break;
            case A: // Item selected
                itemSelect(e);
                break;
        }
        return false;
    }

    private void selectOneofItem(KeyEvent e) {
        switch (e.getKeyCode()) {
            case KeyEvent.VK_ENTER:

                break;
            case KeyEvent.VK_Q:
            case KeyEvent.VK_ESCAPE:
                break;
            case KeyEvent.VK_UP:
                break;
            case KeyEvent.VK_DOWN:
                break;
        }
    }

    private void itemSelect(KeyEvent e) {

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
