#pragma once
#include "../GameState.h"
#include "Path.h"

struct vertex
{
    vertex() {}
    vertex(int x, int y) : x(x), y(y) {}
    int x;
    int y;

    std::vector<vertex> getNeighbors(int maxX,int maxY) const
    {
        std::vector<vertex> vec;
        if (x != 0)
            vec.push_back({ x - 1,y });
        if (y != 0)
            vec.push_back({ x,y - 1 });
        if (x != maxX-1)
            vec.push_back({ x + 1,y });
        if (y != maxY - 1)
            vec.push_back({ x,y + 1 });
        return vec;
    }
    // without this errors during set creation
    friend bool operator<(const vertex& p1, const vertex& p2)
    {
        return p1.x < p2.x || (p1.x==p2.x && p1.y < p2.y);
    }
    friend bool operator==(const vertex& p1, const vertex& p2)
    {
        return p1.x == p2.x && p1.y == p2.y;
    }

};

class LogicUtils
{
	static int h(vertex from, vertex to);
    static int d(const GameState& state, vertex vert);
    static std::vector<std::pair<int, int>> reconstructPath(std::map<vertex, vertex> cameFrom, vertex current);
public:
	static Path getShortestPath(
        const GameState& state, int fromX, int fromY, int toX, int toY);
};

