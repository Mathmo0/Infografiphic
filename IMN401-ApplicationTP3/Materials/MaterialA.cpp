#include "MaterialA.h"




MaterialA::MaterialA(string name) :
	MaterialGL(name)
{
}

MaterialA::~MaterialA()
{

}

void MaterialA::render(Node* o)
{
}


void MaterialA::animate(Node* o, const float elapsedTime)
{
	glm::vec3 axis = glm::vec3(1.0, 0, 0);
	o->frame()->rotate(axis,0.2);
}