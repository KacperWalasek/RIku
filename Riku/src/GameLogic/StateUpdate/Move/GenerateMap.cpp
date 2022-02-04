#include "GenerateMap.h"
#include "../../LogicAssets.h"
#include "../../Tile/TileDescription.h"
#include "../Patch/Patch.h"
#include "../../Tile/MapGenerator.h"
#include "BuildTileObject.h"
#include "CombinedMove.h"
#include "CreateUnit.h"

GenerateMap::GenerateMap(int playerCount)
    : playerCount(playerCount)
{
}

std::shared_ptr<Patch> GenerateMap::createPatch(const GameState& state, const LogicAssets& assets) const
{
    if (state.map.size() != 0)
        return std::make_shared<Patch>(state.playerOnMove);
    auto map = assets.mapGenerator.getFunction("onCreateMap")().get<std::vector<std::vector<TileDescription>>>();
    std::shared_ptr<IMove> combined = nullptr;;
    for(int i = 0; i< map.size(); i++) {
	    for (int j = 0; j < map[i].size(); j++)
		    if (!map[i][j].tileObject.empty()) {
			    std::shared_ptr<IMove> build = std::make_shared<BuildTileObject>(-1, std::make_pair(i, j),
			                                                                     map[i][j].tileObject);
			    //combined = combined ? std::make_shared<CombinedMove>(combined, build) : build;
		    }
    }
	int tmpCount=0;
	std::vector<std::pair<int, int> > prevPositions;
	int minSqrDistance=12;
    for (int i = 0; i < playerCount; i++)
    {
		if(tmpCount>200000)
			break;
		bool isOK=true;
		int x = (int)rand()%map.size();
	    int y = (int)rand()%map[0].size();
		if(map[x][y].biome=="sea")
			isOK=false;
		else
			for(auto&& [px, py]: prevPositions) {
				if((px-x)*(px-x)+(py-y)*(py-y)<minSqrDistance) {
					isOK=false;
					break;
				}
			}
		if(!isOK) {
			i--;
			tmpCount++;
			continue;
		}
		prevPositions.emplace_back(x,y);
        // TODO: when players will be map change player index
        std::shared_ptr<IMove> create = std::make_shared<CreateUnit>(i, "stefan", x, y);
        combined = combined ? std::make_shared<CombinedMove>(combined, create) : create;
		tmpCount=0;
    }
    Patch patch = Patch(map) + Patch(combined) + Patch(0);
    patch.playerCount = playerCount;
    return std::make_shared<Patch>(patch);
}

bool GenerateMap::isDoable(const GameState& state, const LogicAssets& assets, bool popup) const
{
    return true;
}

std::shared_ptr<IMove> GenerateMap::asPointner() const
{
    return std::make_shared<GenerateMap>(playerCount);
}
