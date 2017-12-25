package Screen.Pane;

import Screen.FontManager;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Arrays;

import static Screen.FontManager.FontStyle.NORMAL;
import static Screen.FontManager.FontStyle.THIN;
import static Screen.Pane.TitleCanvas.TextAlign.CENTER;
import static Screen.Pane.TitleCanvas.TextAlign.LEFT;
import static Screen.Pane.TitleCanvas.TextAlign.RIGHT;

public class TitleCanvas extends AbstractPanel {
    private ArrayList<Object> varContainer = new ArrayList<>();
    private static final String basePath = "src\\Game\\Resources\\Images\\Title_Logo.png";
    private final ImageIcon logoSprite = new ImageIcon(basePath);

    public TitleCanvas() {
        setDoubleBuffered(false);
        setLayout(null);
        setBounds(new Rectangle(0, 0, 720, 400));
        setBackground(Color.black);
        setForeground(new Color(255, 255, 255));
        setFont(FontManager.getFont(NORMAL).deriveFont(24F));
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        drawTitleLogo(g);
        drawTitle(g);

        switch (getLocalSwitchFlag()) {
            case 8:
                drawFirstTitle(g); break;
            case 4: // 스탯 화면에서 최종 결정시
                drawShowPlayerInfo(g); break;
            case 3: // 이름 정할 때
                drawShowMakingName(g); break;
            case 2: // 스탯 정할 때
                drawShowMakingStatus(g); break;
            case 1:
                drawLoadingSituation(g); break;
        }

        drawCopyrightTm(g);
    }

    private void drawShowPlayerInfo(Graphics g) {
        int half = getWidth() / 2;
        int halfquat = half / 2 * 3;
        int top = 12;
        int offset = 24;

        g.setColor(Color.YELLOW);
        g.setFont(FontManager.getFont(THIN));
        drawString(g, halfquat, top + (offset * 3), CENTER,
                "Overall information of Your avatar");

        _drawPlayerInformation(g);

        g.setColor(Color.WHITE);
        g.setFont(FontManager.getFont(THIN));
        drawString(g, half + 16, top + (offset * 12), LEFT,
                "To dive into the world : ",
                "To go previous scene : ");
        g.setColor(Color.cyan);
        drawString(g, getWidth() - 16, top + (offset * 12), RIGHT,
                "Press <Enter>",
                "Press <Q/B/ESC>");
    }

    private void _drawPlayerInformation(Graphics g) {
        int half = getWidth() / 2;
        int top = 12;
        int offset = 24;

        g.setColor(Color.WHITE);
        drawString(g, half + 16, top + (offset * 4), LEFT,
                "Avatar's name : ",
                "",
                "Health point : ",
                "Magica point : ",
                "Attack point : ",
                "Defence point : ",
                "Dexity point : ");

        g.setColor(Color.yellow);
        drawString(g, getWidth() - 16, top + (offset * 4), RIGHT,
                (String)varContainer.get(0),
                "",
                String.valueOf(varContainer.get(1)),
                String.valueOf(varContainer.get(2)),
                String.valueOf(varContainer.get(3)),
                String.valueOf(varContainer.get(4)),
                String.valueOf(varContainer.get(5)));
    }

    private void drawTitleLogo(Graphics g) {
        g.drawImage(logoSprite.getImage(), 64, 24, this);
    }

    private void drawTitle(Graphics g) {
        int x = getWidth() / 4 * 3;
        int offset = 32;
        int y = 24;

        g.setFont(FontManager.getFont(NORMAL).deriveFont(24f));
        g.setColor(Color.white);
        drawString("Nultima", x, offset + y, CENTER, g);
    }

    private void drawFirstTitle(Graphics g) {
        int x = getWidth() / 4 * 3;
        int half = getWidth() / 2;
        int top = 12;
        int y = 24;

        g.setFont(FontManager.getFont(THIN));
        g.setColor(Color.yellow);
        drawString("The short adventure of", x, top + y * 3, CENTER, g);
        drawString("1970'like retro style", x, top + y * 4, CENTER, g);

        g.setColor(Color.white);
        drawString("To create new character : ", half + 16, top + y * 7, LEFT, g);
        g.setColor(Color.cyan);
        drawString("Press <N/n>", getWidth() - 16, top + y * 7, RIGHT, g);

        g.setColor(Color.white);
        drawString("To load saved file : ", half + 16, top + y * 8, LEFT, g);
        g.setColor(Color.cyan);
        drawString("Press <L/l>", getWidth() - 16, top + y * 8, RIGHT, g);

        g.setColor(Color.gray);
        drawString("To finish the game : ", half + 16, top + y * 10, LEFT, g);
        g.setColor(Color.cyan);
        drawString("Press <Q/Esc>", getWidth() - 16, top + y * 10, RIGHT, g);
    }

    private void drawCopyrightTm(Graphics g) {
        int halfquat = getWidth() / 4 * 3;
        int bottom = getHeight();

        g.setColor(Color.white);
        g.setFont(FontManager.getFont(THIN));
        drawString("2017 KNU java project", halfquat, bottom - 32, CENTER, g);
    }

    private void drawShowMakingName(Graphics g) {
        int half = getWidth() / 2;
        int halfquat = half / 2 * 3;
        int top = 12;
        int offset = 24;

        g.setColor(Color.YELLOW);
        g.setFont(FontManager.getFont(THIN));
        drawString(g, halfquat, top + (offset * 3), CENTER,
                "You have to make name",
                "before go to the Nultima world.");

        _drawPlayerName(g);

        g.setColor(Color.WHITE);
        g.setFont(FontManager.getFont(THIN));
        drawString(g, half + 16, top + (offset * 12), LEFT,
                "To make a decision : ",
                "To go previous scene : ");
        g.setColor(Color.cyan);
        drawString(g, getWidth() - 16, top + (offset * 12), RIGHT,
                "Press <Enter>",
                "Press <ESC>");
    }

    private void _drawPlayerName(Graphics g) {
        int half = getWidth() / 2;
        int halfquat = half / 2 * 3;
        int top = 12;
        int offset = 24;

        g.setColor(Color.white);
        drawString(g, halfquat, top + (offset * 6), CENTER,
                "Your name is..");

        g.setColor(Color.CYAN);
        g.setFont(FontManager.getFont(NORMAL));
        drawString(g, halfquat, top + (offset * 7), CENTER,
                (String)varContainer.get(0));
    }

    private void drawShowMakingStatus(Graphics g) {
        int half = getWidth() / 2;
        int halfquat = half / 2 * 3;
        int top = 12;
        int offset = 24;

        g.setColor(Color.YELLOW);
        g.setFont(FontManager.getFont(THIN));
        drawString(g, halfquat, top + (offset * 3), CENTER,
                "You have to decide status",
                "before go to the Nultima world.");

        _drawStatusValues(g);

        g.setColor(Color.white);
        drawString("To make a name :",
                half + 16, top + offset * 11, LEFT, g);
        g.setColor(Color.cyan);
        drawString("Press <Enter>",
                getWidth() - 16, top + offset * 11, RIGHT, g);

        g.setColor(Color.white);
        drawString("To roll status once more :",
                half + 16, top + offset * 12, LEFT, g);
        g.setColor(Color.cyan);
        drawString("Press <R/r>",
                getWidth() - 16, top + offset * 12, RIGHT, g);

        g.setColor(Color.white);
        drawString("To go back main screen :",
                half + 16, top + offset * 13, LEFT, g);
        g.setColor(Color.cyan);
        drawString("Press <B/b>",
                getWidth() - 16, top + offset * 13, RIGHT, g);
    }

    private void _drawStatusValues(Graphics g) {
        int half = getWidth() / 2;
        int top = 12;
        int offset = 24;

        g.setColor(Color.white);
        drawString(g, half + 16, top + (offset * 6), LEFT,
                "Health point : ",
                "Magica point : ",
                "Attack point : ",
                "Defence point : ",
                "Dexity point : ");

        g.setColor(Color.yellow);
        drawString(g, getWidth() - 16, top + (offset * 6), RIGHT,
                String.valueOf(varContainer.get(0)),
                String.valueOf(varContainer.get(1)),
                String.valueOf(varContainer.get(2)),
                String.valueOf(varContainer.get(3)),
                String.valueOf(varContainer.get(4)));
    }

    private void drawLoadingSituation(Graphics g) {
        int half = getWidth() / 2;
        int halfquat = half / 2 * 3;
        int top = 12;
        int offset = 24;

        g.setColor(Color.white);
        g.setFont(FontManager.getFont(NORMAL));
        drawString(g, halfquat, top + (offset * 4), CENTER,
                "Load Character");

        g.setFont(FontManager.getFont(THIN));
        drawString(g, half + 16, top + (offset * 6), LEFT,
                "Level : ",
                "Health point : ",
                "Magica point : ",
                "Attack point : ",
                "Defence point : ",
                "Dexity point : ");

        g.setColor(Color.yellow);
        drawString(g, getWidth() - 16, top + (offset * 6), RIGHT,
                String.valueOf(varContainer.get(0)),
                String.valueOf(varContainer.get(1)),
                String.valueOf(varContainer.get(2)),
                String.valueOf(varContainer.get(3)),
                String.valueOf(varContainer.get(4)),
                String.valueOf(varContainer.get(5)));

        g.setColor(Color.WHITE);
        g.setFont(FontManager.getFont(THIN));
        drawString(g, half + 16, top + (offset * 12), LEFT,
                "To dive into the world : ",
                "To go previous scene : ");
        g.setColor(Color.cyan);
        drawString(g, getWidth() - 16, top + (offset * 12), RIGHT,
                "Press <Enter>",
                "Press <Q/B/ESC>");
    }

    @Override
    public <T> void handle(T[] args) {
        if (args instanceof Boolean[]) { // 스위치 조작 시 사용
            localSwitch.A = (Boolean)args[0];
            localSwitch.B = (Boolean)args[1];
            localSwitch.C = (Boolean)args[2];
            localSwitch.D = (Boolean)args[3];
            this.revalidate();
            this.repaint();
        } else if (args instanceof Integer[]) { // 캐릭터 스테이터스 가져올때 사용
            // [0] : 체력, [1] : 매지카, [2] : 공격, [3] : 방어, [4] : 회피
            varContainer.clear();
            varContainer.addAll(Arrays.asList(args));
        } else if (args instanceof String[]) { // 캐릭터 이름 정할 떄 사용
            // [0] : 이름
            varContainer.clear();
            varContainer.add((String)args[0]);
        } else { // 그 외.
            varContainer.clear();
            varContainer.addAll(Arrays.asList(args));
        }
    }

    private void drawString(String str, int x, int y, TextAlign align, Graphics g) {
        int length = str.length();
        int size;
        String name = g.getFont().getName();

        if (name.equals("Px437 IBM CGA"))
            size = g.getFont().getSize();
        else if (name.equals("Px437 IBM CGA-2y"))
            size = g.getFont().getSize()/2;
        else
            size = g.getFont().getSize()/2;

        switch (align) {
            case LEFT:
                g.drawString(str, x, y);
                break;
            case CENTER:
                g.drawString(str, x - (length * size) / 2, y);
                break;
            case RIGHT:
                g.drawString(str, x - (length * size), y);
                break;
        }
    }

    public void drawString(Graphics g, int x, int y,
                           TextAlign align, String... args) {
        int size;
        String name = g.getFont().getName();

        if (name.equals("Px437 IBM CGA"))
            size = g.getFont().getSize();
        else if (name.equals("Px437 IBM CGA-2y"))
            size = g.getFont().getSize()/2;
        else
            size = g.getFont().getSize()/2;

        // 출력부
        for (int i = 0; i < args.length; ++i) {
            int length = args[i].length();

            switch (align) {
                case LEFT:
                    g.drawString(args[i], x, y + (i * 24));
                    break;
                case CENTER:
                    g.drawString(args[i], x - (length * size) / 2, y + (i * 24));
                    break;
                case RIGHT:
                    g.drawString(args[i], x - (length * size), y + (i * 24));
                    break;
            }
        }
    }

    public static enum TextAlign {
        LEFT,
        CENTER,
        RIGHT;
    }
}
