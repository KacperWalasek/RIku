asset_type="map_generator"

map_generator = {}

function onCreateMap()
    local arr = {}
    local biomes = {"forest","desert","tundra"}
    local areas = {"wet","dry"}
    local grounds = {"sand","stone","grass"}
    local r = RandomWrapper.new()
    for i=1,100 do
        arr[i]={}
        for j=1,100 do
            arr[i][j] = TileDescription.new(1,biomes[1],grounds[1],areas[1])
        end
    end
    return arr
end