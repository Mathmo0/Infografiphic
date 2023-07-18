
#include "MaterialTP3.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>

//std::chrono::steady_clock::time_point timeValue;

MaterialTP3::MaterialTP3(string name) :
	MaterialGL(name)
{
	/************Déclaration des programmes **************************/
	vp = new GLProgram(MaterialPath + "Shaders/Main-VS.glsl", GL_VERTEX_SHADER);
	fp = new GLProgram(MaterialPath + "Shaders/Main-FS.glsl", GL_FRAGMENT_SHADER);

	m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
	m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);


	l_View = glGetUniformLocation(vp->getId(), "View");
	l_Proj = glGetUniformLocation(vp->getId(), "Proj");
	l_Model = glGetUniformLocation(vp->getId(), "Model");

	l_Color = glGetUniformLocation(vp->getId(), "color");
	l_Phong = glGetUniformLocation(fp->getId(), "Phong");

	l_Lumpos = glGetUniformLocation(vp->getId(), "posLum");
	l_campos = glGetUniformLocation(vp->getId(), "posCam");

	/**************************************/	
}

void MaterialTP3::setColor(glm::vec3 color)
{
	Color = color;
}

void MaterialTP3::setPhong(glm::vec4 phong)
{
	Phong = phong;
}

MaterialTP3::~MaterialTP3()
{
	
}

void MaterialTP3::render(Node *o)
{

	
	m_ProgramPipeline->bind();
	o->drawGeometry(GL_TRIANGLES);
	m_ProgramPipeline->release();


}

void MaterialTP3::animate(Node* o, const float elapsedTime)
{
	/**********************************************
	* 
	* TP 2 - A completer
	Calculer et Transmettre les matrices Model View et Proj au shaders
	- Utilisez glm::value_ptr(mat) pour trouver le pointeur de la matrice mat a transmettre au GPU via la fonction glProgramUniform*()
	- Une matrice 4X4 se transmet grace a glProgramUniformMatrix4fv

	****************************************************/
	
	glm::mat4 Model = o->frame()->getModelMatrix();
	auto Modelptr = glm::value_ptr(Model);
	
	Camera* camera = Scene::getInstance()->camera();

	glm::vec3 posCamera = camera->frame()->convertPtTo(glm::vec3(0, 0, 0), o->frame());
	glm::vec3 posLumiere = Scene::getInstance()->getNode("Lumiere")->frame()->convertPtTo(glm::vec3(0, 0, 0), o->frame());

	glm::mat4 Projection = camera->getProjectionMatrix();
	auto Projectionptr = glm::value_ptr(Projection);

	glm::mat4 View = camera->getViewMatrix();
	auto Viewptr = glm::value_ptr(View);

	// Var uniforme dans le vertex shader
	glProgramUniformMatrix4fv(this->vp->getId(), l_Model, 1.0, false, Modelptr);
	glProgramUniformMatrix4fv(this->vp->getId(), l_Proj, 1.0, false, Projectionptr);
	glProgramUniformMatrix4fv(this->vp->getId(), l_View, 1.0, false, Viewptr);
	
	glProgramUniform3fv(this->vp->getId(), l_Lumpos, 1, glm::value_ptr(posLumiere));
	glProgramUniform3fv(this->vp->getId(), l_campos, 1, glm::value_ptr(posCamera));

	// Var uniforme dans le fragment shader
	glProgramUniform3fv(this->vp->getId(), l_Color, 1, glm::value_ptr(Color));
	glProgramUniform4fv(this->fp->getId(), l_Phong, 1, glm::value_ptr(Phong));

	/*********************************************/
}
