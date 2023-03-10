// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace glm;

#include <common/shader.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/texture.hpp>

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
glm::vec3 camera_position   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_up    = glm::vec3(0.0f, 1.0f,  0.0f);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//rotation
float angle = 0.;
float angleSun = 0.;
float angleEarth = 0.;
float angleMoon = 0.;
float zoom = 1.;

//Model updated
mat4 newMod = mat4(1.f);

// Our light
struct Light {
    vec3 position;
    vec3 color;

    void setLight(){
        color = vec3 (300, 300, 300);
    }
}; 

Light light;

/*******************************************************************************/

void createPlan(std::vector<unsigned short>& indices, std::vector<std::vector<unsigned short>>& triangles, std::vector<glm::vec3>& indexed_vertices, std::vector<float>& uv, float step){

    indices.clear();
    uv.clear();
    indexed_vertices.clear();

    int nbSommets = 10;

    srand(time(NULL));

    for (int i = 0; i < nbSommets-1; ++i){
        for (int j = 0; j < nbSommets-1; ++j)
        {
            indices.push_back(i * nbSommets + j);
            indices.push_back(i * nbSommets+ j + 1);
            indices.push_back((i+1) * nbSommets + j);

            indices.push_back(i* nbSommets + j + 1);
            indices.push_back((i+1) * nbSommets + j + 1);
            indices.push_back((i+1) * nbSommets + j);
        }
    }

    for(int i = 0; i < nbSommets; i++){
        for(int j = 0; j < nbSommets; j++){
            indexed_vertices.push_back(glm::vec3((float)j*step,(float)i*step,0 ));

            uv.push_back((float)j/(nbSommets-1));
            uv.push_back((float)i/(nbSommets-1));
        }
    }
}

// Calcul du barycentre
vec3 calculBarycentre(std::vector<glm::vec3>& indexed_vertices){
		vec3 barycentre = vec3(0.0f);
		for(int i=0; i < indexed_vertices.size(); i++)
			barycentre += indexed_vertices[i];
		
		return barycentre /= (float) indexed_vertices.size();
}

// Calcul des uv d'une sph??re
void calculUVSphere(std::vector<glm::vec3>& indexed_vertices, std::vector<float>& uv){
    uv.clear();
    for(unsigned int i = 0; i < indexed_vertices.size(); i++){
        vec3 n = normalize(indexed_vertices[i] - calculBarycentre(indexed_vertices));
        float u = std::atan2(n[0],n[2]) / (float)(2 * M_PI) + 0.5;
        float v = n[1] * 0.5 + 0.5;
        uv.push_back(u);
        uv.push_back(v);
    }
}

void loadUV(std::vector<float> uv, GLuint programID){
    GLuint uvbuffer;
    glGenBuffers(1,&uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER,uvbuffer);
    glBufferData(GL_ARRAY_BUFFER,uv.size()*sizeof(float),&uv[0],GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,uvbuffer);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,(void*)0);
}

void loadTexture2D(char* texture_name, GLuint programID){
    GLuint texture = loadBMP_custom(texture_name);
    GLuint textureID = glGetUniformLocation(programID,"textureSampler");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureID, 0);
}

void loadHeightMap(char* texture_name, GLuint programID){
    GLuint heightmap = loadBMP_custom(texture_name);
    GLuint heightmapID = glGetUniformLocation(programID,"heightMapSampler");

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,heightmap);
    glUniform1i(heightmapID,1);
}

void loadNormalMap(char* texture_name, GLuint programID){
    GLuint normalMap = loadBMP_custom(texture_name);
    GLuint normalMapID = glGetUniformLocation(programID,"NormalMapSampler");

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D,normalMap);
    glUniform1i(normalMapID,1);
}

int main( void )
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "TP4 - Transformations", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    //  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

    // Dark blue background
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    //glEnable(GL_CULL_FACE);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl" );

    /*****************TODO***********************/
    // Get a handle for our "Model View Projection" matrices uniforms

    /****************************************/
    std::vector<unsigned short> indices; //Triangles concat??n??s dans une liste
    std::vector<std::vector<unsigned short> > triangles;
    std::vector<glm::vec3> indexed_vertices;
    std::vector<float> uv;

    float step = 2. / 10.;

    //Chargement du fichier de maillage
    std::string filename("sphere.off");
    loadOFF(filename, indexed_vertices, indices, triangles );
    calculUVSphere(indexed_vertices, uv);

    // createPlan(indices, triangles, indexed_vertices, uv, step);
    loadUV(uv, programID);
    loadNormalMap( "normal.bmp", programID);
    loadTexture2D( "puech.bmp", programID);

    // Initialisation de la lumi??re
    light.setLight();
    glUniform3fv(glGetUniformLocation(programID, "lightPosition"), 1, &light.position[0]); 
    glUniform3fv(glGetUniformLocation(programID, "lightColor"), 1, &light.color[0]);
    glUniform3f(glGetUniformLocation(programID, "viewPos"), camera_position.x, camera_position.y, camera_position.z);
    

    // Load it into a VBO
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

    // Generate a buffer for the indices as well
    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

    // Get a handle for our "LightPosition" uniform
    glUseProgram(programID);
    GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
   

    // For speed computation
    double lastTime = glfwGetTime();
    int nbFrames = 0;

    do{

        // Measure speed
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // glfwSetInputMode
        // -----
        processInput(window);


        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);


        /*****************TODO***********************/
        // Model matrix : an identity matrix (model will be at the origin) then change

        // View matrix : camera/view transformation lookat() utiliser camera_position camera_target camera_up

        // Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units

        // Send our transformation to the currently bound shader,
        // in the "Model View Projection" to the shader uniforms

        /****************************************/
        // -- PREMIERE CHAISE --
        mat4 model = mat4(1.0f);
        
        mat4 view = glm::lookAt(camera_position, camera_position + camera_target, camera_up);
        mat4 projection = glm::perspective<float>(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);

        // model = rotate(model, glm::radians(130.0f), vec3(1.,0.,0.));
        model = translate(model, vec3(-1.,-1.,0.));

        mat4 mvp =  projection * view * model;

        GLuint mvpID = glGetUniformLocation(programID, "mvp");
        glUniformMatrix4fv(mvpID,1,GL_FALSE, &mvp[0][0]);

        // // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                    0,                  // attribute
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                    );

        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

        // // Draw the triangles !
        glDrawElements(
                    GL_TRIANGLES,      // mode
                    indices.size(),    // count
                    GL_UNSIGNED_SHORT,   // type
                    (void*)0           // element array buffer offset
                    );


        glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &elementbuffer);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //Camera zoom in and out
    float cameraSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera_position += cameraSpeed * camera_target;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera_position -= cameraSpeed * camera_target;

    //Camera translations
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera_position -= glm::normalize(glm::cross(camera_target, camera_up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera_position += glm::normalize(glm::cross(camera_target, camera_up)) * cameraSpeed;

    //SCALE OBJECT
    if(glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
        newMod = glm::scale(newMod,vec3(0.9,0.9,0.9));

    if(glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
        newMod = glm::scale(newMod,vec3(1.1,1.1,1.1));

    //TRANSLATION OBJECT
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        newMod = glm::translate(newMod, vec3(-0.1,0.,0.));

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        newMod = glm::translate(newMod, vec3(0.1,0.,0.));

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        newMod = glm::translate(newMod, vec3(0.,-0.1,0.));

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        newMod = glm::translate(newMod, vec3(0.,0.1,0.));

    //rotation
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
        angle += 5;
    }

    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
        angle -= 5;
    }

    // ACTIVATE / DESACTIVATE MODE LINE POLYGONMODE
    if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  

    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
