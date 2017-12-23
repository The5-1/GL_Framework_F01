#include "RendererCP.h"
#include "Logging.h"


namespace The5 
{
	RendererCP::RendererCP(Application * application) : IComponentProcessor<RenderableC>(application)
	{

	}

	void RendererCP::drawAll()
	{
		/*
		for (int i = 0; i < mComponentPointers.size(); i++)
		{
			//mComponentPointers.at(i).
		}
		*/
	}

}