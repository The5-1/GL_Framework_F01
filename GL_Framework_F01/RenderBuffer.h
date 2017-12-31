#pragma once

#include "ForwardDeclarations.h"
#include "stl_include.h"
#include "Logging.h"
//#include "IPixelBuffer.h"

namespace The5 {

	/** RenderBuffer are optimized for WRITE only. Typically used for depth or stencils that are not Read*/
	class RenderBuffer
	{
	public:

		///public Fields
		/** Texture name */
		std::string name;

		///Constructor / Destructor
		/** Constructor */
		RenderBuffer() = default;
		/** Destructor */
		~RenderBuffer() = default;

		///Getters / Setters
		/** documentation */

		///Methods
		void setAttachmentType(TextureAttachmentType attachmentType)
		{
			this->attachmentType = attachmentType;
		}

		TextureAttachmentType getAttachmentType()
		{
			return this->attachmentType;
		}

		GLuint getBufferID()
		{
			return bufferID;
		}

	protected:
		///friend classes
		/** documentation */

		///private Constructor
		/** documentation */

		///private Fields
		/** texture ID */
		GLuint bufferID = 0;
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
		/** documentation */

		void generateBuffer(unsigned int width, unsigned int height, GLint internalFormat)
		{
			glGenRenderbuffers(1, &bufferID);
			glBindRenderbuffer(GL_RENDERBUFFER, bufferID);
			glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}

	};
}