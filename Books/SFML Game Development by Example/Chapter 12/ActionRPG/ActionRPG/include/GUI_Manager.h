#pragma once

#include "GUI_Event.h"
#include "GUI_Interface.h"
#include "SharedContext.h"

//struct SharedContext;

class GUI_Manager {
	friend class GUI_Interface;
public:
	SharedContext* GetContext() { return m_context; }

	void AddEvent(GUI_Event& event) {}

private:
	GUI_Element* CreateElement(const GUI_ElementType& id, GUI_Interface* owner) { return nullptr; }
	SharedContext* m_context;
};