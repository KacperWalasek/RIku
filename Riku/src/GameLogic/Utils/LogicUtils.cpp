#include "LogicUtils.h"
#include <queue>
#include <list>

//heurystyka
double LogicUtils::h(vertex from, vertex to)
{
    return sqrt(pow((to.x - from.x),2) + pow((to.y - from.y), 2));
}

//koszt ruchu
double LogicUtils::d(const GameState& state,vertex vert)
{
    if (state.map[vert.x][vert.y].unit)
        return 1000000;
    return state.map[vert.x][vert.y].getCost();
}

std::vector<std::pair<int, int>> LogicUtils::reconstructPath(std::map<vertex, vertex> cameFrom, vertex current)
{
    std::list<std::pair<int, int>> totalPath = { {current.x, current.y} };
    while (cameFrom.find(current) != cameFrom.end())
    {
        current = cameFrom[current];
        totalPath.push_front({ current.x, current.y });
    }
    return { std::make_move_iterator(std::begin(totalPath)),
             std::make_move_iterator(std::end(totalPath)) };
}

Path LogicUtils::getShortestPath(
    const GameState& state, int fromX, int fromY, int toX, int toY)
{
    vertex start(fromX, fromY);
    vertex end(toX, toY);

    std::map<vertex, double> fScore;
    std::map<vertex, double> gScore;

    auto priority = [&fScore](const vertex& x, const vertex& y) { return fScore[x] > fScore[y]; };
    auto openSet = std::multiset< vertex, decltype(priority)>(priority);
    std::map<vertex, vertex> cameFrom;

    fScore.emplace(start, h(start, end));
    gScore.emplace(start, 0);
    openSet.insert(start);

    while (openSet.size()>0)
    {
        vertex current = *(openSet.rbegin());
        if (current.x == toX && current.y == toY) {
            if (gScore[current] > 10000)
                break;
            return { reconstructPath(cameFrom, current), (int)ceil(gScore[current])};
        }
        openSet.erase(std::find_if(openSet.begin(), openSet.end(), [current](const auto& elem) {
            return elem == current;
            }));
        for (vertex neighbor : current.getNeighbors(state.map.size(),state.map[0].size()))
        {
            double tentative_gScore = gScore[current] + d(state, neighbor);
            if (gScore.find(neighbor) == gScore.end() || tentative_gScore < gScore[neighbor])
            {
                cameFrom.insert_or_assign(neighbor, current);
                gScore.insert_or_assign(neighbor, tentative_gScore);
                fScore.insert_or_assign(neighbor, tentative_gScore + h(neighbor, end));

                //nieoptymalne (ale nwm jak to zrobic lepiej)
                if (std::find_if(openSet.begin(), openSet.end(), [neighbor](const auto& elem) {
                        return elem==neighbor;
                    }) == openSet.end())
                    openSet.insert(neighbor);
            }
        }
    }
    return { {}, INT_MAX };
}
