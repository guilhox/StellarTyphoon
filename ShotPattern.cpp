#include "ShotPattern.h"

ShotPattern::ShotPattern(hgeSprite *pspr, float radius)
{
       int i;
       for(i=0; i<1600; i++)
       {
       shot[i] = new Shot(pspr, radius);
       thetaorig[i] = 0;
       }
       
       type = 1;
       activeIndex = 0;
       waveSize=0;
       ox = -1;
       oy = -1;                  
       aimed = false; 
                                   
}

void ShotPattern::update(bool alive)
{
       int i;
       
       for(i=0; i<1600; i++)
       {
       shot[i]->update();
       
       if(shot[i]->getX() > (800+shot[i]->getRadius())||shot[i]->getX() < (0-shot[i]->getRadius())||shot[i]->getY() > (600+shot[i]->getRadius())||shot[i]->getY() < (0-shot[i]->getRadius()))
       shot[i]->hit();
       }
       if(timer%interval==0&&alive)
       {
           timer = 0;
           for(i=activeIndex; i<activeIndex + waveSize; i++)
             {
                   shot[i]->activate();
                   shot[i]->teleport(ox, oy);
             }
         
           activeIndex+=waveSize;
           if(activeIndex>1600-waveSize) activeIndex = 0;
       }
       
       timer++;
}

void ShotPattern::setup(float _n1, float _n2, float minspeed, float maxspeed, float theta, float dtheta, int _interval, int _type, bool _aimed)
{
     int i, n;
     float n1, n2;
     
     aimed = _aimed;
     
     if(_n1*_n2>1600)
     {
         _n1=32;
         _n2=8;
     }
     
       type = _type;
       interval = _interval;
     
     switch(type)
     {
                 case 1://radial simples
                      {
                           waveSize = (int)_n1*_n2;
                                 
                           for(i=0; i<1600/waveSize; i++)
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n1*_n2 + n2);
                                 if(_n2>1)
                                 shot[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*(n2/(_n2-1)), theta+(n1/_n1)+dtheta*n2, false, 1);
                                 else
                                 shot[n]->shoot(0, 0, minspeed, theta+(n1/_n1)+dtheta*n2, false, 1);
                                 
                                 thetaorig[n] = shot[n]->getTheta();
                                 } 
                     
                      }break;
                 case 2://aleatório
                      {
                            waveSize = (int)_n1*_n2;
                            for(i=0; i<1600; i++)
                             {
                                     shot[i]->shoot(0, 0,minspeed+(float)rand()/((float)RAND_MAX/(maxspeed-minspeed)),(float)rand()/((float)RAND_MAX), true, 1);
                                     thetaorig[i] = shot[i]->getTheta();
                             }     
                         
                      }break;
                 case 3://rajada centralizada
                      {
                            waveSize = (int)_n1*_n2;
                                 
                           for(i=0; i<1600/waveSize; i++)
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n1*_n2 + n2);
                                 if(_n2>1)
                                 shot[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*(n2/(_n2-1)), theta-(dtheta/2) + dtheta*((n1+0.5)/_n1), false, 1);
                                 else
                                 shot[n]->shoot(0, 0, minspeed, theta-(dtheta/2) + dtheta*((n1+0.5)/_n1), false, 1);
                                 
                                 thetaorig[n] = shot[n]->getTheta();
                                 }     
                         
                      }break;
                 case 4://radial duplo
                      {
                            waveSize = (int)_n1*_n2;
                                 
                           for(i=0; i<1600/waveSize; i++)
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n1*_n2 + n2);
                                 if(n%2==0)
                                 {
                                 if(_n2>1)   
                                 shot[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*(n2/(_n2-1)), theta+(n1/_n1)+dtheta*n2, false, 1);
                                 else
                                 shot[n]->shoot(0, 0, minspeed, theta+(n1/_n1)+dtheta*n2, false, 1);
                                 }
                                 else
                                 {
                                 if(_n2>1)   
                                 shot[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*((n2-1)/(_n2-1)), theta+(n1/_n1)-dtheta*(n2-1), false, 1);
                                 else
                                 shot[n]->shoot(0, 0, minspeed, theta+(n1/_n1)-dtheta*(n2-1), false, 1);
                                 }
                                 thetaorig[n] = shot[n]->getTheta();
                                 } 
                                 }break;
                 case 5://rajada aleatória
                      {
                            waveSize = (int)_n1*_n2;
                                 
                           for(i=0; i<1600/waveSize; i++)
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n1*_n2 + n2);
                                 shot[n]->shoot(0, 0, minspeed + (float)rand()/((float)RAND_MAX/(maxspeed-minspeed)),(float)rand()/((float)RAND_MAX/(dtheta))-(dtheta/2), false, 1);
                                 thetaorig[n] = shot[n]->getTheta();
                                 }     
                         
                      }break;
     }
}

Shot** ShotPattern::getShot()
{
       return shot;
}

void ShotPattern::activate(int n, float x, float y)
{
     int i;
     
     for(i=activeIndex; i<activeIndex + n; i++)
     {
           shot[i]->activate();
           shot[i]->teleport(x, y);
     }
     
     activeIndex+=n;
     if(activeIndex>1600-n) activeIndex = 0;
     
}

void ShotPattern::moveOrigin(float _ox, float _oy)
{
ox = _ox;
oy = _oy;     
}

int ShotPattern::getWaveSize()
{
    return waveSize;
}

void ShotPattern::aim(float _theta)
{
     int i;
     
     for(i=activeIndex; i<activeIndex + waveSize; i++)
     {
     shot[i]->hit();
     shot[i]->setTheta(thetaorig[i] + _theta);         
     }
}

bool ShotPattern::isAimed()
{
     return aimed;
}
