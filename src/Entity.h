//
// Created by rashi on 11/04/2024.
//

#ifndef PLATFORMERSFML_ENTITY_H
#define PLATFORMERSFML_ENTITY_H
#include "GameObject.h"

class Entity: public GameObject
{
 public:
  Entity();

  Vector2 vector = Vector2(0,0);
  float getSpeed();
  void setSpeed(float value);

 protected:
  float speed;
};

#endif // PLATFORMERSFML_ENTITY_H
