#include "../GUI/EasyGL.h"

GUIFrame::GUIFrame() : GUIPanel("GUI MAIN PANEL")
{
  listener = NULL;
  update   = true;
}

bool GUIFrame::loadXMLSettings(const TiXmlElement *element) 
{
  if(!XMLArbiter::inspectElementInfo(element, "Panel"))
    return Logger::writeErrorLog("Need a Panel node in the xml file");

  bool defaultFont = true;

  for(const TiXmlElement *child = element->FirstChildElement();	
      child;
   	  child = child->NextSiblingElement() )
  {
    std::string elementName  = child->Value();

    if(!elementName.size())
      continue;
    
    if(elementName == "Font")
    {
      int fontIndex = GUIFontManager::addFont(child);
      if(defaultFont && fontIndex >= 0)
      {
        GUIFontManager::setDefaultFont(fontIndex);
        defaultFont = false;
      }
      continue;
    }
 
    if(elementName == "Texture")
    {
      if(elementsTexture.loadXMLSettings(child))
      {
        GUITexCoordDescriptor::setTextureHeight(elementsTexture.getHeight());
        GUITexCoordDescriptor::setTextureWidth(elementsTexture.getWidth());
      }
      continue;
    }

    if(elementName == "TexCoordsDesc")
    {
      GUITexCoordDescriptor descriptor;
      descriptor.loadXMLSettings(child);
      addOrReplaceTexCoordsInfo(descriptor);
      continue;
    }
  }
  return   GUIPanel::loadXMLSettings(element);
}

void  GUIFrame::render(float tick)
{
  if(!visible)
    return;

  size_t t = 0;

  while(updateCount)
  {
    for(t = 0; t < elements.size(); t++)
      elements[t]->forceUpdate(true);
    updateCount--;
  }

  for(t = 0; t < elements.size(); t++)
    elements[t]->render(tick);
}

void GUIFrame::addOrReplaceTexCoordsInfo(GUITexCoordDescriptor &info)
{
  for(size_t t = 0; t < texCoords.size(); t++)
    if(texCoords[t].getType() == info.getType())
    {
      texCoords[t].setTexCoords(info.getTexCoords());
      return;
    }
  texCoords.push_back(info);
}

GUITexCoordDescriptor *GUIFrame::getTexCoordsInfo(int type)
{
  for(size_t t = 0; t < texCoords.size(); t++)
    if(texCoords[t].getType() == type)
      return &texCoords[t];
  return NULL;
}

void  GUIFrame::setGUIEventListener(GUIEventListener *listener_)
{
  listener = listener_;
}

GUIEventListener *GUIFrame::getEventsListener()
{
  return listener;
}

void  GUIFrame::setElementsTexture(const char* texturePath)
{
  elementsTexture.load2D(texturePath);
}

void  GUIFrame::setElementsTexture(const Texture &texture)
{
  elementsTexture = texture;
}

Texture *GUIFrame::getElementsTexture()
{
  return !elementsTexture.getID() ? NULL : &elementsTexture;
}

void  GUIFrame::enableGUITexture()
{
  if(elementsTexture.getID())
    elementsTexture.activate();
}

void  GUIFrame::disableGUITexture()
{
  elementsTexture.deactivate();
}

void GUIFrame::forceUpdate(bool update)
{
  updateCount = update ? getTreeHeight() + 1 : 0;
}

void GUIFrame::clear()
{
  elementsTexture.destroy();
  texCoords.clear();
  GUIPanel::clear();
}

const Tuple4i &GUIFrame::getWindowBounds()
{
  windowBounds.set(0, 0, int(dimensions.x), int(dimensions.y));
  return windowBounds;
}

GUIFrame::~GUIFrame()
{
  clear();
}
