---@class node
self = self

local iMoveSpeed
local iJumpForce
local oRB

local iLastJumpTime = 0
local iJumpCooldownDuration = 1

self.MoveForward = function(icForward)
    if not oRB then return end
    oRB:ApplyLocalForceAtCenterOfMass(fmath.vec3:new(0, 0, -iMoveSpeed))
end

self.MoveBackward = function(icBackward)
    if not oRB then return end
    oRB:ApplyLocalForceAtCenterOfMass(fmath.vec3:new(0, 0, iMoveSpeed))
end

self.MoveLeft = function(icLeft)
    if not oRB then return end
    oRB:ApplyLocalForceAtCenterOfMass(fmath.vec3:new(-iMoveSpeed, 0, 0))
end

self.MoveRight = function(icRight)
    if not oRB then return end
    oRB:ApplyLocalForceAtCenterOfMass(fmath.vec3:new(iMoveSpeed, 0, 0))
end

self.Jump = function(icJump)
    if not oRB then return end

    local iCurTime = os.clock()
    if iLastJumpTime > iCurTime then return end
    iLastJumpTime = iCurTime + iJumpCooldownDuration

    print("saute")
    oRB:ApplyLocalForceAtCenterOfMass(fmath.vec3:new(0, iJumpForce, 0))
end

function self:SetMoveSpeed(iNewMoveSpeed)
    assert(type(iMoveSpeed) == "number", "MovementComponent: Valid number expected for move speed")
    iMoveSpeed = iNewMoveSpeed
end

function self:GetMoveSpeed()
    return iMoveSpeed
end

function self:SetJumpForce(iNewJumpForce)
    assert(type(iNewJumpForce) == "number", "MovementComponent: Valid number expected for jump force")
    iJumpForce = iNewJumpForce
end

function self:GetJumpForce()
    return iJumpForce
end

function self:SetJumpCooldown(iNewJumpCooldownDuration)
    assert(type(iNewJumpCooldownDuration) == "number", "MovementComponent: Valid number expected for jump cooldown")
    iJumpCooldownDuration = iNewJumpCooldownDuration
end

function self:GetJumpCooldown()
    return iJumpCooldownDuration
end

function self:Setup(oNewRigidBody, iNewMoveSpeed, iNewJumpForce)
    assert(oNewRigidBody ~= nil, "MovementComponent: Valid rigidbody must be provided")

    oRB = oNewRigidBody
    iMoveSpeed = iNewMoveSpeed or 100
    iJumpForce = iNewJumpForce or 5000

    print("MovementComponent Initialized")
end