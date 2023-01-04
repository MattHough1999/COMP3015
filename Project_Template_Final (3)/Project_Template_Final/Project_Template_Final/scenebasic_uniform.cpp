#include <sstream>:
#include "scenebasic_uniform.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

using std::cerr;
using std::endl;
using glm::vec3;
using glm::mat4;
float rotationSpeed = 1.0f;
float R = 0.0f, G = 0.0f, B = 0.0f;
int state = 0;
bool meshPresent,back = true;

SceneBasic_Uniform::SceneBasic_Uniform() : torus(0.7f, 0.3f, 50, 50), plane(4.0f, 4.0f, 2, 2)
{
    newMesh = ObjMesh::loadWithAdjacency("media/newModel.obj", true);
}

void SceneBasic_Uniform::initScene()
{
    compile();
    glEnable(GL_DEPTH_TEST);

    view = glm::lookAt(vec3(0.5f, 0.75f, 0.75f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    projection = mat4(1.0f);
    float x = 2, z = 2;
    
    for (int i = 0; i < 3; i++)
    {
        std::stringstream namePos;
        std::stringstream nameL;
        namePos << "Lights[" << i << "].Position";
        nameL << "Lights[" << i << "].L";
        x = 2.0f * cosf((glm::two_pi<float>() / 3) * i);
        z = 2.0f * sinf((glm::two_pi<float>() / 3) * i);
        prog.setUniform(namePos.str().c_str(), view * glm::vec4(x, 1.2f, z + 1.0f, 1.0f));
        prog.setUniform(nameL.str().c_str(), vec3(1.0f, 1.0f, 1.0f));
    }

    prog.setUniform("Lights[0].La", 1.0f, 1.0f, 1.8f);
    prog.setUniform("Lights[1].La", 1.8f, 1.8f, 1.0f);
    prog.setUniform("Lights[2].La", 1.8f, 1.0f, 1.0f);
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
	//Oscilates the model back and forth.

    if (rotationSpeed >= -180.0f && back == true) 
    {
        rotationSpeed = rotationSpeed - 1;
        if (rotationSpeed < -180.0f) back = false;
    }
    else if (rotationSpeed <= 180.0f && back == false) 
    {
        rotationSpeed = rotationSpeed + 1;
        if (rotationSpeed > 180.0f) back = true;
    }
    
    //Sequentially changes the R,B,G values.
    switch (state)
    {
    case 0:
        if(R > 1.0f)
        {
            state++;
            break;
        }
        R = R + 0.01;
        break;
    case 1:
        if (G > 1.0f)
        {
            state++;
            break;
        }
        G = G + 0.01;
        break;
    case 2:
        if (B > 1.0f)
        {
            state++;
            break;
        }
        B = B + 0.01;
        break;
    case 3:
        if (R <= 0.1f)
        {
            state++;
            break;
        }
        R = R - 0.01;
        break;
    case 4:
        if (B <= 0.1f)
        {
            state++;
            break;
        }
        B = B - 0.01;
        break;
    case 5:
        if (G <= 0.1f)
        {
            state = 0;
            break;
        }
        G = G - 0.01;
        break;
    }
}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //New Mesh uniforms and translations
    
    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", R * 0.8, G * 0.8, B * 0.8);
    prog.setUniform("Material.Shininess", 180.0f);
    
    model = mat4(1.0f);
    model = glm::scale(model, vec3(0.5f, 0.5f, 0.5f));
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotationSpeed), vec3(0.0f, 2.0f, 0.0f));
    setMatrices();
    newMesh->render();
    
    //Plane uniforms and translations
   
    prog.setUniform("Material.Kd", 0.6f, 0.6f, 0.6f);
    prog.setUniform("Material.Ks", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Ka", 0.1f, 0.3f, 0.3f);
    prog.setUniform("Material.Shininess", 10.0f);
    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, -0.45f, 0.0f));
    setMatrices();
    plane.render();

    //Torus uniforms and translations
    
    prog.setUniform("Material.Kd", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Ks", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 280.0f);
    model = mat4(1.0f);
    model = glm::translate(model, vec3(-0.25f, -0.70f, -0.3f));
    model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
    setMatrices(); 
    torus.render();
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

