

#ifndef _MaterialTP3_
#define _MaterialTP3_


#include "MaterialGL.h"

class MaterialTP3 : public MaterialGL
{
	public :

		//Attributs
		
		//Constructeur-Destructeur

		/**
			Constructeur de la classe � partir du nom du mat�riau 
			@param name : nom du mat�riau
		*/
		MaterialTP3(string name="");

		/**
			Destructeur de la classe
		*/
		~MaterialTP3();

		//M�thodes

		/**
			M�thode virtuelle qui est appel�e pour faire le rendu d'un objet en utilisant ce mat�riau
			@param o : Node/Objet pour lequel on veut effectuer le rendu
		*/
		virtual void render(Node *o);

		/**
			M�thode virtuelle qui est appel�e pour modifier une valeur d'un param�tre n�cessaire pour le rendu
			@param o : Node/Objet concern� par le rendu
			@param elapsedTime : temps
		*/
		virtual void animate(Node* o, const float elapsedTime);


		virtual void displayInterface() {};

		virtual void setColor(glm::vec3 color);
		virtual void setPhong(glm::vec4 phong);

		
	protected :
		GLProgram* vp;
		GLProgram* fp;

		GLuint l_View,l_Proj, l_Model, l_Color, l_Phong, l_Lumpos, l_campos;

		glm::vec4 Phong;
		glm::vec3 Color;
};

#endif