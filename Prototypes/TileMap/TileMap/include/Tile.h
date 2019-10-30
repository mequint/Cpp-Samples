#pragma once

struct Tile {
	Tile() {}
	Tile(const std::string& name, int id, bool isSolid, bool isWarp) :
		Name(name),
		Id(id),
		IsSolid(isSolid),
		IsWarp(isWarp)	{
	}

	std::string Name;
	int Id;
	bool IsSolid;
	bool IsWarp;
};