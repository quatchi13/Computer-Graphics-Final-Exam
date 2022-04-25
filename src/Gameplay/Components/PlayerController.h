#pragma once
#include "IComponent.h"
#include "Gameplay/Physics/RigidBody.h"
#include "Gameplay/Physics/Colliders/BoxCollider.h"
#include "Gameplay/Physics/Colliders/PlaneCollider.h"
#include "Gameplay/Physics/Colliders/SphereCollider.h"
#include "Gameplay/Physics/Colliders/ConvexMeshCollider.h"
#include "Gameplay/Physics/Colliders/CylinderCollider.h"
#include "Gameplay/Physics/TriggerVolume.h"
#include "Graphics/DebugDraw.h"

#include "Application/Layers/PostProcessingLayer.h"
#include "Application/Application.h"
#include "Application/Layers/PostProcessing/Nightvision.h"
#include "Application/Layers/PostProcessing/Pixelation.h"

/// <summary>
/// A player controller which allows for key inputs to move an object in the scene
/// Hopefully I can get this to interact nicely with collisions
/// </summary>
class PlayerController : public Gameplay::IComponent {
public:
	typedef std::shared_ptr<PlayerController> Sptr;

	const glm::vec3& gravity = glm::vec3(0.0f, 0.0f, -9.8f);

	std::weak_ptr<Gameplay::IComponent> Panel;

	PlayerController();
	virtual ~PlayerController();

	virtual void Awake() override;
	virtual void Update(float deltaTime) override;

public:
	virtual void RenderImGui() override;
	MAKE_TYPENAME(PlayerController);
	virtual nlohmann::json ToJson() const override;
	static PlayerController::Sptr FromJson(const nlohmann::json& blob);
	
	void SetJump(bool state);

	PostProcessingLayer::Sptr& postProcess = Application::Get().GetLayer<PostProcessingLayer>();
protected:
	glm::vec3 _jumpForce;
	float _moveSpeed;

	bool _isJump = false;
	bool _isLeft = false;
	bool _isRight = false;
	bool _canJump = false;
	Gameplay::Physics::RigidBody::Sptr _body;
};
