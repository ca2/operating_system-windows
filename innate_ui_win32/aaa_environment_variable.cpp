#include "framework.h"
#include "acme/operating_system.h"


// See property_set::parse_environment_variable

//
//CLASS_DECL_ACME void parse(environment_variable_value_array & array, const string_array_base & straEnvironment)
//{
//   
//   for (auto & strEnvironment : straEnvironment)
//   {
//
//      auto find = strEnvironment.find("=");
//
//      if (find <= 0)
//      {
//         
//         continue;
//
//      }
//
//      environment_variable_value variablevalue;
//
//      // get the left hand side (LHS) of "=" in the string
//      variablevalue.m_element1 = strEnvironment.left()(find);
//
//      variablevalue.m_element2 = strEnvironment.substr(find + 1);
//
//      array.add(variablevalue);
//
//   }
//
//}
//
//
//
