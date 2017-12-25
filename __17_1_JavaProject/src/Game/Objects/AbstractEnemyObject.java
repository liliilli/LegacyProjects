package Game.Objects;

import Custom.Pair;
import Game.Map.MapInfoContainer;
import Game.Objects.Moves.AbstractMoving;

import java.awt.event.KeyEvent;
import java.util.Vector;

public abstract class AbstractEnemyObject extends AbstractCharObject {
    public AbstractEnemyObject(int x, int y, MapInfoContainer c) {
        super(x, y, c);
    }

    public abstract void create();

    @Override
    public void refresh() {
        if (isRefreshed)
            return;

        if (rangeCheck(mMap.getPlayerObject())) {
            battle(this, mMap.getPlayerObject());
        } else
            move(this);

        isRefreshed = true;
    }

    // 상, 하, 좌, 우에 플레이어가 있는지 확인한다.
    private boolean rangeCheck(AbstractCharObject player) {
        int playerX = player.getX();
        int playerY = player.getY();
        int myX = this.getX();
        int myY = this.getY();

        if (checkPos(playerX, playerY, myX--, myY) ||
                checkPos(playerX, playerY, myX++, myY) ||
                checkPos(playerX, playerY, myX, myY--) ||
                checkPos(playerX, playerY, myX, myY++)) {
            return true;
        }

        return false;
    }

    private boolean checkPos(int pX, int pY, int mX, int mY) {
        return pX == mX && pY == mY;
    }

    protected abstract void battle(AbstractCharObject my, AbstractCharObject enemy);

    @Override
    public void destroy() {
        System.out.println("꾸에엑");
        System.out.println(this.getName() + "은/는 죽었습니다.");
    }


    /*
     * 적 캐릭터는 키 입력과 상호작용을 할 수 없습니다.
     */
    @Override
    public final void input(KeyEvent e) { assert false; }
    @Override
    public final void communicate() { assert false; }
}

