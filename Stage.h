#include "Enemy.h"

class Stage{
      private:
              Enemy *inimigos[100];
              Boss *chefe;
              ShotPattern *padroes[100];
              BossPattern *bpadroes[20];
              int timer;
              int stageNumber;
              float aimShot(float x1, float y1, float x2, float y2);
      public:
             Stage(int n, hgeSprite *sprites[221]);
             void update(float px, float py);
             Boss* getBoss();
             Enemy* getEnemy(int index);
      };
