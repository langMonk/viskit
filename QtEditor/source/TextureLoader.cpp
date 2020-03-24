#include "TextureLoader.h"
#include "SOIL/SOIL.h"

namespace textureLoader
{
	bool loadTexture(GLuint* outId, const char* filename)
	{
		//assert(outTexId);
		*outId = SOIL_load_OGL_texture
		(
			filename,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
		);

		if (*outId == 0)
		{
			//LOG_ERROR("Cannot load texture: %s", filename);
		}

		return *outId != 0;
	}
}