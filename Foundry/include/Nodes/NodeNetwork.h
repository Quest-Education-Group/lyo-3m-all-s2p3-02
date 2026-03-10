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
	void ConnectTo(const char* addressIP, int addressPort);
	void CloseNetwork();
	void PrintNetworkInfos();
	void SendMsgToServer(const char* message);
	void SendMsgToClients(const char* message);

	void SetNetworkPort(int const addressPORT);
	Network& GetNetwork() { return m_network; };

protected:

private:

	Network m_network;
};

#endif