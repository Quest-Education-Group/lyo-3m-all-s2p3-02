---@type NodeRigidBody

local self = self
local oActivatorComponent
local oReceiverComponent
local bIsCollected = false

local function ResetInteraction()
    oReceiverComponent:SetInteract(true)
end

function self:Interaction()
    --Collect the key()
    oActivatorComponent:DoAction()
end

function self:GetPrompt()
    return "Press F to collect the key"
end

function OnInit()
    local oCompContainer = self:FindChild("components")
    oReceiverComponent = oCompContainer:FindChild("InteractReceiverComponent")
    oActivatorComponent = self:GetNode("/SceneRoot/RB_Door/components/ActivableComponent")

    if not oActivatorComponent then return end
end

function OnUpdate(iDelta) end

function OnDestroy() end