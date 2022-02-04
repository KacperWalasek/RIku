asset_type="tileobject"
name="military_barraks"

tileobject = {
    description = "military_barraks_description",
    gui = {
        name = "Units",
        headers = { "name", "wood" },
        options = { 
            {
                name = "peasant",
                wood = 3
            },
            {
                name = "warrior",
                wood = 3
            },
            {
                name = "knight",
                wood = 10
            }
        }
    },
    behavior = {
        resource_factory = {
            {
                resource = "wood",
                quantity = 10
            }
        }
    }
}

function onOptionChosen(option,mapX,mapY)
    local wood = option["wood"]:as_int(1)
    local name = option["name"]:as_string("", false)
    return MoveWrapper.new(CombinedMove.new(MoveWrapper.new(CreateUnitAround.new(name,mapX,mapY)),MoveWrapper.new(UseResources.new("wood",wood))))
end

function onOptionShow(option)
    local wood = option["wood"]:as_string("", true)
    local name = option["name"]:as_string("", false)
    return name, wood  
end
