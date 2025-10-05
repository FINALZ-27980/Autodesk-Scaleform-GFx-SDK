#include "../GUI/EasyGL.h"

GUIClippedRectangle::GUIClippedRectangle(int size)
{
  setTextureRectangle(0,0,1,1);
  setBordersColor(0.0f, 0.9f, 0.0f);
  setClipSize(size);
  setBGColor(0.413f, 0.7f, 0.52f, 0.75f);

  drawBackground = false;
  drawBounds     = false;
}

void  GUIClippedRectangle::setClipSize(int clipSizeArg)
{
  clipSize = clamp(clipSizeArg, 0, 100);
}

int GUIClippedRectangle::getClipSize()
{
  return clipSize;
}

void GUIClippedRectangle::setVisibleBounds(bool visibleArg)
{
  drawBounds = visibleArg;
}

bool  GUIClippedRectangle::boundsVisible()
{
  return drawBounds;
}

bool GUIClippedRectangle::loadXMLClippedRectangleInfo(const TiXmlElement *element)
{
  if(!element)
    return false;

  const TiXmlElement *absolutePriority = XMLArbiter::getChildElementByName(element, "Texture");
  setVisibleBounds(XMLArbiter::analyzeBooleanAttr(element,  "drawBounds",     drawBounds));
  enableBGColor(XMLArbiter::analyzeBooleanAttr(element,     "drawBackground", drawBackground));
  setClipSize(XMLArbiter::fillComponents1i(element,         "clipSize",       clipSize));
 
  if(absolutePriority)
    texture.loadXMLSettings(absolutePriority);

  for(const TiXmlElement *child = element->FirstChildElement();	
      child;
   	  child = child->NextSiblingElement() )
  {
    const char * value = child->Value();

    if(!value)
      continue;

    if(!strcmp(value, "TextureRectangle"))
      setTextureRectangle(XMLArbiter::fillComponents4f(child, textureRectangle));

    if(!strcmp(value, "BordersColor"))
      setBordersColor(XMLArbiter::fillComponents3f(child, bordersColor));
 
    if(!strcmp(value, "BGColor"))
      setBGColor(XMLArbiter::fillComponents4f(child, bgColor));
  }

  return true;
}

void  GUIClippedRectangle::setBGColor(const Tuple4f& color)
{
  setBGColor(color.x, color.y, color.z, color.w);
}

void  GUIClippedRectangle::setBGColor(float r, float g, float b, float a)
{
  bgColor.set(clamp(r, 0.0f, 255.0f),
              clamp(g, 0.0f, 255.0f),
              clamp(b, 0.0f, 255.0f),
              clamp(a, 0.0f, 255.0f));

  bgColor.x /= (bgColor.x > 1.0) ? 255.0f : 1.0f;
  bgColor.y /= (bgColor.y > 1.0) ? 255.0f : 1.0f;
  bgColor.z /= (bgColor.z > 1.0) ? 255.0f : 1.0f;
  bgColor.w /= (bgColor.w > 1.0) ? 255.0f : 1.0f;
}

void  GUIClippedRectangle::setBordersColor(const Tuple3f& color)
{
  setBordersColor(color.x, color.y, color.z);
}

const Tuple3f &GUIClippedRectangle::getBordersColor()
{
  return bordersColor;
}

void  GUIClippedRectangle::setBordersColor(float r, float g, float b)
{
  bordersColor.set(clamp(r, 0.0f, 255.0f),
                   clamp(g, 0.0f, 255.0f),
                   clamp(b, 0.0f, 255.0f));
  bordersColor.x /= (bordersColor.x > 1.0) ? 255.0f : 1.0f;
  bordersColor.y /= (bordersColor.y > 1.0) ? 255.0f : 1.0f;
  bordersColor.z /= (bordersColor.z > 1.0) ? 255.0f : 1.0f;
}

void GUIClippedRectangle::renderClippedBounds()
{
  if(drawBackground || drawBounds)
  {
    glVertexPointer(2, GL_INT, 0, vertices[0]);
    glEnableClientState(GL_VERTEX_ARRAY);

    if(texture.getID() && drawBackground)
    {
      glTexCoordPointer(2, GL_FLOAT, 0, texCoords[0]) ;
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      texture.activate();
    }
  }

  if(drawBackground)
  {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4fv(bgColor);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 7);
    glDisable(GL_BLEND);

    if(texture.getID())
    {
      texture.deactivate();
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
  }

  if(drawBounds)
  {
    glColor3fv(bordersColor);
    glDrawArrays(GL_LINE_STRIP, 0, 7);
  }

  glColor3f(1,1,1);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void  GUIClippedRectangle::computeClippedBounds(const Tuple4i &windowBounds)
{
  float yTexOffset    = float(clipSize)/(windowBounds.w - windowBounds.y),
        xTexOffset    = float(clipSize)/(windowBounds.z - windowBounds.x);

  xTexOffset *= textureRectangle.z - textureRectangle.x;
  yTexOffset *= textureRectangle.w - textureRectangle.y;

  vertices[0].set(windowBounds.x, windowBounds.y + clipSize);
  vertices[1].set(windowBounds.x, windowBounds.w);
  vertices[2].set(windowBounds.z - clipSize, windowBounds.w);
  vertices[3].set(windowBounds.z, windowBounds.w - clipSize);
  vertices[4].set(windowBounds.z, windowBounds.y);
  vertices[5].set(windowBounds.x + clipSize, windowBounds.y);
  vertices[6].set(windowBounds.x, windowBounds.y + clipSize);

  texCoords[0].set(textureRectangle.x             , textureRectangle.w - yTexOffset);
  texCoords[1].set(textureRectangle.x             , textureRectangle.y);
  texCoords[2].set(textureRectangle.z - xTexOffset, textureRectangle.y             );
  texCoords[3].set(textureRectangle.z             , textureRectangle.y + yTexOffset);
  texCoords[4].set(textureRectangle.z             , textureRectangle.w);
  texCoords[5].set(textureRectangle.x + xTexOffset, textureRectangle.w             );
  texCoords[6].set(textureRectangle.x             , textureRectangle.w - yTexOffset);
}

void  GUIClippedRectangle::enableBGColor(bool enable)
{
  drawBackground = enable;
}

void GUIClippedRectangle::setTextureRectangle(const Tuple4f &tr)
{
  setTextureRectangle(tr.x, tr.y, tr.z, tr.w);
}

void GUIClippedRectangle::setTextureRectangle(float x, float y, float z, float w)
{
  if(x > 1.0f || y > 1.0f || z > 1.0f || w > 1.0f)
  if(texture.getID())
  {
    x = clamp(x, 0.0f, float(texture.getWidth() ));
    y = clamp(y, 0.0f, float(texture.getHeight()));
    z = clamp(z, 0.0f, float(texture.getWidth() ));
    w = clamp(w, 0.0f, float(texture.getHeight()));
    
    x /= texture.getWidth();
    z /= texture.getWidth();

    w /= texture.getHeight();
    y /= texture.getHeight();

  }

  textureRectangle.set(clamp(x, 0.0f, 1.0f),
                       clamp(y, 0.0f, 1.0f),
                       clamp(z, 0.0f, 1.0f),
                       clamp(w, 0.0f, 1.0f));
}

const  Tuple4f &GUIClippedRectangle::getTextureRectangle()
{
  return textureRectangle;
} 

Texture &GUIClippedRectangle::getTexture()
{
  return texture;
} 

void  GUIClippedRectangle::setTexture(const Texture & textureArg)
{
  texture = textureArg;
}

bool  GUIClippedRectangle::isBGColorOn()
{
  return drawBackground;
}

const Tuple4f &GUIClippedRectangle::getBGColor()
{
  return bgColor;
}

const Tuple2i *GUIClippedRectangle::getVertices() const
{
  return vertices;
}

const Tuple2f *GUIClippedRectangle::getTexCoords() const
{
  return texCoords;
}
