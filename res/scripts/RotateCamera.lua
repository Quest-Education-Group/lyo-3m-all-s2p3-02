function OnInit()
    print(self)
end

function OnUpdate(dt)
    local vec = fmath.vec3:new(0, dt, 0)
    self:AddLocalRotation(vec)
end

function OnDestroy()
end
