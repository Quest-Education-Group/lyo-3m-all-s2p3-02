local iMoveSpeed = 2000.0
local parent
local oCurrentEntity

local function MoveForward(icForward) print("move forward")
    self:ApplyLocalForceAtCenterOfMass(fmath.vec3:new(0, 0, -iMoveSpeed))
end

local function MoveBackward(icBackward) print("move backward")
    self:ApplyLocalForceAtCenterOfMass(fmath.vec3:new(0, 0, iMoveSpeed))
end

local function MoveLeft(icLeft) print("move left")
    self:ApplyLocalForceAtCenterOfMass(fmath.vec3:new(-iMoveSpeed, 0, 0))
end

local function MoveRight(icRight) print("move right")
    self:ApplyLocalForceAtCenterOfMass(fmath.vec3:new(iMoveSpeed, 0, 0))
end

local function MoveDown(icDown) print("move down")
    self:ApplyLocalForceAtCenterOfMass(fmath.vec3:new(0, -iMoveSpeed, 0))
end

local function MoveUp(icUp) print("move up")
    self:ApplyLocalForceAtCenterOfMass(fmath.vec3:new(0, iMoveSpeed, 0))
end

local function RotateRight(icRight) print("Rotate right")
    self:ApplyWorldTorque(fmath.vec3:new(0, iMoveSpeed, 0))
end

local function RotateLeft(icLeft) print("move left")
    self:ApplyWorldTorque(fmath.vec3:new(0, -iMoveSpeed, 0))
end

local function SetCurrentEntity(ndHit)
    if oCurrentEntity == ndHit then
        return
    end

    oCurrentEntity = ndHit
end

local function CheckInteraction()
    local hit = physics.Raycast(parent:GetPosition(), parent:GetLocalForward()*-1, 1)

    if not hit then
        print("there is nothing there, clement")
        SetCurrentEntity(nil)
        return
    end

    if not hit.node then
        print("Node not found in the hit")
        SetCurrentEntity(nil)
        return
    end

    local ircomp = hit.node:FindChild("InteractRecieverComponent")

    if not ircomp then
        print("This node doesn't have interact reciever component")
        SetCurrentEntity(hit.node)
        return
    end

    if ircomp:CanInteract() then
        print(ircomp:GetPrompt())
    end

    SetCurrentEntity(hit.node)
end

local function TryInteract()
    if not oCurrentEntity then return end

    local ircomp = oCurrentEntity:FindChild("InteractRecieverComponent")

    if not ircomp then
        print("Cannot interact with"..oCurrentEntity:GetName())
        return
    end

    if ircomp:CanInteract() then
        ircomp:Interact()
    else
        print("Interactable, but not now because I decided so")
    end
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

    actionmap:GetAction("INTERACT").Event = TryInteract
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

    timer.Create("RaycastDelay", 3, 100000, CheckInteraction)
end

function OnUpdate(dt)
    
end

function OnDestroy()
    
end
