package Game.Objects.Characters.Enemy;

import Game.Map.ContainerType;
import Game.Map.MapInfoContainer;
import Game.Objects.AbstractCharObject;
import Game.Objects.AbstractEnemyObject;
import Game.Objects.Armors.ArmorType;
import Game.Objects.Moves.MoveType;
import Game.Objects.Weapons.WeaponType;
import Screen.PanelHandler;

import static Screen.PanelHandler.PanelList.PLAY_STATUS;

public class E_Hobgoblin extends AbstractEnemyObject {
    public E_Hobgoblin(int x, int y, String name, MapInfoContainer c) {
        super(x, y, c);
        mName = name;
    }

    @Override
    public void create() {
        setStatus(40, 13, 10, 8, 6);
        setWeapon(WeaponType.HAND);
        setArmor(ArmorType.IRON);
        setMoving(MoveType.NORMAL);
    }

    @Override
    protected void battle(AbstractCharObject my, AbstractCharObject enemy) {
        int myAtk = my.getStatus().getAtkPoint();
        int myDex = my.getStatus().getDexPoint();
        int enDef = my.getStatus().getDefPoint();
        int enDex = my.getStatus().getDexPoint();

        // 지금은 Dex 로 인한 회피율 , 크리티컬, 반격율 산출은 하지 않음.
        // 오직 Atk - Def 로만...
        int damage = myAtk - (int)(enDef / 1.5);
        boolean counter = false;
        boolean dodge = false;

        // Enemy 에게 피드백
        enemy.getStatus().decreaseHeartPoint(damage);

        displayLog(
                my.getName() + " Attacked " + enemy.getName() + "!",
                enemy.getName() + " was damaged by " + damage);

        System.out.println(enemy.getName() + ":" + enemy.getStatus().getHeartPoint());
        PanelHandler.handle(PLAY_STATUS, enemy.getStatus());

        if (enemy.getStatus().isDead()) {
            displayLog("Player is dead.");
            mMap.getCharacterContainer(ContainerType.PLAYER).remove(enemy);
        }
    }
}
