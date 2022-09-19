/////////////////////////////////////////////////////////////////
// trgl.cpp:
//           Recebe como parâmetro uma string, contendo o nome
//           do arquivo da imagem com o mapa de alturas, carrega
//           esta imagem, e gera a visualilzação 3D do terreno.
// 
/////////////////////////////////////////////////////////////////

#include "trgl.h"

int main(int argc, char* argv[])
{
   // Abrir a imagem fornecida, e coletar dados e dimensões da imagem.
   std::string myImg = argv[1];
   
   // Cria objeto de imagem e lê a imagem.
   workImage img1;
   img1.carrega(myImg);
   
   /*
   // Constrói o mesh, a partir da imagem.
   Mesh msh(img1);
   
   // Constrói os Triangle strips, a partir da imagem.
   TriangleStrip tStrip(img1);
   */

   return 0;
}
