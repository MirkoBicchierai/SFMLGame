//define all constant used on all projects
#define FONT_ROOT "../font"
#define IMG_PLAYER_ROOT "../img/Player"
#define IMG_ENEMY_ROOT "../img/Enemy"
#define IMG_ROOT "../img"
#define TITLE "The Road Of Knight"
#define IMG_PLAYER_OBJ_ROOT "../img/Player_obj"
#define MAP_ROOT "../map"
#define MAP_ROOT_TUTORIAL "../map/tutorial"
#define MAP_ROOT_GAME "../map/game"
#define AUDIO_ROOT "../audio"

//enum for the player
enum sourceState{
    upNormal=64*8,
    leftNormal=0,
    dim=64,
    moveFinal=64*8,
    topMoveUp=64*8,
    topMoveDown=64*10,
    topMoveLeft=64*9,
    topMoveRight=64*11,
    topDiePlayer=64*20,
    maxLeftDiePlayer=64*5
};
//enum for the enemy
enum enemyRect{
    leftNormalEnemy=0,
    dimEnemy=64,
    moveFinalEnemy=64*8,
    topMoveUpEnemy=64*8,
    topMoveDownEnemy=64*10,
    topMoveLeftEnemy=64*9,
    topMoveRightEnemy=64*11,
    dieMaxEnemy=64*5,
    dieTopEnemy=64*20,
    maxAttackEnemyNormal=64*7,
    maxAttackEnemyExtra=64*5,

    offset=64*8,
    rightSwordEnemy=64*7,
    leftSwordEnemy=64*5,
    upSwordEnemy=64*4,
    downSwordEnemy=64*6,

};
//enum for the player attack sword
enum swordState{
    leftNormalSword=0,
    UpSword=64 * 12,
    DownSword=64 * 14,
    RightSword=64 * 15,
    LeftSword=64 * 13,
    finalSwordAttack=64*5,
};
//enum for the player attack bow
enum bowState{
    leftNormalBow=0,
    UpBow=64 * 16,
    DownBow=64 * 18,
    RightBow=64 * 19,
    LeftBow=64 * 17,
    finalBowAttack=64*12,
};
//enum for the player attack spell
enum magicState{
    leftNormalMagic=0,
    finalMagicAttack=64*6,
    UpMagic=64 * 0,
    DownMagic=64 * 2,
    RightMagic=64 * 3,
    LeftMagic=64 * 1,
};
//enum for the fireBall
enum fireBallState{
    dimFireBall=64,
    NormalLeft=0,
    LeftFireBall=64*0,
    RightFireBall=64*4,
    DownFireBall=64*6,
    UpFireBall=64*2,
    finalBallAnimation=64*7,
};
//enum for the arrow
enum ArrowState{
    dimArrow=32,
    LeftNormalArrow=0,
    TopNormalArrow=0,
    baseRotation=0,
    RightRotation=270,
    DownRotation=0,
    LeftRotation=90,
    UpRotation=180
};
//enum for Tile, checked from position on the image tile-set
enum tileSetCollision{
    topMinWall=64*3,
    topMaxWall=64*10,

    topMinWater=64*1,
    topMaxWater=64*2,

    topFloor=0,

    topChestMin=64*18,
    topChestMax=64*19,
    leftChestMin=64*5,
    topSingleChest=19*64,
    leftSingleChest=64,

    topLeverSingle=20*64,
    leftLeverSingle=7*64,

    topLever=21*64,
    leftMinLever=3*64,
    leftMaxLever=5*64,

    topMinDoorClosed_gold=14*64,
    topMaxDoorClosed_gold=15*64,
    leftMinDoorClosed_gold=64*4,
    leftMaxDoorClosed_gold=64*5,

    topMinDoorClosed_silver=14*64,
    topMaxDoorClosed_silver=15*64,
    leftMinDoorClosed_silver=64*6,
    leftMaxDoorClosed_silver=64*7,

    topMinDoorOpened=12*64,
    topMaxDoorOpened=13*64,
    leftMinDoorOpened=64*6,
    leftMaxDoorOpened=64*7,

    topMinGate=64*16,
    topMaxGate=64*17,
    LeftGate=64*8,

    goldKeyTop=22*64,
    goldKeyLeft=8*64,
    silverKeyLeft=6*64,
    silverKeyTop=22*64,

};

