asset_type = "unit"
--no name means that this file is a root of
is_abstract = true
unit = {
    mp = 25,
    hp = 10,
    str = 10
}
function myluafunction(times)
    return string.rep("(-)", times)
end

function parentfunction()
    return true
end