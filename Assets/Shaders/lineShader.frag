
#version 330

varying vec3 f_color;
void main()
{
	gl_FragColor = vec4(f_color.xyz,1.0);
}
