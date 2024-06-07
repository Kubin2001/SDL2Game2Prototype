#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include "Font.h"


class ButtonInfo {
    private:
        SDL_Rect rectangle;
        std::string text = "";

    public:
        std::string GetText();
        void SetText(std::string temptext);
        SDL_Rect* GetRectangle();

};

class Button {
    private:
        SDL_Rect rectangle;
        std::string text;
        int textSize;
        int textStep;
        bool predefinedSize = true;

    public:
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

class Hearth {
    private:
        SDL_Rect rectangle;

    public:
        SDL_Rect* GetRectangle();

};

class UI
{
    private:
        SDL_Renderer* renderer;
        SDL_Texture * texturehearth = nullptr;
        SDL_Texture* textureButton = nullptr;
        SDL_Texture* textureButtonInfo = nullptr;
        std::vector<Hearth> HP;
        std::vector<Button> Buttons;
        ButtonInfo* buttonInfo;
        int menuType = 0;
        int score = 0;

    public:
        Font* font;

        UI(SDL_Renderer* renderer);

        SDL_Texture *GetTextureHearth();
        void SetTextureHearth(SDL_Texture* temptex);
        SDL_Texture* GetTextureButton();
        void SetTextureButton(SDL_Texture* temptex);
        SDL_Texture* GetTextureButtonInfo();
        void SetTextureButtonInfo(SDL_Texture* temptex);
        int GetScore();
        void SetScore(int temp);

        std::vector<Hearth> &getHP();
        void CreateHearths();
        void RemoveHearths();
        void AddHearth();

        void CreateButton();

        void CreateSingleButton(int x, int y, int w, int h, std::string text, int textSize, int textStep, bool sizePredefined);

        void CreateButtonInfo(int x, int y, int w, int h, std::string text, int textSize, int textStep);

        void Render();
        void RenderHP();
        void RenderScore();
        void RenderButton();

        void RenderSingleButton(int index, int textureType);

        void CreateScoreButton();

        void OnClick(SDL_Event event);

        void OnClickEditor(int &number, SDL_Event event);

        ~UI();
};
