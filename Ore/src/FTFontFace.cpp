#include "UIElements/FTFontFace.h"
#include "Logger.hpp"
#include "TextureObject.h"
#include "Buffer.h"

#include <glad/glad.h>
#include <filesystem>
#include <span>

namespace Ore
{
	FTFontFace::FTFontFace(std::filesystem::path path)
	{
		if (s_refcount == 0 && FT_Init_FreeType(&s_ftLibrary))
		{
			Logger::LogWithLevel(LogLevel::ERROR, "ERROR::FREETYPE: Could not init FreeType Library");
			return;
		}

		s_refcount++;

		if (FT_New_Face(s_ftLibrary, path.string().c_str(), 0, &m_face))
		{
			Logger::LogWithLevel(LogLevel::ERROR, "Failed to load font");
			return;
		}

		LoadChar();
		Logger::LogWithLevel(LogLevel::DEBUG, "Created font atlas for : ", path);
	}

	FTFontFace::FTFontFace(FTFontFace const& other)
	{
		m_face = other.m_face;
		s_refcount++;
	}

	FTFontFace::FTFontFace(FTFontFace&& other) noexcept
	{
		m_face = std::move(other.m_face);
	}

	void FTFontFace::SetSize(uint32 width, uint32 height)
	{
		FT_Set_Pixel_Sizes(m_face, width, height);
	}

	void FTFontFace::LoadChar()
	{
		//generate a 1024*1024 textures
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1, &m_bitmap);

		TextureObject texture(m_bitmap, TextureType::TYPE_2D);
		texture.GenerateTexture(DataType::UBYTE, 1024, 1024, GL_RED, GL_RED);
		texture.Bind();
		texture.AddParameters(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		texture.AddParameters(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		texture.AddParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		texture.AddParameters(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		uint32 advanceX = 0;
		uint32 advanceY = 0;
		for (uint8 c = 0; c < 128; c++)
		{
			if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
			{
				Logger::LogWithLevel(LogLevel::ERROR, "ERROR::FREETYTPE: Failed to load Glyph");
				return;
			}

			glTexSubImage2D(
				m_bitmap,
				0,
				advanceX,
				advanceY,
				m_face->glyph->bitmap.width,
				m_face->glyph->bitmap.rows,
				GL_RED,
				GL_UNSIGNED_BYTE,
				m_face->glyph->bitmap.buffer
			);

			advanceX = (advanceX + m_face->glyph->advance.x) % 1024;
			if (advanceX >= 1024) advanceY += m_face->glyph->bitmap.rows;
		}

		//GLuint buffID;
		//glGenBuffers(1, &buffID);

		//std::span<byte> charData = std::span<byte>(m_face->glyph->bitmap.buffer, m_face->glyph->bitmap.width * m_face->glyph->bitmap.rows);
		//Buffer<byte> buffer(charData, buffID, BufferType::PIXEL_UNPACK_BUFFER, false);
		//buffer.Bind();

		//buffer.
	}

	FTFontFace::~FTFontFace()
	{
		FT_Done_Face(m_face);
		s_refcount--;
		if (s_refcount == 0) FT_Done_FreeType(s_ftLibrary);
	}
};