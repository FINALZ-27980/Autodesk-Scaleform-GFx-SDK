#include "GenUtils.h"

/*******************************************************************************************/
/*IOXMLObject                                                                              */
/*                                                                                         */
/*******************************************************************************************/

IOXMLObject::IOXMLObject(const std::string &ionameArg)
{
  ioname = ionameArg;
}

bool IOXMLObject::loadXMLSettings(const std::string  &path  )
{
  if(!ioname.size())
    return Logger::writeErrorLog("Cannot load XML settings -> NULL element name");

  std::string verified = MediaPathManager::lookUpMediaPath(path);

  if(!verified.size())
    return Logger::writeErrorLog(std::string("Couldn't locate the <") +
                                 ioname + "> XML file at \""       +
                                 path   + "\" even with a look up");

  TiXmlDocument xmlStack(verified);

  if(!xmlStack.LoadFile())
    return Logger::writeErrorLog(std::string("Invalid XML file -> ") + verified);


  for(const TiXmlElement *child = xmlStack.FirstChildElement();
      child;
   	  child = child->NextSiblingElement() )
    if(ioname == child->Value())
      return loadXMLSettings(child);

  return Logger::writeErrorLog(std::string("Need a <") + ioname + "> tag in the XML file");
}

bool IOXMLObject::exportXMLSettings(const std::string &xmlPath)
{
  ofstream xmlFile(xmlPath.c_str(), ios::app | ios::binary);
  bool result = exportXMLSettings(xmlFile);
  xmlFile.close();
  return result;
}

bool IOXMLObject::isSuitable(const TiXmlElement *element)
{
  if(!element)
    return  Logger::writeErrorLog(std::string("NULL <") + ioname +  "> node");

  if(ioname != element->Value())
    return Logger::writeErrorLog(std::string("Need a <") + ioname + "> tag in the XML Node");

  return true;
}

/*******************************************************************************************/
/*XMLArbiter                                                                               */
/*                                                                                         */
/*******************************************************************************************/

Tuple4f &XMLArbiter::fillComponents4f(const TiXmlElement *element, Tuple4f &tuple)
{
  if(element)
  for(const TiXmlAttribute *attribute = element->FirstAttribute();
      attribute;
      attribute = attribute->Next())
  {
    const char *name  = attribute->Name(),
               *value = attribute->Value();

    if(name && value)
    switch(name[0])
    {
      case 'x': case 'X': case 'r': case 'R': case 's': case 'S':
        tuple.x = float(atof(value));
      break;

      case 'y': case 'Y': case 'g': case 'G': case 't': case 'T':
        tuple.y = float(atof(value));
      break;

      case 'z': case 'Z': case 'b': case 'B': case 'u': case 'U':
        tuple.z = float(atof(value));
      break;

      case 'w': case 'W': case 'a': case 'A': case 'v': case 'V':
        tuple.w = float(atof(value));
      break;
    }
  }
  return tuple;
}

Tuple4i &XMLArbiter::fillComponents4i(const TiXmlElement *element, Tuple4i &tuple)
{
  if(element)
  for(const TiXmlAttribute *attribute = element->FirstAttribute();
      attribute;
      attribute = attribute->Next())
  {
    const char *name  = attribute->Name(),
               *value = attribute->Value();

    if(name && value)
    switch(name[0])
    {
      case 'x': case 'X': case 'r': case 'R': case 's': case 'S':
        tuple.x = atoi(value);
      break;

      case 'y': case 'Y': case 'g': case 'G': case 't': case 'T':
        tuple.y = atoi(value);
      break;

      case 'z': case 'Z': case 'b': case 'B': case 'u': case 'U':
        tuple.z = atoi(value);
      break;

      case 'w': case 'W': case 'a': case 'A': case 'v': case 'V':
        tuple.w = atoi(value);
      break;
    }
  }
  return tuple;
}

Tuple4d &XMLArbiter::fillComponents4d(const TiXmlElement *element, Tuple4d &tuple)
{
  if(element)
  for(const TiXmlAttribute *attribute = element->FirstAttribute();
      attribute;
      attribute = attribute->Next())
  {
    const char *name  = attribute->Name(),
               *value = attribute->Value();

    if(name && value)
    switch(name[0])
    {
      case 'x': case 'X': case 'r': case 'R': case 's': case 'S':
        tuple.x = atof(value);
      break;

      case 'y': case 'Y': case 'g': case 'G': case 't': case 'T':
        tuple.y = atof(value);
      break;

      case 'z': case 'Z': case 'b': case 'B': case 'u': case 'U':
        tuple.z = atof(value);
      break;

      case 'w': case 'W': case 'a': case 'A': case 'v': case 'V':
        tuple.w = atof(value);
      break;
    }
  }
  return tuple;
}


Tuple3f &XMLArbiter::fillComponents3f(const TiXmlElement *element, Tuple3f &tuple)
{
  if(element)
  for(const TiXmlAttribute *attribute = element->FirstAttribute();
      attribute;
      attribute = attribute->Next())
  {
    const char *name  = attribute->Name(),
               *value = attribute->Value();

    if(name && value)
    switch(name[0])
    {
      case 'x': case 'X': case 'r': case 'R': case 's': case 'S':
        tuple.x = float(atof(value));
      break;

      case 'y': case 'Y': case 'g': case 'G': case 't': case 'T':
        tuple.y = float(atof(value));
      break;

      case 'z': case 'Z': case 'b': case 'B': case 'u': case 'U':
        tuple.z = float(atof(value));
      break;
    }
  }
  return tuple;
}

Tuple3i &XMLArbiter::fillComponents3i(const TiXmlElement *element, Tuple3i &tuple)
{
  if(element)
  for(const TiXmlAttribute *attribute = element->FirstAttribute();
      attribute;
      attribute = attribute->Next())
  {
    const char *name  = attribute->Name(),
               *value = attribute->Value();

    if(name && value)
    switch(name[0])
    {
      case 'x': case 'X': case 'r': case 'R': case 's': case 'S':
        tuple.x = atoi(value);
      break;

      case 'y': case 'Y': case 'g': case 'G': case 't': case 'T':
        tuple.y = atoi(value);
      break;

      case 'z': case 'Z': case 'b': case 'B': case 'u': case 'U':
        tuple.z = atoi(value);
      break;
    }
  }
  return tuple;
}

Tuple3d &XMLArbiter::fillComponents3d(const TiXmlElement *element, Tuple3d &tuple)
{
  if(element)
  for(const TiXmlAttribute *attribute = element->FirstAttribute();
      attribute;
      attribute = attribute->Next())
  {
    const char *name  = attribute->Name(),
               *value = attribute->Value();

    if(name && value)
    switch(name[0])
    {
      case 'x': case 'X': case 'r': case 'R': case 's': case 'S':
        tuple.x = atof(value);
      break;

      case 'y': case 'Y': case 'g': case 'G': case 't': case 'T':
        tuple.y = atof(value);
      break;

      case 'z': case 'Z': case 'b': case 'B': case 'u': case 'U':
        tuple.z = atof(value);
      break;
    }
  }
  return tuple;
}

Tuple2f &XMLArbiter::fillComponents2f(const TiXmlElement *element, Tuple2f &tuple)
{
  if(element)
  for(const TiXmlAttribute *attribute = element->FirstAttribute();
      attribute;
      attribute = attribute->Next())
  {
    const char *name  = attribute->Name(),
               *value = attribute->Value();

    if(name && value)
    switch(name[0])
    {
      case 'x': case 'X': case 'r': case 'R': case 's': case 'S':
        tuple.x = float(atof(value));
      break;

      case 'y': case 'Y': case 'g': case 'G': case 't': case 'T':
        tuple.y = float(atof(value));
      break;
    }
  }
  return tuple;
}

Tuple2i &XMLArbiter::fillComponents2i(const TiXmlElement *element, Tuple2i &tuple)
{
  if(element)
  for(const TiXmlAttribute *attribute = element->FirstAttribute();
      attribute;
      attribute = attribute->Next())
  {
    const char *name  = attribute->Name(),
               *value = attribute->Value();

    if(name && value)
    switch(name[0])
    {
      case 'x': case 'X': case 'r': case 'R': case 's': case 'S':
        tuple.x = atoi(value);
      break;

      case 'y': case 'Y': case 'g': case 'G': case 't': case 'T':
        tuple.y = atoi(value);
      break;
    }
  }
  return tuple;
}

Tuple2d &XMLArbiter::fillComponents2d(const TiXmlElement *element, Tuple2d &tuple)
{
  if(element)
  for(const TiXmlAttribute *attribute = element->FirstAttribute();
      attribute;
      attribute = attribute->Next())
  {
    const char *name  = attribute->Name(),
               *value = attribute->Value();

    if(name && value)
    switch(name[0])
    {
      case 'x': case 'X': case 'r': case 'R': case 's': case 'S':
        tuple.x = atof(value);
      break;

      case 'y': case 'Y': case 'g': case 'G': case 't': case 'T':
        tuple.y = atof(value);
      break;
    }
  }
  return tuple;
}


double  XMLArbiter::fillComponents1d(const TiXmlElement *element,
                                     const char         *attr,
                                     double              valueArg)
{
  double value = valueArg;

  if(element && attr)
  if(element->Attribute(attr, &value))
    return value;

  return valueArg;
}

float   XMLArbiter::fillComponents1f(const TiXmlElement *element,
                                     const char         *attr,
                                     float               valueArg)
{
  double value = valueArg;

  if(element && attr)
  if(element->Attribute(attr, &value))
    return float(value);

  return valueArg;
}

int     XMLArbiter::fillComponents1i(const TiXmlElement *element,
                                     const char         *attr,
                                     int                 valueArg)
{
  int value = valueArg;

  if(element && attr)
  if(element->Attribute(attr, &value))
    return value;

  return valueArg;
}


bool XMLArbiter::analyzeBooleanAttr(const TiXmlElement *element,
                                    const char         *attr,
                                    bool                source)
{
  if(element && attr)
  for(const TiXmlAttribute *attribute = element->FirstAttribute();
      attribute;
      attribute = attribute->Next())
  {
    const char *name  = attribute->Name(),
               *value = attribute->Value();

    if(name && !strcmp(name, attr) && value)
    {
      source = !strcmp(value, "true");
      break;
    }
  }
  return source;
}

const TiXmlElement *XMLArbiter::getChildElementByName(const TiXmlElement *element,
                                                      const char         *name)
{
  if(element && name)
  for(const TiXmlElement *child = element->FirstChildElement();
      child;
   	  child = child->NextSiblingElement() )
  {
    const char *value = child->Value();
    if(value && !strcmp(name, value))
      return child;
  }
  return NULL;
}

bool XMLArbiter::inspectElementInfo(const TiXmlElement *element,
                                    const char         *desiredType)
{
  if(!element || !desiredType || !element->Value() || strcmp(element->Value(), desiredType))
    return false;

  return true;
}

/*
www.sourceforge.net/projects/tinyxml
Original code (2.0 and earlier )copyright (c) 2000-2002 Lee Thomason (www.grinninglizard.com)

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any
damages arising from the use of this software.

Permission is granted to anyone to use this software for any
purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must
not claim that you wrote the original software. If you use this
software in a product, an acknowledgment in the product documentation
would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and
must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#include <ctype.h>

#ifdef TIXML_USE_STL
#include <sstream>
#endif


bool TiXmlBase::condenseWhiteSpace = true;

void TiXmlBase::PutString( const TIXML_STRING& str, TIXML_OSTREAM* stream )
{
	TIXML_STRING buffer;
	PutString( str, &buffer );
	(*stream) << buffer;
}

void TiXmlBase::PutString( const TIXML_STRING& str, TIXML_STRING* outString )
{
	int i=0;

	while( i<(int)str.length() )
	{
		unsigned char c = (unsigned char) str[i];

		if (    c == '&'
		     && i < ( (int)str.length() - 2 )
			 && str[i+1] == '#'
			 && str[i+2] == 'x' )
		{
			// Hexadecimal character reference.
			// Pass through unchanged.
			// &#xA9;	-- copyright symbol, for example.
			//
			// The -1 is a bug fix from Rob Laveaux. It keeps
			// an overflow from happening if there is no ';'.
			// There are actually 2 ways to exit this loop -
			// while fails (error case) and break (semicolon found).
			// However, there is no mechanism (currently) for
			// this function to return an error.
			while ( i<(int)str.length()-1 )
			{
				outString->append( str.c_str() + i, 1 );
				++i;
				if ( str[i] == ';' )
					break;
			}
		}
		else if ( c == '&' )
		{
			outString->append( entity[0].str, entity[0].strLength );
			++i;
		}
		else if ( c == '<' )
		{
			outString->append( entity[1].str, entity[1].strLength );
			++i;
		}
		else if ( c == '>' )
		{
			outString->append( entity[2].str, entity[2].strLength );
			++i;
		}
		else if ( c == '\"' )
		{
			outString->append( entity[3].str, entity[3].strLength );
			++i;
		}
		else if ( c == '\'' )
		{
			outString->append( entity[4].str, entity[4].strLength );
			++i;
		}
		else if ( c < 32 )
		{
			// Easy pass at non-alpha/numeric/symbol
			// Below 32 is symbolic.
			char buf[ 32 ];
			sprintf( buf, "&#x%02X;", (unsigned) ( c & 0xff ) );
			//*ME:	warning C4267: convert 'size_t' to 'int'
			//*ME:	Int-Cast to make compiler happy ...
			outString->append( buf, (int)strlen( buf ) );
			++i;
		}
		else
		{
			//char realc = (char) c;
			//outString->append( &realc, 1 );
			*outString += (char) c;	// somewhat more efficient function call.
			++i;
		}
	}
}


// <-- Strange class for a bug fix. Search for STL_STRING_BUG
TiXmlBase::StringToBuffer::StringToBuffer( const TIXML_STRING& str )
{
	buffer = new char[ str.length()+1 ];
	if ( buffer )
	{
		strcpy( buffer, str.c_str() );
	}
}


TiXmlBase::StringToBuffer::~StringToBuffer()
{
	delete [] buffer;
}
// End strange bug fix. -->


TiXmlNode::TiXmlNode( NodeType _type ) : TiXmlBase()
{
	parent = 0;
	type = _type;
	firstChild = 0;
	lastChild = 0;
	prev = 0;
	next = 0;
}


TiXmlNode::~TiXmlNode()
{
	TiXmlNode* node = firstChild;
	TiXmlNode* temp = 0;

	while ( node )
	{
		temp = node;
		node = node->next;
		delete temp;
	}
}


void TiXmlNode::CopyTo( TiXmlNode* target ) const
{
	target->SetValue (value.c_str() );
	target->userData = userData;
}


void TiXmlNode::Clear()
{
	TiXmlNode* node = firstChild;
	TiXmlNode* temp = 0;

	while ( node )
	{
		temp = node;
		node = node->next;
		delete temp;
	}

	firstChild = 0;
	lastChild = 0;
}


TiXmlNode* TiXmlNode::LinkEndChild( TiXmlNode* node )
{
	node->parent = this;

	node->prev = lastChild;
	node->next = 0;

	if ( lastChild )
		lastChild->next = node;
	else
		firstChild = node;			// it was an empty list.

	lastChild = node;
	return node;
}


TiXmlNode* TiXmlNode::InsertEndChild( const TiXmlNode& addThis )
{
	TiXmlNode* node = addThis.Clone();
	if ( !node )
		return 0;

	return LinkEndChild( node );
}


TiXmlNode* TiXmlNode::InsertBeforeChild( TiXmlNode* beforeThis, const TiXmlNode& addThis )
{
	if ( !beforeThis || beforeThis->parent != this )
		return 0;

	TiXmlNode* node = addThis.Clone();
	if ( !node )
		return 0;
	node->parent = this;

	node->next = beforeThis;
	node->prev = beforeThis->prev;
	if ( beforeThis->prev )
	{
		beforeThis->prev->next = node;
	}
	else
	{
		assert( firstChild == beforeThis );
		firstChild = node;
	}
	beforeThis->prev = node;
	return node;
}


TiXmlNode* TiXmlNode::InsertAfterChild( TiXmlNode* afterThis, const TiXmlNode& addThis )
{
	if ( !afterThis || afterThis->parent != this )
		return 0;

	TiXmlNode* node = addThis.Clone();
	if ( !node )
		return 0;
	node->parent = this;

	node->prev = afterThis;
	node->next = afterThis->next;
	if ( afterThis->next )
	{
		afterThis->next->prev = node;
	}
	else
	{
		assert( lastChild == afterThis );
		lastChild = node;
	}
	afterThis->next = node;
	return node;
}


TiXmlNode* TiXmlNode::ReplaceChild( TiXmlNode* replaceThis, const TiXmlNode& withThis )
{
	if ( replaceThis->parent != this )
		return 0;

	TiXmlNode* node = withThis.Clone();
	if ( !node )
		return 0;

	node->next = replaceThis->next;
	node->prev = replaceThis->prev;

	if ( replaceThis->next )
		replaceThis->next->prev = node;
	else
		lastChild = node;

	if ( replaceThis->prev )
		replaceThis->prev->next = node;
	else
		firstChild = node;

	delete replaceThis;
	node->parent = this;
	return node;
}


bool TiXmlNode::RemoveChild( TiXmlNode* removeThis )
{
	if ( removeThis->parent != this )
	{
		assert( 0 );
		return false;
	}

	if ( removeThis->next )
		removeThis->next->prev = removeThis->prev;
	else
		lastChild = removeThis->prev;

	if ( removeThis->prev )
		removeThis->prev->next = removeThis->next;
	else
		firstChild = removeThis->next;

	delete removeThis;
	return true;
}

const TiXmlNode* TiXmlNode::FirstChild( const char * _value ) const
{
	const TiXmlNode* node;
	for ( node = firstChild; node; node = node->next )
	{
		if ( node->SValue() == _value )
			return node;
	}
	return 0;
}


TiXmlNode* TiXmlNode::FirstChild( const char * _value )
{
	TiXmlNode* node;
	for ( node = firstChild; node; node = node->next )
	{
		if ( node->SValue() == _value )
			return node;
	}
	return 0;
}


const TiXmlNode* TiXmlNode::LastChild( const char * _value ) const
{
	const TiXmlNode* node;
	for ( node = lastChild; node; node = node->prev )
	{
		if ( node->SValue() == _value )
			return node;
	}
	return 0;
}

TiXmlNode* TiXmlNode::LastChild( const char * _value )
{
	TiXmlNode* node;
	for ( node = lastChild; node; node = node->prev )
	{
		if ( node->SValue() == _value )
			return node;
	}
	return 0;
}

const TiXmlNode* TiXmlNode::IterateChildren( const TiXmlNode* previous ) const
{
	if ( !previous )
	{
		return FirstChild();
	}
	else
	{
		assert( previous->parent == this );
		return previous->NextSibling();
	}
}

TiXmlNode* TiXmlNode::IterateChildren( TiXmlNode* previous )
{
	if ( !previous )
	{
		return FirstChild();
	}
	else
	{
		assert( previous->parent == this );
		return previous->NextSibling();
	}
}

const TiXmlNode* TiXmlNode::IterateChildren( const char * val, const TiXmlNode* previous ) const
{
	if ( !previous )
	{
		return FirstChild( val );
	}
	else
	{
		assert( previous->parent == this );
		return previous->NextSibling( val );
	}
}

TiXmlNode* TiXmlNode::IterateChildren( const char * val, TiXmlNode* previous )
{
	if ( !previous )
	{
		return FirstChild( val );
	}
	else
	{
		assert( previous->parent == this );
		return previous->NextSibling( val );
	}
}

const TiXmlNode* TiXmlNode::NextSibling( const char * _value ) const
{
	const TiXmlNode* node;
	for ( node = next; node; node = node->next )
	{
		if ( node->SValue() == _value )
			return node;
	}
	return 0;
}

TiXmlNode* TiXmlNode::NextSibling( const char * _value )
{
	TiXmlNode* node;
	for ( node = next; node; node = node->next )
	{
		if ( node->SValue() == _value )
			return node;
	}
	return 0;
}

const TiXmlNode* TiXmlNode::PreviousSibling( const char * _value ) const
{
	const TiXmlNode* node;
	for ( node = prev; node; node = node->prev )
	{
		if ( node->SValue() == _value )
			return node;
	}
	return 0;
}

TiXmlNode* TiXmlNode::PreviousSibling( const char * _value )
{
	TiXmlNode* node;
	for ( node = prev; node; node = node->prev )
	{
		if ( node->SValue() == _value )
			return node;
	}
	return 0;
}

void TiXmlElement::RemoveAttribute( const char * name )
{
	TiXmlAttribute* node = attributeSet.Find( name );
	if ( node )
	{
		attributeSet.Remove( node );
		delete node;
	}
}

const TiXmlElement* TiXmlNode::FirstChildElement() const
{
	const TiXmlNode* node;

	for (	node = FirstChild();
			node;
			node = node->NextSibling() )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}

TiXmlElement* TiXmlNode::FirstChildElement()
{
	TiXmlNode* node;

	for (	node = FirstChild();
			node;
			node = node->NextSibling() )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}

const TiXmlElement* TiXmlNode::FirstChildElement( const char * _value ) const
{
	const TiXmlNode* node;

	for (	node = FirstChild( _value );
			node;
			node = node->NextSibling( _value ) )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}

TiXmlElement* TiXmlNode::FirstChildElement( const char * _value )
{
	TiXmlNode* node;

	for (	node = FirstChild( _value );
			node;
			node = node->NextSibling( _value ) )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}

const TiXmlElement* TiXmlNode::NextSiblingElement() const
{
	const TiXmlNode* node;

	for (	node = NextSibling();
	node;
	node = node->NextSibling() )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}

TiXmlElement* TiXmlNode::NextSiblingElement()
{
	TiXmlNode* node;

	for (	node = NextSibling();
	node;
	node = node->NextSibling() )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}

const TiXmlElement* TiXmlNode::NextSiblingElement( const char * _value ) const
{
	const TiXmlNode* node;

	for (	node = NextSibling( _value );
	node;
	node = node->NextSibling( _value ) )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}

TiXmlElement* TiXmlNode::NextSiblingElement( const char * _value )
{
	TiXmlNode* node;

	for (	node = NextSibling( _value );
	node;
	node = node->NextSibling( _value ) )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}


const TiXmlDocument* TiXmlNode::GetDocument() const
{
	const TiXmlNode* node;

	for( node = this; node; node = node->parent )
	{
		if ( node->ToDocument() )
			return node->ToDocument();
	}
	return 0;
}

TiXmlDocument* TiXmlNode::GetDocument()
{
	TiXmlNode* node;

	for( node = this; node; node = node->parent )
	{
		if ( node->ToDocument() )
			return node->ToDocument();
	}
	return 0;
}

TiXmlElement::TiXmlElement (const char * _value)
	: TiXmlNode( TiXmlNode::ELEMENT )
{
	firstChild = lastChild = 0;
	value = _value;
}


#ifdef TIXML_USE_STL
TiXmlElement::TiXmlElement( const std::string& _value )
	: TiXmlNode( TiXmlNode::ELEMENT )
{
	firstChild = lastChild = 0;
	value = _value;
}
#endif


TiXmlElement::TiXmlElement( const TiXmlElement& copy)
	: TiXmlNode( TiXmlNode::ELEMENT )
{
	firstChild = lastChild = 0;
	copy.CopyTo( this );
}


void TiXmlElement::operator=( const TiXmlElement& base )
{
	ClearThis();
	base.CopyTo( this );
}


TiXmlElement::~TiXmlElement()
{
	ClearThis();
}


void TiXmlElement::ClearThis()
{
	Clear();
	while( attributeSet.First() )
	{
		TiXmlAttribute* node = attributeSet.First();
		attributeSet.Remove( node );
		delete node;
	}
}


const char * TiXmlElement::Attribute( const char * name ) const
{
	const TiXmlAttribute* node = attributeSet.Find( name );

	if ( node )
		return node->Value();

	return 0;
}


const char * TiXmlElement::Attribute( const char * name, int* i ) const
{
	const char * s = Attribute( name );
	if ( i )
	{
		if ( s )
			*i = atoi( s );
		else
			*i = 0;
	}
	return s;
}


const char * TiXmlElement::Attribute( const char * name, double* d ) const
{
	const char * s = Attribute( name );
	if ( d )
	{
		if ( s )
			*d = atof( s );
		else
			*d = 0;
	}
	return s;
}


int TiXmlElement::QueryIntAttribute( const char* name, int* ival ) const
{
	const TiXmlAttribute* node = attributeSet.Find( name );
	if ( !node )
		return TIXML_NO_ATTRIBUTE;

	return node->QueryIntValue( ival );
}


int TiXmlElement::QueryDoubleAttribute( const char* name, double* dval ) const
{
	const TiXmlAttribute* node = attributeSet.Find( name );
	if ( !node )
		return TIXML_NO_ATTRIBUTE;

	return node->QueryDoubleValue( dval );
}


void TiXmlElement::SetAttribute( const char * name, int val )
{
	char buf[64];
	sprintf( buf, "%d", val );
	SetAttribute( name, buf );
}


void TiXmlElement::SetDoubleAttribute( const char * name, double val )
{
	char buf[256];
	sprintf( buf, "%f", val );
	SetAttribute( name, buf );
}


void TiXmlElement::SetAttribute( const char * name, const char * _value )
{
	TiXmlAttribute* node = attributeSet.Find( name );
	if ( node )
	{
		node->SetValue( _value );
		return;
	}

	TiXmlAttribute* attrib = new TiXmlAttribute( name, _value );
	if ( attrib )
	{
		attributeSet.Add( attrib );
	}
	else
	{
		TiXmlDocument* document = GetDocument();
		if ( document ) document->SetError( TIXML_ERROR_OUT_OF_MEMORY, 0, 0, TIXML_ENCODING_UNKNOWN );
	}
}

void TiXmlElement::Print( FILE* cfile, int depth ) const
{
	int i;
	for ( i=0; i<depth; i++ )
	{
		fprintf( cfile, "    " );
	}

	fprintf( cfile, "<%s", value.c_str() );

	const TiXmlAttribute* attrib;
	for ( attrib = attributeSet.First(); attrib; attrib = attrib->Next() )
	{
		fprintf( cfile, " " );
		attrib->Print( cfile, depth );
	}

	// There are 3 different formatting approaches:
	// 1) An element without children is printed as a <foo /> node
	// 2) An element with only a text child is printed as <foo> text </foo>
	// 3) An element with children is printed on multiple lines.
	TiXmlNode* node;
	if ( !firstChild )
	{
		fprintf( cfile, " />" );
	}
	else if ( firstChild == lastChild && firstChild->ToText() )
	{
		fprintf( cfile, ">" );
		firstChild->Print( cfile, depth + 1 );
		fprintf( cfile, "</%s>", value.c_str() );
	}
	else
	{
		fprintf( cfile, ">" );

		for ( node = firstChild; node; node=node->NextSibling() )
		{
			if ( !node->ToText() )
			{
				fprintf( cfile, "\n" );
			}
			node->Print( cfile, depth+1 );
		}
		fprintf( cfile, "\n" );
		for( i=0; i<depth; ++i )
		fprintf( cfile, "    " );
		fprintf( cfile, "</%s>", value.c_str() );
	}
}

void TiXmlElement::StreamOut( TIXML_OSTREAM * stream ) const
{
	(*stream) << "<" << value;

	const TiXmlAttribute* attrib;
	for ( attrib = attributeSet.First(); attrib; attrib = attrib->Next() )
	{
		(*stream) << " ";
		attrib->StreamOut( stream );
	}

	// If this node has children, give it a closing tag. Else
	// make it an empty tag.
	TiXmlNode* node;
	if ( firstChild )
	{
		(*stream) << ">";

		for ( node = firstChild; node; node=node->NextSibling() )
		{
			node->StreamOut( stream );
		}
		(*stream) << "</" << value << ">";
	}
	else
	{
		(*stream) << " />";
	}
}


void TiXmlElement::CopyTo( TiXmlElement* target ) const
{
	// superclass:
	TiXmlNode::CopyTo( target );

	// Element class:
	// Clone the attributes, then clone the children.
	const TiXmlAttribute* attribute = 0;
	for(	attribute = attributeSet.First();
	attribute;
	attribute = attribute->Next() )
	{
		target->SetAttribute( attribute->Name(), attribute->Value() );
	}

	TiXmlNode* node = 0;
	for ( node = firstChild; node; node = node->NextSibling() )
	{
		target->LinkEndChild( node->Clone() );
	}
}


TiXmlNode* TiXmlElement::Clone() const
{
	TiXmlElement* clone = new TiXmlElement( Value() );
	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


TiXmlDocument::TiXmlDocument() : TiXmlNode( TiXmlNode::DOCUMENT )
{
	tabsize = 4;
	ClearError();
}

TiXmlDocument::TiXmlDocument( const char * documentName ) : TiXmlNode( TiXmlNode::DOCUMENT )
{
	tabsize = 4;
	value = documentName;
	ClearError();
}


#ifdef TIXML_USE_STL
TiXmlDocument::TiXmlDocument( const std::string& documentName ) : TiXmlNode( TiXmlNode::DOCUMENT )
{
	tabsize = 4;
    value = documentName;
	ClearError();
}
#endif


TiXmlDocument::TiXmlDocument( const TiXmlDocument& copy ) : TiXmlNode( TiXmlNode::DOCUMENT )
{
	copy.CopyTo( this );
}


void TiXmlDocument::operator=( const TiXmlDocument& copy )
{
	Clear();
	copy.CopyTo( this );
}


bool TiXmlDocument::LoadFile( TiXmlEncoding encoding )
{
	// See STL_STRING_BUG below.
	StringToBuffer buf( value );

	if ( buf.buffer && LoadFile( buf.buffer, encoding ) )
		return true;

	return false;
}


bool TiXmlDocument::SaveFile() const
{
	// See STL_STRING_BUG below.
	StringToBuffer buf( value );

	if ( buf.buffer && SaveFile( buf.buffer ) )
		return true;

	return false;
}

bool TiXmlDocument::LoadFile( const char* filename, TiXmlEncoding encoding )
{
	// Delete the existing data:
	Clear();
	location.Clear();

	// There was a really terrifying little bug here. The code:
	//		value = filename
	// in the STL case, cause the assignment method of the std::string to
	// be called. What is strange, is that the std::string had the same
	// address as it's c_str() method, and so bad things happen. Looks
	// like a bug in the Microsoft STL implementation.
	// See STL_STRING_BUG above.
	// Fixed with the StringToBuffer class.
	value = filename;

	FILE* file = fopen( value.c_str (), "r" );

	if ( file )
	{
		// Get the file size, so we can pre-allocate the string. HUGE speed impact.
		long length = 0;
		fseek( file, 0, SEEK_END );
		length = ftell( file );
		fseek( file, 0, SEEK_SET );

		// Strange case, but good to handle up front.
		if ( length == 0 )
		{
			fclose( file );
			return false;
		}

		// If we have a file, assume it is all one big XML file, and read it in.
		// The document parser may decide the document ends sooner than the entire file, however.
		TIXML_STRING data;
		data.reserve( length );

		const int BUF_SIZE = 2048;
		char buf[BUF_SIZE];

		while( fgets( buf, BUF_SIZE, file ) )
		{
			data += buf;
		}
		fclose( file );

		Parse( data.c_str(), 0, encoding );

		if (  Error() )
            return false;
        else
			return true;
	}
	SetError( TIXML_ERROR_OPENING_FILE, 0, 0, TIXML_ENCODING_UNKNOWN );
	return false;
}

bool TiXmlDocument::SaveFile( const char * filename ) const
{
	// The old c stuff lives on...
	FILE* fp = fopen( filename, "w" );
	if ( fp )
	{
		Print( fp, 0 );
		fclose( fp );
		return true;
	}
	return false;
}


void TiXmlDocument::CopyTo( TiXmlDocument* target ) const
{
	TiXmlNode::CopyTo( target );

	target->error = error;
	target->errorDesc = errorDesc.c_str ();

	TiXmlNode* node = 0;
	for ( node = firstChild; node; node = node->NextSibling() )
	{
		target->LinkEndChild( node->Clone() );
	}
}


TiXmlNode* TiXmlDocument::Clone() const
{
	TiXmlDocument* clone = new TiXmlDocument();
	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


void TiXmlDocument::Print( FILE* cfile, int depth ) const
{
	const TiXmlNode* node;
	for ( node=FirstChild(); node; node=node->NextSibling() )
	{
		node->Print( cfile, depth );
		fprintf( cfile, "\n" );
	}
}

void TiXmlDocument::StreamOut( TIXML_OSTREAM * out ) const
{
	const TiXmlNode* node;
	for ( node=FirstChild(); node; node=node->NextSibling() )
	{
		node->StreamOut( out );

		// Special rule for streams: stop after the root element.
		// The stream in code will only read one element, so don't
		// write more than one.
		if ( node->ToElement() )
			break;
	}
}


const TiXmlAttribute* TiXmlAttribute::Next() const
{
	// We are using knowledge of the sentinel. The sentinel
	// have a value or name.
	if ( next->value.empty() && next->name.empty() )
		return 0;
	return next;
}

TiXmlAttribute* TiXmlAttribute::Next()
{
	// We are using knowledge of the sentinel. The sentinel
	// have a value or name.
	if ( next->value.empty() && next->name.empty() )
		return 0;
	return next;
}

const TiXmlAttribute* TiXmlAttribute::Previous() const
{
	// We are using knowledge of the sentinel. The sentinel
	// have a value or name.
	if ( prev->value.empty() && prev->name.empty() )
		return 0;
	return prev;
}

TiXmlAttribute* TiXmlAttribute::Previous()
{
	// We are using knowledge of the sentinel. The sentinel
	// have a value or name.
	if ( prev->value.empty() && prev->name.empty() )
		return 0;
	return prev;
}

void TiXmlAttribute::Print( FILE* cfile, int /*depth*/ ) const
{
	TIXML_STRING n, v;

	PutString( name, &n );
	PutString( value, &v );

	if (value.find ('\"') == TIXML_STRING::npos)
		fprintf (cfile, "%s=\"%s\"", n.c_str(), v.c_str() );
	else
		fprintf (cfile, "%s='%s'", n.c_str(), v.c_str() );
}


void TiXmlAttribute::StreamOut( TIXML_OSTREAM * stream ) const
{
	if (value.find( '\"' ) != TIXML_STRING::npos)
	{
		PutString( name, stream );
		(*stream) << "=" << "'";
		PutString( value, stream );
		(*stream) << "'";
	}
	else
	{
		PutString( name, stream );
		(*stream) << "=" << "\"";
		PutString( value, stream );
		(*stream) << "\"";
	}
}

int TiXmlAttribute::QueryIntValue( int* ival ) const
{
	if ( sscanf( value.c_str(), "%d", ival ) == 1 )
		return TIXML_SUCCESS;
	return TIXML_WRONG_TYPE;
}

int TiXmlAttribute::QueryDoubleValue( double* dval ) const
{
	if ( sscanf( value.c_str(), "%lf", dval ) == 1 )
		return TIXML_SUCCESS;
	return TIXML_WRONG_TYPE;
}

void TiXmlAttribute::SetIntValue( int _value )
{
	char buf [64];
	sprintf (buf, "%d", _value);
	SetValue (buf);
}

void TiXmlAttribute::SetDoubleValue( double _value )
{
	char buf [256];
	sprintf (buf, "%lf", _value);
	SetValue (buf);
}

const int TiXmlAttribute::IntValue() const
{
	return atoi (value.c_str ());
}

const double  TiXmlAttribute::DoubleValue() const
{
	return atof (value.c_str ());
}


TiXmlComment::TiXmlComment( const TiXmlComment& copy ) : TiXmlNode( TiXmlNode::COMMENT )
{
	copy.CopyTo( this );
}


void TiXmlComment::operator=( const TiXmlComment& base )
{
	Clear();
	base.CopyTo( this );
}


void TiXmlComment::Print( FILE* cfile, int depth ) const
{
	for ( int i=0; i<depth; i++ )
	{
		fputs( "    ", cfile );
	}
	fprintf( cfile, "<!--%s-->", value.c_str() );
}

void TiXmlComment::StreamOut( TIXML_OSTREAM * stream ) const
{
	(*stream) << "<!--";
	//PutString( value, stream );
	(*stream) << value;
	(*stream) << "-->";
}


void TiXmlComment::CopyTo( TiXmlComment* target ) const
{
	TiXmlNode::CopyTo( target );
}


TiXmlNode* TiXmlComment::Clone() const
{
	TiXmlComment* clone = new TiXmlComment();

	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


void TiXmlText::Print( FILE* cfile, int /*depth*/ ) const
{
	TIXML_STRING buffer;
	PutString( value, &buffer );
	fprintf( cfile, "%s", buffer.c_str() );
}


void TiXmlText::StreamOut( TIXML_OSTREAM * stream ) const
{
	PutString( value, stream );
}


void TiXmlText::CopyTo( TiXmlText* target ) const
{
	TiXmlNode::CopyTo( target );
}


TiXmlNode* TiXmlText::Clone() const
{
	TiXmlText* clone = 0;
	clone = new TiXmlText( "" );

	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


TiXmlDeclaration::TiXmlDeclaration( const char * _version,
									const char * _encoding,
									const char * _standalone )
	: TiXmlNode( TiXmlNode::DECLARATION )
{
	version = _version;
	encoding = _encoding;
	standalone = _standalone;
}


#ifdef TIXML_USE_STL
TiXmlDeclaration::TiXmlDeclaration(	const std::string& _version,
									const std::string& _encoding,
									const std::string& _standalone )
	: TiXmlNode( TiXmlNode::DECLARATION )
{
	version = _version;
	encoding = _encoding;
	standalone = _standalone;
}
#endif


TiXmlDeclaration::TiXmlDeclaration( const TiXmlDeclaration& copy )
	: TiXmlNode( TiXmlNode::DECLARATION )
{
	copy.CopyTo( this );
}


void TiXmlDeclaration::operator=( const TiXmlDeclaration& copy )
{
	Clear();
	copy.CopyTo( this );
}


void TiXmlDeclaration::Print( FILE* cfile, int /*depth*/ ) const
{
	fprintf (cfile, "<?xml ");

	if ( !version.empty() )
		fprintf (cfile, "version=\"%s\" ", version.c_str ());
	if ( !encoding.empty() )
		fprintf (cfile, "encoding=\"%s\" ", encoding.c_str ());
	if ( !standalone.empty() )
		fprintf (cfile, "standalone=\"%s\" ", standalone.c_str ());
	fprintf (cfile, "?>");
}

void TiXmlDeclaration::StreamOut( TIXML_OSTREAM * stream ) const
{
	(*stream) << "<?xml ";

	if ( !version.empty() )
	{
		(*stream) << "version=\"";
		PutString( version, stream );
		(*stream) << "\" ";
	}
	if ( !encoding.empty() )
	{
		(*stream) << "encoding=\"";
		PutString( encoding, stream );
		(*stream ) << "\" ";
	}
	if ( !standalone.empty() )
	{
		(*stream) << "standalone=\"";
		PutString( standalone, stream );
		(*stream) << "\" ";
	}
	(*stream) << "?>";
}


void TiXmlDeclaration::CopyTo( TiXmlDeclaration* target ) const
{
	TiXmlNode::CopyTo( target );

	target->version = version;
	target->encoding = encoding;
	target->standalone = standalone;
}


TiXmlNode* TiXmlDeclaration::Clone() const
{
	TiXmlDeclaration* clone = new TiXmlDeclaration();

	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


void TiXmlUnknown::Print( FILE* cfile, int depth ) const
{
	for ( int i=0; i<depth; i++ )
		fprintf( cfile, "    " );
	fprintf( cfile, "<%s>", value.c_str() );
}


void TiXmlUnknown::StreamOut( TIXML_OSTREAM * stream ) const
{
	(*stream) << "<" << value << ">";		// Don't use entities here! It is unknown.
}


void TiXmlUnknown::CopyTo( TiXmlUnknown* target ) const
{
	TiXmlNode::CopyTo( target );
}


TiXmlNode* TiXmlUnknown::Clone() const
{
	TiXmlUnknown* clone = new TiXmlUnknown();

	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


TiXmlAttributeSet::TiXmlAttributeSet()
{
	sentinel.next = &sentinel;
	sentinel.prev = &sentinel;
}


TiXmlAttributeSet::~TiXmlAttributeSet()
{
	assert( sentinel.next == &sentinel );
	assert( sentinel.prev == &sentinel );
}


void TiXmlAttributeSet::Add( TiXmlAttribute* addMe )
{
	assert( !Find( addMe->Name() ) );	// Shouldn't be multiply adding to the set.

	addMe->next = &sentinel;
	addMe->prev = sentinel.prev;

	sentinel.prev->next = addMe;
	sentinel.prev      = addMe;
}

void TiXmlAttributeSet::Remove( TiXmlAttribute* removeMe )
{
	TiXmlAttribute* node;

	for( node = sentinel.next; node != &sentinel; node = node->next )
	{
		if ( node == removeMe )
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
			node->next = 0;
			node->prev = 0;
			return;
		}
	}
	assert( 0 );		// we tried to remove a non-linked attribute.
}

const TiXmlAttribute* TiXmlAttributeSet::Find( const char * name ) const
{
	const TiXmlAttribute* node;

	for( node = sentinel.next; node != &sentinel; node = node->next )
	{
		if ( node->name == name )
			return node;
	}
	return 0;
}

TiXmlAttribute*	TiXmlAttributeSet::Find( const char * name )
{
	TiXmlAttribute* node;

	for( node = sentinel.next; node != &sentinel; node = node->next )
	{
		if ( node->name == name )
			return node;
	}
	return 0;
}

#ifdef TIXML_USE_STL
TIXML_ISTREAM & operator >> (TIXML_ISTREAM & in, TiXmlNode & base)
{
	TIXML_STRING tag;
	tag.reserve( 8 * 1000 );
	base.StreamIn( &in, &tag );

	base.Parse( tag.c_str(), 0, TIXML_DEFAULT_ENCODING );
	return in;
}
#endif


TIXML_OSTREAM & operator<< (TIXML_OSTREAM & out, const TiXmlNode & base)
{
	base.StreamOut (& out);
	return out;
}


#ifdef TIXML_USE_STL
std::string & operator<< (std::string& out, const TiXmlNode& base )
{
   std::ostringstream os_stream( std::ostringstream::out );
   base.StreamOut( &os_stream );

   out.append( os_stream.str() );
   return out;
}
#endif


TiXmlHandle TiXmlHandle::FirstChild() const
{
	if ( node )
	{
		TiXmlNode* child = node->FirstChild();
		if ( child )
			return TiXmlHandle( child );
	}
	return TiXmlHandle( 0 );
}


TiXmlHandle TiXmlHandle::FirstChild( const char * value ) const
{
	if ( node )
	{
		TiXmlNode* child = node->FirstChild( value );
		if ( child )
			return TiXmlHandle( child );
	}
	return TiXmlHandle( 0 );
}


TiXmlHandle TiXmlHandle::FirstChildElement() const
{
	if ( node )
	{
		TiXmlElement* child = node->FirstChildElement();
		if ( child )
			return TiXmlHandle( child );
	}
	return TiXmlHandle( 0 );
}


TiXmlHandle TiXmlHandle::FirstChildElement( const char * value ) const
{
	if ( node )
	{
		TiXmlElement* child = node->FirstChildElement( value );
		if ( child )
			return TiXmlHandle( child );
	}
	return TiXmlHandle( 0 );
}


TiXmlHandle TiXmlHandle::Child( int count ) const
{
	if ( node )
	{
		int i;
		TiXmlNode* child = node->FirstChild();
		for (	i=0;
				child && i<count;
				child = child->NextSibling(), ++i )
		{
			// nothing
		}
		if ( child )
			return TiXmlHandle( child );
	}
	return TiXmlHandle( 0 );
}


TiXmlHandle TiXmlHandle::Child( const char* value, int count ) const
{
	if ( node )
	{
		int i;
		TiXmlNode* child = node->FirstChild( value );
		for (	i=0;
				child && i<count;
				child = child->NextSibling( value ), ++i )
		{
			// nothing
		}
		if ( child )
			return TiXmlHandle( child );
	}
	return TiXmlHandle( 0 );
}


TiXmlHandle TiXmlHandle::ChildElement( int count ) const
{
	if ( node )
	{
		int i;
		TiXmlElement* child = node->FirstChildElement();
		for (	i=0;
				child && i<count;
				child = child->NextSiblingElement(), ++i )
		{
			// nothing
		}
		if ( child )
			return TiXmlHandle( child );
	}
	return TiXmlHandle( 0 );
}


TiXmlHandle TiXmlHandle::ChildElement( const char* value, int count ) const
{
	if ( node )
	{
		int i;
		TiXmlElement* child = node->FirstChildElement( value );
		for (	i=0;
				child && i<count;
				child = child->NextSiblingElement( value ), ++i )
		{
			// nothing
		}
		if ( child )
			return TiXmlHandle( child );
	}
	return TiXmlHandle( 0 );
}

#include <stddef.h>

//#define DEBUG_PARSER

// Note tha "PutString" hardcodes the same list. This
// is less flexible than it appears. Changing the entries
// or order will break putstring.	
TiXmlBase::Entity TiXmlBase::entity[ NUM_ENTITY ] = 
{
	{ "&amp;",  5, '&' },
	{ "&lt;",   4, '<' },
	{ "&gt;",   4, '>' },
	{ "&quot;", 6, '\"' },
	{ "&apos;", 6, '\'' }
};

// Bunch of unicode info at:
//		http://www.unicode.org/faq/utf_bom.html
// Including the basic of this table, which determines the #bytes in the
// sequence from the lead byte. 1 placed for invalid sequences --
// although the result will be junk, pass it through as much as possible.
// Beware of the non-characters in UTF-8:	
//				ef bb bf (Microsoft "lead bytes")
//				ef bf be
//				ef bf bf 

const unsigned char TIXML_UTF_LEAD_0 = 0xefU;
const unsigned char TIXML_UTF_LEAD_1 = 0xbbU;
const unsigned char TIXML_UTF_LEAD_2 = 0xbfU;

const int TiXmlBase::utf8ByteTable[256] = 
{
	//	0	1	2	3	4	5	6	7	8	9	a	b	c	d	e	f
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x00
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x10
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x20
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x30
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x40
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x50
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x60
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x70	End of ASCII range
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x80 0x80 to 0xc1 invalid
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x90 
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0xa0 
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0xb0 
		1,	1,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	// 0xc0 0xc2 to 0xdf 2 byte
		2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	// 0xd0
		3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	// 0xe0 0xe0 to 0xef 3 byte
		4,	4,	4,	4,	4,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1	// 0xf0 0xf0 to 0xf4 4 byte, 0xf5 and higher invalid
};


void TiXmlBase::ConvertUTF32ToUTF8( unsigned long input, char* output, int* length )
{
	const unsigned long BYTE_MASK = 0xBF;
	const unsigned long BYTE_MARK = 0x80;
	const unsigned long FIRST_BYTE_MARK[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

	if (input < 0x80) 
		*length = 1;
	else if ( input < 0x800 )
		*length = 2;
	else if ( input < 0x10000 )
		*length = 3;
	else if ( input < 0x200000 )
		*length = 4;
	else
		{ *length = 0; return; }	// This code won't covert this correctly anyway.

	output += *length;

	// Scary scary fall throughs.
	switch (*length) 
	{
		case 4:
			--output; 
			*output = (char)((input | BYTE_MARK) & BYTE_MASK); 
			input >>= 6;
		case 3:
			--output; 
			*output = (char)((input | BYTE_MARK) & BYTE_MASK); 
			input >>= 6;
		case 2:
			--output; 
			*output = (char)((input | BYTE_MARK) & BYTE_MASK); 
			input >>= 6;
		case 1:
			--output; 
			*output = (char)(input | FIRST_BYTE_MARK[*length]);
	}
}


/*static*/ int TiXmlBase::IsAlpha( unsigned char anyByte, TiXmlEncoding /*encoding*/ )
{
	// This will only work for low-ascii, everything else is assumed to be a valid
	// letter. I'm not sure this is the best approach, but it is quite tricky trying
	// to figure out alhabetical vs. not across encoding. So take a very 
	// conservative approach.

//	if ( encoding == TIXML_ENCODING_UTF8 )
//	{
		if ( anyByte < 127 )
			return isalpha( anyByte );
		else
			return 1;	// What else to do? The unicode set is huge...get the english ones right.
//	}
//	else
//	{
//		return isalpha( anyByte );
//	}
}


/*static*/ int TiXmlBase::IsAlphaNum( unsigned char anyByte, TiXmlEncoding /*encoding*/ )
{
	// This will only work for low-ascii, everything else is assumed to be a valid
	// letter. I'm not sure this is the best approach, but it is quite tricky trying
	// to figure out alhabetical vs. not across encoding. So take a very 
	// conservative approach.

//	if ( encoding == TIXML_ENCODING_UTF8 )
//	{
		if ( anyByte < 127 )
			return isalnum( anyByte );
		else
			return 1;	// What else to do? The unicode set is huge...get the english ones right.
//	}
//	else
//	{
//		return isalnum( anyByte );
//	}
}


class TiXmlParsingData
{
	friend class TiXmlDocument;
  public:
	void Stamp( const char* now, TiXmlEncoding encoding );

	const TiXmlCursor& Cursor()	{ return cursor; }

  private:
	// Only used by the document!
	TiXmlParsingData( const char* start, int _tabsize, int row, int col )
	{
		assert( start );
		stamp = start;
		tabsize = _tabsize;
		cursor.row = row;
		cursor.col = col;
	}

	TiXmlCursor		cursor;
	const char*		stamp;
	int				tabsize;
};


void TiXmlParsingData::Stamp( const char* now, TiXmlEncoding encoding )
{
	assert( now );

	// Do nothing if the tabsize is 0.
	if ( tabsize < 1 )
	{
		return;
	}

	// Get the current row, column.
	int row = cursor.row;
	int col = cursor.col;
	const char* p = stamp;
	assert( p );

	while ( p < now )
	{
		// Treat p as unsigned, so we have a happy compiler.
		const unsigned char* pU = (const unsigned char*)p;

		// Code contributed by Fletcher Dunn: (modified by lee)
		switch (*pU) {
			case 0:
				// We *should* never get here, but in case we do, don't
				// advance past the terminating null character, ever
				return;

			case '\r':
				// bump down to the next line
				++row;
				col = 0;				
				// Eat the character
				++p;

				// Check for \r\n sequence, and treat this as a single character
				if (*p == '\n') {
					++p;
				}
				break;

			case '\n':
				// bump down to the next line
				++row;
				col = 0;

				// Eat the character
				++p;

				// Check for \n\r sequence, and treat this as a single
				// character.  (Yes, this bizarre thing does occur still
				// on some arcane platforms...)
				if (*p == '\r') {
					++p;
				}
				break;

			case '\t':
				// Eat the character
				++p;

				// Skip to next tab stop
				col = (col / tabsize + 1) * tabsize;
				break;

			case TIXML_UTF_LEAD_0:
				if ( encoding == TIXML_ENCODING_UTF8 )
				{
					if ( *(p+1) && *(p+2) )
					{
						// In these cases, don't advance the column. These are
						// 0-width spaces.
						if ( *(pU+1)==TIXML_UTF_LEAD_1 && *(pU+2)==TIXML_UTF_LEAD_2 )
							p += 3;	
						else if ( *(pU+1)==0xbfU && *(pU+2)==0xbeU )
							p += 3;	
						else if ( *(pU+1)==0xbfU && *(pU+2)==0xbfU )
							p += 3;	
						else
							{ p +=3; ++col; }	// A normal character.
					}
				}
				else
				{
					++p;
					++col;
				}
				break;

			default:
				if ( encoding == TIXML_ENCODING_UTF8 )
				{
					// Eat the 1 to 4 byte utf8 character.
					int step = TiXmlBase::utf8ByteTable[*((unsigned char*)p)];
					if ( step == 0 )
						step = 1;		// Error case from bad encoding, but handle gracefully.
					p += step;

					// Just advance one column, of course.
					++col;
				}
				else
				{
					++p;
					++col;
				}
				break;
		}
	}
	cursor.row = row;
	cursor.col = col;
	assert( cursor.row >= -1 );
	assert( cursor.col >= -1 );
	stamp = p;
	assert( stamp );
}


const char* TiXmlBase::SkipWhiteSpace( const char* p, TiXmlEncoding encoding )
{
	if ( !p || !*p )
	{
		return 0;
	}
	if ( encoding == TIXML_ENCODING_UTF8 )
	{
		while ( *p )
		{
			const unsigned char* pU = (const unsigned char*)p;
			
			// Skip the stupid Microsoft UTF-8 Byte order marks
			if (	*(pU+0)==TIXML_UTF_LEAD_0
				 && *(pU+1)==TIXML_UTF_LEAD_1 
				 && *(pU+2)==TIXML_UTF_LEAD_2 )
			{
				p += 3;
				continue;
			}
			else if(*(pU+0)==TIXML_UTF_LEAD_0
				 && *(pU+1)==0xbfU
				 && *(pU+2)==0xbeU )
			{
				p += 3;
				continue;
			}
			else if(*(pU+0)==TIXML_UTF_LEAD_0
				 && *(pU+1)==0xbfU
				 && *(pU+2)==0xbfU )
			{
				p += 3;
				continue;
			}

			if ( IsWhiteSpace( *p ) || *p == '\n' || *p =='\r' )		// Still using old rules for white space.
				++p;
			else
				break;
		}
	}
	else
	{
		while ( *p && IsWhiteSpace( *p ) || *p == '\n' || *p =='\r' )
			++p;
	}

	return p;
}

#ifdef TIXML_USE_STL
/*static*/ bool TiXmlBase::StreamWhiteSpace( TIXML_ISTREAM * in, TIXML_STRING * tag )
{
	for( ;; )
	{
		if ( !in->good() ) return false;

		int c = in->peek();
		// At this scope, we can't get to a document. So fail silently.
		if ( !IsWhiteSpace( c ) || c <= 0 )
			return true;

		*tag += (char) in->get();
	}
}

/*static*/ bool TiXmlBase::StreamTo( TIXML_ISTREAM * in, int character, TIXML_STRING * tag )
{
	//assert( character > 0 && character < 128 );	// else it won't work in utf-8
	while ( in->good() )
	{
		int c = in->peek();
		if ( c == character )
			return true;
		if ( c <= 0 )		// Silent failure: can't get document at this scope
			return false;

		in->get();
		*tag += (char) c;
	}
	return false;
}
#endif

const char* TiXmlBase::ReadName( const char* p, TIXML_STRING * name, TiXmlEncoding encoding )
{
	*name = "";
	assert( p );

	// Names start with letters or underscores.
	// Of course, in unicode, tinyxml has no idea what a letter *is*. The
	// algorithm is generous.
	//
	// After that, they can be letters, underscores, numbers,
	// hyphens, or colons. (Colons are valid ony for namespaces,
	// but tinyxml can't tell namespaces from names.)
	if (    p && *p 
		 && ( IsAlpha( (unsigned char) *p, encoding ) || *p == '_' ) )
	{
		while(		p && *p
				&&	(		IsAlphaNum( (unsigned char ) *p, encoding ) 
						 || *p == '_'
						 || *p == '-'
						 || *p == '.'
						 || *p == ':' ) )
		{
			(*name) += *p;
			++p;
		}
		return p;
	}
	return 0;
}

const char* TiXmlBase::GetEntity( const char* p, char* value, int* length, TiXmlEncoding encoding )
{
	// Presume an entity, and pull it out.
    TIXML_STRING ent;
	int i;
	*length = 0;

	if ( *(p+1) && *(p+1) == '#' && *(p+2) )
	{
		unsigned long ucs = 0;
		ptrdiff_t delta = 0;
		unsigned mult = 1;

		if ( *(p+2) == 'x' )
		{
			// Hexadecimal.
			if ( !*(p+3) ) return 0;

			const char* q = p+3;
			q = strchr( q, ';' );

			if ( !q || !*q ) return 0;

			delta = q-p;
			--q;

			while ( *q != 'x' )
			{
				if ( *q >= '0' && *q <= '9' )
					ucs += mult * (*q - '0');
				else if ( *q >= 'a' && *q <= 'f' )
					ucs += mult * (*q - 'a' + 10);
				else if ( *q >= 'A' && *q <= 'F' )
					ucs += mult * (*q - 'A' + 10 );
				else 
					return 0;
				mult *= 16;
				--q;
			}
		}
		else
		{
			// Decimal.
			if ( !*(p+2) ) return 0;

			const char* q = p+2;
			q = strchr( q, ';' );

			if ( !q || !*q ) return 0;

			delta = q-p;
			--q;

			while ( *q != '#' )
			{
				if ( *q >= '0' && *q <= '9' )
					ucs += mult * (*q - '0');
				else 
					return 0;
				mult *= 10;
				--q;
			}
		}
		if ( encoding == TIXML_ENCODING_UTF8 )
		{
			// convert the UCS to UTF-8
			ConvertUTF32ToUTF8( ucs, value, length );
		}
		else
		{
			*value = (char)ucs;
			*length = 1;
		}
		return p + delta + 1;
	}

	// Now try to match it.
	for( i=0; i<NUM_ENTITY; ++i )
	{
		if ( strncmp( entity[i].str, p, entity[i].strLength ) == 0 )
		{
			assert( strlen( entity[i].str ) == entity[i].strLength );
			*value = entity[i].chr;
			*length = 1;
			return ( p + entity[i].strLength );
		}
	}

	// So it wasn't an entity, its unrecognized, or something like that.
	*value = *p;	// Don't put back the last one, since we return it!
	return p+1;
}


bool TiXmlBase::StringEqual( const char* p,
							 const char* tag,
							 bool ignoreCase,
							 TiXmlEncoding encoding )
{
	assert( p );
	assert( tag );
	if ( !p || !*p )
	{
		assert( 0 );
		return false;
	}

	const char* q = p;

	if ( ignoreCase )
	{
		while ( *q && *tag && ToLower( *q, encoding ) == ToLower( *tag, encoding ) )
		{
			++q;
			++tag;
		}

		if ( *tag == 0 )
			return true;
	}
	else
	{
		while ( *q && *tag && *q == *tag )
		{
			++q;
			++tag;
		}

		if ( *tag == 0 )		// Have we found the end of the tag, and everything equal?
			return true;
	}
	return false;
}

const char* TiXmlBase::ReadText(	const char* p, 
									TIXML_STRING * text, 
									bool trimWhiteSpace, 
									const char* endTag, 
									bool caseInsensitive,
									TiXmlEncoding encoding )
{
    *text = "";
	if (    !trimWhiteSpace			// certain tags always keep whitespace
		 || !condenseWhiteSpace )	// if true, whitespace is always kept
	{
		// Keep all the white space.
		while (	   p && *p
				&& !StringEqual( p, endTag, caseInsensitive, encoding )
			  )
		{
			int len;
			char cArr[4] = { 0, 0, 0, 0 };
			p = GetChar( p, cArr, &len, encoding );
			text->append( cArr, len );
		}
	}
	else
	{
		bool whitespace = false;

		// Remove leading white space:
		p = SkipWhiteSpace( p, encoding );
		while (	   p && *p
				&& !StringEqual( p, endTag, caseInsensitive, encoding ) )
		{
			if ( *p == '\r' || *p == '\n' )
			{
				whitespace = true;
				++p;
			}
			else if ( IsWhiteSpace( *p ) )
			{
				whitespace = true;
				++p;
			}
			else
			{
				// If we've found whitespace, add it before the
				// new character. Any whitespace just becomes a space.
				if ( whitespace )
				{
					(*text) += ' ';
					whitespace = false;
				}
				int len;
				char cArr[4] = { 0, 0, 0, 0 };
				p = GetChar( p, cArr, &len, encoding );
				if ( len == 1 )
					(*text) += cArr[0];	// more efficient
				else
					text->append( cArr, len );
			}
		}
	}
	return p + strlen( endTag );
}

#ifdef TIXML_USE_STL

void TiXmlDocument::StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag )
{
	// The basic issue with a document is that we don't know what we're
	// streaming. Read something presumed to be a tag (and hope), then
	// identify it, and call the appropriate stream method on the tag.
	//
	// This "pre-streaming" will never read the closing ">" so the
	// sub-tag can orient itself.

	if ( !StreamTo( in, '<', tag ) ) 
	{
		SetError( TIXML_ERROR_PARSING_EMPTY, 0, 0, TIXML_ENCODING_UNKNOWN );
		return;
	}

	while ( in->good() )
	{
		int tagIndex = (int) tag->length();
		while ( in->good() && in->peek() != '>' )
		{
			int c = in->get();
			if ( c <= 0 )
			{
				SetError( TIXML_ERROR_EMBEDDED_NULL, 0, 0, TIXML_ENCODING_UNKNOWN );
				break;
			}
			(*tag) += (char) c;
		}

		if ( in->good() )
		{
			// We now have something we presume to be a node of 
			// some sort. Identify it, and call the node to
			// continue streaming.
			TiXmlNode* node = Identify( tag->c_str() + tagIndex, TIXML_DEFAULT_ENCODING );

			if ( node )
			{
				node->StreamIn( in, tag );
				bool isElement = node->ToElement() != 0;
				delete node;
				node = 0;

				// If this is the root element, we're done. Parsing will be
				// done by the >> operator.
				if ( isElement )
				{
					return;
				}
			}
			else
			{
				SetError( TIXML_ERROR, 0, 0, TIXML_ENCODING_UNKNOWN );
				return;
			}
		}
	}
	// We should have returned sooner.
	SetError( TIXML_ERROR, 0, 0, TIXML_ENCODING_UNKNOWN );
}

#endif

const char* TiXmlDocument::Parse( const char* p, TiXmlParsingData* prevData, TiXmlEncoding encoding )
{
	ClearError();

	// Parse away, at the document level. Since a document
	// contains nothing but other tags, most of what happens
	// here is skipping white space.
	if ( !p || !*p )
	{
		SetError( TIXML_ERROR_DOCUMENT_EMPTY, 0, 0, TIXML_ENCODING_UNKNOWN );
		return 0;
	}

	// Note that, for a document, this needs to come
	// before the while space skip, so that parsing
	// starts from the pointer we are given.
	location.Clear();
	if ( prevData )
	{
		location.row = prevData->cursor.row;
		location.col = prevData->cursor.col;
	}
	else
	{
		location.row = 0;
		location.col = 0;
	}
	TiXmlParsingData data( p, TabSize(), location.row, location.col );
	location = data.Cursor();

	if ( encoding == TIXML_ENCODING_UNKNOWN )
	{
		// Check for the Microsoft UTF-8 lead bytes.
		const unsigned char* pU = (const unsigned char*)p;
		if (	*(pU+0) && *(pU+0) == TIXML_UTF_LEAD_0
			 && *(pU+1) && *(pU+1) == TIXML_UTF_LEAD_1
			 && *(pU+2) && *(pU+2) == TIXML_UTF_LEAD_2 )
		{
			encoding = TIXML_ENCODING_UTF8;
		}
	}

    p = SkipWhiteSpace( p, encoding );
	if ( !p )
	{
		SetError( TIXML_ERROR_DOCUMENT_EMPTY, 0, 0, TIXML_ENCODING_UNKNOWN );
		return 0;
	}

	while ( p && *p )
	{
		TiXmlNode* node = Identify( p, encoding );
		if ( node )
		{
			p = node->Parse( p, &data, encoding );
			LinkEndChild( node );
		}
		else
		{
			break;
		}

		// Did we get encoding info?
		if (    encoding == TIXML_ENCODING_UNKNOWN
			 && node->ToDeclaration() )
		{
			TiXmlDeclaration* dec = node->ToDeclaration();
			const char* enc = dec->Encoding();
			assert( enc );

			if ( *enc == 0 )
				encoding = TIXML_ENCODING_UTF8;
			else if ( StringEqual( enc, "UTF-8", true, TIXML_ENCODING_UNKNOWN ) )
				encoding = TIXML_ENCODING_UTF8;
			else if ( StringEqual( enc, "UTF8", true, TIXML_ENCODING_UNKNOWN ) )
				encoding = TIXML_ENCODING_UTF8;	// incorrect, but be nice
			else 
				encoding = TIXML_ENCODING_LEGACY;
		}

		p = SkipWhiteSpace( p, encoding );
	}

	// Was this empty?
	if ( !firstChild ) {
		SetError( TIXML_ERROR_DOCUMENT_EMPTY, 0, 0, encoding );
		return 0;
	}

	// All is well.
	return p;
}

void TiXmlDocument::SetError( int err, const char* pError, TiXmlParsingData* data, TiXmlEncoding encoding )
{	
	// The first error in a chain is more accurate - don't set again!
	if ( error )
		return;

	assert( err > 0 && err < TIXML_ERROR_STRING_COUNT );
	error   = true;
	errorId = err;
	errorDesc = errorString[ errorId ];

	errorLocation.Clear();
	if ( pError && data )
	{
		//TiXmlParsingData data( pError, prevData );
		data->Stamp( pError, encoding );
		errorLocation = data->Cursor();
	}
}


TiXmlNode* TiXmlNode::Identify( const char* p, TiXmlEncoding encoding )
{
	TiXmlNode* returnNode = 0;

	p = SkipWhiteSpace( p, encoding );
	if( !p || !*p || *p != '<' )
	{
		return 0;
	}

	TiXmlDocument* doc = GetDocument();
	p = SkipWhiteSpace( p, encoding );

	if ( !p || !*p )
	{
		return 0;
	}

	// What is this thing? 
	// - Elements start with a letter or underscore, but xml is reserved.
	// - Comments: <!--
	// - Decleration: <?xml
	// - Everthing else is unknown to tinyxml.
	//

	const char* xmlHeader = { "<?xml" };
	const char* commentHeader = { "<!--" };
	const char* dtdHeader = { "<!" };

	if ( StringEqual( p, xmlHeader, true, encoding ) )
	{
		#ifdef DEBUG_PARSER
			TIXML_LOG( "XML parsing Declaration\n" );
		#endif
		returnNode = new TiXmlDeclaration();
	}
	else if ( StringEqual( p, commentHeader, false, encoding ) )
	{
		#ifdef DEBUG_PARSER
			TIXML_LOG( "XML parsing Comment\n" );
		#endif
		returnNode = new TiXmlComment();
	}
	else if ( StringEqual( p, dtdHeader, false, encoding ) )
	{
		#ifdef DEBUG_PARSER
			TIXML_LOG( "XML parsing Unknown(1)\n" );
		#endif
		returnNode = new TiXmlUnknown();
	}
	else if (    IsAlpha( *(p+1), encoding )
			  || *(p+1) == '_' )
	{
		#ifdef DEBUG_PARSER
			TIXML_LOG( "XML parsing Element\n" );
		#endif
		returnNode = new TiXmlElement( "" );
	}
	else
	{
		#ifdef DEBUG_PARSER
			TIXML_LOG( "XML parsing Unknown(2)\n" );
		#endif
		returnNode = new TiXmlUnknown();
	}

	if ( returnNode )
	{
		// Set the parent, so it can report errors
		returnNode->parent = this;
	}
	else
	{
		if ( doc )
			doc->SetError( TIXML_ERROR_OUT_OF_MEMORY, 0, 0, TIXML_ENCODING_UNKNOWN );
	}
	return returnNode;
}

#ifdef TIXML_USE_STL

void TiXmlElement::StreamIn (TIXML_ISTREAM * in, TIXML_STRING * tag)
{
	// We're called with some amount of pre-parsing. That is, some of "this"
	// element is in "tag". Go ahead and stream to the closing ">"
	while( in->good() )
	{
		int c = in->get();
		if ( c <= 0 )
		{
			TiXmlDocument* document = GetDocument();
			if ( document )
				document->SetError( TIXML_ERROR_EMBEDDED_NULL, 0, 0, TIXML_ENCODING_UNKNOWN );
			return;
		}
		(*tag) += (char) c ;
		
		if ( c == '>' )
			break;
	}

	if ( tag->length() < 3 ) return;

	// Okay...if we are a "/>" tag, then we're done. We've read a complete tag.
	// If not, identify and stream.

	if (    tag->at( tag->length() - 1 ) == '>' 
		 && tag->at( tag->length() - 2 ) == '/' )
	{
		// All good!
		return;
	}
	else if ( tag->at( tag->length() - 1 ) == '>' )
	{
		// There is more. Could be:
		//		text
		//		closing tag
		//		another node.
		for ( ;; )
		{
			StreamWhiteSpace( in, tag );

			// Do we have text?
			if ( in->good() && in->peek() != '<' ) 
			{
				// Yep, text.
				TiXmlText text( "" );
				text.StreamIn( in, tag );

				// What follows text is a closing tag or another node.
				// Go around again and figure it out.
				continue;
			}

			// We now have either a closing tag...or another node.
			// We should be at a "<", regardless.
			if ( !in->good() ) return;
			assert( in->peek() == '<' );
			size_t tagIndex = tag->length();

			bool closingTag = false;
			bool firstCharFound = false;

			for( ;; )
			{
				if ( !in->good() )
					return;

				int c = in->peek();
				if ( c <= 0 )
				{
					TiXmlDocument* document = GetDocument();
					if ( document )
						document->SetError( TIXML_ERROR_EMBEDDED_NULL, 0, 0, TIXML_ENCODING_UNKNOWN );
					return;
				}
				
				if ( c == '>' )
					break;

				*tag += (char) c;
				in->get();

				if ( !firstCharFound && c != '<' && !IsWhiteSpace( c ) )
				{
					firstCharFound = true;
					if ( c == '/' )
						closingTag = true;
				}
			}
			// If it was a closing tag, then read in the closing '>' to clean up the input stream.
			// If it was not, the streaming will be done by the tag.
			if ( closingTag )
			{
				if ( !in->good() )
					return;

				int c = in->get();
				if ( c <= 0 )
				{
					TiXmlDocument* document = GetDocument();
					if ( document )
						document->SetError( TIXML_ERROR_EMBEDDED_NULL, 0, 0, TIXML_ENCODING_UNKNOWN );
					return;
				}
				assert( c == '>' );
				*tag += (char) c;

				// We are done, once we've found our closing tag.
				return;
			}
			else
			{
				// If not a closing tag, id it, and stream.
				const char* tagloc = tag->c_str() + tagIndex;
				TiXmlNode* node = Identify( tagloc, TIXML_DEFAULT_ENCODING );
				if ( !node )
					return;
				node->StreamIn( in, tag );
				delete node;
				node = 0;

				// No return: go around from the beginning: text, closing tag, or node.
			}
		}
	}
}
#endif

const char* TiXmlElement::Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding )
{
	p = SkipWhiteSpace( p, encoding );
	TiXmlDocument* document = GetDocument();

	if ( !p || !*p )
	{
		if ( document ) document->SetError( TIXML_ERROR_PARSING_ELEMENT, 0, 0, encoding );
		return 0;
	}

//	TiXmlParsingData data( p, prevData );
	if ( data )
	{
		data->Stamp( p, encoding );
		location = data->Cursor();
	}

	if ( *p != '<' )
	{
		if ( document ) document->SetError( TIXML_ERROR_PARSING_ELEMENT, p, data, encoding );
		return 0;
	}

	p = SkipWhiteSpace( p+1, encoding );

	// Read the name.
	const char* pErr = p;

    p = ReadName( p, &value, encoding );
	if ( !p || !*p )
	{
		if ( document )	document->SetError( TIXML_ERROR_FAILED_TO_READ_ELEMENT_NAME, pErr, data, encoding );
		return 0;
	}

    TIXML_STRING endTag ("</");
	endTag += value;
	endTag += ">";

	// Check for and read attributes. Also look for an empty
	// tag or an end tag.
	while ( p && *p )
	{
		pErr = p;
		p = SkipWhiteSpace( p, encoding );
		if ( !p || !*p )
		{
			if ( document ) document->SetError( TIXML_ERROR_READING_ATTRIBUTES, pErr, data, encoding );
			return 0;
		}
		if ( *p == '/' )
		{
			++p;
			// Empty tag.
			if ( *p  != '>' )
			{
				if ( document ) document->SetError( TIXML_ERROR_PARSING_EMPTY, p, data, encoding );		
				return 0;
			}
			return (p+1);
		}
		else if ( *p == '>' )
		{
			// Done with attributes (if there were any.)
			// Read the value -- which can include other
			// elements -- read the end tag, and return.
			++p;
			p = ReadValue( p, data, encoding );		// Note this is an Element method, and will set the error if one happens.
			if ( !p || !*p )
				return 0;

			// We should find the end tag now
			if ( StringEqual( p, endTag.c_str(), false, encoding ) )
			{
				p += endTag.length();
				return p;
			}
			else
			{
				if ( document ) document->SetError( TIXML_ERROR_READING_END_TAG, p, data, encoding );
				return 0;
			}
		}
		else
		{
			// Try to read an attribute:
			TiXmlAttribute* attrib = new TiXmlAttribute();
			if ( !attrib )
			{
				if ( document ) document->SetError( TIXML_ERROR_OUT_OF_MEMORY, pErr, data, encoding );
				return 0;
			}

			attrib->SetDocument( document );
			const char* pErr = p;
			p = attrib->Parse( p, data, encoding );

			if ( !p || !*p )
			{
				if ( document ) document->SetError( TIXML_ERROR_PARSING_ELEMENT, pErr, data, encoding );
				delete attrib;
				return 0;
			}

			// Handle the strange case of double attributes:
			TiXmlAttribute* node = attributeSet.Find( attrib->Name() );
			if ( node )
			{
				node->SetValue( attrib->Value() );
				delete attrib;
				return 0;
			}

			attributeSet.Add( attrib );
		}
	}
	return p;
}


const char* TiXmlElement::ReadValue( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding )
{
	TiXmlDocument* document = GetDocument();

	const char* pWithWhiteSpace = p;
	// Read in text and elements in any order.
	p = SkipWhiteSpace( p, encoding );
	while ( p && *p )
	{
		if ( *p != '<' )
		{
			// Take what we have, make a text element.
			TiXmlText* textNode = new TiXmlText( "" );

			if ( !textNode )
			{
				if ( document ) document->SetError( TIXML_ERROR_OUT_OF_MEMORY, 0, 0, encoding );
				    return 0;
			}

			if ( TiXmlBase::IsWhiteSpaceCondensed() )
			{
				p = textNode->Parse( p, data, encoding );
			}
			else
			{
				// Special case: we want to keep the white space
				// so that leading spaces aren't removed.
				p = textNode->Parse( pWithWhiteSpace, data, encoding );
			}

			if ( !textNode->Blank() )
				LinkEndChild( textNode );
			else
				delete textNode;
		} 
		else 
		{
			// We hit a '<'
			// Have we hit a new element or an end tag?
			if ( StringEqual( p, "</", false, encoding ) )
			{
				return p;
			}
			else
			{
				TiXmlNode* node = Identify( p, encoding );
				if ( node )
				{
					p = node->Parse( p, data, encoding );
					LinkEndChild( node );
				}				
				else
				{
					return 0;
				}
			}
		}
		p = SkipWhiteSpace( p, encoding );
	}

	if ( !p )
	{
		if ( document ) document->SetError( TIXML_ERROR_READING_ELEMENT_VALUE, 0, 0, encoding );
	}	
	return p;
}


#ifdef TIXML_USE_STL
void TiXmlUnknown::StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag )
{
	while ( in->good() )
	{
		int c = in->get();	
		if ( c <= 0 )
		{
			TiXmlDocument* document = GetDocument();
			if ( document )
				document->SetError( TIXML_ERROR_EMBEDDED_NULL, 0, 0, TIXML_ENCODING_UNKNOWN );
			return;
		}
		(*tag) += (char) c;

		if ( c == '>' )
		{
			// All is well.
			return;		
		}
	}
}
#endif


const char* TiXmlUnknown::Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding )
{
	TiXmlDocument* document = GetDocument();
	p = SkipWhiteSpace( p, encoding );

//	TiXmlParsingData data( p, prevData );
	if ( data )
	{
		data->Stamp( p, encoding );
		location = data->Cursor();
	}
	if ( !p || !*p || *p != '<' )
	{
		if ( document ) document->SetError( TIXML_ERROR_PARSING_UNKNOWN, p, data, encoding );
		return 0;
	}
	++p;
    value = "";

	while ( p && *p && *p != '>' )
	{
		value += *p;
		++p;
	}

	if ( !p )
	{
		if ( document )	document->SetError( TIXML_ERROR_PARSING_UNKNOWN, 0, 0, encoding );
	}
	if ( *p == '>' )
		return p+1;
	return p;
}

#ifdef TIXML_USE_STL
void TiXmlComment::StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag )
{
	while ( in->good() )
	{
		int c = in->get();	
		if ( c <= 0 )
		{
			TiXmlDocument* document = GetDocument();
			if ( document )
				document->SetError( TIXML_ERROR_EMBEDDED_NULL, 0, 0, TIXML_ENCODING_UNKNOWN );
			return;
		}

		(*tag) += (char) c;

		if ( c == '>' 
			 && tag->at( tag->length() - 2 ) == '-'
			 && tag->at( tag->length() - 3 ) == '-' )
		{
			// All is well.
			return;		
		}
	}
}
#endif


const char* TiXmlComment::Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding )
{
	TiXmlDocument* document = GetDocument();
	value = "";

	p = SkipWhiteSpace( p, encoding );

//	TiXmlParsingData data( p, prevData );
	if ( data )
	{
		data->Stamp( p, encoding );
		location = data->Cursor();
	}
	const char* startTag = "<!--";
	const char* endTag   = "-->";

	if ( !StringEqual( p, startTag, false, encoding ) )
	{
		document->SetError( TIXML_ERROR_PARSING_COMMENT, p, data, encoding );
		return 0;
	}
	p += strlen( startTag );
	p = ReadText( p, &value, false, endTag, false, encoding );
	return p;
}


const char* TiXmlAttribute::Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding )
{
	p = SkipWhiteSpace( p, encoding );
	if ( !p || !*p ) return 0;

	int tabsize = 4;
	if ( document )
		tabsize = document->TabSize();

//	TiXmlParsingData data( p, prevData );
	if ( data )
	{
		data->Stamp( p, encoding );
		location = data->Cursor();
	}
	// Read the name, the '=' and the value.
	const char* pErr = p;
	p = ReadName( p, &name, encoding );
	if ( !p || !*p )
	{
		if ( document ) document->SetError( TIXML_ERROR_READING_ATTRIBUTES, pErr, data, encoding );
		return 0;
	}
	p = SkipWhiteSpace( p, encoding );
	if ( !p || !*p || *p != '=' )
	{
		if ( document ) document->SetError( TIXML_ERROR_READING_ATTRIBUTES, p, data, encoding );
		return 0;
	}

	++p;	// skip '='
	p = SkipWhiteSpace( p, encoding );
	if ( !p || !*p )
	{
		if ( document ) document->SetError( TIXML_ERROR_READING_ATTRIBUTES, p, data, encoding );
		return 0;
	}
	
	const char* end;

	if ( *p == '\'' )
	{
		++p;
		end = "\'";
		p = ReadText( p, &value, false, end, false, encoding );
	}
	else if ( *p == '"' )
	{
		++p;
		end = "\"";
		p = ReadText( p, &value, false, end, false, encoding );
	}
	else
	{
		// All attribute values should be in single or double quotes.
		// But this is such a common error that the parser will try
		// its best, even without them.
		value = "";
		while (    p && *p										// existence
				&& !IsWhiteSpace( *p ) && *p != '\n' && *p != '\r'	// whitespace
				&& *p != '/' && *p != '>' )						// tag end
		{
			value += *p;
			++p;
		}
	}
	return p;
}

#ifdef TIXML_USE_STL
void TiXmlText::StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag )
{
	while ( in->good() )
	{
		int c = in->peek();	
		if ( c == '<' )
			return;
		if ( c <= 0 )
		{
			TiXmlDocument* document = GetDocument();
			if ( document )
				document->SetError( TIXML_ERROR_EMBEDDED_NULL, 0, 0, TIXML_ENCODING_UNKNOWN );
			return;
		}

		(*tag) += (char) c;
		in->get();
	}
}
#endif

const char* TiXmlText::Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding )
{
	value = "";
//	TiXmlParsingData data( p, prevData );
	if ( data )
	{
		data->Stamp( p, encoding );
		location = data->Cursor();
	}
	bool ignoreWhite = true;

	const char* end = "<";
	p = ReadText( p, &value, ignoreWhite, end, false, encoding );
	if ( p )
		return p-1;	// don't truncate the '<'
	return 0;
}

#ifdef TIXML_USE_STL
void TiXmlDeclaration::StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag )
{
	while ( in->good() )
	{
		int c = in->get();
		if ( c <= 0 )
		{
			TiXmlDocument* document = GetDocument();
			if ( document )
				document->SetError( TIXML_ERROR_EMBEDDED_NULL, 0, 0, TIXML_ENCODING_UNKNOWN );
			return;
		}
		(*tag) += (char) c;

		if ( c == '>' )
		{
			// All is well.
			return;
		}
	}
}
#endif

const char* TiXmlDeclaration::Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding _encoding )
{
	p = SkipWhiteSpace( p, _encoding );
	// Find the beginning, find the end, and look for
	// the stuff in-between.
	TiXmlDocument* document = GetDocument();
	if ( !p || !*p || !StringEqual( p, "<?xml", true, _encoding ) )
	{
		if ( document ) document->SetError( TIXML_ERROR_PARSING_DECLARATION, 0, 0, _encoding );
		return 0;
	}
//	TiXmlParsingData data( p, prevData );
	if ( data )
	{
		data->Stamp( p, _encoding );
		location = data->Cursor();
	}
	p += 5;

	version = "";
	encoding = "";
	standalone = "";

	while ( p && *p )
	{
		if ( *p == '>' )
		{
			++p;
			return p;
		}

		p = SkipWhiteSpace( p, _encoding );
		if ( StringEqual( p, "version", true, _encoding ) )
		{
			TiXmlAttribute attrib;
			p = attrib.Parse( p, data, _encoding );		
			version = attrib.Value();
		}
		else if ( StringEqual( p, "encoding", true, _encoding ) )
		{
			TiXmlAttribute attrib;
			p = attrib.Parse( p, data, _encoding );		
			encoding = attrib.Value();
		}
		else if ( StringEqual( p, "standalone", true, _encoding ) )
		{
			TiXmlAttribute attrib;
			p = attrib.Parse( p, data, _encoding );		
			standalone = attrib.Value();
		}
		else
		{
			// Read over whatever it is.
			while( p && *p && *p != '>' && !IsWhiteSpace( *p ) )
				++p;
		}
	}
	return 0;
}

bool TiXmlText::Blank() const
{
	for ( unsigned i=0; i<value.length(); i++ )
		if ( !IsWhiteSpace( value[i] ) )
			return false;
	return true;
}

// The goal of the seperate error file is to make the first
// step towards localization. tinyxml (currently) only supports
// latin-1, but at least the error messages could now be translated.
//
// It also cleans up the code a bit.
//

const char* TiXmlBase::errorString[ TIXML_ERROR_STRING_COUNT ] =
{
	"No error",
	"Error",
	"Failed to open file",
	"Memory allocation failed.",
	"Error parsing Element.",
	"Failed to read Element name",
	"Error reading Element value.",
	"Error reading Attributes.",
	"Error: empty tag.",
	"Error reading end tag.",
	"Error parsing Unknown.",
	"Error parsing Comment.",
	"Error parsing Declaration.",
	"Error document empty.",
	"Error null (0) or unexpected EOF found in input stream.",
};
