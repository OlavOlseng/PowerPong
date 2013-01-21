attribute vec3 coord3d;
uniform mat4 mvp;
void main(){
	gl_Position = mvp*vec4(coord3d.xyz,1.0);
};