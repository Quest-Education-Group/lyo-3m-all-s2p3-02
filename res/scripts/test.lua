local nTest
local nTestChild

function OnGameStarted()
    print("GameStarted")
end

function OnInit()
    nTest = CreateNode3D("bob")
    nTestChild = CreateNode3D("bobChild")

    print("billy")

    LoadNode("res/scripts/prefabs/TestEdit.nd.json")
    print("billy")

end

function OnUpdate(dt)

end
