#pragma once
#include "Application/Layers/PostProcessingLayer.h"
#include "Graphics/Textures/Texture3D.h"
#include "Graphics/ShaderProgram.h"



class Filmgrain : public PostProcessingLayer::Effect {
public:
	MAKE_PTRS(Filmgrain);

	Filmgrain();
	virtual ~Filmgrain();

	virtual void Apply(const Framebuffer::Sptr& gBuffer) override;

	virtual void RenderImGui() override;

	Filmgrain::Sptr FromJson(const nlohmann::json& data);

	virtual nlohmann::json ToJson() const override;

protected:
	ShaderProgram::Sptr _shader;
	float _strength = 0.3f;
	float _scale = 10000.0f;
	float _amount = 30.0f;

};