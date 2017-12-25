package Screen;

import com.sun.istack.internal.FinalArrayList;

import java.awt.*;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

public class FontManager {
    private static final float fontSize = 16f;
    private static final ArrayList<Font> fonts = new ArrayList<>();

    static {
        try {

            fonts.add(Font.createFont(Font.TRUETYPE_FONT,
                new File(FontStyle.THIN.getFontPath())).deriveFont(fontSize));
            fonts.add(Font.createFont(Font.TRUETYPE_FONT,
                new File(FontStyle.NORMAL.getFontPath())).deriveFont(fontSize));
            fonts.add(Font.createFont(Font.TRUETYPE_FONT,
                new File(FontStyle.FAT.getFontPath())).deriveFont(fontSize));
        }
        catch (IOException | FontFormatException err) {
            err.printStackTrace();
        }
    }

    public static int getFontSize() {
        return (int)fontSize;
    }

    public static Font getFont(FontStyle style) {
        return fonts.get(style.get());
    }

    public enum FontStyle {
        THIN(0,"src\\Px437_IBM_CGA-2y.ttf"),
        NORMAL(1,"src\\Px437_IBM_CGA.ttf"),
        FAT(2,"src\\Px437_IBM_BIOS-2x.ttf");

        private final int index;
        private final String fontPath;
        FontStyle(int i, String fontPath) {
            index = i;
            this.fontPath = fontPath;
        }

        public int get() { return index; }
        public String getFontPath() { return fontPath; }
    }

    public enum FontColor {
        NORMAL(16, 16, 16),
        WARNING(16, 16, 0),
        HIGHLIGHT(0, 16, 16),
        FATAL(16, 0, 0);

        private final Color color;
        FontColor(int r, int g, int b) {
            color = new Color((r == 0) ? 0 : r * 16 - 1,
                    (g == 0) ? 0 : g * 16 - 1,
                    (b == 0) ? 0 : b * 16 - 1);
        }

        public static Color getColorOf(FontColor type) {
            return type.color;
        }
    }
}
