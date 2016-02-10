//
//  TextureUtils.cpp
//  Origami
//
//  Created by Sephiroth on 8/15/14.
//  Copyright (c) 2014 Sephiroth. All rights reserved.
//

#include "TextureUtils.hpp"
#include "ResourcesUtils.hpp"

#include <SOIL2/SOIL2.h>

NS_O_BEGIN


void TextureUtils::getFileName(const char * imagepath, std::string &fileName, int &scale)
{
    std::string name = std::string(imagepath);
    size_t lastindex = name.find_last_of(".");
    std::string rawname = name;
    std::string extname = "";
    if (lastindex != std::string::npos) {
        rawname = name.substr(0, lastindex);
        extname = name.substr(lastindex, name.length());
    }

    for (FileSuffix fs : ODirector::director()->fileExtensions) {
        std::string fileNameVerif = rawname + fs.suffix + extname;
        if (ResourcesUtils::doesFileExists(fileNameVerif.c_str())) {
            fileName = fileNameVerif;
            scale = fs.scale;
            return;
        }
        else
        {
            OErrLog("Resource \"" << fileNameVerif << "\" was not found.");
        }
    }

    fileName = std::string(imagepath);
    scale = 1;
}

OTexture* TextureUtils::loadTexture(const char* texname, bool invert_y /* = true */,
                                   GLint param_W_S /* = GL_CLAMP_TO_BORDER */,
                                   GLint param_W_T /* = GL_CLAMP_TO_BORDER */)
{

    int width;
    int height;
    int channels;

    int scaleFactor;
    std::string fileName;
    getFileName(texname, fileName, scaleFactor);

    //Load file into buffer
    unsigned char* buffer;
    size_t buffer_length;
    ResourcesUtils::fileLength(fileName.c_str(), buffer, buffer_length);

    unsigned char *img = SOIL_load_image_from_memory(buffer,(int) buffer_length, &width, &height, &channels, SOIL_LOAD_RGBA);

    if(img == NULL)
    {
        OErrLog("Could not load texture : " << fileName);
        return nullptr;
    }


    if (invert_y) {
        int i, j;
        for( j = 0; j*2 < height; ++j )
        {
            int index1 = j * width * channels;
            int index2 = (height - 1 - j) * width * channels;
            for( i = width * channels; i > 0; --i )
            {
                unsigned char temp = img[index1];
                img[index1] = img[index2];
                img[index2] = temp;
                ++index1;
                ++index2;
            }
        }
    }

    OTexture *texture = new OTexture();
    texture->param_W_S = param_W_S;
    texture->param_W_T = param_W_T;

    glBindTexture(GL_TEXTURE_2D,0);
    // Créer la texture
    glGenTextures(1, &(texture->textureID));
    glBindTexture(GL_TEXTURE_2D, texture->textureID);

    if(glIsTexture(texture->textureID) == false)
    {
        OErrLog("Could not create ogl texture for : " << texname);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param_W_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param_W_T);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

//    glGenerateMipmap(GL_TEXTURE_2D);


    SOIL_free_image_data(img);

    texture->setHeight(height);
    texture->setWidth(width);
    texture->setScale(scaleFactor);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

void TextureUtils::reloadTexture(OTexture* texture, const char * imagepath, bool invert_y)
{
  int width;
  int height;
  int channels;

  int scaleFactor;
  std::string fileName;
  getFileName(imagepath, fileName, scaleFactor);

  //Load file into buffer
  unsigned char* buffer;
  size_t buffer_length;
  ResourcesUtils::fileLength(fileName.c_str(), buffer, buffer_length);

  unsigned char *img = SOIL_load_image_from_memory(buffer,(int) buffer_length, &width, &height, &channels, SOIL_LOAD_RGBA);

  if(img == NULL)
  {
      OErrLog("Could not load texture : " << fileName);
      return ;
  }

  if (invert_y) {
      int i, j;
      for( j = 0; j*2 < height; ++j )
      {
          int index1 = j * width * channels;
          int index2 = (height - 1 - j) * width * channels;
          for( i = width * channels; i > 0; --i )
          {
              unsigned char temp = img[index1];
              img[index1] = img[index2];
              img[index2] = temp;
              ++index1;
              ++index2;
          }
      }
  }

  glBindTexture(GL_TEXTURE_2D,0);
// Créer la texture
  glGenTextures(1, &(texture->textureID));
  glBindTexture(GL_TEXTURE_2D, texture->textureID);

  if(glIsTexture(texture->textureID) == false)
  {
      OErrLog("Could not create ogl texture for : " << imagepath);
  }
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture->param_W_S);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture->param_W_T);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

  //    glGenerateMipmap(GL_TEXTURE_2D);


  SOIL_free_image_data(img);

  glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint TextureUtils::makeTexture(GLsizei width, GLsizei height, GLint internalformat, GLenum format, GLenum type, GLint param_MAG, GLint param_MIN, GLint param_W_S, GLint param_W_T)
{
    GLuint texture;
    OGLCall(glGenTextures(1, &texture));
    OGLCall(glBindTexture(GL_TEXTURE_2D, texture));
    OGLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, type, 0));
    OGLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param_MAG));
    OGLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param_MIN));
    OGLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param_W_S));
    OGLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param_W_T));
    return texture;
};



GLuint TextureUtils::loadTextureCube(const char* PosXFilename,
    const char* NegXFilename,
    const char* PosYFilename,
    const char* NegYFilename,
    const char* PosZFilename,
    const char* NegZFilename)
{
    GLuint texture = SOIL_load_OGL_cubemap(
        ResourcesUtils::getResourcePathforFile(PosXFilename),
        ResourcesUtils::getResourcePathforFile(NegXFilename),
        ResourcesUtils::getResourcePathforFile(PosYFilename),
        ResourcesUtils::getResourcePathforFile(NegYFilename),
        ResourcesUtils::getResourcePathforFile(PosZFilename),
        ResourcesUtils::getResourcePathforFile(NegZFilename),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS// | SOIL_FLAG_INVERT_Y
        );

    OGLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, texture));
    OGLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    //    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    if (0 == texture) {
        OErrLog("SOIL loading error: "<< SOIL_last_result() << " \n");
    }

    return texture;
}
NS_O_END
