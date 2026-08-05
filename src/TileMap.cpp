//
// Created by rashi on 10/04/2024.
//

#include "TileMap.h"
#include <fstream>
#include <iostream>

uint8_t TileMap::getTileSize()
{
  return tile_size;
}

void TileMap::setTileSize(uint8_t size)
{
  tile_size = size;
}

uint8_t TileMap::getMapWidth()
{
  return map_width;
}

void TileMap::setMapWidth(uint8_t size)
{
  map_width = size;
}

uint8_t TileMap::getMapHeight()
{
  return map_height;
}

void TileMap::setMapHeight(uint8_t size)
{
  map_height = size;
}

void TileMap::setTileScale(float scale)
{
  tile_scale = scale;
}

float TileMap::getTileScale()
{
  return tile_scale;
}

// Updates the TileMap.tile_map to the map defined in filename.csv
// Dubiously inefficient as it adds in empty tiles
bool TileMap::constructTileMap(std::string filename)
{

  tile_map = new GameObject *[map_height];
  for (int i = 0; i < map_width; i++)
  {
    tile_map[i] = new GameObject[map_width];
  }

  // Read the csv file
  std::ifstream map;
  map.open(filename, std::ifstream::in);
  if (!map.is_open())
  {
    std::cout << "Error opening " << filename << std::endl;
    return false;
  }

  // The actual file reading/parsing bit
  std::string line;
  int row = 0;
  while (std::getline(map, line))
  {
    int column = 0;

    // Read the value of the line
    for (char c : line)
    {
      if (c == ',')
      {
        continue;
      }

      // Populate the tile_map 2D array with the correct cells
      switch (c)
      {
        case '0':
          // Leave this cell empty
          tile_map[row][column].enabled = false;
          break;

        case '1':
          // Make a dirt tile
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(dirt_texture, "Data/Images/kenney_pixelplatformer/Tiles/tile_0122.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case '2':
          // Make a coin
          tile_map[row][column].enabled = true;
          tile_map[row][column].collectable = true;
          tile_map[row][column].collideable = false;
          tile_map[row][column].setSprite(coin_texture, "Data/Images/kenney_physicspack/PNG/Other/coinGold.png");
          tile_map[row][column].getSprite()->setScale(0.8, 0.8);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case '3':
          // Grass left
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(grass_left, "Data/Images/kenney_pixelplatformer/Tiles/tile_0001.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case '4':
          // Grass mid
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(grass_mid, "Data/Images/kenney_pixelplatformer/Tiles/tile_0002.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case '5':
          // Grass right
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(grass_right, "Data/Images/kenney_pixelplatformer/Tiles/tile_0003.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case '6':
          // Dirt top right
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(dirt_TR, "Data/Images/kenney_pixelplatformer/Tiles/tile_0025.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case '7':
          // dirt top left
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(dirt_TL, "Data/Images/kenney_pixelplatformer/Tiles/tile_0024.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case '8':
          // dirt bottom right (soft)
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(dirt_BR, "Data/Images/kenney_pixelplatformer/Tiles/tile_0004.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case '9':
          // dirt bottom left (soft)
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(dirt_BL, "Data/Images/kenney_pixelplatformer/Tiles/tile_0005.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case 'A':
          // Grass with no side
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(grass_PM, "Data/Images/kenney_pixelplatformer/Tiles/tile_0020.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case 'B':
          // Grass top left
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(grass_TL, "Data/Images/kenney_pixelplatformer/Tiles/tile_0021.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case 'C':
          // Grass top mid
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(grass_TM, "Data/Images/kenney_pixelplatformer/Tiles/tile_0022.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case 'D':
          // Grass top right
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(grass_TR, "Data/Images/kenney_pixelplatformer/Tiles/tile_0023.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case 'E':
          // Dirt left
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(dirt_l, "Data/Images/kenney_pixelplatformer/Tiles/tile_0121.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case 'F':
          // Dirt right
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(dirt_r, "Data/Images/kenney_pixelplatformer/Tiles/tile_0123.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case 'G':
          // Dirt with no side
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(dirt_pm, "Data/Images/kenney_pixelplatformer/Tiles/tile_0120.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case 'H':
          // Dirt bottom left
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(dirt_BL, "Data/Images/kenney_pixelplatformer/Tiles/tile_0141.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case 'I':
          // Dirt bottom mid
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(dirt_bm, "Data/Images/kenney_pixelplatformer/Tiles/tile_0142.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;

        case 'J':
          // Dirt bottom right
          tile_map[row][column].enabled = true;
          tile_map[row][column].setSprite(dirt_br, "Data/Images/kenney_pixelplatformer/Tiles/tile_0143.png");
          tile_map[row][column].getSprite()->setScale(tile_scale, tile_scale);
          tile_map[row][column].getSprite()->setPosition(column * tile_size * tile_scale, row * tile_size * tile_scale);
          break;
      }
      column++;
    }
    row++;
  }
  map.close();
  return true;
}

void TileMap::destroyTileMap()
{
  // Clear the tile map (or at least I hope it clears it)
  for (int i = 0; i < map_width; i++)
  {
    delete[] tile_map[i];
  }
  delete[] tile_map;
}
