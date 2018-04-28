#include "IntroState.h"

#include <glm/gtc/matrix_transform.hpp>

#include "StateManager.h"
#include "Text.h"

IntroState::IntroState(StateManager * stateManager) : 
	State(stateManager)
{
}

IntroState::~IntroState()
{
}

void IntroState::Initialize()
{
	auto context = m_pStateManager->GetContext();

	// TODO: Window should return a projection matrix of some sort
	glm::mat4 ortho = glm::ortho(0.0f, static_cast<float>(context->Window->GetWidth()), static_cast<float>(context->Window->GetHeight()), 0.0f, -1.0f, 1.0f);

	Shader textShader = context->ShaderManager->LoadShader("text", "Assets/shaders/text.vert", "Assets/shaders/text.frag");
	textShader.Use();
	textShader.Set("projection", ortho);	// Get from the window projector

	Font font = context->FontManager->Load("Assets/fonts/arial.ttf", "arial24", 24);

	m_text = new Text(textShader, font, "Intro State");
	m_text->SetPosition(50.0f, 50.0f);
}

void IntroState::Cleanup()
{
	delete m_text;
}

void IntroState::Activate() {}
void IntroState::Deactivate() {}

// Nothing to update...for now
void IntroState::Update() {}

void IntroState::Draw()
{
	m_text->Draw();
}
