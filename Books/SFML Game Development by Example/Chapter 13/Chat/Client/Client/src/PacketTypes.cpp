#include "PacketTypes.h"

void StampPacket(const PacketType& type, sf::Packet& packet) {
	packet << PacketID(type);
}
