package Game.Objects.Weapons;

import java.io.Serializable;

public interface GWeapon extends Serializable {
    void    attack();
    String  toString();
}
