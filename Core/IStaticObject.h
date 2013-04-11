#ifndef I_STATIC_OBJECT_H
#define I_STATIC_OBJECT_H

#include "Entity.h"
//#include "BoundingBox"
//#include "Material"

class IStaticObject		:public Entity
{
	protected:
		//BoundingBox boundingBox;


	public:
		IStaticObject();
		virtual~IStaticObject();

};


#endif

