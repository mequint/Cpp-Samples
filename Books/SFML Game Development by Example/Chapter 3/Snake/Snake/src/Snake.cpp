#include "Snake.h"

Snake::Snake(int blockSize, Textbox* log) {
	m_log = log;
	m_size = blockSize;

	m_bodyRect.setSize(sf::Vector2f(static_cast<float>(m_size - 1), static_cast<float>(m_size - 1)));
	Reset();
}

Snake::~Snake() = default;

void Snake::SetDirection(Direction dir) { m_dir = dir; }
Direction Snake::GetDirection() { return m_dir; }

int Snake::GetSpeed() { return m_speed; }

sf::Vector2i Snake::GetPosition() {
	return !m_snakeBody.empty() ? m_snakeBody.front().position : sf::Vector2i(1, 1);
}

int Snake::GetLives() { return m_lives; }
int Snake::GetScore() { return m_score; }

void Snake::IncreaseScore() {
	m_score += 10;
	m_log->Add("You ate an apple. Score: " + std::to_string(static_cast<long long>(m_score)));
}

bool Snake::HasLost() { return m_lost; }
void Snake::Lose() { m_lost = true; }
void Snake::ToggleLost() { m_lost = !m_lost; }

Direction Snake::GetPhysicalDirection() {
	if (m_snakeBody.size() <= 1) {
		return Direction::None;
	}

	SnakeSegment& head = m_snakeBody[0];
	SnakeSegment& neck = m_snakeBody[1];

	if (head.position.x == neck.position.x) {
		return head.position.y > neck.position.y ? Direction::Down : Direction::Up;
	}
	else if (head.position.y == neck.position.y) {
		return head.position.x > neck.position.x ? Direction::Right : Direction::Left;
	}

	return Direction::None;
}

void Snake::Extend() {
	if (m_snakeBody.empty()) return;

	SnakeSegment& tailHead = m_snakeBody[m_snakeBody.size() - 1];

	if (m_snakeBody.size() > 1) {
		SnakeSegment& tailBone = m_snakeBody[m_snakeBody.size() - 2];

		if (tailHead.position.x == tailBone.position.x) {
			if (tailHead.position.y > tailBone.position.y) {
				m_snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y + 1));
			}
			else {
				m_snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y - 1));
			}
		}
		else if (tailHead.position.y == tailBone.position.y) {
			if (tailHead.position.x > tailBone.position.x) {
				m_snakeBody.push_back(SnakeSegment(tailHead.position.x + 1, tailHead.position.y));
			}
			else {
				m_snakeBody.push_back(SnakeSegment(tailHead.position.x - 1, tailHead.position.y));
			}
		}
	}
	else {
		if (m_dir == Direction::Up) {
			m_snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y + 1));
		}
		else if (m_dir == Direction::Down) {
			m_snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y - 1));
		}
		else if (m_dir == Direction::Left) {
			m_snakeBody.push_back(SnakeSegment(tailHead.position.x + 1, tailHead.position.y));
		}
		else if (m_dir == Direction::Right) {
			m_snakeBody.push_back(SnakeSegment(tailHead.position.x - 1, tailHead.position.y));
		}
	}
}

void Snake::Reset() {
	m_snakeBody.clear();
	m_snakeBody.push_back(SnakeSegment(5, 7));
	m_snakeBody.push_back(SnakeSegment(5, 6));
	m_snakeBody.push_back(SnakeSegment(5, 5));

	SetDirection(Direction::None);
	m_speed = 15;
	m_lives = 3;
	m_score = 0;

	m_lost = false;
}

void Snake::Move() {
	for (int i = m_snakeBody.size() - 1; i > 0; --i) {
		m_snakeBody[i].position = m_snakeBody[i - 1].position;
	}

	if (m_dir == Direction::Left) {
		--m_snakeBody[0].position.x;
	}
	else if (m_dir == Direction::Right) {
		++m_snakeBody[0].position.x;
	}
	else if (m_dir == Direction::Up) {
		--m_snakeBody[0].position.y;
	}
	else if (m_dir == Direction::Down) {
		++m_snakeBody[0].position.y;
	}
}

void Snake::Tick() {
	if (m_snakeBody.empty()) return;
	if (m_dir == Direction::None) return;

	Move();
	CheckCollision();
}

void Snake::Cut(int segments) {
	for (int i = 0; i < segments; ++i) {
		m_snakeBody.pop_back();
	}

	--m_lives;
	if (!m_lives) { Lose(); return; }

	m_log->Add("You have lost a life! Lives left: " + std::to_string(static_cast<long long>(m_lives)));
}


void Snake::Render(sf::RenderWindow & window) {
	if (m_snakeBody.empty()) return;

	auto head = m_snakeBody.begin();
	m_bodyRect.setFillColor(sf::Color::Yellow);
	m_bodyRect.setPosition(static_cast<float>(head->position.x * m_size), static_cast<float>(head->position.y * m_size));

	window.draw(m_bodyRect);

	m_bodyRect.setFillColor(sf::Color::Green);
	for (auto iter = m_snakeBody.begin() + 1; iter != m_snakeBody.end(); ++iter) {
		m_bodyRect.setPosition(static_cast<float>(iter->position.x * m_size), static_cast<float>(iter->position.y * m_size));
		window.draw(m_bodyRect);
	}
}

void Snake::CheckCollision() {
	if (m_snakeBody.size() < 5) return;

	SnakeSegment& head = m_snakeBody.front();

	for (auto iter = m_snakeBody.begin() + 1; iter != m_snakeBody.end(); ++iter) {
		if (iter->position == head.position) {
			int segments = m_snakeBody.end() - iter;

			Cut(segments);
			break;
		}
	}
}