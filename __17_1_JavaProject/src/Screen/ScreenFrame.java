package Screen;

import Screen.Pane.*;

import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class ScreenFrame extends JFrame implements InterfaceScreen {
    private static ScreenFrame  _instance = null;
    private final String _windowTitle = "Nultima";

    private final PanelHandler panelHandler = PanelHandler.getInstance();

    public ScreenFrame() {
        setLayout(null);
        setTitle(_windowTitle);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setSize(720, 400);
        setResizable(false);
        setVisible(true);
        requestFocus();
    }

    public void refreshAll() {
        revalidate();
        repaint();
    }


    public static ScreenFrame getInstance() {
        if (_instance == null) {
            synchronized (ScreenFrame.class) {
                if (_instance == null) _instance = new ScreenFrame();
            }
        }

        return _instance;
    }

    public void exitScreen() {
        removeAll();
        setVisible(false);
        dispose();
    }

    public PanelHandler _getPH() { return panelHandler; }
}
