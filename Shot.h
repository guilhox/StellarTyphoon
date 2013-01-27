#include "hgesprite.h"
#include <math.h>

class Shot
{
      public:
              Shot (hgeSprite *sspr, float radius);
              virtual void update ();
              virtual void shoot (float x, float y,  float speed, float theta, bool friendly, int power);
              bool isFriendly();
              hgeSprite getSprite();
              float getSpeed();
              float getX();
              float getY();
              float getTheta();
              float getRadius();
              void setTheta(float newTheta);
              int getTimer();
              int getPower();
              void activate();
              bool isActive();
              void teleport(float x, float y);
              void hit();
      protected:
              hgeSprite *sspr;
              float speed;
              float x;
              float y;
              float theta;
              bool friendly;
              bool active;
              int timer;
              int power;
              float radius;
      
};

class variableShot: public Shot
{
      public:
              variableShot (hgeSprite *sspr, float radius);
              void update ();
              void shoot (float x, float y,  float speed, float theta, bool friendly, int power, float accel, float rotation, float alpha);
              void setSpeed(float newSpeed);
              void setAccel(float newAccel);
              void setRotation(float newRotation);
              void setAlpha(float newAlpha);
              float getOx();
              float getOy();
              float getAccel();
              float getRotation();
              float getAlpha();

      private:
              float accel;
              float rotation;
              float alpha;
              float ox;
              float oy;
};
