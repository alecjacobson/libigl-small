/* ---------------------------------------------------------------------------
// XMLSerializationTest.h
// Author: Christian Sch�ller on 19/11/13.
------------------------------------------------------------------------------
 Used to demonstrates howto use the XMLSerialization class.
----------------------------------------------------------------------------*/
#ifndef XML_SERIALIZABLE_H
#define XML_SERIALIZABLE_H  

#include <igl/xml/XMLSerialization.h>

namespace igl
{

  class XMLSerializationTest : public ::igl::XMLSerialization
  {
  public:
      
    int testInt;
    std::vector<float> testVector;
      
    XMLSerializationTest();
    void InitSerialization();
      
    bool Test();
  };

  XMLSerializerTest::XMLSerializerTest()
    : XMLSerialization("testObject")
  {
  }

  void XMLSerializerTest::InitSerialization()
  {
    xmlSerializer->Add(testInt,"testInt");
    xmlSerializer->Add(testVector,"testVector");
      
    testInt = 10;
      
    testVector.push_back(1.0001f);
    testVector.push_back(2.0001f);
    testVector.push_back(3.0001f);
  }
}

#endif