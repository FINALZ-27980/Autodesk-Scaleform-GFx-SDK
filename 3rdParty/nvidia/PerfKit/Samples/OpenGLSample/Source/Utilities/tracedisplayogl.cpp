/***
 * Copyright (C) 2005
 * E. Scott Larsen and Jeff Kiel 
 * Copyright NVIDIA Corporation 2005
 * TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THIS SOFTWARE IS PROVIDED *AS IS* AND NVIDIA AND
 * AND ITS SUPPLIERS DISCLAIM ALL WARRANTIES, EITHER EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL NVIDIA
 * OR ITS SUPPLIERS BE LIABLE FOR ANY SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER
 * INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, LOSS OF
 * BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS) ARISING OUT OF THE USE OF OR INABILITY TO USE THIS
 * SOFTWARE, EVEN IF NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 **/
#include <GL/glut.h>
#include <math.h>

#include "tracedisplay.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**************************************************/
void COGLTraceDisplay::Push()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_TEXTURE_2D);
#ifdef GL_TEXTURE_RECTANGLE_NV
	//hmm, how to detect and re-enable if it is enabled?
	glDisable(GL_TEXTURE_RECTANGLE_NV);
#endif
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,1,0,1,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

    // Allow transparency...
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/**************************************************/
void COGLTraceDisplay::Pop()
{
    glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

/**************************************************/
void COGLTraceDisplay::Background()
{
	if (_draw_back)
	{
		glColor4fv(_background_color);
		glBegin(GL_QUADS);
		glVertex2f(_left,			_bottom);
		glVertex2f(_left+_width,	_bottom);
		glVertex2f(_left+_width,	_bottom+_height);
		glVertex2f(_left,			_bottom+_height);
		glEnd();
	}
}

/**************************************************/
void COGLTraceDisplay::Text(const Entries::iterator &it,const float count)
{
	if (_draw_text_column) {
		const float deltax = float(_width)/_entries.size();
		const float deltay = 0.02f;
		float centerAlign;
        char msg[256];
		int i, n, p, w;

		// Name
        n = sprintf(msg,"%s", it->trace->name().c_str());
        p = glutBitmapLength(_glutFont, (const unsigned char*)msg);
        w = glutGet(GLUT_WINDOW_WIDTH);
        centerAlign = (deltax - ((float)p / (float)w)) / 2.0f;

        glRasterPos2f(_left + centerAlign + (count * deltax), _bottom - 0.02f);
		for(i = 0; i < n; i++) {
			glutBitmapCharacter(_glutFont, msg[i]);
		}

        if (_draw_double_column) {
            n = sprintf(msg,"[%d, %d]", (int)it->trace->secondToLast(), (int)it->trace->last());
            p = glutBitmapLength(_glutFont, (const unsigned char*)msg);
            w = glutGet(GLUT_WINDOW_WIDTH);
            centerAlign = (deltax - ((float)p / (float)w)) / 2.0f;

            glRasterPos2f(_left + centerAlign + (count * deltax), _bottom - 0.02f - deltay);
            for(i = 0; i < n; i++) {
			    glutBitmapCharacter(_glutFont, msg[i]);
            }
        } else {
		    glRasterPos2f(_left + (count * deltax), _bottom - 0.02f - deltay);
            n = sprintf(msg,"[%.2f]", (float)it->trace->last());
		    for(i = 0; i < n; i++) {
			    glutBitmapCharacter(_glutFont, msg[i]);
		    }
        }

	} else if (_draw_text) {
		const float deltax = float(_width)/2.0f;
		const float deltay = 0.02f;
        glRasterPos2f(_left + (((int)count % 2) * deltax), _bottom - 0.02f - ((int)(count / 2) * deltay));
		char msg[256];
        int n = sprintf(msg,"%s [%.2f]",it->trace->name().c_str(), (float)it->trace->last());
		for(int i=0;i<n;i++)
			glutBitmapCharacter(_glutFont, msg[i]);
	}
}

/**************************************************/
void COGLTraceDisplay::DisplayLineStream()
{
	float count = 0;
	for(Entries::iterator it = _entries.begin(); it != _entries.end(); ++it)
	{
		glColor4fv(&(it->r));
		glBegin(GL_LINE_STRIP);
        float min = it->trace->min();
        float max = it->trace->max();
		float magic = max - min;
        float x, y;
		for (size_t i=0;i<it->trace->size();++i)
		{
            x = _left+_width*float(i)/float(it->trace->capacity()-1);
            y = _bottom+_height*((*(it->trace))(i) - min)/magic;
            y = y < min ? min : (y > max ? max : (y != y ? _bottom : y));

			glVertex2f(x, y);
		}
		glEnd();
		Text(it,count);
		++count;
	}
}

/**************************************************/
void COGLTraceDisplay::DisplayLineWrap()
{
	float count = 0;
	for(Entries::iterator it = _entries.begin(); it != _entries.end(); ++it)
	{
		glColor4fv(&(it->r));
		glBegin(GL_LINE_STRIP);
		float magic = it->trace->max() - it->trace->min();
		for (size_t i=0;i<it->trace->size();++i)
		{
			glVertex2f(_left+_width*float(i)/float(it->trace->capacity()-1),
			_bottom+_height*((*(it->trace))[i]-it->trace->min())/magic);
		}
		glEnd();
		Text(it,count);
		++count;
	}
}

/**************************************************/
void COGLTraceDisplay::DisplayNeedle()
{
	float base_percent = 15.0f;
	float count = 0;
	for(Entries::iterator it = _entries.begin(); it != _entries.end(); ++it)
	{
		glColor4fv(&(it->r));
		glBegin(GL_TRIANGLES);
		float magic = it->trace->max() - it->trace->min();
		float a = float(1) - (it->trace->last()-it->trace->min())/magic;
		a *= float(M_PI);
		glVertex2f(_left+_width/float(2)+_width*cosf(a+M_PI/float(2))/base_percent,_bottom+_height*sinf(a+M_PI/float(2))/base_percent);
		glVertex2f(_left+_width/float(2)+_width*cosf(a-M_PI/float(2))/base_percent,_bottom+_height*sinf(a-M_PI/float(2))/base_percent);
		glVertex2f(_left+_width/float(2)+_width*cosf(a)/float(2),_bottom+_height*sinf(a));
		glEnd();
		Text(it,count);
		++count;
	}
}

/**************************************************/
void COGLTraceDisplay::DisplayBar()
{
	float count = 0;
	float max = (float)_entries.size();

    if (_draw_double_column) {
	    for(Entries::iterator it = _entries.begin(); it != _entries.end(); ++it)
	    {
		    float magic = it->trace->max() - it->trace->min();
            float data0 = it->trace->secondToLast();
		    float data1 = it->trace->last();

            float localLeft   = _left + ((((0.0f + count)*_width)/max) * 1.02f);
            float localMiddle = _left + ((((0.5f + count)*_width)/max) * 1.00f);
            float localRight  = _left + ((((1.0f + count)*_width)/max) * 0.98f);

            glBegin(GL_QUADS);

		    glColor4fv(&(it->r));
		    glVertex2f(localLeft,   _bottom);
		    glVertex2f(localMiddle, _bottom);
		    glVertex2f(localMiddle, _bottom+_height*(data0-it->trace->min())/magic);
		    glVertex2f(localLeft,   _bottom+_height*(data0-it->trace->min())/magic);

		    glColor4f((&(it->r))[0]*0.75f, (&(it->r))[1]*0.75f, (&(it->r))[2]*0.75f, 1.0f);
            glVertex2f(localMiddle, _bottom);
		    glVertex2f(localRight,  _bottom);
		    glVertex2f(localRight,  _bottom+_height*(data1-it->trace->min())/magic);
		    glVertex2f(localMiddle, _bottom+_height*(data1-it->trace->min())/magic);

		    glEnd();

            Text(it,count);
		    ++count;
	    }
    } else {
        for(Entries::iterator it = _entries.begin(); it != _entries.end(); ++it)
	    {
		    glColor4fv(&(it->r));
		    glBegin(GL_QUADS);
		    float magic = it->trace->max() - it->trace->min();
		    glVertex2f(_left + count*_width/max,		_bottom);
		    glVertex2f(_left + (1.0f+count)*_width/max,	_bottom);
		    glVertex2f(_left + (1.0f+count)*_width/max,	_bottom+_height*(it->trace->last()-it->trace->min())/magic);
		    glVertex2f(_left + count*_width/max,		_bottom+_height*(it->trace->last()-it->trace->min())/magic);
		    glEnd();
		    Text(it,count);
		    ++count;
	    }
    }
}
