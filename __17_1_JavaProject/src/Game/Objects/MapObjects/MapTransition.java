package Game.Objects.MapObjects;


import Custom.Pair;
import Game.Game;
import Game.Map.MapInfoContainer;
import Game.Objects.AbstractCharObject;
import Game.Objects.AbstractMapObject;
import Game.Map.MapListType;
import Scenes.SceneState;

public class MapTransition extends AbstractMapObject {
    private MapListType mDestination;
    private Pair<Integer, Integer> mDestinationPos;

    private final Game mGame = Game.getInstance();

    public MapTransition(MapListType dst, Pair<Integer, Integer> position,
                         MapInfoContainer mapInfoContainer,
                         Pair<Integer, Integer> dstPosition) {
        super(position, mapInfoContainer);

        mDestination = dst;
        mDestinationPos = dstPosition;
    }

    public MapTransition(Pair<Integer, Integer> position,
                         MapInfoContainer mapInfoContainer) {
        super(position, mapInfoContainer);
    }

    public MapTransition setDestination(MapListType dst,
                                        Pair<Integer, Integer> dstPos) {
        mDestination = dst;
        mDestinationPos = dstPos;
        return this;
    }

    @Override
    public void create() {

    }

    @Override
    public void interact(AbstractCharObject src) {
        System.out.println("맵 이동 중입니다.");
        mMap._scene.addState(SceneState.SCENE_MOVE);
        mGame.changeScene(mDestination, mDestinationPos);
        mMap._scene.popState();
    }

    @Override
    public void destroy() {

    }
}
