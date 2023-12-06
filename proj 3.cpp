#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Board.h"
#include "TextureManager.h"

using namespace std;


int main()
{

	ifstream inFile;
	inFile.open("boards/config.cfg");

	string sWidth;
	getline(inFile, sWidth);
	int tempWidth = stoi(sWidth);

	string sHeight;
	getline(inFile, sHeight);
	int tempHeight = stoi(sHeight);

	string mineTemp;
	getline(inFile, mineTemp);
	int mineCount = stoi(mineTemp);

	unsigned int width = tempWidth * 32;
	unsigned int height = (tempHeight * 32) + 100;

	int tiles = tempHeight * tempWidth;

	
	sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper");
	Tile init;
	Board board(init);
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();
		board.gameFunctions(window);
		window.display();
		
		
	}
	
	
	
	return 0;
}

