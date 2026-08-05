
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "GameObject.h"
#include "TileMap.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Vector2.h"
#include <random>
#include <iostream>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

  const float GRAVITY = 9.8;

 private:
  int score;

  sf::RenderWindow& window;
  sf::Font font;
  sf::Text title_text;
  sf::Text score_text;
  sf::Text life_text;
  sf::Text menu_text;
  sf::Text death_text;
  sf::Text end_text;

  sf::Texture background_texture1;
  sf::Texture background_texture2;
  sf::Sprite background_sprite1;
  sf::Sprite background_sprite2;

  sf::SoundBuffer b_jump, b_coin, b_complete, b_hurt;
  sf::Sound jump_sound, coin_sound, complete_sound, hurt_sound;

  std::string score_string;
  std::string life_string;

  Player player;
  sf::Texture player_texture;
  bool input_jump = false;
  bool in_air = true;
  bool touched_roof = false;
  int lives = 3;
  const float base_pitch = 1.f, pitch_range = 0.05f;

  GameObject end_object;
  sf::Texture end_texture;

  Enemy enemy1;
  Enemy enemy2;
  sf::Texture enemy_texture;

  TileMap game_map;

  int level = 1;
  Vector2 l1spawn = Vector2(76, 609);
  Vector2 l2spawn = Vector2(49, 246);

  void initGame();
  void initLevel2();
  void updatePlayer(float delta);
  void updateCoins();
  void updateEnemy(Enemy &enemy, float delta);
  void updateEnd();
  
  // Whoever decided to do this for random numbers needs to be checked out that guy is NOT okay
  inline float getRandomPitch(float base, float range)
  {
    static std::random_device rnd;
    static std::mt19937 gen(rnd());
    std::uniform_real_distribution<float> dist(base - range, base + range);
    float val = dist(gen);
    return val;
  }
};

#endif // PLATFORMER_GAME_H
