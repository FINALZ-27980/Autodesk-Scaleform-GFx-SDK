#include "../GUI/EasyGL.h"

bool GUIFont::build()
{
  if(!getName().size())
    return Logger::writeErrorLog("Null font path");
  
  return font.load(getName().c_str());
}

bool GUIFont::loadXMLSettings(const TiXmlElement *element)
{
  if(!XMLArbiter::inspectElementInfo(element, "Font"))
    return Logger::writeErrorLog("Need a Font node in the xml file");

  setName(element->Attribute("path"));

  return true;
}

CFont *GUIFont::getFontObject()
{
  return &font;
}

bool  GUIFont::operator ==(const GUIFont &compare)
{
  return (name   == compare.getName());  
}

bool  GUIFont::operator !=(const GUIFont &compare)
{
  return !operator ==(compare);  
}

GUIFont::~GUIFont()
{
  font.~CFont();
}
