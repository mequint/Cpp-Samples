#pragma once

namespace qe {
	using MessageType = unsigned int;

	// Message data for the union
	struct TwoFloats { float x, y; };

	struct Message {
		Message(const MessageType& type) : m_type(type) {}

		MessageType m_type;
		int m_sender;
		int m_receiver;

		// TODO: Replace union with std::variant (later)
		union {
			TwoFloats m_2f;
			bool m_bool;
			int m_int;
		};
	};
}