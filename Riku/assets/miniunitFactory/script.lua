asset_type="tileobject"
name="miniunit_factory"

tileobject = {
    description = "miniunit_factory_description",
    gui = {
        name = "Units",
        headers = { "name", "wood" },
        options = { 
            {
                name = "julka_ciocia_stefana",
                wood = 3
            },
            {
                name = "maciek_syn_stefana",
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
    return MoveWrapper.new(CombinedMove.new(MoveWrapper.new(AddMiniUnit.new(name,mapX,mapY)),MoveWrapper.new(UseResources.new("wood",wood))))
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