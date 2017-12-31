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
		/** Constructor */
		RenderTarget(std::string name);
		/** Destructor */
		~RenderTarget() = default;

		///Getters / Setters
		/** documentation */

		///Methods
		/** documentation */

	protected:
		///friend classes
		/** documentation */

		///private Constructor
		/** documentation */

		///private Fields
		/** Framebuffer Object ID */
		GLuint fboID = 0;
		/** Framebuffer Object ID */
		std::vector<Texture*> textures;
		/** window to get resolution from*/
		//Window* window; //--> dynamic scaling requires extra effort for FBOs and handling callbacks
		/** use the windows resolution */
		//bool useWindowResolution = true;

		///private Methods
		/** create FBO*/
		void createFBO();

		void bindFBO();

		void attachTexture(Texture* texture);

		void bindWriteFBO();
		void bindReadFBO();

		bool checkFramebufferErrors();

	};
}