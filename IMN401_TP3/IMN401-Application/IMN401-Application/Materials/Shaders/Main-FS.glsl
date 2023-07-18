#version 460


uniform vec4 Phong;

layout (location = 0) out vec4 Color;
in vec3 normal;
in vec3 colorvs;

in BRDF
{
	vec3 V;
    vec3  L;
};

void main()
{
    vec3 R = reflect(normalize(-L), normal); // vecteur de reflexion

	float id = Phong.y * max(dot(normal, normalize(L)), 0);
    float is = Phong.z * pow(max(dot(normalize(R), normalize(V)), 0), Phong.w);
    float ia = Phong.x;

    vec3 newColor = ia * colorvs + (id * colorvs + is) * vec3(1, 1, 1);

    Color = vec4(newColor, 1.0);
}