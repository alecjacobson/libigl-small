/* ---------------------------------------------------------------------------
 // XMLSerializable.h
 // Author: Christian Sch�ller on 19/11/13.
 ------------------------------------------------------------------------------
 Inherit from this abstract class to have full control over the serialization
 of your user defined class.
 ----------------------------------------------------------------------------*/
#ifndef XML_SERIALIZABLE_H
#define XML_SERIALIZABLE_H

#include <iostream>
#include <tinyxml2.h>

namespace igl
{

  class XMLSerializable
  {
  public:
    /**
    * Default name of serializable object
    */
    std::string Name;
      
    /**
      * This function gets called if the objects were not found during deserialization.
      * Initialize your objects as you like.
      */
    virtual void Init() = 0;
    /**
      * Serialize your stuff within this function.
      * It contains the current serialization xml file. You can use SaveToXMLDoc or SaveGroupToXMLElement to add your objects.
      */
    virtual bool Serialize(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* element) = 0;
      
    /**
      * Deserialize your stuff within this function.
      * It contains the current serialization xml file. You can use LoadFromXMLDoc or LoadGroupFromXMLElement to read out your objects.
      */
    virtual bool Deserialize(tinyxml2::XMLDocument* doc, const tinyxml2::XMLElement* element) = 0;
  };
}

#endif