#pragma once
#include "Graphics.h"

class MineField
{
private:
    class Tile {
    public:
        enum class State
        {
            Hidden,
            Flagged,
            Revealed
        };
    public:
        void SpawnMine();
        bool HasMine() const;
        void Reveal();
        bool isRevealed() const;
        void ToggleFlag();
        bool isFlagged() const;
        void Draw(const Vei2& screenpos, bool lost, Graphics& gfx) const ;
        void setAdjMineCount(int nMines);
    private:
        State state = State::Hidden;
        bool hasMine = false;
        int nAdjMines = -1;
    };
public:
    MineField(int nMines);
    void Draw(Graphics& gfx) const;
    void onRevealClick(const Vei2& screenPos);
    void onFlagClick(const Vei2& screenPos);
    RectI GetRect() const;
    int CountAdjMines(const Vei2& GridPos);
private:
    Tile& TileAt(const Vei2& gridPos);
    const Tile& TileAt(const Vei2& gridPos) const;
    Vei2 ScreenToGrid(const Vei2& screenPos);
private:
    static constexpr int width = 20;
    static constexpr int height = 16;
    bool lost = false;
    Tile field[width * height];
};

