asset_type="tileobject"
name="wood_factory"

tileobject = {
    gui = {
        name = "Units",
        headers = { {"", {2, "cost"}}, { "name", "iron", "wood" } },
        options = { 
            {
                name = "Warrior",
                iron = 20,
                wood = 0,
                description = "warrior_description"
            },
            {
                name = "Archer",
                iron = 10,
                wood = 10,
                description = "archer_description"
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

function onBeingPlaced(hookable) 
    return MoveWrapper.new(TestMove.new())
end
