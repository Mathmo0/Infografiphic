
#include "MaterialTP2.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>

std::chrono::steady_clock::time_point timeValue;

MaterialTP2::MaterialTP2(string name) :
	MaterialGL(name)
{
	timeValue = std::chrono::high_resolution_clock::now();
	float time = 0.0f;

	/************Déclaration des programmes **************************/
	vp = new GLProgram(MaterialPath + "Shaders/Main-VS.glsl", GL_VERTEX_SHADER);
	fp = new GLProgram(MaterialPath + "Shaders/Main-FS.glsl", GL_FRAGMENT_SHADER);

	m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
	m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);


	l_View = glGetUniformLocation(vp->getId(), "View");
	l_Proj = glGetUniformLocation(vp->getId(), "Proj");
	l_Model = glGetUniformLocation(vp->getId(), "Model");
	l_Time = glGetUniformLocation(vp->getId(), "Time");

	/**************************************/

		
}

MaterialTP2::~MaterialTP2()
{
	
}

void MaterialTP2::render(Node *o)
{

	
	m_ProgramPipeline->bind();
	o->drawGeometry(GL_TRIANGLES);
	m_ProgramPipeline->release();


}

void MaterialTP2::animate(Node* o, const float elapsedTime)
{
	/**********************************************
	* 
	* TP 2 - A completer
	Calculer et Transmettre les matrices Model View et Proj au shaders
	- Utilisez glm::value_ptr(mat) pour trouver le pointeur de la matrice mat a transmettre au GPU via la fonction glProgramUniform*()
	- Une matrice 4X4 se transmet grace a glProgramUniformMatrix4fv

	****************************************************/
	
	glm::mat4 Model = o->frame()->getModelMatrix();
	//glm::mat4 *Model2 = o->frame()->getMatrix();
	auto Modelptr = glm::value_ptr(Model);
	
	Camera* camera = Scene::getInstance()->camera();
	
	glm::mat4 Projection = camera->getProjectionMatrix();
	auto Projectionptr = glm::value_ptr(Projection);

	glm::mat4 View = camera->getViewMatrix();
	auto Viewptr = glm::value_ptr(View);

	auto timeNow = std::chrono::high_resolution_clock::now();
	float duration = std::chrono::duration<float, std::milli>(timeNow - timeValue).count();
	float time = duration;

	glProgramUniformMatrix4fv(this->vp->getId(), l_Model, 1.0, false, Modelptr);
	glProgramUniformMatrix4fv(this->vp->getId(), l_Proj, 1.0, false, Projectionptr);
	glProgramUniformMatrix4fv(this->vp->getId(), l_View, 1.0, false, Viewptr);
	glProgramUniform1f(this->vp->getId(), l_Time, time);
	/*********************************************/
}
