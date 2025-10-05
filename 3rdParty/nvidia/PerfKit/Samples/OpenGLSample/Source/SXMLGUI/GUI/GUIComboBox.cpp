#include "../GUI/EasyGL.h"

GUIComboBox::GUIComboBox(const std::string& cbs) : GUIRectangle(cbs)

{
  setScrollingColor(0.2f, 0.75f, 0.35f, 1.0f);
  setFontScales(1.0f, 1.0f);
  setPosition(0.5, 0.5);

  currentSelection = new GUILabel("Unknown", "itemCBS_0");
  dropMenuButton   = new GUIButton("cbddb");
  upperPanel       = new GUIPanel("cbup");
  lowerPanel       = new GUIPanel("cblp");

  upperPanel->setLayout(PL_XAXIS_LAYOUT);

  upperPanel->setVisibleBounds(true);
  upperPanel->enableBGColor(true);
  upperPanel->setInterval(6, 3);
  upperPanel->addWidget(currentSelection);
  upperPanel->addWidget(dropMenuButton);

  lowerPanel->setLayout(PL_YAXIS_LAYOUT);
  lowerPanel->setInterval(6, 2);
  lowerPanel->setVisible(false);
  lowerPanel->enableBGColor(true);
  lowerPanel->setVisibleBounds(true);
  lowerPanel->setAnchorPoint(AT_CORNERLU);
  lowerPanel->setClipSize(0);

  displayScrollingRectangle =      true;
  selectionIndex            =        -1;
  widgetType                = WT_COMBO_BOX;
  fontIndex                 =         0;
  lockItems                 =     false;
  deployed                  =     false;
}

GUIComboBox::~GUIComboBox()
{
  deleteObject(upperPanel);
  deleteObject(lowerPanel);  
}

GUIEventListener  *GUIComboBox::getEventsListener()
{
  return this;
}

void  GUIComboBox::setFontScales(const Tuple2f &scales)
{
  setFontScales(scales.x, scales.y);
}

void  GUIComboBox::setFontScales(float wScale, float hScale)
{
  fontScales.x = clamp(hScale, 0.01f, 20.0f);
  fontScales.y = clamp(wScale, 0.01f, 20.0f);
}

const Tuple2f  &GUIComboBox::getFontScales()
{
  return fontScales;
}

bool GUIComboBox::loadXMLSettings(const TiXmlElement *element)
{
  if(!XMLArbiter::inspectElementInfo(element, "ComboBox"))
    return Logger::writeErrorLog("Need a ComboBox node in the xml file");

  const   TiXmlElement *child  = NULL;
  Tuple3f bordersColor         = upperPanel->getBordersColor();
  Tuple4f bgColor              = upperPanel->getBGColor();
  float   lowerPanelColorScale = 1.0f;

  if(child = XMLArbiter::getChildElementByName(element, "Button"))
  {
    dropMenuButton->loadXMLClippedRectangleInfo(child);
    dropMenuButton->loadXMLSettings(child);
    dropMenuButton->setCallbackString("cbddb");
    dropMenuButton->setLabelString("");
    dropMenuButton->setActive(true);
    dropMenuButton->setVisible(true);
  }

  displayScrollingRectangle = XMLArbiter::analyzeBooleanAttr(element, "displayScrollingRectangle", displayScrollingRectangle);
  lowerPanelColorScale      = XMLArbiter::fillComponents1f(element,   "lowerPanelColorScale", lowerPanelColorScale);
  fontScales.y              = XMLArbiter::fillComponents1f(element,   "hScale",    fontScales.y);
  fontScales.x              = XMLArbiter::fillComponents1f(element,   "wScale",    fontScales.x);
  fontIndex                 = XMLArbiter::fillComponents1i(element,   "fontIndex", fontIndex);

  for(child = element->FirstChildElement();	
      child;
   	  child = child->NextSiblingElement() )
  {
    const char *value = child->Value();
    if(!value)
      continue;

    if(!strcmp(value, "ScrollingColor"))
      setScrollingColor(XMLArbiter::fillComponents4f(child, scrollingColor));

    if(!strcmp(value, "BordersColor"))
      XMLArbiter::fillComponents3f(child, bordersColor);

    if(!strcmp(value, "BGColor"))
      XMLArbiter::fillComponents4f(child, bgColor);

    if(!strcmp(value, "Item"))
      addItem(child->Attribute("string"));
  }

  upperPanel->setBordersColor(bordersColor);
  lowerPanel->setBordersColor(bordersColor);

  upperPanel->setBGColor(bgColor);
  lowerPanel->setBGColor(bgColor.x*lowerPanelColorScale,
                         bgColor.y*lowerPanelColorScale,
                         bgColor.z*lowerPanelColorScale,
                         bgColor.w);

  setFontScales(fontScales);

  return GUIRectangle::loadXMLSettings(element) && (items.size() != 0);
}

void GUIComboBox::checkMouseEvents(MouseEvent &evt, int extraInfo, bool rBits)
{
  upperPanel->checkMouseEvents(evt, extraInfo, rBits);
  scrollingRectangle.x = 1;

  if(lowerPanel->isVisible())
    lowerPanel->checkMouseEvents(evt, extraInfo, rBits);

  if(!currentSelection->isFocused() && !dropMenuButton->isFocused())
    deployed = false;

  if(deployed)
  {
    lowerPanel->setVisible(true);
    evt.consume();
  }
  else
    lowerPanel->setVisible(false);
}

void GUIComboBox::actionPerformed(GUIEvent &evt)
{
  GUIEventListener  *eventsListener  = parent->getEventsListener();
  GUIRectangle      *sourceRectangle = evt.getEventSource();
  int                widgetType      = sourceRectangle->getWidgetType();

  if(currentSelection->isClicked() || dropMenuButton->isClicked())
    deployed = !deployed;

  if(widgetType == WT_LABEL && (sourceRectangle->getParent() == lowerPanel))
  {
    GUILabel *newSelection = (GUILabel*)sourceRectangle;
    if(newSelection->isMouseOver())
      scrollingRectangle = newSelection->getWindowBounds();

    if(newSelection->isClicked() && (newSelection->getLabelString() != currentSelection->getLabelString()))
    {
      currentSelection->setLabelString(newSelection->getLabelString());
      selectionIndex = getItemIndex(newSelection->getLabelString());
      update         = true;
      if(eventsListener)
			{
				GUIEvent evt(this);
        eventsListener->actionPerformed(evt);
			}
    }
  }
}

void GUIComboBox::render(float clockTick)
{
  if(!parent || !visible)
    return;

  computeWindowBounds();
  upperPanel->render(clockTick);

  if(lowerPanel->isVisible())
  {
    lowerPanel->renderClippedBounds();
    lowerPanel->enableBGColor(false);
    lowerPanel->setVisibleBounds(false);

    if(scrollingRectangle.x >= lowerPanel->getWindowBounds().x && displayScrollingRectangle)
    {

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4fv(scrollingColor);

      glBegin(GL_TRIANGLE_STRIP);
      glVertex2i(scrollingRectangle.x - 2, scrollingRectangle.y);
      glVertex2i(scrollingRectangle.x - 2, scrollingRectangle.w);
      glVertex2i(scrollingRectangle.z + 1, scrollingRectangle.y);
      glVertex2i(scrollingRectangle.z + 1, scrollingRectangle.w);
      glEnd();

      glDisable(GL_BLEND);
    }

    lowerPanel->render(clockTick);
    lowerPanel->enableBGColor(true);
    lowerPanel->setVisibleBounds(true);
  }
}

void GUIComboBox::finalizeSize()
{
  if(!items.size() || lockItems )
    return;

  GUIFont *font             = GUIFontManager::getFont(fontIndex);
  const    int    *spaces   = font ? font->getFontObject()->getCharHorizontalGlyphs() : NULL;
  float            maxWidth = 0,
                   height   = 0;
  int              cbsIndex = 1;
  if(spaces)
  {
    float  width    = 0;
    size_t length   = 0;

    height   =  float(font->getFontObject()->getHeight());

    for(size_t l = 0; l < items.size(); l++)
    {
      length = items[l].size();
      width  = 0.0f;

      for(size_t t = 0; t < length; t++)
        width += spaces[items[l][t]];

      maxWidth = width > maxWidth ? width : maxWidth;
    }
  }
  else
    return;

  currentSelection->setLabelString(items[0]);
  currentSelection->setDimensions(maxWidth*fontScales.x + 2.0f, height*fontScales.y);
  currentSelection->getLabel()->setFontIndex(fontIndex);
  currentSelection->getLabel()->setScales(fontScales);
  dropMenuButton->setDimensions(height*fontScales.y + 4.0f, height*fontScales.y + 4.0f);

  char buffer[256];
  
  for(size_t l = 0; l < items.size(); l++)
  {
    sprintf(buffer, "itemCBS %d", (cbsIndex++));
    GUILabel *newLabel = new GUILabel(items[l].c_str(), buffer);
    newLabel->getLabel()->setFontIndex(fontIndex);
    newLabel->setDimensions(maxWidth*fontScales.x + 2.0f /*+ height*fontScales.y + 10.0f*/, height*fontScales.y);
    newLabel->getLabel()->setScales(fontScales);
    if(!lowerPanel->addWidget(newLabel))
      deleteObject(newLabel);
  }
  selectionIndex =    0;
  lockItems      = true;
}

const void GUIComboBox::computeWindowBounds()
{
  finalizeSize();

  if(parent && update)
  {
    upperPanel->setAnchorPoint(getAnchorPoint());
    upperPanel->setPosition(getPosition());
    upperPanel->setParent(parent);
    upperPanel->forceUpdate(true);
    upperPanel->computeWindowBounds();
    upperPanel->forceUpdate(false);
    windowBounds = upperPanel->getWindowBounds();

    lowerPanel->setPosition(0.0f, float(upperPanel->getHeight()));
    lowerPanel->setParent(upperPanel);
    lowerPanel->forceUpdate(true);

    //Redirect mouse events to combo box action listener
    lowerPanel->setParent(this);
    upperPanel->setParent(this);
  }
}

void GUIComboBox::addItem(const std::string &item)
{
  if(lockItems || !item.size())
    return;

  for(size_t t = 0; t < items.size(); t++)
    if(items[t] == item)
      return;

  items.push_back(item);
}

int  GUIComboBox::getItemIndex(const std::string &item)
{
  for(size_t t = 0; t < items.size(); t++)
    if(items[t] == item)
      return int(t);

  return -1;
}

const std::vector<std::string> &GUIComboBox::getItems() const
{
  return items;
}

const char  *GUIComboBox::getSelectedItem()  const
{
  return selectionIndex < 0 ? NULL : items[selectionIndex].c_str();
}

const char  *GUIComboBox::getItem(size_t index) const
{
  return index >= items.size() ? NULL :  items[index].c_str();
}

void    GUIComboBox::setScrollingColor(float r, float g, float b, float a)
{
  scrollingColor.set(clamp(r, 0.0f, 255.0f),
                     clamp(g, 0.0f, 255.0f),
                     clamp(b, 0.0f, 255.0f),
                     clamp(a, 0.0f, 255.0f));

  scrollingColor.x /= (scrollingColor.x > 1.0) ? 255.0f : 1.0f;
  scrollingColor.y /= (scrollingColor.y > 1.0) ? 255.0f : 1.0f;
  scrollingColor.z /= (scrollingColor.z > 1.0) ? 255.0f : 1.0f;
  scrollingColor.w /= (scrollingColor.w > 1.0) ? 255.0f : 1.0f;
}

void    GUIComboBox::setScrollingColor(const Tuple4f &rgba)
{
  setScrollingColor(rgba.x, rgba.y, rgba.z, rgba.w);
}

const   Tuple4f &GUIComboBox::getScrollingColor() const
{
  return  scrollingColor;
}

void    GUIComboBox::enableScrollingRectangle(bool on)
{
  displayScrollingRectangle = on;
}

bool    GUIComboBox::scrollingRectangleEnabled()
{
  return displayScrollingRectangle;
}

bool GUIComboBox::isDeployed()
{
  if(lowerPanel) return lowerPanel->isVisible();
  return false;
}
