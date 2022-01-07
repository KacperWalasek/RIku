asset_type="tileobject"
name="test_tile_object"
tileobject = {
    gui = {
        name = "GuiName",
        options = { 
            {
                name = "opt1"
            },
            {
                name = "opt2"
            }
        }
    },
    behavior = {
        resource_factory = {
            {
                resource = "resource1",
                quantity = 10
            }
        }
    }
}


function onOptionChosen(option,mapX,mapY)
    return MoveWrapper.new(AddSkill.new("test_skill",11,10))
end
