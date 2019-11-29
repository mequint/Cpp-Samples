#include <iostream>
#include <SFML/Network.hpp>
#include "Server.h"

void Handler(sf::IpAddress& ip, const PortNumber& port, const PacketID& packetId, sf::Packet& packet, Server* server) {
	ClientID id = server->GetClientID(ip, port);
	if (id >= 0) {
		if (static_cast<PacketType>(packetId) == PacketType::Disconnect) {
			server->RemoveClient(ip, port);

			sf::Packet p;
			StampPacket(PacketType::Message, p);
			
			std::string message;
			message = "Client left! " + ip.toString() + ":" + std::to_string(port);
			p << message;
			server->Broadcast(p, id);
		}
		else if (static_cast<PacketType>(packetId) == PacketType::Message) {
			std::string receivedMessage;
			packet >> receivedMessage;

			std::string message = ip.toString() + ":" + std::to_string(port) + " :" + receivedMessage;
			sf::Packet p;

			StampPacket(PacketType::Message, p);
			p << message;
			server->Broadcast(p, id);
		}
	}
	else {
		if (static_cast<PacketType>(packetId) == PacketType::Connect) {
			ClientID id = server->AddClient(ip, port);

			sf::Packet packet;
			StampPacket(PacketType::Connect, packet);
			server->Send(id, packet);
		}
	}
}

void CommandProcess(Server* server) {
	while (server->IsRunning()) {
		std::string str;
		std::getline(std::cin, str);

		if (str == "!quit") {
			server->Stop();
			break;
		}
		else if (str == "dc") {
			server->DisconnectAll();
			std::cout << "DC..." << std::endl;
		}
		else if (str == "list") {
			std::cout << server->GetClientCount() << " clients online:" << std::endl;
			std::cout << server->GetClientList() << std::endl;
		}
	}
}

int main() {
	Server server(Handler);

	if (server.Start()) {
		sf::Thread c(&CommandProcess, &server);
		c.launch();

		sf::Clock clock;
		clock.restart();

		while (server.IsRunning()) {
			server.Update(clock.restart());
		}

		std::cout << "Stopping server..." << std::endl;
	}

	std::cout << "Press 'Enter' to continue";
	std::cin.get();

	return EXIT_SUCCESS;
}