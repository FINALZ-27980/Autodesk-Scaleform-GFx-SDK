#include "../GUI/EasyGL.h"

GUILabel::GUILabel(const std::string &ls,
                   const std::string &callback) :  GUIAlphaElement(callback)
{
  setDimensions(40, 5);
  setLabelString(ls);
  widgetType = WT_LABEL;
}

bool GUILabel::loadXMLSettings(const TiXmlElement *element)
{
  if(!XMLArbiter::inspectElementInfo(element, "Label"))
    return Logger::writeErrorLog("Need a Label node in the xml file");

  return  GUIAlphaElement::loadXMLSettings(element);
}

void GUILabel::render(float clockTick)
{
  if(!parent || !visible)
    return;

  Tuple2i center = getCenter();

  if(label.needUpdating())
    parent->forceUpdate(true);

  switch(anchor)
  {
    case AT_CORNERLU: label.print(windowBounds.x, windowBounds.y); break;
    case AT_CORNERLD: label.print(windowBounds.x, windowBounds.y - label.getHeight()); break;
    case AT_CORNERRU: label.print(windowBounds.z, windowBounds.y); break;
    case AT_CORNERRD: label.print(windowBounds.z, windowBounds.y - label.getHeight()); break;
    default: label.printCenteredXY(center.x, center.y);
  }
}

const Tuple4i &GUILabel::getWindowBounds()
{
  if(parent && update)
  {
    int height       = 0,
        width        = 0;
    label.computeDimensions();

    if(dimensions.x > 1)
      width  = dimensions.x  < label.getWidth() ? label.getWidth() : (int)dimensions.x;
    else
      width  = getWidth()    < label.getWidth() ? label.getWidth() : getWidth();
 
    if(dimensions.x > 1)
      height  = dimensions.y  < label.getHeight() ? label.getHeight() : (int)dimensions.y;
    else
      height  = getHeight()   < label.getHeight() ? label.getHeight() : getHeight();

    dimensions.set(float(width),  float(height));
    GUIRectangle::computeWindowBounds();
  }
  return windowBounds;
}
