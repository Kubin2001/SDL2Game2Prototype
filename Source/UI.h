#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <optional>
#include "Font.h"
#include "TextureManager.h"
#include "Minimap.h"


class Button {
    private:
        static SDL_Texture* greyTexture;
        static SDL_Texture* whiteTexture;
        SDL_Texture* texture;
        SDL_Rect rectangle;
        std::string text;
        int textSize;
        int textStep;
        bool predefinedSize = true;

    public:
        static SDL_Texture* GetGreyTexture();
        static void SetGreyTexture(SDL_Texture * temp);
        static SDL_Texture* GetWhiteTexture();
        static void SetWhiteTexture(SDL_Texture* temp);


        SDL_Texture* GetTexture();

        void SetTexture(SDL_Texture* temp);
        std::string GetText();
        void SetText(std::string temptext);
        SDL_Rect* GetRectangle();

        int GetTextSize();
        void SetTextSize(int temp);
        int GetTextStep();
        void SetTextStep(int temp);
        bool GetPredefinedSize();
        void SetPredefinedSize(bool temp);

};


class UI
{
    private:
        SDL_Renderer* renderer;
        std::vector<Button> Buttons;

        bool showMap = false;
        int mapDelay = 0;


    public:
        Font* font;

        std::unique_ptr<Minimap> minimap;

        UI(SDL_Renderer* renderer);

        void LoadTextures(TextureManager* textureManager);

        void CreateSingleButton(int x, int y, int w, int h, int texture, std::optional<std::string> text, std::optional<int> textSize, std::optional<int> textStep, std::optional<bool> textsizePredefined);

        void Render();

        void RenderSingleButton(int index, int textureType);

        void OpenMap(SDL_Event event);

        ~UI();
};
