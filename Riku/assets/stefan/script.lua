asset_type="unit"
name = "stefan"
unit = {
    movement_points = 1000,
    miniunits = {
        "warrior",
        "archer",
        "archer",
    }
}

function onBeingPlaced(mapX, mapY) 
    return MoveWrapper.new(TestMove.new("placed"))
end

function onBeingCreated(mapX, mapY) 
    return MoveWrapper.new(TestMove.new("created"))
end

function onTurnEnd(mapX, mapY) 
    return MoveWrapper.new(TestMove.new("end"))
end

function onTurnBegin(mapX, mapY) 
    return MoveWrapper.new(TestMove.new("begin"))
end

function onDestroy(mapX, mapY) 
    return MoveWrapper.new(TestMove.new("destroy"))
end
