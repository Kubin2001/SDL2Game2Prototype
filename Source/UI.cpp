#include <iostream>
#include <string>
#include <fstream>
#include <SDL.h>
#include "UI.h"
#include "Colision.h"
#include "Font.h"

extern int windowType;
extern int windowWidth;
extern int windowHeight;

UI::UI(SDL_Renderer *renderer){
    font = new Font();
    buttonInfo = new ButtonInfo();
    this->renderer = renderer;
}

SDL_Texture* UI::GetTextureHearth() {return texturehearth;}

void UI::SetTextureHearth(SDL_Texture * temptex) {texturehearth = temptex;}


SDL_Texture* UI::GetTextureButton() {return textureButton;}

void UI::SetTextureButton(SDL_Texture* temptex) {textureButton = temptex;}

SDL_Texture* UI::GetTextureButtonInfo() {return textureButtonInfo;}

void UI::SetTextureButtonInfo(SDL_Texture* temptex) {textureButtonInfo = temptex;}

std::vector<Hearth>& UI::getHP() {return HP;}

int UI::GetScore() {
    return score;
}
void UI::SetScore(int temp) {
    score = temp;
}

void UI::Render() {
    if (windowType == 1) {
        RenderButton();
        for (size_t  i = 0; i < Buttons.size(); i++)
        {
            switch (Buttons[i].GetPredefinedSize())
            {
                 case 0:{
                    int size = Buttons[i].GetRectangle()->w / Buttons[i].GetText().length() - 2;
                    font->RenderText(renderer, Buttons[i].GetText(), Buttons[i].GetRectangle()->x, Buttons[i].GetRectangle()->y, size, size, size + 2);
                    break;
                 }

                 case 1:{
                    font->RenderText(renderer, Buttons[i].GetText(), Buttons[i].GetRectangle()->x, Buttons[i].GetRectangle()->y,
                        Buttons[i].GetTextSize(), Buttons[i].GetTextSize(), Buttons[i].GetTextStep());
                    break;
                 }

            }
            
        }
    }
    else if (windowType == 2) {
        RenderHP();
        RenderScore();
    }

}

void UI::RenderHP() {
    for (int i = 0; i < HP.size(); i++) {
        SDL_RenderCopy(renderer, texturehearth, NULL, HP[i].GetRectangle());
    }
}

void UI::RenderScore() {
    font->RenderText(renderer,"SCORE:" + std::to_string(score), 1000, 50, 40, 40, 42);
}

void UI::RenderButton() {
    for (int i = 0; i < Buttons.size(); i++)
    {
        SDL_RenderCopy(renderer, textureButton, NULL, Buttons[i].GetRectangle());
    }

}

void UI::CreateHearths() {
    Hearth tempHP;
    int xCord = 20;
    int yCord = 20;
    for (int i = 0; i < 6; i++)
    {
        HP.push_back(tempHP);
        HP[HP.size() - 1].GetRectangle()->x = xCord;
        HP[HP.size() - 1].GetRectangle()->y = yCord;
        HP[HP.size() - 1].GetRectangle()->w = 40;
        HP[HP.size() - 1].GetRectangle()->h = 40;

        xCord += 50;
    }
}

void UI::RemoveHearths() {
    if (!HP.empty()) {
        HP.pop_back();
    }

}

void UI::AddHearth() {
    Hearth hearth;
    if (HP.size() < 6) {
        HP.push_back(hearth);
        HP[HP.size() - 1].GetRectangle()->x = HP[HP.size() - 2].GetRectangle()->x + 50;
        HP[HP.size() - 1].GetRectangle()->y = HP[HP.size() - 2].GetRectangle()->y;
        HP[HP.size() - 1].GetRectangle()->w = HP[HP.size() - 2].GetRectangle()->w;
        HP[HP.size() - 1].GetRectangle()->h = HP[HP.size() - 2].GetRectangle()->h;
    }
}

void UI::CreateButton() {
    int xPos = 0;
    int yPos = 0;
    Button button;
    switch (menuType)
    {
        case 0: { //Main menu
            std::ifstream levelFile("Data/menu_main.txt");
            std::string line;
            xPos = 600;
            yPos = 200;
            for (int i = 0; i < 4; i++)
            {
                std::getline(levelFile, line);
                CreateSingleButton(xPos, yPos, 200, 50, line, 29, 30,false);
                yPos += 150;
            }
        }
            break;
        case 1: { //Levels Selector
            std::ifstream levelFile("Data/menu_levels.txt");
            std::string line;
            xPos = 100;
            yPos = 200;
            for (int i = 0; i < 11; i++)
            {
                std::getline(levelFile, line);
                CreateSingleButton(xPos, yPos, 200, 100, line, 29, 30, false);
                xPos += 250;
                if (i == 4) {
                    xPos = 100;
                    yPos += 300;
                }
                if (i == 9) {
                    xPos = 600;
                    yPos = 650;
                }

            }
        }
            break;
        case 2: { //Player Levels Selector 
            std::ifstream levelFile("Data/menu_player_high_scores.txt");
            std::string line;
            xPos = 100;
            yPos = 200;
            for (int i = 0; i < 11; i++)
            {
                std::getline(levelFile, line);
                CreateSingleButton(xPos, yPos, 200, 100, line, 29, 30,false);
                xPos += 250;
                if (i == 4) {
                    xPos = 100;
                    yPos += 300;
                }
                if (i == 9) {
                    xPos = 600;
                    yPos = 650;
                }

            }
        }
           break;

        case 3: { //Score Button
            CreateScoreButton();
            CreateSingleButton(650, 500, 100, 40, "BACK", 29, 30, false);
        }
          break;
    }
}

void UI::CreateSingleButton(int x, int y, int w, int h, std::string text, int textSize, int textStep,bool sizePredefined) {
    Button button;
    Buttons.push_back(button);
    Buttons.back().GetRectangle()->x = x;
    Buttons.back().GetRectangle()->y = y;
    Buttons.back().GetRectangle()->w = w;
    Buttons.back().GetRectangle()->h = h;
    Buttons.back().SetText(text);
    Buttons.back().SetTextSize(textSize);
    Buttons.back().SetTextStep(textStep);
    Buttons.back().SetPredefinedSize(sizePredefined);
}

void UI::RenderSingleButton(int index, int textureType) {
    switch (textureType)
    {
        case 1:
            SDL_RenderCopy(renderer, textureButton, NULL, Buttons[index].GetRectangle());
            break;
        case 2:
            SDL_RenderCopy(renderer, textureButtonInfo, NULL, Buttons[index].GetRectangle());
            break;
    }
    if (Buttons[index].GetText() != "") {
        font->RenderText(renderer, Buttons[index].GetText(), Buttons[index].GetRectangle()->x,
            Buttons[index].GetRectangle()->y, Buttons[index].GetTextSize(), Buttons[index].GetTextSize(), Buttons[index].GetTextStep());
    }
}


void UI::CreateButtonInfo(int x, int y , int w, int h,std::string text,int textSize, int textStep) {
    buttonInfo->GetRectangle()->x = x;
    buttonInfo->GetRectangle()->y = y;
    buttonInfo->GetRectangle()->w = w;
    buttonInfo->GetRectangle()->h = h;
    buttonInfo->SetText(text);

    SDL_RenderCopy(renderer, textureButtonInfo, NULL, buttonInfo->GetRectangle());
    font->RenderText(renderer, buttonInfo->GetText(), buttonInfo->GetRectangle()->x, buttonInfo->GetRectangle()->y, textSize, textSize, textStep);
    SDL_RenderPresent(renderer);
}

void UI::CreateScoreButton() {
}

void UI::OnClick(SDL_Event event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        SDL_Rect mouse;
        Uint32 mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);
        mouse.w = 1;
        mouse.h = 1;
    }

}

void UI::OnClickEditor(int &number,SDL_Event event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        SDL_Rect mouse;
        Uint32 mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);
        mouse.w = 1;
        mouse.h = 1;
        for (int i = 0; i < Buttons.size(); i++)
        {
            if (SimpleCollision(mouse, *Buttons[i].GetRectangle()) == 1) {
                number = i;
            }
        }
    }
}


SDL_Rect* Hearth::GetRectangle() {
    return &rectangle;
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

SDL_Rect* ButtonInfo::GetRectangle() {
    return &rectangle;
}

void ButtonInfo::SetText(std::string temptext) {
    text = temptext;
}

std::string ButtonInfo::GetText() {
    return text;
}

UI::~UI() {
    delete font;
    delete buttonInfo;
    SDL_DestroyTexture(texturehearth);
    SDL_DestroyTexture(textureButton);
    SDL_DestroyTexture(textureButtonInfo);
    if (!Buttons.empty()) {
        Buttons.clear();
    }
    if (!HP.empty()) {
        HP.clear();
    }
}
