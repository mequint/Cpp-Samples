#pragma once

#include <SFML/System.hpp>

namespace qe {
	enum class eAnimationAction { None = 0, Linear, Loop, Reflect };

	class AnimationControl {
	public:
		AnimationControl();
		virtual ~AnimationControl();

		void update(float dt);

		void frameStep();

		void start();
		void pause();
		void stop();

		// *** Properties *** //
		std::string getName() const;
		void setName(const std::string& name);

		void setCurrentFrame(int frame);
		int getCurrentFrame() const;

		void setStartFrame(int frame);
		int getStartFrame() const;

		void setEndFrame(int frame);
		int getEndFrame() const;

		void setFrameRow(int row);
		int getFrameRow() const;

		void setFrameTime(float time);
		float getFrameTime() const;

		void setElapsedTime(float time);
		float getElapsedTime() const;

		void setFrameAction(eAnimationAction action);
		eAnimationAction getFrameAction() const;

		void setIsRunning(bool isRunning);
		bool getIsRunning() const;

		void setHasChanged(bool hasChanged);
		bool getHasChanged();

	protected:
		std::string m_name;

		int m_currentFrame;
		int m_startFrame, m_endFrame;
		int m_frameRow;

		float m_frameTime;
		float m_elapsedTime;

		eAnimationAction m_frameAction;
		bool m_isRunning;
		bool m_isProgressing;
		bool m_hasChanged;
	};
}