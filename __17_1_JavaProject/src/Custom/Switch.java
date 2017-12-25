package Custom;

public enum Switch {
    On (true), Off (false);

    public final boolean state;
    Switch(boolean input) { state = input; }

    public static Switch valueOf(boolean bool) {
        return bool ? Switch.On : Switch.Off;
    }
}
