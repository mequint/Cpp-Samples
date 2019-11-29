#include "Server.h"

#include <iostream>

Server::Server(void(*handler)(sf::IpAddress &, const PortNumber &, const PacketID &, sf::Packet &, Server *)) :
	m_listenThread(&Server::Listen, this), m_running(false) {

	m_packetHandler = std::bind(handler, std::placeholders::_1, std::placeholders::_2,
		std::placeholders::_3, std::placeholders::_4, std::placeholders::_5);
}

Server::~Server() {
	Stop();
}

void Server::BindTimeoutHandler(void(*handler)(const ClientID &)) {
	m_timeoutHandler = std::bind(handler, std::placeholders::_1);
}

bool Server::Send(const ClientID & id, sf::Packet & packet) {
	sf::Lock lock(m_mutex);

	auto iter = m_clients.find(id);
	if (iter == m_clients.end()) return false;

	if (m_outgoing.send(packet, iter->second.m_clientIP, iter->second.m_clientPort) != sf::Socket::Done) {
		std::cout << "Error sending a packet..." << std::endl;
		return false;
	}

	m_totalSent += packet.getDataSize();

	return true;
}

bool Server::Send(sf::IpAddress & ip, const PortNumber & port, sf::Packet & packet) {
	if (m_outgoing.send(packet, ip, port) != sf::Socket::Done) return false;

	m_totalSent += packet.getDataSize();
	return true;
}

void Server::Broadcast(sf::Packet & packet, const ClientID & ignore) {
	sf::Lock lock(m_mutex);

	for (auto& iter : m_clients) {
		if (iter.first != ignore) {
			if (m_outgoing.send(packet, iter.second.m_clientIP, iter.second.m_clientPort) != sf::Socket::Done) {
				std::cout << "Error broadcasting a packet to client: " << iter.first << std::endl;
				continue;
			}

			m_totalSent += packet.getDataSize();
		}
	}
}

void Server::Listen() {
	sf::IpAddress ip;
	PortNumber port;
	sf::Packet packet;

	std::cout << "Beginning to listen..." << std::endl;

	while (m_running) {
		packet.clear();
		
		sf::Socket::Status status = m_incoming.receive(packet, ip, port);
		if (status != sf::Socket::Done) {
			if (m_running) {
				std::cout << "Error receiving a packet from: " << ip << ":" << port << ". Code:" << status << std::endl;
				continue;
			}
			else {
				std::cout << "Socket unbound." << std::endl;
				break;
			}
		}

		m_totalReceived += packet.getDataSize();

		PacketID pId;

		// Non-conventional packet
		if (!(packet >> pId)) {
			std::cout << "Invalid packet received: unable to extract id." << std::endl;
			continue;
		}

		// Invalid packet type
		PacketType type = static_cast<PacketType>(pId);
		if (type < PacketType::Disconnect || type >= PacketType::OutOfBounds) {
			std::cout << "Invalid packet received: id is out of bounds." << std::endl;
			continue;
		}

		if (type == PacketType::Heartbeat) {
			bool clientFound = false;
			
			sf::Lock lock(m_mutex);

			for (auto& iter : m_clients) {
				if (iter.second.m_clientIP != ip || iter.second.m_clientPort != port) continue;

				clientFound = true;

				if (!iter.second.m_heartbeatWaiting) {
					std::cout << "Invalid heartbeat packet received!" << std::endl;
					break;
				}

				iter.second.m_ping = m_serverTime.asMilliseconds() - iter.second.m_heartbeatSent.asMilliseconds();
				iter.second.m_lastHeartbeat = m_serverTime;
				iter.second.m_heartbeatWaiting = false;
				iter.second.m_heartbeatRetry = 0;
				break;
			}

			if (!clientFound) {
				std::cout << "Heartbeat from unknown client received..." << std::endl;
			}
		}
		else if (m_packetHandler) {
			m_packetHandler(ip, port, static_cast<PacketID>(type), packet, this);
		}
	}

	std::cout << "...Listening stopped." << std::endl;
}

void Server::Update(const sf::Time & time) {
	m_serverTime += time;

	if (m_serverTime.asMilliseconds() < 0) {
		m_serverTime -= sf::milliseconds(sf::Int32(Network::HighestTimestamp));

		sf::Lock lock(m_mutex);
		for (auto& iter : m_clients) {
			iter.second.m_lastHeartbeat = sf::milliseconds(std::abs(iter.second.m_lastHeartbeat.asMilliseconds() -
				sf::Int32(Network::HighestTimestamp)));
		}
	}

	sf::Lock lock(m_mutex);

	for (auto iter = m_clients.begin(); iter != m_clients.end(); ) {
		sf::Int32 elapsed = m_serverTime.asMilliseconds() - iter->second.m_lastHeartbeat.asMilliseconds();

		if (elapsed >= HEARTBEAT_INTERVAL) {
			if (elapsed >= sf::Int32(Network::ClientTimeout) || iter->second.m_heartbeatRetry > HEARTBEAT_RETRIES) {
				// Remove client
				std::cout << "Client " << iter->first << " has timed out." << std::endl;

				if (m_timeoutHandler) {
					m_timeoutHandler(iter->first);
				}

				iter = m_clients.erase(iter);
				continue;
			}

			if (!iter->second.m_heartbeatWaiting || (elapsed >= HEARTBEAT_INTERVAL * (iter->second.m_heartbeatRetry + 1))) {
				// Heartbeat
				if (iter->second.m_heartbeatRetry >= 3) {
					std::cout << "Re-try(" << iter->second.m_heartbeatRetry << ") heartbeat for client " << iter->first << std::endl;
				}

				sf::Packet heartbeat;
				StampPacket(PacketType::Heartbeat, heartbeat);

				heartbeat << m_serverTime.asMilliseconds();
				Send(iter->first, heartbeat);

				if (iter->second.m_heartbeatRetry == 0) {
					iter->second.m_heartbeatSent = m_serverTime;
				}

				iter->second.m_heartbeatWaiting = true;
				++iter->second.m_heartbeatRetry;

				m_totalSent += heartbeat.getDataSize();
			}
		}

		++iter;
	}
}

ClientID Server::AddClient(const sf::IpAddress& ip, const PortNumber& port) {
	sf::Lock lock(m_mutex);

	for (auto& iter : m_clients) {
		if (iter.second.m_clientIP == ip && iter.second.m_clientPort == port) {
			return ClientID(Network::NullID);
		}
	}

	ClientID id = m_lastID;
	ClientInfo info(ip, port, m_serverTime);

	m_clients.emplace(id, info);
	++m_lastID;

	return id;
}

ClientID Server::GetClientID(const sf::IpAddress& ip, const PortNumber& port) {
	sf::Lock lock(m_mutex);
	for (auto& iter : m_clients) {
		if (iter.second.m_clientIP == ip && iter.second.m_clientPort == port) return iter.first;
	}

	return ClientID(Network::NullID);
}

bool Server::HasClient(const ClientID& id) {
	return m_clients.find(id) != m_clients.end();
}

bool Server::HasClient(const sf::IpAddress& ip, const PortNumber & port) {
	return GetClientID(ip, port) >= 0;
}

bool Server::GetClientInfo(const ClientID& id, ClientInfo & info) {
	sf::Lock lock(m_mutex);
	for (auto& iter : m_clients) {
		if (iter.first == id) {
			info = iter.second;
			return true;
		}
	}

	return false;
}

bool Server::RemoveClient(const ClientID& id) {
	sf::Lock lock(m_mutex);

	auto iter = m_clients.find(id);
	if (iter == m_clients.end()) return false;

	sf::Packet p;
	StampPacket(PacketType::Disconnect, p);
	Send(id, p);
	m_clients.erase(iter);

	return true;
}

bool Server::RemoveClient(const sf::IpAddress& ip, const PortNumber& port) {
	sf::Lock lock(m_mutex);

	for (auto iter = m_clients.begin(); iter != m_clients.end(); ++iter) {
		if (iter->second.m_clientIP == ip && iter->second.m_clientPort == port) {
			sf::Packet p;
			StampPacket(PacketType::Disconnect, p);
			Send(iter->first, p);
			m_clients.erase(iter);
			return true;
		}
	}

	return false;
}

void Server::DisconnectAll() {
	if (!m_running) return;

	sf::Packet p;
	StampPacket(PacketType::Disconnect, p);
	Broadcast(p);

	sf::Lock lock(m_mutex);
	m_clients.clear();
}

bool Server::Start() {
	if (m_running) return false;
	if (m_incoming.bind(static_cast<unsigned short>(Network::ServerPort) != sf::Socket::Done)) return false;

	m_outgoing.bind(sf::Socket::AnyPort);

	Setup();

	std::cout << "Incoming port: " << m_incoming.getLocalPort() << ". Outgoing port: " << m_outgoing.getLocalPort() << std::endl;

	m_listenThread.launch();

	m_running = true;
	return true;
}

bool Server::Stop() {
	if (!m_running) return false;
	DisconnectAll();

	m_running = false;
	m_incoming.unbind();

	return true;
}

bool Server::IsRunning() { return m_running; }
unsigned int Server::GetClientCount() { return m_clients.size(); }

std::string Server::GetClientList() {
	std::string list;
	std::string delimiter = "--------------------------------------";
	list = delimiter;
	list += '\n';
	list += "ID";
	list += '\t';
	list += "Client IP:PORT";
	list += '\t'; list += '\t';
	list += "Ping";
	list += '\n';
	list += delimiter;
	list += '\n';

	for (auto iter = m_clients.begin(); iter != m_clients.end(); ++iter) {
		list += std::to_string(iter->first);
		list += '\t';
		list += iter->second.m_clientIP.toString() + ":" + std::to_string(iter->second.m_clientPort);
		list += '\t';
		list += std::to_string(iter->second.m_ping) + "ms.";
		list += '\n';
	}

	list += delimiter;
	list += '\n';
	list += "Total data sent: " + std::to_string(m_totalSent / 1000) + "kB. Total data received: " +
		std::to_string(m_totalReceived / 1000) + "kB";

	return list;
}

sf::Mutex& Server::GetMutex() { return m_mutex; }

void Server::Setup() {
	m_lastID = 0;
	m_running = false;
	m_totalSent = 0;
	m_totalReceived = 0;
}