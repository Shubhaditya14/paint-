#include <optional>
#include <array>
#include <optional>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "config.hpp"

namespace paint
{
sf::Vector2f toCoords(sf::RenderWindow& window, const sf::Vector2i pixel)
{
    return window.mapPixelToCoords(pixel, window.getView());
}

sf::CircleShape makeBrushStamp(const ToolSettings& tool, const sf::Vector2f position)
{
    const sf::Color color = tool.tool == ToolType::Eraser ? config::kBackgroundColor : tool.color;

    sf::CircleShape stamp(tool.radius);
    stamp.setFillColor(color);
    stamp.setOrigin({tool.radius, tool.radius});
    stamp.setPosition(position);
    return stamp;
}

std::vector<sf::RectangleShape> makePalette(const sf::Vector2f viewTopLeft,
                                            const sf::Vector2f viewSize,
                                            const std::vector<sf::Color>& colors,
                                            const float width,
                                            const float swatchHeight,
                                            const float padding,
                                            const float startYOffset)
{
    std::vector<sf::RectangleShape> palette;
    palette.reserve(colors.size());

    const float x = viewTopLeft.x + viewSize.x - width - padding;
    float y = viewTopLeft.y + startYOffset;

    for (const auto& color : colors)
    {
        sf::RectangleShape swatch({width, swatchHeight});
        swatch.setFillColor(color);
        swatch.setPosition({x, y});
        palette.push_back(swatch);
        y += swatchHeight + padding;
    }

    return palette;
}

std::optional<std::size_t> hitTestPalette(const std::vector<sf::RectangleShape>& palette,
                                          const sf::Vector2f position)
{
    for (std::size_t i = 0; i < palette.size(); ++i)
    {
        if (palette[i].getGlobalBounds().contains(position))
        {
            return i;
        }
    }

    return std::nullopt;
}

enum class ButtonAction
{
    Brush,
    Eraser,
    Clear,
    Save
};

struct Button
{
    sf::RectangleShape shape;
    std::vector<sf::RectangleShape> icon;
    std::optional<sf::Text> label;
    ButtonAction action;
};

std::vector<sf::RectangleShape> makeIcon(const ButtonAction action,
                                         const sf::Vector2f position,
                                         const sf::Vector2f size)
{
    std::vector<sf::RectangleShape> parts;

    const float insetX = size.x * 0.2F;
    const float insetY = size.y * 0.2F;
    const sf::Vector2f basePos = position + sf::Vector2f{insetX, insetY};
    const sf::Vector2f baseSize{size.x - insetX * 2.0F, size.y - insetY * 2.0F};

    if (action == ButtonAction::Brush)
    {
        sf::RectangleShape body({baseSize.x * 0.7F, baseSize.y * 0.18F});
        body.setPosition(basePos + sf::Vector2f{baseSize.x * 0.15F, baseSize.y * 0.6F});
        sf::RectangleShape tip({baseSize.x * 0.25F, baseSize.y * 0.25F});
        tip.setPosition(basePos + sf::Vector2f{baseSize.x * 0.6F, baseSize.y * 0.35F});
        tip.setRotation(sf::degrees(-35.0F));
        parts.push_back(body);
        parts.push_back(tip);
    }
    else if (action == ButtonAction::Eraser)
    {
        sf::RectangleShape body({baseSize.x * 0.65F, baseSize.y * 0.35F});
        body.setPosition(basePos + sf::Vector2f{baseSize.x * 0.18F, baseSize.y * 0.4F});
        body.setRotation(sf::degrees(-20.0F));
        sf::RectangleShape edge({baseSize.x * 0.25F, baseSize.y * 0.12F});
        edge.setPosition(basePos + sf::Vector2f{baseSize.x * 0.55F, baseSize.y * 0.35F});
        edge.setRotation(sf::degrees(-20.0F));
        parts.push_back(body);
        parts.push_back(edge);
    }
    else if (action == ButtonAction::Clear)
    {
        sf::RectangleShape diag1({baseSize.x * 0.7F, baseSize.y * 0.1F});
        diag1.setPosition(basePos + sf::Vector2f{baseSize.x * 0.15F, baseSize.y * 0.45F});
        diag1.setRotation(sf::degrees(45.0F));
        sf::RectangleShape diag2({baseSize.x * 0.7F, baseSize.y * 0.1F});
        diag2.setPosition(basePos + sf::Vector2f{baseSize.x * 0.15F, baseSize.y * 0.45F});
        diag2.setRotation(sf::degrees(-45.0F));
        parts.push_back(diag1);
        parts.push_back(diag2);
    }
    else if (action == ButtonAction::Save)
    {
        sf::RectangleShape body({baseSize.x * 0.8F, baseSize.y * 0.65F});
        body.setPosition(basePos + sf::Vector2f{baseSize.x * 0.1F, baseSize.y * 0.2F});
        sf::RectangleShape notch({baseSize.x * 0.4F, baseSize.y * 0.2F});
        notch.setPosition(basePos + sf::Vector2f{baseSize.x * 0.3F, baseSize.y * 0.2F});
        parts.push_back(body);
        parts.push_back(notch);
    }

    for (auto& part : parts)
    {
        part.setFillColor(sf::Color::Black);
    }

    return parts;
}

std::optional<sf::Text> makeLabel(const std::string& text,
                                  const sf::Font* font,
                                  const float size,
                                  const sf::Vector2f center,
                                  const sf::Color color)
{
    if (font == nullptr)
    {
        return std::nullopt;
    }

    sf::Text label(*font, text, static_cast<unsigned int>(size));
    label.setFillColor(color);
    const sf::FloatRect bounds = label.getLocalBounds();
    label.setOrigin({bounds.position.x + bounds.size.x * 0.5F, bounds.position.y + bounds.size.y * 0.5F});
    label.setPosition(center);
    return label;
}

std::vector<Button> makeButtons(const sf::Vector2f viewTopLeft,
                                const sf::Vector2f viewSize,
                                const float width,
                                const float height,
                                const float spacing,
                                const float padding,
                                const sf::Font* font)
{
    const float x = viewTopLeft.x + viewSize.x - width - padding;
    float y = viewTopLeft.y + padding;

    std::vector<Button> buttons;
    buttons.reserve(4);

    const std::array<ButtonAction, 4> actions{ButtonAction::Brush, ButtonAction::Eraser, ButtonAction::Clear,
                                              ButtonAction::Save};

    for (const auto action : actions)
    {
        sf::RectangleShape rect({width, height});
        rect.setPosition({x, y});
        rect.setOutlineThickness(1.0F);
        rect.setOutlineColor(sf::Color::Black);

        Button button;
        button.shape = rect;
        button.icon = makeIcon(action, rect.getPosition(), rect.getSize());
        button.label = makeLabel(
            action == ButtonAction::Brush ? "Brush"
            : action == ButtonAction::Eraser ? "Eraser"
            : action == ButtonAction::Clear  ? "Clear"
                                             : "Save",
            font,
            height * 0.45F,
            rect.getPosition() + rect.getSize() * 0.5F,
            sf::Color::Black);
        button.action = action;
        buttons.push_back(button);

        y += height + spacing;
    }

    return buttons;
}

std::optional<ButtonAction> hitTestButtons(const std::vector<Button>& buttons, const sf::Vector2f position)
{
    for (const auto& button : buttons)
    {
        if (button.shape.getGlobalBounds().contains(position))
        {
            return button.action;
        }
    }

    return std::nullopt;
}

void styleButtons(std::vector<Button>& buttons,
                  const ButtonAction active,
                  const sf::Vector2f cursor,
                  const sf::Color background)
{
    const sf::Color base = sf::Color(220, 220, 220);
    const sf::Color hover = sf::Color(200, 200, 200);
    const sf::Color activeColor = sf::Color(180, 210, 255);
    const sf::Color danger = sf::Color(230, 180, 180);
    const sf::Color success = sf::Color(180, 230, 180);

    for (auto& button : buttons)
    {
        const bool isHover = button.shape.getGlobalBounds().contains(cursor);
        sf::Color fill = base;

        if (button.action == ButtonAction::Clear)
        {
            fill = danger;
        }
        else if (button.action == ButtonAction::Save)
        {
            fill = success;
        }

        if (button.action == active)
        {
            fill = activeColor;
        }
        else if (isHover)
        {
            fill = hover;
        }

        button.shape.setFillColor(fill);
    }
}

bool saveCanvas(const sf::Vector2u size,
                const sf::Color background,
                const std::vector<sf::CircleShape>& strokes,
                const std::string& path)
{
    sf::RenderTexture renderTexture({size.x, size.y});

    renderTexture.clear(background);

    for (const auto& stamp : strokes)
    {
        renderTexture.draw(stamp);
    }

    renderTexture.display();
    const sf::Image image = renderTexture.getTexture().copyToImage();
    return image.saveToFile(path);
}
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({paint::config::kWindowWidth, paint::config::kWindowHeight}),
                            paint::config::kWindowTitle);

    window.setView(window.getDefaultView());

    sf::Font font;
    const bool fontLoaded = font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf");

    paint::ToolSettings toolSettings{};
    std::vector<sf::CircleShape> brushStrokes;
    brushStrokes.reserve(2048);
    bool isDrawing = false;

    const std::vector<sf::Color> paletteColors{paint::config::kDefaultBrushColor,
                                               sf::Color::Red,
                                               sf::Color::Green,
                                               sf::Color::Blue,
                                               sf::Color::Yellow,
                                               sf::Color::Magenta,
                                               sf::Color::Cyan,
                                               sf::Color::White};

    while (window.isOpen())
    {
        const sf::View view = window.getView();
        const sf::Vector2f viewSize = view.getSize();
        const sf::Vector2f viewCenter = view.getCenter();
        const sf::Vector2f viewTopLeft{viewCenter.x - viewSize.x * 0.5F, viewCenter.y - viewSize.y * 0.5F};

        const std::vector<paint::Button> buttons = paint::makeButtons(viewTopLeft,
                                                                      viewSize,
                                                                      paint::config::kButtonWidth,
                                                                      paint::config::kButtonHeight,
                                                                      paint::config::kButtonSpacing,
                                                                      paint::config::kToolbarPadding,
                                                                      fontLoaded ? &font : nullptr);

        const float toolbarHeight = paint::config::kToolbarPadding +
                                    (paint::config::kButtonHeight * 4.0F) +
                                    (paint::config::kButtonSpacing * 3.0F);
        const float paletteStart = toolbarHeight + paint::config::kPalettePadding;

        const std::vector<sf::RectangleShape> palette = paint::makePalette(
            viewTopLeft,
            viewSize,
            paletteColors,
            paint::config::kPaletteWidth,
            paint::config::kPaletteSwatchHeight,
            paint::config::kPalettePadding,
            paletteStart);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto* pressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (pressed->button == sf::Mouse::Button::Left)
                {
                    const sf::Vector2f position = paint::toCoords(window, pressed->position);

                    if (const std::optional<paint::ButtonAction> buttonHit =
                            paint::hitTestButtons(buttons, position))
                    {
                        isDrawing = false;

                        if (*buttonHit == paint::ButtonAction::Brush)
                        {
                            toolSettings.tool = paint::ToolType::Brush;
                        }
                        else if (*buttonHit == paint::ButtonAction::Eraser)
                        {
                            toolSettings.tool = paint::ToolType::Eraser;
                        }
                        else if (*buttonHit == paint::ButtonAction::Clear)
                        {
                            brushStrokes.clear();
                        }
                        else if (*buttonHit == paint::ButtonAction::Save)
                        {
                            paint::saveCanvas(window.getSize(), paint::config::kBackgroundColor, brushStrokes,
                                              "paint.png");
                        }
                    }
                    else if (const std::optional<std::size_t> hit = paint::hitTestPalette(palette, position))
                    {
                        toolSettings.color = paletteColors[*hit];
                        isDrawing = false;
                    }
                    else
                    {
                        isDrawing = true;
                        brushStrokes.emplace_back(paint::makeBrushStamp(toolSettings, position));
                    }
                }
            }

            if (const auto* released = event->getIf<sf::Event::MouseButtonReleased>())
            {
                if (released->button == sf::Mouse::Button::Left)
                {
                    isDrawing = false;
                }
            }

            if (const auto* moved = event->getIf<sf::Event::MouseMoved>())
            {
                if (isDrawing)
                {
                    const sf::Vector2f position = paint::toCoords(window, moved->position);
                    brushStrokes.emplace_back(paint::makeBrushStamp(toolSettings, position));
                }
            }

            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                sf::View updatedView(sf::FloatRect({0.0F, 0.0F},
                                                   {static_cast<float>(resized->size.x),
                                                    static_cast<float>(resized->size.y)}));
                window.setView(updatedView);
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::C)
                {
                    brushStrokes.clear();
                }
                else if (keyPressed->code == sf::Keyboard::Key::S)
                {
                    paint::saveCanvas(window.getSize(), paint::config::kBackgroundColor, brushStrokes, "paint.png");
                }
            }
        }

        const sf::Vector2f cursor = paint::toCoords(window, sf::Mouse::getPosition(window));

        std::vector<paint::Button> styledButtons = buttons;
        paint::styleButtons(styledButtons,
                            toolSettings.tool == paint::ToolType::Eraser ? paint::ButtonAction::Eraser
                                                                          : paint::ButtonAction::Brush,
                            cursor,
                            paint::config::kBackgroundColor);

        window.clear(paint::config::kBackgroundColor);

        for (const auto& stamp : brushStrokes)
        {
            window.draw(stamp);
        }

        for (const auto& button : styledButtons)
        {
            window.draw(button.shape);
            for (const auto& part : button.icon)
            {
                window.draw(part);
            }
            if (button.label.has_value())
            {
                window.draw(*button.label);
            }
        }

        for (const auto& swatch : palette)
        {
            window.draw(swatch);
        }

        window.display();
    }

    return 0;
}
