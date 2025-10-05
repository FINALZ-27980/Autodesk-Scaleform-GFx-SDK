#include "../GUI/EasyGL.h"

GUIButton::GUIButton(const std::string &callback) :  GUIAlphaElement(callback), GUIClippedRectangle()
{
  setBordersColor(0.0f, 0.0f, 0.0f);
  setDimensions(40, 22);
  setPosition(0.5, 0.5);
  setColor(100, 150, 190);

  widgetType     = WT_BUTTON;

  drawBackground = true;
  drawBounds     = true;
  bounce         = true;
}

bool GUIButton::loadXMLSettings(const TiXmlElement *element)
{
  if(!XMLArbiter::inspectElementInfo(element, "Button"))
    return Logger::writeErrorLog("Need a Button node in the xml file");

  enableBounce(XMLArbiter::analyzeBooleanAttr(element, "bounce", true));
  return GUIAlphaElement::loadXMLSettings(element) &&
         GUIClippedRectangle::loadXMLClippedRectangleInfo(element);
}

void GUIButton::enableBounce(bool bounce_){ bounce = bounce_; }
bool GUIButton::bounceEnabled()           { return bounce;    }

void GUIButton::render(float clockTick)
{
  if(!parent || !visible)
    return;

  modifyCurrentAlpha(clockTick);
  bgColor = color;

  Tuple3f tempColor    = label.getColor();
  float   displacement = 2.0f*(pressed || clicked)*bounce;
  int     xCenter      = (windowBounds.x + windowBounds.z)/2,
          yCenter      = (windowBounds.y + windowBounds.w)/2;

  glTranslatef(displacement, displacement, 0.0);
  renderClippedBounds();
  label.printCenteredXY(xCenter, yCenter);
  glTranslatef(-displacement, -displacement, 0.0f);
}

const void GUIButton::computeWindowBounds()
{
  if(parent && update)
  {
    GUIRectangle::computeWindowBounds();
    label.computeDimensions();

    int width  = windowBounds.z - windowBounds.x,
        height = windowBounds.w - windowBounds.y;

    if(width  <= label.getWidth() + 2*clipSize)
    {
      if(anchor == AT_CENTER)
      {
        width = (label.getWidth() - width)/2 + clipSize + 2;
        windowBounds.x -=width;
        windowBounds.z +=width;
      }
      if((anchor == AT_CORNERLU) || (anchor == AT_CORNERLD))
      {
        width = (label.getWidth() - width)/2 + clipSize + 2;
        windowBounds.z +=2*width;
      }
    }

    if(height + 2*clipSize <  label.getHeight())
    {

      height = (label.getHeight() - height)/2 + clipSize + 2;
      windowBounds.y -= height;
      windowBounds.w += height;
    }

    computeClippedBounds(windowBounds);
  }
}
