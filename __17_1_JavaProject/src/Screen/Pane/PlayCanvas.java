package Screen.Pane;

import Custom.Pair;
import Game.Game;
import Game.Map.ContainerType;
import Game.Map.ObjectType;
import Game.Objects.AbstractCharObject;
import Scenes.AbstractScene;
import Screen.SpriteManager;

import java.awt.*;
import java.util.ArrayList;
import java.util.Random;

import static Screen.FontManager.*;
import static Screen.FontManager.FontColor.FATAL;
import static Screen.FontManager.FontColor.getColorOf;

public class PlayCanvas extends AbstractPanel {
    private final int gridSize = 32;
    Pair<Integer, Integer> yRegion = new Pair<>(0,0);
    Pair<Integer, Integer> xRegion = new Pair<>(0,0);

    // 표시할 그리드는 총 22 x 8 이다.
    // 주인공이 한 가운데 있을 때, 왼쪽 10, 오른쪽 11, 위 4, 아래 3 이다.
    private ArrayList<ArrayList<Character>> presentGrid = new ArrayList<>();

    public PlayCanvas() {
        setDoubleBuffered(true);
        setLayout(null);
        setBounds(new Rectangle(8, 0, 704, 256));
        setBackground(new Color(0x40, 0, 0x40));
        setForeground(new Color(255, 255, 255));
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        if (!isRefreshed()) {
            getGridDrawInformation(Game.getInstance().recentScene());
            drawMapTo(g);
            drawSpritesTo(g);

            switch (new Random().nextInt(4)) {
                case 0: g.setColor(getColorOf(FATAL)); break;
                case 1: g.setColor(getColorOf(FontColor.NORMAL)); break;
                case 2: g.setColor(getColorOf(FontColor.HIGHLIGHT)); break;
                case 3: g.setColor(getColorOf(FontColor.WARNING)); break;
            }
        }
    }

    // 이 프로젝트에서 가장 긴 메소드
    public void getGridDrawInformation(AbstractScene fromScene) {
        ArrayList<ArrayList<Character>> cont = fromScene.getMapContainer().getMap();
        AbstractCharObject player = fromScene.getMapContainer().getPlayerObject();
        int x = player.getX();
        int y = player.getY();

        if (4 <= y && y + 4 <= cont.size()) {
            yRegion.setFirst(y - 4);
            yRegion.setSecond(y + 4);
        } else {
            if (y < 4) yRegion.setFirst(0);
            else yRegion.setFirst(y - 4);

            if (y + 4 > cont.size()) yRegion.setSecond(cont.size());
            else yRegion.setSecond(y + 4);
        }

        if (10 <= x && x + 11 <= cont.get(0).size()) {
            xRegion.setFirst(x - 10);
            xRegion.setSecond(x + 11);
        } else {
            if (x < 10) xRegion.setFirst(0);
            else xRegion.setFirst(x - 10);

            if (x + 12 > cont.get(0).size()) xRegion.setSecond(cont.get(0).size());
            else xRegion.setSecond(x + 12);
        }

        // 막대한 오버헤드. 수정 필요
        presentGrid.clear();

        int j = 0;
        for (int upBlank = 0; upBlank < 4 - y; ++upBlank) {
            presentGrid.add(new ArrayList<>());
            j++;
        }

        for (int yPos = yRegion.getFirst(); yPos < yRegion.getSecond(); ++yPos) {
            if (presentGrid.size() - 1 < j) {
                presentGrid.add(new ArrayList<>());
            }

            // 왼쪽 공백을 채움
            for (int leftBlank = 0; leftBlank < 10 - x; ++leftBlank)
                presentGrid.get(j).add(ObjectType.NONE.value());

            // 중간을 채움
            for (int xPos = xRegion.getFirst(); xPos < xRegion.getSecond(); ++xPos) {
                presentGrid.get(j).add(cont.get(yPos).get(xPos));
            }

            // 오른쪽 공백을 채움
            for (int rightBlank = xRegion.getSecond(); rightBlank < x + 12; ++rightBlank) {
                presentGrid.get(j).add(ObjectType.NONE.value());
            }

            j++;
        }

        for (int downBlank = yRegion.getSecond(); downBlank < y + 4; ++downBlank) {
            presentGrid.add(new ArrayList<>());
        }
    }

    private void drawMapTo(Graphics g) {
        int y = 0;
        for(ArrayList<Character> xContainer : presentGrid) {
            int x = 0;
            if (xContainer.isEmpty()) {
                for (int i = 0; i < 22; i++)
                    _drawImage(ObjectType.NONE, i, y, g);
                y++;
                continue;
            }

            for (char xChar : xContainer) {
                _drawImage(ObjectType.newType(xChar), x++, y, g);
            }

            y++;
        }
    }

    private void _drawImage(ObjectType objectType, int x, int y, Graphics g) {
        g.drawImage(SpriteManager.getImage(objectType), x * gridSize, y * gridSize, this);
    }

    private void drawSpritesTo(Graphics g) {
        AbstractCharObject player =
                Game.getInstance().recentScene().getMapContainer().getPlayerObject();
        int x = player.getX();
        int y = player.getY();

        for (AbstractCharObject elm :
                Game.getInstance().recentScene().getCharacterContainer(ContainerType.NPC)) {
                if (_isInCanvasRegion(elm, x, y))
                    _drawImage(ObjectType.NPC,
                            10 + (elm.getX() - x),
                            4 + (elm.getY() - y), g);
        }

        for (AbstractCharObject elm :
                Game.getInstance().recentScene().getCharacterContainer(ContainerType.ENEMY)) {
                if (_isInCanvasRegion(elm, x, y))
                    _drawImage(ObjectType.ENEMY,
                            10 + (elm.getX() - x),
                            4 + (elm.getY() - y), g);
        }

        g.drawImage(SpriteManager.PLAYER.getImage(),
                10 * gridSize,
                4 * gridSize, this);
    }

    private boolean _isInCanvasRegion(AbstractCharObject elm, int x, int y) {
        return (x - 10 <= elm.getX() && elm.getY() < x + 12) &&
                (y - 4 <= elm.getY() && elm.getY() < y + 4);
    }

    @Override
    public <T> void handle(T[] args) {
    }
}
