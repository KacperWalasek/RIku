asset_type="tileobject"
name="stone_factory"

tileobject = {
    description = "stone_factory_description",
    behavior = {
        resource_factory = {
            {
                resource = "iron",
                quantity = 10
            },
            {
                resource = "stone",
                quantity = 200
            }
        },
        require_resources = {
            {
                resource = "stone"
            }
        },
        use_resources = {
            {
                resource = "wood",
                quantity = 5
            },
            {
                resource = "stone",
                quantity = 5
            }
        }
    }
}

function onBeingPlaced(hookable) 
    return MoveWrapper.new(TestMove.new())
end
