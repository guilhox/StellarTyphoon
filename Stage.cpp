#include "Stage.h"

Stage::Stage(int n, hgeSprite *sprites[221])
{
     int i;
     
     stageNumber = n;          

     if(stageNumber>5) stageNumber = 5;
     if(stageNumber<1) stageNumber = 1;
     
     for(i=101; i<201; i++)
      padroes[i-101] = new ShotPattern(sprites[i], 4);
      
      for(i=201; i<221; i++)
      bpadroes[i-201] = new BossPattern(sprites[i], 4);
     
     if(stageNumber==1)
     {
      for(i=0; i<10; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 300+30*i, 900, 40*i, 700, 100+40*i, 5, 20);     
      padroes[i]->setup(3, 1, 8, 8, 0, 0.05, 20, 3, true, 3);
      inimigos[i]->setShotPattern(padroes[i]);   
      }
      for(i=10; i<20; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 900+30*(i-10), 900, 600-40*(i-10), 700, 500-40*(i-10), 5, 20);
      padroes[i]->setup(3, 1, 8, 8, 0, 0.05, 20, 3, true, 3);
      inimigos[i]->setShotPattern(padroes[i]);         
      }
      
      inimigos[20] = new Enemy(sprites[20], 1500, 900, 300, 650, 300, 3, 250);   
      padroes[20]->setup(8, 32, 6, 8, 0, 0.0115, 120, 4, true, 256);
      inimigos[20]->setShotPattern(padroes[20]);
      
      for(i=21; i<41; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 2000+15*(i-21), 600, -100, 600, 701, 8, 10);
      padroes[i]->setup(3, 1, 6, 6, 0, 0.1, 5, 3, true, 3);
      inimigos[i]->setShotPattern(padroes[i]);         
      }
      for(i=41; i<61; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 2450+15*(i-41), 700, 700, 700, -101, 8, 10);
      padroes[i]->setup(3, 1, 6, 6, 0, 0.1, 5, 3, true, 3);
      inimigos[i]->setShotPattern(padroes[i]);         
      }  
      for(i=61; i<81; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 2900+15*(i-61), 500, -100, 500, 701, 8, 10);
      padroes[i]->setup(3, 1, 6, 6, 0, 0.1, 5, 3, true, 3);
      inimigos[i]->setShotPattern(padroes[i]);         
      }
      
      inimigos[81] = new Enemy(sprites[81], 3200, 900, 300, 650, 300, 3, 150);   
      padroes[81]->setup(8, 16, 2, 4, 0, 0.005, 45, 4, true, 128);
      inimigos[81]->setShotPattern(padroes[81]);       
      
      inimigos[82] = new Enemy(sprites[82], 3600, 900, 100, 650, 100, 3, 100);   
      padroes[82]->setup(8, 8, 2, 4, 0, 0.0075, 45, 4, true, 64);
      inimigos[82]->setShotPattern(padroes[82]);       
      
      inimigos[83] = new Enemy(sprites[83], 3600, 900, 500, 650, 500, 3, 100);   
      padroes[83]->setup(8, 8, 2, 4, 0, 0.0075, 45, 4, true, 64);
      inimigos[83]->setShotPattern(padroes[83]);  
      
      inimigos[84] = new Enemy(sprites[84], 4000, 900, 90, 650, 90, 3, 75);   
      padroes[84]->setup(8, 4, 2, 4, 0, 0.00875, 45, 4, true, 32);
      inimigos[84]->setShotPattern(padroes[84]);       
      
      inimigos[85] = new Enemy(sprites[85], 4000, 900, 230, 650, 230, 3, 75);   
      padroes[85]->setup(8, 4, 2, 4, 0, 0.00875, 45, 4, true, 32);
      inimigos[85]->setShotPattern(padroes[85]);       
      
      inimigos[86] = new Enemy(sprites[86], 4000, 900, 370, 650, 370, 3, 75);   
      padroes[86]->setup(8, 4, 2, 4, 0, 0.00875, 45, 4, true, 32);
      inimigos[86]->setShotPattern(padroes[86]);      
      
      inimigos[87] = new Enemy(sprites[87], 4000, 900, 510, 650, 510, 3, 75);   
      padroes[87]->setup(8, 4, 2, 4, 0, 0.00875, 45, 4, true, 32);
      inimigos[87]->setShotPattern(padroes[87]);       
      
      for(i=88; i<99; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 4500+15*(i-88), 600, -100, 600, 701, 8, 10);
      padroes[i]->setup(3, 1, 6, 6, 0, 0.1, 2, 3, true, 3);
      inimigos[i]->setShotPattern(padroes[i]);         
      }
      
      inimigos[99] = new Enemy(sprites[99], 4800, 900, 300, 650, 300, 3, 300);   
      padroes[99]->setup(1, 4, 1, 8, 0, 0.005, 1, 2, false, 4);
      inimigos[99]->setShotPattern(padroes[99]); 
      
      chefe = new Boss(sprites[100], 5700, 900, 300, 650, 300, 1, 30000, 10);
      //bpadroes[0]->setup(16, 512, 0.5, 3, 0, 0.02, 8, 7, false, 32);
      //bpadroes[0]->shift(90, -4, 0.1, 0.01, 0, 0, 1, 1,1,1,1,1, 0, true);
      //bpadroes[0]->shift(90, 0, -0.2, 0, 0, 0, 2, 1,1,1,1,1, 1, true);
      bpadroes[0]->setup(32, 64, 200, 200, -1.0/128.0, 1.0/4096.0, 450, 1, false, 2048);
      bpadroes[0]->shift(1, 8, 33, 0, 0, 0, 1, 0,2,1,1,1, 0, true);
      //bpadroes[0]->shift(1, -1, 0, 0, 0, 0, 2, 2,1,1,1,1, 1, true);
      //bpadroes[0]->shift(1, 0, 0.25, 0, 0, 0, 2, 1,1,1,1,1, 2, true);
      bpadroes[0]->shift(30, 0, 0, 0, 0, 0, 1, 0,1,1,1,1, 3, true);
      bpadroes[0]->shift(150, 1, -0.8, 0, 0, 0, 2, 0,1,1,1,1, 4, true);
      bpadroes[0]->shift(150, 1, 0.4, 0, 0, 0, 1, 0,1,1,1,1, 5, true);
      bpadroes[0]->shift(150, 1, -1.0/2048.0, 0, 0, 0, 2, 0,1,1,1,1, 6, true);
      bpadroes[1]->setup(2, 71, -600, 600, 0, 1, 60, 3, true, 142);
      bpadroes[1]->shift(1, 8, 0.25, 0, 0, 0, 1, 0,1,1,1,1, 0, true);
      bpadroes[1]->shift(60, 1, 0.1, 0, 0, 0, 2, 0,1,1,1,1, 1, true);
      bpadroes[1]->shift(60, 1, -0.2, 0, 0, 0, 4, 0,1,1,1,1, 2, true);
      bpadroes[2]->setup(512, 4, 4, 8, 0, 0, 450, 1, true, 2048);
      bpadroes[2]->shift(30, 0, 0, 0, 0, 0, 1, 0,1,1,1,1, 0, true);
      bpadroes[2]->shift(90, 1, 4, 0, 0, 0, 1, 0,2,1,1,1, 1, true);
      bpadroes[2]->shift(135, 2, -0.5, 0, 0, 0, 2, 0,2,1,1,1, 2, true);
      bpadroes[2]->shift(180, 0, 4, 0, 0, 0, 1, 1,2,1,1,1, 3, true);
      bpadroes[3]->setup(24, 400, 4, 8, 0, 1.0/1024.0, 6, 7, false, 24);
      //bpadroes[3]->shift(30, 0, 0, 0, 0, 0, 1, 0,1,1,1,1, 0);
      bpadroes[3]->shift(45, 1, 25, 0, 0, 0, 1, 0,2,0,1,1, 1, true);
      //bpadroes[3]->shift(120, 2, 1, 0, 0, 0, 2, 0,2,1,1,1, 2);
      bpadroes[4]->setup(25, 400, 1, 2, 0, 0.5, 12, 3, true, 25);
      bpadroes[4]->shift(90, 2, 2, 0, 0, 0, 2, 2,2,1,1,1, 0, true);
      bpadroes[5]->setup(4, 2500, 4, 8, 0, 1.0/10000.0, 1, 6, false, 4);
      bpadroes[6]->setup(500, 2, 2, 4, 0, 0, 20, 1, false, 500);
      bpadroes[7]->setup(3, 1, -0.1, 8, 0, 0.03, 1, 5, true, 3);
      bpadroes[8]->setup(96, 2, 2, 2, 0, 1.0/128.0, 12, 1, true, 192);
      bpadroes[8]->shift(5, 0, 0, 0, 0.015, 0, 1, 1,1,1,1,1, 0, true);
      bpadroes[8]->shift(5, 0, 0, 0, -0.03, 0, 2, 1,1,1,1,1, 1, true);
      bpadroes[8]->shift(30, 0, 0, 0, -1, 0, 1, 1,1,1,2,1, 2, false);
      bpadroes[9]->setup(32, 64, -12, 12, 0, 1.0/2048.0, 450, 8, true, 2048);
      bpadroes[9]->shift(30, 0, 0, 0, 0, 0, 1, 0,1,1,1,1, 0, true);
      bpadroes[9]->shift(30, 1, -31.0, 0, 0, 0, 1, 0,2,1,1,1, 1, true);
      //bpadroes[9]->shift(150, 0, 0.25, 0, 0, 0, 1, 1,1,1,1,1, 2, true);
      //bpadroes[9]->shift(150, 0, -0.5, 0, 0, 0, 2, 1,1,1,1,1, 3, true);
      
      for(i=0; i<10; i++)
      chefe->setShotPattern(bpadroes[i], i);
      
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
                if(timer>400){
                chefe->getActivePattern()->moveOrigin(chefe->getX(), chefe->getY());
                
                if(chefe->getActivePattern()->isAimed()&&chefe->isAlive())
                chefe->getActivePattern()->aim(aimShot(chefe->getX(), chefe->getY(), px, py));
                //chefe->getActivePattern()->update(chefe->isAlive());
                chefe->getActivePattern()->update(chefe->isAlive());
                }
                
                
                timer++;
                
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
