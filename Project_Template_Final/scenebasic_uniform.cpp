#include <sstream>:
#include "scenebasic_uniform.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <./gl/glut.h>
#include "helper/texture.h"
//#include <GLFW/glfw3.h>


using std::cerr;
using std::endl;
using glm::vec3;
using glm::mat4;
float rotationSpeed = 1.0f;
float R = 0.0f, G = 0.0f, B = 0.0f;
int state = 0;
bool meshPresent,back = true;

/*
SceneBasic_Uniform::SceneBasic_Uniform() : torus(0.7f, 0.3f, 50, 50), teapot(20, glm::translate(mat4(1.0f), vec3(0.0f, 1.5f, 0.25f))) plane(4.0f, 4.0f, 2, 2)
{
    //pigMesh = ObjMesh::loadWithAdjacency("../Project_Template_Final/media/pig_triangulated.obj",true);
    
    newMesh = ObjMesh::loadWithAdjacency("../Project_Template_Final/media/newModel.obj", true);
    
}

*/
SceneBasic_Uniform::SceneBasic_Uniform() : cube(0.1f)
{

}

void SceneBasic_Uniform::initScene()
{
    
/*
    compile();
	glEnable(GL_DEPTH_TEST);
   
    //initialise the model matrix
    model = mat4(1.0f);
    
    //Places the Teapot in the view model.
    model = glm::translate(model, vec3(0.0, -1.0, 0.0));
    model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(30.0f), vec3(0.0f, 0.0f, 1.0f));
    view = glm::lookAt(vec3(4.0f, 4.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

    projection = mat4(1.0f);

    //make sure you use the correct name, check your vertex shader
    prog.setUniform("Material.Ks", R, G, B);
    prog.setUniform("Material.Ka", R, G, B);
    prog.setUniform("Material.Kd", R,G,B);
    prog.setUniform("Material.Shininess", 0.05f) ;//seting the Kd uniform
    prog.setUniform("Lights.La", 1.0f, 1.0f, 1.0f);     //setting the Ld uniform
    prog.setUniform("Lights.L", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Lights.Position", view * glm::vec4(5.0f, 5.0f, 2.0f, 0.0f)); //setting Light Position

*/
    compile();
    glEnable(GL_DEPTH_TEST);
    view = glm::lookAt(vec3(1.0f, 1.25f, 1.25f), vec3(0.0f, 0.0f, 0.0f),
        vec3(0.0f, 1.0f, 0.0f));
    /*
    view = glm::lookAt(vec3(0.5f, 0.75f, 0.75f), vec3(0.0f, 0.0f, 0.0f),
        vec3(0.0f, 1.0f, 0.0f));
        */
    projection = mat4(1.0f);
    float x, z;
    for (int i = 0; i < 3; i++)
    {
        std::stringstream name;
        name << "Lights[" << i << "].Position";
        x = 2.0f * cosf((glm::two_pi<float>() / 3) * i);
        z = 2.0f * sinf((glm::two_pi<float>() / 3) * i);
        prog.setUniform(name.str().c_str(), view * glm::vec4(x, 1.2f, z +
            1.0f, 1.0f));
    }

    prog.setUniform("Lights[0].L", vec3(1.0f, 1.0f, 1.8f));
    prog.setUniform("Lights[1].L", vec3(1.0f, 1.8f, 1.0f));
    prog.setUniform("Lights[2].L", vec3(1.8f, 1.0f, 1.0f));
    prog.setUniform("Lights[0].La", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Lights[1].La", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Lights[2].La", 1.0f, 1.0f, 1.0f);

    GLuint texID = Texture::loadTexture("../Project_Template_Final/media/texture/brick1.jpg");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texID);
}



void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/phong.vert");
		prog.compileShader("shader/phong.frag");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
    
    //glutKeyboardFunc(void(*callback)(unsigned char,int,int))
    
	//Oscilates the teapot back and forth.
    if (rotationSpeed >= -180.0f && back == true) {
        //model = glm::rotate(model, glm::radians(rotationSpeed), vec3(0.0f, 0.0f, 2.0f));
        rotationSpeed = rotationSpeed - 1;
        if (rotationSpeed < -180.0f) back = false;
    }
    else if (rotationSpeed <= 180.0f && back == false) {
        //model = glm::rotate(model, glm::radians(rotationSpeed), vec3(0.0f, 0.0f, 2.0f));
        rotationSpeed = rotationSpeed + 1;
        if (rotationSpeed > 180.0f) back = true;
    }
    
    
    //Sequentially changes the R,B and G values.
    switch (state)
    {
    case 0:
        if(R > 1.0f)
        {
            state++;
            break;
        }
        R = R + 0.02;
        break;
    case 1:
        if (G > 1.0f)
        {
            state++;
            break;
        }
        G = G + 0.02;
        break;
    case 2:
        if (B > 1.0f)
        {
            state++;
            break;
        }
        B = B + 0.02;
        break;
    case 3:
        if (R <= 0.1f)
        {
            state++;
            break;
        }
        R = R - 0.02;
        break;
    case 4:
        if (B <= 0.1f)
        {
            state++;
            break;
        }
        B = B - 0.02;
        break;
    case 5:
        if (G <= 0.1f)
        {
            state = 0;
            break;
        }
        G = G - 0.02;
        break;
    }
    
            

    
    
}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    /*
    
    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    //prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Ka", R, G, B);
    prog.setUniform("Material.Shininess", 180.0f);

    model = mat4(1.0f);
    model = glm::scale(model, vec3(0.5f, 0.5f, 0.5f));
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(0.0f, 1.00f, 0.0f));
    model = glm::rotate(model, glm::radians(rotationSpeed), vec3(0.0f, 2.0f, 0.0f));
    setMatrices();
    newMesh->render();
    
    //New Mesh uniforms and translations
        
    prog.setUniform("Material.Kd", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 180.0f);
    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, -0.45f, 0.0f));
    setMatrices();
    plane.render();

    
    prog.setUniform("Material.Kd", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 180.0f);
    model = mat4(1.0f);
    model = glm::translate(model, vec3(-0.25f, -0.70f, -0.2f));
    model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
    setMatrices(); //we set matrices 
    torus.render();
    /*
    prog.setUniform("Material.Kd", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 180.0f);
    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, -0.45f, 0.0f));
    setMatrices(); //we render the torus
    teapot.render();  
    */
    prog.setUniform("Material.Kd", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 180.0f);
    cube.render();
}

void SceneBasic_Uniform::setMatrices()
{
    mat4 mv = view * model; //we create a model view matrix
    
    prog.setUniform("ModelViewMatrix", mv); //set the uniform for the model view matrix
    
    prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]))); //we set the uniform for normal matrix
    
    prog.setUniform("MVP", projection * mv); //we set the model view matrix by multiplying the mv with the projection matrix
}

void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}

