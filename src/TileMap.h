//
// Created by rashi on 10/04/2024.
//

#ifndef PLATFORMERSFML_TILEMAP_H
#define PLATFORMERSFML_TILEMAP_H
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <string>

class TileMap
{
 public:
  GameObject** tile_map;

  uint8_t getTileSize();
  void setTileSize(uint8_t size);
  uint8_t getMapWidth();
  void setMapWidth(uint8_t size);
  uint8_t getMapHeight();
  void setMapHeight(uint8_t size);
  float getTileScale();
  void setTileScale(float scale);


  bool constructTileMap(std::string mapname);
  void destroyTileMap();

 private:
  uint8_t tile_size;
  uint8_t map_width;
  uint8_t map_height;
  float tile_scale = 1.f;

  sf::Texture dirt_texture; // 1
  sf::Texture coin_texture; // 2

  // Grass tilemap textures
  sf::Texture grass_left;   // 3
  sf::Texture grass_mid;    // 4
  sf::Texture grass_right;  // 5

  sf::Texture dirt_TR;      // 6
  sf::Texture dirt_TL;      // 7
  sf::Texture dirt_BR;      // 8
  sf::Texture dirt_BL;      // 9

  sf::Texture grass_PM;     // A
  sf::Texture grass_TL;     // B
  sf::Texture grass_TM;     // C
  sf::Texture grass_TR;     // D

  sf::Texture dirt_l;       // E
  sf::Texture dirt_r;       // F
  sf::Texture dirt_pm;      // G
  sf::Texture dirt_bl;      // H
  sf::Texture dirt_bm;      // I
  sf::Texture dirt_br;      // J

};

#endif // PLATFORMERSFML_TILEMAP_H
