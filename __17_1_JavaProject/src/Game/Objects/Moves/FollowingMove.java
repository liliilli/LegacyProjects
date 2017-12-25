package Game.Objects.Moves;

import Custom.Pair;
import Game.Map.MapInfoContainer;
import Game.Map.ObjectType;
import Game.Objects.AbstractCharObject;

import java.util.*;

public class FollowingMove extends AbstractMoving {
    private static Byte[][] _movement = {
            {-1, 0}      // Left
            , {0, -1}    // Up
            , {1, 0}     // Right
            , {0, 1}};   // Down

    @Override
    public void move(AbstractCharObject source) {
        if (source.getMap().getPlayerObject() != null) {
            Pair<Integer, Integer> result = getShortestPath(source);
            int x = result.getFirst() - source.getX();
            int y = result.getSecond() - source.getY();
            source.setPosition(x, y);
        }
    }

    // 현재는 BFS 로만 구현됨.
    private Pair<Integer, Integer> getShortestPath(AbstractCharObject inp) {
        AbstractCharObject source = inp;
        MapInfoContainer mapContainer = inp.getMap();
        AbstractCharObject player = mapContainer.getPlayerObject();

        // 우선 BFS 만 구현
        Queue<Pair<Integer, Integer>> frontier = new LinkedList<>();
        Map<Pair<Integer, Integer>, Pair<Integer, Integer>> visited =
                new HashMap<>();
        frontier.add(source.getPosition());
        visited.put(source.getPosition(), null);

        while (!frontier.isEmpty()) {
            Pair<Integer, Integer> current = frontier.poll();
            Vector<Pair<Integer, Integer>> neighbors
                    = getNeighbors(current, mapContainer);

            if (current.equals(player.getPosition()))
                break;

            for(Pair<Integer, Integer> elm : neighbors) {
                if(!visited.containsKey(elm)) {
                    frontier.add(elm);
                    visited.put(elm, current);
                }
            }
        }

        // 다음에 이동할 위치를 찾는다.
        Pair<Integer, Integer> old;
        Pair<Integer, Integer> nextDirection = player.getPosition();
        while (true) {
            old = nextDirection;
            nextDirection = visited.get(old);
            if (nextDirection == source.getPosition()) {
                break;
            }
        }

        return old;
    }

    private Vector<Pair<Integer, Integer>> getNeighbors(
            Pair<Integer, Integer> input, MapInfoContainer container) {
        Vector<Pair<Integer, Integer>> neighbors = new Vector<>();

        for(int i : new int[]{0, 1, 2, 3}) {
            int x = input.getFirst()  + _movement[i][0];
            int y = input.getSecond() + _movement[i][1];

            Character _chars = container.getMap(x, y);
            if (_chars == ObjectType.WALL.value()) {}
            else if (_chars == ObjectType.MOVE.value()) {}
            else { // Default
                neighbors.add(new Pair<>(x, y));
            }
        }

        return neighbors;
    }
}
