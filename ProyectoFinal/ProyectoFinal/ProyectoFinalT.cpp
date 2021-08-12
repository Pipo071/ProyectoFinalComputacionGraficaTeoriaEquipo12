#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void animacion();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT, i = 0, j = 0, k = 0;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 10.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float range = 0.0f;
float rot = 0.0f;


// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni(1.0f, 0.0f, 0.0f);
bool active;



//Animacion Ave
glm::vec3 PosIniAve(-50.0f, 0.0f, 10.0f);
float movKitAvX = 0.0;
float movKitAvZ = 0.0;
float rotKitAv = 90.0;
float rotKitAI = 0.0;
bool circuitoAve = false;
bool recorrido1Av = true;
bool recorrido2Av = false;
bool recorrido3Av = false;
bool recorrido4Av = false;
bool recorrido5Av = false;


//Animacion tiro a canasta
glm::vec3 PosIniBalon (5.7f, 2.6f, 139.95f);
float rotBrazo = 45.0;
bool accionTiro = false;
bool sentido_1R = true;
bool sentido_2R = false;
bool sentido_3R = false;
bool accionBalon = false;
bool recorridoB1 = true;
bool recorridoB2 = false;
bool recorridoB3 = false;
bool recorridoB4 = false;
bool recorridoB5 = false;
bool recorridoB6 = false;
float movKitBX = 0.0;
float movKitBY = 0.0;
int control = 0;


//Animacion de recorrido de carros antes y despues de chocar
float movKitX = 0.0;
float movKitZ = 0.0;
float movKitY = 0.0;
float movKitX2 = 0.0;
float movKitY2 = 0.0;
float movKitZ2 = 0.0;
float movKitX3 = 0.0;
float movKitY3 = 0.0;
float movKitZ3 = 0.0;
float movKitX4 = 0.0;
float movKitY4 = 0.0;
float movKitZ4 = 0.0;
float movKitX5 = 0.0;
float movKitY5 = 0.0;
float movKitZ5 = 0.0;
float rotKitX = 0.0;
float rotKitY = 0.0;
float rotKitZ = 0.0;
float rotKitX2 = 0.0;
float rotKitY2 = 0.0;
float rotKitZ2 = 0.0;
float rotKitX3 = 0.0;
float rotKitY3 = 0.0;
float rotKitZ3 = 0.0;
float rotKitX4 = 0.0;
float rotKitY4 = 0.0;
float rotKitZ4 = 0.0;
float rotKitA = 0.0;
float rotKitB = 0.0;
float rotKitC = 0.0;
bool circuito = false;
bool circuito2 = false;
bool circuito3 = false;
bool circuito4 = false;
bool circuitoDog = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = false;
bool recorrido6 = false;
bool recorrido7 = false;
bool recorrido8 = false;
bool recorrido9 = true;
bool recorrido10 = false;
bool recorrido11 = false;
bool recorrido12 = false;
bool recorrido13 = false;
bool recorrido14 = false;
bool recorrido15 = true;
bool recorrido16 = false;
bool recorrido17 = false;
bool recorrido18 = false;
bool recorrido19 = false;
bool recorrido20 = false;
bool recorrido21 = false;
bool recorrido22 = false;
bool recorrido23 = false;
bool recorrido24 = false;
bool recorrido25 = true;
bool recorrido26 = false;
bool recorrido27 = false;
bool recorrido28 = false;
bool recorrido29 = false;
bool recorrido30 = false;
bool recorrido31 = false;
bool recorrido32 = false;
bool recorrido33 = true;
bool recorrido34 = false;
bool recorrido35 = false;
bool recorrido36 = false;
bool recorrido37 = false;
bool recorrido38 = false;
bool recorrido39 = false;
bool recorrido40 = false;


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// Keyframes
float posX = PosIni.x, posY = PosIni.y, posZ = PosIni.z, PTIzq = 0, PTDer = 0, PEIzq = 0, PEDer = 0, rotKitAD=0;

#define MAX_FRAMES 9
int i_max_steps = 190;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float PTIzq;
	float PTDer;
	float PEIzq;
	float PEDer;
	float rotIncD;
	float rotIncD2;
	float rotIncD3;
	float rotIncD4;
	float rotAD;
	float rotKitAD;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

glm::vec3 LightP1;




void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].PTIzq = PTIzq;
	KeyFrame[FrameIndex].PTDer = PTDer;
	KeyFrame[FrameIndex].PEIzq = PEIzq;
	KeyFrame[FrameIndex].PEDer = PEDer;


	KeyFrame[FrameIndex].rotKitAD = rotKitAD;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	PTIzq = KeyFrame[0].PTIzq;
	PTDer = KeyFrame[0].PTDer;
	PEIzq = KeyFrame[0].PEIzq;
	PEDer = KeyFrame[0].PEDer;


	rotKitAD = KeyFrame[0].rotKitAD;

}

void interpolation(void)
{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	KeyFrame[playIndex].rotIncD = (KeyFrame[playIndex + 1].PTIzq - KeyFrame[playIndex].PTIzq) / i_max_steps;
	KeyFrame[playIndex].rotIncD2 = (KeyFrame[playIndex + 1].PTDer - KeyFrame[playIndex].PTDer) / i_max_steps;
	KeyFrame[playIndex].rotIncD3 = (KeyFrame[playIndex + 1].PEIzq - KeyFrame[playIndex].PEIzq) / i_max_steps;
	KeyFrame[playIndex].rotIncD4 = (KeyFrame[playIndex + 1].PEDer - KeyFrame[playIndex].PEDer) / i_max_steps;

	KeyFrame[playIndex].rotAD = (KeyFrame[playIndex + 1].rotKitAD - KeyFrame[playIndex].rotKitAD) / i_max_steps;

	
}




int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final Equipo 12", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	printf("%f", glfwGetTime());

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
	Shader shader("Shaders/modelLoading.vs", "Shaders/modelLoading.frag");

	Model Balon((char*)"Models/Balon/Balon.obj");
	Model Parque((char*)"Models/Park/Parque.obj");
	Model Casa1((char*)"Models/Casa/casa1.obj");
	Model Casa2((char*)"Models/Casa/casa2.obj");
	Model Casa3((char*)"Models/Casa/casa3.obj");
	Model Casa4((char*)"Models/Casa/casa4.obj");
	Model Piso((char*)"Models/Piso/Piso.obj");
	Model Ave((char*)"Models/Pajaro/PajaroCuerpo.obj");
	Model AlaD((char*)"Models/Pajaro/AlaD.obj");
	Model AlaI((char*)"Models/Pajaro/AlaI.obj");
	Model Cancha((char*)"Models/Tirador/tC.obj");
	Model Brazo((char*)"Models/Tirador/brazoT.obj");
	Model Brazo2((char*)"Models/Tirador/brazoT2.obj");
	Model Carro1((char*)"Models/Auto1/Auto1.obj");
	Model Carro2((char*)"Models/Auto2/Auto2.obj");
	Model Grua((char*)"Models/Grua/Grua.obj");
	Model Chocado1((char*)"Models/Auto1/Choque1.obj");
	Model Chocado2((char*)"Models/Auto2/Choque2.obj");
	Model Llanta1((char*)"Models/Auto1/Llanta1.obj");
	Model Llanta2((char*)"Models/Auto1/Llanta1.obj");
	Model LlantaG((char*)"Models/Grua/LlantaG.obj");
	Model Gancho1((char*)"Models/Grua/Gancho1.obj");
	Model Gancho2((char*)"Models/Grua/Gancho2.obj");
	Model Gancho3((char*)"Models/Grua/Gancho3.obj");
	Model Perro((char*)"Models/Perro/CuerpoPe.obj");
	Model PEI((char*)"Models/Perro/PataEIz.obj");
	Model PED((char*)"Models/Perro/PataEDe.obj");
	Model PTI((char*)"Models/Perro/PataTIz.obj");
	Model PTD((char*)"Models/Perro/PataTDe.obj");
	Model Plev((char*)"Models/Perro/PataLevan.obj");
	Model Nada((char*)"Models/Nada/Nada.obj");
	Model Carrochoca1[2] = { Carro1,Chocado1 };
	Model Carrochoca2[2] = { Carro2,Chocado2 };
	Model LlantasA1[2] = { Llanta1,Nada };
	Model LlantasA2[2] = { Llanta2,Nada };
	Model Gancho[3] = { Gancho1,Gancho3,Gancho2 };
	Model Pipi[2] = { PTD,Plev };





	//Model BotaDer((char*)"Models/Personaje/bota.obj");
	//Model PiernaDer((char*)"Models/Personaje/piernader.obj");
	//Model PiernaIzq((char*)"Models/Personaje/piernaizq.obj");
	//Model Torso((char*)"Models/Personaje/torso.obj");
	//Model BrazoDer((char*)"Models/Personaje/brazoder.obj");
	//Model BrazoIzq((char*)"Models/Personaje/brazoizq.obj");
	//Model Cabeza((char*)"Models/Personaje/cabeza.obj");
	// Build and compile our shader program

	//Inicialización de KeyFrames

	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].PTIzq = 0;
		KeyFrame[i].PTDer = 0;
		KeyFrame[i].PEIzq = 0;
		KeyFrame[i].PEDer = 0;
		KeyFrame[i].rotIncD = 0;
		KeyFrame[i].rotIncD2 = 0;
		KeyFrame[i].rotIncD3 = 0;
		KeyFrame[i].rotIncD4 = 0;
		KeyFrame[i].rotAD = 0;
		KeyFrame[i].rotKitAD = 0;
	}



	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		// Positions            // Normals              // Texture Coords
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
	};


	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};

	// Positions all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	//SkyBox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	// Load textures
	vector<const GLchar*> faces;
	faces.push_back("SkyB/right.tga");
	faces.push_back("SkyB/left.tga");
	faces.push_back("SkyB/top.tga");
	faces.push_back("SkyB/bottom.tga");
	faces.push_back("SkyB/back.tga");
	faces.push_back("SkyB/front.tga");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	//texturas paredes
	GLuint texture1, texture2, texture3, texture4;
	glGenTextures(1, &texture1);
	glGenTextures(1, &texture2);
	glGenTextures(1, &texture3);
	glGenTextures(1, &texture4);

	int textureWidth, textureHeight, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	// Diffuse map
	image = stbi_load("images/pared.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);

	image = stbi_load("images/pared2.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);

	image = stbi_load("images/pared3.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);

	// Specular map
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	image = stbi_load("images/container2_specular.png", &textureWidth, &textureHeight, &nrChannels, 0);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);

	glBindTexture(GL_TEXTURE_2D, 0);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);


	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);



	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		animacion();


		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
		// == ==========================
		// Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		// the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		// by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		// by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
		// == ==========================
		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);


		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), LightP1.x, LightP1.y, LightP1.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), LightP1.x, LightP1.y, LightP1.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.032f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 1.0f, 1.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.032f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.032f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 1.0f, 0.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 0.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.032f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();


		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		// Bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);


		glBindVertexArray(VAO);
		glm::mat4 tmp = glm::mat4(1.0f); //Temp


		//Carga de modelo 
		glm::mat4 model(1);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 7.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 14.0f, 8.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture3);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(18.0f, 7.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 14.0f, 8.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-18.0f, 7.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 14.0f, 8.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture4);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 12, 0.0f));
		model = glm::scale(model, glm::vec3(40.0f, 2.0f, 7.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Parque
		view = camera.GetViewMatrix();
		glm::mat4 model2(1);
		tmp = model2 = glm::translate(model2, glm::vec3(0, 0, 0));
		model2 = glm::translate(model2, glm::vec3(0.0f, 0.0f, 45.0f));
		//model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
		model2 = glm::scale(model2, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		Parque.Draw(lightingShader);


		////Balon
		//view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		//tmp = model = glm::translate(model, glm::vec3(0, 0, 0));
		//model = glm::translate(model, glm::vec3(0.0f, 1.0f, 15.0f));
		////model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
		//model = glm::scale(model, glm::vec3(0.025f, 0.05f, 0.025f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Balon.Draw(lightingShader);

		//Casa1
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		tmp = model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::translate(model, glm::vec3(55.0f, 0.0f, 20.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa1.Draw(lightingShader);

		//Casa2
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		tmp = model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::translate(model, glm::vec3(55.0f, 0.0f, 45.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa2.Draw(lightingShader);

		//Casa3
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		tmp = model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::translate(model, glm::vec3(55.0f, 0.0f, 70.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa3.Draw(lightingShader);

		//Casa4
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		tmp = model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::translate(model, glm::vec3(30.0f, 0.0f, 105.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa1.Draw(lightingShader);

		//Casa5
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		tmp = model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::translate(model, glm::vec3(10.0f, 0.0f, 105.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa2.Draw(lightingShader);

		//Casa6
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		tmp = model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 105.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa3.Draw(lightingShader);

		//Casa7
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		tmp = model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::translate(model, glm::vec3(-30.0f, 0.0f, 105.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa4.Draw(lightingShader);

		//Casa8
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		tmp = model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::translate(model, glm::vec3(-55.0f, 0.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa3.Draw(lightingShader);

		//Casa9
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		tmp = model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::translate(model, glm::vec3(-55.0f, 0.0f, 45.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa2.Draw(lightingShader);

		//Casa10
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		tmp = model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::translate(model, glm::vec3(-55.0f, 0.0f, 70.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa1.Draw(lightingShader);

		////Ave

		view = camera.GetViewMatrix();
		glm::mat4 model3(1);
		model3 = glm::translate(model3, PosIniAve + glm::vec3(movKitAvX, 30.0f, movKitAvZ));
		model3 = glm::rotate(model3, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model3 = glm::rotate(model3, glm::radians(rotKitAv), glm::vec3(0.0f, 1.0f, 0.0f));
		model3 = glm::scale(model3, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model3));
		Ave.Draw(lightingShader);


		//Ala Derecha
		view = camera.GetViewMatrix();
		//model3 = glm::translate(model3, glm::vec3(1.15f, 3.142f, -1.38f));
		model3 = glm::translate(model3, glm::vec3(0.0f, 0.0f, 0.0f));
		model3 = glm::rotate(model3, glm::radians(rotKitAD), glm::vec3(0.0f, 0.0f, 1.0f));
		model3 = glm::scale(model3, glm::vec3(1, 1, 1));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model3));
		AlaD.Draw(lightingShader);

		//Ala Izquierda
		view = camera.GetViewMatrix();
		//model3 = glm::translate(model3, glm::vec3(1.15f, 3.142f, -1.38f));
		model3 = glm::translate(model3, glm::vec3(0.0f, 0.0f, 0.0f));
		//model3 = glm::rotate(model3, glm::radians(-rotKitAD), glm::vec3(0.0f, 0.0f, 1.0));
		model3 = glm::scale(model3, glm::vec3(1, 1, 1));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model3));
		AlaI.Draw(lightingShader);

		//Piso
		view = camera.GetViewMatrix();
		glm::mat4 model4(1);
		model4 = glm::translate(model4, glm::vec3(0, 0, 0));
		model4 = glm::translate(model4, glm::vec3(0.0f, 0.0f, 0.0f));
		model4 = glm::rotate(model4, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model4 = glm::scale(model4, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model4));
		Piso.Draw(lightingShader);


		//Cancha
		view = camera.GetViewMatrix();
		glm::mat4 model5(1);
		model5 = glm::translate(model5, glm::vec3(0, 0, 0));
		model5 = glm::translate(model5, glm::vec3(5.7f, 2.6f, 140.0f));
		model5 = glm::rotate(model5, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model5 = glm::scale(model5, glm::vec3(1.3f, 1.3f, 1.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model5));
		Cancha.Draw(lightingShader);

		//Brazo Derecho
		view = camera.GetViewMatrix();
		//model3 = glm::translate(model3, glm::vec3(1.15f, 3.142f, -1.38f));
		model5 = glm::translate(model5, glm::vec3(0.0f, 0.0f, 0.0f));
		model5 = glm::rotate(model5, glm::radians(rotBrazo), glm::vec3(1.0f, 0.0f, 0.0f));
		model5 = glm::scale(model5, glm::vec3(1, 1, 1));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model5));
		Brazo.Draw(lightingShader);


		//Brazo Izquierdo
		view = camera.GetViewMatrix();
		glm::mat4 model7(1);
		model7 = glm::translate(model7, glm::vec3(0, 0, 0));
		model7 = glm::translate(model7, glm::vec3(5.7f, 2.6f, 140.0f));
		model7 = glm::rotate(model7, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model7 = glm::scale(model7, glm::vec3(1.3f, 1.3f, 1.3f));
		model7 = glm::rotate(model7, glm::radians(rotBrazo), glm::vec3(0.1f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model7));
		Brazo2.Draw(lightingShader);


		//Balon
		view = camera.GetViewMatrix();
		model5 = glm::mat4(1);
		model5 = glm::translate(model5, glm::vec3(0.0f, 0.0f, 0.0f));
		model5 = glm::translate(model5, PosIniBalon + glm::vec3(movKitBX,movKitBY , 0.0f));
		model5 = glm::rotate(model5, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model5 = glm::rotate(model5, glm::radians(rotBrazo), glm::vec3(0.1f, 0.0f, 0.0f));
		model5 = glm::scale(model5, glm::vec3(1, 1, 1));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model5));
		Balon.Draw(lightingShader);


		//view = camera.GetViewMatrix();
		//glm::mat4 model3(1);
		//model3 = glm::translate(model3, PosIniAve + glm::vec3(movKitAvX, 30.0f, movKitAvZ));
		//model3 = glm::rotate(model3, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		//model3 = glm::rotate(model3, glm::radians(rotKitAv), glm::vec3(0.0f, 1.0f, 0.0f));
		//model3 = glm::scale(model3, glm::vec3(1.5f, 1.5f, 1.5f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model3));
		//Ave.Draw(lightingShader);

		///-------------------------------------------------------------Choque de carros----------------------------------------------------------------

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		shader.Use();
		view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		//Recorridos de carros hasta chocar
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, PosIni + glm::vec3(movKitX, 0, movKitZ));
		model = glm::translate(model, glm::vec3(-9, 1.36, 1.0f));
		model = glm::rotate(model, glm::radians(rotKitY), glm::vec3(1.0f, 0.0f, 0.0));
		model = glm::rotate(model, glm::radians(rotKitZ), glm::vec3(0.0f, 0.0f, 1.0));
		model = glm::rotate(model, glm::radians(rotKitX), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Carrochoca1[i].Draw(shader);

		//view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(-7.5, 0.5, 3.3f));
		//model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, PosIni + glm::vec3(movKitX, 0, movKitZ));
		//model = glm::rotate(model, glm::radians(rotKitX), glm::vec3(0.0f, 1.0f, 0.0));;
		//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//LlantasA1[i].Draw(shader);

		//view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(-7.5, 0.5, -1.35f));
		//model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, PosIni + glm::vec3(movKitX, 0, movKitZ));
		//model = glm::rotate(model, glm::radians(rotKitX), glm::vec3(0.0f, 1.0f, 0.0));
		//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//LlantasA1[i].Draw(shader);


		//view = camera.GetViewMatrix();
		//model = glm::mat4(1);;
		//model = glm::translate(model, PosIni + glm::vec3(movKitX, 0, movKitZ));
		//model = glm::translate(model, glm::vec3(-10.45, 0.5, 3.3f));
		//model = glm::rotate(model, glm::radians(rotKitX), glm::vec3(0.0f, 1.0f, 0.0));
		//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//LlantasA1[i].Draw(shader);

		//view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		//model = glm::translate(model, PosIni + glm::vec3(movKitX, 0, movKitZ));
		//model = glm::translate(model, glm::vec3(-10.45, 0.5, -1.35f));
		//model = glm::rotate(model, glm::radians(rotKitX), glm::vec3(0.0f, 1.0f, 0.0));
		//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//LlantasA1[i].Draw(shader);


		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, PosIni + glm::vec3(movKitX2, 0, movKitZ2));
		model = glm::translate(model, glm::vec3(7, 1.41, 1.0f));
		model = glm::rotate(model, glm::radians(rotKitY2), glm::vec3(1.0f, 0.0f, 0.0));
		model = glm::rotate(model, glm::radians(rotKitZ2), glm::vec3(0.0f, 0.0f, 1.0));
		model = glm::rotate(model, glm::radians(rotKitX2), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Carrochoca2[i].Draw(shader);

		/*view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(8.4, 0.5, 3.2f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX2, 0, movKitZ2));
		model = glm::rotate(model, glm::radians(rotKitX2), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		LlantasA2[i].Draw(shader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(8.4, 0.5, -1.35f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX2, 0, movKitZ2));
		model = glm::rotate(model, glm::radians(rotKitX2), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		LlantasA2[i].Draw(shader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(7.45, 0.5, 3.2f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX2, 0, movKitZ2));
		model = glm::rotate(model, glm::radians(rotKitX2), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		LlantasA2[i].Draw(shader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(7.45, 0.5, -1.35f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX2, 0, movKitZ2));
		model = glm::rotate(model, glm::radians(rotKitX2), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		LlantasA2[i].Draw(shader);*/

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-20, 2.3, -6.7f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX3, 0, movKitZ3));
		model = glm::rotate(model, glm::radians(rotKitX3), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Grua.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-20, 2.3, -6.7f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX3, 0, movKitZ3));
		model = glm::rotate(model, glm::radians(rotKitX3), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Gancho[j].Draw(shader);

		/*view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-16, 0.5, -7.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX3, 0, movKitZ3));
		model = glm::rotate(model, glm::radians(rotKitX3), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LlantaG.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-21, 0.5, -7.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX3, 0, movKitZ3));
		model = glm::rotate(model, glm::radians(rotKitX3), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LlantaG.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-23, 0.5, -7.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX3, 0, movKitZ3));
		model = glm::rotate(model, glm::radians(rotKitX3), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LlantaG.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-16, 0.5, -8.2f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX3, 0, movKitZ3));
		model = glm::rotate(model, glm::radians(rotKitX3), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LlantaG.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-21, 0.5, -8.2f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX3, 0, movKitZ3));
		model = glm::rotate(model, glm::radians(rotKitX3), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LlantaG.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-23, 0.5, -8.2f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX3, 0, movKitZ3));
		model = glm::rotate(model, glm::radians(rotKitX3), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LlantaG.Draw(lightingShader);*/

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(20, 2.3, -8.5f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX4, 0, movKitZ4));
		model = glm::rotate(model, glm::radians(rotKitX4), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Grua.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(20, 2.3, -8.5f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX4, 0, movKitZ4));
		model = glm::rotate(model, glm::radians(rotKitX4), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Gancho[j].Draw(shader);

		//view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(16, 0.5, -7.0f));
		//model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, PosIni + glm::vec3(movKitX4, 0, movKitZ4));
		//model = glm::rotate(model, glm::radians(rotKitX4), glm::vec3(0.0f, 1.0f, 0.0));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//LlantaG.Draw(lightingShader);

		//view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(21, 0.5, -7.0f));
		//model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, PosIni + glm::vec3(movKitX4, 0, movKitZ4));
		//model = glm::rotate(model, glm::radians(rotKitX4), glm::vec3(0.0f, 1.0f, 0.0));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//LlantaG.Draw(lightingShader);

		//view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(23, 0.5, -7.0f));
		//model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, PosIni + glm::vec3(movKitX4, 0, movKitZ4));
		//model = glm::rotate(model, glm::radians(rotKitX4), glm::vec3(0.0f, 1.0f, 0.0));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//LlantaG.Draw(lightingShader);

		//view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(16, 0.5, -8.2f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, PosIni + glm::vec3(movKitX4, 0, movKitZ4));
		//model = glm::rotate(model, glm::radians(rotKitX4), glm::vec3(0.0f, 1.0f, 0.0));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//LlantaG.Draw(lightingShader);

		//view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(21, 0.5, -8.2f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, PosIni + glm::vec3(movKitX4, 0, movKitZ4));
		//model = glm::rotate(model, glm::radians(rotKitX4), glm::vec3(0.0f, 1.0f, 0.0));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//LlantaG.Draw(lightingShader);

		//view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(23, 0.5, -8.2f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, PosIni + glm::vec3(movKitX4, 0, movKitZ4));
		//model = glm::rotate(model, glm::radians(rotKitX4), glm::vec3(0.0f, 1.0f, 0.0));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//LlantaG.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0, 1.2, 30.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX5, 0, movKitZ5));
		/*model = glm::rotate(model, glm::radians(rotKitA), glm::vec3(0.0f, 1.0f, 0.0));*/
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Perro.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-0.65, 1.1, 30.35f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX5, 0, movKitZ5));
		/*model = glm::rotate(model, glm::radians(rotKitA), glm::vec3(0.0f, 1.0f, 0.0));*/
		model = glm::rotate(model, glm::radians(-PTIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Pipi[k].Draw(shader);


		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-0.65, 1.1, 29.8));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX5, 0, movKitZ5));
		/*model = glm::rotate(model, glm::radians(rotKitA), glm::vec3(0.0f, 1.0f, 0.0));*/
		model = glm::rotate(model, glm::radians(-PTDer), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PTI.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.5, 1.1, 30.35f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX5, 0, movKitZ5));
		/*model = glm::rotate(model, glm::radians(rotKitA), glm::vec3(0.0f, 1.0f, 0.0));*/
		model = glm::rotate(model, glm::radians(-PEIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PEI.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.5, 1.1, 29.8f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX5, 0, movKitZ5));
		/*model = glm::rotate(model, glm::radians(rotKitA), glm::vec3(0.0f, 1.0f, 0.0));*/
		model = glm::rotate(model, glm::radians(-PEDer), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PED.Draw(lightingShader);

		glBindVertexArray(0);


		// We now draw as many light bulbs as we have point lights.


		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		// Draw skybox as last
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		SkyBoxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default




		// Swap the screen buffers
		glfwSwapBuffers(window);
	}




	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();




	return 0;
}


void animacion()
{

	//Movimiento del personaje

	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;

			PTIzq += KeyFrame[playIndex].rotIncD;
			PTDer += KeyFrame[playIndex].rotIncD2;
			PEIzq += KeyFrame[playIndex].rotIncD3;
			PEDer += KeyFrame[playIndex].rotIncD4;

			rotKitAD += KeyFrame[playIndex].rotAD;

			i_curr_steps++;
		}

	}
	//recorrido Auto1
	if (circuito)
	{
		if (recorrido1)
		{
			rotKitX = 0;
			rotKitY = 0;
			movKitZ += 0.8f;
			if (movKitZ > 10)
			{
				recorrido1 = false;
				recorrido2 = true;
			}
		}

		if (recorrido2)
		{
			rotKitX = 270;
			movKitX -= 0.8f;
			if (movKitX < -20)
			{
				recorrido2 = false;
				recorrido3 = true;
			}
		}

		if (recorrido3)
		{
			rotKitX = 0;
			movKitZ += 0.8f;
			if (movKitZ > 70)
			{
				recorrido3 = false;
				recorrido4 = true;
			}
		}

		if (recorrido4)
		{
			rotKitX = 90;
			movKitX += 0.8f;
			if (movKitX > 35)
			{
				recorrido4 = false;
				recorrido5 = true;
			}
		}

		if (recorrido5)
		{
			rotKitX = 270;
			rotKitZ = -30;
			movKitX -= 0.5f;
			if (movKitX < -20 && movKitZ > 70)
			{
				recorrido5 = false;
				recorrido6 = true;
			}
		}

		if (recorrido6)
		{
			rotKitX = 180;
			rotKitZ = 0;
			rotKitY = 30;
			movKitZ -= 0.5f;
			if (movKitZ < 10)
			{
				recorrido6 = false;
				recorrido7 = true;
			}
		}

		if (recorrido7)
		{
			rotKitX = 90;
			rotKitY = 0;
			rotKitZ = 30;
			movKitX += 0.5f;
			if (movKitX > 0)
			{
				recorrido7 = false;
				recorrido8 = true;
			}
		}

		if (recorrido8)
		{
			rotKitX = 180;
			rotKitZ = 0;
			rotKitY = 30;
			movKitZ -= 0.5f;
			if (movKitZ < 0)
			{
				recorrido8 = false;
				recorrido1 = true;
			}
		}

	}
	//recorrido Auto2
	if (circuito2)
	{
		if (recorrido9)
		{
			rotKitX2 = 0;
			rotKitY2 = 0;
			movKitZ2 += 0.5f;
			if (movKitZ2 > 10)
			{
				recorrido9 = false;
				recorrido10 = true;
			}
		}

		if (recorrido10)
		{
			rotKitX2 = 90;
			movKitX2 += 0.5f;
			if (movKitX2 > 20)
			{
				recorrido10 = false;
				recorrido11 = true;
			}
		}

		if (recorrido11)
		{
			rotKitX2 = 0;
			movKitZ2 += 0.5f;
			if (movKitZ2 > 70)
			{
				recorrido11 = false;
				recorrido12 = true;
			}
		}

		if (recorrido12)
		{
			rotKitX2 = 180;
			rotKitY2 = 30;
			movKitZ2 -= 0.5f;
			if (movKitZ2 < 10)
			{
				recorrido12 = false;
				recorrido13 = true;
			}
		}


		if (recorrido13)
		{
			rotKitX2 = 270;
			rotKitY2 = 0;
			rotKitZ2 = -30;
			movKitX2 -= 0.5f;
			if (movKitX2 < 0)
			{
				recorrido13 = false;
				recorrido14 = true;
			}
		}


		if (recorrido14)
		{
			rotKitX2 = 180;
			rotKitZ2 = 0;
			rotKitY2 = 30;
			movKitZ2 -= 0.5f;
			if (movKitZ2 < 0)
			{
				recorrido14 = false;
				recorrido9 = true;
			}
		}

	}

	//Recorrido gruas
	if (circuito3)
	{
		if (recorrido15)
		{
			rotKitX3 = 0;
			movKitZ3 += 0.5f;
			if (movKitZ3 > 12)
			{
				recorrido15 = false;
				recorrido16 = true;
			}
		}

		if (recorrido16)
		{
			rotKitX3 = 270;
			movKitX3 -= 0.5f;
			if (movKitX3 < -20)
			{
				recorrido16 = false;
				recorrido17 = true;
			}
		}

		if (recorrido17)
		{
			rotKitX3 = 180;
			movKitZ3 -= 0.5f;
			if (movKitZ3 < -6)
			{
				recorrido17 = false;
				recorrido18 = true;
			}
		}

		if (recorrido18)
		{
			rotKitX3 = 270;
			movKitX3 -= 0.5f;
			if (movKitX3 < -80)
			{
				recorrido18 = false;
				recorrido19 = true;
			}
		}

		if (recorrido19)
		{
			rotKitX3 = 0;
			movKitZ3 += 0.5f;
			if (movKitZ3 > 40)
			{
				recorrido19 = false;
				recorrido20 = true;
			}
		}

		if (recorrido20)
		{
			rotKitX3 = 180;
			movKitZ3 -= 0.5f;
			if (movKitZ3 < -7)
			{
				recorrido20 = false;
				recorrido21 = true;
			}
		}

		if (recorrido21)
		{
			rotKitX3 = 90;
			movKitX3 += 0.5f;
			if (movKitX3 > -21)
			{
				recorrido21 = false;
				recorrido22 = true;
			}
		}

		if (recorrido22)
		{
			rotKitX3 = 0;
			movKitZ3 += 0.5f;
			if (movKitZ3 > 12)
			{
				recorrido22 = false;
				recorrido23 = true;
			}
		}

		if (recorrido23)
		{
			rotKitX3 = 90;
			movKitX3 += 0.5f;
			if (movKitX3 > 0)
			{
				recorrido23 = false;
				recorrido24 = true;
			}
		}

		if (recorrido24)
		{
			rotKitX3 = 180;
			movKitZ3 -= 0.5f;
			if (movKitZ3 < -2)
			{
				recorrido24 = false;
				recorrido15 = true;
			}
		}

	}

	if (circuito4)
	{
		if (recorrido25)
		{
			rotKitX4 = 0;
			movKitZ4 += 0.5f;
			if (movKitZ4 > 12)
			{
				recorrido25 = false;
				recorrido26 = true;
			}
		}

		if (recorrido26)
		{
			rotKitX4 = 90;
			movKitX4 += 0.5f;
			if (movKitX4 > 20)
			{
				recorrido26 = false;
				recorrido27 = true;
			}
		}

		if (recorrido27)
		{
			rotKitX4 = 180;
			movKitZ4 -= 0.5f;
			if (movKitZ4 < -7)
			{
				recorrido27 = false;
				recorrido28 = true;
			}
		}

		if (recorrido28)
		{
			rotKitX4 = 90;
			movKitX4 += 0.5f;
			if (movKitX4 > 70)
			{
				recorrido28 = false;
				recorrido29 = true;
			}
		}

		if (recorrido29)
		{
			rotKitX4 = 270;
			movKitX4 -= 0.5f;
			if (movKitX4 < 20)
			{
				recorrido29 = false;
				recorrido30 = true;
			}
		}

		if (recorrido30)
		{
			rotKitX4 = 0;
			movKitZ4 += 0.5f;
			if (movKitZ4 > 12)
			{
				recorrido30 = false;
				recorrido31 = true;
			}
		}

		if (recorrido31)
		{
			rotKitX4 = 270;
			movKitX4 -= 0.5f;
			if (movKitX4 < 0)
			{
				recorrido31 = false;
				recorrido32 = true;
			}
		}

		if (recorrido32)
		{
			rotKitX4 = 180;
			movKitZ4 -= 0.5f;
			if (movKitZ4 < 0)
			{
				recorrido32 = false;
				recorrido25 = true;
			}
		}



	}

	if (circuitoDog)
	{
		if (recorrido33)
		{
			movKitZ5 -= 0.1f;
			if (movKitZ5 < -5)
			{
				recorrido33 = false;
				recorrido34 = true;
			}
		}

		if (recorrido34)
		{
			movKitZ5 += 0.1f;
			if (movKitZ5 > 0)
			{
				recorrido34 = false;
				recorrido33 = true;
			}
		}


	}
	//Movimiento del tiro a canasta
	if (accionTiro) {
		if (sentido_1R)
		{
			rotBrazo -= 0.5f;
			if (rotBrazo < -75)
			{
				sentido_1R = false;
				sentido_2R = true;
			}

		}

		if (sentido_2R)
		{
			rotBrazo += 0.5f;
			if (rotBrazo > -45)
			{
				sentido_2R = false;
				accionBalon = true;
			}
		}
		if (sentido_3R)
		{
			accionBalon = false;
			rotBrazo += -0.5f;
			if (rotBrazo > -75)
			{
				sentido_3R = false;
				//sentido_2R = true;
			}
		}

	}
	//Movimiento de balon 
	if (accionBalon) {
		if (recorridoB1)
		{
			movKitBX += 0.5f;
			movKitBY += 0.5f;
			if (movKitBY > 2.5)
			{
				recorridoB1 = false;
				recorridoB2 = true;
			}

		}

		if (recorridoB2)
		{
			movKitBX += 0.5f;
			movKitBY -= 0.5f;			
			if (movKitBY < 1.0)
			{
				movKitBX -= 0.5f;
				recorridoB2 = false;
				recorridoB3 = true;
			}
		}
		if (recorridoB3)
		{
			movKitBY -= 0.5f;
			if (movKitBY < -2.5)
			{
				recorridoB3 = false;
				recorridoB4 = true;
			}
		}
		if (recorridoB4)
		{
			movKitBX -= 0.25f;
			movKitBY += 0.5f;
			if (movKitBY > 0)
			{
				recorridoB4 = false;
				recorridoB5 = true;
			}
		}
		if (recorridoB5)
		{
			movKitBX -= 0.25f;
			movKitBY -= 0.5f;
			if (movKitBY < -2.5)
			{
				recorridoB5 = false;
				recorridoB6 = true;
			}
		}
		if (recorridoB6)
		{
			movKitBX -= 0.25f;
			movKitBY += 0.5f;
			if (movKitBY > -0.5)
			{
				control += 1;
				recorridoB6 = false;
				accionBalon = false;
				sentido_3R = true;
				accionTiro = false;
				//sentido_3R = true;
				//recorridoB6 = false;
			}
		}
	}

	//Movimiento del Ave

	if (circuitoAve) {
		if (recorrido1Av)
		{		
			rotKitAD -= 45.0f;
			movKitAvX += 0.5f;
			rotKitAD += 45.0f;
			if (movKitAvX > 90)
			{
				recorrido1Av = false;
				recorrido2Av = true;
			}
		}
		if (recorrido2Av)
		{
			rotKitAv = 0;
			movKitAvZ += 0.5f;
			if (movKitAvZ > 115)
			{
				recorrido2Av = false;
				recorrido3Av = true;

			}
		}

		if (recorrido3Av)
		{
			rotKitAv = 270;
			movKitAvX -= 0.5f;
			if (movKitAvX < 0)
			{
				recorrido3Av = false;
				recorrido4Av = true;
			}
		}

		if (recorrido4Av)
		{
			rotKitAv = 180;
			movKitAvZ -= 0.5f;
			if (movKitAvZ < 0)
			{
				recorrido4Av = false;
				recorrido5Av = true;
			}
		}
		if (recorrido5Av)
		{
			rotKitAv = 90;
			movKitAvX += 0.5f;
			if (movKitAvX > 0)
			{
				recorrido5Av = false;
				recorrido1Av = true;
			}
		}
	}

}


// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

	if (GLFW_KEY_Q == key && GLFW_PRESS == action) {
		if (i == 0) {
			i = 1;
		}
		else {
			i -= 1;
		}
	}

	if (GLFW_KEY_Z == key && GLFW_PRESS == action) {
		if (j == 0) {
			j = 2;
		}
		else {
			j -= 1;
		}
	}

	if (GLFW_KEY_X == key && GLFW_PRESS == action) {
		if (k == 0) {
			k = 1;
		}
		else {
			k -= 1;
		}
	}

	if (keys[GLFW_KEY_L])
	{
		if (play == false && (FrameIndex > 1))
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}

	}

	if (keys[GLFW_KEY_K])
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}

	}


	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
			LightP1 = glm::vec3(1.0f, 0.0f, 0.0f);
		else
			LightP1 = glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	if (keys[GLFW_KEY_1])
	{
		if (PTIzq < 45.0f)
			PTIzq += 1.0f;

	}

	if (keys[GLFW_KEY_2])
	{
		if (PTIzq > -45)
			PTIzq -= 1.0f;

	}

	if (keys[GLFW_KEY_3])
	{
		if (PTDer < 45.0f)
			PTDer += 1.0f;

	}

	if (keys[GLFW_KEY_4])
	{
		if (PTDer > -45)
			PTDer -= 1.0f;

	}

	if (keys[GLFW_KEY_5])
	{
		if (PEIzq < 45.0f)
			PEIzq += 1.0f;

	}

	if (keys[GLFW_KEY_6])
	{
		if (PEIzq > -45)
			PEIzq -= 1.0f;

	}

	if (keys[GLFW_KEY_7])
	{
		if (PEDer < 45.0f)
			PEDer += 1.0f;

	}

	if (keys[GLFW_KEY_8])
	{
		if (PEDer > -45)
			PEDer -= 1.0f;

	}

	if (keys[GLFW_KEY_9])
	{
		if (rotKitAD < 10.0f)
			rotKitAD += 10.0f;

	}

	if (keys[GLFW_KEY_0])
	{
		if (rotKitAD > -10.0f)
			rotKitAD -= 10.0f;

	}




	////Mov Personaje
	//if (keys[GLFW_KEY_H])
	//{
	//	posZ += 1;
	//}

	//if (keys[GLFW_KEY_Y])
	//{
	//	posZ -= 1;
	//}

	//if (keys[GLFW_KEY_G])
	//{
	//	posX -= 1;
	//}

	//if (keys[GLFW_KEY_J])
	//{
	//	posX += 1;
	//}

	//Circuitos

	if (keys[GLFW_KEY_O])
	{
		circuito = true;
	}

	if (keys[GLFW_KEY_P])
	{
		circuito = false;
	}

	if (keys[GLFW_KEY_U])
	{
		circuito2 = true;
	}

	if (keys[GLFW_KEY_I])
	{
		circuito2 = false;
	}
	if (keys[GLFW_KEY_T])
	{
		circuito3 = true;
	}

	if (keys[GLFW_KEY_Y])
	{
		circuito3 = false;
	}
	if (keys[GLFW_KEY_E])
	{
		circuito4 = true;
	}

	if (keys[GLFW_KEY_R])
	{
		circuito4 = false;
	}

	if (keys[GLFW_KEY_C])
	{
		circuitoDog = true;
	}

	if (keys[GLFW_KEY_V])
	{
		circuitoDog = false;
	}

	if (keys[GLFW_KEY_N])
	{
		accionTiro = true;
	}

	if (keys[GLFW_KEY_M])
	{
		accionTiro = false;
	}
	if (keys[GLFW_KEY_G])
	{
		circuitoAve = true;
	}

	if (keys[GLFW_KEY_H])
	{
		circuitoAve = false;
	}




	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}






}