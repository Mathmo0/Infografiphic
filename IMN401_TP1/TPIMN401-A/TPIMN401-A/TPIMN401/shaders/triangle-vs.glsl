#version 460

/*

TP1 du cours IMN401 a remettre le 20 fevrier 2023

    Remis par : 
        Ivan Serra Moncadas seri1101
        Mathis MOYSE moym1101
        Robin LEJEUNE lejr0501
*/

out gl_PerVertex{
	vec4 gl_Position;
};
layout (location = 0) in vec3 Position;

out color{
	vec2 pos;
};

uniform float time;

void main()
{
	float radius = 0.5 + 0.2 * cos(time / 1000.0);
	vec3 newPosition = vec3(radius * Position.x, radius * Position.y, Position.z);
	gl_Position = vec4(newPosition, 1.0);
	pos = vec2(newPosition[0], newPosition[1]);
}