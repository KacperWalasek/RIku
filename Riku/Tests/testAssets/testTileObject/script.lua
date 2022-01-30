asset_type="tileobject"
name="test_tile_object"
tileobject = {
    gui = {
        name = "GuiName",
        headers = { "name" },
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
    return MoveWrapper.new(AddSkill.new("test_skill",mapX,mapY))
end

function onOptionShow(option)
    local name = option["name"]:as_string("", false)
    return name 
end