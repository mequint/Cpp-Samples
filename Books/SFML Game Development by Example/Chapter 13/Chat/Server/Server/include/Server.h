#pragma once

#include <functional>
#include <SFML/Network.hpp>
#include <unordered_map>

#include "NetworkDefinitions.h"
#include "PacketTypes.h"

#define HEARTBEAT_INTERVAL 1000
#define HEARTBEAT_RETRIES 5

struct ClientInfo {
	ClientInfo(const sf::IpAddress& ip, const PortNumber& port, const sf::Time& heartbeat) :
		m_clientIP(ip), m_clientPort(port), m_lastHeartbeat(heartbeat), m_heartbeatWaiting(false),
		m_heartbeatRetry(0), m_ping(0) {}

	ClientInfo& operator=(const ClientInfo& rhs) {
		m_clientIP = rhs.m_clientIP;
		m_clientPort = rhs.m_clientPort;
		m_lastHeartbeat = rhs.m_lastHeartbeat;
		m_heartbeatSent = rhs.m_heartbeatSent;
		m_heartbeatWaiting = rhs.m_heartbeatWaiting;
		m_heartbeatRetry = rhs.m_heartbeatRetry;
		m_ping = rhs.m_ping;

		return *this;
	}

	sf::IpAddress m_clientIP;
	PortNumber m_clientPort;
	sf::Time m_lastHeartbeat;
	sf::Time m_heartbeatSent;

	bool m_heartbeatWaiting;
	unsigned short m_heartbeatRetry;
	unsigned int m_ping;
};

using Clients = std::unordered_map<ClientID, ClientInfo>;

class Server;
using PacketHandler = std::function<void(sf::IpAddress&, const PortNumber&, const PacketID&, sf::Packet&, Server*)>;
using TimeoutHandler = std::function<void(const ClientID&)>;

class Server {
public:
	template <class T>
	Server(void(T::*handler)(sf::IpAddress&, const PortNumber&, const PacketID&, sf::Packet& packet, Server*),
		T* instance) : m_listenThread(&Server::Listen, this) {

		m_packetHandler = std::bind(handler, instance, std::placeholders::_1, std::placeholders_2,
			std::placeholders::_3, std::placeholders::_4, std::placeholders::_5);
	}

	Server(void(*handler)(sf::IpAddress&, const PortNumber&, const PacketID&, sf::Packet&, Server*));
	~Server();

	template <class T>
	void BindTimeoutHandler(void(T::*handler)(const ClientID&), T* instance) {
		m_timeoutHandler = std::bind(handler, instance, std::placeholders::_1);
	}

	void BindTimeoutHandler(void(*handler)(const ClientID&));

	bool Send(const ClientID& id, sf::Packet& packet);
	bool Send(sf::IpAddress& ip, const PortNumber& port, sf::Packet& packet);
	void Broadcast(sf::Packet& packet, const ClientID& ignore = ClientID(Network::NullID));

	void Listen();
	void Update(const sf::Time& time);

	ClientID AddClient(const sf::IpAddress& ip, const PortNumber& port);
	ClientID GetClientID(const sf::IpAddress& ip, const PortNumber& port);

	bool HasClient(const ClientID& id);
	bool HasClient(const sf::IpAddress& ip, const PortNumber& port);
	bool GetClientInfo(const ClientID& id, ClientInfo& info);
	bool RemoveClient(const ClientID& id);
	bool RemoveClient(const sf::IpAddress& ip, const PortNumber& port);

	void DisconnectAll();
	bool Start();
	bool Stop();

	bool IsRunning();

	unsigned int GetClientCount();
	std::string GetClientList();

	sf::Mutex& GetMutex();

private:
	void Setup();

	ClientID m_lastID;

	sf::UdpSocket m_incoming;
	sf::UdpSocket m_outgoing;

	PacketHandler m_packetHandler;
	TimeoutHandler m_timeoutHandler;

	Clients m_clients;
	sf::Time m_serverTime;

	bool m_running;

	sf::Thread m_listenThread;
	sf::Mutex m_mutex;

	size_t m_totalSent;
	size_t m_totalReceived;
};