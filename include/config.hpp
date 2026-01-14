#pragma once

#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace paint::config
{
constexpr unsigned int kWindowWidth = 800;
constexpr unsigned int kWindowHeight = 600;
inline const std::string kWindowTitle = "Paint";
inline const sf::Color kBackgroundColor = sf::Color::White;
inline const sf::Color kDefaultBrushColor = sf::Color::Black;
constexpr float kDefaultBrushRadius = 6.0F;
constexpr float kPaletteWidth = 44.0F;
constexpr float kPaletteSwatchHeight = 32.0F;
constexpr float kPalettePadding = 8.0F;
constexpr float kButtonWidth = 84.0F;
constexpr float kButtonHeight = 30.0F;
constexpr float kButtonSpacing = 6.0F;
constexpr float kToolbarPadding = 8.0F;
}

namespace paint
{
enum class ToolType
{
    Brush,
    Eraser
};

struct ToolSettings
{
    ToolType tool{ToolType::Brush};
    sf::Color color{config::kDefaultBrushColor};
    float radius{config::kDefaultBrushRadius};
};
}
