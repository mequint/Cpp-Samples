#include <iostream>
#include <SFML/Graphics.hpp>

#include "TileMap.h"

int main() {
	TileMap map;

	if (map.LoadFromFile("../media/Maps/sample1.map")) {
		for (int i = 0; i < map.GetHeight(); ++i) {
			for (int j = 0; j < map.GetWidth(); ++j) {
				std::cout << map.GetMapTile(j, i);
			}

			std::cout << std::endl;
		}
	}

	sf::RenderWindow window(sf::VideoMode(256, 256, 32), "Tile Map");
	window.setFramerateLimit(30);
	
	sf::Texture tileTexture;
	if (!tileTexture.loadFromFile("../media/Textures/Tiles.png")) {
		std::cout << "Failed to load tiles texture..." << std::endl;
		return EXIT_FAILURE;
	}

	sf::Sprite tileSprite;
	tileSprite.setTexture(tileTexture);

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("../media/Textures/StickFigure.png")) {
		std::cout << "Failed to load stick figure texture..." << std::endl;
		return EXIT_FAILURE;
	}

	// Have a start location for the game (this will be set when a game is loaded in the future)
	sf::Vector2i characterPosition(1, 1);
	sf::Sprite characterSprite;
	characterSprite.setTexture(playerTexture);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}

				if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
					if (characterPosition.y > 0) {
						--characterPosition.y;
						
						Tile tile = map.GetTileData(map.GetMapTile(characterPosition.x, characterPosition.y));
						if (tile.IsSolid) {
							++characterPosition.y;
						}
					}
				}
				else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
					if (characterPosition.x > 0) {
						--characterPosition.x;

						Tile tile = map.GetTileData(map.GetMapTile(characterPosition.x, characterPosition.y));
						if (tile.IsSolid) {
							++characterPosition.x;
						}
					}
				}
				else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
					if (characterPosition.y < map.GetHeight() - 1) {
						++characterPosition.y;

						Tile tile = map.GetTileData(map.GetMapTile(characterPosition.x, characterPosition.y));
						if (tile.IsSolid) {
							--characterPosition.y;
						}
					}
				}
				else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
					if (characterPosition.x < map.GetWidth() - 1) {
						++characterPosition.x;

						Tile tile = map.GetTileData(map.GetMapTile(characterPosition.x, characterPosition.y));
						if (tile.IsSolid) {
							--characterPosition.x;
						}
					}
				}
			}
		}

		window.clear();

		for (int i = 0; i < map.GetHeight(); ++i) {
			for (int j = 0; j < map.GetWidth(); ++j) {
				int tile = map.GetMapTile(j, i);

				tileSprite.setPosition(static_cast<float>(j * map.GetTileSize()), static_cast<float>(i * map.GetTileSize()));
				tileSprite.setTextureRect(sf::IntRect(tile * map.GetTileSize() + 1, 0, map.GetTileSize(), map.GetTileSize()));
				window.draw(tileSprite);
			}
		}

		// Suggests a "get sprite size" function
		sf::Vector2f spritePosition = sf::Vector2f(static_cast<float>(characterPosition.x * 32), static_cast<float>(characterPosition.y * 32));
		characterSprite.setPosition(spritePosition);

		window.draw(characterSprite);
		
		window.display();
	}

	return EXIT_SUCCESS;
}

// Phase 1:

/*  10/10/2019
	Created the initial Tile Map class
	-Stores the tile size
	-Stores the map width and height
	-Stores the tile palette data
	-Stores a vector of tile ids
	
	Loaded a texture that visually representation the Tiles
	Displays the texture on a sprite using the Id and the Tile Size to determine which tile is displayed

	Loaded a texture that represents a character moving on the map
	Assigned a tile map position to the sprite
	Draw the sprite based on the characters position on the map

	10/11/2019
	Replaced the Id value in the Tile Palette to a Tile structure which has the following values
	Tile struct
	-Name
	-Id
	-IsSolid

	Updated movement code to revert the character to the last position it moved if the tile IsSolid
*/