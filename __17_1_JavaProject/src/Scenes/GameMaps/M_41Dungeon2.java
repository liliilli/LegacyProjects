package Scenes.GameMaps;

import Custom.Intent;
import Custom.Pair;
import Game.Game;
import Game.Map.CharacterType;
import Game.Map.ContainerType;
import Game.Objects.AbstractCharObject;
import Game.Objects.CharacterStatus;
import Scenes.AbstractScene;
import Scenes.SceneState;
import Screen.PanelHandler;
import Screen.ScreenFrame;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.io.IOException;
import java.util.ArrayList;

import static Screen.PanelHandler.PanelList.*;

public class M_41Dungeon2 extends AbstractScene {
    private boolean flag = false;

    public M_41Dungeon2() throws IOException, FontFormatException {
        super("src\\Game\\Resources\\Maps\\MapF0.map");
        addState(SceneState.NORMAL);

        assert mContainer.getPlayerObject() != null;
        focusedObj = mContainer.getPlayerObject();
    }

    @Override
    public void activate() {
        PanelHandler.getInstance().activatePane(PLAY_SCR);
        PanelHandler.getInstance().activatePane(PLAY_LOG);
        PanelHandler.getInstance().activatePane(PLAY_STATUS);
        PanelHandler.getInstance().getPanel(PLAY_SCR).setRelease();
        PanelHandler.getInstance().getPanel(PLAY_LOG).setRelease();
        PanelHandler.getInstance().getPanel(PLAY_STATUS).setRelease();
        ScreenFrame.getInstance().refreshAll();

        PanelHandler.handle(PLAY_LOG, "Enter " + mContainer.getMapName() + "...");
    }

    @Override
    public boolean input(KeyEvent e) {
        switch (sceneState.peek()) {
            default: throw new RuntimeException("Does not find scene state");
            case NORMAL:
                inputNormal(e); break;
            case FOCUS_LOGPANEL:
                inputToLogPanel(e); break;
            case FOCUS_MESSAGE:
                break;
            case SOMETHING_ELSE:
                break;
        }

        return true;
    }

    private void inputNormal(KeyEvent e) {
        switch (e.getKeyCode()) {
            case KeyEvent.VK_Q:
                addState(SceneState.FOCUS_MESSAGE);
                mSuper.endLoopSequence();
                Game.getInstance().exit();
                break;
        }

        // 플레이어 캐릭터가 있는 지 확인한다.
        if (!(mContainer.getPlayerObject() == null)) {
            focusedObj.input(e);
            flag = true;
        }
    }

    private void inputToLogPanel(KeyEvent e) {
        focusedObj.input(e);
    }

    @Override
    public synchronized boolean refresh() {
        switch (sceneState.peek()) {
            case NORMAL:
                if (mContainer.getPlayerObject() != null)
                    mContainer.getPlayerObject().refresh();

                ArrayList<AbstractCharObject> _temp =
                        getCharacterContainer(ContainerType.ENEMY);
                ArrayList<AbstractCharObject> _npcs =
                            getCharacterContainer(ContainerType.NPC);

                for (AbstractCharObject elm : _npcs) { elm.refresh(); }
                for (AbstractCharObject elm : _temp) { elm.refresh(); }
                break;
            case FOCUS_LOGPANEL:
                focusedObj.refresh();
                break;
            case FOCUS_MESSAGE:
                break;
            case SCENE_MOVE:
                break;
            case SOMETHING_ELSE:
                break;
        }

        return false;
    }

    @Override
    public boolean draw() {
        if (flag) {
            // Test Routine
            int x = 0, y = 0;
            boolean no = false;
            ArrayList<AbstractCharObject> _temp =
                    getCharacterContainer(ContainerType.ENEMY);
            ArrayList<AbstractCharObject> _npcs =
                    getCharacterContainer(ContainerType.NPC);

            for (ArrayList<Character> row : mContainer.getMap()) {
                for (Character character : row) {
                    if (mContainer.getPlayerObject().getX() == x
                            && mContainer.getPlayerObject().getY() == y) {
                        System.out.print('#');
                        no = true;
                    }

                    if (_temp.size() != 0) {
                        for (AbstractCharObject elm : _temp) {
                            if (elm.getX() == x && elm.getY() == y) {
                                System.out.print('&');
                                no = true;
                            }
                        }
                    }

                    if (_npcs.size() != 0) {
                        for (AbstractCharObject elm : _npcs) {
                            if (elm.getX() == x && elm.getY() == y) {
                                System.out.print('O');
                                no = true;
                            }
                        }
                    }

                    if (!no)
                        System.out.print(character);

                    ++x;
                    no = false;
                }
                System.out.println();
                ++y;
                x = 0;
            }

            flag = false;
        }

        PanelHandler.getInstance().getPanel(PLAY_SCR).revalidate();
        PanelHandler.getInstance().getPanel(PLAY_SCR).repaint();
        return false;
    }

    @Override
    public void deactivate() {
        PanelHandler.getInstance().deactivatePane(PLAY_SCR);
        PanelHandler.getInstance().deactivatePane(PLAY_LOG);
        PanelHandler.getInstance().deactivatePane(PLAY_STATUS);
    }

    @Override
    public void wrapInformationWithIntent() {
        Intent.newIntent().
                add("PlayerInformation",
                        getMapContainer().getPlayerObject().getStatus());
        Intent.getIntent().
                add("PlayerPosition",
                        getMapContainer().getPlayerObject().getPosition());
    }

    @Override
    public void wrapInformationWithIntent(String key, Object object) {
        Intent.getIntent().
                add(key, object);
    }

    @Override
    public void resolveInformationWithIntent(Intent intent) {
        if ((Boolean)intent.get("IsPlayerExist")) {
            Pair<Integer, Integer> playerPos =
                    ((Pair<Integer, Integer>) intent.get("AfterPlayerPosition"));
            CharacterStatus playerStatus =
                    ((CharacterStatus) intent.get("PlayerInformation"));

            getCharacterContainer(ContainerType.PLAYER).add(
                    CharacterType.create(CharacterType.TEST_NAME,
                            playerPos, "", mContainer));
            mContainer.getPlayerObject().setStatus(playerStatus);
            focusedObj = mContainer.getPlayerObject();
        }
    }
}
