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
HTEXTURE			tex, otex, ntex, stex, ttex, ptex;
hgeQuad				quad, quadjogo, quadover;

// Pointers to the HGE objects we will use
hgeGUI				*gui, *dead, *pause;
hgeFont				*fnt;
hgeSprite			*spr, *ospr, *sspr, *sspr2, *espr, *lspr, *bspr, *aspr, *fade;
hgeSprite           *title, *play, *options, *highscores, *credits, *quit, *gameover, *retry, *quitmenu, *contin, *quitmen;
hgeSprite*			spt, *sprites[221];
hgeParticleSystem*	par;

variableShot *tiro[300], *tiro2[300], *btiro[2000];

Stage *FASE;

// Some "gameplay" variables
float ox=100.0f, oy=300.0f;//Coordenadas do jogador
float dist = 9999;
int acont = 20, bcont = 10, cont = 10, cont2 = 30, deathcont = 60, bombcont = 0, h=0, s=0, s2=0, s3=0, espn=0, sprshift, lives = 5, bombs = 5, closest = 0;

bool g = false, e = true, d = false, p = false;

// Play sound effect
void boom() {
	int pan=int((ox-400)/4);
	float pitch=0.05f;
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
	if(g && !p)
	{
         switch(espn)//Varia os sprites dos inimigos a cada frame
         {
                     case 0:espr->SetTextureRect(180, 0, 40, 20, false); break;
                     case 1:espr->SetTextureRect(220, 0, 40, 20, false); break;
                     case 2:espr->SetTextureRect(260, 0, 40, 20, false); break;
                     case 3:espr->SetTextureRect(300, 0, 40, 20, false); break;
         }
         
         if(espn<3) espn++;
         else espn = 0;
         
         FASE->update(ox, oy);
                          
           ospr->SetTextureRect(46, 0, 44, 32, false);//Reseta o sprite do player para a posição original
           sprshift = 0;
         	float dt=hge->Timer_GetDelta();
	// Process keys
	if (hge->Input_GetKeyState(HGEK_SHIFT))//Diminui a velocidade
          {
          speed=2;
          ospr->SetTextureRect(0, 0, 44, 32, false);//Muda o sprite para a versão com menos brilho na turbina
          sprshift = 45;
          }
	if (hge->Input_GetKeyState(HGEK_ESCAPE) || hge->Input_GetKeyState(HGEK_ENTER)){ //Pausa o jogo
	      //g=false;
          p=true;
          pause->SetFocus(1);
          pause->Enter();
          }
	if (hge->Input_GetKeyState(HGEK_LEFT)) ox-=speed;//Move para a esquerda
	if (hge->Input_GetKeyState(HGEK_RIGHT)) ox+=speed;//Move para a direita
	if (hge->Input_GetKeyState(HGEK_X)&&bombcont==0&&bombs>0) {//Ativa a bomba (se existir)
       bombs--;
       bombcont = 180;
       s2 = 0;
       }
    if (hge->Input_GetKeyState(HGEK_UP))//Move para cima
       {
       oy-=speed;
       ospr->SetTextureRect(90+sprshift, 0, 45, 32, false);//Muda o sprite para a versão inclinada
       ospr->SetFlip(false, false, false);
       }
       if (hge->Input_GetKeyState(HGEK_DOWN))//Move para baixo
     {
      oy+=speed;
      ospr->SetTextureRect(90+sprshift, 0, 45, 32, false);
      ospr->SetFlip(false, true, false);
      }
	if (hge->Input_GetKeyState(HGEK_Z))//Atira
                {
                   
                               if(cont==0){
                                for (i=0; i<10; i++)
                                {
                                      if(!tiro[s]->isActive())//Tiro vermelho (reto)
                                      {
                                      tiro[s]->activate();//Ativa apenas os tiros que não estiverem ativos no vetor
                                      tiro[s]->shoot(ox, oy, 15, - 0.02 + 0.005*i, true, 1, 0, 0, 0); //Padrão de rajada frontal com 10 tiros por onda, intervalo de 4 frames por onda, dano de 1 por tiro e velocidade de 15 pixels por frame
                                      s++;
                                      boom();//Barulho
                                      }    
                                }
                                cont = 4;
                                if(s>290)  s=0;
                                }
                                
                                if(acont==0){
                                for (i=0; i<6; i++)
                                {
                                      if(!tiro2[s3]->isActive())//Tiro branco (segue o inimigo mais próximo)
                                      {
                                      tiro2[s3]->activate();//Ativa apenas os tiros que não estiverem ativos no vetor
                                      if(i%2==0)
                                      tiro2[s3]->shoot(ox, oy, 0, 0.25-0.025*i, true, 2, 0.1, 0, 0); //Padrão de rajada lateral (para cima da nave) com 3 tiros por onda, intervalo de 20 frames por onda, aceleração de 0,1 pixel por frame por frame e dano de 2 por tiro
                                      else
                                      tiro2[s3]->shoot(ox, oy, 0, 0.725 + 0.025*i, true, 2, 0.1, 0, 0); //Padrão de rajada lateral (para baixo da nave) com 3 tiros por onda, intervalo de 20 frames por onda, aceleração de 0,1 pixel por frame por frame e dano de 2 por tiro
                                      s3++;
                                      }    
                                }                               
                          
                          acont = 20;
                          if(s3>290)  s3=0;   
                          }                                     
                }

                for(i=0; i<100; i++)
                FASE->getEnemy(i)->getSprite()->SetColor(0xFFBBBBBB);
                
                FASE->getBoss()->getSprite()->SetColor(0xFFBBBBBB);
                
                
                dist = 9999;
        
        for(i=0; i<100; i++)
        {
                 if(FASE->getEnemy(i)->isAlive())
                 if(distance(FASE->getEnemy(i)->getX(), FASE->getEnemy(i)->getY(), ox, oy)<dist)
                 {
                  dist = distance(FASE->getEnemy(i)->getX(), FASE->getEnemy(i)->getY(), ox, oy);//Determina o inimigo mais próximo do jogador
                  closest = i;
                 }
        }
    
    if(bombcont>0)
    for(i=0; i<2000; i++)
    {       
    btiro[i]->update(); //Atualiza a posição dos tiros da bomba (se estiver ativada)
    
    if(btiro[i]->getX() > 1200||btiro[i]->getX() < -400||btiro[i]->getY() > 900||btiro[i]->getY() < -300)
        btiro[i]->hit(); //Desativa os tiros da bomba que saíram da tela
        
    for(j=0; j<100; j++){
        
        if(FASE->getEnemy(j)->isAlive())//Testa colisão entre tiros da bomba e os inimigos
            if(distance(FASE->getEnemy(j)->getX(), FASE->getEnemy(j)->getY(), btiro[i]->getX(), btiro[i]->getY())<20&&btiro[i]->isActive()&&FASE->getEnemy(j)->isAlive())
            {
            FASE->getEnemy(j)->damage(btiro[i]->getPower());
            if(FASE->getEnemy(j)->getHealth()<=0) FASE->getEnemy(j)->die();
            espr->SetColor(0xFFFFFFFF);//Inimigos brilham quando são acertados
            btiro[i]->hit();//Desativa o tiro que acertou
            }
        }
        if(FASE->getBoss()->isAlive())//Testa colisão entre tiros da bomba e o chefe
        if(distance(FASE->getBoss()->getX(), FASE->getBoss()->getY(), btiro[i]->getX(), btiro[i]->getY())<40&&btiro[i]->isActive()&&FASE->getBoss()->isAlive())
            {
            FASE->getBoss()->damage(1);//Dano mínimo
            
            if(FASE->getBoss()->getHealth()<=0) FASE->getBoss()->die();
            btiro[i]->hit();
            }
    }           
    for(i=0; i<300; i++)
       {
        tiro[i]->update();//Atualiza tiros normais
        tiro2[i]->update();//Atualiza tiros que seguem
        
        if (!FASE->getBoss()->isAlive()&&tiro2[i]->getTimer()>45&&FASE->getEnemy(closest)->isAlive())//Mira no inimigo mais próximo o tiro 2, se o chefe não estiver na tela
            tiro2[i]->setTheta(aimShot(tiro2[i]->getX(), tiro2[i]->getY(), FASE->getEnemy(closest)->getX(), FASE->getEnemy(closest)->getY()));
        else if (FASE->getBoss()->isAlive()&&tiro2[i]->getTimer()>45) //Mira no chefe (prioridade maior)
            tiro2[i]->setTheta(aimShot(tiro2[i]->getX(), tiro2[i]->getY(), FASE->getBoss()->getX(), FASE->getBoss()->getY()));
        
        if(tiro[i]->getX() > 1200||tiro[i]->getX() < -400||tiro[i]->getY() > 900||tiro[i]->getY() < -300)
        tiro[i]->hit();
        
        if(tiro2[i]->getX() > 1200||tiro2[i]->getX() < -400||tiro2[i]->getY() > 900||tiro2[i]->getY() < -300)
        tiro2[i]->hit();
        
        for(j=0; j<100; j++){
        
        if(FASE->getEnemy(j)->isAlive())//testes de colisão
            if(distance(FASE->getEnemy(j)->getX(), FASE->getEnemy(j)->getY(), tiro[i]->getX(), tiro[i]->getY())<20&&tiro[i]->isActive()&&FASE->getEnemy(j)->isAlive())
            {
            FASE->getEnemy(j)->damage(tiro[i]->getPower());
            if(FASE->getEnemy(j)->getHealth()<=0) FASE->getEnemy(j)->die();
            FASE->getEnemy(j)->getSprite()->SetColor(0xFFFFFFFF);
            tiro[i]->hit();
            }
            else if (distance(FASE->getEnemy(j)->getX(), FASE->getEnemy(j)->getY(), tiro2[i]->getX(), tiro2[i]->getY())<20&&tiro2[i]->isActive()&&FASE->getEnemy(j)->isAlive())
            {
            FASE->getEnemy(j)->damage(tiro2[i]->getPower());
            if(FASE->getEnemy(j)->getHealth()<=0) FASE->getEnemy(j)->die();
            FASE->getEnemy(j)->getSprite()->SetColor(0xFFFFFFFF);
            tiro2[i]->hit();
            }
        }
        if(FASE->getBoss()->isAlive())//testes de colisão
        if(distance(FASE->getBoss()->getX(), FASE->getBoss()->getY(), tiro[i]->getX(), tiro[i]->getY())<40&&tiro[i]->isActive()&&FASE->getBoss()->isAlive())
            {
            FASE->getBoss()->damage(tiro[i]->getPower());
            
            if(FASE->getBoss()->getHealth()<=0) FASE->getBoss()->die();
            tiro[i]->hit();
            }else if (distance(FASE->getBoss()->getX(), FASE->getBoss()->getY(), tiro2[i]->getX(), tiro2[i]->getY())<20&&tiro2[i]->isActive()&&FASE->getBoss()->isAlive())
            {
            FASE->getBoss()->damage(tiro2[i]->getPower());
            if(FASE->getBoss()->getHealth()<=0) FASE->getBoss()->die();
            tiro2[i]->hit();
            }
        
        }
        
        for(i=0; i<100; i++){
                 if(FASE->getEnemy(i)->exists())
                for(j=0; j<1000; j++){        
                    if(g&&bombcont==0&&distance(ox, oy, FASE->getEnemy(i)->getShotPattern()->getShot()[j]->getX(), FASE->getEnemy(i)->getShotPattern()->getShot()[j]->getY())<4&&deathcont==0&&FASE->getEnemy(i)->getShotPattern()->getShot()[j]->isActive())
                    {//Testa se o player foi acertado por um tiro inimigo
                    lives--;
                    if(lives==0)//Game Over
                    	{
                            //g = false; gui->SetFocus(1); gui->Enter();
                            g = false; d = true; dead->SetFocus(1); dead->Enter();
                            lives = 5;
                            bombs = 5;
                            ox = 100;//Retorna o player para posição inicial
                            oy = 300;
                            for(i=0; i<300; i++)
                            {
                             tiro[i]->hit();//Desativa todos os tiros normais
                             tiro2[i]->hit();//Desativa todos os tiros teleguiados
                             }
                            FASE = new Stage(1, sprites);
                            return false;
                        }
                    else{
                    deathcont=120;//Invencibilidade de 2 segundos
                    ospr->SetColor(0x66FFFFFF);//Transparência enquanto deathcont>0
                    }
                    ox = 100;//Retorna o player para posição inicial
                    oy = 300;
                    
                    FASE->getEnemy(i)->getShotPattern()->getShot()[j]->hit();//Desativa tiro inimigo que acertou
                    }
                }
        
        }
        
        if(FASE->getBoss()->exists())
        for(j=0; j<10000; j++){    
        if(g&&bombcont==0&&distance(ox, oy, FASE->getBoss()->getActivePattern()->getShot()[j]->getX(), FASE->getBoss()->getActivePattern()->getShot()[j]->getY())<4&&deathcont==0&&FASE->getBoss()->getActivePattern()->getShot()[j]->isActive())
            {//Mesmos testes de antes, agora com os tiros do chefe
            lives--;
            if(lives==0)
                    	{
                            //g = false; gui->SetFocus(1); gui->Enter();
                            g = false; d = true; dead->SetFocus(1); dead->Enter();
                            lives = 5;
                            bombs = 5;
                            ox = 100;//Retorna o player para posição inicial
                            oy = 300;

                          for(i=0; i<300; i++)
                          {
                          tiro[i]->hit();//Desativa todos os tiros normais
                          tiro2[i]->hit();//Desativa todos os tiros teleguiados
                          }
                            FASE = new Stage(1, sprites);
                            return false;
                        }
            else{
            deathcont=120;
            ospr->SetColor(0x66FFFFFF);
            }
            ox = 100;
            oy = 300;
            
            ospr->SetColor(0x66FFFFFF);
            
            FASE->getBoss()->getActivePattern()->getShot()[j]->hit();
            }
            }
            
            if(bombcont>1&&bcont==0)//Performa as operações com os tiros da bomba, se a bomba for ativada
            {
                       for (i=0; i<128; i++)
                          {
                              if(!btiro[s2]->isActive())
                              {
                              btiro[s2]->activate();//Ativa apenas os tiros que não estiverem ativos no vetor
                              btiro[s2]->shoot(ox, oy, 0, i*(1.0/128.0), true, 5, 1, 0, 0); //Padrão radial simples com 128 tiros por onda, intervalo de 10 frames entre as ondas, dano 5 por tiro e aceleração de 1 pixel por frame por frame
                              s2++;
                              boom();
                              }
                              if(s2>1800)
                                 {
                                 s2=0;
                                 }
                          }    
                          bcont = 10;
            }
            else if(bombcont == 1) {
                 s2 = 0;
                 for(i=0; i<2000; i++)
                          btiro[i]->hit();//Apaga todos os tiros da bomba quando esta acaba
                 }
       
    //Redução de todos os contadores
	if (cont>0) cont--;//Contador do tiro reto (determina os intervalos entre os tiros)
	if (acont>0) acont--;//Contador do tiro mirado (determina os intervalos entre os tiros)
	if (bcont>0) bcont--;//Contador dos tiros da bomba (determina os intervalos entre os tiros)
	if (deathcont>0) deathcont--;//Contador de invencibilidade após a morte
	if (bombcont>0) bombcont--;//Contador de duração total da bomba
	if (deathcont==0) ospr->SetColor(0xFFFFFFFF); //Retira a transparência do jogador
	
	
	
	speed=8;//retorna a velocidade do jogador para o valor original automaticamente (cancelado se shift permanecer apertado)
	
	//Essas linhas proíbem que o jogador saia da tela:
	if(ox>784) {ox=784;}
	if(ox<16) {ox=16;}
	if(oy>584) {oy=584;}
	if(oy<16) {oy=16;}	
     }
     
     else if (p){ //Operações de jogo pausado
     id=pause->Update(dt);
	
	if(id == -1)
	{          
        if(hge->Input_GetKeyState(HGEK_ESCAPE)) { g=false; p=false; gui->SetFocus(1); gui->Enter(); }
          
		switch(lastid)
		{
			case 1:
                 	p = false;
                 	g = true;
                 	break;
			case 2:
                 p = false;
                 g = false;
                 lives = 5;
                 bombs = 5;
                 ox = 100;//Retorna o player para posição inicial
                 oy = 300;
                 for(i=0; i<2000; i++)
                          btiro[i]->hit();//Desativa todos os tiros de bomba
                  for(i=0; i<300; i++)
                  {
                          tiro[i]->hit();//Desativa todos os tiros normais
                          tiro2[i]->hit();//Desativa todos os tiros teleguiados
                  }
                          
                 FASE = new Stage(1, sprites);
				gui->SetFocus(1);
				gui->Enter();
				break;
		}
	}
	else if(id) { lastid=id; pause->Leave(); }
    }
     
    else if (d){ //Operações quando o jogador perde
    id=dead->Update(dt);
	
	if(id == -1)
	{          
        if(hge->Input_GetKeyState(HGEK_ESCAPE)) { g=false; d=false; gui->SetFocus(1); gui->Enter(); }
          
		switch(lastid)
		{
			case 1:
                 	d = false;
                 	g = true;
                 	break;
			case 2:
                 d = false;
				gui->SetFocus(1);
				gui->Enter();
				break;
		}
	}
	else if(id) { lastid=id; dead->Leave(); }
    }
    else{//Operações que ocorrem enquanto o jogo não está ativo
	id=gui->Update(dt);
	
	if(id == -1)
	{
          
        if(hge->Input_GetKeyState(HGEK_ESCAPE)) { g=false; gui->SetFocus(1); gui->Enter(); }
          
		switch(lastid)
		{
			case 1:
                 	g = true;
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
	if(g)
	{
    hge->Gfx_RenderQuad(&quadjogo);
	par->Render();
	ospr->Render(ox, oy);
	//sspr->Render(ox, oy);
	
	
	for(i=0; i<300; i++)
		{
             if(tiro[i]->isActive()){
             sspr->RenderStretch(tiro[i]->getX()-12, tiro[i]->getY()-12, tiro[i]->getX()+12, tiro[i]->getY()+12);   
             }
             
             if(tiro2[i]->isActive())
             aspr->RenderStretch(tiro2[i]->getX()-12, tiro2[i]->getY()-12, tiro2[i]->getX()+12, tiro2[i]->getY()+12);  
            
        }
        for(i=0; i<2000; i++){
        if(btiro[i]->isActive()){
             bspr->RenderStretch(btiro[i]->getX()-15, btiro[i]->getY()-15, btiro[i]->getX()+15, btiro[i]->getY()+15);   
             }   
        }
        for(i=0; i<lives; i++)
             lspr->RenderStretch(700+20*i-8, 17, 700+20*i+8, 33);  
        
        for(i=0; i<bombs; i++)
             bspr->RenderStretch(700+20*i-8, 37, 700+20*i+8, 53);
        
        for(j=0; j<100; j++){
                 
            e = true;
                 
        	if (FASE->getEnemy(j)->isAlive()) FASE->getEnemy(j)->getSprite()->Render(FASE->getEnemy(j)->getX(), FASE->getEnemy(j)->getY());
        	else e = false;
        	
        	if (FASE->getEnemy(j)->exists())
            for(i=0; i<1000; i++)
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
            for(i=0; i<10000; i++)
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
                
                if (p){
                //hge->Gfx_RenderQuad(&quadpreto);
                fade->Render(0,0);
                pause->Render();
                }
	
    }
    else if (d){
	     hge->Gfx_RenderQuad(&quadover);
         gameover->Render(220.5, 150);
         dead->Render();
         }
    else
    {
        hge->Gfx_RenderQuad(&quad);
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

	hge->System_SetState(HGE_LOGFILE, "Stellar Typhoon.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "Stellar Typhoon");
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
		ptex=hge->Texture_Load("quadradopreto.png");
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
		ospr=new hgeSprite(ntex, 45, 0, 45, 32);//Sprite do jogador
		ospr->SetColor(0xFFFFFFFF);
		ospr->SetHotSpot(16,16);
		
		lspr=new hgeSprite(ntex, 45, 0, 45, 32);//Sprite das vidas (naves vermelhas)
		lspr->SetColor(0xFFFF5555);
		lspr->SetHotSpot(16,16);
		
        sspr = new  hgeSprite(stex, 0, 48, 48, 48) ;//Sprite de tiros do jogador
        sspr->SetColor(0x33FFFFFF);
		sspr->SetHotSpot(24,24); 
		
		sspr2 = new  hgeSprite(otex, 64, 96, 32, 32) ;//Sprite de tiros inimigos
        sspr2->SetColor(0xFFFFFFFF);
		sspr2->SetHotSpot(16,16); 
		
		aspr = new  hgeSprite(stex, 48, 0, 48, 48) ;//Sprite dos tiros mirados
        aspr->SetColor(0x44FFFFFF);
		aspr->SetHotSpot(24,24); 
		
		bspr = new  hgeSprite(stex, 144, 0, 48, 48) ;//Sprite dos tiros da bomba
        bspr->SetColor(0xFFFFFFFF);
		bspr->SetHotSpot(24,24); 
		
		espr = new  hgeSprite(ntex, 180, 0, 40, 20) ;//sprite dos inimigos
        espr->SetColor(0xFFBBBBBB);
		espr->SetHotSpot(20,10); 
		
		fade = new hgeSprite(ptex, 0, 0, 800, 600) ;//sprite de tela preta para fade
        fade->SetColor(0x99999999);
		fade->SetHotSpot(0,0); 
		
		title = new hgeSprite(ttex, 0, 0, 359, 137) ;//Sprite do título
		title->SetColor(0xF9FBF9FD);
		
		play = new hgeSprite(ttex, 0, 139, 86, 29) ;		
		options = new hgeSprite(ttex, 88, 139, 141, 29) ;		
		highscores = new hgeSprite(ttex, 82, 170, 225, 29) ;		
		credits = new hgeSprite(ttex, 231, 139, 141, 29) ;		
		quit = new hgeSprite(ttex, 0, 170, 80, 29) ;
		
		gameover = new hgeSprite(ttex, 373, 0, 312, 116) ;
		retry = new hgeSprite(ttex, 373, 139, 107, 29) ;
		quitmenu = new hgeSprite(ttex, 481, 139, 248,29) ;
		
		contin = new hgeSprite(ttex, 305, 170, 165, 29) ;
		
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
		
		for(i=0; i<300; i++)
		{
                 tiro[i] = new variableShot (sspr, 12);
                 tiro2[i] = new variableShot (aspr, 12);
        }
        
        for(i=0; i<2000; i++)
		{
                 btiro[i] = new variableShot (bspr, 15);
        }
        

        
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
	    
	    quadjogo = quad;
	    quadjogo.tex=hge->Texture_Load("bg1.png");
	    if(!quadjogo.tex)
		{
			// If one of the data files is not found, display
			// an error message and shutdown.
			MessageBox(NULL, "Can't load BG1.PNG", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
			return 0;
		}
		
		quadover = quad;
	    quadover.tex=hge->Texture_Load("gameover.png");
	    if(!quadover.tex)
		{
			// If one of the data files is not found, display
			// an error message and shutdown.
			MessageBox(NULL, "Can't load GAMEOVER.PNG", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
			return 0;
		}
		
		/*quadpreto = quad;
        quadpreto.tex=hge->Texture_Load("quadradopreto.png");
	    if(!quadpreto.tex)
		{
			// If one of the data files is not found, display
			// an error message and shutdown.
			MessageBox(NULL, "Can't load QUADRADOPRETO.PNG", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
			return 0;
		}
		for(int i=0;i<4;i++)
		    quadpreto.v[i].col=0x77777777;*/

		// Load the font, create the cursor sprite
		fnt=new hgeFont("font1.fnt");
		spr=new hgeSprite(tex,0,0,32,32);

		// Create and initialize the GUI
		gui=new hgeGUI();

		gui->AddCtrl(new hgeGUIMenuItem(1,fnt,ospr,snd,400,300,0.0f,play));
		gui->AddCtrl(new hgeGUIMenuItem(2,fnt,ospr,snd,400,340,0.1f,options));
		gui->AddCtrl(new hgeGUIMenuItem(3,fnt,ospr,snd,400,380,0.2f,highscores));
		gui->AddCtrl(new hgeGUIMenuItem(4,fnt,ospr,snd,400,420,0.3f,credits));
		gui->AddCtrl(new hgeGUIMenuItem(5,fnt,ospr,snd,400,460,0.4f,quit));

		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		gui->SetCursor(spr);
		gui->SetFocus(1);
		gui->Enter();
		
		dead = new hgeGUI();
		
		dead->AddCtrl(new hgeGUIMenuItem(1,fnt,ospr,snd,400,300,0.0f,retry));
		dead->AddCtrl(new hgeGUIMenuItem(2,fnt,ospr,snd,400,340,0.1f,quitmenu));
		
		dead->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		dead->SetCursor(spr);
		
		pause = new hgeGUI();
		
		pause->AddCtrl(new hgeGUIMenuItem(1,fnt,ospr,snd,400,300,0.0f,contin));
		pause->AddCtrl(new hgeGUIMenuItem(2,fnt,ospr,snd,400,340,0.1f,quitmenu));
		
		pause->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		pause->SetCursor(spr);

		// Let's rock now!
		hge->System_Start();

		// Delete created objects and free loaded resources
		delete gui;
		delete dead;
		delete pause;
		delete fnt;
		delete spr;
		delete par;
		delete spt;
		delete ospr;
		delete espr;	
		delete sspr;
		delete sspr2;
		delete aspr;
		delete bspr;
		delete espr;
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
