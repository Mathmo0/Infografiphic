
#include "EngineGL.h"
#include "Scene.h"

#include "Materials/MaterialTP2.h"
#include "Materials/Materiel.h"
#include <Materials/MaterialTP3.h>



EngineGL::EngineGL(int width, int height) 
{
	m_Width = width;
	m_Height = height;
	scene = Scene::getInstance();		
}

EngineGL::~EngineGL()
{


}


void EngineGL::setupEngine()
{
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, m_Width, m_Height);
	setClearColor(glm::vec4(0.5,0.5,0.5,1.0));


	this->allNodes = new NodeCollector();

	allNodes->collect(scene->getRoot());

	LOG_INFO << "initialisation complete" << std::endl;
}

bool EngineGL::init()
{
	LOG_INFO << "Initializing Scene" << std::endl;




	//Création d'un materiau de Base
	MaterialTP2* material = new MaterialTP2("IMN401-TP2");
	MaterialTP3* materialtp3 = new MaterialTP3("IMN401-TP3");
	MaterialTP3* materialtp3B = new MaterialTP3("IMN401-TP3");

	/***********Création d'un objet, méthode détaillée*/

	//Création d'un noeud Bunny
	Node* bunny = scene->getNode("Bunny");

	//Définition d'un modèle 3D pour le noeud Bunny
	bunny->setModel(scene->m_Models.get<ModelGL>(ObjPath + "Bunny.obj"));

	//Mise à l 'échelle  du repère 3D du noeud Bunny
	bunny->frame()->scale(glm::vec3(30.0));

	materialtp3B->setColor(glm::vec3(0, 0, 1));
	materialtp3B->setPhong(glm::vec4(0.2, 0.8, 1.0, 100)); // ka = 0.2, kd = 0.8, ks = 1.0 et s = 100

	//Assigner le materiau material au noeud Bunny
	bunny->setMaterial(materialtp3B);

	//Adotpion du noeud Bunny par le noeud Scene
	scene->getSceneNode()->adopt(bunny);
	
	/****************
	*
	*  TP 3 : A compléter
	*
	******************/
	Node* wall = scene->getNode("Wall");

	//Définition d'un modèle 3D pour le noeud Bunny
	wall->setModel(scene->m_Models.get<ModelGL>(ObjPath + "Wall.obj"));

	//Mise à l 'échelle  du repère 3D du noeud Bunny
	wall->frame()->scale(glm::vec3(10.0));
	wall->frame()->translate(glm::vec3(0, -0.5, 0));

	materialtp3->setColor(glm::vec3(0, 1, 0));
	materialtp3->setPhong(glm::vec4(0.1, 0.25, 0.5, 50)); // ka = 0.1, kd = 0.25, ks = 0.5 et s = 50

	//Assigner le materiau material au noeud Bunny
	wall->setMaterial(materialtp3);

	//Adotpion du noeud Bunny par le noeud Scene
	scene->getSceneNode()->adopt(wall);

	/*
		Lumiere
	*/
	Node* Lumiere = scene->getNode("Lumiere");

	//Définition d'un modèle 3D pour le noeud Bunny
	Lumiere->setModel(scene->m_Models.get<ModelGL>(ObjPath + "Sphere.obj"));

	//Mise à l 'échelle  du repère 3D du noeud Bunny
	Lumiere->frame()->translate(glm::vec3(0, 5, 0));
	Lumiere->frame()->scale(glm::vec3(30.0));

	//Assigner le materiau material au noeud Bunny
	Lumiere->setMaterial(material);

	//Adotpion du noeud Bunny par le noeud Scene
	scene->getSceneNode()->adopt(Lumiere);

	setupEngine();
	return(true);
}


void EngineGL::render ()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	// Rendu de la liste de tous les noeuds
	for (unsigned int i = 0; i < allNodes->nodes.size(); i++)
		allNodes->nodes[i]->render();
	
}

void EngineGL::animate (const float elapsedTime)
{
	// Animate each node
	for (unsigned int i = 0; i < allNodes->nodes.size (); i++)
		allNodes->nodes[i]->animate (elapsedTime);
	

	// Update Camera Buffer
	//Scene::getInstance()->camera()->updateBuffer();
}

void EngineGL::onWindowResize(int w, int h)
{
	glViewport(0, 0, w, h);
}

void EngineGL::setClearColor(glm::vec4 color)
{
	glClearColor(color.x, color.y, color.z,color.w);
}
void EngineGL::displayInterface()
{

}
