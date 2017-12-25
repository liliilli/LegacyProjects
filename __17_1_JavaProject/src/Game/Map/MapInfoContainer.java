package Game.Map;

import Custom.Pair;
import Game.Objects.AbstractCharObject;
import Game.Objects.AbstractEnemyObject;
import Game.Objects.AbstractMapObject;
import Game.Objects.AbstractNPCObject;
import Game.Objects.Characters.Test.TestCharacter;
import Game.Objects.Characters.Test.TestEnemy;
import Game.Objects.Characters.Test.TestNPC;
import Scenes.AbstractScene;
import com.sun.istack.internal.Nullable;
import com.sun.xml.internal.messaging.saaj.util.ByteInputStream;

import java.io.InputStream;
import java.util.ArrayList;

public final class MapInfoContainer {

    private String                      mMapName    = "";
    private int                         mMapId      = 0;
    private int                         mTileSet    = 0;

    private Pair<Integer, Integer>      mMapSize    = new Pair<>(0, 0);
    private ArrayList<ArrayList<Character>>   mMap = new ArrayList<>();

    private AbstractCharObject              mPlayer     = null;
    private ArrayList<AbstractNPCObject>    mNpcs       = new ArrayList<>();
    private ArrayList<AbstractEnemyObject>  mEnemies    = new ArrayList<>();
    private ArrayList<AbstractMapObject>    mMapObjs    = new ArrayList<>();

    private ArrayList<ArrayList<AbstractCharObject>> mCObjects = new ArrayList<>();

    public AbstractScene _scene = null;

    public MapInfoContainer(AbstractScene scene) {
        _scene = scene;
        for(int i = 0; i < 3; ++i) { mCObjects.add(new ArrayList<>()); }
    }

    public final void setMapName(String input) { mMapName = input; }
    public final void setMapId(int input) { mMapId = input; }
    public final void setTileSet(int input) { mTileSet = input; }
    public final void setWidth(int input) { mMapSize.setFirst(input); }
    public final void setHeight(int input) { mMapSize.setSecond(input); }

    public final int getMapId()      { return mMapId; }
    public final String getMapName()  { return mMapName; }
    public final int getWidth() { return mMapSize.getFirst(); }
    public final int getHeight() { return mMapSize.getSecond(); }

    public ArrayList<ArrayList<AbstractCharObject>> getCharObjects() {
        return mCObjects;
    }

    public ArrayList<AbstractCharObject> getCharacterContainer(
            ContainerType type) {
        switch (type) {
            case PLAYER: return mCObjects.get(0);
            case NPC:   return mCObjects.get(1);
            case ENEMY: return mCObjects.get(2);
            default: return null;
        }
    }

    public AbstractCharObject getPlayerObject() {
        if (mCObjects.get(0).size() != 0)
            return mCObjects.get(0).get(0);
        else
            return null;
    }

    public ArrayList<AbstractMapObject> getMapObjects() { return mMapObjs; }

    public ArrayList<ArrayList<Character>> getMap() { return mMap; }

    public char getMap(int x, int y) {
        try {
            return mMap.get(y).get(x);
        }
        catch (ArrayIndexOutOfBoundsException err) {
            return ObjectType.NONE.value();
        }
    }


    public void addMapNewRow() { mMap.add(new ArrayList<>()); }

    public void addCharToLast(char c) { mMap.get(mMap.size() -1).add(c); }

    public void addMapDependentObject(AbstractMapObject object) {
        mMapObjs.add(object);
    }

    public final void _setMapName(String input) {
        String value = input.substring(input.indexOf(' ') + 1);
        setMapName(value);
    }
    public final void _setMapId(String input) {
        String value = input.substring(input.indexOf(' ') + 1);
        this.setMapId(Integer.parseInt(value, 16));
    }
    public final void _setTileSet(String input) {
        String value = input.substring(input.indexOf(' ') + 1);
        this.setTileSet(Integer.parseInt(value, 16));
    }
    public final void _setWidth(String input) {
        String value = input.substring(input.indexOf(' ') + 1);
        this.setWidth(Integer.parseInt(value));
    }
    public final void _setHeight(String input) {
        String value = input.substring(input.indexOf(' ') + 1);
        this.setHeight(Integer.parseInt(value));
    }

    public final void addCharacter(CharacterType type,
                                   Pair<Integer, Integer> position,
                                   String name) {
        getCharacterContainer(type.sort()).
                add(CharacterType.create(type, position, name, this));
    }
}
