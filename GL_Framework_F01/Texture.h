#pragma once

#include "ForwardDeclarations.h"
#include "stl_include.h"
#include "Logging.h"

namespace The5 {




	/** documentation */
	class Texture
	{
	public:
		///public Fields
		/** Texture name */
		std::string name;
		/** path to image file, nullptr if not based on external image*/
		The5::Image* image;

		///Constructor / Destructor
		/** Constructor: detailed */
		Texture(std::string name, int width, unsigned int height, GLint internalFormat, GLint format, GLint type, TextureAttachmentType attachmentType = TextureAttachmentType::ColorAttachment)
			: name(name), attachmentType(attachmentType)
		{
			generateTexture(width, height, internalFormat, format, type);
		}
		/** Destructor */
		~Texture() = default;

		///Getters / Setters
		/** documentation */

		///Methods
		/** load a image into the texture */
		void loadImage();

		void setAttachmentType(TextureAttachmentType attachmentType)
		{
			this->attachmentType = attachmentType;
		}

		TextureAttachmentType getAttachmentType()
		{
			return this->attachmentType;
		}

		GLuint getTextureID()
		{
			return textureID;
		}

		void resizeTexture(int width, unsigned int height)
		{
			generateTexture(width, height, this->internalFormat, this->format, this->type);
		}
	protected:
		///friend classes
		/** documentation */

		///private Constructor
		/** documentation */

		///private Fields
		/** texture ID */
		GLuint textureID = 0;
		/** width */
		unsigned int width;
		/** height */
		unsigned int height;
		/** depth for 3D textures */
		unsigned int depth;
		/** texture internalformat */
		GLint internalFormat;
		/** texture format */
		GLint format;
		/** texture type */
		GLint type;

		///private Fields specific to usage in FBOs
		/** attachment type for usage in FBO/RenderTarget */
		TextureAttachmentType attachmentType = TextureAttachmentType::ColorAttachment;
		TextureFormatArchetype formatArchetype = TextureFormatArchetype::noTextureFormatArchetype;

		///private Methods
		/** generate Texture */
		void generateTexture(unsigned int width, unsigned int height, GLint internalFormat, GLint format, GLint type)
		{
			if (width < 1 || height < 1)
			{
				ERR("Texture dimensions must not be 0!");
				return;
			}
			else
			{
				glGenTextures(1, &textureID);
				glBindTexture(GL_TEXTURE_2D, textureID);

				GLint mipLevel = 0;
				const GLvoid * data = NULL;
				glTexImage2D(GL_TEXTURE_2D, mipLevel, format, width, height, 0, format, type, data);

				this->width = width;
				this->height = height;
				this->internalFormat = internalFormat;
				this->format = format;
				this->type = type;

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

	};
}