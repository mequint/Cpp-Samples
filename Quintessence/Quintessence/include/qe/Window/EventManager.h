#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "EventBinding.h"
#include "qe/State/StateObserver.h"

namespace qe {
	using Bindings = std::unordered_map<std::string, std::shared_ptr<EventBinding>>;
	using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

	using Callbacks = std::unordered_map<StateType, CallbackContainer>;

	class EventManager : public StateObserver {
	public:
		EventManager();
		~EventManager();

		bool addBinding(const std::string& name, int eventType, int code);
		bool addBinding(std::shared_ptr<EventBinding> binding);
		bool removeBinding(const std::string& name);

		void setFocus(bool focus);

		template <class T>
		bool addCallback(const StateType& state, const std::string& name,
			void(T::*function)(EventDetails*), T* instance) {

			auto iter = m_callbacks.emplace(state, CallbackContainer()).first;
			auto temp = std::bind(function, instance, std::placeholders::_1);

			return iter->second.emplace(name, temp).second;
		}

		template <class T>
		bool addCallback(const std::string& name, void(T::*function)(EventDetails*), T* instance) {
			return addCallback<T>(m_currentState, name, function, instance);
		}

		bool removeCallback(const StateType& state, const std::string& name);

		void handleEvent(sf::Event& event);

		void update();

		sf::Vector2i getMousePosition(sf::Window* window = nullptr) const;

		// Inherited via StateObserver
		void changeState(const StateType & state) override;
		void removeState(const StateType & state) override;

	protected:
		Bindings m_bindings;
		Callbacks m_callbacks;

		bool m_hasFocus;
	};
}