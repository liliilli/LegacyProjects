package Game.Map;

import Custom.Pair;
import Game.Objects.AbstractCharObject;
import Game.Objects.MapObjects.MapTransition;

import java.io.*;
import java.util.ArrayList;

public class MapLoader {
    private MapInfoType readSwitch;
    private MapInfoContainer mapContainer;

    public MapLoader() { readSwitch  = MapInfoType.HEADER; }

    public void LoadFile(String fileName, MapInfoContainer cont) {
        try {
            mapContainer = cont;
            FileReader mStream = new FileReader(new File(fileName));
            BufferedReader bufStream = new BufferedReader(mStream);

            while (true) {
                String retrievedString = bufStream.readLine();
                if (retrievedString != null) {
                    switch (readSwitch) {
                        case HEADER:    ReadHeader(retrievedString); break;
                        case MAP_INFO:  ReadMapFloor(retrievedString); break;
                        case OBJECT:    ReadObjects(retrievedString); break;
                    }
                }
                else
                    break;
            }

            mStream.close();
        } catch (FileNotFoundException e) {
            System.out.println("File Not Found");
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private boolean isSeparatorNull(int separator) {
        if (separator != -1)    return false;
        else                    return true;
    }

    private void ReadHeader(String buffer) {
        if (buffer.charAt(0) == '#') {
            int separator = buffer.indexOf(' ');
            if (isSeparatorNull(separator)) {
                readSwitch = MapInfoType.MAP_INFO;
                return;
            }

            String header = buffer.substring(1, separator);
            switch (header) {
                case "MAPID":   mapContainer._setMapId(buffer); break;
                case "NAME":    mapContainer._setMapName(buffer); break;
                case "WIDTH":   mapContainer._setWidth(buffer); break;
                case "HEIGHT":  mapContainer._setHeight(buffer); break;
                case "TILESET": mapContainer._setTileSet(buffer); break;
            }
        }
    }

    private void ReadMapFloor(String buffer) {
        if (buffer.charAt(0) == '#') { // If given string is header of objects
            readSwitch = MapInfoType.OBJECT;
            return;
        }

        // If got string is involved in map floor
        mapContainer.addMapNewRow();
        int length = buffer.length();
        for (int i = 0; i < length; ++i) {
            mapContainer.addCharToLast(buffer.charAt(i));
        }
    }

    private void ReadObjects(String buffer) throws NullPointerException {
        String  model   = buffer.substring(0, 1);
        int     x       = Integer.parseInt(buffer.substring(2, 4));
        int     y       = Integer.parseInt(buffer.substring(5, 7));
        int     number  = Integer.parseInt(buffer.substring(8, 10), 16);
        isValid(model, x, y);

        switch (ObjectType.newType(model.charAt(0))) {
            case MOVE: // 맵 이동 오브젝트
                String  dest    = buffer.substring(11, 13);
                int     dest_x  = Integer.parseInt(buffer.substring(14, 16));
                int     dest_y  = Integer.parseInt(buffer.substring(17, 19));

                mapContainer.addMapDependentObject(
                        ((MapTransition)ObjectType.create(ObjectType.MOVE,
                                new Pair<>(x, y), mapContainer))
                                .setDestination(
                                        MapListType.getMapType(
                                                Integer.parseInt(dest, 16)),
                                        new Pair<>(dest_x, dest_y)));
                break;
            case TREASURE: // 보물 오브젝트
                break;
            case NPC: // 일반 Character 오브젝트
                String  name    = buffer.substring(11);
                addCharacterObject(number, x, y, name);
                break;
        }
    }

    private boolean isValid(String model, int x, int y) {
        if (isInvalidType(model) && isThereWall(x, y)
                && isThereSomething(x, y) && isDuplicated(model, x, y)) {
            return false;
        }
        else
            return true;
    }

    private boolean isInvalidType(String model) {
        // 만약 잘못된 양식으로 오브젝트를 생성하려 하면 false를 한다.
        if (!"EO".contains(model)) {
            // 오류!
        }

        return false;
    }

    private boolean isThereWall(int x, int y) {
        // 만약 지정한 위치에 벽이 있다면 false 한다.
        if ("W.".contains(String.valueOf(getMapPosition(x, y)))) {
            // 오류!
        }

        return false;
    }

    private boolean isThereSomething(int x, int y) {
        ArrayList<ArrayList<AbstractCharObject>> _objects
                = mapContainer.getCharObjects();
        for (ArrayList<AbstractCharObject> container : _objects) {
            for (AbstractCharObject element : container) {
                if (element.getX() == x && element.getY() == y) {
                    // 오류!
                }
            }
        }

        return false;
    }

    private boolean isDuplicated(String model, int x, int y) {
        // 만약 Model이 E (이동) 이나, 맵과 좌표가 다를 경우
        if (model.equals('E')) {
            if (!getMapPosition(x, y).equals('E')) {
                // 오류!
            }
        }

        return true;
    }

    private void addCharacterObject(int number, int x, int y, String name) {
        CharacterType type = CharacterType.newType(number);
        Pair<Integer, Integer> position = new Pair<>(x, y);
        mapContainer.addCharacter(type, position, name);
    }

    private Character getMapPosition(int x, int y) {
        return mapContainer.getMap().get(y).get(x);
    }
}
