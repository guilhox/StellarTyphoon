#include "Shot.h"

class ShotPattern
{
      public:
             ShotPattern(hgeSprite *pspr, float radius);
             void updatePattern(float theta);
             void updateShots();
             void shift(int timer, float speed, float theta, float accel, float rotation, float alpha, int div, int absSpeed, int absTheta, int absRot, int absAccel, int absAlpha, int index, bool single);
             virtual Shot** getShot();
             void moveOrigin(float ox, float oy);
             int getWaveSize();
             int getCurrentIndex();
             bool isAimed();
             virtual void aim(float theta);
             void reset();
      
      protected:
              static Shot *shot[20000];
              static int currentIndex; 
              Shot *pattern[20000];
              int timer;
              int shiftTimer[10];
              int div[10];
              int interval;
              int activeIndex;
              int waveSize;
              int patternSize;
              float ox;
              float oy;
              float shiftSpeed[10];
              float shiftTheta[10];
              float shiftAccel[10];
              float shiftRot[10];
              float shiftAlpha[10];
              bool aimed;
              bool singleShift[10];
              int absSpeed[10];
              int absTheta[10];
              int absRot[10];
              int absAccel[10];
              int absAlpha[10];
      
};

class SimpleRadialPattern: public ShotPattern
{
      public:
      SimpleRadialPattern(hgeSprite *pspr, float radius, float n1, float n2, float minspeed, float maxspeed, float theta, float dtheta, int interval, bool aimed, int wave);
};

class DoubleRadialPattern: public ShotPattern
{
      public:
      DoubleRadialPattern(hgeSprite *pspr, float radius, float n1, float n2, float minspeed, float maxspeed, float theta, float dtheta, int interval, bool aimed, int wave);
};

class RandomPattern: public ShotPattern
{
      public:
      RandomPattern(hgeSprite *pspr, float radius, float minspeed, float maxspeed, int interval, int wave);
};

class CentralBurstPattern: public ShotPattern
{
      public:
      CentralBurstPattern(hgeSprite *pspr, float radius, float n1, float n2, float minspeed, float maxspeed, float theta, float dtheta, int interval, bool aimed, int wave);
};

class RandomBurstPattern: public ShotPattern
{
      public:
      RandomBurstPattern(hgeSprite *pspr, float radius, float minspeed, float maxspeed, float theta, float dtheta, int interval, bool aimed, int wave);
};

class CustomRadialPattern1: public ShotPattern
{
      public:
      CustomRadialPattern1(hgeSprite *pspr, float radius, float n1, float n2, float minspeed, float maxspeed, float theta, float dtheta, int interval, bool aimed, int wave);
};

class CustomRadialPattern2: public ShotPattern
{
      public:
      CustomRadialPattern2(hgeSprite *pspr, float radius, float n1, float n2, float minspeed, float maxspeed, float theta, float dtheta, int interval, bool aimed, int wave);
};

class CustomRadialPattern3: public ShotPattern
{
      public:
      CustomRadialPattern3(hgeSprite *pspr, float radius, float n1, float n2, float minspeed, float maxspeed, float theta, float dtheta, int interval, bool aimed, int wave);
};
