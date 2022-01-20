asset_type="skill"
name = "Courage"

skill = {}

function onUse(mapX, mapY)
    return MoveWrapper.new(MiniResign.new())
end