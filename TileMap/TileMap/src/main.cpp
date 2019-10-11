#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "TileMap.h"

enum Direction { None = -1, Up, Down, Left, Right };

void MoveCharacter(TileMap* map, sf::Vector2i& position, Direction dir);

int main() {

	std::unordered_map<std::string, std::unique_ptr<TileMap>> mapDictionary;

	std::ifstream file("../media/Maps/World.maplist");
	if (file.is_open()) {
		std::string mapName;
		while (std::getline(file, mapName)) {
			auto map = std::make_unique<TileMap>();

			if (!map->LoadFromFile("../media/Maps/" + mapName + ".map")) {
				std::cout << "Could not load " << mapName << ".map" << std::endl;
				return EXIT_FAILURE;
			}

			mapDictionary[mapName] = std::move(map);
		}
	}

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

	sf::RenderWindow window(sf::VideoMode(384, 256, 32), "Tile Map");
	window.setFramerateLimit(30);

	auto mapIter = mapDictionary.find("Field");
	if (mapIter == mapDictionary.end()) {
		std::cout << "Didn't find the Field map" << std::endl;
		return EXIT_FAILURE;
	}

	// Have a start location for the game (this will be set when a game is loaded in the future)
	sf::Vector2i characterPosition(1, 1);
	sf::Sprite characterSprite;
	characterSprite.setTexture(playerTexture);

	auto map = mapIter->second.get();

	Direction dir = Direction::None;
	bool enableWarp = true;

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
					dir = Direction::Up;
					enableWarp = true;
				}
				else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
					dir = Direction::Left;
					enableWarp = true;
				}
				else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
					dir = Direction::Down;
					enableWarp = true;
				}
				else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
					dir = Direction::Right;
					enableWarp = true;
				}
			}
		}

		// Update
		MoveCharacter(map, characterPosition, dir);

		// On Warp?
		auto tile = map->GetTileData(map->GetMapTile(characterPosition.x, characterPosition.y));
		if (tile.IsWarp && enableWarp) {
			std::cout << "Warp!" << std::endl;

			auto warp = map->GetWarpData(characterPosition.x, characterPosition.y);
			std::cout << "Moving to " << warp.MapName << " " << warp.ToX << " " << warp.ToY << std::endl;

			auto mapIter = mapDictionary.find(warp.MapName);
			if (mapIter != mapDictionary.end()) {
				map = mapIter->second.get();
				characterPosition.x = warp.ToX;
				characterPosition.y = warp.ToY;

				enableWarp = false;
			}
		}

		// Draw
		window.clear();

		for (int i = 0; i < map->GetHeight(); ++i) {
			for (int j = 0; j < map->GetWidth(); ++j) {
				int tile = map->GetMapTile(j, i);

				tileSprite.setPosition(static_cast<float>(j * map->GetTileSize()), static_cast<float>(i * map->GetTileSize()));
				tileSprite.setTextureRect(sf::IntRect(tile * map->GetTileSize() + 1, 0, map->GetTileSize(), map->GetTileSize()));
				window.draw(tileSprite);
			}
		}

		// Suggests a "get sprite size" function
		sf::Vector2f spritePosition = sf::Vector2f(static_cast<float>(characterPosition.x * 32), static_cast<float>(characterPosition.y * 32));
		characterSprite.setPosition(spritePosition);

		window.draw(characterSprite);
		
		window.display();

		dir = Direction::None;
	}

	return EXIT_SUCCESS;
}

void MoveCharacter(TileMap* map, sf::Vector2i& position, Direction dir) {
	if (dir == Direction::Up) {
		if (position.y > 0) {
			--position.y;

			Tile tile = map->GetTileData(map->GetMapTile(position.x, position.y));
			if (tile.IsSolid) {
				++position.y;
			}
		}
	}
	else if (dir == Direction::Down) {
		if (position.y < map->GetHeight() - 1) {
			++position.y;

			Tile tile = map->GetTileData(map->GetMapTile(position.x, position.y));
			if (tile.IsSolid) {
				--position.y;
			}
		}
	}
	else if (dir == Direction::Left) {
		if (position.x > 0) {
			--position.x;

			Tile tile = map->GetTileData(map->GetMapTile(position.x, position.y));
			if (tile.IsSolid) {
				++position.x;
			}
		}
	}
	else if (dir == Direction::Right) {
		if (position.x < map->GetWidth() - 1) {
			++position.x;

			Tile tile = map->GetTileData(map->GetMapTile(position.x, position.y));
			if (tile.IsSolid) {
				--position.x;
			}
		}
	}
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

	Insights: Palettizing the tile data instead storing that data tile by tile is a waste of space.
		The tile palette allows for a map to only deal with Id's and has a further benefit of allowing the tile
		texture to be changed in design time.  An example problem would be the implemenation of a weather and
		seasons system.  Another example would be the introduction of biomes (such as in Minecraft).

	10/11/2019a
	Replaced the Id value in the Tile Palette to a Tile structure which has the following values
	Tile struct
	-Name
	-Id
	-IsSolid

	Updated movement code to revert the character to the last position it moved if the tile IsSolid

	10/11/2019b
	Created a Map Dictionary which contains Map data for multiple maps.
	Made the Map Dictionary load from a file of Map names

	Updated the Tile Map to implement Warp tiles.
	Optimized map loading, ensuring that important map data is on the same line as the data being loaded

	Gotchas: If you warp onto another warp tile, the tile will warp to the new warp warp location.  If this lands 
		on the first warp, this will begin an infinite loop.  That said, upon arrival in the new area, warps need
		to be disabled until the player moves.

	Insights: The "warp" tile is an example of a concept called a "trigger".  A future feature would be to
		make the "warp" tile generic and allow for a callback or a scripted event to be passed into the trigger.
		Alternatively, trigger tiles could be removed enitrely and made into an invisible object that rests on top
		of the map (perhaps a trigger layer), can be represented by a variety of different shapes and can work 
		with a collision detection system.

	Polish:
		Add a transition animations between maps which pauses the game state until the transition is complete
*/