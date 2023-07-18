
#include "MaterialTP2.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>

std::chrono::steady_clock::time_point beginTime;

MaterialTP2::MaterialTP2(string name) :
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

	beginTime = std::chrono::steady_clock::now();
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
	glm::mat4 matModel = o->frame()->getModelMatrix();
	glm::mat4 matView = Scene::getInstance()->camera()->getViewMatrix();
	glm::mat4 matProj= Scene::getInstance()->camera()->getProjectionMatrix();
	GLsizei count = 1;
	glProgramUniformMatrix4fv(vp->getId(), l_Model, count, false,glm::value_ptr(matModel));
	glProgramUniformMatrix4fv(vp->getId(), l_View, count, false, glm::value_ptr(matView));
	glProgramUniformMatrix4fv(vp->getId(), l_Proj, count, false, glm::value_ptr(matProj));


	GLint loc = glGetUniformLocation(vp->getId(), "time");
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	float time = std::chrono::duration_cast<std::chrono::milliseconds>(end - beginTime).count() * 0.001;
	glProgramUniform1f(vp->getId(), loc, time);

	/*********************************************/
}
