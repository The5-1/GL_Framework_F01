#pragma once

#include "ForwardDeclarations.h"
#include "GL_include.h"

namespace The5 {

	/** documentation */
	class RenderTarget
	{
	public:
		///public Fields
		std::string name;
		/** Frame Buffer Dimensions */
		unsigned int height;
		unsigned int width;

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
		/** FBO */
		GLuint fboID;
		/** window to get resolution from --> dynamic scaling requires extra effort for FBOs */
		Window* window;

		///private Methods
		/** create FBO */
		void createFBO();

		void bindFBO();
		void bindWriteFBO();
		void bindReadFBO();

		bool checkErrors();

	};
}