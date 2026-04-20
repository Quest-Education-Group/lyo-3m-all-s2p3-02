#ifndef ORE_FTFONTFACE__H_
#define ORE_FTFONTFACE__H_

#include "FontFace.h"

#include <ft2build.h>
#include FT_FREETYPE_H  

namespace Ore
{
	class FTFontFace : public FontFace
	{
	public:
		FTFontFace(std::filesystem::path path);
		FTFontFace(FTFontFace const& other);
		FTFontFace(FTFontFace&& other) noexcept;
		~FTFontFace() override;

		void SetSize(uint32 width, uint32 height);
		void LoadChar();

	private:
		inline static FT_Library s_ftLibrary;
		inline static int32 s_refcount = 0;
		FT_Face m_face{};
		uint32 m_bitmap = 0;
	};
}

#endif