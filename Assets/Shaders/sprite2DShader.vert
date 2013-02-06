#version 330
in vec3 coord3d;
in vec2 texcoord2d;
uniform mat4 mvp;

out vec2 f_texcoord;
void main()
{

	f_texcoord = texcoord2d;
	gl_Position    = mvp*vec4(coord3d,1.0);
	
}
