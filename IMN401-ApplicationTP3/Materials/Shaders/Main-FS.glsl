#version 460



in VTF
{
 vec3 couleur;
};

in BRDF
{
    vec3 V;
    vec3  L;
    vec3 NormaleOut;
};

uniform float kd;
uniform float ks;
uniform float ka;

uniform float alpha;
uniform vec3 colorLum;


layout (location = 0) out vec4 Color;

void main()
{
    vec3 R = reflect(normalize(-L), NormaleOut);
    float Id = kd * max(dot(NormaleOut, normalize(L)), 0);
    float Is = ks * pow(max(dot(normalize(R), normalize(V)),0), alpha);
    float Ia = ka;
    vec3 newColor = couleur * Ia + (couleur * Id + Is) * colorLum;
	Color = vec4(newColor,1.0);
}