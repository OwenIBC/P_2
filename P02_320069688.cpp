
// Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
// Bailón Cruz Owen Isaac 

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <glew.h>
#include <glfw3.h>

// glm
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>


#include "Mesh.h"
#include "Shader.h"
#include "Window.h"

// Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; // grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader> shaderList;

// Vertex Shaders y Fragment Shaders
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";

// Nuevos shaders de colores para la casa
static const char* vShaderRojo = "shaders/shaderrojo.vert";
static const char* vShaderVerde = "shaders/shaderverde.vert";
static const char* vShaderAzul = "shaders/shaderazul.vert";
static const char* vShaderCafe = "shaders/shadercafe.vert";
static const char* vShaderVerdeOscuro = "shaders/shaderverdeoscuro.vert";

float angulo = 0.0f;

// Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		// Base 
		0, 1, 2,  2, 3, 0,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,  0.5f, 
		 0.5f, -0.5f,  0.5f, 
		 0.5f, -0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f, 
		 0.0f,  0.5f,  0.0f  
	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 15, 18); 
	meshList.push_back(obj1);
}

// Vértices cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		0, 1, 2, 2, 3, 0, 
		1, 5, 6, 6, 2, 1, 
		7, 6, 5, 5, 4, 7, 
		4, 0, 3, 3, 7, 4, 
		4, 5, 1, 1, 0, 4, 
		3, 2, 6, 6, 7, 3  
	};

	GLfloat cubo_vertices[] = {
		
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

// Iniciales Owen Isaac Bailón Cruz (O, I, B, C)
void CrearLetrasyFiguras()
{
	// =============== O =================

	GLfloat vertO[] = {
		// Palo Izquierdo
		-0.9f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f,  -0.8f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f,  -0.8f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.9f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f,  -0.8f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  -0.9f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		// Palo Derecho
		-0.7f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f,  -0.6f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f,  -0.6f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.7f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f,  -0.6f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  -0.7f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		// Palo Arriba
		-0.8f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f,  -0.7f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f,  -0.7f, 0.8f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.8f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f,  -0.7f, 0.8f, 0.0f, 1.0f, 1.0f, 0.0f,  -0.8f, 0.8f, 0.0f, 1.0f, 1.0f, 0.0f,
		// Palo Abajo
		-0.8f, 0.6f, 0.0f, 1.0f, 1.0f, 0.0f,  -0.7f, 0.6f, 0.0f, 1.0f, 1.0f, 0.0f,  -0.7f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.8f, 0.6f, 0.0f, 1.0f, 1.0f, 0.0f,  -0.7f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  -0.8f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f
	};
	MeshColor* meshO = new MeshColor();
	meshO->CreateMeshColor(vertO, 144);
	meshColorList.push_back(meshO);

	// =============== I =================

	GLfloat vertI[] = {
		// Techo
		-0.5f, 0.9f, 0.0f, 0.0f, 1.0f, 1.0f,  -0.3f, 0.9f, 0.0f, 0.0f, 1.0f, 1.0f,  -0.3f, 0.8f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.9f, 0.0f, 0.0f, 1.0f, 1.0f,  -0.3f, 0.8f, 0.0f, 0.0f, 1.0f, 1.0f,  -0.5f, 0.8f, 0.0f, 0.0f, 1.0f, 1.0f,
		// Centro
		-0.45f, 0.8f, 0.0f, 0.0f, 1.0f, 1.0f, -0.35f, 0.8f, 0.0f, 0.0f, 1.0f, 1.0f, -0.35f, 0.6f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.45f, 0.8f, 0.0f, 0.0f, 1.0f, 1.0f, -0.35f, 0.6f, 0.0f, 0.0f, 1.0f, 1.0f, -0.45f, 0.6f, 0.0f, 0.0f, 1.0f, 1.0f,
		// Base
		-0.5f, 0.6f, 0.0f, 0.0f, 1.0f, 1.0f,  -0.3f, 0.6f, 0.0f, 0.0f, 1.0f, 1.0f,  -0.3f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.6f, 0.0f, 0.0f, 1.0f, 1.0f,  -0.3f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,  -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f
	};
	MeshColor* meshI = new MeshColor();
	meshI->CreateMeshColor(vertI, 108);
	meshColorList.push_back(meshI);

	// =============== B =================

	GLfloat vertB[] = {
		// Palo Izquierdo Principal
		-0.2f, 0.9f, 0.0f, 1.0f, 0.0f, 1.0f,  -0.1f, 0.9f, 0.0f, 1.0f, 0.0f, 1.0f,  -0.1f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.2f, 0.9f, 0.0f, 1.0f, 0.0f, 1.0f,  -0.1f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,  -0.2f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		// Palos Horizontales (Arriba, Medio, Abajo)
		-0.1f, 0.9f, 0.0f, 1.0f, 0.0f, 1.0f,   0.0f, 0.9f, 0.0f, 1.0f, 0.0f, 1.0f,   0.0f, 0.8f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.1f, 0.9f, 0.0f, 1.0f, 0.0f, 1.0f,   0.0f, 0.8f, 0.0f, 1.0f, 0.0f, 1.0f,  -0.1f, 0.8f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.1f, 0.75f, 0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.75f, 0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.65f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.1f, 0.75f, 0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.65f, 0.0f, 1.0f, 0.0f, 1.0f, -0.1f, 0.65f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.1f, 0.6f, 0.0f, 1.0f, 0.0f, 1.0f,   0.0f, 0.6f, 0.0f, 1.0f, 0.0f, 1.0f,   0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.1f, 0.6f, 0.0f, 1.0f, 0.0f, 1.0f,   0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,  -0.1f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		// Barriga de Arriba y Abajo
		 0.0f, 0.9f, 0.0f, 1.0f, 0.0f, 1.0f,   0.1f, 0.9f, 0.0f, 1.0f, 0.0f, 1.0f,   0.1f, 0.65f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.0f, 0.9f, 0.0f, 1.0f, 0.0f, 1.0f,   0.1f, 0.65f, 0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.65f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.0f, 0.75f, 0.0f, 1.0f, 0.0f, 1.0f,  0.1f, 0.75f, 0.0f, 1.0f, 0.0f, 1.0f,  0.1f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.0f, 0.75f, 0.0f, 1.0f, 0.0f, 1.0f,  0.1f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,   0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f
	};
	MeshColor* meshB = new MeshColor();
	meshB->CreateMeshColor(vertB, 216);
	meshColorList.push_back(meshB);

	// =============== C =================

	GLfloat vertC[] = {
		// Techo
		 0.2f, 0.9f, 0.0f, 1.0f, 1.0f, 1.0f,   0.5f, 0.9f, 0.0f, 1.0f, 1.0f, 1.0f,   0.5f, 0.8f, 0.0f, 1.0f, 1.0f, 1.0f,
		 0.2f, 0.9f, 0.0f, 1.0f, 1.0f, 1.0f,   0.5f, 0.8f, 0.0f, 1.0f, 1.0f, 1.0f,   0.2f, 0.8f, 0.0f, 1.0f, 1.0f, 1.0f,
		// Palo Izquierdo
		 0.2f, 0.8f, 0.0f, 1.0f, 1.0f, 1.0f,   0.3f, 0.8f, 0.0f, 1.0f, 1.0f, 1.0f,   0.3f, 0.6f, 0.0f, 1.0f, 1.0f, 1.0f,
		 0.2f, 0.8f, 0.0f, 1.0f, 1.0f, 1.0f,   0.3f, 0.6f, 0.0f, 1.0f, 1.0f, 1.0f,   0.2f, 0.6f, 0.0f, 1.0f, 1.0f, 1.0f,
		// Base
		 0.2f, 0.6f, 0.0f, 1.0f, 1.0f, 1.0f,   0.5f, 0.6f, 0.0f, 1.0f, 1.0f, 1.0f,   0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		 0.2f, 0.6f, 0.0f, 1.0f, 1.0f, 1.0f,   0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,   0.2f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f
	};
	MeshColor* meshC = new MeshColor();
	meshC->CreateMeshColor(vertC, 108);
	meshColorList.push_back(meshC);
}

void CreateShaders()
{

	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	// shader de color por VAO (letras)
	Shader* shader2 = new Shader();
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	// Rojo
	Shader* shaderRojo = new Shader();
	shaderRojo->CreateFromFiles(vShaderRojo, fShader);
	shaderList.push_back(*shaderRojo);

	// Verde
	Shader* shaderVerde = new Shader();
	shaderVerde->CreateFromFiles(vShaderVerde, fShader);
	shaderList.push_back(*shaderVerde);

	// Azul
	Shader* shaderAzul = new Shader();
	shaderAzul->CreateFromFiles(vShaderAzul, fShader);
	shaderList.push_back(*shaderAzul);

	// Café
	Shader* shaderCafe = new Shader();
	shaderCafe->CreateFromFiles(vShaderCafe, fShader);
	shaderList.push_back(*shaderCafe);

	// Verde Oscuro
	Shader* shaderVerdeOscuro = new Shader();
	shaderVerdeOscuro->CreateFromFiles(vShaderVerdeOscuro, fShader);
	shaderList.push_back(*shaderVerdeOscuro);
}

int main()
{
	mainWindow = Window(800, 800);
	mainWindow.Initialise();

	glEnable(GL_DEPTH_TEST);

	CreaPiramide(); 
	CrearCubo();    
	CrearLetrasyFiguras(); 
	CreateShaders();

	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;


	// Perspectiva para que la casa 3D se vea con profundidad real
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	glm::mat4 model(1.0);

	// Vectores de la cámara 
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	// Velocidad de movimiento
	float cameraSpeed = 0.0005f;

	float yaw = -90.0f;	
	float pitch = 0.0f;	
	float lastX = 400, lastY = 400; 
	bool firstMouse = true; 

	glfwSetInputMode(mainWindow.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	while (!mainWindow.getShouldClose())
	{
		glfwPollEvents();

		// ------------------------------------------------------------
		// 0.1. CONTROLES DE MOVIMIENTO (W, A, S, D, R, F)
		// ------------------------------------------------------------
	

		if (glfwGetKey(mainWindow.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(mainWindow.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(mainWindow.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(mainWindow.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;


		if (glfwGetKey(mainWindow.getWindow(), GLFW_KEY_R) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraUp;
		if (glfwGetKey(mainWindow.getWindow(), GLFW_KEY_F) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraUp;


		// ------------------------------------------------------------
		// 0.2. CONTROLES DE ROTACIÓN
		// ------------------------------------------------------------


		double mouseX, mouseY;
		glfwGetCursorPos(mainWindow.getWindow(), &mouseX, &mouseY);

		if (firstMouse)
		{
			lastX = (float)mouseX;
			lastY = (float)mouseY;
			firstMouse = false;
		}

		float xoffset = (float)mouseX - lastX;
		float yoffset = lastY - (float)mouseY; // Invertido ya que las coordenadas Y van de abajo hacia arriba
		lastX = (float)mouseX;
		lastY = (float)mouseY;

		float sensitivity = 0.1f; // Sensibilidad del ratón
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);

		// ------------------------------------------------------------

		// Crear la matriz de vista 
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		// Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// ------------------------------------------------------------
		// 1. RENDER DE LAS INICIALES (O, I, B, C)
		// ------------------------------------------------------------

		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		uniformView = shaderList[1].getViewLocation();
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));

		model = glm::mat4(1.0);
		
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, -4.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshColorList[0]->RenderMeshColor(); // O
		meshColorList[1]->RenderMeshColor(); // I
		meshColorList[2]->RenderMeshColor(); // B
		meshColorList[3]->RenderMeshColor(); // C

		// ------------------------------------------------------------
		// 2. RENDER DE LA CASA (Mismos colores de tu imagen de referencia)
		// ------------------------------------------------------------

		// --- BASE DE LA CASA --
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		uniformView = shaderList[2].getViewLocation();
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, -4.0f));
		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f)); 
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		// --- TECHO (Pirámide, Azul) ---
		shaderList[4].useShader(); 
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		uniformView = shaderList[4].getViewLocation();
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.45f, -4.0f));
		model = glm::scale(model, glm::vec3(1.5f, 0.7f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		// --- PUERTA (Cubo, Verde) ---
		shaderList[3].useShader(); 
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		uniformView = shaderList[3].getViewLocation();
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.7f, -3.39f));
		model = glm::scale(model, glm::vec3(0.3f, 0.6f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		// --- VENTANAS ---

		// Ventana 1 (Izquierda)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.35f, -0.1f, -3.39f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		// Ventana 2 (Derecha)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.35f, -0.1f, -3.39f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		// ------------------------------------------------------------
		// 3. RENDER DE LOS ÁRBOLES (Nuevos)
		// ------------------------------------------------------------

		// --- TRONCOS ---
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		uniformView = shaderList[5].getViewLocation();
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));

		// Tronco 1 (Izquierdo)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.3f, -0.8f, -4.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		// Tronco 2 (Derecho)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.3f, -0.8f, -4.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		// --- HOJAS DE LOS ÁRBOLES ---
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		uniformView = shaderList[6].getViewLocation();
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));

		// Hojas 1 (Izquierdas)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.3f, -0.3f, -4.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.8f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); // meshList[0] es la pirámide

		// Hojas 2 (Derechas)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.3f, -0.3f, -4.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.8f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); 


		// ------------------------------------------------------------
		// 4. RENDER DEL CÉSPED / SUELO 
		// ------------------------------------------------------------

		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		uniformView = shaderList[6].getViewLocation();

		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(0.0f, -0.95f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 0.1f, 4.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));


		meshList[1]->RenderMesh();


		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}