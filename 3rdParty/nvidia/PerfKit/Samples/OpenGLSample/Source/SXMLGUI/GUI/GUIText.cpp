#include "../GUI/EasyGL.h"

GUIText::GUIText(const std::string &text)
{
  fontIndex =    -1;
  update    = true;

  color.set(1.0,1.0,1.0);
  scales.set(1.0f, 1.0f);
  setString(text);
}

GUIText::GUIText(const GUIText & copy)
{
  this->operator=(copy);
}

GUIText &GUIText::operator =(const GUIText & copy)
{
  if(this != &copy)
  {
    fontIndex = copy.fontIndex;
    scales    = copy.scales;
    update    = copy.update;
    color     = copy.color;
    size      = copy.size;
    text      = copy.text;
  }
  return *this;
}

GUIText &GUIText::operator =(const std::string & str)
{
  setString(str);
  return *this;
}

bool GUIText::loadXMLSettings(const TiXmlElement *element)
{
  if(!element || !element->Value() || strcmp(element->Value(),  "Text"))
    return Logger::writeErrorLog("Need a Text node in the xml file");
 
  for(const TiXmlElement *child = element->FirstChildElement();	
      child;
   	  child = child->NextSiblingElement() )
  {
    const char * value = child->Value();

    if(value)
    {
      if(!strcmp(value, "Color"))
        XMLArbiter::fillComponents3f(child, color);

      if(!strcmp(value, "Font"))
        fontIndex = GUIFontManager::addFont(child);
    }
  }

  setHeightScale(XMLArbiter::fillComponents1f(element, "hScale", 1.0f));
  setWidthScale(XMLArbiter::fillComponents1f(element, "wScale", 1.0f));
  setFontIndex(XMLArbiter::fillComponents1i(element, "fontIndex", fontIndex));
  setString(element->Attribute("string"));

  return true;
}

const std::string& GUIText::getString(){  return text; }

void GUIText::setString(const std::string &textArg)
{
  if(textArg.size() && text != textArg)
  {
    text   = textArg;
    update = true;
  }
}

void GUIText::setString(const char *textArg)
{
  if(textArg && text != textArg)
  {
    text   = textArg;
    update = true;
  }
}

void GUIText::clear()
{
  text.clear();
  update = false;
  size.set(0,0);
}

int GUIText::getFontIndex()
{
  return fontIndex;
}

void GUIText::setFontIndex(int index)
{
  fontIndex = index;
}

void  GUIText::print(int x, int y, int startIndex, int endIndex)
{
  if(!text.size())
    return;

  endIndex   = (endIndex  < 0) ? int(text.size()) : endIndex;
  startIndex = clamp(startIndex, 0, endIndex);

  GUIFontManager::setCurrentFont(fontIndex);
  GUIFont *currentFont = GUIFontManager::getCurrentFont();
  computeDimensions();

  if(!currentFont && !(currentFont = GUIFontManager::getDefaultFont()))
    return;

  currentFont->getFontObject()->printSubString(float(x), float(y), scales.x, scales.y, 
                                               color.x, color.y, color.z,
                                               startIndex, endIndex,
                                               text);
}

void  GUIText::printCenteredX (int x, int y, int startIndex, int endIndex)
{
  if(!text.size())
    return;

  computeDimensions();
  print(x - size.x/2, y, startIndex, endIndex);
}

void  GUIText::printCenteredY (int x, int y, int startIndex, int endIndex)
{
  if(!text.size())
    return;

  computeDimensions();
  print(x,  y - size.y/2, startIndex, endIndex);
}

void  GUIText::printCenteredXY(int x, int y, int startIndex, int endIndex)
{
  if(!text.size())
    return;

  computeDimensions();
  print(x - size.x/2, y - size.y/2, startIndex, endIndex);
}

void GUIText::computeDimensions()
{
  if(needUpdating())
  {
    GUIFontManager::setCurrentFont(fontIndex);
    GUIFont *currentFont = GUIFontManager::getCurrentFont();

    if(!currentFont && !(currentFont = GUIFontManager::getDefaultFont()))
      return;

    if(currentFont == GUIFontManager::getDefaultFont())
      fontIndex = GUIFontManager::findFontIndex(currentFont);

    if(text.size())
    {
      size = currentFont->getFontObject()->getStringDimensions(text);
      size.x = int(float(size.x)*scales.x);
    }
    size.y = int(float(currentFont->getFontObject()->getHeight())*scales.y);
    forceUpdate(false);
  }
}

void GUIText::setSize(const Tuple2i& sizeArg){ size = sizeArg; }
void GUIText::setSize(int x, int y){ size.set(x, y); }

int  GUIText::getHeight(){ return abs(size.y); }
int  GUIText::getWidth() { return abs(size.x); }

const Tuple2i& GUIText::getSize(){ return size; }
bool  GUIText::needUpdating(){ return update; }

void  GUIText::forceUpdate(bool updateArg){ update = updateArg; }
void  GUIText::setColor(const Tuple3f &color){ setColor(color.x, color.y, color.z); }

void GUIText::setColor(float r, float g, float b)
{
  color.set(clamp(r, 0.0f, 255.0f),
            clamp(g, 0.0f, 255.0f),
            clamp(b, 0.0f, 255.0f));

  color.x /= (color.x > 1.0) ? 255.0f : 1.0f;
  color.y /= (color.y > 1.0) ? 255.0f : 1.0f;
  color.z /= (color.z > 1.0) ? 255.0f : 1.0f;
}

void   GUIText::setHeightScale(float hs)
{
  scales.y = clamp(hs, 0.1f, 20.0f);
}
void   GUIText::setWidthScale(float ws)
{
  scales.x = clamp(ws, 0.1f, 20.0f);
}
void   GUIText::setScales(Tuple2f scales)
{
  setHeightScale(scales.y);
  setWidthScale(scales.x);
}
 
float  GUIText::getHeightScale()
{
  return scales.y;
}

float  GUIText::getWidthScale()
{
  return scales.x;
} 

const  Tuple2f &GUIText::getScales()
{
  return scales;
}
const Tuple3f &GUIText::getColor()
{ 
  return color;
}
