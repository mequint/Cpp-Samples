#pragma once

struct Tile {
	Tile(const std::string& name, int id, bool isSolid) :
		Name(name),
		Id(id),
		IsSolid(isSolid) {
	}

	std::string Name;
	int Id;
	bool IsSolid;
};