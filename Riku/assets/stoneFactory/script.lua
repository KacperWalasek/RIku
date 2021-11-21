asset_type="tileobject"
name="stone_factory"

tileobject = {
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
        }
    }
}


function onBeingPlaced(hookable) 
    return MoveWrapper.new(TestMove.new())
end
