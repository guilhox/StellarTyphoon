#include "Shot.h"

Shot::Shot(hgeSprite *_sspr, float _radius)
{
     sspr = _sspr;
     radius = _radius;
     x = -1;
     y = -1;
     theta = 0;
     power = 0;
     speed = 0;
     timer = 0;
     active = false;
     shifted = false;
     
     accel = 0;
     rotation = 0;
     alpha = 0;
                     
}

void Shot::update()
{
     int i;
     
     if(active)
     {
     x += speed*cosf(2*3.1415926*theta);
     y += speed*sinf(2*3.1415926*theta);
     speed += accel;
     theta += rotation;
     rotation += alpha;
     timer++;
     
     if(shifted)
     for(i=0; i<10; i++)
               {
               if(shiftTimer[i]>0&&((timer == shiftTimer[i]&&singleShift[i]==true)||(timer>0&&timer%shiftTimer[i]==0&&singleShift[i]==false)))
                       {
            
                                         if(absSpeed[i]==0) speed = shiftSpeed[i];
                                         else if(absSpeed[i]==1) speed += shiftSpeed[i];
                                         else if(absSpeed[i]==2) speed *= shiftSpeed[i];
                                         if(absAccel[i]==0) accel = shiftAccel[i];
                                         else if(absAccel[i]==1) accel += shiftAccel[i];
                                         else if(absAccel[i]==2) accel *= shiftAccel[i];
                                         if(absTheta[i]==0) theta = shiftTheta[i];
                                         else if(absTheta[i]==1)  theta += shiftTheta[i];
                                         else if(absTheta[i]==2)  theta *= shiftTheta[i];
                                         if(absRot[i]==0) rotation = shiftRot[i];
                                         else if(absRot[i]==1) rotation += shiftRot[i];
                                         else if(absRot[i]==2) rotation *= shiftRot[i];
                                         if(absAlpha[i]==0) alpha = shiftAlpha[i];
                                         else if(absAlpha[i]==1) alpha += shiftAlpha[i];
                                         else if(absAlpha[i]==2) alpha *= shiftAlpha[i];
                       }
               }
     }
}

void Shot::shoot(float _x, float _y,  float _speed, float _theta, bool _friendly, int _power, float _accel, float _rotation, float _alpha)
{
     x = _x;
     y = _y;
     ox = x;
     oy = y;
     theta = _theta;
     power = _power;
     speed = _speed;
     
     accel = _accel;
     rotation = _rotation;
     alpha = _alpha;  
}

hgeSprite Shot::getSprite()
{
      return *sspr;         
}

float Shot::getSpeed()
{
      return speed;
}

float Shot::getX()
{
      return x;
}

float Shot::getY()
{
      return y;
}

float Shot::getTheta()
{
      return theta;
}

float Shot::getRadius()
{
      return radius;
}

int Shot::getPower()
{
      return power;
}

int Shot::getTimer()
{
      return timer;
}

void Shot::setTheta(float newTheta)
{
     theta = newTheta;
}

void Shot::activate()
{
      active = true;
}

bool Shot::isActive()
{
      return active;
}

void Shot::hit()
{
       active = false;
       timer = 0;
}

void Shot::setID(int _ID)
{
     ID = _ID;
}

int Shot::getID()
{
    return ID;
}


void Shot::setSpeed(float newSpeed)
{
     speed = newSpeed;
}

void Shot::setAccel(float newAccel)
{
     accel = newAccel;
}

void Shot::setRotation(float newRotation)
{
     rotation = newRotation;
}

void Shot::setAlpha(float newAlpha)
{
     alpha = newAlpha;
}

float Shot::getAccel()
{
      return accel;
}

float Shot::getRotation()
{
      return rotation;
}

float Shot::getAlpha()
{
      return alpha;      
}

float Shot::getOx()
{
      return ox;      
}

float Shot::getOy()
{
      return oy;      
}

void Shot::teleport(float _x, float _y)
{
     x=_x;
     y=_y;
}

void Shot::shift(int timer, float speed, float theta, float accel, float rotation, float alpha, int _absSpeed, int _absTheta, int _absAccel, int _absRot, int _absAlpha, int index, bool single)
{
     shifted = true;
     
       shiftTimer[index] = timer;
       shiftSpeed[index] = speed;
       shiftTheta[index] = theta;
       shiftAccel[index] = accel;
       shiftRot[index] = rotation;
       shiftAlpha[index] = alpha;
       
       absSpeed[index] = _absSpeed;
       absTheta[index] = _absTheta;
       absRot[index] = _absRot;
       absAccel[index] = _absAccel;
       absAlpha[index] = _absAlpha;
       
       singleShift[index] = single;
}
