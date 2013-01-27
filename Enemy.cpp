#include "Enemy.h"

Enemy::Enemy(hgeSprite *_espr, int _spawnTime, float _ox, float _oy, float _fx, float _fy, float _speed, int _health)
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
     existence = false;
     spawnTime = _spawnTime;
}

void Enemy::update()
{
     timer++;
     
     if(timer==spawnTime)
     {
     alive = true;           
     existence = true;         
     }
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
         
     }
     
}

/*void Enemy::spawn(float _ox, float _oy, int _health)
{
     ox=_ox;
     oy=_oy;
     x=_sx;
     y=_sy;
     health=_health;
     alive = true;
}*/

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

/*void Enemy::setVariableShotPattern(hgeSprite *sspr, float _n1, float _n2, float sspeed, float dspeed, float theta, float dtheta, int type, float accel, float rotation, float alpha)
{
     int i;
     float n1, n2;
     
     for(i=0; i<2000; i++)
     {
              shot[i] = new variableShot(sspr);
     }
     
     switch(type)
     {
                 case 1://espiral duplo (alterar rotação a cada frame!!!)
                      {
                            
                      }break;
     }     
     
}*/

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

bool Enemy::exists()
{
      return existence;     
}

void Enemy::setExist(bool e){
     existence = e;
     }
/////////////////////////////////////////////////////////////////////

Boss::Boss (hgeSprite *_espr, int _spawnTime, float _ox, float _oy, float _fx, float _fy, float _speed, int _health, int _nPatterns) : Enemy(_espr, _spawnTime, _ox, _oy, _fx, _fy, _speed, _health)
{
     int i;      

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
     nPatterns = _nPatterns;
     spawnTime = _spawnTime;
     
     if(nPatterns>20) nPatterns = 20;
     if(nPatterns<4) nPatterns = 4;
     
     if(health<1000) health = 1000;
     
     activePattern = 0;
     
     for(i=0; i<nPatterns; i++)
     {
     triggerPattern[i] = health*(1-i/nPatterns);
     }
     
     for(i=nPatterns; i<20; i++)
     {
     triggerPattern[i] = 0;
     }
           
}

void Boss::update()
{
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
         
         if(health<=triggerPattern[activePattern])
         activePattern++;
         
     }
}
void Boss::setShotPattern(ShotPattern *_pattern, float trigger, int index)
{
     if(index>nPatterns) index = nPatterns;
     if(index<0) index = 0;
     
     pattern[index] = _pattern;
     triggerPattern[index] = trigger;
}

void Boss::setShotPattern(ShotPattern *_pattern, int index)
{
     if(index>nPatterns) index = nPatterns;
     if(index<0) index = 0;
     
     pattern[index] = _pattern;     
}

ShotPattern* Boss::getShotPattern(int index)
{
     if(index>nPatterns) index = nPatterns;
     if(index<0) index = 0;
     
     return pattern[index];             
}

ShotPattern* Boss::getActivePattern()
{
     return pattern[activePattern];             
}
