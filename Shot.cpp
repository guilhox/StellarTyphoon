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
     friendly = true;
                     
}

void Shot::update()
{
     if(active)
     {
     x += speed*cosf(2*3.1415926*theta);
     y += speed*sinf(2*3.1415926*theta);
     timer++;
     }
}

void Shot::shoot(float _x, float _y,  float _speed, float _theta, bool _friendly, int _power)
{
     x = _x;
     y = _y;
     theta = _theta;
     power = _power;
     speed = _speed;
     friendly = _friendly;     
}

hgeSprite Shot::getSprite()
{
      return *sspr;         
}

bool Shot::isFriendly()
{
      return friendly;  
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

/////////////////////////////////////////////////////////////
variableShot::variableShot(hgeSprite *_sspr, float _radius) : Shot(_sspr, radius)
{
     sspr = _sspr;
     radius = _radius;
     x = -1;
     y = -1;
     ox = 0;
     oy = 0;
     theta = 0;
     power = 0;
     speed = 0;
     friendly = true;
     active = false;
     timer = 0;
     
     accel = 0;
     rotation = 0;
     alpha = 0;
                     
}

void variableShot::update()
{
     if(active)
     {
      x += speed*cosf(2*3.1415926*theta);
      y += speed*sinf(2*3.1415926*theta);
      speed += accel;
      theta += rotation;
      rotation += alpha;
      timer++;
      }
}

void variableShot::shoot(float _x, float _y,  float _speed, float _theta, bool _friendly, int _power, float _accel, float _rotation, float _alpha)
{
     x = _x;
     y = _y;
     ox = _x;
     oy = _y;
     theta = _theta;
     power = _power;
     speed = _speed;
     friendly = _friendly;    
     
     accel = _accel;
     rotation = _rotation;
     alpha = _alpha; 
}

void variableShot::setSpeed(float newSpeed)
{
     speed = newSpeed;
}

void variableShot::setAccel(float newAccel)
{
     accel = newAccel;
}

void variableShot::setRotation(float newRotation)
{
     rotation = newRotation;
}

void variableShot::setAlpha(float newAlpha)
{
     alpha = newAlpha;
}

float variableShot::getAccel()
{
      return accel;
}

float variableShot::getRotation()
{
      return rotation;
}

float variableShot::getAlpha()
{
      return alpha;      
}

float variableShot::getOx()
{
      return ox;      
}

float variableShot::getOy()
{
      return oy;      
}

void Shot::teleport(float _x, float _y)
{
     x=_x;
     y=_y;
}
