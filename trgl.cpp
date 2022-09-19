/////////////////////////////////////////////////////////////////
// trgl.cpp:
//           Recebe como parâmetro uma string, contendo o nome
//           do arquivo da imagem com o mapa de alturas, carrega
//           esta imagem, e gera a visualilzação 3D do terreno.
// Uso:
//           ./trgl <ARQUIVO> <WIN-WIDTH> <WIN-HEIGHT>
// 
/////////////////////////////////////////////////////////////////

#include "trgl.h"

#include <Mesh.h>
#include <TriangleStrip.h>

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

int useWireframe = 0;
int displayGrayscale = 0;

// camera - give pretty starting point
Camera camera(glm::vec3(67.0f, 627.5f, 169.9f),
              glm::vec3(0.0f, 1.0f, 0.0f),
              -128.1f, -42.4f);
bool firstMouse = true;
float lastX;
float lastY;

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
        
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever a key event occurs, this callback is called
// ---------------------------------------------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int modifiers)
{
    if(action == GLFW_PRESS)
    {
        switch(key)
        {
            case GLFW_KEY_SPACE:
                useWireframe = 1 - useWireframe;
                break;
            case GLFW_KEY_G:
                displayGrayscale = 1 - displayGrayscale;
                break;
            default:
                break;
        }
    }
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

int main(int argc, char* argv[])
{
   // Abrir a imagem fornecida, e coletar dados e dimensões da imagem.
   std::string myImg = argv[1];

   const unsigned int SCR_WIDTH  = atoi(argv[2]);
   const unsigned int SCR_HEIGHT = atoi(argv[3]);

   lastX = SCR_WIDTH / 2.0f;
   lastY = SCR_HEIGHT / 2.0f;

   // Cria objeto de imagem e lê a imagem.
   workImage img1;
   img1.carrega(myImg);
   
   // Constrói o mesh, a partir da imagem.
   Mesh msh(img1);
   
   std::cout << "Loaded " << msh.getSize() / 3 << " vertices" << std::endl;

   // Constrói os Triangle strips, a partir da imagem.
   TriangleStrip tStrip(img1);

   std::cout << "Loaded " << tStrip.getSize() << " triangulos" << std::endl;
   
   // Inicializa e configura o ambiente do glfw
   glfwInit();
   // Instalada versão 4.6 no GLAD, mas usando aqui versão mais baixa, 3.3.
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
   // Cria janela GLFW.
   GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Desafio OpenGL: Mapa de alturas", NULL, NULL);
   if (window == NULL)
   {
      std::cout << "Falha na criação da janela GLFW" << std::endl;
      glfwTerminate();
      return -1;
   }
   glfwMakeContextCurrent(window);
   
   // TODO - definir possíveis callbacks.
   // framebuffer_size_callback, key_callback, mouse_callback, scroll_callback
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   glfwSetKeyCallback(window, key_callback);
   glfwSetCursorPosCallback(window, mouse_callback);
   glfwSetScrollCallback(window, scroll_callback);

   // E talvez capturar mouse
   // tell GLFW to capture our mouse
   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   
   // Carrega funções OpenGL, pelo GLAD.
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
      std::cout << "Falha na inicialização do GLAD" << std::endl;
      return -1;
   }
   
   // Configura estado global do OpenGL
   glEnable(GL_DEPTH_TEST);

   // Compilar os shader programs
   Shader heightMapShader("8.3.cpuheight.vs","8.3.cpuheight.fs");

   // first, configure the cube's VAO (and terrainVBO + terrainIBO)
   unsigned int terrainVAO, terrainVBO, terrainIBO;
   glGenVertexArrays(1, &terrainVAO);
   glBindVertexArray(terrainVAO);

   std::vector<float> vertices = msh.getVrtx();

   glGenBuffers(1, &terrainVBO);
   glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
   ////glBufferData(GL_ARRAY_BUFFER, msh.getSize() * sizeof(float), , GL_STATIC_DRAW);
   glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

   // position attribute
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   std::vector<unsigned> indices = tStrip.getIdx();

   glGenBuffers(1, &terrainIBO);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainIBO);
   ////glBufferData(GL_ELEMENT_ARRAY_BUFFER, tStrip.getSize() * sizeof(unsigned), , GL_STATIC_DRAW);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), &indices[0], GL_STATIC_DRAW);

   const int numStrips = tStrip.getNumStrips();
   const int numTrisPerStrip = tStrip.getNumVertsPerStrip();

   // render loop
   while (!glfwWindowShouldClose(window))
   {
      // input
      processInput(window);

      // render
      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // be sure to activate shader when setting uniforms/drawing objects
      heightMapShader.use();

      // view/projection transformations
      glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100000.0f);
      glm::mat4 view = camera.GetViewMatrix();
      heightMapShader.setMat4("projection", projection);
      heightMapShader.setMat4("view", view);

      // world transformation
      glm::mat4 model = glm::mat4(1.0f);
      heightMapShader.setMat4("model", model);
        
      // render the cube
      glBindVertexArray(terrainVAO);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      for(unsigned strip = 0; strip < numStrips; strip++)
      {
          glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
                         numTrisPerStrip+2,   // number of indices to render
                         GL_UNSIGNED_INT,     // index data type
                         (void*)(sizeof(unsigned) * (numTrisPerStrip+2) * strip)); // offset to starting index
      }

      // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   // optional: de-allocate all resources once they've outlived their purpose:
   glDeleteVertexArrays(1, &terrainVAO);
   glDeleteBuffers(1, &terrainVBO);
   glDeleteBuffers(1, &terrainIBO);

   // glfw: terminate, clearing all previously allocated GLFW resources.
   glfwTerminate();

   return 0;
}


