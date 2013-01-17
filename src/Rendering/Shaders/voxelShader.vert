// simple vertex shader
attribute vec4 coord4d;

uniform mat4 mvp;



void main()
{
	gl_Position    = mvp*vec4(coord4d.xyz,1.0);

}
