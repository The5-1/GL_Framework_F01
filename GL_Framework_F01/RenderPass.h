#pragma once

#include "ForwardDeclarations.h"
#include "GL_include.h"

namespace The5 {

	/** documentation */
	class RenderPass
	{
	public:

		///public Fields
		/** documentation */

		///Constructor / Destructor
		/** Constructor */
		RenderPass();
		/** Destructor */
		~RenderPass() = default;

		///Getters / Setters
		/** documentation */

		///Methods
		/** documentation */
		void setOnscreenRendering();

	protected:
		///friend classes
		friend RenderTarget;
		/** documentation */

		///private Constructor
		/** documentation */

		///private Fields
		/** RenderTarget this RenderPass renders to */
		RenderTarget_uptr mRenderTarget;

		///private Methods
		/** documentation */

	};
}