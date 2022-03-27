#include "scenebasic_uniform.h"

#include <iostream>
using std::cerr;
using std::endl;

#include <glm/gtc/matrix_transform.hpp>
using glm::vec3;
using glm::mat4;

float rotationSpeed = 1.0f;
float R = 0.0f, G = 0.0f, B = 0.0f;

int state = 0;

bool back = true;

//constructor for torus
//SceneBasic_Uniform::SceneBasic_Uniform() : torus(0.7f, 0.3f, 50, 50) {}

//constructor for teapot
SceneBasic_Uniform::SceneBasic_Uniform() : teapot(20, glm::translate(mat4(1.0f), vec3(0.0f, 1.5f, 0.25f))) {}



void SceneBasic_Uniform::initScene()
{
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
    prog.setUniform("Material.Kd", R,G,B); //seting the Kd uniform
    prog.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);     //setting the Ld uniform
    prog.setUniform("Light.Position", view * glm::vec4(5.0f, 5.0f, 2.0f, 0.0f)); //setting Light Position
}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
	//Oscilates the teapot back and forth.
    if (rotationSpeed >= -4.0f && back == true) {
        model = glm::rotate(model, glm::radians(rotationSpeed), vec3(0.0f, 0.0f, 2.0f));
        rotationSpeed = rotationSpeed - 0.02;
        if (rotationSpeed < -4.0f) back = false;
    }
    else if (rotationSpeed <= 4.0f && back == false) {
        model = glm::rotate(model, glm::radians(rotationSpeed), vec3(0.0f, 0.0f, 2.0f));
        rotationSpeed = rotationSpeed + 0.02;
        if (rotationSpeed > 4.0f) back = true;
    }
    
    //Sequentially changes the R,B and G values.
    switch (state)
    {
    case 0:
        if(R > 4.0f)
        {
            state++;
            break;
        }
        R = R + 0.02;
        break;
    case 1:
        if (G > 4.0f)
        {
            state++;
            break;
        }
        G = G + 0.02;
        break;
    case 2:
        if (B > 4.0f)
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
    //Updates the teapot's colour based on the RGB values.
    prog.setUniform("Material.Kd", R, G, B);
    
            

    
    
}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setMatrices(); //we set matrices 
    //torus.render();     //we render the torus
    teapot.render();  
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
