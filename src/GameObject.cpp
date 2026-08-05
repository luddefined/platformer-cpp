//
// Created by rashi on 10/04/2024.
//

#include "GameObject.h"

#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
  enabled = true;
  sprite = new sf::Sprite;
}

GameObject::~GameObject()
{
  delete sprite;
}

bool GameObject::setSprite(sf::Texture &texture, std::string file)
{
  if (!texture.loadFromFile(file))
  {
    std::cout << "Did not load file " << file << std::endl;
    return false;
  }
  else
  {
    sprite->setTexture(texture);
    return true;
  }
}

sf::Sprite* GameObject::getSprite()
{
  return sprite;
}

// Checks if this game object collides with another sprite
bool GameObject::touched(sf::Sprite &body_sprite)
{
  if (sprite->getPosition().x + sprite->getGlobalBounds().width >= body_sprite.getPosition().x
      and sprite->getPosition().x <= body_sprite.getPosition().x + body_sprite.getGlobalBounds().width
      and sprite->getPosition().y + sprite->getLocalBounds().height >= body_sprite.getPosition().y
      and sprite->getPosition().y <= body_sprite.getPosition().y + body_sprite.getGlobalBounds().height)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// Returns the distance between the left of this sprite and right of another
float GameObject::touchedDepthLeft(sf::Sprite& body_sprite)
{
  float a = sprite->getPosition().x;
  float b = body_sprite.getPosition().x + body_sprite.getGlobalBounds().width;
  return a - b;
}

// Returns the distance between the right of this sprite and left of another
float GameObject::touchedDepthRight(sf::Sprite& body_sprite)
{
  float a = sprite->getPosition().x + sprite->getGlobalBounds().width;
  float b = body_sprite.getPosition().x;
  return a - b;
}

// Returns the distance between the top of this sprite and bottom of another
float GameObject::touchedDepthTop(sf::Sprite& body_sprite)
{
  float a = sprite->getPosition().y;
  float b = body_sprite.getPosition().y + body_sprite.getGlobalBounds().height;
  return a - b;
}

// Returns the distance between the bottom of this sprite and top of another
float GameObject::touchedDepthBottom(sf::Sprite& body_sprite)
{
  float a = sprite->getPosition().y + sprite->getGlobalBounds().height;
  float b = body_sprite.getPosition().y;
  return a - b;
}

// Returns the x midpoint of the object
float GameObject::midpointx()
{
  return sprite->getPosition().x + (2/sprite->getGlobalBounds().width);
}

// Returns the y midpoint of the object
float GameObject::midpointy()
{
  return sprite->getPosition().y + (2/sprite->getGlobalBounds().height);
}
