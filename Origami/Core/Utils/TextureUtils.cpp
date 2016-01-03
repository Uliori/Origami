//
//  TextureUtils.cpp
//  Origami
//
//  Created by Sephiroth on 8/15/14.
//  Copyright (c) 2014 Sephiroth. All rights reserved.
//

#include "TextureUtils.h"
#include "ResourcesUtils.h"

#include <SOIL2/SOIL2.h>

NS_O_BEGIN
        
OTexture TextureUtils::loadTexture(const char* texname, bool invert_y)
{
    
    OTexture texture = {};
    
    int width;
    int height;
    int channels;
    
    
    //Load file into buffer
    unsigned char* buffer;
    size_t buffer_length;
    ResourcesUtils::fileLength(texname, buffer, buffer_length);
    
    unsigned char *img = SOIL_load_image_from_memory(buffer,(int) buffer_length, &width, &height, &channels, SOIL_LOAD_RGBA);
//            unsigned char *img = SOIL_load_image(ResourcesUtils::getResourcePathforFile(texname), &width, &height, &channels, SOIL_LOAD_RGBA);
    
    if(img == NULL)
    {
        OErrLog("Could not load texture : " << texname);
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
    
    
    // Créer la texture
    glGenTextures(1, &(texture.textureID));
    glBindTexture(GL_TEXTURE_2D, texture.textureID);
    
    if(glIsTexture(texture.textureID) == false)
    {
        OErrLog("Could not create ogl texture for : " << texname);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    
    
    SOIL_free_image_data(img);
    
    texture.height = (float)height;
    texture.width = (float)width;

    glBindTexture(GL_TEXTURE_2D, 0);
    
    return texture;
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

