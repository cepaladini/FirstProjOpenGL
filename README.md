# FirstProjOpenGL
Receber imagem com mapa de alturas, e gerar visualização 3D do terreno, relacionada a esta imagem.

--------------------------------------------------------------------------

## Créditos
Este projeto foi desenvolvido usando os seguintes recursos:

### 1 - Projeto: Learn OpenGL

    . https://learnopengl.com/About
    
    . Licenciado nos termos da CC BY 4.0 license as published by Creative Commons
      https://creativecommons.org/licenses/by-nc/4.0/legalcode
    
    . Autor: Joey de Vries - https://twitter.com/JoeyDeVriez
    
### 2 - Projeto: GLFW

    . https://www.glfw.org/
    
    . Licenciado nos termos da zlib/libpng license, a BSD-like license that allows static linking with closed source software
      https://opensource.org/licenses/zlib-license.php

### 3 - Projeto: GLAD

    . https://github.com/Dav1dde/glad
    
    . The glad generated code itself is any of Public Domain, WTFPL or CC0
      https://github.com/Dav1dde/glad

### 4 - Projeto STB - Library for C/C++ image loader: stb_image.h
    . https://github.com/nothings/stb
    
    . Licenciado nos termos single-file public domain (or MIT licensed)
      https://github.com/nothings/stb/blob/master/LICENSE

### 5 - Projeto: GLM - OpenGL Mathematics 

    . https://glm.g-truc.net/0.9.8/index.html
    
    . Licenciado nos termos Happy Bunny License (Modified MIT) or the MIT License
      http://glm.g-truc.net/copying.txt
    
--------------------------------------------------------------------------

## Requisitos

### 1 - Fazer o download e build da GLFW, versão 3.3.8, obtendo a seguinte estrutura de diretórios (a partir do PATH do projeto) após o build:

    GLFW/3.3.8/
    ├── include
    │   └── GLFW
    │       ├── glfw3.h
    │       └── glfw3native.h
    └── lib
        ├── cmake
        │   └── glfw3
        │       ├── glfw3Config.cmake
        │       ├── glfw3ConfigVersion.cmake
        │       ├── glfw3Targets.cmake
        │       └── glfw3Targets-noconfig.cmake
        ├── libglfw3.a
        └── pkgconfig
            └── glfw3.pc
            
    Observar o arquivo ./GLFW/3.3.8/lib/pkgconfig/glfw3.pc. Ele será reconhecido através do arquivo init.sh, e 
    posteriormente usado no arquivo Makefile, para configurar o acesso ao GLFW instalado.
    
### 2 - Gerar o arquivo glad.zip, a partir do site do gerador GLAD (https://glad.dav1d.de/), com as seguintes configurações:

    OpenGL loader generated by glad 0.1.36 on Mon Sep 12 00:35:45 2022.
    Language/Generator: C/C++
    Specification: gl
    APIs: gl=4.6
    Profile: core
    Extensions:
    Loader: True
    Local files: False
    Omit khrplatform: False
    Reproducible: False
    
#### Criar no PATH do projeto o diretório ./glad/, e abrir o arquivo glad.zip dentro deste diretório, gerando a seguinte estrutura:

    glad/
    ├── include
    │   ├── glad
    │   │   └── glad.h
    │   └── KHR
    │       └── khrplatform.h
    └── src
        └── glad.c

### 3 - Baixar o arquivo stb_image.h a partir do site:
    https://github.com/nothings/stb 

#### Criar no PATH do projeto o diretório ./stb/, e colocar o arquivo baixado dentro deste diretório, gerando a seguinte estrutura:
    stb/
    └── stb_image.h
    
### 4 -


--------------------------------------------------------------------------
