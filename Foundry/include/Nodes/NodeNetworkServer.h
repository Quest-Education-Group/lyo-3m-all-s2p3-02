#ifndef FOUNDRY_NODENETWORK__H_
#define FOUNDRY_NODENETWORK__H_

#include "Node.h"
#include "Servers/NetworkServer.h"

class NodeNetwork : public Node
{
public:
	NodeNetwork(std::string const& name);
	~NodeNetwork() override = default;

	virtual void OnUpdate(double delta) override;

	bool InitAsClient();
	bool InitAsServer(uint16 port);
	void ConnectTo(const char* addressIP, int addressPort);

	ENetAddress const& GetAddress() const;

protected:
	NetworkType m_networkType;
};

#endif