package Custom;

import java.io.Serializable;

public enum GlobalSwitch implements Serializable {
    HELLO_WORLD(0x00),
    // VILLAGE 01
    GOT_KINGS_MESSAGE(0x10),
    BOUGHT_IRON_SWORD(0x11),
    REQUEST_HOPGOBLIN_INPROGRESS(0x12),
    REQUEST_HOPGOBLIN_COMPLETE(0x13),
    // DUNGEON 01

    // VILLAGE 02

    // DUNGEON 02

    // VILLAGE 03

    // DUNGEON 03

    // SATAN CASTLE
    SAVED_PRINCESS(0xB0),
    KILLED_SATAN(0xB1),
    // TEST
    TEST_TRAPPED(0xF0),
    TEST_SWITCH(0xF1);

    private final int number;
    private boolean toggled = false;

    GlobalSwitch(int i) { number = i; }
    public void     set(Switch input) { toggled = input.state; }
    public boolean  get() { return this.toggled; }
    public int      getNumber() { return number; }

    public static GlobalSwitch[] getSwitches() {
        return GlobalSwitch.values();
    }

    public static void setSwitches(GlobalSwitch[] input) {
        int i = 0;
        for (GlobalSwitch elm : GlobalSwitch.values()) {
            if (elm.getNumber() == input[i].getNumber())
                elm.set(Switch.valueOf(input[i++].get()));
        }
    }
}

