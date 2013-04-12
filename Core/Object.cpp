<<<<<<< HEAD
#include "Object.h"

Object::Object()
	:Entity(Type::I_DRAWABLE_OBJECT)
{

}
Object::~Object()
{

}

void Object::Update()
{

}
void Object::Render()
{
	
}

bool Object::Initialize(/*Model* modelRawData*/)
{
	return true;
}

=======
#include "Object.h"

Object::Object()
	:Entity(Type::I_DRAWABLE_OBJECT)
{

}
Object::~Object()
{

}

void Object::Update()
{

}
void Object::Render()
{
	
}

bool Object::Initialize(RawObjectData modelRawData)
{
	
	return true;
}

>>>>>>> 1ed802f4b6ab5e0da54017392c9b581129a6155b
