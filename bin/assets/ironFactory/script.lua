asset_type="tileobject"
name="iron_factory"

tileobject = {
    description = "iron_factory_description",
    behavior = {
        resource_factory = {
            {
                resource = "iron",
                quantity = 2
            }
        },
        use_resources = {
            {
                resource = "wood",
                quantity = 30
            },
            {
                resource = "stone",
                quantity = 10
            }
        }
    }
}
