#pragma once
#include "IComponent.h"

#include "Application/Layers/PostProcessingLayer.h"
#include "Application/Application.h"
#include "Application/Layers/PostProcessing/Pixelation.h"

/// <summary>
/// Showcases a very simple behaviour that rotates the parent gameobject at a fixed rate over time
/// </summary>
class RotatingBehaviour : public Gameplay::IComponent {
public:
	typedef std::shared_ptr<RotatingBehaviour> Sptr;

	RotatingBehaviour() = default;
	glm::vec3 RotationSpeed;
	glm::vec3 MoveSpeed;


	PostProcessingLayer::Sptr& postProcess = Application::Get().GetLayer<PostProcessingLayer>();
	bool state = false;

	virtual void Update(float deltaTime) override;
	virtual void OnTriggerVolumeEntered(const std::shared_ptr<Gameplay::Physics::RigidBody>& body) override;
	virtual void RenderImGui() override;

	virtual nlohmann::json ToJson() const override;
	static RotatingBehaviour::Sptr FromJson(const nlohmann::json& data);

	MAKE_TYPENAME(RotatingBehaviour);
};

