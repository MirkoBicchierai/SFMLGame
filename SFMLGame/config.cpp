enum sourceState{
    upNormal=64*8,
    leftNormal=0,
    dim=64,
    moveFinal=64*8,
    topMoveUp=64*8,
    topMoveDown=64*10,
    topMoveLeft=64*9,
    topMoveRight=64*11,
};

enum swordState{
    leftNormalSword=0,
    UpSword=64 * 12,
    DownSword=64 * 14,
    RightSword=64 * 15,
    LeftSword=64 * 13,
    finalSwordAttack=64*5,
};

enum bowState{
    leftNormalBow=0,
    UpBow=64 * 16,
    DownBow=64 * 18,
    RightBow=64 * 19,
    LeftBow=64 * 17,
    finalBowAttack=64*12,
};

enum magicState{
    leftNormalMagic=0,
    finalMagicAttack=64*6,
    UpMagic=64 * 0,
    DownMagic=64 * 2,
    RightMagic=64 * 3,
    LeftMagic=64 * 1,
};

enum fireBallState{
    dimFireBall=64,
    NormalLeft=0,
    LeftFireBall=64*0,
    RightFireBall=64*4,
    DownFireBall=64*6,
    UpFireBall=64*2,
    finalBallAnimation=64*7,
};

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

enum tileSetWall{
    topMin=16*8,
};
