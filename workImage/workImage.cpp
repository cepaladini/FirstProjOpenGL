#include <workImage.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

workImage::workImage()
{
   width = height = nchannels = 0;
   data = NULL;
}

workImage::workImage(std::string arquivo)
{
   carrega(arquivo);
}

workImage::~workImage()
{
   stbi_image_free(data);
}

// Para carregar a imagem no buffer data, usa biblioteca STB.
void workImage::carrega(std::string arquivo)
{
   data = stbi_load(arquivo.c_str(), &width, &height, &nchannels, 0);
   
   if (data)
   {
      std::cout << "Imagem carregada. Tamanho: Height = " << height << " Width = " << width << std::endl;
   }
   else
   {
      std::cout << "Falhou a carga da Imagem" << std::endl;
   }
}

int workImage::getW()
{
   return width;
}

int workImage::getH()
{
   return height;
}

int workImage::getNC()
{
   return nchannels;
}

unsigned char* workImage::get_data()
{
   return data;
}


