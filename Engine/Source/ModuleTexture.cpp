#include "ModuleTexture.h"
#include "Application.h"
#include "ModuleEditor.h"


void ModuleTexture::LoadTexture(const char* nameTexture, Info& info)
{
	ScratchImage scratchImage;
	const size_t cSize = strlen(nameTexture) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, nameTexture, cSize);

	long success = LoadFromDDSFile(wc, DDS_FLAGS_NONE, NULL, scratchImage);
    if (success < 0) {
        success = LoadFromTGAFile(wc, NULL, scratchImage);
        if (success < 0) {
            LoadFromWICFile(wc, WIC_FLAGS_NONE, NULL, scratchImage);
        }
    }
    
	App->editor->logs.emplace_back("Texture loaded");

	GLuint tbo;
	ScratchImage flipped;
	FlipRotate(scratchImage.GetImages(), scratchImage.GetImageCount(), scratchImage.GetMetadata(), TEX_FR_FLIP_VERTICAL, flipped);
	const Image* image = flipped.GetImage(0, 0, 0);
	glGenTextures(1, &tbo);
	glBindTexture(GL_TEXTURE_2D, tbo);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	TexMetadata metadata = flipped.GetMetadata();
	int internalFormat, format, type;
	switch (metadata.format)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_RGBA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_BGRA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		internalFormat = GL_RGB8;
		format = GL_BGR;
		type = GL_UNSIGNED_BYTE;
		break;
	default:
		assert(false && "Unsupported format");
	}
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, metadata.width, metadata.height, 0, format, type, image->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	info.id = tbo;
	info.path = nameTexture;
}
