#version 330

in vec3 coord3d;
in vec3 color3d;

uniform mat4 mvp;
varying vec3 f_color;
void main()
{
	f_color = color3d;
	gl_Position = mvp*vec4(coord3d,1.0);
}
