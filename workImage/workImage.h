#ifndef WORKIMAGE_H
#define WORKIMAGE_H

#include <string>
#include <iostream>

// Classe usada para gerenciar a carga da imagem,
// e manter suas informações armazenadas para uso
// posterior, durante o processamento.
class workImage
{
   private:
      int width, height, nchannels;
      unsigned char* data;
            
   public:
      void carrega(std::string arquivo);
      int getW();
      int getH();
      int getNC();
      
      unsigned char* get_data();
      
      workImage();
      workImage(std::string arquivo);
      ~workImage();
};

#endif

