#include "OTextureCache.h"

#include <string>

NS_O_BEGIN

OTextureCache::OTextureCache() {

}

OTextureCache::~OTextureCache() {
    for (auto iterator : m_TextureMap) {
        OTexture texture = iterator.second;
        if(glIsTexture(texture.textureID) == true)
            glDeleteTextures(1, &texture.textureID);
    }
    
    OLog("Textures deleted !");
}

OTexture OTextureCache::getTexture(const std::string& texturePath,
                                   bool invert_y /* = true */,
                                   GLint param_W_S /* = GL_CLAMP_TO_BORDER */,
                                   GLint param_W_T /* = GL_CLAMP_TO_BORDER */) {
    //lookup the texture and see if its in the map
    auto mit = m_TextureMap.find(texturePath);

    //check if its not in the map
    if (mit == m_TextureMap.end()) {
        //Load the texture
        OTexture newTexture = TextureUtils::loadTexture(texturePath.c_str(), invert_y, param_W_S, param_W_T);

        //Insert it into the map
        m_TextureMap.insert(make_pair(texturePath, newTexture));

        return newTexture;
    }
    return mit->second;
}

void OTextureCache::checkTextures()
{
    for(auto texture : m_TextureMap)
    {
        if (glIsTexture(texture.second.textureID) == false) {
            OLog("Texture : "<< texture.first << " recreated.");
            texture.second = TextureUtils::loadTexture(texture.first.c_str());
        }
    }
}

NS_O_END