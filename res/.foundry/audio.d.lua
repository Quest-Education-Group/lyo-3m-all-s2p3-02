-- -- NodeAudioListener -- --
---@class NodeAudioListener
AudioListener = {}

-- Constructeur de la classe NodeAudioListener
---@param name
---@return NodeAudioListener
function NodeAudioListener:new(name) end

-- Exemple de methode
---@return vec3
function NodeAudioListener:GetListenerPosition() end

---@param position
function NodeAudioListener:SetListenerPosition(position) end

---@return vec3
function NodeAudioListener:GetListenerDirection() end

---@param position
function NodeAudioListener:SetListenerDirection(position) end


-- -- NodeAudioEmitter -- --
---@class NodeAudioEmitter
AudioListener = {}

-- Constructeur de la classe NodeAudioEmitter
---@param name
---@return NodeAudioEmitter
function NodeAudioEmitter:new(name) end

---@param filePath
---@return boolean
function NodeAudioEmitter:Load(filePath) end

function NodeAudioEmitter:Play() end
function NodeAudioEmitter:Stop() end

---@param isLooping
function NodeAudioEmitter:SetLoop(isLooping) end

---@param position
function NodeAudioEmitter:SetSourcePosition(position) end

---@return vec3
function NodeAudioEmitter:GetSourcePosition() end

---@return boolean
function NodeAudioEmitter:IsPlaying() end