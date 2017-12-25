package Game.Objects.Weapons;

import Game.Objects.Armors.GArmor;
import Game.Objects.Armors.Nude;

public enum WeaponType {
    HAND,
    LEATHER,
    IRON;

    public static GWeapon newType(WeaponType type) {
        switch (type) {
            case HAND: return new WeaponHand();
            case LEATHER: return new WeaponHand();
            case IRON: return new WeaponHand();
            default: return null;
        }
    }
}
