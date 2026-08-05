
#include "Game.h"
#include <iostream>

namespace
{
    // Game state enum
    enum class gamestate
  {
    MENU = 0,   // Initial state
    GAME = 1,   // State while in level
    LOST = 2,   // State when the player loses all health
    WIN = 3     // State after touching the end goal.
  };
  gamestate game_state;

  // Player movement direction enum
  enum class user_input_direction
  {
    NONE = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4,
  };
  user_input_direction input_direction;

  // Whoever designed this method of making random numbers needs to be checked out

}

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{
}

bool Game::init()
{
  game_state = gamestate::MENU;

  // Load font
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Font did not load\n";
  }

  // Initialise level backgrounds
  if (!background_texture1.loadFromFile("Data/Images/kenney_physicspack/PNG/Backgrounds/colored_grass.png"))
  {
    std::cout << "Background of level 1 did not load\n";
  }
  background_sprite1.setTexture(background_texture1);
  background_sprite1.setScale(
    window.getSize().x / background_sprite1.getGlobalBounds().width,
    window.getSize().y / background_sprite1.getGlobalBounds().height);

  if (!background_texture2.loadFromFile("Data/Images/lvl1.png"))
  {
    std::cout << "Background of level 2 did not load\n";
  }

  // Load sounds
  b_jump.loadFromFile("Data/Audio/jump.wav");
  b_coin.loadFromFile("Data/Audio/coin.wav");
  b_complete.loadFromFile("Data/Audio/complete.wav");
  b_hurt.loadFromFile("Data/Audio/hurt.wav");
  jump_sound.setBuffer(b_jump);
  coin_sound.setBuffer(b_coin);
  complete_sound.setBuffer(b_complete);
  hurt_sound.setBuffer(b_hurt);

  background_sprite2.setTexture(background_texture2);
  background_sprite2.setScale(
    window.getSize().x / background_sprite2.getGlobalBounds().width,
    window.getSize().y / background_sprite2.getGlobalBounds().height);


  // Title text
  title_text.setFont(font);
  title_text.setString("Press enter to start game");
  title_text.setCharacterSize(70);
  title_text.setFillColor(sf::Color::White);
  title_text.setPosition(
    window.getSize().x * 0.5 - title_text.getGlobalBounds().width/2,
    window.getSize().y * 0.4 - title_text.getGlobalBounds().height/2);

  // Instructions text
  menu_text.setFont(font);
  menu_text.setString("Press A / D to move\nPress space to jump");
  menu_text.setCharacterSize(40);
  menu_text.setFillColor(sf::Color::White);
  menu_text.setPosition(
    window.getSize().x * 0.5 - menu_text.getGlobalBounds().width/2,
    window.getSize().y * 0.7 - menu_text.getGlobalBounds().height/2);

  // Score text
  score_text.setFont(font);
  score_text.setCharacterSize(18);
  score_text.setFillColor(sf::Color::White);
  score_string = "Score: " + std::to_string(score);
  score_text.setPosition(
    window.getSize().x * 0.1,
    window.getSize().y * 0.95);

  // Lives text
  life_text.setFont(font);
  life_text.setCharacterSize(18);
  life_text.setFillColor(sf::Color::White);
  life_string = "Lives: " + std::to_string(lives);
  life_text.setPosition(
    window.getSize().x * 0.21,
    window.getSize().y * 0.95);

  // Death screen text
  death_text.setFont(font);
  death_text.setCharacterSize(40);
  death_text.setFillColor(sf::Color::White);

  // End screen text
  end_text.setFont(font);
  end_text.setCharacterSize(40);
  end_text.setFillColor(sf::Color::White);

  // End post
  end_object.setSprite(end_texture, "Data/Images/kenney_physicspack/PNG/Other/flagRed.png");
  end_object.getSprite()->setScale(0.5, 0.5);

  // Player initialisation
  player.setSprite(player_texture, "Data/Images/kenney_pixelplatformer/Characters/character_0000.png");
  player.getSprite()->setScale(1,1);
  player.setSpeed(4.3);

  // Enemy initialisation (there's really only space for two of them)
  enemy1.setSprite(enemy_texture, "Data/Images/kenney_pixelplatformer/Characters/character_0009.png");
  enemy1.getSprite()->setScale(1,1);
  enemy1.setSpeed(70);


  enemy2.setSprite(enemy_texture, "Data/Images/kenney_pixelplatformer/Characters/character_0009.png");
  enemy2.getSprite()->setScale(1,1);
  enemy2.setSpeed(70);



  // Tile map initialisation (30x30 map, though only 20x30 tiles are shown (breaks if width < height))
  game_map.setTileSize(18);
  game_map.setMapHeight(30);
  game_map.setMapWidth(30);
  game_map.setTileScale(2);
  // game_map.constructTileMap("../Data/Tilemaps/testmap.csv");

  return true;
}

void Game::update(float dt)
{
  switch (game_state)
  {
    case gamestate::GAME:
      updatePlayer(dt);
      updateEnemy(enemy1, dt);
      updateEnemy(enemy2, dt);
      updateCoins();
      updateEnd();
      break;
  }
}

void Game::render()
{

  switch (game_state)
  {
    case gamestate::MENU:
      window.draw(title_text);
      window.draw(menu_text);
      break;

    case gamestate::GAME:
      if (level == 1)
      {
        window.draw(background_sprite1);
      }
      else if (level == 2)
      {
        window.draw(background_sprite2);
      }
      window.draw(*player.getSprite());
      window.draw(*enemy1.getSprite());
      window.draw(*enemy2.getSprite());
      for (int i = 0; i < game_map.getMapWidth(); i++)
      {
        for (int j = 0; j < game_map.getMapHeight(); j++)
        {
          if (game_map.tile_map[i][j].enabled)
          {
            window.draw(*game_map.tile_map[i][j].getSprite());
          }
        }
      }
      window.draw(score_text);
      window.draw(life_text);
      window.draw(*end_object.getSprite());
      break;

    case gamestate::LOST:
      window.draw(death_text);
      break;

    case gamestate::WIN:
      window.draw(end_text);
      break;
  }
}

void Game::mouseClicked(sf::Event event)
{
  std::cout << "click\n";
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
  std::cout << click.x << " | " << click.y << "\n";

}

void Game::keyPressed(sf::Event event)
{
  switch (game_state)
  {
    case gamestate::MENU:
      if (event.key.code == sf::Keyboard::Key::Enter)
      {
        initGame();
      }

    case gamestate::GAME:
      if (event.key.code == sf::Keyboard::Key::W)
      {
        input_direction = user_input_direction::UP;
      }
      else if (event.key.code == sf::Keyboard::Key::S)
      {
        input_direction = user_input_direction::DOWN;
      }
      else if (event.key.code == sf::Keyboard::Key::A)
      {
        input_direction = user_input_direction::LEFT;
      }
      else if (event.key.code == sf::Keyboard::Key::D)
      {
        input_direction = user_input_direction::RIGHT;
      }
      else if (event.key.code == sf::Keyboard::Space)
      {
        input_jump = true;
      }
      break;

    case gamestate::LOST:
      if (event.key.code == sf::Keyboard::Key::Enter)
      {
        level = 1;
        game_map.destroyTileMap();
        initGame();
      }
      break;

    case gamestate::WIN:
      if (event.key.code == sf::Keyboard::Key::Enter)
      {
        if (level == 2)
        {
          game_map.destroyTileMap();
          initLevel2();
        }
      }
  }
}

void Game::keyReleased(sf::Event event)
{
  switch (game_state)
  {
    case gamestate::GAME:
    {
      if (event.key.code == sf::Keyboard::Key::W
          or event.key.code == sf::Keyboard::Key::S
          or event.key.code == sf::Keyboard::Key::A
          or event.key.code == sf::Keyboard::Key::D)
      {
        input_direction = user_input_direction::NONE;
      }
      else if (event.key.code == sf::Keyboard::Key::Space)
      {
        input_jump = false;
      }
      break;
    }
  }
}

// Moves the player around and updates its position
void Game::updatePlayer(float delta)
{
  // Iterate through tiles and resolve horizontal and vertical movements
  // Only has to loop through all tiles twice (don't think that's efficient)

  // Check player horizontal input
  if (input_direction != user_input_direction::NONE)
  {
    if (input_direction == user_input_direction::LEFT)
    {
      player.move_to_speed = -player.getSpeed();
    }
    else if (input_direction == user_input_direction::RIGHT)
    {
      player.move_to_speed = player.getSpeed();
    }

    // Add to player.vector.x until they reach the max speed
    if (player.vector.x < player.move_to_speed and input_direction == user_input_direction::RIGHT)
    {
      player.vector.x += player.acceleration * delta;
    }
    else if (player.vector.x > player.move_to_speed and input_direction == user_input_direction::LEFT)
    {
      player.vector.x -= player.acceleration * delta;
    }
  }
  else if (input_direction == user_input_direction::NONE)
  {
    // Decelerate the player
    if (player.vector.x < 0)
    {
      player.vector.x += player.deceleration * delta;
      if (player.vector.x > 0)
      {
        player.vector.x = 0;
      }
    }
    else if (player.vector.x > 0)
    {
      player.vector.x -= player.deceleration * delta;
      if (player.vector.x < 0)
      {
        player.vector.x = 0;
      }
    }
  }

  // Check player vertical positions and handle jumping
  if (input_jump and !in_air)
  {
    in_air = true;
    player.vector.y = -player.getJumpForce() * delta;
    jump_sound.setPitch(getRandomPitch(base_pitch, pitch_range));
    jump_sound.play();
  }

  if (in_air)
  {
    player.vector.y += GRAVITY * delta;
  }
  else
  {
    player.vector.y = 0;
  }

  if (touched_roof)
  {
    player.vector.y = GRAVITY*delta;
    touched_roof = false;
  }

  in_air = true;

  // Move the player horizontally and resolve horizontal collisions
  player.getSprite()->move(player.vector.x, 0);
  for (int i = 0; i < game_map.getMapWidth(); i++)
  {
    for (int j = 0; j < game_map.getMapHeight(); j++)
    {
      if (game_map.tile_map[i][j].enabled and game_map.tile_map[i][j].collideable and player.touched(*game_map.tile_map[i][j].getSprite()))
      {
        float depth = 0.f;
        // Check if tile is the left wall of the player
        if (player.getSprite()->getPosition().x <= game_map.tile_map[i][j].getSprite()->getPosition().x + game_map.tile_map[i][j].getSprite()->getGlobalBounds().width
            and player.getSprite()->getPosition().x + player.getSprite()->getGlobalBounds().width >= game_map.tile_map[i][j].getSprite()->getPosition().x + game_map.tile_map[i][j].getSprite()->getGlobalBounds().width)
        {
          /*  Another check to see if the tile is to the left of the player
              Checks if midpoint of tile is between the side of the player
              If this is false, it will check if the top and bottom of the
              player are between the sides of the player
          */
          bool valid = false;
          if ((player.getSprite()->getPosition().y < game_map.tile_map[i][j].midpointy()) and (game_map.tile_map[i][j].midpointy() < player.getSprite()->getPosition().y + player.getSprite()->getGlobalBounds().height))
          {
            valid = true;
          }
          // Check top of tile
          else if ((player.getSprite()->getPosition().y < game_map.tile_map[i][j].getSprite()->getPosition().y) and (game_map.tile_map[i][j].getSprite()->getPosition().y < player.getSprite()->getPosition().y + player.getSprite()->getGlobalBounds().height))
          {
            valid = true;
          }
          // Check bottom of tile
          else if ((player.getSprite()->getPosition().y < game_map.tile_map[i][j].getSprite()->getPosition().y + game_map.tile_map[i][j].getSprite()->getGlobalBounds().height) and (game_map.tile_map[i][j].getSprite()->getPosition().y + game_map.tile_map[i][j].getSprite()->getGlobalBounds().height < player.getSprite()->getPosition().y + player.getSprite()->getGlobalBounds().height))
          {
            valid = true;
          }
          // Doing the same but for the player (player smaller than tile)
          else if ((game_map.tile_map[i][j].getSprite()->getPosition().y < player.midpointy()) and (player.midpointy() < game_map.tile_map[i][j].getSprite()->getPosition().y + game_map.tile_map[i][j].getSprite()->getGlobalBounds().height))
          {
            valid = true;
          }
          else if ((game_map.tile_map[i][j].getSprite()->getPosition().y < player.getSprite()->getPosition().y + player.getSprite()->getGlobalBounds().height) and (player.getSprite()->getPosition().y + player.getSprite()->getGlobalBounds().height < game_map.tile_map[i][j].getSprite()->getPosition().y + game_map.tile_map[i][j].getSprite()->getGlobalBounds().height))
          {
            valid = true;
          }
          else if ((game_map.tile_map[i][j].getSprite()->getPosition().y < player.getSprite()->getPosition().y) and (player.getSprite()->getPosition().y < game_map.tile_map[i][j].getSprite()->getPosition().y + game_map.tile_map[i][j].getSprite()->getGlobalBounds().height))
          {
            valid = true;
          }

          if (valid)
          {
            player.vector.x = 0;
            depth = player.touchedDepthLeft(*game_map.tile_map[i][j].getSprite());
          }
        }

        // Check if player is touching wall to its right
        else if (player.getSprite()->getPosition().x + player.getSprite()->getGlobalBounds().width >= game_map.tile_map[i][j].getSprite()->getPosition().x
            and player.getSprite()->getPosition().x <= game_map.tile_map[i][j].getSprite()->getPosition().x)
        {
          bool valid = false;
          if ((player.getSprite()->getPosition().y < game_map.tile_map[i][j].midpointy()) and (game_map.tile_map[i][j].midpointy() < player.getSprite()->getPosition().y + player.getSprite()->getGlobalBounds().height))
          {
            valid = true;
          }
          else if ((player.getSprite()->getPosition().y < game_map.tile_map[i][j].getSprite()->getPosition().y) and (game_map.tile_map[i][j].getSprite()->getPosition().y < player.getSprite()->getPosition().y + player.getSprite()->getGlobalBounds().height))
          {
            valid = true;
          }
          else if ((player.getSprite()->getPosition().y < game_map.tile_map[i][j].getSprite()->getPosition().y + game_map.tile_map[i][j].getSprite()->getGlobalBounds().height) and (game_map.tile_map[i][j].getSprite()->getPosition().y + game_map.tile_map[i][j].getSprite()->getGlobalBounds().height < player.getSprite()->getPosition().y + player.getSprite()->getGlobalBounds().height))
          {
            valid = true;
          }
          else if ((game_map.tile_map[i][j].getSprite()->getPosition().y < player.midpointy()) and (player.midpointy() < game_map.tile_map[i][j].getSprite()->getPosition().y + game_map.tile_map[i][j].getSprite()->getGlobalBounds().height))
          {
            valid = true;
          }
          else if ((game_map.tile_map[i][j].getSprite()->getPosition().y < player.getSprite()->getPosition().y + player.getSprite()->getGlobalBounds().height) and (player.getSprite()->getPosition().y + player.getSprite()->getGlobalBounds().height < game_map.tile_map[i][j].getSprite()->getPosition().y + game_map.tile_map[i][j].getSprite()->getGlobalBounds().height))
          {
            valid = true;
          }
          else if ((game_map.tile_map[i][j].getSprite()->getPosition().y < player.getSprite()->getPosition().y) and (player.getSprite()->getPosition().y < game_map.tile_map[i][j].getSprite()->getPosition().y + game_map.tile_map[i][j].getSprite()->getGlobalBounds().height))
          {
            valid = true;
          }

          if (valid)
          {
            player.vector.x = 0;
            depth = player.touchedDepthRight(*game_map.tile_map[i][j].getSprite());
          }
        }

        // Push player outside tile
        player.getSprite()->move(-depth, 0);
      }
    }
  }

  // Move the player vertically and resolve vertical collisions
  player.getSprite()->move(0, player.vector.y);
  for (int i = 0; i < game_map.getMapWidth(); i++)
  {
    for (int j = 0; j < game_map.getMapHeight(); j++)
    {
      if (game_map.tile_map[i][j].enabled and game_map.tile_map[i][j].collideable and player.touched(*game_map.tile_map[i][j].getSprite()))
      {
        float depth = 0.f;
        // Check if tile is the floor of the player
        if (player.getSprite()->getPosition().y + player.getSprite()->getGlobalBounds().height >= game_map.tile_map[i][j].getSprite()->getPosition().y
            and player.getSprite()->getPosition().y <= game_map.tile_map[i][j].getSprite()->getPosition().y)
        {
          // Validating whether this tile is actually the floor or the roof
          bool valid = false;
          if ((player.getSprite()->getPosition().x < game_map.tile_map[i][j].midpointx()) and (game_map.tile_map[i][j].midpointx() < player.getSprite()->getPosition().x + player.getSprite()->getGlobalBounds().width))
          {
            valid = true;
          }
          else if ((player.getSprite()->getPosition().x < game_map.tile_map[i][j].getSprite()->getPosition().x) and (game_map.tile_map[i][j].getSprite()->getPosition().x < player.getSprite()->getPosition().x + player.getSprite()->getGlobalBounds().width))
          {
            valid = true;
          }
          else if ((player.getSprite()->getPosition().x < game_map.tile_map[i][j].getSprite()->getPosition().x + game_map.tile_map[i][j].getSprite()->getGlobalBounds().width) and (game_map.tile_map[i][j].getSprite()->getPosition().x + game_map.tile_map[i][j].getSprite()->getGlobalBounds().width < player.getSprite()->getPosition().x + player.getSprite()->getGlobalBounds().width))
          {
            valid = true;
          }
          else if ((game_map.tile_map[i][j].getSprite()->getPosition().x < player.midpointx()) and (player.midpointx() < game_map.tile_map[i][j].getSprite()->getPosition().x + game_map.tile_map[i][j].getSprite()->getGlobalBounds().width))
          {
            valid = true;
          }
          else if ((game_map.tile_map[i][j].getSprite()->getPosition().x < player.getSprite()->getPosition().x + player.getSprite()->getGlobalBounds().width) and (player.getSprite()->getPosition().x + player.getSprite()->getGlobalBounds().width < game_map.tile_map[i][j].getSprite()->getPosition().x + game_map.tile_map[i][j].getSprite()->getGlobalBounds().width))
          {
            valid = true;
          }
          else if ((game_map.tile_map[i][j].getSprite()->getPosition().x < player.getSprite()->getPosition().x) and (player.getSprite()->getPosition().x < game_map.tile_map[i][j].getSprite()->getPosition().x + game_map.tile_map[i][j].getSprite()->getGlobalBounds().width))
          {
            valid = true;
          }

          if (valid)
          {
            in_air = false;
            depth = player.touchedDepthBottom(*game_map.tile_map[i][j].getSprite());
          }
        }

        // Check if tile is the roof of the player
        else if (player.getSprite()->getPosition().y <= game_map.tile_map[i][j].getSprite()->getPosition().y + game_map.tile_map[i][j].getSprite()->getGlobalBounds().height
            and player.getSprite()->getPosition().y + player.getSprite()->getGlobalBounds().height >= game_map.tile_map[i][j].getSprite()->getPosition().y + game_map.tile_map[i][j].getSprite()->getGlobalBounds().height)
        {

          bool valid = false;
          if ((player.getSprite()->getPosition().x < game_map.tile_map[i][j].midpointx()) and (game_map.tile_map[i][j].midpointx() < player.getSprite()->getPosition().x + player.getSprite()->getGlobalBounds().width))
          {
            valid = true;
          }
          else if ((player.getSprite()->getPosition().x < game_map.tile_map[i][j].getSprite()->getPosition().x) and (game_map.tile_map[i][j].getSprite()->getPosition().x < player.getSprite()->getPosition().x + player.getSprite()->getGlobalBounds().width))
          {
            valid = true;
          }
          else if ((player.getSprite()->getPosition().x < game_map.tile_map[i][j].getSprite()->getPosition().x + game_map.tile_map[i][j].getSprite()->getGlobalBounds().width) and (game_map.tile_map[i][j].getSprite()->getPosition().x + game_map.tile_map[i][j].getSprite()->getGlobalBounds().width < player.getSprite()->getPosition().x + player.getSprite()->getGlobalBounds().width))
          {
            valid = true;
          }
          else if ((game_map.tile_map[i][j].getSprite()->getPosition().x < player.midpointx()) and (player.midpointx() < game_map.tile_map[i][j].getSprite()->getPosition().x + game_map.tile_map[i][j].getSprite()->getGlobalBounds().width))
          {
            valid = true;
          }
          else if ((game_map.tile_map[i][j].getSprite()->getPosition().x < player.getSprite()->getPosition().x + player.getSprite()->getGlobalBounds().width) and (player.getSprite()->getPosition().x + player.getSprite()->getGlobalBounds().width < game_map.tile_map[i][j].getSprite()->getPosition().x + game_map.tile_map[i][j].getSprite()->getGlobalBounds().width))
          {
            valid = true;
          }
          else if ((game_map.tile_map[i][j].getSprite()->getPosition().x < player.getSprite()->getPosition().x) and (player.getSprite()->getPosition().x < game_map.tile_map[i][j].getSprite()->getPosition().x + game_map.tile_map[i][j].getSprite()->getGlobalBounds().width))
          {
            valid = true;
          }

          if (valid)
          {
            touched_roof = true;
            depth = player.touchedDepthTop(*game_map.tile_map[i][j].getSprite());
          }
        }

        // Push player outside tile
        player.getSprite()->move(0, -depth);
      }
    }
  }
}

// Checks when coins are touched and adds to player score
void Game::updateCoins()
{
  bool won = true;

  // Loop through tile map and check for coins
  for (int i = 0; i < game_map.getMapWidth(); i++)
  {
    for (int j = 0; j < game_map.getMapHeight(); j++)
    {
      // See if tile is enabled and collectable (is a coin)
      if (game_map.tile_map[i][j].enabled and game_map.tile_map[i][j].collectable)
      {
        won = false;
        // Check if player touches the coin
        if (player.touched(*game_map.tile_map[i][j].getSprite()))
        {
          coin_sound.setPitch(getRandomPitch(base_pitch, pitch_range));
          coin_sound.play();
          game_map.tile_map[i][j].enabled = false;
          score += 10;
          score_string = "Score: " + std::to_string(score * lives);
          score_text.setString(score_string);
        }
      }
    }
  }
}

// Initialises the game
void Game::initGame()
{
  game_map.constructTileMap("../Data/Tilemaps/map2.csv");
  score = 0;
  lives = 3;
  score_string = "Score: " + std::to_string(score);
  score_text.setString(score_string);
  life_text.setString(life_string);

  enemy1.setSpawnPoint(400, 587);
  enemy1.point0 = Vector2(337, 587);  // Left point
  enemy1.point1 = Vector2(490, 587);  // Right point

  enemy2.setSpawnPoint(280, 299);
  enemy2.point0 = Vector2(260, 299);
  enemy2.point1 = Vector2(412, 299);

  enemy1.getSprite()->setPosition(enemy1.getSpawnPoint().x, enemy1.getSpawnPoint().y);
  enemy2.getSprite()->setPosition(enemy2.getSpawnPoint().x, enemy2.getSpawnPoint().y);
  end_object.getSprite()->setPosition(75,217);

  player.vector.x = 0;  player.vector.y = 0;
  player.getSprite()->setPosition(l1spawn.x, l1spawn.y);

  game_state = gamestate::GAME;
}

// Initialises level 2
void Game::initLevel2()
{
  // Load level background (again)

  game_map.constructTileMap("../Data/Tilemaps/map3.csv");
  score_string = "Score: " + std::to_string(score * lives);
  score_text.setString(score_string);
  life_text.setString(life_string);

  enemy1.setSpawnPoint(200, 623);
  enemy1.point0 = Vector2(184, 623);
  enemy1.point1 = Vector2(434, 623);

  enemy1.getSprite()->setPosition(enemy1.getSpawnPoint().x, enemy1.getSpawnPoint().y);

  // enemy2.getSprite()->setPosition(enemy2.getSpawnPoint().x, enemy2.getSpawnPoint().y);


  end_object.getSprite()->setPosition(937,613);

  player.vector.x = 0;  player.vector.y = 0;
  player.getSprite()->setPosition(l2spawn.x, l2spawn.y);

  game_state = gamestate::GAME;
}

// Moves enemies
void Game::updateEnemy(Enemy &enemy, float delta)
{
  if (enemy.move_right)
  {
    enemy.vector.x = enemy.getSpeed() * delta;
  }
  else
  {
    enemy.vector.x = -enemy.getSpeed() * delta;
  }

  // Move enemy horizontally
  enemy.getSprite()->move(enemy.vector.x, 0);
  for (int i = 0; i < game_map.getMapWidth(); i++)
  {
    for (int j = 0; j < game_map.getMapHeight(); j++)
    {
      if (
        game_map.tile_map[i][j].enabled and
        game_map.tile_map[i][j].collideable and
        enemy.touched(*game_map.tile_map[i][j].getSprite()))
      {
        // Reflect enemy movement direction
        // enemy1.getSprite()->setPosition(game_map.tile_map[i][j].getSprite()->getPosition().x - enemy1.getSprite()->getGlobalBounds().width, enemy1.getSprite()->getPosition().y);
        enemy.move_right = !enemy.move_right;
        return;
      }
    }
  }
  // Check if enemy passes its patrol points
  if (enemy.getSprite()->getPosition().x <= enemy.point0.x)
  {
    enemy.move_right = true;
  }
  else if (enemy.getSprite()->getPosition().x >= enemy.point1.x)
  {
    enemy.move_right = false;
  }

  // Check if enemy hits the player
  if (enemy.touched(*player.getSprite()))
  {
    hurt_sound.play();
    lives--;
    life_string = "Lives: " + std::to_string(lives);
    life_text.setString(life_string);
    score_string = "Score: " + std::to_string(score * lives);
    score_text.setString(score_string);
    if (lives > 0)
    {
      // Respawn player
      player.vector.x = 0;  player.vector.y = 0;
      if (level == 1)
      {
        player.getSprite()->setPosition(l1spawn.x, l1spawn.y);
      }
      else if (level == 2)
      {
        player.getSprite()->setPosition(l2spawn.x, l2spawn.y);
      }
      enemy.getSprite()->setPosition(enemy.getSpawnPoint().x, enemy.getSpawnPoint().y);
    }
    else
    {
      // Game over!!!
      death_text.setString("Game over\nFinal score: "+ std::to_string(score) + "\nPress Enter to restart");
      death_text.setPosition(
        window.getSize().x * 0.5 - death_text.getGlobalBounds().width/2,
        window.getSize().y * 0.5 - death_text.getGlobalBounds().height/2);
      game_state = gamestate::LOST;
    }
  }
}

// Function simply checks whether the game has ended
void Game::updateEnd()
{
  std::string end_str;
  if (player.touched(*end_object.getSprite()))
  {
    complete_sound.play();
    level++;
    if (level == 2)
    {
      end_str = "Level complete\nPress enter to start next level";

    }
    else if (level > 2)
    {
      end_str = "You win!\nFinal score: " + std::to_string(score * lives);
    }

    end_text.setString(end_str);
    end_text.setPosition(
      window.getSize().x * 0.5 - end_text.getGlobalBounds().width/2,
      window.getSize().y * 0.5 - end_text.getGlobalBounds().height/2);
    game_state = gamestate::WIN;
  }
}

