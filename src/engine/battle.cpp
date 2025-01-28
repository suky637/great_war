#include "engine/battle.h"

BattleResult BattleSystem::simulateBattle(BattleData battleData) {
    float enemyMultiplier = battleData.enemyDefending ? 3 : 2;
    float playerMultiplier = battleData.enemyDefending ? 2 : 3;

    // TODO: adding randomness

    // Checking the ratio of forces
    float forceDifference = battleData.amountOfTroops_Player * playerMultiplier - battleData.amountOfTroops_Enemy * enemyMultiplier;
    BattleResult res;
    if (forceDifference < 0) {
        // Enemy Winning
        res.damageReceived = forceDifference * -0.1f;
        res.damageSent = forceDifference * -0.05f;
        return res;
    }
    else if (forceDifference > 0) {
        res.damageReceived = forceDifference * 0.05f;
        res.damageSent = forceDifference * 0.1f;
        return res;
    }
    else if (forceDifference == 0) {
        res.damageReceived = 100;
        res.damageSent = 100;
        return res;
    }
    res.damageReceived = 0;
    res.damageSent = 0;
    return res;
}