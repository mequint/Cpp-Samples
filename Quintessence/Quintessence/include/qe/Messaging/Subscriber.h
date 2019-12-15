#pragma once

#include "Message.h"

namespace qe {
	class Subscriber {
	public:
		virtual ~Subscriber() {}

		virtual void notify(const Message& message) = 0;
	};
}