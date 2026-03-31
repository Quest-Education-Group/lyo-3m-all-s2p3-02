
-- -- AudioServer -- --
---@class AudioServer
AudioServer = {}
---@return boolean
function AudioServer:Init() end
function AudioServer:Shutdown() end
---@param name string
---@return AudioChannel
function AudioServer:CreateChannel(name) end
---@param volume number
function AudioServer:SetMasterVolume(volume) end
---@return number
function AudioServer:GetMasterVolume() end
---@param channel AudioChannel
---@param volume number
function AudioServer:SetGroupVolume(channel, volume) end
---@param channel AudioChannel
---@return number
function AudioServer:GetGroupVolume(channel) end


---@class AudioChannel
AudioChannel = {}


-- -- NodeAudioListener -- --
---@class NodeAudioListener
NodeAudioListener = {}

-- Constructeur de la classe NodeAudioListener
---@param name string
---@return NodeAudioListener
function NodeAudioListener:new(name) end

-- Exemple de methode
---@return vec3
function NodeAudioListener:GetListenerPosition() end

---@param position vec3
function NodeAudioListener:SetListenerPosition(position) end

---@return vec3
function NodeAudioListener:GetListenerDirection() end

---@param position vec3
function NodeAudioListener:SetListenerDirection(position) end


-- -- NodeAudioEmitter -- --
---@class NodeAudioEmitter
NodeAudioEmitter = {}

-- Constructeur de la classe NodeAudioEmitter
---@param name string
---@return NodeAudioEmitter
function NodeAudioEmitter:new(name) end

---@param filePath string
---@param channel AudioChannel
---@return boolean
function NodeAudioEmitter:Load(filePath, channel) end

function NodeAudioEmitter:Play() end
function NodeAudioEmitter:Stop() end

---@param isLooping boolean
function NodeAudioEmitter:SetLoop(isLooping) end

---@param position vec3
function NodeAudioEmitter:SetSourcePosition(position) end

---@return vec3
function NodeAudioEmitter:GetSourcePosition() end

---@return boolean
function NodeAudioEmitter:IsPlaying() end