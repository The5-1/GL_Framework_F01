#pragma once

#include "ForwardDeclarations.h"
#include "GL_include.h"

namespace The5 {

	/** documentation */
	class RenderPass
	{
	public:

		///public Fields
		/** name */
		std::string name;

		///Constructor / Destructor
		/** Destructor */
		~RenderPass() = default;

		///Getters / Setters
		/** documentation */

		///Methods
		/** documentation */

		//static RenderPass* const OnscreenRenderpass;

	protected:
		///friend classes
		friend RendererCP;
		friend RenderTarget;
		/** documentation */

		///private Constructor
		/** Constructor */
		RenderPass(std::string name);

		///private Fields
		/** clear color active */
		bool clearColorActive = true;
		/** clear depth active */
		bool clearDepthActive = true;

		/** a RenderTarget this RenderPass renders to, render Targets can be drawn to from multiple passes */
		RenderTarget* mRenderTarget;
		/** override the per-object material and use this for all objects assigned to this pass */
		IMaterial* overrideMaterial = nullptr;

		///private Methods
		/** documentation */

	};
}