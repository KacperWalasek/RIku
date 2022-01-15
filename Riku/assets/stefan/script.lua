asset_type="unit"
name = "stefan"
unit = {
    movement_points = 50,
    miniunits = {
        "julka_ciocia_stefana",
        "maciek_syn_stefana",
        "maciek_syn_stefana",
    }
}

function onTurnEnd(hookable) --W przyszlosci prawdopodobnie to bedzie Unit a nie Hookable
    return MoveWrapper.new(TestMove.new())
end
