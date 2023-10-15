#include "MineField.h"
#include <assert.h>
#include <random>
#include "Vei2.h"
#include "SpriteCodex.h"
#include <algorithm>

MineField::MineField(int nMines)
{
    assert(nMines > 0 && nMines < (width* height));
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> xDist(0, width - 1);
    std::uniform_int_distribution<int> yDist(0, height - 1);
    for (int i = 0; i < nMines; i++)
    {
        Vei2 pos;
        do
        {
            pos = { xDist(rng), yDist(rng) };
        } while (TileAt(pos).HasMine());

        TileAt(pos).SpawnMine();
    }

    for (Vei2 gridPos = { 0,0 }; gridPos.y < height; gridPos.y++)
    {
        for (gridPos.x = 0; gridPos.x < width; gridPos.x++)
        {
            TileAt(gridPos).setAdjMineCount(CountAdjMines(gridPos));
        }
    }


}

void MineField::Draw(Graphics& gfx) const
{
    gfx.DrawRect({0, width*SpriteCodex::tileSize, 0, height*SpriteCodex::tileSize}, SpriteCodex::baseColor);
    for (Vei2 gridPos = { 0,0 }; gridPos.y < height; gridPos.y++)
    {
        for (gridPos.x = 0; gridPos.x < width; gridPos.x++)
        {
            TileAt(gridPos).Draw(gridPos * SpriteCodex::tileSize, lost, gfx);
        }
    }
}

void MineField::onRevealClick(const Vei2& screenPos)
{
    if (!lost)
    {
        const Vei2 gridPos = ScreenToGrid(screenPos);
        Tile& tile = TileAt(gridPos);
        if (!tile.isRevealed() && !tile.isFlagged())
        {
            tile.Reveal();
            if (tile.HasMine())
            {
                lost = true;
            }
        }
        recurseReveal(gridPos);
    }
}

void MineField::onFlagClick(const Vei2& screenPos)
{
    if (!lost)
    {
        const Vei2 gridPos = ScreenToGrid(screenPos);
        Tile& tile = TileAt(gridPos);
        if (!tile.isRevealed())
        {
            tile.ToggleFlag();
        }
    }
}

void MineField::recurseReveal(const Vei2& gridPos)
{
    Tile & tile = TileAt(gridPos);
    if (tile.hasNoAdjMines())
    {
        for (Vei2 iterator = gridPos - Vei2(1, 1); iterator.y <= (gridPos.y + 1); iterator.y++)
        {
            for (iterator.x = gridPos.x - 1; iterator.x <= (gridPos.x + 1); iterator.x++)
            {
                if (!(iterator.x < 0 || iterator.x >= width || iterator.y < 0 || iterator.y >= height))
                {
                    Tile& tile = TileAt(iterator);
                    if (!tile.isRevealed())
                    {
                        tile.Reveal();
                        recurseReveal(iterator);
                    }
                }
            }
        }
    }
}

RectI MineField::GetRect() const
{
    return RectI({ 0,0 }, width*SpriteCodex::tileSize, height*SpriteCodex::tileSize);
}

int MineField::CountAdjMines(const Vei2& gridPos)
{
    // Calculating loop boundaries using max is what he did beforehand.
    // not a bad idea. then don't need additional if statment to check.

    int mineCount = 0;
    for (Vei2 iterator = gridPos - Vei2(1, 1); iterator.y <= (gridPos.y + 1); iterator.y++)
    {
        for (iterator.x = gridPos.x - 1; iterator.x <= (gridPos.x + 1); iterator.x++)
        {
            if (!(iterator.x < 0 || iterator.x >= width || iterator.y < 0 || iterator.y >= height))
            {
                if (TileAt(iterator).HasMine())
                {
                    mineCount++;
                }
            }
            
        }
        
    }
    return mineCount;
}

MineField::Tile& MineField::TileAt(const Vei2& gridPos)
{
    return field[gridPos.y * width + gridPos.x];
}

const MineField::Tile& MineField::TileAt(const Vei2& gridPos) const
{
    return field[gridPos.y * width + gridPos.x];
}

Vei2 MineField::ScreenToGrid(const Vei2& screenPos)
{
    return screenPos / SpriteCodex::tileSize;
}

void MineField::Tile::SpawnMine()
{
    assert(!hasMine);
    hasMine = true;
}


bool MineField::Tile::HasMine() const
{
    return hasMine;
}

void MineField::Tile::Reveal()
{
    assert(state != State::Revealed);
    state = State::Revealed;
}

bool MineField::Tile::isRevealed() const
{
    return (state == State::Revealed);
}

void MineField::Tile::ToggleFlag()
{
    assert(!isRevealed());
    if (isFlagged())
    {
        state = State::Hidden;
        return;
    }

    state = State::Flagged;
}

bool MineField::Tile::isFlagged() const
{
    return state == State::Flagged;
}

bool MineField::Tile::hasNoAdjMines() const
{
    return nAdjMines == 0;
}

void MineField::Tile::Draw(const Vei2& screenpos, bool lost, Graphics& gfx) const
{
    if (lost)
    {
        switch (state)
        {
        case State::Hidden:
            if (HasMine())
            {
                SpriteCodex::DrawTileBomb(screenpos, gfx);
            }
            else {
                SpriteCodex::DrawTileButton(screenpos, gfx);
            }
            break;
        case State::Flagged:
            if (HasMine())
            {
                SpriteCodex::DrawTileBomb(screenpos, gfx);
                SpriteCodex::DrawTileFlag(screenpos, gfx);
            }
            else
            {
                SpriteCodex::DrawTileBomb(screenpos, gfx);
                SpriteCodex::DrawTileCross(screenpos, gfx);
            }
            break;
        case State::Revealed:
            if (!hasMine)
            {
                SpriteCodex::DrawTileNumber(screenpos, nAdjMines, gfx);
            }
            else
            {
                SpriteCodex::DrawTileBombRed(screenpos, gfx);
            }
            break;
        }
        return; 
    }

    switch (state)
    {
    case State::Hidden:
        SpriteCodex::DrawTileButton(screenpos, gfx);
        break;
    case State::Flagged:
        SpriteCodex::DrawTileButton(screenpos, gfx);
        SpriteCodex::DrawTileFlag(screenpos, gfx);
        break;
    case State::Revealed:
        if (!hasMine)
        {
            SpriteCodex::DrawTileNumber(screenpos, nAdjMines, gfx);
        }
        else
        {
            SpriteCodex::DrawTileBomb(screenpos, gfx);
        }
        break;
    }
}

void MineField::Tile::setAdjMineCount(int nMines)
{
    assert(nAdjMines == -1);
    nAdjMines = nMines;
}
