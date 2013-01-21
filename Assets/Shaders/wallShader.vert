attribute vec3 coord3d;
attribute vec3 color3d;
attribute vec3 normal3d;
attribute float blockType;
uniform mat4 mvp;
uniform mat4 modelMatrix;
varying vec3 f_color;
varying vec4 texcoord;
varying int f_type;
varying vec4 f_normal;
varying vec4 f_position;

		
		
void main()
{
	texcoord = vec4(coord3d,blockType);
	f_type = int(blockType);
	f_color = color3d;
	f_normal = modelMatrix*vec4(normal3d.xyz,0.0);
	f_position = modelMatrix*vec4(coord3d.xyz,1.0);
	gl_Position = mvp*vec4(coord3d.xyz,1.0);

};
