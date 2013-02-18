#include "hgesprite.h"
#include <math.h>

class Shot
{
      public:
              Shot (hgeSprite *sspr, float radius);
              void update ();
              void shoot (float x, float y,  float speed, float theta, bool friendly, int power, float accel, float rotation, float alpha);
              void setSpeed(float newSpeed);
              void setAccel(float newAccel);
              void setRotation(float newRotation);
              void setAlpha(float newAlpha);
              void shift(int timer, float speed, float theta, float accel, float rotation, float alpha, int absSpeed, int absTheta, int absRot, int absAccel, int absAlpha, int index, bool single);
              float getOx();
              float getOy();
              float getAccel();
              float getRotation();
              float getAlpha();
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
              void setID(int ID);
              int getID();
      private:
              hgeSprite *sspr;
              float speed;
              float x;
              float y;
              float theta;
              bool active;
              int timer;
              int power;
              float radius;
              int ID;
              float accel;
              float rotation;
              float alpha;
              float ox;
              float oy;
              int shiftTimer[10];
              float shiftSpeed[10];
              float shiftTheta[10];
              float shiftAccel[10];
              float shiftRot[10];
              float shiftAlpha[10];
              bool singleShift[10];
              bool shifted;
              int absSpeed[10];
              int absTheta[10];
              int absRot[10];
              int absAccel[10];
              int absAlpha[10];
      
};
