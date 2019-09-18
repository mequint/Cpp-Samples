#pragma once

#include "Message.h"

namespace qe {
	class Observer
	{
		public:
			virtual ~Observer() {}
			virtual void Notify(const Message& message) = 0;
	};
}