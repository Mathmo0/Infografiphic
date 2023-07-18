
#include "EngineGL.h"
#include "Scene.h"

#include "Materials/MaterialTP2.h"

#include "Materials/MaterialTP3.h"
#include "Materials/MaterialA.h"



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
	MaterialTP3* material = new MaterialTP3("IMN401-TP3");

	/***********Création d'un objet, méthode détaillée*/

	//Création d'un noeud Bunny
	Node* bunny = scene->getNode("Bunny");

	//Définition d'un modèle 3D pour le noeud Bunny
	bunny->setModel(scene->m_Models.get<ModelGL>(ObjPath + "Bunny.obj"));

	//Mise à l 'échelle  du repère 3D du noeud Bunny
	bunny->frame()->scale(glm::vec3(30.0));

	//Assigner le materiau material au noeud Bunny
	bunny->setMaterial(material);

	//Adotpion du noeud Bunny par le noeud Scene
	scene->getSceneNode()->adopt(bunny);

	/****************
	* 
	*  TP 2 : A compléter
	* 	
	******************/
	
/*
	MaterialTP2* material2 = new MaterialTP2("IMN401-TP2");

	Node* A = scene->getNode("A");
	A->frame()->attachTo(bunny->frame());

	Node* sphere = scene->getNode("Sphere");

	sphere->setModel(scene->m_Models.get<ModelGL>(ObjPath + "Sphere.obj"));


	sphere->setMaterial(material2);

	sphere->frame()->translate(glm::vec3(1.0, 0, 0));
	sphere->frame()->attachTo(A->frame());

	bunny->adopt(A);
	A->adopt(sphere);


	MaterialA* material3 = new MaterialA("IMN401-TP2");
	 A->setMaterial(material3);
	// A->getMaterial()->animate()
	//bunny->adopt(A);
	//A->adopt(sphere);
	*/


	/****************
*
*  TP 3 : A compléter
*
******************/

	 //wall
	 //Création d'un materiau de Base
	 MaterialTP3* materialWall = new MaterialTP3("IMN401-TP3");

	 /***********Création d'un objet, méthode détaillée*/

	 //Création d'un noeud Bunny
	 Node* wall = scene->getNode("Wall");

	 //Définition d'un modèle 3D pour le noeud Bunny
	 wall->setModel(scene->m_Models.get<ModelGL>(ObjPath + "Wall.obj"));

	 //Mise à l 'échelle  du repère 3D du noeud Bunny
	 wall->frame()->translate(glm::vec3(0, -5, 0));
	 wall->frame()->scale(glm::vec3(5.0));

	 //Assigner le materiau material au noeud Bunny
	 wall->setMaterial(materialWall);


	 //Adotpion du noeud Bunny par le noeud Scene
	 scene->getSceneNode()->adopt(wall);



	 //wall
	 //Création d'un materiau de Base
	 MaterialTP2* materialLum = new MaterialTP2("IMN401-TP4");

	 /***********Création d'un objet, méthode détaillée*/

	 //Création d'un noeud Bunny
	 Node* lumiere = scene->getNode("Lumiere");

	 //Définition d'un modèle 3D pour le noeud Bunny
	 lumiere->setModel(scene->m_Models.get<ModelGL>(ObjPath + "Sphere.obj"));

	 //Mise à l 'échelle  du repère 3D du noeud Bunny
	 lumiere->frame()->translate(glm::vec3(0, 5, 0));

	 //Assigner le materiau material au noeud Bunny
	 lumiere->setMaterial(materialLum);

	 lumiere->frame()->scale(glm::vec3(10.0));

	 //Adotpion du noeud Bunny par le noeud Scene
	 scene->getSceneNode()->adopt(lumiere);





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
