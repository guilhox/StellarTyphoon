#include "Enemy.h"

Enemy::Enemy(hgeSprite *_espr, int _spawnTime, int _warmUpTime, float _ox, float _oy, float _fx, float _fy, float _speed, int _health)
{               
     espr=_espr;
     ox=_ox;
     oy=_oy;
     x=_ox;
     y=_oy;
     health=_health;
     fx=_fx;
     fy=_fy;
     speed=_speed;
     timer = 0;
     alive = false;
     spawnTime = _spawnTime;
     warmUpTime = _warmUpTime;
}

void Enemy::update(float theta)
{
     timer++;
     
     if(timer==spawnTime)
     alive = true;             

     if(alive)
     {
         if(distance(x, y, fx, fy)<speed&&speed>0)
         {
                        x=fx;
                        y=fy;
                        speed=0;
         }
         else
         {
             x+=speed*((fx-ox)/distance(ox, oy, fx, fy));
             y+=speed*((fy-oy)/distance(ox, oy, fx, fy));
         }
         
         if(timer>=warmUpTime+spawnTime&&pattern!=NULL)
         {
         pattern->moveOrigin(x, y);
         pattern->updatePattern(theta);
         }
     }
     
}

void Enemy::moveTo(float _fx, float _fy, float _speed)
{
     ox=x;
     oy=y;
     fx=_fx;
     fy=_fy;
     speed=_speed;
}


void Enemy::setShotPattern(ShotPattern *_pattern)
{
     pattern = _pattern;
}

ShotPattern* Enemy::getShotPattern()
{
      return pattern;
}

hgeSprite* Enemy::getSprite()
{
      return espr;          
}

float Enemy::getSpeed()
{
      return speed;
}

float Enemy::getX()
{
      return x;
}

float Enemy::getY()
{
      return y;
}

int Enemy::getHealth()
{
      return health;
}

bool Enemy::isAlive()
{
     return alive;
}

void Enemy::die()
{
     speed=0;
     x=-1;
     y=-1;
     alive = false;
}

void Enemy::damage(int power)
{
     health-=power;
}

float Enemy::distance (float x1, float y1, float x2, float y2)
{
      return sqrtf((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

/////////////////////////////////////////////////////////////////////

Boss::Boss (hgeSprite *_espr, int _spawnTime, int _warmUpTime, float _ox, float _oy, float _fx, float _fy, float _speed, int _health, int _nPatterns) : Enemy(_espr, _spawnTime, _warmUpTime, _ox, _oy, _fx, _fy, _speed, _health)
{
     int i;      

     timer = 0;
     alive = false;
     nPatterns = _nPatterns;
     
     if(nPatterns>20) nPatterns = 20;
     if(nPatterns<4) nPatterns = 4;
     
     if(health<1000) health = 1000;
     
     activePattern = 0;
     
     for(i=0; i<nPatterns; i++)
     {
     triggerPattern[i] = health*(1-((float)i)/(float)nPatterns);
     }
     
     for(i=nPatterns; i<20; i++)
     {
     pattern[i] = new ShotPattern(_espr, 1);
     triggerPattern[i] = 0;
     }
           
}

void Boss::update(float theta)
{
     int i;
     
     timer++;
     
     if(timer==spawnTime)
     alive = true;   

     //if(timer==spawnTime + duration)
     //alive = false;                    
     
     if(alive)
     {
         if(distance(x, y, fx, fy)<speed&&speed>0)
         {
                        x=fx;
                        y=fy;
                        speed=0;
         }
         else
         {
             x+=speed*((fx-ox)/distance(ox, oy, fx, fy));
             y+=speed*((fy-oy)/distance(ox, oy, fx, fy));
         }
         
         if(health<triggerPattern[activePattern+1])
         {
         for(i=0; i<20000; i++)
         pattern[activePattern]->getShot()[i]->hit();
         
         activePattern++;
         }
         if(timer>=warmUpTime+spawnTime&&pattern[activePattern]!=NULL)
         {
         pattern[activePattern]->moveOrigin(x, y);
         pattern[activePattern]->updatePattern(theta);
         }
     }
}
void Boss::setShotPattern(ShotPattern *_pattern, float trigger, int index)
{
     if(index>nPatterns) index = nPatterns-1;
     if(index<0) index = 0;
     
     pattern[index] = _pattern;
     triggerPattern[index] = trigger;
}

void Boss::setShotPattern(ShotPattern *_pattern, int index)
{
     if(index>nPatterns) index = nPatterns-1;
     if(index<0) index = 0;
     
     pattern[index] = _pattern;     
}

ShotPattern* Boss::getShotPattern(int index)
{
     if(index>nPatterns) index = nPatterns-1;
     if(index<0) index = 0;
     
     return pattern[index];             
}

ShotPattern* Boss::getActivePattern()
{
     return pattern[activePattern];             
}
