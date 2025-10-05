#include "../GUI/EasyGL.h"

vector<GUIFont *> GUIFontManager::guiFontList;
GUIFont *GUIFontManager::currentFont    = NULL;
GUIFont *GUIFontManager::defaultFont    = NULL;

int GUIFontManager::getCharacterWidth(char Char, GUIFont *font)
{
  GUIFont *currentFont = getDefaultFont();
  if(!font)
  {
    if(currentFont)
      return  currentFont->getFontObject()->getCharHorizontalGlyphs()[Char];  
  }
  else
    return font->getFontObject()->getCharHorizontalGlyphs()[Char];
  return 0;
}

int GUIFontManager::getCharacterWidth(char Char, int fontIndex)
{
  GUIFont *currentFont = getFont(fontIndex);
  currentFont          = currentFont ? currentFont : getDefaultFont();
  if(currentFont)
    return  currentFont->getFontObject()->getCharHorizontalGlyphs()[Char];  

  return 0;
}

void  GUIFontManager::setCurrentFont(size_t index)
{
  setCurrentFont(getFont(index));
}

void GUIFontManager::setCurrentFont(GUIFont *currentFont_)
{
  if(!currentFont_ && !(currentFont_ = defaultFont))
    return;
  
  if(!currentFont || currentFont->operator!=(*currentFont_))
  {
    currentFont = currentFont_;
  }
}

GUIFont *GUIFontManager::getCurrentFont()
{
  return currentFont;
}

void GUIFontManager::setDefaultFont(size_t index)
{
  setDefaultFont(getFont(index));
}

void GUIFontManager::setDefaultFont(GUIFont *defaultFont_)
{
  defaultFont = defaultFont_;
}

GUIFont *GUIFontManager::getDefaultFont()
{
  return defaultFont;
}

int GUIFontManager::findFontIndex(GUIFont *font)
{
  if(!font)
    return -1;

  for(size_t i = 0; i < guiFontList.size(); i++)
    if(guiFontList[i]->operator ==(*font))
       return int(i);

  return -1;
}

GUIFont *GUIFontManager::getFont(size_t index)
{
  return index >= guiFontList.size() ? NULL : guiFontList[index];
}

int GUIFontManager::addFont(const TiXmlElement *fontNode)
{
  GUIFont *newFont  = new GUIFont();
  int      index    = -1;

  if(newFont->loadXMLSettings(fontNode))
  {
    index = findFontIndex(newFont);
    if(index >= 0)
    {
      deleteObject(newFont);
    }
    else
    {
      if(!newFont->build())
      {
        deleteObject(newFont);
      }
      else
      {
        if(newFont->build())
        {
          addFont(newFont);
          index = int(guiFontList.size() - 1);
        }
      }
    }
  }
  return index; 
}

bool GUIFontManager::addFont(GUIFont *font)
{
  if(!font)
    return false;

  guiFontList.push_back(font); 
  return true;
}

void GUIFontManager::clear()
{
  for(size_t i = 0; i < guiFontList.size(); i++)
    deleteObject(guiFontList[i]); 
  
  guiFontList.clear();
}
