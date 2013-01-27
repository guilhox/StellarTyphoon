#include "ShotPattern.h"

ShotPattern::ShotPattern(hgeSprite *pspr, float radius)
{
       int i;
       for(i=0; i<1000; i++)
       {
       shot[i] = new variableShot(pspr, radius);
       thetaorig[i] = 0;
       speedorig[i] = 0;
       accelorig[i] = 0;
       rotorig[i] = 0;
       alphaorig[i] = 0;
       }
       
       type = 1;
       activeIndex = 0;
       waveSize=0;
       ox = -1;
       oy = -1;                  
       aimed = false; 
       
       for(i=0; i<10; i++)
       {
       shiftTimer[i] = 0;
       shiftSpeed[i] = 0;
       shiftTheta[i] = 0;
       shiftAccel[i] = 0;
       shiftRot[i] = 0;
       shiftAlpha[i] = 0;
       div[i] = 1;
       absSpeed[i] = 0;
       absTheta[i] = 0;
       absAccel[i] = 0;
       absRot[i] = 0;
       absAlpha[i] = 0;
       singleShift[i] = true;
       }
                                   
}

void ShotPattern::update(bool alive)
{
       int i, j;
       
       for(i=0; i<1000; i++)
       {
       
       for(j=0; j<10; j++)
       {
           if(shot[i]->isActive()&&shiftTimer[j]>0&&((shot[i]->getTimer() == shiftTimer[j]&&singleShift[j]==true)||(shot[i]->getTimer()>0&&shot[i]->getTimer()%shiftTimer[j]==0&&singleShift[j]==false))&&(i%div[j]) == 0)
           {

                             if(absSpeed[j]==0) shot[i]->setSpeed(shiftSpeed[j]);
                             else if(absSpeed[j]==1) shot[i]->setSpeed(shot[i]->getSpeed()+shiftSpeed[j]);
                             else if(absSpeed[j]==2) shot[i]->setSpeed(shot[i]->getSpeed()*shiftSpeed[j]);
                             if(absAccel[j]==0) shot[i]->setAccel(shiftAccel[j]);
                             else if(absAccel[j]==1) shot[i]->setAccel(shot[i]->getAccel()+shiftAccel[j]);
                             else if(absAccel[j]==2) shot[i]->setAccel(shot[i]->getAccel()*shiftAccel[j]);
                             if(absTheta[j]==0) shot[i]->setTheta(shiftTheta[j]);
                             else if(absTheta[j]==1)  shot[i]->setTheta(shot[i]->getTheta()+shiftTheta[j]);
                             else if(absTheta[j]==2)  shot[i]->setTheta(shot[i]->getTheta()*shiftTheta[j]);
                             if(absRot[j]==0) shot[i]->setRotation(shiftRot[j]);
                             else if(absRot[j]==1) shot[i]->setRotation(shot[i]->getRotation()+shiftRot[j]);
                             else if(absRot[j]==2) shot[i]->setRotation(shot[i]->getRotation()*shiftRot[j]);
                             if(absAlpha[j]==0) shot[i]->setAlpha(shiftAlpha[j]);
                             else if(absAlpha[j]==1) shot[i]->setAlpha(shot[i]->getAlpha()+shiftAlpha[j]);
                             else if(absAlpha[j]==2) shot[i]->setAlpha(shot[i]->getAlpha()*shiftAlpha[j]);
           }
       }
       
       shot[i]->update();
       
       if(shot[i]->getX() > (800+shot[i]->getRadius())||shot[i]->getX() < (0-shot[i]->getRadius())||shot[i]->getY() > (600+shot[i]->getRadius())||shot[i]->getY() < (0-shot[i]->getRadius()))
       shot[i]->hit();
       }
       if(timer%interval==0&&alive)
       {
           for(i=activeIndex; i<activeIndex + waveSize; i++)
             {
                   shot[i]->activate();
                   shot[i]->teleport(ox, oy);
             }
         
           activeIndex+=waveSize;
           if(activeIndex>1000-waveSize) activeIndex = 0;
       }
       
       timer++;
}

void ShotPattern::update(bool alive, int wave)
{
       int i, j;
       
       for(i=0; i<1000; i++)
       {
       
       
       for(j=0; j<10; j++)
       {
           if(shot[i]->isActive()&&shiftTimer[j]>0&&((shot[i]->getTimer() == shiftTimer[j]&&singleShift[j]==true)||(shot[i]->getTimer()>0&&shot[i]->getTimer()%shiftTimer[j]==0&&singleShift[j]==false))&&(i%div[j]) == 0)
           {

                             if(absSpeed[j]==0) shot[i]->setSpeed(shiftSpeed[j]);
                             else if(absSpeed[j]==1) shot[i]->setSpeed(shot[i]->getSpeed()+shiftSpeed[j]);
                             else if(absSpeed[j]==2) shot[i]->setSpeed(shot[i]->getSpeed()*shiftSpeed[j]);
                             if(absAccel[j]==0) shot[i]->setAccel(shiftAccel[j]);
                             else if(absAccel[j]==1) shot[i]->setAccel(shot[i]->getAccel()+shiftAccel[j]);
                             else if(absAccel[j]==2) shot[i]->setAccel(shot[i]->getAccel()*shiftAccel[j]);
                             if(absTheta[j]==0) shot[i]->setTheta(shiftTheta[j]);
                             else if(absTheta[j]==1)  shot[i]->setTheta(shot[i]->getTheta()+shiftTheta[j]);
                             else if(absTheta[j]==2)  shot[i]->setTheta(shot[i]->getTheta()*shiftTheta[j]);
                             if(absRot[j]==0) shot[i]->setRotation(shiftRot[j]);
                             else if(absRot[j]==1) shot[i]->setRotation(shot[i]->getRotation()+shiftRot[j]);
                             else if(absRot[j]==2) shot[i]->setRotation(shot[i]->getRotation()*shiftRot[j]);
                             if(absAlpha[j]==0) shot[i]->setAlpha(shiftAlpha[j]);
                             else if(absAlpha[j]==1) shot[i]->setAlpha(shot[i]->getAlpha()+shiftAlpha[j]);
                             else if(absAlpha[j]==2) shot[i]->setAlpha(shot[i]->getAlpha()*shiftAlpha[j]);
           }
       }
       
       shot[i]->update();
       
       if(shot[i]->getX() > (800+shot[i]->getRadius())||shot[i]->getX() < (0-shot[i]->getRadius())||shot[i]->getY() > (600+shot[i]->getRadius())||shot[i]->getY() < (0-shot[i]->getRadius()))
       shot[i]->hit();
       }
       if(timer%interval==0&&alive)
       {
           for(i=activeIndex; i<activeIndex + wave; i++)
             {
                   shot[i]->activate();
                   shot[i]->teleport(ox, oy);
             }
         
           activeIndex+=wave;
           if(activeIndex>1000-waveSize) activeIndex = 0;
           
       }
       
       timer++;
}

void ShotPattern::setup(float _n1, float _n2, float minspeed, float maxspeed, float theta, float dtheta, int _interval, int _type, bool _aimed, int wave)
{
     int i, n;
     float n1, n2;
     
     aimed = _aimed;
     
     if(_n1*_n2>1000)
     {
         _n1=16;
         _n2=8;
     }
     if (wave>1000) wave = 1000;
     else if (wave<1) wave = 1;
     
       type = _type;
       interval = _interval;
     
     switch(type)
     {
                 case 1://radial simples
                      {
                           waveSize = (int)_n1*_n2;
                                 
                           for(i=0; i<1000/waveSize; i++)
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n1*_n2 + n2);
                                 if(_n2>1)
                                 shot[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*(n2/(_n2-1)), theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 else
                                 shot[n]->shoot(0, 0, minspeed, theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 
                                 thetaorig[n] = shot[n]->getTheta();
                                 speedorig[n] = shot[n]->getSpeed();
                                 accelorig[n] = shot[n]->getAccel();
                                 rotorig[n] = shot[n]->getRotation();
                                 alphaorig[n] = shot[n]->getAlpha();
                                 } 
                     
                      }break;
                 case 2://aleatório
                      {
                            waveSize = (int)_n1*_n2;
                            for(i=0; i<1000; i++)
                             {
                                     shot[i]->shoot(0, 0,minspeed+(float)rand()/((float)RAND_MAX/(maxspeed-minspeed)),(float)rand()/((float)RAND_MAX), true, 1, 0, 0, 0);
                                     thetaorig[i] = shot[i]->getTheta();
                                 speedorig[i] = shot[i]->getSpeed();
                                 accelorig[i] = shot[i]->getAccel();
                                 rotorig[i] = shot[i]->getRotation();
                                 alphaorig[i] = shot[i]->getAlpha();
                             }     
                         
                      }break;
                 case 3://rajada centralizada
                      {
                            waveSize = (int)_n1*_n2;
                                 
                           for(i=0; i<1000/waveSize; i++)
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n2*_n1 + n1);
                                 if(_n2>1)
                                 shot[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*(n2/(_n2-1)), theta-(dtheta/2) + dtheta*((n1+0.5)/_n1), false, 1, 0, 0, 0);
                                 else
                                 shot[n]->shoot(0, 0, minspeed, theta-(dtheta/2) + dtheta*((n1+0.5)/_n1), false, 1, 0, 0, 0);
                                 
                                 thetaorig[n] = shot[n]->getTheta();
                                 speedorig[n] = shot[n]->getSpeed();
                                 accelorig[n] = shot[n]->getAccel();
                                 rotorig[n] = shot[n]->getRotation();
                                 alphaorig[n] = shot[n]->getAlpha();
                                 }     
                         
                      }break;
                 case 4://radial duplo
                      {
                            waveSize = (int)_n1*_n2;
                                 
                           for(i=0; i<1000/waveSize; i++)
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n1*_n2 + n2);
                                 if(n%2==0)
                                 {
                                 if(_n2>1)   
                                 shot[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*(n2/(_n2-1)), theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 else
                                 shot[n]->shoot(0, 0, minspeed, theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 }
                                 else
                                 {
                                 if(_n2>1)   
                                 shot[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*((n2-1)/(_n2-1)), theta+(n1/_n1)-dtheta*(n2-1), false, 1, 0, 0, 0);
                                 else
                                 shot[n]->shoot(0, 0, minspeed, theta+(n1/_n1)-dtheta*(n2-1), false, 1, 0, 0, 0);
                                 }
                                 thetaorig[n] = shot[n]->getTheta();
                                 speedorig[n] = shot[n]->getSpeed();
                                 accelorig[n] = shot[n]->getAccel();
                                 rotorig[n] = shot[n]->getRotation();
                                 alphaorig[n] = shot[n]->getAlpha();
                                 } 
                                 }break;
                 case 5://rajada aleatória
                      {
                            waveSize = (int)_n1*_n2;
                                 
                           for(i=0; i<1000/waveSize; i++)
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n1*_n2 + n2);
                                 shot[n]->shoot(0, 0, minspeed + (float)rand()/((float)RAND_MAX/(maxspeed-minspeed)),(float)rand()/((float)RAND_MAX/(dtheta))-(dtheta/2), false, 1, 0, 0, 0);
                                 thetaorig[n] = shot[n]->getTheta();
                                 speedorig[n] = shot[n]->getSpeed();
                                 accelorig[n] = shot[n]->getAccel();
                                 rotorig[n] = shot[n]->getRotation();
                                 alphaorig[n] = shot[n]->getAlpha();
                                 }     
                         
                      }break;
                 case 6://radial duplo modificado
                      {
                            waveSize = (int)_n1*_n2;
                                 
                           for(i=0; i<1000/waveSize; i++)
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n2*_n1 + n1);
                                 if(n%2==0)
                                 {
                                 if(_n2>1)   
                                 shot[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*(n2/(_n2-1)), theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 else
                                 shot[n]->shoot(0, 0, minspeed, theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 }
                                 else
                                 {
                                 if(_n2>1)   
                                 shot[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*((n2-1)/(_n2-1)), theta+(n1/_n1)-dtheta*(n2-1), false, 1, 0, 0, 0);
                                 else
                                 shot[n]->shoot(0, 0, minspeed, theta+(n1/_n1)-dtheta*(n2-1), false, 1, 0, 0, 0);
                                 }
                                 thetaorig[n] = shot[n]->getTheta();
                                 speedorig[n] = shot[n]->getSpeed();
                                 accelorig[n] = shot[n]->getAccel();
                                 rotorig[n] = shot[n]->getRotation();
                                 alphaorig[n] = shot[n]->getAlpha();
                                 } 
                                 }break;
                      
     }
     
     waveSize = wave;
}

void ShotPattern::shift(int timer, float speed, float theta, float accel, float rotation, float alpha, int d, int _absSpeed, int _absTheta, int _absAccel, int _absRot, int _absAlpha, int index, bool single)
{
       shiftTimer[index] = timer;
       shiftSpeed[index] = speed;
       shiftTheta[index] = theta;
       shiftAccel[index] = accel;
       shiftRot[index] = rotation;
       shiftAlpha[index] = alpha;
       div[index] = d;
       
       absSpeed[index] = _absSpeed;
       absTheta[index] = _absTheta;
       absRot[index] = _absRot;
       absAccel[index] = _absAccel;
       absAlpha[index] = _absAlpha;
       
       singleShift[index] = single;
}

variableShot** ShotPattern::getShot()
{
       return shot;
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

//////////////////////////////////////////////////////////////////////////
BossPattern::BossPattern(hgeSprite *pspr, float radius):ShotPattern(pspr, radius)
{
       int i;
       for(i=0; i<10000; i++)
       {
       bshot[i] = new variableShot(pspr, radius);
       bthetaorig[i] = 0;
       bspeedorig[i] = 0;
       baccelorig[i] = 0;
       brotorig[i] = 0;
       balphaorig[i] = 0;
       }
       
       type = 1;
       activeIndex = 0;
       waveSize=0;
       ox = -1;
       oy = -1;                  
       aimed = false; 
       
       for(i=0; i<10; i++)
       {
       shiftTimer[i] = 0;
       shiftSpeed[i] = 0;
       shiftTheta[i] = 0;
       shiftAccel[i] = 0;
       shiftRot[i] = 0;
       shiftAlpha[i] = 0;
       div[i] = 1;
       absSpeed[i] = 0;
       absTheta[i] = 0;
       absAccel[i] = 0;
       absRot[i] = 0;
       absAlpha[i] = 0;
       singleShift[i] = true;
       }
                                   
}

void BossPattern::update(bool alive)
{
       int i, j;
       
       for(i=0; i<10000; i++)
       {
       
       for(j=0; j<10; j++)
       {
           if(bshot[i]->isActive()&&shiftTimer[j]>0&&((bshot[i]->getTimer() == shiftTimer[j]&&singleShift[j]==true)||(bshot[i]->getTimer()>0&&bshot[i]->getTimer()%shiftTimer[j]==0&&singleShift[j]==false))&&(i%div[j]) == 0)
           {

                             if(absSpeed[j]==0) bshot[i]->setSpeed(shiftSpeed[j]);
                             else if(absSpeed[j]==1) bshot[i]->setSpeed(bshot[i]->getSpeed()+shiftSpeed[j]);
                             else if(absSpeed[j]==2) bshot[i]->setSpeed(bshot[i]->getSpeed()*shiftSpeed[j]);
                             if(absAccel[j]==0) bshot[i]->setAccel(shiftAccel[j]);
                             else if(absAccel[j]==1) bshot[i]->setAccel(bshot[i]->getAccel()+shiftAccel[j]);
                             else if(absAccel[j]==2) bshot[i]->setAccel(bshot[i]->getAccel()*shiftAccel[j]);
                             if(absTheta[j]==0) bshot[i]->setTheta(shiftTheta[j]);
                             else if(absTheta[j]==1)  bshot[i]->setTheta(bshot[i]->getTheta()+shiftTheta[j]);
                             else if(absTheta[j]==2)  bshot[i]->setTheta(bshot[i]->getTheta()*shiftTheta[j]);
                             if(absRot[j]==0) bshot[i]->setRotation(shiftRot[j]);
                             else if(absRot[j]==1) bshot[i]->setRotation(bshot[i]->getRotation()+shiftRot[j]);
                             else if(absRot[j]==2) bshot[i]->setRotation(bshot[i]->getRotation()*shiftRot[j]);
                             if(absAlpha[j]==0) bshot[i]->setAlpha(shiftAlpha[j]);
                             else if(absAlpha[j]==1) bshot[i]->setAlpha(bshot[i]->getAlpha()+shiftAlpha[j]);
                             else if(absAlpha[j]==2) bshot[i]->setAlpha(bshot[i]->getAlpha()*shiftAlpha[j]);
           }
       }
       
       bshot[i]->update();
       
       if(bshot[i]->getX() > (1600+bshot[i]->getRadius())||bshot[i]->getX() < (-800-bshot[i]->getRadius())||bshot[i]->getY() > (1200+bshot[i]->getRadius())||bshot[i]->getY() < (-600-bshot[i]->getRadius()))
       bshot[i]->hit();
       }
       if(timer%interval==0&&alive)
       {
           for(i=activeIndex; i<activeIndex + waveSize; i++)
             {
                   bshot[i]->hit();
                   bshot[i]->setSpeed(bspeedorig[i]);
                   bshot[i]->setAccel(baccelorig[i]);
                   if(!aimed)
                   bshot[i]->setTheta(bthetaorig[i]);
                   bshot[i]->setRotation(brotorig[i]);
                   bshot[i]->setAlpha(balphaorig[i]);   
                   bshot[i]->activate();
                   bshot[i]->teleport(ox, oy);
             }
         
           activeIndex+=waveSize;
           if(activeIndex>10000-waveSize)activeIndex = 0;
           else if(bshot[activeIndex]->getX()==-1||activeIndex>10000-waveSize) activeIndex = 0;
       }
       
       timer++;
}

void BossPattern::update(bool alive, int wave)
{
       int i, j;
       
       for(i=0; i<10000; i++)
       {
       if(!bshot[i]->isActive())
       {
                         bshot[i]->setSpeed(bspeedorig[i]);
                         bshot[i]->setAccel(baccelorig[i]);
                         if(!aimed)
                         bshot[i]->setTheta(bthetaorig[i]);
                         bshot[i]->setRotation(brotorig[i]);
                         bshot[i]->setAlpha(balphaorig[i]);                     
       }
       
       
       for(j=0; j<10; j++)
       {
           if(bshot[i]->isActive()&&shiftTimer[j]>0&&((bshot[i]->getTimer() == shiftTimer[j]&&singleShift[j]==true)||(bshot[i]->getTimer()>0&&bshot[i]->getTimer()%shiftTimer[j]==0&&singleShift[j]==false))&&(i%div[j]) == 0)
           {
                             if(absSpeed[j]==0) bshot[i]->setSpeed(shiftSpeed[j]);
                             else if(absSpeed[j]==1) bshot[i]->setSpeed(bshot[i]->getSpeed()+shiftSpeed[j]);
                             else if(absSpeed[j]==2) bshot[i]->setSpeed(bshot[i]->getSpeed()*shiftSpeed[j]);
                             if(absAccel[j]==0) bshot[i]->setAccel(shiftAccel[j]);
                             else if(absAccel[j]==1) bshot[i]->setAccel(bshot[i]->getAccel()+shiftAccel[j]);
                             else if(absAccel[j]==2) bshot[i]->setAccel(bshot[i]->getAccel()*shiftAccel[j]);
                             if(absTheta[j]==0) bshot[i]->setTheta(shiftTheta[j]);
                             else if(absTheta[j]==1)  bshot[i]->setTheta(bshot[i]->getTheta()+shiftTheta[j]);
                             else if(absTheta[j]==2)  bshot[i]->setTheta(bshot[i]->getTheta()*shiftTheta[j]);
                             if(absRot[j]==0) bshot[i]->setRotation(shiftRot[j]);
                             else if(absRot[j]==1) bshot[i]->setRotation(bshot[i]->getRotation()+shiftRot[j]);
                             else if(absRot[j]==2) bshot[i]->setRotation(bshot[i]->getRotation()*shiftRot[j]);
                             if(absAlpha[j]==0) bshot[i]->setAlpha(shiftAlpha[j]);
                             else if(absAlpha[j]==1) bshot[i]->setAlpha(bshot[i]->getAlpha()+shiftAlpha[j]);
                             else if(absAlpha[j]==2) bshot[i]->setAlpha(bshot[i]->getAlpha()*shiftAlpha[j]);
           }
       }
       
       bshot[i]->update();
       
       if(bshot[i]->getX() > (1600+bshot[i]->getRadius())||bshot[i]->getX() < (-800-bshot[i]->getRadius())||bshot[i]->getY() > (1200+bshot[i]->getRadius())||bshot[i]->getY() < (-600-bshot[i]->getRadius()))
       bshot[i]->hit();
       }
       if(timer%interval==0&&alive)
       {
           for(i=activeIndex; i<activeIndex + wave; i++)
             {
                   bshot[i]->activate();
                   bshot[i]->teleport(ox, oy);
             }
         
           activeIndex+=wave;
           if(activeIndex>10000-waveSize)activeIndex = 0;
           else if(bshot[activeIndex]->getX()==-1||activeIndex>10000-waveSize) activeIndex = 0;
       }
       
       timer++;
}

void BossPattern::setup(float _n1, float _n2, float minspeed, float maxspeed, float theta, float dtheta, int _interval, int _type, bool _aimed, int wave)
{
     int i, n;
     float n1, n2;
     
     aimed = _aimed;
     
     if(_n1*_n2>10000)
     {
         _n1=16;
         _n2=8;
     }
     
     if (wave>10000) wave = 10000;
     else if (wave<1) wave = 1;
     
       type = _type;
       interval = _interval;
     
     switch(type)
     {
                 case 1://radial simples
                      {
                           waveSize = (int)_n1*_n2;
                                 
                           for(i=0; i<10000/waveSize; i++)
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n1*_n2 + n2);
                                 if(_n2>1)
                                 bshot[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*(n2/(_n2-1)), theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 else
                                 bshot[n]->shoot(0, 0, minspeed, theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 
                                 bthetaorig[n] = bshot[n]->getTheta();
                                 bspeedorig[n] = bshot[n]->getSpeed();
                                 baccelorig[n] = bshot[n]->getAccel();
                                 brotorig[n] = bshot[n]->getRotation();
                                 balphaorig[n] = bshot[n]->getAlpha();
                                 } 
                     
                      }break;
                 case 2://aleatório
                      {
                            waveSize = (int)_n1*_n2;
                            for(i=0; i<10000; i++)
                             {
                                     bshot[i]->shoot(0, 0,minspeed+(float)rand()/((float)RAND_MAX/(maxspeed-minspeed)),(float)rand()/((float)RAND_MAX), true, 1, 0, 0, 0);
                                     bthetaorig[i] = bshot[i]->getTheta();
                             }     
                         
                      }break;
                 case 3://rajada centralizada
                      {
                            waveSize = (int)_n1*_n2;
                                 
                           for(i=0; i<10000/waveSize; i++)
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n2*_n1 + n1);
                                 if(_n2>1)
                                 bshot[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*(n2/(_n2-1)), theta-(dtheta/2) + dtheta*((n1+0.5)/_n1), false, 1, 0, 0, 0);
                                 else
                                 bshot[n]->shoot(0, 0, minspeed, theta-(dtheta/2) + dtheta*((n1+0.5)/_n1), false, 1, 0, 0, 0);
                                 
                                 bthetaorig[n] = bshot[n]->getTheta();
                                 bspeedorig[n] = bshot[n]->getSpeed();
                                 baccelorig[n] = bshot[n]->getAccel();
                                 brotorig[n] = bshot[n]->getRotation();
                                 balphaorig[n] = bshot[n]->getAlpha();
                                 }     
                         
                      }break;
                 case 4://radial duplo
                      {
                            waveSize = (int)_n1*_n2;
                                 
                           for(i=0; i<10000/waveSize; i++)
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n1*_n2 + n2);
                                 if(n%2==0)
                                 {
                                 if(_n2>1)   
                                 bshot[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*(n2/(_n2-1)), theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 else
                                 bshot[n]->shoot(0, 0, minspeed, theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 }
                                 else
                                 {
                                 if(_n2>1)   
                                 bshot[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*((n2-1)/(_n2-1)), theta+(n1/_n1)-dtheta*(n2-1), false, 1, 0, 0, 0);
                                 else
                                 bshot[n]->shoot(0, 0, minspeed, theta+(n1/_n1)-dtheta*(n2-1), false, 1, 0, 0, 0);
                                 }
                                 bthetaorig[n] = bshot[n]->getTheta();
                                 bspeedorig[n] = bshot[n]->getSpeed();
                                 baccelorig[n] = bshot[n]->getAccel();
                                 brotorig[n] = bshot[n]->getRotation();
                                 balphaorig[n] = bshot[n]->getAlpha();
                                 } 
                                 }break;
                 case 5://rajada aleatória
                      {
                            waveSize = (int)_n1*_n2;
                                 
                           for(i=0; i<10000/waveSize; i++)
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n1*_n2 + n2);
                                 bshot[n]->shoot(0, 0, minspeed + (float)rand()/((float)RAND_MAX/(maxspeed-minspeed)),(float)rand()/((float)RAND_MAX/(dtheta))-(dtheta/2), false, 1, 0, 0, 0);
                                 bthetaorig[n] = bshot[n]->getTheta();
                                 bspeedorig[n] = bshot[n]->getSpeed();
                                 baccelorig[n] = bshot[n]->getAccel();
                                 brotorig[n] = bshot[n]->getRotation();
                                 balphaorig[n] = bshot[n]->getAlpha();
                                 }     
                         
                      }break;
                 case 6://radial modificado (ângulo acelerado)
                      {
                            waveSize = (int)_n1*_n2;
                                 
                           for(i=0; i<10000/waveSize; i++)
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n2*_n1 + n1);
                                 
                                 if(_n2>1)   
                                 bshot[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*(n2/(_n2-1)), theta+(n1/_n1)+dtheta*n2*n2, false, 1, 0, 0, 0);
                                 else
                                 bshot[n]->shoot(0, 0, minspeed, theta+((n1+i)/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 
                                 bthetaorig[n] = bshot[n]->getTheta();
                                 bspeedorig[n] = bshot[n]->getSpeed();
                                 baccelorig[n] = bshot[n]->getAccel();
                                 brotorig[n] = bshot[n]->getRotation();
                                 balphaorig[n] = bshot[n]->getAlpha();
                                 } 
                                 }break;
                 case 7://radial duplo modificado
                      {
                            waveSize = (int)_n1*_n2;
                                 
                           for(i=0; i<10000/waveSize; i++)
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n2*_n1 + n1);
                                 if(n%2==0)
                                 {
                                 if(_n2>1)   
                                 bshot[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*(n2/(_n2-1)), theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 else
                                 bshot[n]->shoot(0, 0, minspeed, theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 }
                                 else
                                 {
                                 if(_n2>1)   
                                 bshot[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*((n2-1)/(_n2-1)), theta+(n1/_n1)-dtheta*(n2-1), false, 1, 0, 0, 0);
                                 else
                                 bshot[n]->shoot(0, 0, minspeed, theta+(n1/_n1)-dtheta*(n2-1), false, 1, 0, 0, 0);
                                 }
                                 bthetaorig[n] = bshot[n]->getTheta();
                                 bspeedorig[n] = bshot[n]->getSpeed();
                                 baccelorig[n] = bshot[n]->getAccel();
                                 brotorig[n] = bshot[n]->getRotation();
                                 balphaorig[n] = bshot[n]->getAlpha();
                                 } 
                                 }break;
                 case 8://radial duplo modificado 2
                      {
                            waveSize = (int)_n1*_n2;
                                 
                           for(i=0; i<10000/waveSize; i++)
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n2*_n1 + n1);
                                 if(n%2==0)
                                 {
                                 if(_n2>1)   
                                 bshot[n]->shoot(0, 0, maxspeed - (maxspeed-minspeed)*4*((n2-_n2/2)*(n2-_n2/2)/(_n2*_n2)), theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 else
                                 bshot[n]->shoot(0, 0, minspeed, theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 }
                                 else
                                 {
                                 if(_n2>1)   
                                 bshot[n]->shoot(0, 0, maxspeed - (maxspeed-minspeed)*4*((n2-_n2/2)*(n2-_n2/2)/(_n2*_n2)), theta+(n1/_n1)+dtheta*(n2-1), false, 1, 0, 0, 0);
                                 else
                                 bshot[n]->shoot(0, 0, minspeed, theta+(n1/_n1)-dtheta*(n2-1), false, 1, 0, 0, 0);
                                 }
                                 bthetaorig[n] = bshot[n]->getTheta();
                                 bspeedorig[n] = bshot[n]->getSpeed();
                                 baccelorig[n] = bshot[n]->getAccel();
                                 brotorig[n] = bshot[n]->getRotation();
                                 balphaorig[n] = bshot[n]->getAlpha();
                                 } 
                                 }break;
                      
     }
     waveSize = wave;
}

   
variableShot** BossPattern::getShot()
 {
        return bshot;
 }
             
void BossPattern::aim(float _theta)
 {
        int i;
     
     for(i=activeIndex; i<activeIndex + waveSize; i++)
     {
     bshot[i]->hit();
     bshot[i]->setTheta(bthetaorig[i] + _theta);         
     }        
 }
