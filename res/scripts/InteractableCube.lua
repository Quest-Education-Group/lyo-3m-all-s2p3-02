-- Interaction behaviour

---@class noderigidbody
self = self

local oPlayer
local oRoot
local bIsEquipped = false
local bA = false
local bB = false
function self:Interaction()

end

function self:GravityGunGrabb()
    print("GRABB OBJ")
    oPlayer = oRoot:FindChild("Player"):As(NodeTypes.NODE_RIGIDBODY)
    if not oPlayer then
        print("--- Interactable Obj does not have a ref to Player --- ")
        return
    else
        print("Player found, adding child ->")
    end
    print("P_Name :" .. oPlayer:GetName())

    self:Reparent(oPlayer, true)
    oPlayer.bIsHoldingObject = 1
    oPlayer.refHeldObject = self
    print("Name sphere = " .. self:GetName())

    -- local vec = self:GetPosition()
    -- print("pos before sphere : {" .. vec.x .. ", " .. vec.y .. ", " .. vec.z .. "}")
    -- local vec2 = self:GetPosition()
    -- print("POS after sphere : {" .. vec2.x .. ", " .. vec2.y .. ", " .. vec2.z .. "}")
    -- self:ResetForces()
    bIsEquipped = true
end

function self:GravityGunThrow()
    oPlayer = oRoot:FindChild("Player"):As(NodeTypes.NODE_RIGIDBODY)
    print("THROW OBJ")
    if not oPlayer then
        print("--- Interactable Obj does not have a ref to Player --- ")
        return
    else
        print("Player found, adding child ->")
    end
    print("P_Name :" .. oPlayer:GetName())

    self:Reparent(oRoot, true)
    oPlayer.bIsHoldingObject = 0
    oPlayer.refHeldObject = nil
    print("Name sphere = " .. self:GetName())
    -- local vec = self:GetPosition()
    -- print("pos before sphere : {" .. vec.x .. ", " .. vec.y .. ", " .. vec.z .. "}")
    -- local vec2 = self:GetPosition()
    -- print("POS after sphere : {" .. vec2.x .. ", " .. vec2.y .. ", " .. vec2.z .. "}")

    bIsEquipped = false
end

function OnInit()

    self:SetBodyType(2)

    self:SetIsGravityEnabled(false)
    oRoot = self:GetParent();
    -- oPlayer = oRoot:FindChild("Player"):As(NodeTypes.NODE_RIGIDBODY)
    if not oPlayer then
        print("--- Interactable Obj did not find Player ref --- ")
    else
        print("--- Interactable Obj found Player ref successfully --- ")
    end
end

local i = 0
function OnUpdate(dt)
    -- if bA then
    --     oPlayer = self:GetParent():GetParent():FindChild("Player"):As(NodeTypes.NODE_RIGIDBODY)
    --     bA = false
    -- end
    --     if bB and i>3 then
    --         -- self:SetBodyType(1)
    --         bA = !bA
    --         i = i + 1
    --     else
    --         bB = !bB
    --     end 
    --     end
    -- self:SetIsGravityEnabled(true)
    -- local vec = self:GetTotalForce()
    -- local vecP = oPlayer:GetTotalForce()
    -- print(self:GetName().." Forces : {" .. vec.x .. ", ".. vec.y .. ", ".. vec.z .. "}")
    -- print(oPlayer:GetName().." LOCAL POS : {" .. vecP.x .. ", ".. vecP.y .. ", ".. vecP.z .. "}")
    -- local vec = self:GetWorldPosition()
    -- local vecP = oPlayer:GetPosition()
    -- print(self:GetName().." LOCAL POS : {" .. vec.x .. ", ".. vec.y .. ", ".. vec.z .. "}")
    -- print(oPlayer:GetName().." LOCAL POS : {" .. vecP.x .. ", ".. vecP.y .. ", ".. vecP.z .. "}")
    -- local res = vecP - vec
    -- print("        DIFF POS : {" .. res.x .. ", ".. res.y .. ", ".. res.z .. "}")
    -- print("___________________")
    -- print("pos sphere : {" .. vec.x .. ", ".. vec.y .. ", ".. vec.z .. "}")
    -- local vec2 = self:GetWorldPosition()
    -- print("WORLD POS sphere : {" .. vec2.x .. ", ".. vec2.y .. ", ".. vec2.z .. "}")
end

function OnDestroy() end
