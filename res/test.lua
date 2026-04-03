
---@type Node3D
self = Node3D

test = 0;


function OnInit()
    local node = CreateNode("Created from lua")
    print("billy")
    local n = CreateNode3D("bob")
    print("bob")
end

function OnUpdate(dt)
    local vec = fmaths.vec3:new()
    print(vec.x)
    -- local vec = fmaths.vec3.new()
    -- print(vec.x)
end
