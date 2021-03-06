#ifndef TIBIA_THING_HPP
#define TIBIA_THING_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "tibia/Tibia.hpp"
#include "tibia/Utility.hpp"
#include "tibia/DrawableAndTransformable.hpp"

namespace tibia
{

class Thing : public tibia::DrawableAndTransformable
{

public:

    typedef std::shared_ptr<tibia::Thing> Ptr;
    typedef std::vector<tibia::Thing::Ptr> List;

    struct SortByTileNumber_t
    {
        bool operator()(tibia::Thing::Ptr a, tibia::Thing::Ptr b) const
        {
            return (a->getTileNumber() < b->getTileNumber());
        }
    };

    struct SortByTileCoords_t
    {
        bool operator()(tibia::Thing::Ptr a, tibia::Thing::Ptr b) const
        {
            //return (a->getTileX() == b->getTileX() ? a->getTileY() < b->getTileY() : a->getTileX() < b->getTileX());

            if (a->getTileX() == b->getTileX())
            {
                if (a->getTileY() == b->getTileY())
                {
                    return a->getDrawIndex() < b->getDrawIndex();
                }
                else
                {
                    return a->getTileY() < b->getTileY();
                }
            }

            return a->getTileX() < b->getTileX();
        }
    };

    Thing::Thing()
    {
        m_drawIndex = tibia::DRAW_INDEX_DEFAULT;

        m_drawOffset = 0;

        m_isReadyForErase = false;
    }

    void updateTileNumber()
    {
        m_tileNumber = m_tileX + (m_tileY * tibia::mapWidth);
    }

    void setCoords(int x, int y)
    {
        setX(x);
        setY(y);

        setTileX(x * tibia::TILE_SIZE);
        setTileY(y * tibia::TILE_SIZE);
    }

    void setTileCoords(int tileX, int tileY)
    {
        setX(tileX / tibia::TILE_SIZE);
        setY(tileY / tibia::TILE_SIZE);

        setTileX(tileX);
        setTileY(tileY);
    }

    void updateTileCoords()
    {
        m_tileX = m_x * tibia::TILE_SIZE;
        m_tileY = m_y * tibia::TILE_SIZE;

        updateTileNumber();
    }

    int getTileX()
    {
        return m_tileX;
    }

    void setTileX(int x)
    {
        m_tileX = x;
    }

    int getTileY()
    {
        return m_tileY;
    }

    void setTileY(int y)
    {
        m_tileY = y;
    }

    sf::Vector2u getTilePosition()
    {
        return sf::Vector2u(m_tileX, m_tileY);
    }

    int getTileNumber()
    {
        return m_tileNumber;
    }

    void setTileNumber(int tileNumber)
    {
        m_tileNumber = tileNumber;
    }

    int getX()
    {
        return m_x;
    }

    void setX(int x)
    {
        m_x = x;
    }

    int getY()
    {
        return m_y;
    }

    void setY(int y)
    {
        m_y = y;
    }

    void setZ(int z)
    {
        m_z = z;
    }

    int getZ()
    {
        return m_z;
    }

    void setDrawIndex(int drawIndex)
    {
        m_drawIndex = drawIndex;
    }

    int getDrawIndex()
    {
        return m_drawIndex;
    }

    void setDrawOffset(int drawOffset)
    {
        m_drawOffset = drawOffset;
    }

    int getDrawOffset()
    {
        return m_drawOffset;
    }

    void setIsReadyForErase(bool b)
    {
        m_isReadyForErase = b;
    }

    bool isReadyForErase()
    {
        return m_isReadyForErase;
    }

    void setIsObject(bool b)
    {
        m_isObject = b;
    }

    bool isObject()
    {
        return m_isObject;
    }

    bool isCreature()
    {
        return m_isCreature;
    }

    void setIsCreature(bool b)
    {
        m_isCreature = b;
    }

private:

    int m_tileX;
    int m_tileY;

    int m_tileNumber;

    int m_x;
    int m_y;
    int m_z;

    int m_drawIndex;

    int m_drawOffset;

    bool m_isReadyForErase;

    bool m_isObject;
    bool m_isCreature;

}; // class Thing

} // namespace tibia

#endif // TIBIA_THING_HPP
