#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>   
#include "Player.h"
#include "TextureManager.h"

class Mobs;

class Player;

class Particle {
    protected:
        SDL_Rect rectangle;
        SDL_Texture* texture;
        int direction = 1;
        int speedX = 0;
        int speedY = 0;
        double angle = 0;
        int lifeTime = 0;
        bool renderable = false;
    public:
        virtual SDL_Rect* GetRectangle();
        virtual SDL_Texture* GetTexture();
        virtual void SetTexture(SDL_Texture *temptex);
        virtual int GetDirection();
        virtual void SetDirection(int temp);
        virtual int GetSpeedX();
        virtual void SetSpeedX(int temp);
        virtual int GetSpeedY();
        virtual void SetSpeedY(int temp);
        virtual double GetAngle();
        virtual void SetAngle(double temp);
        virtual int GetLifeTime();
        virtual void SetLifeTime(int temp);
        virtual bool GetRenderable();
        virtual void SetRenderable(bool temp);
        virtual void Move();

};

class EnemyParticle : public Particle {
    public:
        EnemyParticle(SDL_Rect rect, int direction, int speedX,int speedY, int lifeTime, double angle) {
            this->direction = direction;
            this->speedX = speedX;
            this->speedY = speedY;
            this->lifeTime = lifeTime;
            this->angle = angle;
            this->rectangle = rect;
        }
};


class PlayerParticle : public Particle {
    public:
        PlayerParticle(SDL_Rect rect, int direction, int speedX, int speedY, int lifeTime, double angle) {
            this->direction = direction;
            this->speedX = speedX;
            this->speedY = speedY;
            this->lifeTime = lifeTime;
            this->angle = angle;
            this->rectangle = rect;
        }
};

class ParticlesManager
{
    private:
        SDL_Renderer* renderer;
        std::vector<PlayerParticle> PlayerParticles;
        std::vector<EnemyParticle> EnemyParticles;

    public:
        ParticlesManager(SDL_Renderer* renderer);
        
        void LoadTextures(TextureManager* tetxureManager);

        void Render(SDL_Rect camRect);

        void CreatePlayerParticle(SDL_Rect rect, int direction, int speedX, int speedY, int lifeTime, std::string textureName, double angle, TextureManager* textureManager);

        void CreateEnemyParticle(SDL_Rect rect, int direction, int speedX, int speedY, int lifeTime, std::string textureName, double angle, TextureManager* textureManager);

        template <typename T>
        void CheckColision(std::vector<T>& mobs,Player* player, SDL_Rect camRect);

        template <typename T>
        void CheckColisionMobs(std::vector<T>& mobs, SDL_Rect camRect);

        void CheckColisionPlayer(Player* player, SDL_Rect camRect);

        void EndLifeTime();

        void MoveParticles(const Uint8* state, Player* player);

        void MoveParticlesPlayer(const Uint8* state, Player* player);

        void MoveParticlesEnemy(const Uint8* state, Player* player);

        ~ParticlesManager();
};
