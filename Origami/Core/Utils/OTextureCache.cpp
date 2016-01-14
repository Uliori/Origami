#include "OTextureCache.h"

#include <string>

NS_O_BEGIN

OTextureCache::OTextureCache() {

}

OTextureCache::~OTextureCache() {
    for (auto iterator : m_TextureMap) {
        OTexture *texture = iterator.second;
        if(glIsTexture(texture->textureID) == true)
            glDeleteTextures(1, &texture->textureID);

        SAFE_DELETE(texture);
    }
    m_TextureMap.clear();
    OLog("Textures deleted !");
}

OTexture* OTextureCache::loadTexture(const std::string& texturePath,
                                   bool invert_y /* = true */,
                                   GLint param_W_S /* = GL_CLAMP_TO_BORDER */,
                                   GLint param_W_T /* = GL_CLAMP_TO_BORDER */) {
    //lookup the texture and see if its in the map
    auto mit = m_TextureMap.find(texturePath);

    //check if its not in the map
    if (mit == m_TextureMap.end()) {
        //Load the texture
        OTexture *newTexture = TextureUtils::loadTexture(texturePath.c_str(), invert_y, param_W_S, param_W_T);

        //Insert it into the map
        m_TextureMap.insert(make_pair(texturePath, newTexture));

        return newTexture;
    }
    else
    {
        mit->second->retain();
    }
    
    return mit->second;
}

void OTextureCache::releaseTexture(const std::string& texturePath)
{
    auto mit = m_TextureMap.find(texturePath);
    if (mit != m_TextureMap.end()) {
        OTexture *texture = mit->second;
        int tmpRC = texture->getReferenceCount();
        texture->release();
        if (tmpRC == 1) {
            m_TextureMap.erase(mit);
        }
    }
}

void OTextureCache::checkTextures()
{
    for(auto texture : m_TextureMap)
    {
        if (glIsTexture(texture.second->textureID) == false) {
            OLog("Texture : "<< texture.first << " recreated.");
            texture.second = TextureUtils::loadTexture(texture.first.c_str());
        }
    }
}

void OTextureCache::reloadTextures()
{
    for(auto texture : m_TextureMap)
    {
      if (glIsTexture(texture.second->textureID) == true) {
          glDeleteTextures(1, &texture.second->textureID);
      }
      // then recreate
      TextureUtils::reloadTexture(texture.second, texture.first.c_str());
    }
}

NS_O_END
