#pragma once

#include <functional>
#include <iostream>
#include <SFML/Network.hpp>
#include "NetworkDefinitions.h"
#include "PacketTypes.h"

#define CONNECT_TIMEOUT 5000	// ms

class Client;
using PacketHandler = std::function<void(const PacketID&, sf::Packet&, Client*)>;

class Client {
public:
	Client();
	~Client();

	bool Connect();
	bool Disconnect();

	void Listen();
	bool Send(sf::Packet& packet);

	const sf::Time& GetTime() const;
	const sf::Time& GetLastHeartbeat() const;
	void SetTime(const sf::Time& time);
	void SetServerInformation(const sf::IpAddress& ip, const PortNumber& port);

	template <class T>
	void Setup(void(T::*handler)(const PacketID&, sf::Packet&, Client*), T* instance) {
		m_packetHandler = std::bind(handler, instance,
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	}

	void Setup(void(*handler)(const PacketID&, sf::Packet&, Client*));
	void UnregisterPacketHandler();

	void Update(const sf::Time& time);

	bool IsConnected() const;
	void SetPlayerName(const std::string& name);

	sf::Mutex& GetMutex();

private:
	std::string m_playerName;

	sf::UdpSocket m_socket;
	sf::IpAddress m_serverIp;
	PortNumber m_serverPort;
	PacketHandler m_packetHandler;
	
	bool m_connected;
	sf::Time m_serverTime;
	sf::Time m_lastHeartbeat;

	sf::Thread m_listenThread;
	sf::Mutex m_mutex;
};