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
		/** clear color active */
		bool clearColorActive = true;
		/** clear depth active */
		bool clearDepthActive = true;

		/** a RenderTarget this RenderPass renders to, render Targets can be drawn to from multiple passes */
		RenderTarget* mRenderTarget;

		///private Methods
		/** documentation */

	};
}