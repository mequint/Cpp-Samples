#include "qe/Animation/AnimationControl.h"

qe::AnimationControl::AnimationControl() : 
	m_currentFrame(0), 
	m_startFrame(0), 
	m_endFrame(0), 
	m_frameRow(0),
	m_frameTime(0.0f), 
	m_elapsedTime(0.0f), 
	m_frameAction(eAnimationAction::Linear),
	m_isRunning(false), 
	m_isProgressing(true),
	m_hasChanged(false) {}

qe::AnimationControl::~AnimationControl() = default;

void qe::AnimationControl::update(float dt) {
	if (!m_isRunning) return;

	m_elapsedTime += dt;
	if (m_elapsedTime < m_frameTime) return;

	frameStep();

	m_elapsedTime = 0.0f;
}

void qe::AnimationControl::frameStep() {
	int frame = m_currentFrame + (m_isProgressing ? 1 : -1);
	if ((frame >= m_startFrame && frame <= m_endFrame) || (frame >= m_endFrame <= m_startFrame)) {
		m_currentFrame = frame;
	}
	else {
		switch (m_frameAction) {
			case eAnimationAction::None: {
				// Why are we even animating?
				return;
			}

			case eAnimationAction::Linear: {
				m_currentFrame = m_endFrame;
				pause();
				break;
			}

			case eAnimationAction::Loop: {
				m_currentFrame = m_startFrame;
				break;
			}

			case eAnimationAction::Reflect: {
				m_isProgressing = !m_isProgressing;
				break;
			}
		}
	}
}

void qe::AnimationControl::start() { m_isRunning = true; }
void qe::AnimationControl::pause() { m_isRunning = false; }

void qe::AnimationControl::stop() {
	m_isRunning = false;

	m_currentFrame = m_startFrame;
	m_elapsedTime = 0.0f;
}

std::string qe::AnimationControl::getName() const { return m_name; }
void qe::AnimationControl::setName(const std::string& name) { m_name = name; }

void qe::AnimationControl::setCurrentFrame(int frame) { m_currentFrame = frame; }
int qe::AnimationControl::getCurrentFrame() const { return m_currentFrame; }

void qe::AnimationControl::setStartFrame(int frame) { m_startFrame = frame; }
int qe::AnimationControl::getStartFrame() const { return m_startFrame; }

void qe::AnimationControl::setEndFrame(int frame) { m_endFrame = frame; }
int qe::AnimationControl::getEndFrame() const { return m_endFrame; }

void qe::AnimationControl::setFrameRow(int row) { m_frameRow = row; }
int qe::AnimationControl::getFrameRow() const { return m_frameRow; }

void qe::AnimationControl::setFrameTime(float time) { m_frameTime = time; }
float qe::AnimationControl::getFrameTime() const { return m_frameTime; }

void qe::AnimationControl::setElapsedTime(float time) { m_elapsedTime = time; }
float qe::AnimationControl::getElapsedTime() const { return m_elapsedTime; }

void qe::AnimationControl::setFrameAction(eAnimationAction action) { m_frameAction = action; }
qe::eAnimationAction qe::AnimationControl::getFrameAction() const { return m_frameAction; }

void qe::AnimationControl::setIsRunning(bool isRunning) { m_isRunning = isRunning; }
bool qe::AnimationControl::getIsRunning() const { return m_isRunning; }

void qe::AnimationControl::setHasChanged(bool hasChanged) { m_hasChanged = hasChanged; }

bool qe::AnimationControl::getHasChanged() {
	bool hasChanged = m_hasChanged;
	m_hasChanged = false;

	return hasChanged;
}