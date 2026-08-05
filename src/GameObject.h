//
// Created by rashi on 10/04/2024.
//

#ifndef PLATFORMERSFML_GAMEOBJECT_H
#define PLATFORMERSFML_GAMEOBJECT_H
#include "Vector2.h"
#include <SFML/Graphics.hpp>

class GameObject
{
 public:
  GameObject();
  ~GameObject();

  bool setSprite(sf::Texture &texture, std::string file);
  bool touched(sf::Sprite &body_sprite);
  float midpointx();
  float midpointy();
  float touchedDepthLeft(sf::Sprite &body_sprite);
  float touchedDepthRight(sf::Sprite &body_sprite);
  float touchedDepthTop(sf::Sprite &body_sprite);
  float touchedDepthBottom(sf::Sprite &body_sprite);
  sf::Sprite* getSprite();

  bool enabled;
  bool collectable = false;
  bool collideable = true;

 protected:
  sf::Sprite* sprite = nullptr;
};

#endif // PLATFORMERSFML_GAMEOBJECT_H
