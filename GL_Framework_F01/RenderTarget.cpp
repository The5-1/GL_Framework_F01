#include "RenderTarget.h"
#include "Logging.h"

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

	void RenderTarget::bindWriteFBO()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboID);
	}

	void RenderTarget::bindReadFBO()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, fboID);
	}

	bool RenderTarget::checkErrors()
	{
		GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (result == GL_FRAMEBUFFER_COMPLETE) return true;
		else
		{
			ERR_GL("Error generatig FBO for: " << name);
			return false;
		}
	}

}
