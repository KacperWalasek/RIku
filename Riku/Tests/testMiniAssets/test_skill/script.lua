asset_type="skill"
name = "test_skill"

skill = {}

function onUse(mapX, mapY)
    return MoveWrapper.new(MiniResign.new())
end