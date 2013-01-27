#include "Shot.h"

class ShotPattern
{
      public:
             ShotPattern(hgeSprite *pspr, float radius);
             virtual void update(bool alive);
             virtual void update(bool alive, int wave);
             virtual void setup(float n1, float n2, float minspeed, float maxspeed, float theta, float dtheta, int interval, int type, bool aimed, int wave);
             void shift(int timer, float speed, float theta, float accel, float rotation, float alpha, int div, int absSpeed, int absTheta, int absRot, int absAccel, int absAlpha, int index, bool single);
             virtual variableShot** getShot();
             void moveOrigin(float ox, float oy);
             int getWaveSize();
             bool isAimed();
             virtual void aim(float theta);
      
      private:
              variableShot *shot[1000];
              float thetaorig[1000];
              float speedorig[1000];
              float accelorig[1000];
              float rotorig[1000];
              float alphaorig[1000];
              
      protected:         
              int timer;
              int shiftTimer[10];
              int div[10];
              int interval;
              int type;
              int activeIndex;
              int waveSize;
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

class BossPattern:public ShotPattern
{
      public:
             BossPattern(hgeSprite *pspr, float radius);
             void update(bool alive);
             void update(bool alive, int wave);
             void setup(float n1, float n2, float minspeed, float maxspeed, float theta, float dtheta, int interval, int type, bool aimed, int wave);
             variableShot** getShot();
             void aim(float theta);
      
      private:
              variableShot *bshot[10000];
              float bthetaorig[10000];      
              float bspeedorig[10000];
              float baccelorig[10000];
              float brotorig[10000];
              float balphaorig[10000];
};
