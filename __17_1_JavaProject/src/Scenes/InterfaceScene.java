package Scenes;

import Custom.Intent;

import java.awt.event.KeyEvent;

/**
 * Created by JongminYun on 2017-05-13.
 */
public interface InterfaceScene {
    boolean input(KeyEvent e);
    boolean refresh();
    boolean draw();
    void activate();
    void deactivate();

    void wrapInformationWithIntent();
    void wrapInformationWithIntent(String key, Object object);

    void resolveInformationWithIntent(Intent intent);
}
