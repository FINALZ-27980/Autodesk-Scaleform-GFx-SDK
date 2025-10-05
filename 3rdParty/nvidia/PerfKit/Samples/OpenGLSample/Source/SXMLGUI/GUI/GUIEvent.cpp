#include "../GUI/EasyGL.h"

GUIEvent::GUIEvent(GUIRectangle *element)
{
  callbackString = element? element->getCallbackString() : "Unknown";
  eventSource    = element;
  consumed       = false;
}

GUIEvent::GUIEvent(const GUIEvent& copy)
{
  this->operator =(copy);
}

GUIEvent &GUIEvent::operator= (const GUIEvent& copy)
{
  if(this != &copy)
  {
    callbackString = copy.callbackString;
    eventSource    = copy.eventSource;
    consumed       = copy.consumed;
  }
  return *this;
}

void GUIEvent::setConsumed(bool consumedArg)
{
  consumed = consumedArg;
}

bool GUIEvent::isConsumed()
{
  return consumed;
}
GUIRectangle      *GUIEvent::getEventSource()   { return eventSource ;   }
const std::string &GUIEvent::getCallbackString(){ return callbackString; }

KeyEvent::KeyEvent(int keyID)
{
  id = keyID;
}

KeyEvent::KeyEvent(const KeyEvent& copy)
{
  this->operator =(copy);
}

KeyEvent &KeyEvent::operator= (const KeyEvent& copy)
{
  if(this != &copy)
  {
    id = copy.id;
  }
  return *this;
}

bool KeyEvent::displayable()
{
  return id >= 32 && id <= 126;
}

char KeyEvent::getKeyChar(){ return char(id); }
int  KeyEvent::getKeyID()  { return id      ; }

MouseEvent::MouseEvent()
{
  consume();
}

MouseEvent::MouseEvent(int bID, int xMouse, int yMouse, int invYMouse, int scroll)
{
  scrolling = scroll,
  buttonID  = bID;
  x         = xMouse;
  y         = yMouse;
  yInverse  = invYMouse;
}

MouseEvent::MouseEvent(const MouseEvent& copy)
{
  this->operator =(copy);
}

MouseEvent &MouseEvent::operator= (const MouseEvent& copy)
{
  if(this != &copy)
  {
    scrolling = copy.scrolling;
    buttonID  = copy.buttonID;
    yInverse  = copy.yInverse;
    x         = copy.x;
    y         = copy.y;
  }
  return *this;
}

void MouseEvent::consume()
{
  scrolling = 0;
  buttonID  = MB_UNKNOWN_BUTTON;
  x         = 0;
  y         = 0;
  yInverse  = 0;
}

int MouseEvent::getScrolling(){ return scrolling ; }
int MouseEvent::getButtonID() { return buttonID;   }
int MouseEvent::getYInverse() { return yInverse;   }
int MouseEvent::getX()        { return x;          }
int MouseEvent::getY()        { return y;          }

