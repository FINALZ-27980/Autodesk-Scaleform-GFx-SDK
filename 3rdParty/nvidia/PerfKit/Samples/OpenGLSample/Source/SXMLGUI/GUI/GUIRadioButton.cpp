#include "../GUI/EasyGL.h"

GUIRadioButton::GUIRadioButton(const std::string &callback) : GUICheckBox(callback)
{
  secondaryTexDesc = WT_CHECK_RB_MARK;
  primaryTexDesc   = WT_RADIO_BUTTON;
  widgetType       = WT_RADIO_BUTTON;
  markRatio        = 0.75f;
}

void GUIRadioButton::checkMouseEvents(MouseEvent &newEvent, int extraInfo, bool bits)
{
  GUIRectangle::checkMouseEvents(newEvent, extraInfo, true);

  if(clicked) 
  {
    if(!checked)
    {
      setChecked(true);
     ((GUIPanel*)parent)->notify(this);
    }
  }
  released = false;
  clicked  = false;
}
