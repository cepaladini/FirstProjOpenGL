#ifndef MESH_H
#define MESH_H

#include <workImage.h>

// Mesh centrado na origem , no plano XZ.
// Cada vértice do mesh será colocado no eixo Y.
// Cada vértice do mesh é baseado na respectiva posição no mapa recebido.

class Mesh{
   private:
      // Vértices do mesh para imagem recebida no construtor. 
      // Guarda um vertice para cada coordenada x,y,z do mesh, onde:
      //     vrtx.x = coordenada x do vértice no mesh.
      //     vrtx.y = coordenada y do vértice no mesh (heigh map intensity).
      //     vrtx.z = coordenada z do vértice no mesh.
      
      std::vector<float> vrtx;
      
      // Escalas.
      float yScale=64.0f/256.0f;
      float yShift=16.0f;      
      
   public:
      Mesh(workImage& wImg);
      
      size_t getSize();
      std::vector<float> getVrtx();
};

size_t Mesh::getSize()
{
   return vrtx.size();
}

// fornece cópia do vrtx.
std::vector<float> Mesh::getVrtx()
{   
   std::vector<float> v(vrtx);

   return v;
}

Mesh::Mesh(workImage& wImg)
{
   // coordenadas no plano X,Z do mapa
   int i, j;

   // recebe os valores do heigh map, em cada respectiva posição i,j do mapa.
   unsigned char* texel;

   // dimensões da heigh map/imagem/mesh.
   int width     = wImg.getW() ,
       height    = wImg.getH() ,
       nchannels = wImg.getNC();

   // pega o início do mapa/imagem recebida.
   unsigned char* data = wImg.get_data();
   
   // varre o mapa    
   for (i=0; i<height; i++)
   {
      for (j=0; j<width; j++)
      {
         // pega o valor da altura no heigh map, na posição i,j
         texel = data + (j + width*i) * nchannels;
         
         // registra o vertice i,j no mesh.
         vrtx.push_back(j - width/2.0f);                  // vrtx.x
         vrtx.push_back( (int)texel[0]*yScale - yShift ); // vrtx.y
         vrtx.push_back(i - height/2.0f);                 // vrtx.z      
      }   
   }    
}

#endif

