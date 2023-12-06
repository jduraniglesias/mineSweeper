#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#ifndef TILE_H
#define TILE_H
using namespace std;

class Tile {
public:
	sf::Texture hiddenTileText;
	sf::Sprite tile;
	int mines;
	int x;
	int y;
	bool isFlag;
	bool isMine;
	bool isClicked;
	bool debug;

	Tile() {
		hiddenTileText.loadFromFile("images/tile_hidden.png");
		tile.setTexture(hiddenTileText);
		isFlag = false;
		isMine = false;
		isClicked = false;
		debug = false;
	}
		
};
#endif