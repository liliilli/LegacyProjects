package Game.Objects;

import Game.Objects.Armors.ArmorType;
import Game.Objects.Armors.GArmor;
import Game.Objects.Weapons.GWeapon;
import Game.Objects.Weapons.WeaponType;
import Screen.PanelHandler;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class CharacterStatus implements Serializable {
    public static CharacterStatus createInstance(
            int hp, int mp, int atk, int def, int dex) {
        return new CharacterStatus(hp, mp, atk, def, dex);
    }

    public static CharacterStatus createInstance() {
        return new CharacterStatus(-1, -1, -1, -1, -1);
    }

    private static int LEVEL_MAX = 5;

    public static int[] expArray = new int[]{0, 100, 300, 600, 1000, 1500};
    public static int[] hpArray = new int[]{0, 10, 10, 10, 10, 20};
    public static int[] mpArray = new int[]{0, 3, 3, 3, 3, 5};

    private int level       = 1;
    private int heartPoint  = 0; // If -1, Invincible
    private int magicPoint  = 0; // If -1, Infinite Magika
    private int atkPoint    = 0; // If -1, Infinite Attack
    private int defPoint    = 0; // If -1, Infinite Defense
    private int dexPoint    = 0; // If -1, Always dodge
    private int expeiment   = 0;

    private int maxHp       = 0;
    private int maxMp       = 0;
    private int maxExp      = 0;
    private int nextExp     = 0;

    private int coin        = 0;
    private Map<String, Integer> inventory = new HashMap<>();

    private GWeapon weapon;
    private GArmor armor;

    private CharacterStatus() {
        this(-1, -1, -1, -1, -1);
    }

    private CharacterStatus(int hp, int mp, int atk, int def, int dex) {
        maxHp = heartPoint = hp;
        maxMp = magicPoint = mp;
        atkPoint = atk;
        defPoint = def;
        dexPoint = dex;
        nextExp = expArray[level];
    }

    public void addItem(String item) {
        if (!inventory.containsKey(item))
            inventory.put(item, 1);
        else {
            Integer wrap = inventory.get(item);
            wrap += 1;
            inventory.replace(item, wrap);
        }
    }

    public void addItem(String item, int amount) {
        if (!inventory.containsKey(item))
            inventory.put(item, 0);

        Integer wrap = inventory.get(item);
        wrap += amount;
        inventory.replace(item, wrap);
    }

    public void removeItem(String item) {
        if (!inventory.containsKey(item))
            return;

        Integer wrap = inventory.get(item);
        wrap -= 1;

        if (wrap.equals(0)) {
            inventory.remove(item);
        }
        else
            inventory.replace(item, wrap);
    }

    public void removeAll() {
        inventory = new HashMap<>();
    }

    public void setHeartPoint(int hp) {
        this.maxHp = this.heartPoint = hp;
    }

    public void setMagicaPoint(int mp) {
        this.maxMp = this.magicPoint = mp;
    }

    public void setAtkPoint(int atk) {
        this.atkPoint = atk;
    }

    public void setDefPoint(int def) {
        this.defPoint = def;
    }

    public void setDexPoint(int dex) {
        this.dexPoint = dex;
    }

    public void setFulfillHeartPoint() {
        this.heartPoint = this.maxHp;
    }

    public void increaseHeartPoint(int amt) {
        this.heartPoint += amt;
        if (heartPoint > maxHp)
            heartPoint = maxHp;
    }

    public void decreaseHeartPoint(int dmg) { this.heartPoint -= dmg; }

    public int getLevel() { return level; }

    public int getHeartPoint() { return heartPoint; }

    public int getExperience() { return expeiment; }

    public int getNextExpPercent() {
        return (int)((double)(expeiment - expArray[level - 1])
                / (expArray[level] - expArray[level - 1]) * 100);
    }

    public int getMaxHp() { return maxHp; }

    public int getCoin() { return coin; }

    public boolean decreaseCoin(int value) {
        if (coin - value < 0) return false;
        else coin -= value;

        return true;
    }

    private boolean isLevelUp() {
        return getNextExpPercent() >= 100;
    }

    private void processLevelUp() {
        if (level < LEVEL_MAX) {
            level += 1;

            maxHp += hpArray[level - 1];
            maxMp += mpArray[level - 1];

            setFulfillHeartPoint();

            atkPoint += new Random().nextInt(4) + 1;
            defPoint += new Random().nextInt(4) + 1;
            dexPoint += new Random().nextInt(4) + 1;

            nextExp = expArray[level];
        }
    }

    public void addExp(int expeiment) {
        this.expeiment += expeiment;

        if (isLevelUp()) {
            processLevelUp();
        }
    }

    public int getMaxExp() { return maxExp; }

    public boolean isDead() { return heartPoint <= 0; }

    public void     increaseMagicPoint(int amt) {
        this.magicPoint += amt;
        if (magicPoint > maxMp)
            magicPoint = maxMp;
    }
    public void     decreaseMagicPoint(int dmg) {
        this.magicPoint -= dmg;
        if (magicPoint < 0)
            magicPoint = 0;
    }
    public int  getMagicPoint() { return magicPoint; }

    public int getAtkPoint() { return atkPoint; }
    public int getDefPoint() { return defPoint; }
    public int getDexPoint() { return dexPoint; }

    public GWeapon weapon() { return weapon; }
    public GArmor armor() { return armor; }
    public void setWeapon(WeaponType type) { this.weapon = WeaponType.newType(type); }
    public void setArmor(ArmorType type) { this.armor = ArmorType.newType(type); }
}
