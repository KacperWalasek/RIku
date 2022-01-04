#include "ShortestPathEvaluator.h"
#include <list>
#include <set>

CostEvaluator::CostEvaluator(const std::vector<std::vector<Tile>>& map)
    : map(map)
{}


//heurystyka
int CostEvaluator::h(vertex from, vertex to)
{
    return sqrt(pow((to.x - from.x), 2) + pow((to.y - from.y), 2));
}

//koszt ruchu
int CostEvaluator::d(vertex vert)
{
    if (map[vert.x][vert.y].unit)
        return 1000000;
    return map[vert.x][vert.y].getCost();
}

std::vector<std::pair<int, int>> ShortestPathEvaluator::reconstructPath(std::map<vertex, vertex> cameFrom, vertex current)
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

Path ShortestPathEvaluator::getShortestPath(
    ICostEvaluator& evaluator, int maxX, int maxY, int fromX, int fromY, int toX, int toY)
{
    vertex start(fromX, fromY);
    vertex end(toX, toY);

    std::map<vertex, int> fScore;
    std::map<vertex, int> gScore;

    auto priority = [&fScore](const vertex& x, const vertex& y) { return fScore[x] > fScore[y]; };
    auto openSet = std::multiset< vertex, decltype(priority)>(priority);
    std::map<vertex, vertex> cameFrom;

    fScore.emplace(start, evaluator.h(start, end));
    gScore.emplace(start, 0);
    openSet.insert(start);

    while (openSet.size() > 0)
    {
        vertex current = *(openSet.rbegin());
        if (current.x == toX && current.y == toY) {
            return { reconstructPath(cameFrom, current), gScore[current] };
        }
        openSet.erase(std::find_if(openSet.begin(), openSet.end(), [current](const auto& elem) {
            return elem == current;
            }));
        for (vertex neighbor : current.getNeighbors(maxX, maxY))
        {
            int tentative_gScore = gScore[current] + evaluator.d(neighbor);
            if (gScore.find(neighbor) == gScore.end() || tentative_gScore < gScore[neighbor])
            {
                cameFrom.insert_or_assign(neighbor, current);
                gScore.insert_or_assign(neighbor, tentative_gScore);
                fScore.insert_or_assign(neighbor, tentative_gScore + evaluator.h(neighbor, end));

                //nieoptymalne (ale nwm jak to zrobic lepiej)
                if (std::find_if(openSet.begin(), openSet.end(), [neighbor](const auto& elem) {
                    return elem == neighbor;
                    }) == openSet.end())
                    openSet.insert(neighbor);
            }
        }
    }
    return { {}, INT_MAX };
}
