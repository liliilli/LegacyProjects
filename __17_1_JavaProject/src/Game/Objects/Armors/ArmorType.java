package Game.Objects.Armors;

public enum ArmorType {
    NUDE,
    LEATHER,
    IRON;

    public static GArmor newType(ArmorType type) {
        switch (type) {
            case NUDE: return new Nude();
            case LEATHER: return new Nude();
            case IRON: return new Nude();
            default: return null;
        }
    }
}
