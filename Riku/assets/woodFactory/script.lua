asset_type="tileobject"
name="wood_factory"

tileobject = {
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
