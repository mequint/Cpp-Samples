#pragma once

#include "qe/ECS/ECS_Types.h"

namespace qe {
	class Comp_Base
	{
		public:
			Comp_Base(const Component& type) : m_type(type) {}
			virtual ~Comp_Base() {}

			Component GetType() { return m_type; }

		protected:
			Component m_type;
	};
}