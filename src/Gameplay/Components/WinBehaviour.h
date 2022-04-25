#pragma once
#include "IComponent.h"
#include "Gameplay/Physics/TriggerVolume.h"
#include "Gameplay/Components/RenderComponent.h"
#include "Gameplay/Physics/TriggerVolume.h"


#include "Application/Layers/PostProcessingLayer.h"
#include "Application/Application.h"
#include "Application/Layers/PostProcessing/Nightvision.h"

/// <summary>
/// Provides an example behaviour that uses some of the trigger interface to change the material
/// of the game object the component is attached to when entering or leaving a trigger
/// </summary>
class WinBehaviour : public Gameplay::IComponent {

public:
	typedef std::shared_ptr<WinBehaviour> Sptr;
	WinBehaviour();
	virtual ~WinBehaviour();

	// Inherited from IComponent

	virtual void OnTriggerVolumeEntered(const std::shared_ptr<Gameplay::Physics::RigidBody>& body) override;
	virtual void OnTriggerVolumeLeaving(const std::shared_ptr<Gameplay::Physics::RigidBody>& body) override;
	virtual void RenderImGui() override;
	virtual nlohmann::json ToJson() const override;
	static WinBehaviour::Sptr FromJson(const nlohmann::json& blob);
	MAKE_TYPENAME(WinBehaviour);

	PostProcessingLayer::Sptr& postProcess = Application::Get().GetLayer<PostProcessingLayer>();

protected:
	bool _playerInTrigger;
};