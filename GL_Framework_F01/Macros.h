#pragma once

#include "ForwardDeclarations.h"

#ifndef CLASSNAME_TO_STRING

#define CLASSNAME_TO_STRING(__class__) \
({              \
    __class__ *x;\
    #__class__ ;\
})

#endif // !CLASSNAME_TO_STRING

