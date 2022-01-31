asset_type="tileobject"
name="stone_factory"

tileobject = {
    description = "stone_factory_description",
    behavior = {
        resource_factory = {
            {
                resource = "stone",
                quantity = 1
            }
        },
        use_resources = {
            {
                resource = "wood",
                quantity = 30
            }
        }
    }
}
