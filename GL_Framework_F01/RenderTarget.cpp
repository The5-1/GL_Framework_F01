#include "RenderTarget.h"
#include "Logging.h"
#include "Texture.h"
#include "RenderBuffer.h"
#include "RenderPass.h"

namespace The5
{
	RenderTarget::RenderTarget(std::string name): name(name)
	{
		createFBO();
	}

	void RenderTarget::createFBO()
	{
		glGenFramebuffers(1, &fboID);
	}

	void RenderTarget::bindFBO() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fboID);
	}

	void RenderTarget::unbindFBO() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0); //resets to onscreen
	}

	void RenderTarget::attachReadWriteBuffer(Texture * texture, GLenum attachmentType)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, texture->getTextureID(), 0);
		textureAttachments.insert(std::make_pair(texture, attachmentType));
		checkFramebufferErrors();
	}

	void RenderTarget::attachWriteonlyBuffer(RenderBuffer * renderBuffer, GLenum attachmentType)
	{
		//Renderbuffer must not be bound for this to work, just the FBO
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer->getBufferID());
		//textureAttachments.insert(std::make_pair(texture, attachmentType));
		checkFramebufferErrors();
	}


	void RenderTarget::bindWriteFBO()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboID);
	}

	void RenderTarget::bindReadFBO()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, fboID);
	}

	bool RenderTarget::checkFramebufferErrors()
	{
		GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (result == GL_FRAMEBUFFER_COMPLETE) return true;
		else
		{
			ERR_GL("Error generatig FBO for: " << name << "\n\t Error ID: GL_FRAMEBUFFER_" << result);
			return false;
		}
	}

}
