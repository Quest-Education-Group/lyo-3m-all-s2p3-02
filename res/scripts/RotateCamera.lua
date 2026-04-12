local iMoveSpeed = 3.0

function MoveForward(icForward) print("move forward")
    
    -- self:ApplyWorldForceAtCenterOfMass(fmath.vec3:new(0, 0, -iMoveSpeed))
    self:SetLinearVelocity(fmath.vec3:new(0, 0, -iMoveSpeed))
    
    print(self:GetWorldPosition().x, self:GetWorldPosition().y, self:GetWorldPosition().z)
    -- self:SetWorldPosition(fmath.vec3:new(0, 0, -iMoveSpeed))
    print(self:GetWorldPosition().x, self:GetWorldPosition().y, self:GetWorldPosition().z)
    print("\n\n")
end

function MoveBackward(icBackward) print("move backward")
    -- self:ApplyWorldForceAtCenterOfMass(fmath.vec3:new(0, 0, iMoveSpeed))
    self:SetLinearVelocity(fmath.vec3:new(0, 0, iMoveSpeed))

    print(self:GetWorldPosition().x, self:GetWorldPosition().y, self:GetWorldPosition().z)
    -- self:SetWorldPosition(fmath.vec3:new(0, 0, iMoveSpeed))
    print(self:GetWorldPosition().x, self:GetWorldPosition().y, self:GetWorldPosition().z)
    print("\n\n")
end

function MoveLeft(icLeft) print("move left")
    -- self:ApplyWorldForceAtCenterOfMass(fmath.vec3:new(-iMoveSpeed, 0, 0))
    self:SetLinearVelocity(fmath.vec3:new(-iMoveSpeed, 0, 0))

    print(self:GetWorldPosition().x, self:GetWorldPosition().y, self:GetWorldPosition().z)
    -- self:SetWorldPosition(fmath.vec3:new(-iMoveSpeed, 0, 0))
    print(self:GetWorldPosition().x, self:GetWorldPosition().y, self:GetWorldPosition().z)
    print("\n\n")
end

function MoveRight(icRight) print("move right")
    -- self:ApplyWorldForceAtCenterOfMass(fmath.vec3:new(iMoveSpeed, 0, 0))
    self:SetLinearVelocity(fmath.vec3:new(iMoveSpeed, 0, 0))

    print(self:GetWorldPosition().x, self:GetWorldPosition().y, self:GetWorldPosition().z)
    -- self:SetWorldPosition(fmath.vec3:new(iMoveSpeed, 0, 0))
    print(self:GetWorldPosition().x, self:GetWorldPosition().y, self:GetWorldPosition().z)
    print("\n\n")
end

function MoveDown(icDown)
    -- self:ApplyWorldForceAtCenterOfMass(fmath.vec3:new(0, -iMoveSpeed, 0))
    self:SetLinearVelocity(fmath.vec3:new(0, -iMoveSpeed, 0))
end

function MoveUp(icUp)
    -- self:ApplyWorldForceAtCenterOfMass(fmath.vec3:new(0, iMoveSpeed, 0))
    self:SetLinearVelocity(fmath.vec3:new(0, iMoveSpeed*2, 0))
end

function OnInit() print("big shit")
    local actionmap = actionmap:new("DEFAULT_ACTION_MAP")
    
    print("Begin RB INIT ")
    self:SetBodyType(2)
    self:SetMass(1)
    self:SetIsGravityEnabled(true)
    self:LockAngularAxis(true,true,true)
    self:SetLinearDamping(3)
    
    actionmap:CreateAction("MOVE_FORWARD", 1, 90)
    actionmap:CreateAction("MOVE_BACKWARD", 1, 83)
    actionmap:CreateAction("MOVE_LEFT", 1, 81)
    actionmap:CreateAction("MOVE_RIGHT", 1, 68)
    actionmap:CreateAction("MOVE_DOWN", 1, 65)
    actionmap:CreateAction("MOVE_UP", 1, 69)

    actionmap:GetAction("MOVE_FORWARD").Event = MoveForward
    actionmap:GetAction("MOVE_BACKWARD").Event = MoveBackward
    actionmap:GetAction("MOVE_LEFT").Event = MoveLeft
    actionmap:GetAction("MOVE_RIGHT").Event = MoveRight
    actionmap:GetAction("MOVE_DOWN").Event = MoveDown
    actionmap:GetAction("MOVE_UP").Event = MoveUp
end

function OnUpdate(dt)

end

function OnDestroy()

end