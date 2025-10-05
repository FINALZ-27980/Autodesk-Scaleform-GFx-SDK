/* CFont
 *
 * Copyright (C) 2003-2004, Alexander Zaprjagaev <frustum@frustum.org>
 * Modified by Abdul Bezrati <abezrati@hotmail.com>
 */

#include "Font.h"
#include "GenUtils.h"

CFont::CFont()
{
  fontBaseRange = 0;
  fontHeight    = 0;
  memset(spaces, 0, 256);
}

CFont::~CFont()
{
  if(fontBaseRange)
    glDeleteLists(fontBaseRange, 256);

  fontBaseRange = 0;
  fontTexture.destroy();
}

bool CFont::load(const char* fontPath)
{
  Image  image;
  int    width  = 0,
         height = 0;

  if(!image.load(fontPath))
    return Logger::writeErrorLog("Can't load font file");

  if(image.getComponentsCount() != 4)
    return Logger::writeErrorLog("RGBA image required for font");

  if(!fontTexture.load2DImage(image, GL_CLAMP, GL_CLAMP, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, true))
   return Logger::writeErrorLog("Can't create font texture");

  unsigned char *data = (unsigned char*)image.getDataBuffer();

  height = image.getHeight();
  width  = image.getWidth();

  int spacey[256];
  memset(spacey, 0, 256);

  int size   = width,
      step   = size / 16;

  int x,y,i,j,k;
  for(y = 0, i = 0; y < 16; y++)
  {
    for(x = 0; x < 16; x++, i++)
    {
      unsigned char *ptr;
      spacey[i] = 0;
      for(j = 0; j < step; j++)
      {
        ptr = data + (size * y * step + x * step + j) * 4;
        for(k = 0; k < step; k++)
        {
          if(*(ptr + 3) != 0) break;
          ptr += size * 4;
        }
        if(k != step) break;
        spacey[i]++;
      }
      spaces[i] = 0;
      if(spacey[i] == step)
        continue;
      for(j = step - 1; j >= 0; j--)
      {
        ptr = data + (size * y * step + x * step + j) * 4;
        for(k = 0; k < step; k++) {
          if(*(ptr + 3) != 0) break;
          ptr += size * 4;
        }
        if(k != step) break;
        spaces[i]++;
      }
      spaces[i] = step - spacey[i] - spaces[i];
    }
  }

  if(fontBaseRange)
    glDeleteLists(fontBaseRange, 256);

  fontTexture.activate();
  fontBaseRange = glGenLists(256);

  spaces[(int)(' ')] = step/3;

  for(y = 0, i = 0; y < 16; y++)
  {
    for(x = 0; x < 16; x++, i++)
    {
      float s = (float)x / 16.0f + (float)spacey[i] / (float)size;
      float t = (float)y / 16.0f;
      float ds = (float)spaces[i] / (float)size;
      float dt = 1.0f/ 16.0;
  
      glNewList(fontBaseRange + i,GL_COMPILE);
      glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2f(s + ds,t + dt); glVertex2i(spaces[i],step);
      glTexCoord2f(s + ds,t     ); glVertex2i(spaces[i],   0);
      glTexCoord2f(s     ,t + dt); glVertex2i(0        ,step);
      glTexCoord2f(s     ,t     ); glVertex2i(0        ,   0);
      glEnd();
      glTranslatef(float(spaces[i]),0,0);
      glEndList();
    }
  }
  fontTexture.deactivate();
  fontHeight = height/16;
  return true;
}

Tuple2i CFont::getStringDimensions(const std::string &string)
{
  Tuple2i dimensions(0, fontHeight);

  for(size_t i = 0; i < string.size(); i++)
    dimensions.x += spaces[int(string[i])];

  return dimensions;
}

int  CFont::getMaxFittingLength(const std::string &string, int bounds)
{
  int index         = 0,
      currentLength = 0;

  if(!bounds || !string.size() || !fontTexture.getID())
    return 0;

  for(size_t i = 0; i < string.size(); i++)
    if(currentLength < bounds)
    {
      currentLength += spaces[int(string[i])];
      index++;
    }
    else 
     break;

  return (currentLength < bounds) ? index : index - 1;
}


void CFont::printProportional(float widthRatio, float heightRatio,
                             float width,      float height,
                             float r, float g, float b,
                             const std::string &string)
{
  Tuple4i viewport;

  if(!string.size())
    return;

  glGetIntegerv(GL_VIEWPORT, viewport);

  Tuple2i dimensions = getStringDimensions(string);

  float xPosition = (viewport.z - dimensions.x*width)*widthRatio,
        yPosition = (viewport.w - dimensions.y*height)*heightRatio;

  print(xPosition, yPosition, width, height, r, g, b, string);
}

void CFont::print(float xPosition,  float yPosition,
                 float width,      float height,
                 float r, float g, float b,
                 const std::string &string)
{
  GLint stringLength =  GLint(string.size());
  if(!stringLength || !fontTexture.getID())
    return;

  glColor3f(r,g,b);
  fontTexture.activate();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(xPosition, yPosition, 0);

  glListBase(fontBaseRange);
  glScalef(width, height,1.0f);
  glCallLists(stringLength,GL_UNSIGNED_BYTE, string.c_str());
  glPopMatrix();
  glDisable(GL_BLEND);

  fontTexture.activate();
  glColor3f(1,1,1);
}

int  CFont::getHeight()
{
  return fontHeight;
}

void CFont::printSubString(float xPosition,  float yPosition,
                          float width,      float height,
                          float r, float g, float b,
                          int   start, int end,
                          const std::string &string)
{
  if(start >= end)
    return;

  int stringLength =  int(string.size());
  if(stringLength  < end)
    return;

  glColor3f(r,g,b);
  fontTexture.activate();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(xPosition, yPosition, 0);

  glListBase(fontBaseRange);
  glScalef(width, height,1.0f);
  glCallLists(end - start,GL_UNSIGNED_BYTE, string.c_str() + start);
  glPopMatrix();
  glDisable(GL_BLEND);

  fontTexture.deactivate();
  glColor3f(1,1,1);
}

const   int *CFont::getCharHorizontalGlyphs() const{ return spaces; }

