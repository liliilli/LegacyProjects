package Game;

import Custom.GlobalSwitch;
import Custom.Pair;
import Game.Map.MapInfoContainer;
import Game.Objects.AbstractCharObject;
import Game.Objects.CharacterStatus;
import Scenes.AbstractScene;

import java.io.*;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Stack;

public class ReaderWriter {
    public static boolean save() {
        boolean t = new ReaderWriter().saveProcess();
        return t;
    }

    public static List<Object> load() {
        List<Object> t = new ReaderWriter().loadProcess();
        return t;
    }

    public static final String path = "save.ult";
    public final Game game;

    public ReaderWriter() { game = Game.getInstance(); }

    private boolean saveProcess() {
        try {
            BufferedOutputStream output =
                    new BufferedOutputStream(new FileOutputStream(path));

            AbstractScene refScene = game.recentScene();
            MapInfoContainer refContainer = refScene.getMapContainer();
            AbstractCharObject refPlayer = refContainer.getPlayerObject();

            savePlayerInformation(refPlayer, output);

            output.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return true;
    }

    private void savePlayerInformation(AbstractCharObject player,
                                       BufferedOutputStream dst)
            throws IOException {
        ObjectOutputStream objStream = new ObjectOutputStream(dst);

        CharacterStatus status = player.getStatus();
        objStream.writeObject(status);

        dst.write(player.getX());
        dst.write(player.getY());

        dst.write(game.recentScene().getMapContainer().getMapId());
        GlobalSwitch[] switches = GlobalSwitch.getSwitches();
        objStream.writeObject(switches);
    }

    /**
     * save.urt 에서 각종 필요한 정보를 불러옵니다.
     * @return 게임을 재개하는데 필요한 정보를 오브젝트 배열로 반환합니다.
     * 따라서 이를 이용해서 게임 정보를 다시 인스턴스화 시키기 위해서는 각 인자에
     * 어떤 하위 클래스 인스턴스가 제공되는지 알 수 있어야 합니다.
     * @throws IOException
     * @throws ClassNotFoundException
     */
    private List<Object> loadProcess() {
        List<Object> arrayList = new ArrayList<>();

        try (BufferedInputStream input = new BufferedInputStream(new FileInputStream(path))){
            arrayList.addAll(loadPlayerInformation(input));
        } catch (IOException e) {
            e.printStackTrace();
        }

        return arrayList;
    }

    private Collection<?> loadPlayerInformation(BufferedInputStream input) {
        List<Object> arrayList = new ArrayList<>();

        try (ObjectInputStream objStream = new ObjectInputStream(input)){
            arrayList.add((CharacterStatus)objStream.readObject());
            arrayList.add(new Pair<>(input.read(), input.read()));
            arrayList.add(input.read());
            arrayList.add(objStream.readObject());
        } catch (IOException | ClassNotFoundException err) {
            err.printStackTrace();
        }

        return arrayList;
    }
}
