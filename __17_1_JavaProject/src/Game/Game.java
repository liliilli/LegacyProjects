package Game;

import Custom.Intent;
import Custom.Pair;
import Game.Map.ContainerType;
import Game.Map.MapListType;
import Game.Objects.CharacterStatus;
import Scenes.AbstractScene;
import Screen.ScreenFrame;
import Sound.AbstractSound;
import Sound.SoundSystem;
import Sound.SoundsList;
import com.sun.istack.internal.NotNull;

import javax.xml.ws.Action;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.io.File;
import java.io.IOException;
import java.util.Stack;

import static java.lang.Thread.sleep;

public class Game {
    private static  Game    _instance       = null;
    private boolean         _loop           = true;
    private volatile boolean _loopSafe      = false;

    private static volatile Stack<AbstractScene> mScenes = new Stack<>();
    private static  ScreenFrame mScreen = ScreenFrame.getInstance();
    private static  SoundSystem mSound = SoundSystem.getInstance();

    private long        mStartTime;
    private int         mFps;
    private double      mTick;
    private boolean     mKeyPressed = false;

    public static Game getInstance() {
        if (_instance == null) {
            synchronized (Game.class) {
                if (_instance == null) _instance = new Game();
            }
        }

        return _instance;
    }

    private Game() {
        try {
            mScenes = new Stack<>();

            setFontManager();
            setFps(30);
            mScreen._getPH()._addFrame();
            mScreen.addKeyListener(new gameKeyAdapter());
            mStartTime  = System.currentTimeMillis();
        } catch (IOException | FontFormatException e) {
            e.printStackTrace();
        }
    }

    private void setFps(int value) {
        mFps        = value;
        mTick       = (double)1000 / mFps;
    }

    private void setFontManager() throws IOException, FontFormatException {
        GraphicsEnvironment ge =
                GraphicsEnvironment.getLocalGraphicsEnvironment();
            ge.registerFont(
                    Font.createFont(Font.TRUETYPE_FONT,
                    new File("src\\Px437_IBM_CGA.ttf")));
            ge.registerFont(
                    Font.createFont(Font.TRUETYPE_FONT,
                    new File("src\\Px437_IBM_CGA-2y.ttf")));

    }

    public synchronized AbstractScene recentScene() {
        return !mScenes.empty() ? mScenes.peek() : null; }

    public synchronized void changeScene(MapListType type, Object... args) {
        offLoopSafe();

        // 플레이어 및 가져올 정보를 인텐트에 넣는다.
        recentScene().wrapInformationWithIntent("IsPlayerExist", true);
        recentScene().wrapInformationWithIntent();
        if (args[0] instanceof Pair)
            recentScene().wrapInformationWithIntent("AfterPlayerPosition", args[0]);


        // 씬을 빼고 넣는다.
        recentScene().deactivate();
        popScene();
        addNewScene(MapListType.newMap(type));

        // 새로운 씬에 집어넣을 정보를 전송한다.
        recentScene().resolveInformationWithIntent(Intent.getIntent());
        Intent.removeIntent();
        if (args.length == 2) {
            if (args[1] instanceof CharacterStatus)
            recentScene().getMapContainer().getPlayerObject().
                    setStatus((CharacterStatus)args[1]);
        }

        sceneActivate();
        onLoopSafe();
    }

    public void addNewScene(AbstractScene newScene) {
        mScenes.push(newScene);
    }

    public void sceneActivate() {
        assert recentScene() != null;
        recentScene().activate();
    }

    private void popScene() { mScenes.pop(); }

    // 코루틴을 쓰고 싶었으나 불가.
    @Action
    public void loop() {
        while (_loop) {
            while (_loopSafe) {
                // input 은 쓰레드 독립적으로 구동됨.
                long nowTime = System.currentTimeMillis();
                long mElapsedTime = nowTime - mStartTime;
                // 지금 틱과 예전의 틱의 차이가 한 프레임보다 더 높으면
                // 지연된 프레임 만큼 더 연산함.
                while (mElapsedTime >= mTick) {
                    // 각 오브젝트의 갱신을 행함. (Thread 독립 구문 제외)
                    // 맵을 이동시에는 컨테이너의 초기화를 해야함.
                    recentScene().refresh();
                    mStartTime = nowTime;
                    mElapsedTime -= mTick;
                }

                if (!mScenes.isEmpty())
                    recentScene().draw();
            }
        }
    }

    public void endLoopSequence() {
        _loop = false; _loopSafe = false;
    }

    public synchronized void onLoopSafe()    { _loopSafe = true; }
    private synchronized void offLoopSafe()   { _loopSafe = false; }

    public void playSound(SoundsList type) { mSound.play(type.getSound()); }
    public void pauseSound(int i) {
        //mSound.wait();
    }

    @Action
    public void exit() {
        mScreen.exitScreen();
        System.out.println("Bye World");
    }


    // 연속적으로 누르지 않고, 한번씩만 키를 누를 수 있도록 함.
    class gameKeyAdapter extends KeyAdapter {
        @Override
        public void keyPressed(KeyEvent e) {
            if (!mKeyPressed) {
                mKeyPressed = true;
                recentScene().input(e);
            }
        }

        @Override
        public void keyReleased(KeyEvent e) {
            if (mKeyPressed) mKeyPressed = false;
        }
    }
}
