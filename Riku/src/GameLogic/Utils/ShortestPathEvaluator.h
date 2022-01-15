#pragma once
#include "../Tile/Tile.h"
#include "Path.h"

// Nie rozdzielam tego do oddzielnych plikow bo jest tu tyle klas tylko po to zeby moc uzyc shortestPatha w minigrze
struct vertex
{
    vertex() : x(0), y(0) {}
    vertex(int x, int y) : x(x), y(y) {}
    int x;
    int y;

    std::vector<vertex> getNeighbors(int maxX, int maxY) const
    {
        std::vector<vertex> vec;
        if (x != 0)
            vec.push_back({ x - 1,y });
        if (y != 0)
            vec.push_back({ x,y - 1 });
        if (x != maxX - 1)
            vec.push_back({ x + 1,y });
        if (y != maxY - 1)
            vec.push_back({ x,y + 1 });
        return vec;
    }
    // without this errors during set creation
    friend bool operator<(const vertex& p1, const vertex& p2)
    {
        return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
    }
    friend bool operator==(const vertex& p1, const vertex& p2)
    {
        return p1.x == p2.x && p1.y == p2.y;
    }

};

class ICostEvaluator
{
public:
    virtual double h(vertex from, vertex to) = 0;
    virtual int d(vertex vert) = 0;
};

class CostEvaluator 
    : public ICostEvaluator
{
    const std::vector<std::vector<Tile>>& map;
public:
    CostEvaluator(const std::vector<std::vector<Tile>>& map);
    double h(vertex from, vertex to);
    int d(vertex vert);
};

class ShortestPathEvaluator
{
    static std::vector<std::pair<int, int>> reconstructPath(std::map<vertex, vertex> cameFrom, vertex current);
public:
    static Path getShortestPath(
        ICostEvaluator& evaluator, int maxX, int maxY, int fromX, int fromY, int toX, int toY);
};

