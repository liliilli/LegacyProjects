package Screen.Pane;

import javax.swing.*;
import java.awt.*;

public abstract class AbstractPanel extends JPanel {
    private boolean isRefreshed = true;
    protected LocalSwitches localSwitch = new LocalSwitches();
    public AbstractPanel() { setLayout(null); }

    public void paintComponent(Graphics g) { super.paintComponent(g); }

    public void setRefresh() { isRefreshed = true; }
    public void setRelease() { isRefreshed = false; }
    protected boolean isRefreshed() { return isRefreshed; }

    protected final class LocalSwitches {
        public boolean A = false;
        public boolean B = false;
        public boolean C = false;
        public boolean D = false;
    }

    public int getLocalSwitchFlag() {
        int result = 0;
        if (localSwitch.A)
            result += 8;
        if (localSwitch.B)
            result += 4;
        if (localSwitch.C)
            result += 2;
        if (localSwitch.D)
            result += 1;

        return result;
    }

    public abstract <T extends Object> void handle(T... args);
}
