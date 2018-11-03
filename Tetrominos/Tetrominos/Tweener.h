#pragma once

template <typename T>
class Tweener
{
	public:
		Tweener() {}

		Tweener(T start, T end, int frames, float frameTime)
		{
			m_isPlaying = false;

			m_currentFrame = 0;
			m_frames = frames;

			m_start = start;
			m_end = end;

			m_elapsedTime = 0.0;
			m_frameTime = frameTime;
		}

		T CurrentStep()
		{
			if (m_isComplete) return m_end;

			if (m_start > m_end)
			{
				return m_start - ((m_start - m_end) * m_currentFrame / m_frames);
			}

			return m_start + ((m_end - m_start) * m_currentFrame / m_frames);
		}

		void Update(float dt)
		{
			if (!m_isPlaying) return;

			m_elapsedTime += dt;
			if (m_elapsedTime > m_frameTime)
			{
				m_currentFrame++;
				m_elapsedTime = 0.0f;
			}

			if (m_currentFrame == m_frames)
			{
				m_isPlaying = false;
				m_isComplete = true;
			}
		}

		void Play() { m_isPlaying = true; }
		bool IsPlaying() const { return m_isPlaying; }
		bool IsComplete() const { return m_isComplete; }

		void Reset()
		{
			m_isPlaying = false;
			m_isComplete = false;
			m_currentFrame = 0;
		}

	private:
		int m_frames;
		int m_currentFrame;

		T m_start;
		T m_end;

		float m_elapsedTime;
		float m_frameTime;

		bool m_isPlaying;
		bool m_isComplete;
};

using FloatTweener = Tweener<float>;
using IntTweener = Tweener<int>;