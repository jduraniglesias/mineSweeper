#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
using std::unordered_map;
using std::string;
using sf::Texture;
using sf::Sprite;

class TextureManager
{
	static unordered_map<string, Texture> textures;
	static void LoadTexture(string textureName);
public:
	static Texture& GetTexture(string textureName);
	// Call this once, at the end of main()
	static void Clear();
};

#endif