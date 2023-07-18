#ifndef _GOBLIM_SCENE_
#define _GOBLIM_SCENE_

#include "Node.h"
#include "ModelGL.h"
#include "Camera.h"
#include "Resource_mgr.hpp"
#include "Singleton.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "Logger/ImGuiLogger.h"
#include "Node.h"

const string ObjPath = "./../Objets/";
const string MaterialPath = "./../Materials/";

class Scene : public Singleton<Scene>{
	friend class Singleton<Scene>;
public:
	
	
	Frame* frame();
	Camera* camera();
	
	Node* getRoot();
	Node* getNode(std::string name);

	template <class R>  R* getModel(string a)
	{		
		return m_Models.get<R>(a);
	}
	
	template <class R> R* getNodes(string a)
	{
		return m_Nodes.get<R>(a);
	}
	void releaseNode(string a);
	void releaseNode(Node *n);


	void releaseModel(string a);
	void releaseModel(ModelGL *m);

	void nextManipulatedNode();
	void manipulateNode(std::string name);

	void displayInterface();

	Node* getSceneNode();
	Node* getManipulatedNode();

	
	Resource_mgr<Node> m_Nodes;
	Resource_mgr<ModelGL> m_Models;
	bool needupdate;
	
private:
	Scene(); 
	~Scene();

	Node* m_Root;
	Node *m_Scene;

	Camera* current_Camera;
	Node* current_ManipulatedNode;

};



#endif