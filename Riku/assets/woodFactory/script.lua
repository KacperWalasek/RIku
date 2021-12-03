asset_type="tileobject"
name="wood_factory"

tileobject = {
    gui = {
        name = "Units",
        options = { 
            {
                name = "Warrior",
                wood = 20
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
--MoveWrapper.new(CombinedMove.new(MoveWrapper.new(CreateUnit.new("stefan",1,1)),MoveWrapper.new(CreateUnit.new("stefan",2,1))))
function onOptionChosen()
    return MoveWrapper.new(CombinedMove.new(MoveWrapper.new(CreateUnit.new("stefan",1,1)),MoveWrapper.new(UseResources.new(0,1))))
end

function onBeingPlaced(hookable) 
    return MoveWrapper.new(TestMove.new())
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