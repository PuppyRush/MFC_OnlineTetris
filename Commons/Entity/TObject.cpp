//
// Created by pi on 9/2/18.
//

#include "TObject.h"

TObject::TObject()
:m_unique(TAtomic::newUnique())
{

}


