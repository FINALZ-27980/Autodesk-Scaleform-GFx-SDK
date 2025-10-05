#include "../GUI/EasyGL.h"

GUISlider::GUISlider(const std::string &callback, const int   orientation_) :  GUIAlphaElement(callback)
{
  setDiscDimensions(18, 18);
  setProgress(0.0);
  orientation = orientation_ == OR_VERTICAL ? OR_VERTICAL : OR_HORIZONTAL;
  widgetType  = WT_SLIDER ;
  offset      = 0;

  setDimensions((orientation_ == OR_VERTICAL) ?  18.0f : 100.0f,
                (orientation_ == OR_VERTICAL) ?  85.0f :  18.0f);
}

bool GUISlider::loadXMLSettings(const TiXmlElement *element)
{
  if(!XMLArbiter::inspectElementInfo(element, "Slider"))
    return Logger::writeErrorLog("Need a Slider node in the xml file");
 
  const char * orient = element->Attribute("orientation");

  orientation = (orient  && !strcmp(orient, "VERTICAL")) ? OR_VERTICAL : OR_HORIZONTAL;

  setDiscDimensions(XMLArbiter::fillComponents1i(element, "discWidth",  discDimensions.x),
                    XMLArbiter::fillComponents1i(element, "discHeight", discDimensions.y));
  setProgress(XMLArbiter::fillComponents1f(element, "progress", progress));
  setDimensions((orientation == OR_VERTICAL) ? 18.0f : 100.0f,
               (orientation == OR_VERTICAL) ? 85.0f :  18.0f);
  return   GUIAlphaElement::loadXMLSettings(element);
}

void  GUISlider::setDiscDimensions(const Tuple2i& dimensions)
{
  setDiscDimensions(dimensions.x, dimensions.y);
}

void  GUISlider::setDiscDimensions(int width, int height)
{
  discDimensions.set(clamp(width, 5, 500), clamp(height, 5, 500));
  setDimensions((orientation == OR_HORIZONTAL) ? dimensions.x            : float(discDimensions.x),
                (orientation == OR_HORIZONTAL) ? float(discDimensions.y) : dimensions.y);
}

const Tuple2i &GUISlider::getDiscDimensions()
{
  return discDimensions;
}

void  GUISlider::setProgress(float zeroToOne)
{
  if(!pressed)
    progress = clamp(zeroToOne, 0.0f, 1.0f);
}

float GUISlider::getProgress()
{
  return progress;
}

void GUISlider::render(float clockTick)
{
  if(!parent || !visible)
    return;

  modifyCurrentAlpha(clockTick);  

  if(orientation == OR_VERTICAL)
  {
    renderVertical();
    return;
  }

  GUITexCoordDescriptor *descriptor    = parent->getTexCoordsInfo(WT_SLIDER );
  Tuple2i discXBounds,
          center     = getCenter();


  discXBounds.x  = windowBounds.x;
  discXBounds.x += int(float(windowBounds.z - windowBounds.x)*progress);
  discXBounds.x -= discDimensions.x/2;
  discXBounds.y  = discXBounds.x + discDimensions.x;

  glTranslatef(float(offset), 0, 0);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4fv(color);

  glBegin(GL_TRIANGLE_STRIP);
  glVertex2i(windowBounds.x, center.y - 1);
  glVertex2i(windowBounds.x, center.y + 1);
  glVertex2i(windowBounds.z, center.y - 1);
  glVertex2i(windowBounds.z, center.y + 1);
  glEnd();

  if(descriptor)
  {
    const Tuple4f &texCoords = descriptor->getTexCoords();
    parent->enableGUITexture();

    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(texCoords.x, texCoords.y); 
    glVertex2i(discXBounds.x, windowBounds.y);

    glTexCoord2f(texCoords.x, texCoords.w);
    glVertex2i(discXBounds.x, windowBounds.w);

    glTexCoord2f(texCoords.z, texCoords.y); 
    glVertex2i(discXBounds.y, windowBounds.y);

    glTexCoord2f(texCoords.z, texCoords.w); 
    glVertex2i(discXBounds.y, windowBounds.w);
    glEnd();

    parent->disableGUITexture();
  }
  else
  {
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2i(discXBounds.x, windowBounds.y);
    glVertex2i(discXBounds.x, windowBounds.w);
    glVertex2i(discXBounds.y, windowBounds.y);
    glVertex2i(discXBounds.y, windowBounds.w);
    glEnd();
  }
  glDisable(GL_BLEND);
  glTranslatef(float(-offset), 0, 0);
  label.printCenteredX(center.x + offset, windowBounds.w);
}

void    GUISlider::renderVertical()
{
  GUITexCoordDescriptor *descriptor    = parent->getTexCoordsInfo(WT_SLIDER );
  Tuple2i discYBounds,
          center     = getCenter();

  discYBounds.x  = windowBounds.w;
  discYBounds.x -= int(float(getHeight())*progress);
  discYBounds.x -= discDimensions.y/2;
  discYBounds.y  = discYBounds.x + discDimensions.y;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4fv(color);

  glTranslatef(0, float(+offset), 0);

  glBegin(GL_TRIANGLE_STRIP);
  glVertex2i(center.x - 1, windowBounds.y );
  glVertex2i(center.x - 1, windowBounds.w);
  glVertex2i(center.x + 1, windowBounds.y);
  glVertex2i(center.x + 1, windowBounds.w);
  glEnd();
 
  if(descriptor)
  {
    const Tuple4f &texCoords = descriptor->getTexCoords();
    parent->enableGUITexture();

    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(texCoords.x, texCoords.y); 
    glVertex2i(windowBounds.x, discYBounds.x);

    glTexCoord2f(texCoords.x, texCoords.w);
    glVertex2i(windowBounds.x, discYBounds.y);

    glTexCoord2f(texCoords.z, texCoords.y); 
    glVertex2i(windowBounds.z, discYBounds.x);

    glTexCoord2f(texCoords.z, texCoords.w); 
    glVertex2i(windowBounds.z, discYBounds.y);
    glEnd();

    parent->disableGUITexture();
  }
  else
  {
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2i(windowBounds.x, discYBounds.x);
    glVertex2i(windowBounds.x, discYBounds.y);
    glVertex2i(windowBounds.z, discYBounds.x);
    glVertex2i(windowBounds.z, discYBounds.y);
    glEnd();
  }
  glDisable(GL_BLEND);
  glTranslatef(0, float(-offset), 0);
}

const Tuple4i &GUISlider::getWindowBounds()
{
  if(parent && update)
  {
    GUIRectangle::computeWindowBounds();
    label.computeDimensions();
    realWindowBounds    = windowBounds;
   
    if(orientation == OR_HORIZONTAL)
    {
      int difference = label.getWidth() -  getWidth();
        
      realWindowBounds.x -= discDimensions.x/2;
      realWindowBounds.z += discDimensions.x/2;

      if(difference > 0)
      {
        difference /= 2;
        realWindowBounds.x -= difference;
        realWindowBounds.z += difference;
      }

      realWindowBounds.w += int(label.getHeight()/1.25f);
      offset = clamp(windowBounds.x - realWindowBounds.x, 0, 500);
    }
    else
    {
      offset               = discDimensions.y/2;
      realWindowBounds.y  -= discDimensions.y/2;
      realWindowBounds.w  += discDimensions.y/2;
    }
  }
  return realWindowBounds;
}

void GUISlider::checkMouseEvents(MouseEvent &evt, int extraInfo, bool reservedBits)
{
  GUIEventListener *eventsListener = getEventsListener();
  bool              nRelease = pressed;

  windowBounds.x += (orientation == OR_HORIZONTAL) ? offset : 0;
  windowBounds.y += (orientation != OR_HORIZONTAL) ? offset : 0;
  windowBounds.z += (orientation == OR_HORIZONTAL) ? offset : 0;
  windowBounds.w += (orientation != OR_HORIZONTAL) ? offset : 0;

  GUIRectangle::checkMouseEvents(evt, extraInfo, reservedBits);

  released = !pressed && nRelease;

  if(pressed || released)
  {
    progress = (orientation == OR_HORIZONTAL) ?
                clamp(float(evt.getX() - windowBounds.x)/ (windowBounds.z - windowBounds.x), 0.0f, 1.0f) :
                clamp(1.0f - float(evt.getY() - windowBounds.y)/ (windowBounds.w - windowBounds.y), 0.0f, 1.0f);

    if(eventsListener){
      GUIEvent event = GUIEvent(this);
      eventsListener->actionPerformed(event);
    }
  }

  windowBounds.x -= (orientation == OR_HORIZONTAL) ? offset : 0;
  windowBounds.y -= (orientation != OR_HORIZONTAL) ? offset : 0;
  windowBounds.z -= (orientation == OR_HORIZONTAL) ? offset : 0;
  windowBounds.w -= (orientation != OR_HORIZONTAL) ? offset : 0;
}
