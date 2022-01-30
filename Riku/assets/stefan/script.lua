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

function onTurnEnd(mapX, mapY) --W przyszlosci prawdopodobnie to bedzie Unit a nie Hookable
    return MoveWrapper.new(TestMove.new())
end
