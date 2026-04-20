#ifndef ORE_FONT__H_
#define ORE_FONT__H_

#include "UIElement.h"

#include <filesystem>

namespace Ore
{
    struct Font
    {
        Font() = default;
        Font(std::filesystem::path _fontPath);

        void Load(std::filesystem::path _fontPath);

    private:
        std::filesystem::path fontPath;
    };
}
#endif