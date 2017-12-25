package Game.Objects.Characters.Test;

import Game.Map.ContainerType;
import Game.Map.MapInfoContainer;
import Game.Objects.AbstractCharObject;
import Game.Objects.AbstractMapObject;
import Game.Objects.Armors.ArmorType;
import Game.Objects.Moves.AbstractMoving;
import Game.Objects.Moves.MoveType;
import Game.Objects.Weapons.WeaponType;
import Screen.Pane.PlayLogBuffer;
import Screen.PanelHandler;
import Screen.ScreenFrame;

import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.Random;

import static Screen.PanelHandler.PanelList.PLAY_LOG;
import static Screen.PanelHandler.PanelList.PLAY_STATUS;

@Deprecated
public class TestCharacter extends AbstractCharObject {
    public TestCharacter(int x, int y, String name, MapInfoContainer c) {
        super(x, y, c);
        mName = name;
    }

    @Override
    public void create() {
        setStatus(60, 15, 10, 8, 6);
        setWeapon(WeaponType.HAND);
        setArmor(ArmorType.NUDE);
        setMoving(MoveType.PLAYER_NORMAL);
    }

    @Override
    public void input(KeyEvent e) {
        switch (e.getKeyCode()) {
            case KeyEvent.VK_LEFT:
                move.setDirection(AbstractMoving._moveDirection.LEFT);
                PanelHandler.handle(PLAY_LOG, " Left");
                break;
            case KeyEvent.VK_RIGHT:
                move.setDirection(AbstractMoving._moveDirection.RIGHT);
                PanelHandler.handle(PLAY_LOG, " Right");
                break;
            case KeyEvent.VK_UP:
                move.setDirection(AbstractMoving._moveDirection.UP);
                PanelHandler.handle(PLAY_LOG, " Up");
                break;
            case KeyEvent.VK_DOWN:
                move.setDirection(AbstractMoving._moveDirection.DOWN);
                PanelHandler.handle(PLAY_LOG, " Down");
                break;
        }

        interact();
        isRefreshed = false;
    }

    @Override
    public void destroy() {

    }

    private void interact() {
        // 우선 Object 가 있는가를 확인한다.
        AbstractMoving._moveDirection dir = move.getDirection();
        int x = getX();
        int y = getY();
        if (dir == AbstractMoving._moveDirection.LEFT) --x;
        else if (dir == AbstractMoving._moveDirection.UP) --y;
        else if (dir == AbstractMoving._moveDirection.RIGHT) ++x;
        else if (dir == AbstractMoving._moveDirection.DOWN) ++y;

        // NPC 인가?
        ArrayList<AbstractCharObject> container =
                mMap.getCharacterContainer(ContainerType.NPC);
        for (AbstractCharObject elm : container) {
            if (elm.getX() == x && elm.getY() == y) {
                communicate(this, elm);
                return;
            }
        }

        // 적대 캐릭터인가?
        container = mMap.getCharacterContainer(ContainerType.ENEMY);
        for (AbstractCharObject elm : container) {
            if (elm.getX() == x && elm.getY() == y) {
                battle(this, elm);
                return;
            }
        }

        // 보물상자 등인가?


        // 맵 오브젝트가 바로 밑에 있는가?
        ArrayList<AbstractMapObject> _mapObjects = mMap.getMapObjects();
        for (AbstractMapObject elm : _mapObjects) {
            if (x == elm.getX() && y == elm.getY()) {
                elm.interact(this);
                break;
            }
        }

        status.addExp(new Random().nextInt(10));
        PanelHandler.handle(PLAY_STATUS, status);

        move(this);
    }

    @Override
    public void communicate() {}

    private void communicate(AbstractCharObject source,
                             AbstractCharObject dest) {
        dest.communicate();
    }

    @Override
    protected void battle(AbstractCharObject my,
                        AbstractCharObject enemy) {
        int myAtk = my.getStatus().getAtkPoint();
        int myDex = my.getStatus().getDexPoint();
        int enDef = my.getStatus().getDefPoint();
        int enDex = my.getStatus().getDexPoint();

        // 지금은 Dex 로 인한 회피율 , 크리티컬, 반격율 산출은 하지 않음.
        // 오직 Atk - Def 로만...
        int damage = myAtk - (int)(enDef / 1.5);
        boolean counter = false;
        boolean dodge = false;

        // Enemy 에게 피드백
        enemy.getStatus().decreaseHeartPoint(damage);

        displayLog(
                my.getName() + " Attacked " + enemy.getName() + "!",
                enemy.getName() + " was damaged by " + damage);

        System.out.println(enemy.getName() + ":" + enemy.getStatus().getHeartPoint());

        // 만약 Enemy 의 체력이 0 이하이면, 소거한다.
        if (enemy.getStatus().isDead()) {
            enemy.getStatus().getExperience();

            // 적을 죽인다.
            displayLog( enemy.getName() + " is vanished to the ash." );
            mMap.getCharacterContainer(ContainerType.ENEMY).remove(enemy);
        }
    }

    @Override
    public void refresh() {
        if (isRefreshed)
            return;

        ArrayList<AbstractCharObject> _temp =
                mMap.getCharacterContainer(ContainerType.ENEMY);
        ArrayList<AbstractCharObject> _npcs =
                mMap.getCharacterContainer(ContainerType.NPC);
        for (AbstractCharObject elm : _temp) { elm.offRefresh(); }
        for (AbstractCharObject elm : _npcs) { elm.offRefresh(); }

        isRefreshed = true;
    }
}
