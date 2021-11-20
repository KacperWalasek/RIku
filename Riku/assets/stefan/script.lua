asset_type="unit"
name = "stefan"
unit = {
    movement_points = 20
}

function onTurnEnd(hookable) --W przyszlosci prawdopodobnie to bedzie Unit a nie Hookable
    return MoveWrapper.new(TestMove.new())
end
