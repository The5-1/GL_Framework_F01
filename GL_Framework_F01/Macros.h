#pragma once

#include "ForwardDeclarations.h"


//https://stackoverflow.com/questions/5530248/creating-a-string-list-and-an-enum-list-from-a-c-macro/5530947#5530947
#ifndef ENUM_MACRO
#define ENUM_MACRO(name, v1, v2, v3, v4, v5, v6, v7)\
    enum name { v1, v2, v3, v4, v5, v6, v7};\
    const char *name##Strings[] = { #v1, #v2, #v3, #v4, #v5, #v6, #v7};\
    const char *name##ToString(value) { return name##Strings[value]; }
#endif // !ENUM_MACRO


#ifndef CLASSNAME_TO_STRING
#define CLASSNAME_TO_STRING(__class__) \
({              \
    __class__ *x;\
    #__class__ ;\
})
#endif // !CLASSNAME_TO_STRING

