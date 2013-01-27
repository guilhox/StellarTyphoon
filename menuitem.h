#include "hge.h"
#include "hgefont.h"
#include "hgegui.h"
#include "hgecolor.h"

class hgeGUIMenuItem : public hgeGUIObject
{
public:
  hgeGUIMenuItem(int id, hgeFont *fnt, hgeSprite *ospr, HEFFECT snd,
          float x, float y, float delay, hgeSprite *title);

  virtual void  Render();
  virtual void  Update(float dt);

  virtual void  Enter();
  virtual void  Leave();
  virtual bool  IsDone();
  virtual void  Focus(bool bFocused);
  virtual void  MouseOver(bool bOver);

  virtual bool  MouseLButton(bool bDown);
  virtual bool  KeyClick(int key, int chr);

private:
  hgeFont       *fnt;
  hgeSprite     *ospr;
  HEFFECT       snd;
  float         delay;
  hgeSprite     *title;

  hgeColor      scolor, dcolor, scolor2, dcolor2, color;
  hgeColor      sshadow, dshadow, shadow;
  float         soffset, doffset, offset;
  float         timer, timer2;
};
