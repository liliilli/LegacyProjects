package Screen.Pane;

import Screen.FontManager;

import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import static Screen.FontManager.FontColor.getColorOf;
import static Screen.FontManager.FontStyle.NORMAL;
import static Screen.FontManager.FontStyle.THIN;
import static Screen.FontManager.getFontSize;

public class PlayLogBuffer extends AbstractPanel {
    private final ArrayList<String> stringBuffer = new ArrayList<>();
    private final int startX = 4;
    private final int startY = 20;

    public PlayLogBuffer() throws IOException, FontFormatException {
        setLayout(null);
        setBounds(new Rectangle(0, 260, 560, 400));
        setBackground(new Color(0, 0, 0));
        setForeground(new Color(255, 255, 255));
        setBorder(BorderFactory.createLineBorder(Color.black));
        setFont(FontManager.getFont(THIN));

        stringBuffer.add("WELCOME TO Nultima WORLD!");
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        if (!isRefreshed()) {
            int i = 0;
            g.setColor(getColorOf(FontManager.FontColor.NORMAL));


            for (String elm : stringBuffer) {
                g.drawString(elm, startX, startY + (getFontSize() * i));
                i++;
            }
        }
    }

    @Override
    public <T> void handle(T[] args) {
        if (args instanceof String[]) {
            if (args.length == 1)
                handleString((String)args[0]);
            else
                handleString((String[])args);
        }

        // Must be here
        this.revalidate();
        this.repaint();
    }

    public void handleString(String line) {
        if (stringBuffer.size() == 5)
            stringBuffer.remove(0);

        stringBuffer.add(line);
    }

    public void handleString(String[] line) {
        for (String elm : line) {
            if (stringBuffer.size() == 5)
                stringBuffer.remove(0);

            stringBuffer.add(elm);
        }
    }

    public static enum LogColor {
        NORMAL,
        INPUT,
        BATTLE,
        EMERGENCY;
    }
}
