package Game.Objects;

import Custom.Pair;
import Game.Map.ContainerType;
import Game.Map.MapInfoContainer;
import Game.Map.ObjectType;
import Game.Objects.Armors.ArmorType;
import Game.Objects.Moves.AbstractMoving;
import Game.Objects.Moves.MoveType;
import Game.Objects.Weapons.WeaponType;
import Screen.PanelHandler;

import java.awt.event.KeyEvent;
import java.util.ArrayList;

import static Screen.PanelHandler.PanelList.PLAY_LOG;

public abstract class AbstractCharObject implements GObject {
    protected final MapInfoContainer mMap;
    protected boolean isRefreshed = true;

    protected byte          mLayer = 1;
    protected int           mId;
    protected String        mName = null;

    protected LocalSwitches localSwitch = new LocalSwitches();
    protected Pair<Integer, Integer> position = new Pair<>(0, 0);
    protected CharacterStatus status;
    protected AbstractMoving move;

    public AbstractCharObject(MapInfoContainer c) {
        mMap = c;
    }

    public AbstractCharObject(int x, int y, MapInfoContainer c) {
        initializePosition(x, y);
        mMap = c;
        create();
    }

    private boolean checkCollision(int x, int y) {
        // 우선 맵 사이즈 밖으로 나가지 않도록 함.
        if (x < 0 || y < 0
                || x >= mMap.getWidth()
                || y >= mMap.getHeight()) { return false; }

        // 벽 및 지나갈 수 없는 맵 타일 체크를 함.
        ObjectType src = ObjectType.newType(mMap.getMap(x,y));
        switch(src) {
            default: break;
            case WALL: return false;
            case SEA: return false;
            case NONE: return false;
            case BLOCK: return false;
            case MOUNTAIN: return false;
            case MOVE: return false;
        }

        // 주인공 충돌 체크를 함.
        AbstractCharObject _object = mMap.getPlayerObject();
        if (_object.getX() == x && _object.getY() == y)
            return false;

        // 몬스터 및 오브젝트 충돌 체크를 함.
        ArrayList<AbstractCharObject> _temp
                = mMap.getCharacterContainer(ContainerType.NPC);
        for (AbstractCharObject elm : _temp) {
            if (elm.getX() == x && elm.getY() == y)
                return false;
        }

        _temp = mMap.getCharacterContainer(ContainerType.ENEMY);
        for (AbstractCharObject elm : _temp) {
            if (elm.getX() == x && elm.getY() == y)
                return false;
        }

        return true;
    }

    @Override
    public abstract void input(KeyEvent e);

    public abstract void communicate();

    protected void battle(AbstractCharObject my, AbstractCharObject enemy) {}

    public abstract void create();

    @Override
    public void move(AbstractCharObject inp) { move.move(inp); }

    @Override
    public abstract void destroy();

    public final void initializePosition(int x, int y) {
        position = new Pair<>(x, y);
    }

    public final int getLayer() { return mLayer; }

    public final void setPosition(int x, int y) {
        if (checkCollision(position.getFirst()+x, position.getSecond()+y)) {
            position.setFirst(position.getFirst() + x);
            position.setSecond(position.getSecond() + y);
        }
    }

    public final void setPosition(Byte[] movement) {
        setPosition(movement[0], movement[1]);
    }

    public final void setMoving(MoveType type) { move = MoveType.newType(type); }
    public final void setArmor(ArmorType type) { status.setArmor(type); }
    public final void setWeapon(WeaponType type) { status.setWeapon(type); }
    public final void setStatus(int hp, int mp, int atk, int def, int dex) {
        status = CharacterStatus.createInstance(hp, mp, atk, def, dex);
    }
    public final void setStatus(CharacterStatus statusContainer) {
        status = statusContainer;
    }

    public final Pair<Integer, Integer> getPosition() { return position; }

    public final int getX() { return position.getFirst(); }
    public final int getY() { return position.getSecond(); }

    public final String getName() { return mName; }
    public final CharacterStatus getStatus() { return status; }
    public final MapInfoContainer getMap() { return mMap; }

    public final void offRefresh() { isRefreshed = false; }
    public final void onRefresh() { isRefreshed = true; }

    protected final class LocalSwitches {
        public boolean A = false;
        public boolean B = false;
        public boolean C = false;
        public boolean D = false;

        public String getSwitchStatus() {
            String result = "";
            if (A) result += "1"; else result += "0";
            if (B) result += "1"; else result += "0";
            if (C) result += "1"; else result += "0";
            if (D) result += "1"; else result += "0";

            return result;
        }

        public void resetAll() { A = B = C = D = false; }
        public void setSwitches(String value) {
            if (value.length() != 4)
                throw new RuntimeException("Unexpected length switch args");

            A = (value.charAt(0) == '1') ? true : false;
            B = (value.charAt(1) == '1') ? true : false;
            C = (value.charAt(2) == '1') ? true : false;
            D = (value.charAt(3) == '1') ? true : false;
        }
    }

    @Override
    public final String toString() {
        return "(" + mId + ": " + mName + ", " + mLayer + ")";
    }

    protected void displayLog(String arg, String... args) {
        PanelHandler.handle(PLAY_LOG, arg);
        PanelHandler.handle(PLAY_LOG, args);
    }
}
