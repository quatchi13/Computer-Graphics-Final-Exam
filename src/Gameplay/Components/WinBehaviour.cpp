#include "Gameplay/Components/WinBehaviour.h"
#include "Gameplay/Components/ComponentManager.h"
#include "Gameplay/GameObject.h"

WinBehaviour::WinBehaviour() :
	IComponent()
{ }
WinBehaviour::~WinBehaviour() = default;


void WinBehaviour::OnTriggerVolumeEntered(const std::shared_ptr<Gameplay::Physics::RigidBody>& body)
{
	LOG_INFO("Body has entered {} trigger volume: {}", GetGameObject()->Name, body->GetGameObject()->Name);
	_playerInTrigger = true;
	if (body->GetGameObject()->Name == "Player")
	{
		postProcess->GetEffect<Nightvision>()->Enabled = true;
	}
	
	
}

void WinBehaviour::OnTriggerVolumeLeaving(const std::shared_ptr<Gameplay::Physics::RigidBody>& body) {
	LOG_INFO("Body has left {} trigger volume: {}", GetGameObject()->Name, body->GetGameObject()->Name);
	_playerInTrigger = false;
	
}

void WinBehaviour::RenderImGui() { }

nlohmann::json WinBehaviour::ToJson() const {
	return { };
}

WinBehaviour::Sptr WinBehaviour::FromJson(const nlohmann::json& blob) {
	WinBehaviour::Sptr result = std::make_shared<WinBehaviour>();
	return result;
}
