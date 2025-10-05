#include "../GUI/EasyGL.h"

Tuple2i textureGUIDimensions(256,256);

void GUITexCoordDescriptor::setTextureWidth(int width)
{
  textureGUIDimensions.x = clamp(width, 8, 1024);
}

void GUITexCoordDescriptor::setTextureHeight(int height)
{  
  textureGUIDimensions.y = clamp(height, 8, 1024);
}

GUITexCoordDescriptor::GUITexCoordDescriptor(int widgetTypeArg)
{
  texCoords.set(0.0f,0.0f,1.0f,1.0f);
  widgetType = widgetTypeArg;
}

GUITexCoordDescriptor::GUITexCoordDescriptor(const GUITexCoordDescriptor &copy)
{
  this->operator=(copy);
}

GUITexCoordDescriptor &GUITexCoordDescriptor::operator =(const GUITexCoordDescriptor &copy)
{

  if(this != &copy)
  {
    texCoords  = copy.texCoords;
    widgetType = copy.widgetType;
  } 
  return *this;
}

void GUITexCoordDescriptor::setType(int type)
{
  switch(type)
  {
    case WT_SLIDER :
    case WT_BUTTON:
    case WT_CHECK_BOX:
    case WT_CHECK_BOX_MARK:
    case WT_RADIO_BUTTON:
    case WT_CHECK_RB_MARK:
      widgetType = type;
    break;
    default: widgetType = WT_UNKNOWN;
  }
}

void GUITexCoordDescriptor::setType(const std::string &type)
{
  if(!type.size())
  {
    Logger::writeErrorLog("NULL GUITexCoordDescriptor type");
    return;
  }

  if(type == "MATERIAL_SURFACE"){ widgetType = WT_MATERIAL_SURFACE; return; }
  if(type == "CHECK_BOX_MARK")  { widgetType = WT_CHECK_BOX_MARK;   return; }
  if(type == "CHECK_RB_MARK")   { widgetType = WT_CHECK_RB_MARK;    return; }
  if(type == "RADIO_BUTTON")    { widgetType = WT_RADIO_BUTTON;     return; }
  if(type == "SEPARATOR")       { widgetType = WT_SEPARATOR;        return; }
  if(type == "CHECK_BOX")       { widgetType = WT_CHECK_BOX;        return; }
  if(type == "TEXT_AREA")       { widgetType = WT_TEXT_AREA;        return; }
  if(type == "BUTTON")          { widgetType = WT_BUTTON;           return; }
  if(type == "SLIDER")          { widgetType = WT_SLIDER;           return; }
  if(type == "PANEL")           { widgetType = WT_PANEL;            return; }
  if(type == "LABEL")           { widgetType = WT_LABEL;            return; }

  Logger::writeErrorLog(std::string("Unknow GUITexCoordDescriptor type -> ") + type);
  widgetType = WT_UNKNOWN;
}

int GUITexCoordDescriptor::getType()
{
  return widgetType;
}

void GUITexCoordDescriptor::loadXMLSettings(const TiXmlElement *element)
{
  if(!XMLArbiter::inspectElementInfo(element, "TexCoordsDesc"))
    return;

  std::string name;
  int         xStart        = 0,
              yStart        = 0,
              xEnd          = 0,
              yEnd          = 0;

  xStart = XMLArbiter::fillComponents1i(element, "xStart", xStart);
  yStart = XMLArbiter::fillComponents1i(element, "yStart", yStart);
 
  xEnd = XMLArbiter::fillComponents1i(element, "xEnd", xEnd);
  yEnd = XMLArbiter::fillComponents1i(element, "yEnd", yEnd);
   
  setTexCoords(xStart/float(textureGUIDimensions.x), yStart/float(textureGUIDimensions.y),
               xEnd  /float(textureGUIDimensions.x), yEnd  /float(textureGUIDimensions.y));
  setType(element->Attribute("type"));
}

int GUITexCoordDescriptor::getTextureWidth()
{
  return textureGUIDimensions.x;
}

int GUITexCoordDescriptor::getTextureHeight()
{
  return textureGUIDimensions.y;
}

void GUITexCoordDescriptor::setTexCoords(float x, float y, float z, float w)
{
  texCoords.set(clamp(x,0.0f, 1.0f), clamp(y,0.0f, 1.0f),
                clamp(z,0.0f, 1.0f), clamp(w,0.0f, 1.0f));
}

void GUITexCoordDescriptor::setTexCoords(const Tuple4f& texCoordsArg)
{
  texCoords =  texCoordsArg;
};

const Tuple4f &GUITexCoordDescriptor::getTexCoords()
{
  return texCoords;
}
