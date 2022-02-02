asset_type = "unit"
parent = "parent" --default value: asset_type (if name!=asset_type), root (if name==asset_type and asset_type!=root), "" (for root)
name = "skeleton" --default value: asset_type
is_abstract = false --default value: false (if name!=asset_type)
unit = {
	mp = 10,
	str = 20
}

--Parameters:
--this: unit
--damage: table containing amount:number and type:DamageType
--type: integer or string (from DamageType)
--Returned value:
--number
function takeDamage(this, damage)
    this.hp=this.hp-amount
    return this
end
--Parameters:
--this: unit
--amount: number
--type: integer or string (from DamageType)
--Returned value:
--table
--number
function calculateDamage(this, other)
    local table
    table.amount = this.str
    table.type = 0
    return table
end

