package Screen;

import Screen.Pane.*;

import java.awt.*;
import java.io.IOException;
import java.io.NotActiveException;
import java.util.ArrayList;

public class PanelHandler {
    // ScreenFrame 에 상주하는 PanelHandler 는
    // 싱글턴으로 객체를 할당 받으며, 스크린을 출력하는데 필요한 여러 패널을 관리합니다.
    // 현재 실행된 패널의 목록을 키 스트링 형태로 받을 수도 있으며
    // 패널을 활성화 시키고 비활성화 시키는 것도 당연히 가능합니다.
    // 다만 모든 패널은 항상 정적으로 바인딩이 되어 있으므로 지우는 것은 불가능합니다.
    // 그리고 내부 열거형 타입으로 키를 일일히 타이핑 할 핑요 없이,
    // 열거형 객체로 "강하게" 패널을 불러와 핸들을 전달할 수 있습니다.
    private volatile static PanelHandler handler;
    private ScreenFrame frame;

    private ArrayList<String> activatedPanelList = new ArrayList<>();

    public synchronized static PanelHandler getInstance() {
        if (handler == null) {
            handler = new PanelHandler();
        }

        return handler;
    }

    public String[] getActivatePanels() {
        assert frame != null;

        return (String[])activatedPanelList.toArray();
    }

    public void activatePane(PanelList type) {
        assert frame != null;

        frame.add(type.panel);
        frame.revalidate();
        frame.repaint();

        activatedPanelList.add(type.name());
    }

    public void deactivatePane(PanelList type) {
        assert frame != null;

        frame.remove(type.panel);
        frame.revalidate();
        frame.repaint();

        activatedPanelList.remove(type.name());
    }

    @SafeVarargs
    public static final <T extends Object> void handle(PanelList type,
                                                T... args) {
        if (handler._isActivated(type)) {
            type.panel.handle(args);
        }
        else
            try {
                throw new NotActiveException(
                        type.name() + "is not activated yet.");
            } catch (NotActiveException e) {
                e.printStackTrace();
            }
    }

    private boolean _isActivated(PanelList type) {
        return activatedPanelList.contains(type.name());
    }

    public void _addFrame() {
        frame = ScreenFrame.getInstance();
    }

    public AbstractPanel getPanel(PanelList type) {
        assert _isActivated(type);

        return type.panel;
    }

    public static enum PanelList {
        PLAY_SCR(),
        PLAY_LOG(),
        PLAY_STATUS(),
        SYS_TITLE(),
        SYS_INVENTORY(),
        LOADING();

        private AbstractPanel panel;

        PanelList() {
            try {
                System.out.println(this.name());
                switch (this.name()) {
                    case "PLAY_SCR":        panel = new PlayCanvas(); break;
                    case "PLAY_LOG":        panel = new PlayLogBuffer(); break;

                    case "PLAY_STATUS":     panel = new PlayStatus(); break;
                    case "SYS_TITLE":       panel = new TitleCanvas(); break;
                    case "SYS_INVENTORY":   panel = new PlayInventory(); break;
                    case "LOADING":         panel = null; break;
                    default:                panel = null; break;
                }
            }
            catch (IOException | FontFormatException err) {
                err.printStackTrace();
            }
        }
    }
}
