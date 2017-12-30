#include "RenderPass.h"

namespace The5
{

	void RenderPass::setOnscreenRendering()
	{
		//writing to no specifit Framebuffer renders onscreen
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}
