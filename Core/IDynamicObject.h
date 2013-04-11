#ifndef I_DYNAMIC_OBJECT_H
#define I_DYNAMIC_OBJECT_H

#include "Entity.h"
//#include "BoundingBox"
//#include "Material"

class IDynamicObject	:public Entity
{
	protected:
		//BoundingBox boundingBox;


	public:
		IDynamicObject();
		virtual~IDynamicObject();

};


#endif

