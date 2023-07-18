#version 460

uniform float time;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;
 out gl_PerVertex {
        vec4 gl_Position;
        float gl_PointSize;
        float gl_ClipDistance[];

    };
layout (location = 0) in vec3 Position;
layout(location = 2) in vec3 Normale;

out VTF
{
    vec3 couleur;
};

out BRDF
{
    vec3 V;
    vec3  L;
    vec3 NormaleOut;
};

//uniform float posLum;


uniform vec3 posCamera;
uniform vec3 posLum;
uniform vec3 myColor;

void main()
{ 

    NormaleOut = Normale;

    L = posLum - Position;

    V = posCamera - Position;

	gl_Position = Proj * View* Model * vec4(Position,1.0);

  
    couleur = myColor;

 	

}
