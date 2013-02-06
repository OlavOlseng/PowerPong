#version 330

in vec2 f_texcoord;
uniform sampler2D tex;
void main()
{
	
	gl_FragColor = texture(tex,vec2(f_texcoord.x,f_texcoord.y));
}
