#version 460



uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;
uniform vec3 posLum;
uniform vec3 posCam;
uniform vec3 color;
 out gl_PerVertex {
        vec4 gl_Position;
        float gl_PointSize;
        float gl_ClipDistance[];
};
layout (location = 0) in vec3 Position;

out normal{
    vec3 normal;
};
layout (location = 2) in vec3 Normal;

out ColorVS
{
    vec3 colorvs;
};

out BRDF
{
    vec3 V;
    vec3  L;
};

void main()
{
	gl_Position = Proj * View * Model * vec4(Position,1.0);

 	normal = Normal;

    L = posLum - Position; // vecteur vers la lumiere
    V = posCam - Position; // vecteur vers la camera (oeil)

    colorvs = color;
}
