#include "UIElements/Font.h"
#include <ft2build.h>
#include FT_FREETYPE_H  

namespace Ore
{
	Font::Font(std::filesystem::path _fontPath)
	{
		Load(_fontPath);
	}

	void Load(std::filesystem::path _fontPath)
	{
	}
}