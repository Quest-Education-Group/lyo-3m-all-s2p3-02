#ifndef ORE_TEXT__H_
#define ORE_TEXT__H_

#include "UIElement.h"
#include "UIElements/FontFace.h"

#include <filesystem>

namespace Ore
{
class Text : public UIElement
{
public:
    Text() = default;
    Text(std::string const& _text, sptr<FontFace>& _face) : m_text(_text), m_pFontFace(face) {}
    ~Text() = default;

private:
    std::string m_text;
    sptr<FontFace> m_pFontFace;
};
}
#endif
