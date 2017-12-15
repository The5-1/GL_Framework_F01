#pragma once

#include "assimp_include.h"

namespace THE5 {
	namespace asimp {



		const struct aiScene* loadasset(const char* path)
		{
			/* we are taking one of the postprocessing presets to avoid
			spelling out 20+ single postprocessing flags here. */
			const struct aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
			return scene;
		}



	}
}