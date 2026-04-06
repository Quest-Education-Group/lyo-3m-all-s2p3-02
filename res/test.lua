
local nTest = CreateNode3D("bob")
local nTestChild = CreateNode3D("bobChild")

function OnInit()
    local node = CreateNode("Created from lua")
    -- local nTest = CreateNode3D("bob")
    -- local nTestChild = CreateNode3D("bobChild")
    -- nTest.AddChild(nTest, nTestChild)

    print("billy")
    local vec = fmaths.vec3:new(0,0,2)
    print("vec = (", vec.x,",", vec.y,",", vec.z,")" )
    nTest.SetWorldPosition(nTest, vec)
    vec.z = -vec.z
    print("vec = (", vec.x,",", vec.y,",", vec.z,")" )
    nTestChild.SetWorldPosition(nTestChild, vec)
    print("bob" )
    local pos = nTest:GetWorldPosition()
    print("Init pos = (", pos.x,",", pos.y,",", pos.z,")" )

    pos = nTestChild:GetWorldPosition()
    print("InitChild pos = (", pos.x,",", pos.y,",", pos.z,")" )
    

end

function OnUpdate(dt)
    local vec1 = fmaths.vec3:new(0,0,7)
    nTest.SetWorldPosition(nTest, vec1)

    local vec = fmaths.vec3:new(0,2,0)
    -- nTestChild.SetLocalPosition(nTestChild, vec)
    nTestChild.AddLocalPosition(nTestChild, vec)
    local pos = nTestChild:GetWorldPosition()

    print("Update pos = (", pos.x,",", pos.y,",", pos.z,")" )

    -- local vec = fmaths.vec3.new()
    -- print(vec.x)

    -- print(hook)

    -- hook.Add("MyEvent", "MyFunc", function()
    --     print("Hello")
    -- end)

    -- hook.Call("MyEvent")
    -- print(timer)

    -- timer.Create("Test" .. test, 0, 1, function()
    --     print("executed from timer")
    -- end)
    -- test = test + 1;
end

