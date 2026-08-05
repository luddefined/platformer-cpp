//
// Created by rashi on 17/04/2024.
//

#ifndef PLATFORMERSFML_ENEMY_H
#define PLATFORMERSFML_ENEMY_H

#include "Entity.h"
#include "Vector2.h"

class Enemy: public Entity
{
 public:
  Vector2 getSpawnPoint();
  void setSpawnPoint(float x, float y);

  Vector2 point0 = Vector2(0,0);
  Vector2 point1 = Vector2(0,0);
  bool move_right = true;

 private:
  Vector2 spawn_point = Vector2(0,0);
};

#endif // PLATFORMERSFML_ENEMY_H
