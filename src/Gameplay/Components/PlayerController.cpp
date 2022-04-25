#include "PlayerController.h"

#include "Gameplay/GameObject.h"

#include "Utils/JsonGlmHelpers.h"
#include "Utils/ImGuiHelper.h"
#include "Gameplay/InputEngine.h"
#include "Gameplay/Components/ComponentManager.h"
#include "Gameplay/GameObject.h"
#include "GLM/gtc/quaternion.hpp"


PlayerController::PlayerController() :
	IComponent()
{ }
PlayerController::~PlayerController() = default;

void PlayerController::Awake() {
	_body = GetComponent<Gameplay::Physics::RigidBody>();
	_jumpForce = glm::vec3(0.0f, 0.0f, 9.8f);
	_moveSpeed = 15.0f;
}

void PlayerController::RenderImGui() {

}

nlohmann::json PlayerController::ToJson() const {
	return {

	};
}

PlayerController::Sptr PlayerController::FromJson(const nlohmann::json & blob) {
	PlayerController::Sptr result = std::make_shared<PlayerController>();
	return result;
}


void PlayerController::SetJump(bool state)
{
	_canJump = state;
}


void PlayerController::Update(float deltaTime) {

	_body->ApplyForce(gravity);
	GetGameObject()->SetRotation(glm::vec3(0.0f,0.0f,0.0f));
	if (GetGameObject()->GetPosition().x != 0.0f)
	{
		GetGameObject()->SetPostion(glm::vec3(0, GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z));
	}
	glm::vec3 currentVelocity = _body->GetLinearVelocity();


	
	if (InputEngine::GetKeyState(GLFW_KEY_SPACE) == ButtonState::Pressed && _canJump) {
		_body->ApplyImpulse(_jumpForce);
		Gameplay::IComponent::Sptr ptr = Panel.lock();
		if (ptr != nullptr) {
			ptr->IsEnabled = !ptr->IsEnabled;
		}
		_canJump = false;
	}
	if (InputEngine::GetKeyState(GLFW_KEY_D) == ButtonState::Down) {
		if (currentVelocity.y >= -_moveSpeed)
		{
			_body->ApplyForce(glm::vec3(0.0f, -30.0f, 0.0f));
		}
		Gameplay::IComponent::Sptr ptr = Panel.lock();
		if (ptr != nullptr) {
			ptr->IsEnabled = !ptr->IsEnabled;
		}
	}
	if (InputEngine::GetKeyState(GLFW_KEY_A) == ButtonState::Down) {
		if (currentVelocity.y <= _moveSpeed)
		{
			_body->ApplyForce(glm::vec3(0.0f, 30.0f, 0.0f));
		}
		Gameplay::IComponent::Sptr ptr = Panel.lock();
		if (ptr != nullptr) {
			ptr->IsEnabled = !ptr->IsEnabled;
		}
	}
	//character reset (just in case ;D)
	if (InputEngine::GetKeyState(GLFW_KEY_R) == ButtonState::Down) {
		GetGameObject()->SetPostion(glm::vec3(0, 4.5, 2.5));

		postProcess->GetEffect<Pixelation>()->Enabled = false;
		postProcess->GetEffect<Nightvision>()->Enabled = false;
	}
}