asset_type="skill"
name = "Fireball"

skill = {}

function onUse(mapX, mapY)
    return MoveWrapper.new(MiniAttack.new(mapX,mapY))
end