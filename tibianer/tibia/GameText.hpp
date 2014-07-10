#ifndef TIBIA_GAMETEXT_HPP
#define TIBIA_GAMETEXT_HPP

#include <vector>
#include <string>
#include <sstream>

#include <boost/algorithm/string.hpp>

#include <SFML/Graphics.hpp>

#include "tibia/Tibia.hpp"
#include "tibia/Utility.hpp"
#include "tibia/BitmapFont.hpp"
#include "tibia/BitmapFontText.hpp"
#include "tibia/DrawableAndTransformable.hpp"

namespace tibia
{

class GameText : public tibia::DrawableAndTransformable
{

public:

    void setText(tibia::BitmapFont& bitmapFont, sf::Vector2u tileCoords, int z, std::string text, sf::Color textColor)
    {
        m_texture = bitmapFont.getTexture();

        m_z = z;

        std::vector<std::string> textLines;
        boost::split(textLines, text, boost::is_any_of("\n"));
        //std::stringstream ss(text);
        //std::string line;
        //while (std::getline(ss, line, '\n'))
        //{
            //textLines.push_back(line);
        //}

        sf::Vector2f textPosition = static_cast<sf::Vector2f>(tileCoords);

        textPosition.x += tibia::TILE_SIZE / 2;
        //textPosition.y += tibia::TILE_SIZE / 2;

        if (textLines.size())
        {
            textPosition.y -= tibia::TILE_SIZE * (textLines.size() / 4);
        }

        int textHeight = bitmapFont.getGlyphSize()->y;

        for (auto textLine : textLines)
        {
            tibia::BitmapFontText bitmapFontText;

            bitmapFontText.setText(&bitmapFont, textLine, textColor, true);

            bitmapFontText.setPosition(textPosition);

            textPosition.y = textPosition.y + textHeight + 1;

            m_bitmapFontTextList.push_back(bitmapFontText);
        }
    }

    int getZ()
    {
        return m_z;
    }

    sf::Clock* getClock()
    {
        return &m_clock;
    }

private:

    sf::Texture* m_texture;

    int m_z;

    std::vector<tibia::BitmapFontText> m_bitmapFontTextList;

    sf::Clock m_clock;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        states.texture = m_texture;

        for (auto bitmapFontText : m_bitmapFontTextList)
        {
            target.draw(bitmapFontText, states);
        }
    }

};

} // tibia

#endif // TIBIA_GAMETEXT_HPP
