
class Node3D::Proxy : public Node::Proxy
{
public:
	struct ProxyBinding;

	Proxy(Node& node) : Node::Proxy(node) {}
	
	const glm::vec3& GetPosition() const		{ return m_pNode->GetPosition(); }
	float GetX() const							{ return m_pNode->GetX(); }
	float GetY() const							{ return m_pNode->GetY(); }
	float GetZ() const							{ return m_pNode->GetZ(); }
	const glm::mat4& GetMatrixRotation()		{ return m_pNode->GetMatrixRotation(); }
	//const glm::mat4& GetInverseMatrixRotation() { return m_pNode->GetInverseMatrixRotation(); }
	const glm::vec3& GetRotation() const		{ return m_pNode->GetRotation(); }
	float GetYaw() const						{ return m_pNode->GetYaw(); }
	float GetPitch() const						{ return m_pNode->GetPitch(); }
	float GetRoll() const						{ return m_pNode->GetRoll(); }
	float GetMaxScale() const					{ return m_pNode->GetMaxScale(); }
	float GetMinScale() const					{ return m_pNode->GetMinScale(); }
	const glm::vec3& GetScale() const			{ return m_pNode->GetScale(); }
	const glm::vec3& GetRight()					{ return m_pNode->GetRight(); }
	const glm::vec3& GetUp()					{ return m_pNode->GetUp(); }
	const glm::vec3& GetForward()				{ return m_pNode->GetForward(); }

	void SetPosition(glm::vec3 pos)				{ m_pNode->SetPosition(pos); }
	void SetX(float x)							{ m_pNode->SetX(x); }
	void SetY(float y)							{ m_pNode->SetY(y); }
	void SetZ(float z)							{ m_pNode->SetZ(z); }
	void SetRotation(glm::vec3 rot)				{ m_pNode->SetRotation(rot); }
	void SetYaw(float yaw)						{ m_pNode->SetYaw(yaw); }
	void SetPitch(float pitch)					{ m_pNode->SetPitch(pitch); }
	void SetRoll(float roll)					{ m_pNode->SetRoll(roll); }
	void SetScale(glm::vec3 scale)				{ m_pNode->SetScale(scale); }

	void AddPosition(glm::vec3 pos)				{ m_pNode->AddPosition(pos); }
	void AddX(float x)							{ m_pNode->AddX(x); }
	void AddY(float y)							{ m_pNode->AddY(y); }
	void AddZ(float z)							{ m_pNode->AddZ(z); }
	void AddRotation(glm::vec3 rot)				{ m_pNode->AddRotation(rot); }
	void AddYaw(float yaw)						{ m_pNode->AddYaw(yaw); }
	void AddPitch(float pitch)					{ m_pNode->AddPitch(pitch); }
	void AddRoll(float roll)					{ m_pNode->AddRoll(roll); }
	void AddScale(glm::vec3 scale)				{ m_pNode->AddScale(scale); }

private:
	Node3D* m_pNode;
};

BindProxy(Node3D::Proxy,
	binder.BindClass<Node3D::Proxy>("Node3D",
	"GetPosition", BIND(GetPosition),
	"GetX", BIND(GetX),
	"GetY", BIND(GetY),
	"GetZ", BIND(GetZ),
	"GetMatrixRotation", BIND(GetMatrixRotation),
	//"GetInverseMatrixRotation", BIND(GetInverseMatrixRotation),
	"GetRotation", BIND(GetRotation),
	"GetYaw", BIND(GetYaw),
	"GetPitch", BIND(GetPitch),
	"GetRoll", BIND(GetRoll),
	"GetMaxScale", BIND(GetMaxScale),
	"GetMinScale", BIND(GetMinScale),
	"GetScale", BIND(GetScale),
	"GetRight", BIND(GetRight),
	"GetUp", BIND(GetUp),
	"GetForward", BIND(GetForward),

	"SetPosition", BIND(SetPosition),
	"SetX", BIND(SetX),
	"SetY", BIND(SetY),
	"SetZ", BIND(SetZ),
	"SetRotation", BIND(SetRotation),
	"SetYaw", BIND(SetYaw),
	"SetPitch", BIND(SetPitch),
	"SetRoll", BIND(SetRoll),
	"SetScale", BIND(SetScale),
	"AddPosition", BIND(AddPosition),
	"AddX", BIND(AddX),
	"AddY", BIND(AddY),
	"AddZ", BIND(AddZ),
	"AddRotation", BIND(AddRotation),
	"AddYaw", BIND(AddYaw),
	"AddPitch", BIND(AddPitch),
	"AddRoll", BIND(AddRoll),
	"AddScale", BIND(AddScale));
)