#ifndef _ENEMYAI_H
#define _ENEMYAI_H

#include <Windows.h>
#include "Common.h"
#include "Player.h"

bool InitBoss(PlayerData* Chara);

void UpdateBoss(PlayerData* Chara, PlayerData* pTarget);

void AnimationBoss(PlayerData* Chara);


#endif // !_ENEMYAI_H