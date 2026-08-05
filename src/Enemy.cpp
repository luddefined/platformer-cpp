//
// Created by rashi on 17/04/2024.
//

#include "Enemy.h"

// Returns the enemy spawn point
Vector2 Enemy::getSpawnPoint()

{
  return spawn_point;
}

// Sets the enemy's spawn point
void Enemy::setSpawnPoint(float x, float y)
{
  spawn_point.x = x;
  spawn_point.y = y;
}
