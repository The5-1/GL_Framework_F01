#include "RenderTarget.h"
#include "Logging.h"
#include "Texture.h"

namespace The5
{
	RenderTarget::RenderTarget(std::string name): name(name)
	{

	}

	void RenderTarget::createFBO()
	{
		glGenFramebuffers(1, &fboID);
	}

	void RenderTarget::bindFBO()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fboID);
	}

	void RenderTarget::attachTexture(Texture * texture)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, texture->getAttachmentType(), GL_TEXTURE_2D, texture->getTextureID(), 0);
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
