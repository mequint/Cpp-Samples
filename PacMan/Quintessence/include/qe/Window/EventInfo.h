#pragma once

struct EventInfo {
	EventInfo() { m_eventCode = 0; }
	EventInfo(int eventCode) { m_eventCode = eventCode; }

	int m_eventCode;
};