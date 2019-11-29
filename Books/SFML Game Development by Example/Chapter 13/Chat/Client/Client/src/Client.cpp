#include "Client.h"

Client::Client() : m_listenThread(&Client::Listen, this), m_connected(false) {}
Client::~Client() { m_socket.unbind(); }

bool Client::Connect() {
	if (m_connected) return false;

	m_socket.bind(sf::Socket::AnyPort);
	std::cout << "Bound client to port: " << m_socket.getLocalPort() << std::endl;

	sf::Packet p;
	StampPacket(PacketType::Connect, p);
	p << m_playerName;

	if (m_socket.send(p, m_serverIp, m_serverPort) != sf::Socket::Done) {
		m_socket.unbind();
		return false;
	}

	m_socket.setBlocking(false);
	p.clear();

	sf::IpAddress recvIP;
	PortNumber recvPORT;
	sf::Clock timer;
	timer.restart();

	std::cout << "Attempting to connect to: " << m_serverIp << ":" << m_serverPort << std::endl;

	while (timer.getElapsedTime().asMilliseconds() < CONNECT_TIMEOUT) {
		sf::Socket::Status s = m_socket.receive(p, recvIP, recvPORT);

		if (s != sf::Socket::Done) continue;
		if (recvIP != m_serverIp) continue;

		PacketID id;
		if (!(p >> id)) break;
		if (static_cast<PacketType>(id) != PacketType::Connect) continue;

		m_packetHandler(id, p, this);
		m_connected = true;
		m_socket.setBlocking(true);

		m_lastHeartbeat = m_serverTime;
		m_listenThread.launch();

		return true;
	}

	std::cout << "Connection attempt failed! Server info: " << m_serverIp << ":" << m_serverPort << std::endl;

	m_socket.unbind();
	m_socket.setBlocking(true);

	return false;
}

bool Client::Disconnect() {
	if (!m_connected) return false;

	sf::Packet p;
	StampPacket(PacketType::Disconnect, p);

	sf::Socket::Status s = m_socket.send(p, m_serverIp, m_serverPort);
	m_connected = false;
	m_socket.unbind();

	if (s != sf::Socket::Done) return false;

	return true;
}

void Client::Listen() {
	sf::Packet packet;
	sf::IpAddress recvIP;
	PortNumber recvPORT;

	std::cout << "Beginning to listen..." << std::endl;

	while (m_connected) {
		packet.clear();

		sf::Socket::Status status = m_socket.receive(packet, recvIP, recvPORT);
		if (status != sf::Socket::Done) {
			if (m_connected) {
				std::cout << "Failed receiving a packet from " << recvIP << ":" << recvPORT << ". Status: " <<
					status << std::endl;
				continue;
			}
			else {
				std::cout << "Socket unbound." << std::endl;
				break;
			}
		}

		if (recvIP != m_serverIp) {
			// Ignore
			std::cout << "Invalid packet received: invalid origin." << std::endl;
			continue;
		}

		PacketID pId;
		if (!(packet >> pId)) {
			std::cout << "Invalid packet received: id is out of bounds." << std::endl;
			continue;
		}

		PacketType type = static_cast<PacketType>(pId);
		if (type < PacketType::Disconnect || type >= PacketType::OutOfBounds) {
			std::cout << "Invalid packet received: invalid packet type." << std::endl;
			continue;
		}

		if (type == PacketType::Heartbeat) {
			sf::Packet p;
			StampPacket(PacketType::Heartbeat, p);

			if (m_socket.send(p, m_serverIp, m_serverPort) != sf::Socket::Done) {
				std::cout << "Failed sending a heartbeat!" << std::endl;
			}

			sf::Int32 timestamp;
			packet >> timestamp;

			SetTime(sf::milliseconds(timestamp));
			m_lastHeartbeat = m_serverTime;
		}
		else if (m_packetHandler) {
			m_packetHandler(static_cast<PacketID>(type), packet, this);
		}
	}

	std::cout << "...Listening stopped." << std::endl;
}

bool Client::Send(sf::Packet & packet) {
	if (!m_connected) return false;
	if (m_socket.send(packet, m_serverIp, m_serverPort) != sf::Socket::Done) return false;

	return true;
}

const sf::Time & Client::GetTime() const {
	return m_serverTime;
}

const sf::Time & Client::GetLastHeartbeat() const {
	return m_lastHeartbeat;
}

void Client::SetTime(const sf::Time & time) {
	m_serverTime = time;
}

void Client::SetServerInformation(const sf::IpAddress & ip, const PortNumber & port) {
	m_serverIp = ip;
	m_serverPort = port;
}

void Client::Setup(void(*handler)(const PacketID &, sf::Packet &, Client *)) {
	m_packetHandler = std::bind(handler, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

void Client::UnregisterPacketHandler() {
	m_packetHandler = nullptr;
}

void Client::Update(const sf::Time & time) {
	if (!m_connected) return;

	m_serverTime += time;
	if (m_serverTime.asMilliseconds() < 0) {
		m_serverTime -= sf::milliseconds(sf::Int32(Network::HighestTimestamp));
		m_lastHeartbeat = m_serverTime;
		return;
	}

	if (m_serverTime.asMilliseconds() - m_lastHeartbeat.asMilliseconds() >= sf::Int32(Network::ClientTimeout)) {
		std::cout << "Server connection timed out!" << std::endl;
		Disconnect();
	}
}

bool Client::IsConnected() const { return m_connected; }
void Client::SetPlayerName(const std::string & name) { m_playerName = name; }

sf::Mutex & Client::GetMutex() {
	return m_mutex;
}
