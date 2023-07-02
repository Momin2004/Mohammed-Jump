#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "user.h"
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

void init();
void update();
void draw();

glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float cameraSpeed = 2.5f;

const float cubevertices[] = {
    // position           // color
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // bottom-left
    0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f, // bottom-right
    0.5f, 0.5f, -0.5f,    0.0f, 0.0f, 1.0f, // top-right
    -0.5f, 0.5f, -0.5f,   1.0f, 1.0f, 0.0f, // top-left
    -0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 1.0f, // bottom-back
    0.5f, -0.5f, 0.5f,    1.0f, 0.0f, 1.0f, // bottom-front
    0.5f, 0.5f, 0.5f,     1.0f, 1.0f, 1.0f, // top-front
    -0.5f, 0.5f, 0.5f,    0.5f, 0.5f, 0.5f  // top-back
};

const unsigned int cubeindices[] = {
    // front face
    0, 1, 2,
    2, 3, 0,
    // back face
    4, 5, 6,
    6, 7, 4,
    // left face
    0, 3, 7,
    7, 4, 0,
    // right face
    1, 2, 6,
    6, 5, 1,
    // top face
    3, 2, 6,
    6, 7, 3,
    // bottom face
    0, 1, 5,
    5, 4, 0
};

// Declare global variable for the shader program
unsigned int shaderProgram;

// Function to compile and link shaders
void compileShaders()
{
    // Vertex shader source code
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aColor;
        out vec3 color;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        void main()
        {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
            color = aColor;
        }
    )";

    // Fragment shader source code
    const char* fragmentShaderSource = R"(
        #version 330 core
        in vec3 color;
        out vec4 fragColor;
        void main()
        {
            fragColor = vec4(color, 1.0);
        }
    )";

    // Create and compile the vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create the shader program and link the shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete the shaders as they're linked into the program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


int main(void)
{
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);

    tigl::init();

    init();

	while (!glfwWindowShouldClose(window))
	{
		update();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();


    return 0;
}


void init()
{
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);
    });

    glEnable(GL_DEPTH_TEST);
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.1f, 100.0f);

    cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraSpeed = 0.05f;

}


void update()
{
    // Move the camera position
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        std::cout << "up";
        cameraPosition += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        std::cout << "down";
        cameraPosition -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        std::cout << "left";
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        std::cout << "right";
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    // Calculate the new view matrix
    glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
    tigl::shader->setViewMatrix(view);
}

void draw()
{
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    User player("models/steve/Steve.obj", "models/steve/steve.png");
    //User player("models/Tiles/Goose.obj", "models/Tiles/goose.jpg");
    player.render();
   
}