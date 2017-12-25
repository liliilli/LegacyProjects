package Game.Objects;

import Custom.Pair;

import java.awt.event.KeyEvent;

public interface GObject {
    int  getLayer();
    void input(KeyEvent e);
    void create();
    void refresh();
    void move(AbstractCharObject c);
    void destroy();
}
