package Game.Objects;

import Custom.Pair;
import Game.Map.MapInfoContainer;
import Game.Objects.Armors.GArmor;
import Game.Objects.Moves.GMoving;
import Game.Objects.Weapons.GWeapon;

import java.awt.event.KeyEvent;
import java.util.ArrayList;

public abstract class AbstractMapObject implements GObject {
    protected final MapInfoContainer mMap;

    protected byte          mLayer = 2;
    protected int           mId;

    protected LocalSwitches localSwitch = new LocalSwitches();
    protected final Pair<Integer, Integer> position;
    protected String spritePath;

    public AbstractMapObject(Pair<Integer, Integer> pos, MapInfoContainer map) {
        mMap = map;
        this.position = pos;
    }

    public final int getX() { return position.getFirst(); }
    public final int getY() { return position.getSecond(); }

    @Override
    public void create() { }

    @Override
    public void refresh() { }

    @Override
    public void destroy() { }

    public abstract void interact(AbstractCharObject src);

    public final int  getLayer() { return mLayer; }
    public final void input(KeyEvent e) {}
    public final void move(AbstractCharObject c) {}

    protected final class LocalSwitches {
        public boolean A = false;
        public boolean B = false;
    }

    @Override
    public String toString() {
        return super.toString();
    }
}
