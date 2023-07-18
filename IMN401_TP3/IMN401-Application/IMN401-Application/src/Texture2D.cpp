#include "Texture2D.h"



#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>



Texture2D::Texture2D(const std::string& filename):
	name(filename),id(0), handle(0),image(NULL)
{
	int channels;

	
	image = stbi_load(filename.c_str(), &width, &height, &channels, 4);

	if (image == nullptr)
		std::cout << "Error Loading image file " << filename << endl;
	else
		loadToGPU();




}

void Texture2D::loadToGPU()
{
	int numberOfLevel =  1 + floor(log2(max(width, height)));
	// Load texture to GPU


	glCreateTextures(GL_TEXTURE_2D, 1, &id);
	glTextureStorage2D(id, numberOfLevel,GL_RGBA8,width,height);
	glTextureSubImage2D(id, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateTextureMipmap(id);
	
	glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);


	makeResident();
}

void Texture2D::makeResident()
{
	handle = glGetTextureHandleARB(id);
	glMakeTextureHandleResidentARB(handle);

}




Texture2D::~Texture2D()
{

}
