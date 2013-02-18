#include "ShotPattern.h"
#include "stdio.h"

int ShotPattern::currentIndex = 0;
Shot* ShotPattern::shot[20000];

ShotPattern::ShotPattern(hgeSprite *pspr, float radius)
{
       int i;

       
       for(i=0; i<20000; i++)
       {
                if(shot[i]==NULL) shot[i] = new Shot(pspr, radius);
                pattern[i] = new Shot(pspr, radius);

       }

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

void ShotPattern::updatePattern(float theta)
{
       int i, j;
       
    
       if(timer%interval==0)
       {
           if((currentIndex+waveSize)<=20000)
           {
               for(i=currentIndex; i<currentIndex + waveSize; i++)
                 {
                       shot[i]->setRotation(pattern[i+activeIndex-currentIndex]->getRotation());
                       shot[i]->setAccel(pattern[i+activeIndex-currentIndex]->getAccel());
                       
                       if(aimed)
                         shot[i]->setTheta(pattern[i+activeIndex-currentIndex]->getTheta()+theta);
                       else
                         shot[i]->setTheta(pattern[i+activeIndex-currentIndex]->getTheta());
                       
                       shot[i]->setSpeed(pattern[i+activeIndex-currentIndex]->getSpeed());
                       shot[i]->setAlpha(pattern[i+activeIndex-currentIndex]->getAlpha());
                       shot[i]->teleport(ox, oy);
                       shot[i]->activate();
                       
                       for(j=0; j<10; j++){
                       if((i-currentIndex)%div[j]==0)
                       shot[i]->shift(shiftTimer[j], shiftSpeed[j], shiftTheta[j], shiftAccel[j], shiftRot[j], shiftAlpha[j], absSpeed[j], absTheta[j], absAccel[j], absRot[j], absAlpha[j], j, singleShift[j]);
                       }
                       
                 }
             }
           else{
                currentIndex = 0;
                for(i=0; i<waveSize; i++)
                 {
                       shot[i]->setRotation(pattern[i+activeIndex-currentIndex]->getRotation());
                       shot[i]->setAccel(pattern[i+activeIndex-currentIndex]->getAccel());
                       
                       if(aimed)
                         shot[i]->setTheta(pattern[i+activeIndex-currentIndex]->getTheta()+theta);
                       else
                         shot[i]->setTheta(pattern[i+activeIndex-currentIndex]->getTheta());
                         
                       shot[i]->setSpeed(pattern[i+activeIndex-currentIndex]->getSpeed());
                       shot[i]->setAlpha(pattern[i+activeIndex-currentIndex]->getAlpha());
                       shot[i]->teleport(ox, oy);
                       shot[i]->activate();
                       
                       for(j=0; j<10; j++){
                       if((i-currentIndex)%div[j]==0)
                       shot[i]->shift(shiftTimer[j], shiftSpeed[j], shiftTheta[j], shiftAccel[j], shiftRot[j], shiftAlpha[j], absSpeed[j], absTheta[j], absAccel[j], absRot[j], absAlpha[j], j, singleShift[j]);
                       }
                 }
           }
         
           activeIndex+=waveSize;
           currentIndex+=waveSize;
           if(activeIndex+waveSize>patternSize) activeIndex = 0;
         
       }
       
       
       timer++;
}

void ShotPattern::updateShots()
{
     int i;
     
     for(i=0; i<20000; i++)
       {
              if(shot[i]->isActive()) 
              {
                  shot[i]->update();
                  if(shot[i]->getX() > (1600+shot[i]->getRadius())||shot[i]->getX() < (-800-shot[i]->getRadius())||shot[i]->getY() > (1200+shot[i]->getRadius())||shot[i]->getY() < (-600-shot[i]->getRadius()))
                  shot[i]->hit();
              }
       }
     
}

void ShotPattern::reset()
{
     int i;
     currentIndex = 0;
     for(i=0; i<20000; i++)
       {shot[i] = NULL;
       }
}

int ShotPattern::getCurrentIndex()
{
    return currentIndex;
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

Shot** ShotPattern::getShot()
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
     
     for(i=currentIndex; i<currentIndex + waveSize; i++)
     {
     shot[i]->hit();
     shot[i]->setTheta(shot[i]->getTheta() + _theta);         
     }
}

bool ShotPattern::isAimed()
{
     return aimed;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     SimpleRadialPattern::SimpleRadialPattern(hgeSprite *pspr, float radius, float _n1, float _n2, float minspeed, float maxspeed, float theta, float dtheta, int _interval, bool _aimed, int wave) : ShotPattern(pspr, radius){
       int i, n;
       float n1, n2;
       
       aimed = _aimed;
     
         if(_n1*_n2>20000)
         {
             _n1=20000;
             _n2=1;
         }
         
     
       interval = _interval;
       
       
       patternSize = (int)_n1*_n2;
       if (wave>patternSize) waveSize = patternSize;
       else if(wave<1) waveSize = 1;
       else waveSize = wave;
                                 
                           
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (n1*_n2 + n2);
                                 if(_n2>1)
                                 pattern[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*(n2/(_n2-1)), theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 else
                                 pattern[n]->shoot(0, 0, minspeed, theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 }
                                 
   
       }
       ////////////////////////////////////////////////////////////////////////////////////
       DoubleRadialPattern::DoubleRadialPattern(hgeSprite *pspr, float radius, float _n1, float _n2, float minspeed, float maxspeed, float theta, float dtheta, int _interval, bool _aimed, int wave) : ShotPattern(pspr, radius){
       int i, n;
       float n1, n2;
       
       aimed = _aimed;
     
         if(_n1*_n2>20000)
         {
             _n1=20000;
             _n2=1;
         }
         
     
       interval = _interval;
       
       
       patternSize = (int)_n1*_n2;
       if (wave>patternSize) waveSize = patternSize;
       else if(wave<1) waveSize = 1;
       else waveSize = wave;
                                 
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (n1*_n2 + n2);
                                 if(n%2==0)
                                 {
                                 if(_n2>1)   
                                 pattern[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*(n2/(_n2-1)), theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 else
                                 pattern[n]->shoot(0, 0, minspeed, theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                 }
                                 else
                                 {
                                 if(_n2>1)   
                                 pattern[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*((n2-1)/(_n2-1)), theta+(n1/_n1)-dtheta*(n2-1), false, 1, 0, 0, 0);
                                 else
                                 pattern[n]->shoot(0, 0, minspeed, theta+(n1/_n1)-dtheta*(n2-1), false, 1, 0, 0, 0);
                                 }
                                 }
                                 
   
       }
       //////////////////////////////////////////////////////////////////////////////////////////////////////////
       RandomPattern::RandomPattern(hgeSprite *pspr, float radius, float minspeed, float maxspeed, int _interval, int wave) : ShotPattern(pspr, radius){
       int i;

       interval = _interval;
       patternSize = 20000;
       if (wave>patternSize) waveSize = patternSize;
       else if(wave<1) waveSize = 1;
       else waveSize = wave;
                                 
                            for(i=0; i<patternSize; i++)
                                 pattern[i]->shoot(0, 0,minspeed+(float)rand()/((float)RAND_MAX/(maxspeed-minspeed)),(float)rand()/((float)RAND_MAX), true, 1, 0, 0, 0);

   
       }
       ///////////////////////////////////////////////////////////////////////////////////////////////////////////
       CentralBurstPattern::CentralBurstPattern(hgeSprite *pspr, float radius, float _n1, float _n2, float minspeed, float maxspeed, float theta, float dtheta, int _interval, bool _aimed, int wave) : ShotPattern(pspr, radius){
       int i, n;
       float n1, n2;
       
       aimed = _aimed;
     
         if(_n1*_n2>20000)
         {
             _n1=20000;
             _n2=1;
         }
         
     
       interval = _interval;
       
       
       patternSize = (int)_n1*_n2;
       if (wave>patternSize) waveSize = patternSize;
       else if(wave<1) waveSize = 1;
       else waveSize = wave;
                         
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (n2*_n1 + n1);
                                 if(_n2>1)
                                 pattern[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*(n2/(_n2-1)), theta-(dtheta/2) + dtheta*((n1+0.5)/_n1), false, 1, 0, 0, 0);
                                 else
                                 pattern[n]->shoot(0, 0, minspeed, theta-(dtheta/2) + dtheta*((n1+0.5)/_n1), false, 1, 0, 0, 0);

                                 }
                                 
   
       }
       
                                                        

        //////////////////////////////////////////////////////////////////////////
        RandomBurstPattern::RandomBurstPattern(hgeSprite *pspr, float radius, float minspeed, float maxspeed, float theta, float dtheta, int _interval, bool _aimed, int wave) : ShotPattern(pspr, radius){
           int i, n;
           float n1, n2;
           
           aimed = _aimed;
           interval = _interval;
           
           
           patternSize = 20000;
           if (wave>patternSize) waveSize = patternSize;
           else if(wave<1) waveSize = 1;
           else waveSize = wave;
           
                                  for(i=0; i<20000; i++)
                                     {
                                     pattern[i]->shoot(0, 0, minspeed + (float)rand()/((float)RAND_MAX/(maxspeed-minspeed)),(float)rand()/((float)RAND_MAX/(dtheta))-(dtheta/2), false, 1, 0, 0, 0);

                                     }   
                                     
       
           }
       ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       CustomRadialPattern1::CustomRadialPattern1(hgeSprite *pspr, float radius, float _n1, float _n2, float minspeed, float maxspeed, float theta, float dtheta, int _interval, bool _aimed, int wave) : ShotPattern(pspr, radius){
       int i, n;
       float n1, n2;
       
       aimed = _aimed;
     
         if(_n1*_n2>20000)
         {
             _n1=20000;
             _n2=1;
         }
         
     
       interval = _interval;
       
       
       patternSize = (int)_n1*_n2;
       if (wave>patternSize) waveSize = patternSize;
       else if(wave<1) waveSize = 1;
       else waveSize = wave;
                                 
                              
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (n2*_n1 + n1);
                                 
                                 if(_n2>1)   
                                 pattern[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*(n2/(_n2-1)), theta+(n1/_n1)+dtheta*n2*n2, false, 1, 0, 0, 0);
                                 else
                                 pattern[n]->shoot(0, 0, minspeed, theta+((n1+i)/_n1)+dtheta*n2, false, 1, 0, 0, 0);

                                 } 
                                 
   
       }
       ///////////////////////////////////////////////////////////////////////////////////
       CustomRadialPattern2::CustomRadialPattern2(hgeSprite *pspr, float radius, float _n1, float _n2, float minspeed, float maxspeed, float theta, float dtheta, int _interval, bool _aimed, int wave) : ShotPattern(pspr, radius){
       int i, n;
       float n1, n2;
       
       aimed = _aimed;
     
         if(_n1*_n2>20000)
         {
             _n1=20000;
             _n2=1;
         }
         
     
       interval = _interval;
       
       
       patternSize = (int)_n1*_n2;
       if (wave>patternSize) waveSize = patternSize;
       else if(wave<1) waveSize = 1;
       else waveSize = wave;
                                 
                              
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n2*_n1 + n1);
                                     if(n%2==0)
                                     {
                                         if(_n2>1)   
                                         pattern[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*(n2/(_n2-1)), theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                         else
                                         pattern[n]->shoot(0, 0, minspeed, theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                     }
                                     else
                                     {
                                         if(_n2>1)   
                                         pattern[n]->shoot(0, 0, minspeed + (maxspeed-minspeed)*((n2-1)/(_n2-1)), theta+(n1/_n1)-dtheta*(n2-1), false, 1, 0, 0, 0);
                                         else
                                         pattern[n]->shoot(0, 0, minspeed, theta+(n1/_n1)-dtheta*(n2-1), false, 1, 0, 0, 0);
                                     }

                                 } 
                                 
   
       }
       ///////////////////////////////////////////////////////////////////////////////////       
       CustomRadialPattern3::CustomRadialPattern3(hgeSprite *pspr, float radius, float _n1, float _n2, float minspeed, float maxspeed, float theta, float dtheta, int _interval, bool _aimed, int wave) : ShotPattern(pspr, radius){
       int i, n;
       float n1, n2;
       
       aimed = _aimed;
     
         if(_n1*_n2>20000)
         {
             _n1=20000;
             _n2=1;
         }
         
     
       interval = _interval;
       
       
       patternSize = (int)_n1*_n2;
       if (wave>patternSize) waveSize = patternSize;
       else if(wave<1) waveSize = 1;
       else waveSize = wave;
                                 
                              
                              for(n1=0; n1<(_n1); n1++)
                                 for(n2=0; n2<_n2; n2++)
                                 {
                                 n = (int) (i*waveSize + n1*_n2 + n2);

                                     if(_n2>1)   
                                     pattern[n]->shoot(0, 0, maxspeed - (maxspeed-minspeed)*4*((n2-_n2/2)*(n2-_n2/2)/(_n2*_n2)), theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);
                                     else
                                     pattern[n]->shoot(0, 0, minspeed, theta+(n1/_n1)+dtheta*n2, false, 1, 0, 0, 0);

                                 } 

       }
