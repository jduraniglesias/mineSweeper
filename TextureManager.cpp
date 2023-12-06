#include "TextureManager.h"

// "Redeclare" the variable, so this file knows it exists and can use it
unordered_map<string, Texture> TextureManager::textures;

void TextureManager::LoadTexture(string textureName) {
	string path = "images/";
	path += textureName + ".png";
	textures[textureName].loadFromFile(path);
}

Texture& TextureManager::GetTexture(string textureName) {
	if (textures.find(textureName) == textures.end())
		LoadTexture(textureName);
	return textures[textureName];
}

void TextureManager::Clear() {
	// Get rid of all stored objects
	textures.clear();
}

