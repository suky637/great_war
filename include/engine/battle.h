#pragma once
#include <string>

struct BattleResult
{
    int damageReceived;
    int damageSent;
};

struct BattleData
{
    int amountOfTroops_Player;
    int amountOfTroops_Enemy;
    bool enemyDefending;
};

struct Attack
{
    std::string from; // attacks from
    std::string to; // attacks to
};

namespace BattleSystem
{
    BattleResult simulateBattle(BattleData battleData);
};