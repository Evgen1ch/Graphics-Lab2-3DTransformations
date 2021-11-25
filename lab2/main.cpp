#include "Camera.h"
#include "GLWindow.h"
#include "Model.h"
#include "Shader.h"
#include "stb_image.h"

#include "transtormations.h"

#include <gl/GL.h>

#include "LabTransformator.h"

#define ARRAYSIZEM(arr) (sizeof(arr)) / (sizeof arr[0])

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const char* VERTEX_SHADER_PATH = "shaders\\vertex.vs";
const char* FRAGMENT_SHADER_PATH = "shaders\\fragment.fs";

//CAMERA IS HERE
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
LabTransformator transformator;

//DELTA TIME LOGIC VARIABLES
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

//MOUSE INFO NEEDED
float lastMouseX = WINDOW_WIDTH / 2.0f;
float lastMouseY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

//LOGIC CONSTANTS
const float AXES_LENGTH = 100.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
void setup_callbacks(GLFWwindow* window);
void init_glfw();
void drawAxes(Shader& axesShader, GLuint VAO, const glm::mat4& view, const glm::mat4& projection);

void processInput(GLFWwindow* window);




void makeReflection();
glm::mat4 makeRotationMatrix(RotationDirection dir, float deltaTime);

int main()
{
	init_glfw();
	const GLWindow window(WINDOW_WIDTH, WINDOW_HEIGHT, "Main Window");
	setup_callbacks(window.getGLFWHandle());
	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);
	
	glEnable(GL_DEPTH_TEST);

	Shader axesShader("shaders/axes.vs", "shaders/axes.fs");
	float axes[] = {
		-AXES_LENGTH, 0.0, 0.0,
		AXES_LENGTH, 0.0f, 0.0f,
		0.0f, AXES_LENGTH, 0.0f,
		0.0f, -AXES_LENGTH, 0.0f,
		0.0f, 0.0f, AXES_LENGTH,
		0.0f, 0.0f, -AXES_LENGTH,
	};

	GLuint axesVAO, axesVBO;

	glGenVertexArrays(1, &axesVAO);
	glGenBuffers(1, &axesVBO);

	glBindVertexArray(axesVAO);
	glBindBuffer(GL_ARRAY_BUFFER, axesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axes), axes, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
	glBindVertexArray(0);
	

	Shader shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	
	Model myModel("resources/box/box.obj");
	
	while(!glfwWindowShouldClose(window.getGLFWHandle()))
	{
		// time logic
		// ----------
		const float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		// input
		// -----
		processInput(window.getGLFWHandle());

		// game logic he-he
		// ----------------
		float angle = currentFrame;
		

		// render-render-render-render-render-render-render-render-render
		// --------------------------------------------------------------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		//setup light
		shader.setVec3("viewPos", camera.Position);
		shader.setFloat("material.shininess", 64.0f);
		shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		shader.setVec3("dirLight.ambient", 0.3f, 0.3f, 0.3f);
		shader.setVec3("dirLight.diffuse", 0.8f, 0.8f, 0.8f);
		shader.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Fov), static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), 0.1f, 100.0f);
		glm::mat4 view = camera.getViewMatrix();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		

		//// render the loaded model
		//glm::mat4 model = glm::mat4(1.0f);
		//model = translate(model, glm::vec3(-5.0f, -5.0f, 0.0f)); 
		//model = translate(model, glm::vec3(7.0f, 7.0f, 0.0f)); 
		//model = scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		////object rotaion
		//model = rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
		//shader.setMat4("model", model);
		//myModel.Draw(shader);
		
		glm::mat4 model = transformator.getTransformationMatrix();
		shader.setMat4("model", model);
		myModel.Draw(shader);
		
		/*model = mt::scale(model, glm::vec3(1.0f));
		model = mt::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		model = mt::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		myModel.Draw(shader);*/
		

		//disable shader
		glUseProgram(0);
		drawAxes(axesShader, axesVAO, view, projection);
		
		
		glfwSwapBuffers(window.getGLFWHandle());
		glfwPollEvents();
	}
	glDeleteBuffers(1, &axesVBO);
	glDeleteVertexArrays(1, &axesVAO);
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
	
	//object rotation
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		transformator.processRotation(RotationDirection::Up, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		transformator.processRotation(RotationDirection::Down, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		transformator.processRotation(RotationDirection::Left, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		transformator.processRotation(RotationDirection::Right, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		transformator.processRotation(RotationDirection::RollLeft, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		transformator.processRotation(RotationDirection::RollRight, deltaTime);

	//object movement
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		transformator.processTranslation(MovementDirection::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		transformator.processTranslation(MovementDirection::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		transformator.processTranslation(MovementDirection::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		transformator.processTranslation(MovementDirection::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		transformator.processTranslation(MovementDirection::UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		transformator.processTranslation(MovementDirection::DOWN, deltaTime);
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

glm::mat4 makeRotationMatrix(RotationDirection dir, float deltaTime)
{
	return glm::mat4(1.0f);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	if(firstMouse)
	{
		lastMouseX = xpos;
		lastMouseY = ypos;
		firstMouse = false;
	}
	const float xoffset = static_cast<float>(xpos) - lastMouseX;
	const float yoffset = lastMouseY - static_cast<float>(ypos);
	lastMouseX = static_cast<float>(xpos);
	lastMouseY = static_cast<float>(ypos);

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void setup_callbacks(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void init_glfw()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void drawAxes(Shader& axesShader, GLuint VAO, const glm::mat4& view, const glm::mat4& projection)
{
	axesShader.use();
	//draw axes
	glm::mat4 axesModel(1.0f);
	axesShader.setMat4("model", axesModel);
	axesShader.setMat4("view", view);
	axesShader.setMat4("projection", projection);
	axesShader.setVec3("OurColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 2);
	axesShader.setVec3("OurColor", glm::vec3(0.0f, 1.0f, 0.0f));
	glDrawArrays(GL_LINES, 2, 2);
	axesShader.setVec3("OurColor", glm::vec3(0.0f, 0.0f, 1.0f));
	glDrawArrays(GL_LINES, 4, 2);
	/*glDrawElements(GL_LINES, sizeof(axesIndices), GL_UNSIGNED_INT, nullptr);*/
	glBindVertexArray(0);
	//disable shader
	glUseProgram(0);
}

