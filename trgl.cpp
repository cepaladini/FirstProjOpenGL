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

int main(int argc, char* argv[])
{
   // Abrir a imagem fornecida, e coletar dados e dimensões da imagem.
   std::string myImg = argv[1];

   const unsigned int SCR_WIDTH  = atoi(argv[2]);
   const unsigned int SCR_HEIGHT = atoi(argv[3]);

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
   // E talvez capturar mouse
   
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

   return 0;
}
