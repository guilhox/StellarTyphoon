#include "hge.h"
#include "hgesprite.h"

class ship : public hgeSprite
{
      private:
        int mx;
        int my;
        int mhp;
        float mspeed;
      public:
        ship(int x, int y, int hp, float speed);
}
