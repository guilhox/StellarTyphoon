#include "Stage.h"

Stage::Stage(int n, hgeSprite *sprites[221])
{
     int i;
     
     stageNumber = n;          

     if(stageNumber>5) stageNumber = 5;
     if(stageNumber<1) stageNumber = 1;

     
     if(stageNumber==1)
     {
             
      for(i=0; i<10; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 300+30*i, 0, 900, 40*i, 700, 100+40*i, 5, 20);     
      padroes[i] = new CentralBurstPattern(sprites[i+101], 4, 3, 1, 8, 8, 0, 0.05, 20, true, 3);
      padroes[i]->shift(30, 2, 0, 0, 0, 0, 1, 2,1,1,1,1, 0, true);
      inimigos[i]->setShotPattern(padroes[i]);   
      }
      for(i=10; i<20; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 900+30*(i-10), 0, 900, 600-40*(i-10), 700, 500-40*(i-10), 5, 20);
      padroes[i] = new CentralBurstPattern(sprites[i+101], 4, 3, 1, 8, 8, 0, 0.05, 20, true, 3);
      inimigos[i]->setShotPattern(padroes[i]);         
      }
      
      inimigos[20] = new Enemy(sprites[20], 1500, 60, 900, 300, 650, 300, 3, 250);   
      padroes[20] = new DoubleRadialPattern(sprites[i+101], 4, 32, 32, 3, 4, 0, 0.0115, 10, true, 32);
      inimigos[20]->setShotPattern(padroes[20]);
      
      for(i=21; i<41; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 2000+15*(i-21), 0, 600, -100, 600, 701, 8, 10);
      padroes[i] = new CentralBurstPattern(sprites[i+101], 4, 3, 1, 6, 6, 0, 0.1, 5, true, 3);
      inimigos[i]->setShotPattern(padroes[i]);         
      }
      for(i=41; i<61; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 2450+15*(i-41), 0, 700, 700, 700, -101, 8, 10);
      padroes[i] = new CentralBurstPattern(sprites[i+101], 4, 3, 1, 6, 6, 0, 0.1, 5, true, 3);
      inimigos[i]->setShotPattern(padroes[i]);         
      }  
      for(i=61; i<81; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 2900+15*(i-61), 0, 500, -100, 500, 701, 8, 10);
      padroes[i] = new CentralBurstPattern(sprites[i+101], 4, 3, 1, 6, 6, 0, 0.1, 5, true, 3);
      inimigos[i]->setShotPattern(padroes[i]);         
      }
      
      inimigos[81] = new Enemy(sprites[81], 3200, 60, 900, 300, 650, 300, 3, 150);   
      padroes[81] = new DoubleRadialPattern(sprites[182], 4, 8, 16, 2, 4, 0, 0.005, 5, true, 8);
      inimigos[81]->setShotPattern(padroes[81]);       
      
      inimigos[82] = new Enemy(sprites[82], 3600, 60, 900, 100, 650, 100, 3, 100);   
      padroes[82] = new DoubleRadialPattern(sprites[183], 4, 8, 8, 2, 4, 0, 0.0075, 4, true, 8);
      inimigos[82]->setShotPattern(padroes[82]);       
      
      inimigos[83] = new Enemy(sprites[83], 3600, 60, 900, 500, 650, 500, 3, 100);   
      padroes[83] = new DoubleRadialPattern(sprites[184], 4, 8, 8, 2, 4, 0, 0.0075, 4, true, 8);
      inimigos[83]->setShotPattern(padroes[83]);  
      
      inimigos[84] = new Enemy(sprites[84], 4000, 60, 900, 90, 650, 90, 3, 75);   
      padroes[84] = new DoubleRadialPattern(sprites[185], 4, 8, 4, 2, 4, 0, 0.00875, 3, true, 8);
      inimigos[84]->setShotPattern(padroes[84]);       
      
      inimigos[85] = new Enemy(sprites[85], 4000, 60, 900, 230, 650, 230, 3, 75);  
      padroes[85] = new DoubleRadialPattern(sprites[186], 4, 8, 4, 2, 4, 0, 0.00875, 3, true, 8);
      inimigos[85]->setShotPattern(padroes[85]);       
      
      inimigos[86] = new Enemy(sprites[86], 4000, 60, 900, 370, 650, 370, 3, 75); 
      padroes[86] = new DoubleRadialPattern(sprites[187], 4, 8, 4, 2, 4, 0, 0.00875, 3, true, 8);
      inimigos[86]->setShotPattern(padroes[86]);      
      
      inimigos[87] = new Enemy(sprites[87], 4000, 60, 900, 510, 650, 510, 3, 75);  
      padroes[87] = new DoubleRadialPattern(sprites[188], 4, 8, 4, 2, 4, 0, 0.00875, 3, true, 8);
      inimigos[87]->setShotPattern(padroes[87]);       
      
      for(i=88; i<99; i++)
      {
      inimigos[i] = new Enemy(sprites[i], 4500+15*(i-88), 0, 600, -100, 600, 701, 8, 10);
      padroes[i] = new CentralBurstPattern(sprites[i+101], 4, 3, 1, 6, 6, 0, 0.1, 2, true, 3);
      inimigos[i]->setShotPattern(padroes[i]);         
      }
      
      inimigos[99] = new Enemy(sprites[99], 4800, 60, 900, 300, 650, 300, 3, 300); 
      padroes[99] = new RandomPattern(sprites[200], 4, 1, 8, 2, 4);
      inimigos[99]->setShotPattern(padroes[99]); 
      
      chefe = new Boss(sprites[100], 5700, 400, 900, 300, 650, 300, 1, 30000, 10);
      padroes[100] = new CustomRadialPattern3(sprites[201], 4, 32, 64, 0.04, 0.08, -1.0/160.0, 1.0/4096.0, 450, false, 2048);


      padroes[100]->shift(1, 150, 0, 0, 0, 0, 1, 1,1,1,1,1, 0, true);
      padroes[100]->shift(2, -150, 0, 0, 0, 0, 1, 1,1,1,1,1, 1, true);
      padroes[100]->shift(2, 100, 33, 0, 0, 0, 1, 2,2,1,1,1, 2, true);
      padroes[100]->shift(30, 0, 0, 0, 0, 0, 1, 0,1,1,1,1, 3, true);
      padroes[100]->shift(150, 1, -0.7, 0, 0, 0, 2, 0,1,1,1,1, 4, true);
      padroes[100]->shift(150, 1, 0.35, 0, 0, 0, 1, 0,1,1,1,1, 5, true);
      padroes[100]->shift(150, 1, -1.0/2048.0, 0, 0, 0, 2, 0,1,1,1,1, 6, true);
      padroes[101] = new CentralBurstPattern(sprites[202], 4, 2, 71, -600, 600, 0, 1, 60, true, 142);
      padroes[101]->shift(1, 8, 0.25, 0, 0, 0, 1, 0,1,1,1,1, 0, true);
      padroes[101]->shift(60, 1, 0.1, 0, 0, 0, 2, 0,1,1,1,1, 1, true);
      padroes[101]->shift(60, 1, -0.2, 0, 0, 0, 4, 0,1,1,1,1, 2, true);
      padroes[102] = new SimpleRadialPattern(sprites[203], 4, 512, 4, 4, 8, 0, 0, 450, true, 2048);
      padroes[102]->shift(30, 0, 0, 0, 0, 0, 1, 0,1,1,1,1, 0, true);
      padroes[102]->shift(90, 1, 4, 0, 0, 0, 1, 0,2,1,1,1, 1, true);
      padroes[102]->shift(135, 1.5, -0.5, 0, 0, 0, 2, 0,2,1,1,1, 2, true);
      padroes[102]->shift(180, 0, 4, 0, 0, 0, 1, 1,2,1,1,1, 3, true);
      padroes[103] = new CustomRadialPattern2(sprites[204], 4, 24, 400, 4, 8, 0, 1.0/1024.0, 6, false, 24);
      padroes[103]->shift(45, 1, 25, 0, 0, 0, 1, 0,2,0,1,1, 1, true);
      padroes[104] = new CentralBurstPattern(sprites[205], 4, 49, 200, 1, 2, 0, 0.5, 12, true, 49);
      padroes[104]->shift(90, 2, 2, 0, 0, 0, 2, 2,2,1,1,1, 0, true);
      padroes[105] = new CustomRadialPattern1(sprites[206], 4, 4, 2500, 4, 8, 0, 1.0/10000.0, 1, false, 4);
      padroes[106] = new SimpleRadialPattern(sprites[207], 4, 500, 2, 2, 4, 0, 0, 20, false, 500);
      padroes[107] = new RandomBurstPattern(sprites[208], 4, -0.1, 8, 0, 0.03, 1, true, 3);
      padroes[108] = new SimpleRadialPattern(sprites[209], 4, 96, 2, 2, 2, 0, 1.0/128.0, 60, true, 192);
      padroes[108]->shift(5, 0, 0, 0, 0.015, 0, 1, 1,1,1,1,1, 0, true);
      padroes[108]->shift(5, 0, 0, 0, -0.03, 0, 2, 1,1,1,1,1, 1, true);
      padroes[108]->shift(30, 0, 0, 0, -1, 0, 1, 1,1,1,2,1, 2, false);
      padroes[109] = new CustomRadialPattern3(sprites[210], 4, 32, 64, -12, 12, 0, 1.0/2048.0, 450, true, 2048);
      padroes[109]->shift(30, 0, 0, 0, 0, 0, 1, 0,1,1,1,1, 0, true);
      padroes[109]->shift(30, 1, -31.0, 0, 0, 0, 1, 0,2,1,1,1, 1, true);
      padroes[109]->shift(150, 0, 0.25, 0, 0, 0, 1, 1,1,1,1,1, 2, true);
      padroes[109]->shift(150, 0, -0.5, 0, 0, 0, 2, 1,1,1,1,1, 3, true);
      
      
      for(i=100; i<110; i++)
      chefe->setShotPattern(padroes[i], i-100);

      
     }
          
}
             void Stage::update(float px, float py)
             {
                  int i;
                  
                for(i=0; i<100; i++)
                {
                inimigos[i]->update(aimShot(inimigos[i]->getX(), inimigos[i]->getY(), px, py));

                if(inimigos[i]->getX()<-100||inimigos[i]->getX()>900||inimigos[i]->getY()<-100||inimigos[i]->getY()>700)
                inimigos[i]->die();

                }
                
                inimigos[0]->getShotPattern()->updateShots();
                
                chefe->update(aimShot(chefe->getX(), chefe->getY(), px, py));
                //if(timer>400&&chefe->isAlive()){
                                                
                
                //chefe->getActivePattern()->moveOrigin(chefe->getX(), chefe->getY());
                //chefe->getActivePattern()->updatePattern(aimShot(chefe->getX(), chefe->getY(), px, py));
                //padroes[100]->updatePattern(aimShot(chefe->getX(), chefe->getY(), px, py));
                //}
                
                
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
