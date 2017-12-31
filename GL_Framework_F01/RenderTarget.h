#pragma once

#include "ForwardDeclarations.h"
#include "GL_include.h"

namespace The5 {

	/** documentation */
	class RenderTarget
	{
	public:
		///public Fields
		/** Render Targets name */
		std::string name;

		///Constructor / Destructor
		/** Destructor */
		~RenderTarget() = default;

		///Getters / Setters
		/** documentation */

		///Methods
		/** activate FBO, required for attaching buffers */
		void bindFBO() const;
		/** attach Buffer for READ and WRITE (FBO must be bound first)*/
		void attachReadWriteBuffer(Texture* texture, GLenum attachmentType);
		/** attach Buffer for Writing only (e.g. GL_DEPTH24_STENCIL8) */
		void attachWriteonlyBuffer(RenderBuffer* renderBuffer, GLenum attachmentType);
		/** disable FBO, reset to on-screen rendering */
		void unbindFBO() const;

	protected:
		///friend classes
		friend RendererCP;

		///private Constructor
		/** Constructor */
		RenderTarget(std::string name);

		///private Fields
		/** Framebuffer Object ID */
		GLuint fboID = 0; // 0 = onscreen
		/** Framebuffer Object ID */
		std::map<Texture*, GLenum> textureAttachments;
		/** window to get resolution from*/
		//Window* window; //--> dynamic scaling requires extra effort for FBOs and handling callbacks
		/** use the windows resolution */
		//bool useWindowResolution = true;

		///private Methods
		/** create FBO*/
		void createFBO();

		/** check if the FBO is complete */
		bool checkFramebufferErrors();

		void bindWriteFBO();
		void bindReadFBO();

	};
}