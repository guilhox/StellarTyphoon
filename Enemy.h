#include "ShotPattern.h"
#include <ctime>
#include <math.h>

class Enemy
{
      public:
              Enemy (hgeSprite *espr, int spawnTime, float ox, float oy, float fx, float fy, float speed, int health);
              virtual void update();
             // virtual void spawn(float sx, float sy, int health);
              virtual void moveTo(float fx, float fy, float speed);
              virtual void setShotPattern(ShotPattern *pattern);
              //virtual void setVariableShotPattern(hgeSprite *sspr, float n1, float n2, float sspeed, float dspeed, float theta, float dtheta, int type, float accel, float rotation, float alpha);
              void damage(int power);
              virtual ShotPattern* getShotPattern();
              hgeSprite* getSprite();
              float getSpeed();
              float getX();
              float getY();
              bool isAlive();
              bool exists();
              void setExist(bool e);
              int getHealth();
              virtual void die();
              
      protected:
              float distance(float x1, float y1, float x2, float y2);
              hgeSprite *espr;
              ShotPattern *pattern;
              int health;
              int timer;
              int spawnTime;
              int duration;
              float speed;
              float ox;
              float oy;
              float x;
              float y;
              float fx;
              float fy;
              bool alive;
              bool existence;
};

class Boss: public Enemy
{
      public:
              Boss (hgeSprite *espr, int spawnTime, float ox, float oy, float fx, float fy, float speed, int health, int nPatterns);
              void update();
              void setShotPattern(ShotPattern *pattern, float trigger, int index);
              void setShotPattern(ShotPattern *pattern, int index);
              //void setVariableShotPattern(hgeSprite *sspr, float n1, float n2, float sspeed, float dspeed, float theta, float dtheta, int type, float accel, float rotation, float alpha);
              ShotPattern* getShotPattern(int index);
              ShotPattern* getActivePattern();

              
      private:
              ShotPattern *pattern[20];
              float triggerPattern[20];
              int activePattern;
              int nPatterns;

};
