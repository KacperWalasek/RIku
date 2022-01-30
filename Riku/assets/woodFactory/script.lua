asset_type="tileobject"
name="wood_factory"

tileobject = {
    description = "wood_factory_description",
    gui = {
        name = "Units",
        headers = { "name", "wood" },
        options = { 
            {
                name = "Hero",
                wood = 3
            },
            {
                name = "Archer",
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
    return MoveWrapper.new(CombinedMove.new(MoveWrapper.new(CreateUnitAround.new("stefan",mapX,mapY)),MoveWrapper.new(UseResources.new("wood",wood))))
end

function onOptionShow(option)
    local wood = option["wood"]:as_string("", true)
    local name = option["name"]:as_string("", false)
    return name, wood  
end

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

-- Tak chcemy, żeby to wyglądało w przyszłości. Do tego funkcja onGuiShow zwracająca na podstawie opcji tworząca vector<string> 
-- gui = {
--     name = "Units",
--     headers = { {"", {2, "cost"}}, { "name", "iron", "wood" } },
--     options = { 
--         {
--             name = "Warrior",
--             iron = 20,
--             wood = 0,
--             description = "warrior_description"
--         },
--         {
--             name = "Archer",
--             iron = 10,
--             wood = 10,
--             description = "archer_description"
--         }
--     }
-- },