package Sound;

public enum Note {
    REST, A4, A4$, B4, C4, C4$, D4, D4$, E4, F4, F4$, G4, G4$, C5;

    public double getFrequency() {
        switch (this) {
            default:
                return 0.0000;
            case REST:
                return 0.0000;
            case C4:
                return 261.6256;
            case C4$:
                return 277.1826;
            case D4:
                return 293.6648;
            case D4$:
                return 311.1270;
            case E4:
                return 329.6276;
            case F4:
                return 349.2282;
            case F4$:
                return 369.9944;
            case G4:
                return 391.9954;
            case G4$:
                return 415.3047;
            case A4:
                return 440.0000;
            case A4$:
                return 466.1638;
            case B4:
                return 493.8833;
            case C5:
                return 523.2511;
        }
    }
}
