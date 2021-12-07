asset_type="map_generator"

map_generator = {}

function onCreateMap()
    local arr = {}
    local biomes = {"forest","desert","tundra"}
    local grounds = {"sand","stone","grass"}
    local areas = {"wet","dry"}
    local h = 5.0
    math.randomseed(os.time())  
    for i=1,25 do
        arr[i]={}
        for j=1,25 do
            arr[i][j] = TileDescription.new(math.random(3),biomes[math.random(3)],grounds[math.random(3)],areas[math.random(2)])
        end
    end
    return arr
end
