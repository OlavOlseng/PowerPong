

varying vec4 f_texcoord;
varying float f_normalIndex;
varying vec4 f_position;
varying vec4 f_normal;
uniform sampler2D tileAtlas;
uniform float stepSize;

struct DirectionalLight{
	vec4 diffuse;
	vec4 specular;
	vec4 direction;
};

struct PointLight{
	vec4 diffuse;
	vec4 specular;
	vec4 position;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};


uniform int numDirLights;
uniform int numPointLights;
uniform DirectionalLight dirLights[10];
uniform PointLight pointLights[10];
struct Material{
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	float shininess;
};

uniform Material material;


const vec4 globalAmbient = vec4(0.2,0.2,0.2,0.0);
uniform vec4 cameraPos;



void main()
{
	
	vec4 diffuseLight;
	vec4 specularLight;
	
	float diffuseFactor;
	float specularFactor;
	
	DirectionalLight dirLight;
	PointLight pointLight;
	vec4 direction;
	vec4 vecToLight;
	vec4 ambientLight = material.ambient*globalAmbient;

	vec4 viewDir = normalize(f_position- cameraPos); 
	float attenuation = 0.0;
	float distance = 0.0;

	for(int i = 0;i<numDirLights;i++){
		dirLight = dirLights[i];
		diffuseFactor = clamp(dot(f_normal,-dirLight.direction),0.0,1.0);
		if(diffuseFactor > 0.0){
			diffuseLight += material.diffuse*dirLight.diffuse*diffuseFactor;
			specularFactor = clamp(dot(reflect(-dirLight.direction,f_normal),viewDir),0.0,1.0);
			if(specularFactor >0.0)
				specularLight += material.specular*dirLight.specular*pow(specularFactor,material.shininess);
		}		
	}

	for(int i = 0;i<numPointLights;i++){
		pointLight = pointLights[i];
		vecToLight= f_position - pointLight.position;

		distance = length(vecToLight);
		direction = normalize(-vecToLight);
		attenuation = 1.0/(pointLight.constantAttenuation + pointLight.linearAttenuation*distance + pointLight.quadraticAttenuation*distance*distance);
		
		diffuseFactor = clamp(dot(f_normal,direction),0.0,1.0);
		if(diffuseFactor > 0.0){
			diffuseLight += material.diffuse*pointLight.diffuse*diffuseFactor*attenuation;
			specularFactor = clamp(dot(reflect(direction,f_normal),viewDir),0.0,1.0);
			if(specularFactor >0.00)
				specularLight += material.specular*pointLight.specular*pow(specularFactor,material.shininess)*attenuation;
		}
	}


	

	vec4 color;
	if(f_normalIndex < 3.5){
		color = texture2D(tileAtlas,vec2((fract(f_texcoord.x + f_texcoord.z)+ f_texcoord.w)*stepSize ,fract(f_texcoord.y)));
	}else{
		color = texture2D(tileAtlas,vec2((fract(f_texcoord.x) + f_texcoord.w)*stepSize ,fract(f_texcoord.z)));
	}	
	gl_FragColor = color*(diffuseLight + specularLight + ambientLight);
}


