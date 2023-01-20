#include "Texture.h"

using namespace GLHelper;

Texture::Texture(ImageData* image)
{

	// Create texture
	glGenTextures(1, &texture);

	// Bind new texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Load image data onto texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, image->getData());
	
	// Set texture up- and down-scaling settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Set wrapping modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}

Texture* Texture::fromBMP(string filename)
{

	Texture* texture;

	// Read image data
	ImageData* image = ImageReader::readBMPImage(filename);

	// Create texture from loaded image data
	texture = new Texture(image);

	// Delete image data
	delete image;

	// Return created image
	return texture;

}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, texture);
}
