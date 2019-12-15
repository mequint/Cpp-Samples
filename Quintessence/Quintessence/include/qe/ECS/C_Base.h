#pragma once

namespace qe {
	using ComponentType = unsigned int;

	class C_Base {
	public:
		C_Base(ComponentType type) : m_type(type) {}
		virtual ~C_Base() {}

		int getType() { return m_type; }

	protected:
		ComponentType m_type;
	};
}