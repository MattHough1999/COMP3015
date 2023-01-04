#version 460

//in variable that receives the diffuse calculation from the vertex shader
in vec3 position;
in vec3 normal;
//out variable, this typical for all fragment shaders
layout (location = 0) out vec4 FragColor;
 
 //light information struct
uniform struct LightInfo 
{
  vec4 Position;		//Light position
  vec3 La;				//Ambient
  vec3 L;				//Diffuse and specular
} Lights[3];

//material information struct
uniform struct MaterialInfo 
{
  vec3 Ka;				//Ambient 
  vec3 Kd;				//Diffuse 
  vec3 Ks;				//Specular 
  float Shininess;		//Specular shininess factor
} Material;

 vec3 phongModel(int light,vec3 pos, vec3 n)
 {
	//calculate ambient here
	vec3 ambient = Lights[light].La * Material.Ka;

	//calculate diffuse here
	 vec3 s = normalize(vec3(Lights[light].Position) - pos);
	 float sDotN = max( dot(s,n), 0.0 );
	 vec3 diffuse = Material.Kd * sDotN;

	//calculate specular here
	 vec3 spec = vec3(0.0);
	if( sDotN > 0.0 )
	{
	 vec3 v = normalize(-position.xyz);
	 vec3 r = reflect( -s, n );
	 spec = Material.Ks * pow( max( dot(r,v), 0.0 ), Material.Shininess );
	}

	 return ambient + Lights[light].L * (diffuse + spec);
 }
void main()
{
	for(int i = 0; i<3; i++) 
	{
		FragColor = vec4(phongModel(i,position, normal), 1.0);
	}
}


