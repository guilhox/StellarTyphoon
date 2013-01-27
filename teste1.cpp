/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut06 - Creating menus
*/


// Copy the files "menu.wav", "font1.fnt", "font1.png",
// "bg.png" and "cursor.png" from the folder "precompiled"
// to the folder with executable file. Also copy hge.dll
// and bass.dll to the same folder.


#include "hge.h"
#include "hgefont.h"
#include "hgegui.h"
#include "hgeparticle.h"
#include "hgesprite.h"

#include "Stage.h"

#include "menuitem.h"

#include <math.h>
#include <ctime>


// Pointer to the HGE interface.
// Helper classes require this to work.
HGE *hge=0;

// Some resource handles
HEFFECT				snd, osnd;
HTEXTURE			tex, otex, ntex, stex, ttex;
hgeQuad				quad;

// Pointers to the HGE objects we will use
hgeGUI				*gui;
hgeFont				*fnt;
hgeSprite			*spr, *ospr, *sspr, *sspr2, *sspr3, *espr, *title, *play;
hgeSprite*			spt, *sprites[221];
hgeParticleSystem*	par;

variableShot *tiro[2000];
//Shot *tiroInimigo[2000];
//ShotPattern *p, *p2;
//Enemy *inimigo;
Stage *FASE;

// Some "gameplay" variables
float ox=100.0f, oy=300.0f, sx[50], sy[50], acc=0, timetot=0;
float odx=0.0f, ody=0.0f;
float theta=0, itheta = 0, thetaorig[1600], sp=4;
int cont = 10, cont2 = 30, deathcont = 60, frametot=0, h=0, dir = 1, s=0, s2=0, pattern = 5, pn=0, espn=0, sprshift;

bool g = false, e = false, e2 = true;
const float grav=3;
const float friction=1.00f;

// Play sound effect
void boom() {
	int pan=int((ox-400)/4);
	float pitch=(odx*odx+ody*ody)*0.0005f+0.2f;
	hge->Effect_PlayEx(snd,100,pan,pitch);
}

float distance (float x1, float y1, float x2, float y2)
{
      return sqrtf((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

float aimShot(float x1, float y1, float x2, float y2)
{
      if(x1>x2)   return atan((y2-y1)/(x2-x1))/(2*3.1415926535) + 0.5;      
      else         return atan((y2-y1)/(x2-x1))/(2*3.1415926535);
}

bool FrameFunc()
{
	float dt=hge->Timer_GetDelta();
	static float t=0.0f;
	float speed=8, aim=0;
	float tx,ty;
	int id, i, j;
	static int lastid=0;
	bool pressed = false;

	// If ESCAPE was pressed, tell the GUI to finish
	
	// We update the GUI and take an action if
	// one of the menu items was selected
	if(g)
	{
         switch(espn)
         {
                     case 0:espr->SetTextureRect(180, 0, 40, 20, false); break;
                     case 1:espr->SetTextureRect(220, 0, 40, 20, false); break;
                     case 2:espr->SetTextureRect(260, 0, 40, 20, false); break;
                     case 3:espr->SetTextureRect(300, 0, 40, 20, false); break;
         }
         
         if(espn<3) espn++;
         else espn = 0;
         
         FASE->update(ox, oy);
                       /*if(frametot==60&&inimigo->isAlive())
                             inimigo->moveTo(700, 300, 5);
                             
                       if (cont2>0) cont2--;
                        
                        
                        if(frametot>300)
                        {
                             if(inimigo->isAlive())   
                             {                            
                              p->moveOrigin(inimigo->getX(), inimigo->getY());
                              p2->moveOrigin(inimigo->getX(), inimigo->getY());
                              p2->aim(aimShot(inimigo->getX(), inimigo->getY(), ox, oy));
                              }   
                        p->update(inimigo->isAlive());
                        p2->update(inimigo->isAlive());
                        }
                        
                        if(frametot>450&&inimigo->getSpeed()==0&&inimigo->isAlive())
                        {
                                if(inimigo->getY()>300) 
                                inimigo->moveTo(700, 100, 3);
                                else
                                inimigo->moveTo(700, 500, 3);                           
                        
                        
                        }*/
                        
           ospr->SetTextureRect(45, 0, 45, 32, false);
           sprshift = 0;
         	float dt=hge->Timer_GetDelta();
	// Process keys
	if (hge->Input_GetKeyState(HGEK_SHIFT))
          {
          speed=3;
          ospr->SetTextureRect(0, 0, 45, 32, false);
          sprshift = 45;
          }
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) g=false;
	if (hge->Input_GetKeyState(HGEK_LEFT)) ox-=speed;
	if (hge->Input_GetKeyState(HGEK_RIGHT)) ox+=speed;
    if (hge->Input_GetKeyState(HGEK_UP))
       {
       oy-=speed;
       ospr->SetTextureRect(90+sprshift, 0, 45, 32, false);
       ospr->SetFlip(false, false, false);
       }
       if (hge->Input_GetKeyState(HGEK_DOWN))
     {
      oy+=speed;
      ospr->SetTextureRect(90+sprshift, 0, 45, 32, false);
      ospr->SetFlip(false, true, false);
      }
	if (hge->Input_GetKeyState(HGEK_1)) 
    {pattern=1;
    for(i=0; i<2000; i++)
    tiro[i]->hit();
    }
	if (hge->Input_GetKeyState(HGEK_2)) 
    {pattern=2;
    for(i=0; i<2000; i++)
    tiro[i]->hit();
    }
	if (hge->Input_GetKeyState(HGEK_3))
	{pattern=3;
    for(i=0; i<2000; i++)
    tiro[i]->hit();
    }
	if (hge->Input_GetKeyState(HGEK_4))
	{pattern=4;
    for(i=0; i<2000; i++)
    tiro[i]->hit();
    }
    if (hge->Input_GetKeyState(HGEK_5))
	{pattern=5;
    for(i=0; i<2000; i++)
    tiro[i]->hit();
    }
    if (hge->Input_GetKeyState(HGEK_6))
	{pattern=6;
    for(i=0; i<2000; i++)
    tiro[i]->hit();
    }
	if (hge->Input_GetKeyState(HGEK_Z)&&cont==0)
                {
                 switch(pattern)
                 {
                                case 1:
                          {
                                for (i=0; i<8; i++)
                          {
                              if(!tiro[s]->isActive())
                              {
                              tiro[s]->activate();
                              
                          tiro[s]->shoot(ox, oy, sp, theta+(i*0.125), true, 10, 0, 0, 0); 
                          s++;
                          }
                          }                              
                          boom();
                          cont = 3;
                          theta += dir*0.0125;
                          sp++;
                          }break;
                          
                          case 2:
                               {
                                for (i=0; i<16; i++)
                          {
                              if(!tiro[s]->isActive())
                              {
                              tiro[s]->activate();
                              
                              if(i%2==0) 
                              tiro[s]->shoot(ox, oy, 8, i*(1.0/16.0)-theta, true, 20, 0, 0, 0); 
                              else
                              tiro[s]->shoot(ox, oy, 8, i*(1.0/16.0)+theta, true, 20, 0, 0, 0); 
                          
                          theta += 0.0005;
                          s++;
                          }
                          }                              
                          boom();
                          cont = 10;                    
                               }break;
                               
                          case 3:
                               {
                               
                              if(!tiro[s]->isActive())
                              {
                              tiro[s]->activate();
                              
                              tiro[s]->shoot(ox, oy, 4 + (float)rand()/((float)RAND_MAX/(16-2)),(float)rand()/((float)RAND_MAX), true, 10, 0, 0, 0);
                              s++;
                              tiro[s]->shoot(ox, oy, 4 + (float)rand()/((float)RAND_MAX/(16-2)),(float)rand()/((float)RAND_MAX), true, 10, 0, 0, 0); 
                              s++;
                              tiro[s]->shoot(ox, oy, 4 + (float)rand()/((float)RAND_MAX/(16-2)),(float)rand()/((float)RAND_MAX), true, 10, 0, 0, 0);
                              s++;
                              tiro[s]->shoot(ox, oy, 4 + (float)rand()/((float)RAND_MAX/(16-2)),(float)rand()/((float)RAND_MAX), true, 10, 0, 0, 0);  
                              
                              s++;
                              boom();
                              }
                          //cont = 1;                    
                               }break;
                               
                          case 4:
                               {
                                for (i=0; i<32; i++)
                          {
                              if(!tiro[s]->isActive())
                              {
                              tiro[s]->activate();
                              tiro[s]->shoot(ox, oy, 0, i*(1.0/32.0), true, 5, 0.25, 0, 0); 
                              s++;
                              boom();
                              }
                          }                              
                          
                          cont = 5;
                          }break;
                          case 5:
                               {
                                for (i=0; i<10; i++)
                                {
                                      if(!tiro[s]->isActive())
                                      {
                                      tiro[s]->activate();
                                      tiro[s]->shoot(ox, oy, 15, - 0.02 + 0.005*i, true, 1, 0, 0, 0); 
                                      s++;
                                      boom();
                                      }    
                                }
                                cont = 4;
                                }break; 
                          case 6:
                               {
                                for (i=0; i<6; i++)
                                {
                                      if(!tiro[s]->isActive())
                                      {
                                      tiro[s]->activate();
                                      if(i%2==0)
                                      tiro[s]->shoot(ox, oy, 0, 0.25-0.025*i, true, 2, 0.1, 0, 0); 
                                      else
                                      tiro[s]->shoot(ox, oy, 0, 0.725 + 0.025*i, true, 2, 0.1, 0, 0); 
                                      s++;
                                      boom();
                                      }    
                                }                               
                          
                          cont = 20;
                          }break;
                 }
                    
                 if(s>1800)
                 {
                          s=0;
                 }
                    
                    
                }

                if(sp==16) {sp=4; dir*=-1;}
                
                //inimigo->update();
                for(i=0; i<100; i++)
                FASE->getEnemy(i)->getSprite()->SetColor(0xFFBBBBBB);
                
                FASE->getBoss()->getSprite()->SetColor(0xFFBBBBBB);
                
                
    for(i=0; i<2000; i++)
       {
        tiro[i]->update();
        
        if (pattern==2&&distance(tiro[i]->getOx(), tiro[i]->getOy(), tiro[i]->getX(), tiro[i]->getY())>10)
        {
                      if(i%2==0)                             
                      tiro[i]->setRotation(1/distance(tiro[i]->getOx(), tiro[i]->getOy(), tiro[i]->getX(), tiro[i]->getY()));
                      else
                      tiro[i]->setRotation(-1/distance(tiro[i]->getOx(), tiro[i]->getOy(), tiro[i]->getX(), tiro[i]->getY()));
        }
        
        /*if (pattern==6&&tiro[i]->getTimer()>45&&inimigo->isAlive())
        {
                      tiro[i]->setTheta(aimShot(tiro[i]->getX(), tiro[i]->getY(), inimigo->getX(), inimigo->getY()));
        }*/
        
        if(tiro[i]->getX() > 1200||tiro[i]->getX() < -400||tiro[i]->getY() > 900||tiro[i]->getY() < -300)
        tiro[i]->hit();
        
        for(j=0; j<100; j++){
        
        if(FASE->getEnemy(j)->isAlive())
            if(distance(FASE->getEnemy(j)->getX(), FASE->getEnemy(j)->getY(), tiro[i]->getX(), tiro[i]->getY())<20&&tiro[i]->isActive()&&FASE->getEnemy(j)->isAlive())
            {
            FASE->getEnemy(j)->damage(tiro[i]->getPower());
            if(FASE->getEnemy(j)->getHealth()<=0) FASE->getEnemy(j)->die();
            espr->SetColor(0xFFFFFFFF);
            tiro[i]->hit();
            }
        }
        if(FASE->getBoss()->isAlive())
        if(distance(FASE->getBoss()->getX(), FASE->getBoss()->getY(), tiro[i]->getX(), tiro[i]->getY())<20&&tiro[i]->isActive()&&FASE->getBoss()->isAlive())
            {
            FASE->getBoss()->damage(tiro[i]->getPower());
            if(FASE->getBoss()->getHealth()<=0) FASE->getBoss()->die();
            espr->SetColor(0xFFFFFFFF);
            tiro[i]->hit();
            }
        
        }
        //tiroInimigo[i]->update();
        
        
        //if(tiroInimigo[i]->getX() > 1200||tiroInimigo[i]->getX() < -400||tiroInimigo[i]->getY() > 900||tiroInimigo[i]->getY() < -300)
        //tiroInimigo[i]->hit();
        
        for(i=0; i<100; i++){
                 if(FASE->getEnemy(i)->exists())
                for(j=0; j<1600; j++){        
                    if(distance(ox, oy, FASE->getEnemy(i)->getShotPattern()->getShot()[j]->getX(), FASE->getEnemy(i)->getShotPattern()->getShot()[j]->getY())<6&&deathcont==0)
                    {
                    deathcont=120;
                    ox = 100;
                    oy = 300;
                    ospr->SetColor(0x66FFFFFF);
                    
                    FASE->getEnemy(i)->getShotPattern()->getShot()[j]->hit();
                    }
                }
        
        }
        
        if(FASE->getBoss()->exists())
        for(j=0; j<1600; j++){    
        if(distance(ox, oy, FASE->getBoss()->getActivePattern()->getShot()[j]->getX(), FASE->getBoss()->getActivePattern()->getShot()[j]->getY())<6&&deathcont==0)
            {
            deathcont=120;
            ox = 100;
            oy = 300;
            ospr->SetColor(0x66FFFFFF);
            
            FASE->getBoss()->getActivePattern()->getShot()[j]->hit();
            }
            }
       
	if (cont>0) cont--;
	if (deathcont>0) deathcont--;
	if (deathcont==0) ospr->SetColor(0xFFFFFFFF);
	
	speed=8;
	
    //if(oy<584){pressed=false; ody+=grav*timetot; timetot+=dt;}
	// Do some movement calculations and collision detection	
	//odx*=friction; ody*=friction; ox+=odx; oy+=ody;
	if(ox>784) {ox=784;}
	if(ox<16) {ox=16;}
	if(oy>584) {oy=584;}
	if(oy<16) {oy=16;}

	// Update particle system
	par->info.nEmission=(int)80;
	par->MoveTo(ox,oy);
	par->Update(dt);
	
	frametot++;
     }
    else{
	id=gui->Update(dt);
	
	if(id == -1)
	{
          
        if(hge->Input_GetKeyState(HGEK_ESCAPE)) { g=false; gui->SetFocus(1); gui->Enter(); }
          
		switch(lastid)
		{
			case 1:
                 	g=true;
                 	break;
			case 2:
			case 3:
			case 4:
				gui->SetFocus(1);
				gui->Enter();
				break;

			case 5: return true;
		}
	}
	else if(id) { lastid=id; gui->Leave(); }
    }
    
	return false;
}


bool RenderFunc()
{
     int i, j;
     
	// Render graphics
	hge->Gfx_BeginScene();
	hge->Gfx_RenderQuad(&quad);
	if(g)
	{
	par->Render();
	ospr->Render(ox, oy);
	//sspr->Render(ox, oy);
	
	
	for(i=0; i<2000; i++)
		{
             if(tiro[i]->isActive())
             sspr3->RenderStretch(tiro[i]->getX()-12, tiro[i]->getY()-12, tiro[i]->getX()+12, tiro[i]->getY()+12);   
        }
        
        
        
        for(j=0; j<100; j++){
                 
            e = true;
                 
        	if (FASE->getEnemy(j)->isAlive()) FASE->getEnemy(j)->getSprite()->Render(FASE->getEnemy(j)->getX(), FASE->getEnemy(j)->getY());
        	else e = false;
        	
        	if (FASE->getEnemy(j)->exists())
            for(i=0; i<1600; i++)
        		{
                     if(i%4==0)
                     sspr2->SetColor(0xFFAAFFAA);
                     else if(i%3==0)
                     sspr2->SetColor(0xFFFFAAFF);
                     else if(i%2==0)
                     sspr2->SetColor(0xFFFFAAAA);
                     else
                     sspr2->SetColor(0xFFAAAAFF);
                     
                     if(FASE->getEnemy(j)->getShotPattern()->getShot()[i]->isActive()){
                     sspr2->Render(FASE->getEnemy(j)->getShotPattern()->getShot()[i]->getX(), FASE->getEnemy(j)->getShotPattern()->getShot()[i]->getY()); 
                     e = true;
                     }  
                     
                }
        FASE->getEnemy(j)->setExist(e);        
        }
        
        
        
        e = true;
        
        if (FASE->getBoss()->isAlive()) FASE->getBoss()->getSprite()->Render(FASE->getBoss()->getX(), FASE->getBoss()->getY());
        else e = false;
        
        if (FASE->getBoss()->exists())
            for(i=0; i<1600; i++)
        		{
                     if(i%4==0)
                     sspr2->SetColor(0xFFAAFFAA);
                     else if(i%3==0)
                     sspr2->SetColor(0xFFFFAAFF);
                     else if(i%2==0)
                     sspr2->SetColor(0xFFFFAAAA);
                     else
                     sspr2->SetColor(0xFFAAAAFF);
                     
                     if(FASE->getBoss()->getActivePattern()->getShot()[i]->isActive())
                     {
                     sspr2->Render(FASE->getBoss()->getActivePattern()->getShot()[i]->getX(), FASE->getBoss()->getActivePattern()->getShot()[i]->getY());   
                     e = true;
                     }
                }
                
                FASE->getBoss()->setExist(e);
                
	
    }
    else
    {
        title->Render(220.5, 55);
        gui->Render();
    }

	fnt->SetColor(0xFFFFFFFF);
	fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d\n", hge->Timer_GetDelta(), hge->Timer_GetFPS());
	hge->Gfx_EndScene();

	return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    int i;
    
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "jogo.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "JOGO");
	hge->System_SetState(HGE_FPS, 60);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
	
	srand((unsigned)time(0));

	if(hge->System_Initiate())
	{

        osnd=hge->Effect_Load("menu.wav");
		otex=hge->Texture_Load("particles.png");
		ntex=hge->Texture_Load("spritesheet.png");
		stex=hge->Texture_Load("spheresheet.png");
		ttex=hge->Texture_Load("textsheet.png");
		if(!osnd || !otex)
		{
			// If one of the data files is not found, display
			// an error message and shutdown.
			MessageBox(NULL, "Can't load one of the following files:\nMENU.WAV, PARTICLES.PNG, FONT1.FNT, FONT1.PNG, TRAIL.PSI", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
			return 0;
		}

		// Create and set up a sprite
		ospr=new hgeSprite(ntex, 45, 0, 45, 32);
		ospr->SetColor(0xFFFFFFFF);
		ospr->SetHotSpot(16,16);
		
		sspr = new  hgeSprite(stex, 192, 48, 48, 48) ;
        sspr->SetColor(0xFFFFFFFF);
		sspr->SetHotSpot(24,24); 
		
		sspr2 = new  hgeSprite(otex, 64, 96, 32, 32) ;
        sspr2->SetColor(0xFFFFFFFF);
		sspr2->SetHotSpot(16,16); 
		
		sspr3 = new  hgeSprite(stex, 0, 0, 48, 48) ;
        sspr3->SetColor(0x88FFFFFF);
		sspr3->SetHotSpot(24,24); 
		
		espr = new  hgeSprite(ntex, 180, 0, 40, 20) ;
        espr->SetColor(0xFFBBBBBB);
		espr->SetHotSpot(20,10); 
		
		title = new hgeSprite(ttex, 0, 0, 359, 137) ;
		title->SetColor(0xFCFBF9FD);
		
		play = new hgeSprite(ttex, 0, 139, 51, 24) ;
		
		for (i=0; i<221; i++)
		{
           if(i<100)
           sprites[i] = espr;     
           else if(i==100)
           {
           sprites[i] = new  hgeSprite(ntex, 0, 310, 74, 74) ;
           sprites[i]->SetColor(0xFFBBBBBB);
	       sprites[i]->SetHotSpot(37,37); 
           }
           else sprites[i] = sspr2; 
        }
		
		FASE = new Stage(1, sprites);
		
		for(i=0; i<2000; i++)
		{
                 tiro[i] = new variableShot (sspr, 4);
        }
        
        /*p = new ShotPattern(sspr, 4);
        p->setup(12, 64, 0.5, 4, 0, 3.1415926, 600, 4);
        
        p2 = new ShotPattern(sspr, 4);
        p2->setup(1, 8, 3, 6, 0, 0.025, 90, 5);
        
        inimigo = new Enemy(espr);
        
        inimigo->spawn(100,500,1600);
        inimigo->setShotPattern(p);
        
        for(i=0; i<1600; i++)
		{
              // tiroInimigo[i] = inimigo->getShotPattern()[i];
               thetaorig[i] = p->getShot()[i]->getTheta();
        }         
        
        pn = p->getWaveSize();
        */
        
		// Create and set up a particle system
		spt=new hgeSprite(otex, 32, 32, 32, 32);
		spt->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
		spt->SetHotSpot(16,16);
		par=new hgeParticleSystem("trail.psi",spt);
		par->Fire();


		// Load sound and textures
		quad.tex=hge->Texture_Load("titlescreen.png");
		tex=hge->Texture_Load("cursor.png");
		snd=hge->Effect_Load("menu.wav");
		if(!quad.tex || !tex || !snd)
		{
			// If one of the data files is not found, display
			// an error message and shutdown.
			MessageBox(NULL, "Can't load TITLESCREEN.PNG, CURSOR.PNG or MENU.WAV", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
			return 0;
		}

		// Set up the quad we will use for background animation
		quad.blend=BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_NOZWRITE;

		for(int i=0;i<4;i++)
		{
			// Set up z-coordinate of vertices
			quad.v[i].z=0.5f;
			// Set up color. The format of DWORD col is 0xAARRGGBB
			quad.v[i].col=0xFFFFFFFF;
		}

		quad.v[0].x=0;   quad.v[0].y=0; 
		quad.v[1].x=800; quad.v[1].y=0; 
		quad.v[2].x=800; quad.v[2].y=600; 
		quad.v[3].x=0;   quad.v[3].y=600;
		
		quad.v[0].tx=0;  quad.v[0].ty=0;
	    quad.v[1].tx=1;  quad.v[1].ty=0;
	    quad.v[2].tx=1;  quad.v[2].ty=1;
	    quad.v[3].tx=0;  quad.v[3].ty=1;


		// Load the font, create the cursor sprite
		fnt=new hgeFont("font1.fnt");
		spr=new hgeSprite(tex,0,0,32,32);

		// Create and initialize the GUI
		gui=new hgeGUI();

		gui->AddCtrl(new hgeGUIMenuItem(1,fnt,ospr,snd,400,300,0.0f,play));
		gui->AddCtrl(new hgeGUIMenuItem(2,fnt,ospr,snd,400,340,0.1f,play));
		gui->AddCtrl(new hgeGUIMenuItem(3,fnt,ospr,snd,400,380,0.2f,play));
		gui->AddCtrl(new hgeGUIMenuItem(4,fnt,ospr,snd,400,420,0.3f,play));
		gui->AddCtrl(new hgeGUIMenuItem(5,fnt,ospr,snd,400,460,0.4f,play));

		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		gui->SetCursor(spr);
		gui->SetFocus(1);
		gui->Enter();

		// Let's rock now!
		hge->System_Start();

		// Delete created objects and free loaded resources
		delete gui;
		delete fnt;
		delete spr;
		delete par;
		delete spt;
		delete ospr;
		delete espr;	
		delete sspr;
		delete FASE;
		
		hge->Texture_Free(otex);
		hge->Effect_Free(osnd);
		hge->Effect_Free(snd);
		hge->Texture_Free(tex);
		hge->Texture_Free(quad.tex);
	}

	// Clean up and shutdown
	hge->System_Shutdown();
	hge->Release();
	return 0;
}
