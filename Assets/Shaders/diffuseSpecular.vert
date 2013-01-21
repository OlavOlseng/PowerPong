#version 330

attribute vec3 coord3d;
attribute vec3 normal3d;
attribute vec2 texcoord2d;
uniform mat4 mvp;
uniform mat4 modelMatrix;
varying vec4 f_normal;
varying vec2 f_texcoord;
varying vec4 f_position;
void main()
{
	f_position = modelMatrix*vec4(coord3d,1.0);
	f_normal = normalize(modelMatrix*vec4(normal3d.xyz,0.0));
	f_texcoord = texcoord2d;
	gl_Position = mvp*vec4(coord3d.xyz,1.0);
}


