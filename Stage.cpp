#include "Stage.h"

Stage::Stage(int n, hgeSprite *sprites[221])
{
     int i;
     
     stageNumber = n;          

     if(stageNumber>5) stageNumber = 5;
     if(stageNumber<1) stageNumber = 1;
     
     for(i=101; i<221; i++)
      padroes[i-101] = new ShotPattern(sprites[i], 4);
     
     if(stageNumber==1)
     {
      for(i=0; i<10; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 300+30*i, 900, 40*i, 700, 100+40*i, 5, 20);     
      padroes[i]->setup(3, 1, 8, 8, 0, 0.05, 20, 3, true);
      inimigos[i]->setShotPattern(padroes[i]);   
      }
      for(i=10; i<20; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 900+30*i, 900, 600-40*(i-10), 700, 500-40*(i-10), 5, 20);
      padroes[i]->setup(3, 1, 8, 8, 0, 0.05, 20, 3, true);
      inimigos[i]->setShotPattern(padroes[i]);         
      }
      
      inimigos[20] = new Enemy(sprites[20], 1500, 900, 300, 650, 300, 3, 150);   
      padroes[20]->setup(32, 4, 2, 4, 0, 0.004321, 30, 4, false);
      inimigos[20]->setShotPattern(padroes[20]);
      
      for(i=21; i<41; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 2000+15*i, 600, -100, 600, 701, 8, 10);
      padroes[i]->setup(5, 1, 6, 6, 0, 0.1, 5, 3, true);
      inimigos[i]->setShotPattern(padroes[i]);         
      }
      for(i=41; i<61; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 2450+15*i, 700, 700, 700, -101, 8, 10);
      padroes[i]->setup(5, 1, 6, 6, 0, 0.1, 5, 3, true);
      inimigos[i]->setShotPattern(padroes[i]);         
      }  
      for(i=61; i<81; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 2900+15*i, 500, -100, 500, 701, 8, 10);
      padroes[i]->setup(5, 1, 6, 6, 0, 0.1, 5, 3, true);
      inimigos[i]->setShotPattern(padroes[i]);         
      }
      
      inimigos[81] = new Enemy(sprites[81], 3200, 900, 300, 650, 300, 3, 150);   
      padroes[81]->setup(8, 16, 2, 4, 0, 0.005, 45, 4, false);
      inimigos[81]->setShotPattern(padroes[81]);       
      
      inimigos[82] = new Enemy(sprites[82], 3600, 900, 100, 650, 100, 3, 100);   
      padroes[82]->setup(8, 8, 2, 4, 0, 0.005, 45, 4, false);
      inimigos[82]->setShotPattern(padroes[82]);       
      
      inimigos[83] = new Enemy(sprites[83], 3600, 900, 500, 650, 500, 3, 100);   
      padroes[83]->setup(8, 8, 2, 4, 0, 0.005, 45, 4, false);
      inimigos[83]->setShotPattern(padroes[83]);  
      
      inimigos[84] = new Enemy(sprites[84], 4000, 900, 90, 650, 90, 3, 75);   
      padroes[84]->setup(8, 16, 2, 4, 0, 0.005, 45, 4, false);
      inimigos[84]->setShotPattern(padroes[84]);       
      
      inimigos[85] = new Enemy(sprites[85], 4000, 900, 230, 650, 230, 3, 75);   
      padroes[85]->setup(8, 4, 2, 4, 0, 0.005, 45, 4, false);
      inimigos[85]->setShotPattern(padroes[85]);       
      
      inimigos[86] = new Enemy(sprites[86], 4000, 900, 370, 650, 370, 3, 75);   
      padroes[86]->setup(8, 4, 2, 4, 0, 0.005, 45, 4, false);
      inimigos[86]->setShotPattern(padroes[86]);      
      
      inimigos[87] = new Enemy(sprites[87], 4000, 900, 510, 650, 510, 3, 75);   
      padroes[87]->setup(8, 4, 2, 4, 0, 0.005, 45, 4, false);
      inimigos[87]->setShotPattern(padroes[87]);       
      
      for(i=88; i<99; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 4500+15*i, 600, -100, 600, 701, 8, 10);
      padroes[i]->setup(5, 1, 12, 12, 0, 0.1, 2, 3, true);
      inimigos[i]->setShotPattern(padroes[i]);         
      }
      
      inimigos[99] = new Enemy(sprites[99], 4800, 900, 300, 650, 300, 3, 300);   
      padroes[99]->setup(1, 4, 1, 8, 0, 0.005, 1, 2, false);
      inimigos[99]->setShotPattern(padroes[99]); 
      
      chefe = new Boss(sprites[101], 5700, 900, 300, 650, 300, 1, 3000, 10);
      padroes[100]->setup(4, 16, 0.5, 2, 0, 3.1415926, 300, 4, false);
      padroes[101]->setup(8, 16, 0.5, 2, 0, 3.1415926, 300, 4, false);
      padroes[102]->setup(8, 32, 0.5, 3, 0, 3.1415926, 300, 4, false);
      padroes[103]->setup(8, 48, 0.5, 3, 0, 3.1415926, 300, 4, false);
      padroes[104]->setup(10, 56, 0.5, 4, 0, 3.1415926, 300, 4, false);
      padroes[105]->setup(10, 64, 0.5, 4, 0, 3.1415926, 300, 4, false);
      padroes[106]->setup(12, 64, 0.5, 5, 0, 3.1415926, 300, 4, false);
      padroes[107]->setup(16, 64, 0.5, 6, 0, 3.1415926, 300, 4, false);
      padroes[108]->setup(24, 64, 0.5, 8, 0, 3.1415926, 300, 4, false);
      padroes[109]->setup(28, 72, 0.5, 12, 0, 3.1415926, 150, 4, false);
      
      for(i=0; i<10; i++)
      chefe->setShotPattern(padroes[i+100], i);
      
     }
          
}
             void Stage::update(float px, float py)
             {
                  int i;
                  
                for(i=0; i<100; i++)
                {
                inimigos[i]->update();
                inimigos[i]->getShotPattern()->update(inimigos[i]->isAlive());
                inimigos[i]->getShotPattern()->moveOrigin(inimigos[i]->getX(), inimigos[i]->getY());
                
                if(inimigos[i]->getShotPattern()->isAimed()&&inimigos[i]->isAlive())
                inimigos[i]->getShotPattern()->aim(aimShot(inimigos[i]->getX(), inimigos[i]->getY(), px, py));
                
                if(inimigos[i]->getX()<-100||inimigos[i]->getX()>900||inimigos[i]->getY()<-100||inimigos[i]->getY()>700)
                inimigos[i]->die();
                
                }
                
                chefe->update();
                chefe->getActivePattern()->moveOrigin(chefe->getX(), chefe->getY());
                chefe->getActivePattern()->update(chefe->isAlive());
                
                
                
             }
             
             Boss* Stage::getBoss()
             {
                return chefe;       
             }
             
             Enemy* Stage::getEnemy(int index)
             {
                return inimigos[index];       
             }


            float Stage::aimShot(float x1, float y1, float x2, float y2)
            {
                  if(x1>x2)   return atan((y2-y1)/(x2-x1))/(2*3.1415926535) + 0.5;      
                  else         return atan((y2-y1)/(x2-x1))/(2*3.1415926535);
            }
