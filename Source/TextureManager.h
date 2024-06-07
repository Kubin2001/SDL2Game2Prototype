#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include "SDL_image.h"


class Texture {
	private:
		SDL_Texture* texture;
		std::string name = "";
	public:
		SDL_Texture* GetTexture();

		void SetTexture(SDL_Texture* temptex);

		std::string GetName();

		void SetName(std::string temp);

		bool operator < (Texture& other) {
			return name < other.name;
		}
};

bool TetxureSortHelper(Texture &temp1, Texture &temp2);


SDL_Texture* load(const char* file, SDL_Renderer* ren);


void LoadMultipleTextures(std::vector<Texture>&vector, const std::string& directory, SDL_Renderer* renderer);