asset_type="map_generator"

map_generator = {}

function onCreateMap()
    arr = {}
    for i=1,25 do
        arr[i]={}
        for j=1,25 do
            arr[i][j] = TileDescription.new(0,"biome1","ground1","area1")
        end
    end
    return arr
end