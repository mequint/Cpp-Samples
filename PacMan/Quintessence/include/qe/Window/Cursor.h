#pragma once

namespace qe {
	enum class CursorType {
		Arrow = sf::Cursor::Arrow,
		ArrowWait = sf::Cursor::ArrowWait,
		Wait = sf::Cursor::Wait,
		Text = sf::Cursor::Text,
		Hand = sf::Cursor::Hand,
		SizeHorizontal = sf::Cursor::SizeHorizontal,
		SizeVertical = sf::Cursor::SizeVertical,
		SizeTopLeftBottomRight = sf::Cursor::SizeTopLeftBottomRight,
		SizeBottomLeftTopRight = sf::Cursor::SizeBottomLeftTopRight,
		SizeAll = sf::Cursor::SizeAll,
		Cross = sf::Cursor::Cross,
		Help = sf::Cursor::Help,
		NotAllowed = sf::Cursor::NotAllowed,
		UserDefined
	};
}