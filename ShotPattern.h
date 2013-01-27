#include "Shot.h"

class ShotPattern
{
      public:
             ShotPattern(hgeSprite *pspr, float radius);
             virtual void update(bool alive);
             virtual void setup(float n1, float n2, float minspeed, float maxspeed, float theta, float dtheta, int interval, int type, bool aimed);
             Shot** getShot();
             void activate(int n, float x, float y);
             void moveOrigin(float ox, float oy);
             int getWaveSize();
             bool isAimed();
             void aim(float theta);
      
      private:
              Shot *shot[5000];
              int timer;
              int interval;
              int type;
              int activeIndex;
              int waveSize;
              float ox;
              float oy;
              float thetaorig[5000];
              bool aimed;
      
};
