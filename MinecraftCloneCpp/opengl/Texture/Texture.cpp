#include "Texture.h"
#include "Debugging/Logger.h"

std::unordered_map<std::string, GLuint> Texture::loadedTextures;

Texture::Texture(const std::string& texPath, bool bFlipped)
{
	init(texPath, bFlipped);
}

void Texture::init(const std::string& texPath, bool bFlipped)
{

	if (loadedTextures.contains(texPath)) 
	{
		// We have already loaded and initialized this texure
		ID = loadedTextures[texPath];
		return;
	}


	// Images usually have flipped co-ordinates compared to texCoords so we flip them again
	stbi_set_flip_vertically_on_load(!bFlipped);

	// Load Texture file 
	int width, height, nChannels;
	unsigned char* texData = stbi_load(texPath.c_str(), &width, &height, &nChannels, 0);

	if (texData == nullptr)
	{
		LOG(Warning, "Could not load texture with path {}", texPath);
		return;
	}

	// Reset to default state
	stbi_set_flip_vertically_on_load(bFlipped);

	glGenTextures(1, &ID);

	// Store texture so that it doesnt need to be loaded in again
	loadedTextures[texPath] = ID;

	bind();

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Convert loaded image data into texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

	// Generate mip maps
	glGenerateMipmap(GL_TEXTURE_2D);

	// Release the image data since we've converted it into a texture and dont need it anymore
	stbi_image_free(texData);

	unbind();
}

void Texture::bind()
{
	LOG_FUNC();

	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind()
{
	LOG_FUNC();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setActiveTexture(int activeTextureSlot)
{
	LOG_FUNC();

	glActiveTexture(GL_TEXTURE0+activeTextureSlot);
}
