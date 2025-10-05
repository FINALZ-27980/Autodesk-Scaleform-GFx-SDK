#include "../GUI/EasyGL.h"

GUITextBox::GUITextBox(const std::string &callback, const std::string &text) : GUIAlphaElement(callback)

{
  setBordersColor(0.3f, 0.3f, 0.3f);
  setDimensions(80, 18);
  setPadding(2, 2);
  setColor(0.5f, 0.5f, 0.5f);
  label.setString(text);

  blinkerPosition = 2;
  blinkerTimer    = 0.0f;
  blinkerOn       = false;

  textStartIndex  = 0;
  textEndIndex    = 0;

  dimensions.y    = GUIFontManager::getDefaultFont() ?
                    GUIFontManager::getDefaultFont()->getFontObject()->getHeight() + padding.y : dimensions.y;
  widgetType      = WT_TEXT_BOX;
}

bool GUITextBox::loadXMLSettings(const TiXmlElement* element)
{
  if(!XMLArbiter::inspectElementInfo(element, "TextBox"))
    return Logger::writeErrorLog("Need a TextBox node in the xml file");

  setBordersColor(XMLArbiter::fillComponents3f(XMLArbiter::getChildElementByName(element, "BordersColor"),bordersColor));
  return   GUIAlphaElement::loadXMLSettings(element);
return false;
}

void  GUITextBox::setBordersColor(const Tuple3f& color)
{
  setBordersColor(color.x, color.y, color.z);
}

const Tuple3f &GUITextBox::getBordersColor() const
{
  return bordersColor;
}

void  GUITextBox::setBordersColor(float r, float g, float b)
{
  bordersColor.set(clamp(r, 0.0f, 255.0f),
                   clamp(g, 0.0f, 255.0f),
                   clamp(b, 0.0f, 255.0f));
  bordersColor.x /= (bordersColor.x > 1.0) ? 255.0f : 1.0f;
  bordersColor.y /= (bordersColor.y > 1.0) ? 255.0f : 1.0f;
  bordersColor.z /= (bordersColor.z > 1.0) ? 255.0f : 1.0f;
}

void  GUITextBox::setPadding(const Tuple2i& p)
{
  setPadding(p.x, p.y);
}

void  GUITextBox::setPadding(int x, int y)
{
  padding.set(clamp(x, 0, 25),
              clamp(y, 0, 25));
}

const Tuple2i &GUITextBox::getPadding() const
{
  return padding;
}

void GUITextBox::render(float clockTick)
{
  if(!parent || !visible)
    return;

  modifyCurrentAlpha(clockTick);
  getWindowBounds();

  size_t realBlinkerPosition = clamp(blinkerPosition, size_t(windowBounds.x + padding.x),
                                                      size_t(windowBounds.z - padding.x));
  blinkerTimer += clockTick;
  blinkerTimer -= blinkerTimer > 1.0f ? 1.0f : 0.0f;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4fv(color);

  glBegin(GL_TRIANGLE_STRIP);
  glVertex2i(windowBounds.x, windowBounds.y);
  glVertex2i(windowBounds.x, windowBounds.w);
  glVertex2i(windowBounds.z + padding.x, windowBounds.y);
  glVertex2i(windowBounds.z + padding.x, windowBounds.w);
  glEnd();

  glColor3fv(bordersColor);
  glBegin(GL_LINE_LOOP);
  glVertex2i(windowBounds.x, windowBounds.y);
  glVertex2i(windowBounds.x, windowBounds.w);
  glVertex2i(windowBounds.z + padding.x, windowBounds.w);
  glVertex2i(windowBounds.z + padding.x, windowBounds.y);
  glEnd();
  glDisable(GL_BLEND);

  label.print(windowBounds.x + padding.x, windowBounds.y, int(textStartIndex), int(textEndIndex));

  if(blinkerOn && (blinkerTimer > 0.5f))
  {
    glColor3fv(label.getColor());
    glBegin(GL_LINES);
    glVertex2i((int)realBlinkerPosition, windowBounds.y + padding.y/2);
    glVertex2i((int)realBlinkerPosition, windowBounds.w - padding.y);
    glEnd();
    glColor3f(1,1,1);
  }
}

void GUITextBox::checkMouseEvents(MouseEvent &newEvent, int extraInfo, bool reservedBits)
{
  GUIRectangle::checkMouseEvents(newEvent, extraInfo, true);

  if(mouseOver && (clicked || pressed))
    setupBlinker(newEvent.getX());

  clicked   = false;
  released  = false;
  blinkerOn = focused ? blinkerOn : false;
}

void GUITextBox::checkKeyboardEvents(KeyEvent evt, int extraInfo)
{
  if(!focused || !active)
    return;

  if((evt.getKeyID() >= 32 && evt.getKeyID() <= 127) ||
     (evt.getKeyID() == 8));
  else
    extraInfo = 0;

  if(extraInfo == KE_PRESSED)
  {
    size_t length = label.getString().size();

    if(evt.displayable())
      setupText(TE_INSERT_CHAR, evt.getKeyChar());

    if(length)
    {
      switch(evt.getKeyID())
      {
        case   8:  setupText(TE_BACKSPACE_DELETE); break;
        case 127:  setupText(TE_SIMPLE_DELETE);    break;
      }
    }
  }

  label.forceUpdate(true);
  update = true;
}

void    GUITextBox::setupBlinker(size_t x)
{
  if(!focused || !active)
    return;

  GUIFont *font                = GUIFontManager::getFont(label.getFontIndex());
  const    std::string &string = label.getString();
  const    int         *spaces = NULL;
  blinkerPosition              = getWindowBounds().x + padding.x;
  x -= 1;

  if(font)
  {
     spaces = font->getFontObject()->getCharHorizontalGlyphs();

     for(size_t i = 0; i < string.size(); i++)
     if(blinkerPosition < x)
       blinkerPosition += spaces[int(string[i])];
  }

  blinkerOn = true;
}

void GUITextBox::setupText(int type, char Char)
{
  GUIFont     *font   = GUIFontManager::getFont(label.getFontIndex());
  const int   *spaces = font ? font->getFontObject()->getCharHorizontalGlyphs() : NULL;
  std::string  temp;
  size_t       length = label.getString().size(),
               start  = windowBounds.x + padding.x,
               index  = 0;

  if(!spaces)
    return;

  for(size_t t = 0; t < length; t++)
  {
    if(blinkerPosition > start)
    {
      index++;
      start += spaces[label.getString()[t]];
    }
  }

  if(type == TE_INSERT_CHAR)
  {
    if(index != length && length)
    {
      std::string leftSide;
      leftSide  = label.getString().substr(0, index);
      leftSide += Char;

      temp      = label.getString().substr(index, length - index);
      label.setString(leftSide + temp);
    }
    else
    {
      temp  = label.getString();
      temp += Char;
      label.setString(temp);
    } 
    blinkerPosition  = blinkerPosition + GUIFontManager::getCharacterWidth(Char, font);
  } 

  if(type == TE_BACKSPACE_DELETE && ((int)(blinkerPosition) != (windowBounds.x + padding.x)))
  {
    if(index != length)
    {
      std::string leftSide;
      setupBlinker(blinkerPosition - GUIFontManager::getCharacterWidth(label.getString()[index -1],
                                                                       label.getFontIndex()));

      leftSide = label.getString().substr(0, index - 1);
      temp     = label.getString().substr(index, length - index);
      label.setString(leftSide + temp);
      return;
    }

    setupBlinker(blinkerPosition - GUIFontManager::getCharacterWidth(label.getString()[length -1],
                                                                     font));

    temp = label.getString().substr(0, length - 1);

    if(temp.size())
      label.setString(temp);
    else
    {
      label.clear();
      blinkerPosition = windowBounds.x + padding.x;
    }
  }
  
  if(type == TE_SIMPLE_DELETE && length)
  {
    if(((int)(blinkerPosition) == (windowBounds.x + padding.x)) && (length == 1))
    {
      label.clear();
      return;
    }

    if(index < length)
    {
      std::string leftSide;
      leftSide = label.getString().substr(0, index);
      temp     = label.getString().substr(index + 1, length - index - 1);
      label.setString(leftSide + temp);
    }
  }
  if(type == TE_PARSE_VISIBLE)
     textEndIndex = font->getFontObject()->getMaxFittingLength(label.getString(), getWidth());
}

const Tuple4i &GUITextBox::getWindowBounds()
{
  if(parent && update)
  {
    label.computeDimensions();
    dimensions.y    = label.getHeight() ? label.getHeight() + padding.y : dimensions.y;

    GUIRectangle::computeWindowBounds();
    blinkerPosition = !blinkerPosition ? windowBounds.x + padding.x : blinkerPosition;
    setupText(TE_PARSE_VISIBLE);
  }
  return windowBounds;
}
