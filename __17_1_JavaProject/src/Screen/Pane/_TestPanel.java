package Screen.Pane;

import javax.swing.*;
import java.awt.*;

public class _TestPanel extends AbstractPanel {
    public _TestPanel() {
        setLayout(null);
        setBounds(new Rectangle(0, 0, 720,260));
        setBackground(Color.ORANGE);
        setBorder(BorderFactory.createLineBorder(Color.black));
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.drawString("Hello world", 24, 24);
        g.drawLine(32, 32, 128, 128);
        g.drawRect(144, 144, 160, 160);
    }

    @Override
    public <T> void handle(T[] args) {

    }
}
