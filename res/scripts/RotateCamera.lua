local iMoveSpeed = 3000.0
local parent
local oCurrentEntity
local oCamera

function MoveForward(icForward) print("move forward")
    self:ApplyLocalForceAtCenterOfMass(fmath.vec3:new(0, 0, -iMoveSpeed))
end

function MoveBackward(icBackward) print("move backward")
    self:ApplyLocalForceAtCenterOfMass(fmath.vec3:new(0, 0, iMoveSpeed))
end

function MoveLeft(icLeft) print("move left")
    self:ApplyLocalForceAtCenterOfMass(fmath.vec3:new(-iMoveSpeed, 0, 0))
end

function MoveRight(icRight) print("move right")
    self:ApplyLocalForceAtCenterOfMass(fmath.vec3:new(iMoveSpeed, 0, 0))
end

function MoveDown(icDown) print("move down")
    self:ApplyLocalForceAtCenterOfMass(fmath.vec3:new(0, -iMoveSpeed, 0))
end

function MoveUp(icUp) print("move up")
    self:ApplyLocalForceAtCenterOfMass(fmath.vec3:new(0, iMoveSpeed, 0))
end

function RotateRight(icRight) print("Rotate right")
    self:ApplyWorldTorque(fmath.vec3:new(0, iMoveSpeed, 0))
end

function RotateLeft(icLeft) print("move left")
    self:ApplyWorldTorque(fmath.vec3:new(0, -iMoveSpeed, 0))
end

function SetCurrentEntity(ndHit)
    if oCurrentEntity == ndHit then
        return
    end

    oCurrentEntity = ndHit
end

function CheckInteraction()
    print("Checking what is forward")
    local hit = physics.Raycast(parent:GetPosition(), parent:GetLocalForward()*-1, 10)

    if not hit then
        print("there is nothing there, clement")
        return
    end

    if not hit.node then
        print("Node not found in the hit")
        return
    end

    -- local hitNode = hit.node
    -- local child = hitNode:FindChild("InteractReciever")

    -- if not child then
    --     print("element touche: "..hitNode:GetName())
    --     return
    -- end

    -- if child:CanInteract() then
    --     print("element touche: "..hitNode:GetName())
    --     child:GetPrompt()
    --     SetCurrentEntity(child)
    -- else
    --     print("Cannot be interacted")
    -- end
end

function TryInteract()
    oCurrentEntity:Interact()
end

local function InitActionMap()
    local actionmap = actionmap:new("DEFAULT_ACTION_MAP")

    actionmap:CreateAction("MOVE_FORWARD", 1, 90)
    actionmap:CreateAction("MOVE_BACKWARD", 1, 83)
    actionmap:CreateAction("MOVE_LEFT", 1, 81)
    actionmap:CreateAction("MOVE_RIGHT", 1, 68)
    actionmap:CreateAction("MOVE_DOWN", 1, 65)
    actionmap:CreateAction("MOVE_UP", 1, 69)

    actionmap:CreateAction("ROTATE_RIGHT", 1, 87)
    actionmap:CreateAction("ROTATE_LEFT", 1, 88)

    actionmap:CreateAction("INTERACT", 1, 70)

    actionmap:GetAction("MOVE_FORWARD").Event = MoveForward
    actionmap:GetAction("MOVE_BACKWARD").Event = MoveBackward
    actionmap:GetAction("MOVE_LEFT").Event = MoveLeft
    actionmap:GetAction("MOVE_RIGHT").Event = MoveRight
    actionmap:GetAction("MOVE_DOWN").Event = MoveDown
    actionmap:GetAction("MOVE_UP").Event = MoveUp
    
    actionmap:GetAction("ROTATE_RIGHT").Event = RotateRight
    actionmap:GetAction("ROTATE_LEFT").Event = RotateLeft

    actionmap:GetAction("INTERACT").Event = CheckInteraction
end

function InitRB()
    self:SetBodyType(2)
    self:SetMass(10)
    self:SetIsGravityEnabled(true)
    self:LockAngularAxis(true,false,true)
    self:SetLinearDamping(1)
    self:SetAngularDamping(0.5)
    parent = self:GetNode3DParent()
end

function OnInit() 
    InitRB()
    InitActionMap()
    --oCamera = self:

    --timer.Create("RaycastDelay", 1, 100000, CheckInteraction)
end

function OnUpdate(dt)
    
end

function OnDestroy()
    
end
