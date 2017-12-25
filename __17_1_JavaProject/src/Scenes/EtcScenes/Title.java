package Scenes.EtcScenes;

import Custom.GlobalSwitch;
import Custom.Intent;
import Custom.Pair;
import Game.Game;
import Game.Map.MapListType;
import Game.Objects.Armors.ArmorType;
import Game.Objects.CharacterStatus;
import Game.Objects.Weapons.WeaponType;
import Game.ReaderWriter;
import Scenes.AbstractScene;
import Scenes.SceneState;
import Screen.PanelHandler;
import Screen.ScreenFrame;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.io.IOException;
import java.util.*;
import java.util.List;

import static Game.Map.MapListType.WORLD_FIELD;
import static Screen.PanelHandler.PanelList.SYS_TITLE;

public class Title extends AbstractScene {
    public Title(String path) throws IOException, FontFormatException {
        super(path);
        addState(SceneState.NORMAL);
    }

    private CharacterStatus playerStatus;
    private String playerName = "";

    private List<Object> loadedInformation = new ArrayList<>();

    @Override
    public void activate() {
        PanelHandler.getInstance().activatePane(SYS_TITLE);
        ScreenFrame.getInstance().refreshAll();

        System.out.println("Hello world");
        PanelHandler.handle(SYS_TITLE, true, false, false, false);
    }

    @Override
    public boolean input(KeyEvent e) {
        switch (sceneState.peek()) {
            default: throw new RuntimeException("Does not found scene state");
            case NORMAL: // 타이틀
                inputNormal(e);
                break;
            case B: // 스탯 설정 시
                inputSettingStatus(e);
                break;
            case A: // 파일 로드 시
                inputLoadSituation(e);
            case C: // 로딩 시 Nothing to do
                break;
        }

        return true;
    }

    private void inputNormal(KeyEvent e) {
        switch (e.getKeyCode()) {
            case KeyEvent.VK_Q: // 나가기
            case KeyEvent.VK_ESCAPE:
                addState(SceneState.SOMETHING_ELSE);
                mSuper.endLoopSequence();
                Game.getInstance().exit();
                break;
            case KeyEvent.VK_L: // 로드 키를 눌렀을 때
                addState(SceneState.A);
                loadedInformation = ReaderWriter.load();
                CharacterStatus status = (CharacterStatus)loadedInformation.get(0);
                PanelHandler.handle(SYS_TITLE,
                        status.getLevel(),
                        status.getHeartPoint(),
                        status.getMagicPoint(),
                        status.getAtkPoint(),
                        status.getDefPoint(),
                        status.getDexPoint());
                PanelHandler.handle(SYS_TITLE, false, false, false, true);
                break;
            case KeyEvent.VK_N: // 뉴 게임 키를 눌렀을 때
                addState(SceneState.B);
                setPlayerStatus();
                PanelHandler.handle(SYS_TITLE,
                        playerStatus.getHeartPoint(),
                        playerStatus.getMagicPoint(),
                        playerStatus.getAtkPoint(),
                        playerStatus.getDefPoint(),
                        playerStatus.getDexPoint());
                PanelHandler.handle(SYS_TITLE, false, false, true, false);
                break;
        }
    }

    private void inputSettingStatus(KeyEvent e) {
        if (!localSwitches.A) { // 만약 스테이터스 세팅일 경우
            switch (e.getKeyCode()) {
                case KeyEvent.VK_B: // 메인 화면으로 되돌아감.
                case KeyEvent.VK_ESCAPE:
                    popState();
                    PanelHandler.handle(SYS_TITLE, true, false, false, false);
                    break;
                case KeyEvent.VK_R: // 다시 한번 스탯을 정할 수 있도록 함.
                    setPlayerStatus();
                    PanelHandler.handle(SYS_TITLE,
                            playerStatus.getHeartPoint(),
                            playerStatus.getMagicPoint(),
                            playerStatus.getAtkPoint(),
                            playerStatus.getDefPoint(),
                            playerStatus.getDexPoint());
                    break;
                case KeyEvent.VK_Y:
                case KeyEvent.VK_ENTER: // 이름 설정으로 넘어감
                    localSwitches.A = true; // 스위치 설정
                    PanelHandler.handle(SYS_TITLE, "");
                    PanelHandler.handle(SYS_TITLE, false, false, true, true);
                    break;
            }
        } else if (!localSwitches.B) { // 만약 이름 설정일 경우
            switch (e.getKeyCode()) {
                case KeyEvent.VK_ENTER:
                    localSwitches.B = true;
                    PanelHandler.handle(SYS_TITLE,
                            playerName,
                            playerStatus.getHeartPoint(),
                            playerStatus.getMagicPoint(),
                            playerStatus.getAtkPoint(),
                            playerStatus.getDefPoint(),
                            playerStatus.getDexPoint());
                    PanelHandler.handle(SYS_TITLE, false, true, false, false);
                    break;
                case KeyEvent.VK_ESCAPE:
                    localSwitches.A = false;
                    PanelHandler.handle(SYS_TITLE,
                            playerStatus.getHeartPoint(),
                            playerStatus.getMagicPoint(),
                            playerStatus.getAtkPoint(),
                            playerStatus.getDefPoint(),
                            playerStatus.getDexPoint());
                    PanelHandler.handle(SYS_TITLE, false, false, true, false);
                    break;
                default: {
                    if (Character.isAlphabetic(e.getKeyChar())) {
                        playerName += e.getKeyChar();
                    } else if (e.getKeyCode() == KeyEvent.VK_BACK_SPACE) {
                        playerName =
                                playerName.substring(0, playerName.length()-1);
                    }

                    PanelHandler.handle(SYS_TITLE, playerName);
                }   break;
            }
        } else { // 스테이터스 결정에서 최종 씬일 경우.
            switch (e.getKeyCode()) {
                case KeyEvent.VK_ENTER:
                    startGame();
                    break;
                case KeyEvent.VK_ESCAPE:
                case KeyEvent.VK_B:
                case KeyEvent.VK_Q:
                    localSwitches.B = false;
                    PanelHandler.handle(SYS_TITLE, playerName);
                    PanelHandler.handle(SYS_TITLE, false, false, true, true);
                    break;
            }
        }
    }

    private void startGame() {
        System.out.println(this.getClass().getName() + " : Game start...");
        addState(SceneState.SCENE_MOVE);
        // 컴파일러에서 에러가 나더라도 기본적으로는 타입 추론이 가능함.
        Game.getInstance().changeScene(WORLD_FIELD, new Pair<>(11, 6));
        popState();
    }

    private void setPlayerStatus() {
        if (playerStatus == null) {
            playerStatus = CharacterStatus.createInstance();
            playerStatus.setArmor(ArmorType.NUDE);
            playerStatus.setWeapon(WeaponType.HAND);
        }

        Random engine = new Random();
        int health = engine.nextInt(10) + 30;
        int magica = engine.nextInt(10) + 10;
        int attack = engine.nextInt(5) + 5;
        int defence = engine.nextInt(5) + 5;
        int dexity = engine.nextInt(5) + 3;
        if (engine.nextInt(40) <= 1) { // Special Case
            health += 10;
            magica += 10;
            attack += 10;
            defence += 10;
            dexity += 10;
        }

        playerStatus.setHeartPoint(health);
        playerStatus.setMagicaPoint(magica);
        playerStatus.setAtkPoint(attack);
        playerStatus.setDefPoint(defence);
        playerStatus.setDexPoint(dexity);
    }

    private void inputLoadSituation(KeyEvent e) {
        switch (e.getKeyCode()) {
            case KeyEvent.VK_ESCAPE:
            case KeyEvent.VK_Q:
            case KeyEvent.VK_B:
                popState();
                PanelHandler.handle(SYS_TITLE, true, false, false, false);
                break;
            case KeyEvent.VK_ENTER:
                startGameWithLoadedFile();
                break;
        }
    }

    private void startGameWithLoadedFile() {
        System.out.println(this.getClass().getName() + " : Game start...");
        System.out.println(this.getClass().getName() + " : With Loaded file");
        addState(SceneState.SCENE_MOVE);

        MapListType type = MapListType.getMapType((int)loadedInformation.get(2));
        GlobalSwitch.setSwitches((GlobalSwitch[])loadedInformation.get(3));
        Game.getInstance().changeScene(type,
                (Pair)loadedInformation.get(1),
                (CharacterStatus)loadedInformation.get(0));
        popState();
    }

    @Override
    public boolean refresh() { return false; }

    @Override
    public boolean draw() {
        PanelHandler.getInstance().getPanel(SYS_TITLE).revalidate();
        PanelHandler.getInstance().getPanel(SYS_TITLE).repaint();
        return false;
    }

    @Override
    public void deactivate() {
        PanelHandler.getInstance().deactivatePane(SYS_TITLE);
    }

    @Override
    public void wrapInformationWithIntent() {
        Intent.getIntent().add("PlayerInformation", playerStatus);
    }

    @Override
    public void wrapInformationWithIntent(String key, Object object) {
        Intent.getIntent().add(key, object);
    }

    @Override
    public void resolveInformationWithIntent(Intent intent) {

    }
}
