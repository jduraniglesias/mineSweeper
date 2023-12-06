#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Random.h"
#ifndef BOARD_H
#define BOARD_H
using namespace std;

class Board {
public:
	vector<vector<Tile>> tiles;
	vector<vector<int>> testTiles;
	sf::Texture digitsText;
	sf::Sprite singledigits;
	sf::Sprite doubledigits;
	sf::Sprite tripledigits;
	sf::Texture toggleDebugText;
	sf::Sprite toggleDebug;
	sf::Texture face_happyText;
	sf::Texture face_winText;
	sf::Texture face_loseText;
	sf::Sprite face;
	sf::Texture revealedTileText;
	sf::Texture mineText;
	sf::Texture flagText;
	sf::Texture hiddenTileTextB;
	sf::Texture test_1Text;
	sf::Texture test_2Text;
	sf::Texture test_3Text;
	sf::Sprite test_1;
	sf::Sprite test_2;
	sf::Sprite test_3;
	bool gameOver;
	bool tDebug;
	int tilesH;
	int tilesR;
	int mines;
	int flags;
	int startGame;

	Board(Tile init) {
		ifstream inFile;
		inFile.open("boards/config.cfg");

		string sWidth;
		getline(inFile, sWidth);
		int Width = stoi(sWidth);

		string sHeight;
		getline(inFile, sHeight);
		int Height = stoi(sHeight);

		string mineTemp;
		getline(inFile, mineTemp);
		int mineCount = stoi(mineTemp);

		flags = 0;

		int windowHeight = (Height * 32);
		int windowWidth = (Width * 32);
		startGame = 0;

		for (int i = 0; i < Height; i++) {
			vector<Tile> temp;
			for (int j = 0; j < Width; j++) {
				temp.push_back(init);
			}
			tiles.push_back(temp);
		}

		gameOver = false;
		tDebug = false;

		toggleDebugText.loadFromFile("images/debug.png");
		toggleDebug.setTexture(toggleDebugText);
		toggleDebug.setPosition((windowWidth - 304), windowHeight);
		face_happyText.loadFromFile("images/face_happy.png");
		face_loseText.loadFromFile("images/face_lose.png");
		face_winText.loadFromFile("images/face_win.png");
		face.setTexture(face_happyText);
		face.setPosition((windowWidth - 450), windowHeight);
		digitsText.loadFromFile("images/digits.png");
		singledigits.setTexture(digitsText);
		singledigits.setPosition(42, windowHeight);
		doubledigits.setTexture(digitsText);
		doubledigits.setPosition(21, (windowHeight));
		tripledigits.setTexture(digitsText);
		tripledigits.setPosition(0, windowHeight);
		setTextRectThing();
		revealedTileText.loadFromFile("images/tile_revealed.png");
		mineText.loadFromFile("images/mine.png");
		flagText.loadFromFile("images/flag.png");
		hiddenTileTextB.loadFromFile("images/tile_hidden.png");
		test_1Text.loadFromFile("images/test_1.png");
		test_2Text.loadFromFile("images/test_2.png");
		test_3Text.loadFromFile("images/test_3.png");
		test_1.setTexture(test_1Text);
		test_2.setTexture(test_2Text);
		test_3.setTexture(test_3Text);
		test_1.setPosition((windowWidth - 235), windowHeight);
		test_2.setPosition((windowWidth - 165), windowHeight);
		test_3.setPosition((windowWidth - 95), windowHeight);
		setTiles();
	}

	void setTiles() {

		resetBoard();

		ifstream inFile;
		inFile.open("boards/config.cfg");

		string sWidth;
		getline(inFile, sWidth);
		int tempWidth = stoi(sWidth);

		string sHeight;
		getline(inFile, sHeight);
		int tempHeight = stoi(sHeight);
		for (int i = 0; i < tempHeight; i++) {
			for (int j = 0; j < tempWidth; j++) {
				tiles[i][j].tile.setPosition(j * 32, i * 32);
			}
		}

		randomMines();
	}

	void setTestTiles() {
		resetBoard();

		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 25; j++) {
				tiles[i][j].tile.setPosition(j * 32, i * 32);
			}
		}
		testMines();
	}

	void resetBoard() {
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
		flags = 0;
		setTextRectThing();
		for (int i = 0; i < tempHeight; i++) {
			for (int j = 0; j < tempWidth; j++) {
				tiles[i][j].tile.setTexture(hiddenTileTextB);
				tiles[i][j].isMine = false;
				tiles[i][j].isFlag = false;
				tiles[i][j].isClicked = false;
			}
		}
	}



	void drawWindow(sf::RenderWindow& window) {
		ifstream inFile;
		inFile.open("boards/config.cfg");

		string sWidth;
		getline(inFile, sWidth);
		int tempWidth = stoi(sWidth);

		string sHeight;
		getline(inFile, sHeight);
		int tempHeight = stoi(sHeight);

		for (int i = 0; i < tempHeight; i++) {
			for (int j = 0; j < tempWidth; j++) {
				window.draw(tiles[i][j].tile);
			}
		}
		window.draw(toggleDebug);
		window.draw(face);
		window.draw(singledigits);
		window.draw(doubledigits);
		window.draw(tripledigits);
		window.draw(test_1);
		window.draw(test_2);
		window.draw(test_3);

	}

	void randomMines() {
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
		for (int i = 0; i < mineCount; i++) {
			int mineX = Random::Int(0, tempWidth);
			int mineY = Random::Int(0, tempHeight);
			for (int k = 0; k < tempHeight; k++) {
				for (int j = 0; j < tempWidth; j++) {
					if (k == mineY && j == mineX) {
						tiles[k][j].isMine = true;
					}
				}
			}
		}
	}

	void testMines() {
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
		for (int k = 0; k < tempHeight; k++) {
			for (int j = 0; j < tempWidth; j++) {
				if (testTiles[k][j] == 1) {
					tiles[k][j].isMine = true;
				}

			}
		}
	}

	void toggleDebugFunc(sf::RenderWindow& window, bool d) {
		ifstream inFile;
		inFile.open("boards/config.cfg");

		string sWidth;
		getline(inFile, sWidth);
		int tempWidth = stoi(sWidth);

		string sHeight;
		getline(inFile, sHeight);
		int tempHeight = stoi(sHeight);
		for (int i = 0; i < tempHeight; i++) {
			for (int j = 0; j < tempWidth; j++) {
				if (d == true) {
					if (tiles[i][j].isMine && !tiles[i][j].isClicked) {
						tiles[i][j].tile.setTexture(mineText);
					}
				}
				else {
					if (tiles[i][j].isMine && !tiles[i][j].isClicked) {
						tiles[i][j].tile.setTexture(hiddenTileTextB);
					}
				}
				window.draw(tiles[i][j].tile);
			}
		}
	}

	void readTestFile(string fileName) {
		ifstream inFile;
		string linefromfile;
		inFile.open(fileName);
		testTiles.clear();
		for (int j = 0; j < 16; j++) {
			inFile >> linefromfile;
			vector<int> stuffandsuch;
			for (int i = 0; i < linefromfile.length(); i++) {
				int thing = (int)linefromfile[i] - '0';
				stuffandsuch.push_back(thing);
			}
			testTiles.push_back(stuffandsuch);
		}

	}

	void gameFunctions(sf::RenderWindow& window) {
		ifstream inFile;
		inFile.open("boards/config.cfg");

		string sWidth;
		getline(inFile, sWidth);
		int tempWidth = stoi(sWidth);

		string sHeight;
		getline(inFile, sHeight);
		int tempHeight = stoi(sHeight);
		
		if (gameOver == true) {
			for (int k = 0; k < tempHeight; k++) {
				for (int j = 0; j < tempWidth; j++) {
					if (tiles[k][j].isMine == true) {
						tiles[k][j].tile.setTexture(mineText);
					}
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sf::Vector2i tilePosition = sf::Mouse::getPosition(window);
				sf::FloatRect rect0 = face.getGlobalBounds();
				if (rect0.contains(tilePosition.x, tilePosition.y)) {
					face.setTexture(face_happyText);
					setTiles();
					drawWindow(window);
					gameOver = false;
				}
			}
		}

		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sf::Vector2i tilePosition = sf::Mouse::getPosition(window);
				if (tilePosition.x >= 0 && tilePosition.x < (tempWidth * 32) && tilePosition.y >= 0 && tilePosition.y < (tempHeight * 32)) {
					int x = tilePosition.x / 32;
					int y = tilePosition.y / 32;
					sf::FloatRect rect = tiles[y][x].tile.getGlobalBounds();
					if (rect.contains(tilePosition.x, tilePosition.y)) {
						if (tiles[y][x].isMine == true) {
							tiles[y][x].tile.setTexture(mineText);
							window.draw(tiles[y][x].tile);
							face.setTexture(face_loseText);
							gameOver = true;
							tiles[y][x].isClicked = true;

						}
						else if (!tiles[y][x].isClicked && !tiles[y][x].isMine && !tiles[y][x].isFlag) {
							tiles[y][x].tile.setTexture(revealedTileText);

						}
					}
				}
				
				sf::FloatRect rect2 = toggleDebug.getGlobalBounds();
				sf::FloatRect rect3 = face.getGlobalBounds();
				sf::FloatRect test1 = test_1.getGlobalBounds();
				sf::FloatRect test2 = test_2.getGlobalBounds();
				sf::FloatRect test3 = test_3.getGlobalBounds();
				
				if(rect2.contains(tilePosition.x, tilePosition.y)) {
					if (tDebug == false) {
						tDebug = true;
						toggleDebugFunc(window, tDebug);
					}
					else {
						tDebug = false;
						toggleDebugFunc(window, tDebug);
					}
				}

				
				else if(rect3.contains(tilePosition.x, tilePosition.y)) {
					face.setTexture(face_happyText);
					setTiles();
					drawWindow(window);
					gameOver = false;
				}

				else if (test1.contains(tilePosition.x, tilePosition.y)) {
					readTestFile("boards/testboard1.brd");
					setTestTiles();
				}

				else if (test2.contains(tilePosition.x, tilePosition.y)) {
					readTestFile("boards/testboard2.brd");
					setTestTiles();
				}
				else if (test3.contains(tilePosition.x, tilePosition.y)) {
					readTestFile("boards/testboard3.brd");
					setTestTiles();
				}
		}

		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			if (gameOver == true) {
				
			}
			else {
				sf::Vector2i tilePosition = sf::Mouse::getPosition(window);
				int x = tilePosition.x / 32;
				int y = tilePosition.y / 32;
				sf::FloatRect rect = tiles[y][x].tile.getGlobalBounds();
				if (rect.contains(tilePosition.x, tilePosition.y)) {
					if (!tiles[y][x].isFlag && !tiles[y][x].isClicked) {
						if (tDebug == true) {

						}
						else {
							tiles[y][x].tile.setTexture(flagText);
							tiles[y][x].isFlag = true;
							flags++;
							setTextRectThing();
						}
					}
					else if (tiles[y][x].isFlag && !tiles[y][x].isClicked) {
						if (tDebug == true) {
							
						}
						else {
							tiles[y][x].tile.setTexture(hiddenTileTextB);
							tiles[y][x].isFlag = false;
							flags--;
							setTextRectThing();
						}
						
					}
				}
			}
			
		}
		drawWindow(window);

	}

	void setTextRectThing() {

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

		singledigits.setTextureRect(sf::IntRect(21 * ((mineCount-flags) % 10), 0, 21, 32));
		doubledigits.setTextureRect(sf::IntRect(21 * (((mineCount-flags) / 10) % 10), 0, 21, 32));
		tripledigits.setTextureRect(sf::IntRect(21 * (((mineCount-flags) / 100) % 10), 0, 21, 32));
	}
};

#endif
