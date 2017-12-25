package Screen.Pane;

import Game.Objects.CharacterStatus;
import Screen.FontManager;
import Screen.FontManager.FontColor;

import javax.swing.*;
import java.awt.*;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

import static Screen.FontManager.FontColor.*;
import static Screen.FontManager.FontStyle.NORMAL;

public class PlayStatus extends AbstractPanel {
    private Map<String, Integer> outputList = new HashMap<>();
    private int startX = 4;
    private int startY = 20;

    public PlayStatus() throws IOException, FontFormatException {
        outputList.put("LV", 0);
        outputList.put("HITS", 0);
        outputList.put("MAGI", 0);
        outputList.put("ATK", 0);
        outputList.put("DEF", 0);
        outputList.put("NEXT", 100);

        setLayout(null);
        setBounds(new Rectangle(560, 260, 720, 400));
        setBackground(new Color(0, 0, 0));
        setForeground(new Color(253, 255, 253));
        setBorder(BorderFactory.createLineBorder(Color.black));
        setFont(FontManager.getFont(NORMAL));
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        int maxhp = outputList.get("MAXHIT");
        int percent = outputList.get("HITS") / maxhp * 100;
        if (percent < 30)
            g.setColor(getColorOf(FATAL));
        else if (percent < 60)
            g.setColor(getColorOf(WARNING));
        else
            g.setColor(getColorOf(FontColor.NORMAL));

        g.drawString("LV  :" + outputList.get("LV"), startX, startY);
        g.drawString("Hits:" + outputList.get("HITS"), startX, startY + 16);
        g.drawString("Magi:" + outputList.get("MAGI"), startX, startY + 32);
        g.drawString("ATK :" + outputList.get("ATK"), startX, startY + 48);
        g.drawString("DEF :" + outputList.get("DEF"), startX, startY + 64);
        g.drawString("NEXT:" + outputList.get("NEXT") + "%", startX, startY + 80);
    }

    @Override
    public <T> void handle(T[] args) {
        if (args instanceof CharacterStatus[]) {
            outputList.put("LV", ((CharacterStatus)args[0]).getLevel());
            outputList.put("HITS", ((CharacterStatus)args[0]).getHeartPoint());
            outputList.put("MAGI", ((CharacterStatus)args[0]).getMagicPoint());
            outputList.put("ATK", ((CharacterStatus)args[0]).getAtkPoint());
            outputList.put("DEF", ((CharacterStatus)args[0]).getDefPoint());
            outputList.put("NEXT", ((CharacterStatus)args[0])
                    .getNextExpPercent());
            outputList.put("MAXHIT", ((CharacterStatus)args[0]).getMaxHp());
        }

        this.revalidate();
        this.repaint();
    }
}
