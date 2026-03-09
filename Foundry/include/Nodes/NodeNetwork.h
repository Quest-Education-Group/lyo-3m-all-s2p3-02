#ifndef FOUNDRY_NODENETWORK__H_
#define FOUNDRY_NODENETWORK__H_

#include "Node.h"
#include "Network.h"

enum class NetworkType 
{
	SERVER,
	CLIENT
};

class NodeNetwork : public Node
{
public:
	NodeNetwork(std::string const& name);
	~NodeNetwork() override = default;

	virtual void OnUpdate(double delta) override;

	void InitNetworkFor(NetworkType type);
	void CloseNetwork();

	void SetNetworkPort(int const addressPORT);

	Network& GetNetwork() { return m_network; };

protected:

private:

	Network m_network;
};

#endif