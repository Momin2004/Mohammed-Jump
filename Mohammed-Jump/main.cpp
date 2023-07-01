#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

void init();
void update();
void draw();

const float cubeVertices[] = {
    // Position           // Color
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // Bottom-left
    0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f, // Bottom-right
    0.5f, 0.5f, -0.5f,    0.0f, 0.0f, 1.0f, // Top-right
    -0.5f, 0.5f, -0.5f,   1.0f, 1.0f, 0.0f, // Top-left
    -0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 1.0f, // Bottom-back
    0.5f, -0.5f, 0.5f,    1.0f, 0.0f, 1.0f, // Bottom-front
    0.5f, 0.5f, 0.5f,     1.0f, 1.0f, 1.0f, // Top-front
    -0.5f, 0.5f, 0.5f,    0.5f, 0.5f, 0.5f  // Top-back
};

const unsigned int cubeIndices[] = {
    // Front face
    0, 1, 2,
    2, 3, 0,
    // Back face
    4, 5, 6,
    6, 7, 4,
    // Left face
    0, 3, 7,
    7, 4, 0,
    // Right face
    1, 2, 6,
    6, 5, 1,
    // Top face
    3, 2, 6,
    6, 7, 3,
    // Bottom face
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

}


void update()
{

}

void draw()
{
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the transformation matrices (e.g., model, view, projection)
    // ...

    // Load the cube vertices into a Vertex Buffer Object (VBO)
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // Load the cube indices into an Element Buffer Object (EBO)
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    // Set up vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Compile and link shaders (vertex shader and fragment shader)
    // ...

    // Bind the shaders
    glUseProgram(shaderProgram);

    // Draw the cube
    glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

    // Clean up
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}