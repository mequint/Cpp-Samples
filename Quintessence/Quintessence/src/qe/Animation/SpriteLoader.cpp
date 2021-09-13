#pragma once

#include <fstream>
#include <mutex>
#include <nlohmann/json.hpp>
#include "qe/Animation/SpriteLoader.h"

qe::SpriteLoader::SpriteLoader(qe::TextureManager* textureManager) : 
	m_textureManager(textureManager)
{
}

std::unique_ptr<qe::SpriteAnimation> qe::SpriteLoader::loadFromJsonFile(const std::string& filepath) {
	std::mutex lock;
	lock.lock();
	std::ifstream jsonFile(filepath);

	nlohmann::json json;
	jsonFile >> json;

	jsonFile.close();
	lock.unlock();

	auto sprite = std::make_unique<SpriteAnimation>(m_textureManager);

	// Texture Name
	if (json.contains("textureName") && json["textureName"].is_string()) {
		auto textureName = json["textureName"].get<std::string>();
		sprite->setTexture(textureName);
	}

	// Frame Size
	if (json.contains("frameSize") && json["frameSize"].is_object()) {
		auto frameSizeJson = json["frameSize"].get<nlohmann::json>();

		unsigned int width = 0;
		unsigned int height = 0;

		if (frameSizeJson.contains("width")) {
			width = frameSizeJson["width"].get<unsigned int>();
		}

		if (frameSizeJson.contains("height")) {
			height = frameSizeJson["height"].get<unsigned int>();
		}

		sprite->setFrameSize(width, height);
	}

	// Position
	if (json.contains("position") && json["position"].is_object()) {
		auto positionJson = json["position"].get<nlohmann::json>();

		float x = 0.0f;
		float y = 0.f;

		if (positionJson.contains("x")) {
			x = positionJson["x"].get<float>();
		}

		if (positionJson.contains("y")) {
			y = positionJson["y"].get<float>();
		}

		sprite->setPosition(x, y);
	}

	// Animations
	if (json.contains("animations") && json["animations"].is_array()) {
		auto jsonAnimationArray = json["animations"];

		for (auto const& jsonAnimation : jsonAnimationArray) {
			auto animation = std::make_unique<qe::AnimationControl>();
			auto hasRequiredFields = true;

			if (jsonAnimation.contains("name") && jsonAnimation["name"].is_string()) {
				animation->setName(jsonAnimation["name"].get<std::string>());
			}
			else {
				hasRequiredFields = false;
			}

			if (jsonAnimation.contains("startFrame") && jsonAnimation["startFrame"].is_number_integer()) {
				animation->setStartFrame(jsonAnimation["startFrame"].get<int>());
			}

			if (jsonAnimation.contains("endFrame") && jsonAnimation["endFrame"].is_number_integer()) {
				animation->setEndFrame(jsonAnimation["endFrame"].get<int>());
			}

			if (jsonAnimation.contains("frameRow") && jsonAnimation["frameRow"].is_number_integer()) {
				animation->setFrameRow(jsonAnimation["frameRow"].get<int>());
			}

			if (jsonAnimation.contains("frameTime") && jsonAnimation["frameTime"].is_number_float()) {
				animation->setFrameTime(jsonAnimation["frameTime"].get<float>());
			}

			if (jsonAnimation.contains("frameAction") && jsonAnimation["frameAction"].is_number_integer()) {
				auto frameAction = jsonAnimation["frameAction"].get<int>();

				switch (frameAction) {
					case 1:
					case 2:
					case 3:
						animation->setFrameAction(qe::eAnimationAction(frameAction));
						break;

					default:
						animation->setFrameAction(qe::eAnimationAction::None);
				}
			}

			if (hasRequiredFields) {
				sprite->addAnimation(std::move(animation));
			}
		}
	}

	// Current animation
	if (json.contains("currentAnimation") && json["currentAnimation"].is_string()) {
		sprite->changeAnimation(json["currentAnimation"].get<std::string>(), true);
	}

	return sprite;
}