#ifndef TRIANGLESTRIP_H
#define TRIANGLESTRIP_H

#include <workImage.h>

class TriangleStrip{
   private:
      // Índices para os Triangle Strips.      
      std::vector<unsigned int> idx;
      
      unsigned int numStrips, numVertsPerStrip;

   public:
      TriangleStrip(workImage& wImg);
      
      size_t getSize();
      std::vector<unsigned int> getIdx();
      
      unsigned int getNumStrips();
      unsigned int getNumVertsPerStrip();      
};

size_t TriangleStrip::getSize()
{
   return idx.size();
}

// fornece cópia do idx.
std::vector<unsigned int> TriangleStrip::getIdx()
{   
   std::vector<unsigned int> v(idx);

   return v;
}

unsigned int TriangleStrip::getNumStrips()
{
   return numStrips;
}

unsigned int TriangleStrip::getNumVertsPerStrip()
{
   return numVertsPerStrip;
}

TriangleStrip::TriangleStrip(workImage& wImg)
{
   // Linhas, colunas e lados dos strips
   unsigned int i, j, k;
   
   // dimensões da heigh map/imagem/mesh.
   int width     = wImg.getW(),
       height    = wImg.getH();
   
   // valores necessários para renderização do mesh.
   numStrips        = height-1;
   numVertsPerStrip = width*2;
   
   // gera os indices para cada i,j,k (linha,coluna,lado) dos strips.
   for (i=0; i<height-1; i++)
   {
      for (j=0; j<width; j++)
      {
         for (k=0; k<2; k++)
         {
            idx.push_back(j + width*(i+k));
         }
      }   
   }    
}

#endif

