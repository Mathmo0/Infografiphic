
#include "MaterialTP3.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>

//std::chrono::steady_clock::time_point beginTime;

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

	//beginTime = std::chrono::steady_clock::now();
	/**************************************/

}

MaterialTP3::~MaterialTP3()
{

}

void MaterialTP3::render(Node* o)
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
	glm::mat4 matModel = o->frame()->getModelMatrix();
	glm::mat4 matView = Scene::getInstance()->camera()->getViewMatrix();
	glm::mat4 matProj = Scene::getInstance()->camera()->getProjectionMatrix();
	GLsizei count = 1;
	glProgramUniformMatrix4fv(vp->getId(), l_Model, count, false, glm::value_ptr(matModel));
	glProgramUniformMatrix4fv(vp->getId(), l_View, count, false, glm::value_ptr(matView));
	glProgramUniformMatrix4fv(vp->getId(), l_Proj, count, false, glm::value_ptr(matProj));


	float kd = 0.8;
    float ks = 1.0;
	float ka = 0.2; 
	glm::vec3 posCamera = Scene::getInstance()->camera()->frame()->convertPtTo(glm::vec3(0,0,0),o->frame());
	float alpha = 100;
	Frame *frameLum = Scene::getInstance()->getNode("Lumiere")->frame();
	glm::vec3 posLum = frameLum->convertPtTo(glm::vec3(0,0,0),o->frame());

	//glm::vec3 posLum = o->frame()->convertPtTo(glm::vec3(0, 0, 0), Scene::getInstance()->getNode("Lumiere")->frame());
	

	GLint locKd = glGetUniformLocation(fp->getId(), "kd");
	glProgramUniform1f(fp->getId(), locKd, kd);
	GLint locKs = glGetUniformLocation(fp->getId(), "ks");
	glProgramUniform1f(fp->getId(), locKs, ks);
	GLint locKa = glGetUniformLocation(fp->getId(), "ka");
	glProgramUniform1f(fp->getId(), locKa, ka);
	GLint locAlpha = glGetUniformLocation(fp->getId(), "alpha");
	glProgramUniform1f(fp->getId(), locAlpha, alpha);
	GLint locPosCamera = glGetUniformLocation(vp->getId(), "posCamera");
	glProgramUniform3fv(vp->getId(), locPosCamera, 1, glm::value_ptr(posCamera));

	GLint locPosLum = glGetUniformLocation(vp->getId(), "posLum");
	glProgramUniform3fv(vp->getId(), locPosLum, 1, glm::value_ptr(posLum));


	glm::vec3 colorLum = glm::vec3(1, 1, 1);
	GLint locColorLum = glGetUniformLocation(fp->getId(), "colorLum");
	glProgramUniform3fv(fp->getId(), locColorLum, 1, glm::value_ptr(colorLum));


	glm::vec3 color = glm::vec3(0.2, 0.6, 0.8);
	GLint locColor = glGetUniformLocation(vp->getId(), "myColor");
	glProgramUniform3fv(vp->getId(), locColor, 1, glm::value_ptr(color));
	//glProgramUniform3f(vp->getId(), loc, posLum);
	//std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	//float time = std::chrono::duration_cast<std::chrono::milliseconds>(end - beginTime).count() * 0.001;
	//glProgramUniform1f(vp->getId(), loc, time);

	/*********************************************/
}
