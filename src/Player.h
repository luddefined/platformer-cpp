//
// Created by rashi on 11/04/2024.
//

#ifndef PLATFORMERSFML_PLAYER_H
#define PLATFORMERSFML_PLAYER_H
#include "Entity.h"

class Player: public Entity
{

 public:
  float getJumpForce();

  float move_to_speed;
  float acceleration = 13;
  float deceleration = 17;

 private:
  float jump_force = 370;
};

#endif // PLATFORMERSFML_PLAYER_H
