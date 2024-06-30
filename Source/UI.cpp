#include <iostream>
#include <string>
#include <fstream>
#include <SDL.h>
#include <optional>
#include "UI.h"
#include "Colision.h"
#include "Font.h"
#include "Minimap.h"

extern int windowType;
extern int windowWidth;
extern int windowHeight;

//BUTTON


SDL_Texture* Button::greyTexture = nullptr;
SDL_Texture* Button::whiteTexture = nullptr;


SDL_Texture* Button::GetGreyTexture(){
    return greyTexture;
}

void Button::SetGreyTexture(SDL_Texture* temp) {
    greyTexture = temp;
}

SDL_Texture* Button::GetWhiteTexture() {
    return whiteTexture;
}

void Button::SetWhiteTexture(SDL_Texture* temp) {
    whiteTexture = temp;
}

SDL_Texture* Button::GetTexture() {
    return texture;
}

void Button::SetTexture(SDL_Texture* temp) {
    texture = temp;
}

SDL_Rect* Button::GetRectangle() {
    return &rectangle;
}

void Button::SetText(std::string temptext) {
    text = temptext;
}

std::string Button::GetText() {
    return text;
}

int Button::GetTextSize() {
    return textSize;
}
void Button::SetTextSize(int temp) {
    textSize = temp;
}
int Button::GetTextStep() {
    return textStep;
}
void Button::SetTextStep(int temp) {
    textStep = temp;
}

bool Button::GetPredefinedSize() {
    return predefinedSize;
}
void Button::SetPredefinedSize(bool temp) {
    predefinedSize = temp;
}
//BUTTON


UI::UI(SDL_Renderer *renderer){
    font = new Font();
    this->renderer = renderer;
    this->minimap = std::make_unique<Minimap>(renderer);
}


void UI::LoadTextures() {
    TextureManager::LoadMultipleTextures("Textures/Interface");
    Button::SetGreyTexture(TextureManager::GetTextureByName("buttonGrey"));
    Button::SetWhiteTexture(TextureManager::GetTextureByName("buttonWhite"));
}

void UI::Render() {
    for (auto it : Buttons) {
        SDL_RenderCopy(renderer, it.GetTexture(), NULL, it.GetRectangle());
    }
    if (showMap) {
        minimap->Render();
    }
}


void UI::CreateSingleButton(int x, int y, int w, int h, int texture, std::optional<std::string> text, std::optional<int> textSize, std::optional<int> textStep, std::optional<bool> textsizePredefined) {
    Button button;
    Buttons.push_back(button);
    Buttons.back().GetRectangle()->x = x;
    Buttons.back().GetRectangle()->y = y;
    Buttons.back().GetRectangle()->w = w;
    Buttons.back().GetRectangle()->h = h;
    switch (texture)
    {
        case 1:
            Buttons.back().SetTexture(Button::GetGreyTexture());
            break;
        case 2:
            Buttons.back().SetTexture(Button::GetWhiteTexture());
            break;
    }
    if (text.has_value()) {
        Buttons.back().SetText(text.value());
        Buttons.back().SetTextSize(textSize.value());
        Buttons.back().SetTextStep(textStep.value());
        Buttons.back().SetPredefinedSize(textsizePredefined.value());
    }
}

void UI::RenderSingleButton(int index, int textureType) {
    switch (textureType)
    {
        case 1:
            //SDL_RenderCopy(renderer, textureButton, NULL, Buttons[index].GetRectangle());
            break;
        case 2:
            //SDL_RenderCopy(renderer, textureButtonInfo, NULL, Buttons[index].GetRectangle());
            break;
    }
    if (Buttons[index].GetText() != "") {
        font->RenderText(renderer, Buttons[index].GetText(), Buttons[index].GetRectangle()->x,
            Buttons[index].GetRectangle()->y, Buttons[index].GetTextSize(), Buttons[index].GetTextSize(), Buttons[index].GetTextStep());
    }
}

void UI::OpenMap(SDL_Event event) {
    if (mapDelay == 0) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.scancode == SDL_SCANCODE_M) {
                if (showMap) {
                    Buttons.clear();
                    showMap = false;
                }
                else
                {
                    CreateSingleButton(25, 25, windowWidth - 50,windowHeight - 50 ,1, std::nullopt, std::nullopt, std::nullopt, std::nullopt);
                    showMap = true;
                }

            }
        }
    }
    else
    {
        mapDelay--;
    }
}

UI::~UI() {
    delete font;
    if (!Buttons.empty()) {
        Buttons.clear();
    }
}
