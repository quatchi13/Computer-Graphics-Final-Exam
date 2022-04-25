#include "Gameplay/Components/RotatingBehaviour.h"

#include "Gameplay/GameObject.h"
#include "Utils/ImGuiHelper.h"
#include "Utils/JsonGlmHelpers.h"





void RotatingBehaviour::Update(float deltaTime) {
	GetGameObject()->SetRotation(GetGameObject()->GetRotationEuler() + RotationSpeed * deltaTime);

	GetGameObject()->SetPostion(GetGameObject()->GetPosition() + MoveSpeed * deltaTime);

	if (GetGameObject()->GetPosition().z < 1.00)
	{
		GetGameObject()->SetPostion(glm::vec3(0,-2,4));
		count++;
	}

	if (count > 9)
	{
		postProcess->GetEffect<Nightvision>()->Enabled = true;
	}
}

void RotatingBehaviour::OnTriggerVolumeEntered(const std::shared_ptr<Gameplay::Physics::RigidBody>& body)
{

	if (body->GetGameObject()->Name == "Player")
	{
		postProcess->GetEffect<Pixelation>()->Enabled = true;
		state = true;
	}
		
}

void RotatingBehaviour::RenderImGui() {
	LABEL_LEFT(ImGui::DragFloat3, "Speed", &RotationSpeed.x);
}



nlohmann::json RotatingBehaviour::ToJson() const {
	return {
		{ "speed", RotationSpeed }
	};
}

RotatingBehaviour::Sptr RotatingBehaviour::FromJson(const nlohmann::json& data) {
	RotatingBehaviour::Sptr result = std::make_shared<RotatingBehaviour>();
	result->RotationSpeed = JsonGet(data, "speed", result->RotationSpeed);
	return result;
}
