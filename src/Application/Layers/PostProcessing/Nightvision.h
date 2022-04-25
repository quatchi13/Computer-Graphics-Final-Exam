#pragma once
#include "Application/Layers/PostProcessingLayer.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/Textures/Texture3D.h"

class Nightvision : public PostProcessingLayer::Effect {
public:
	MAKE_PTRS(Nightvision);

	Nightvision();
	virtual ~Nightvision();

	virtual void Apply(const Framebuffer::Sptr& gBuffer) override;
	virtual void RenderImGui() override;


	Nightvision::Sptr FromJson(const nlohmann::json& data);

	virtual nlohmann::json ToJson() const override;


protected:
	ShaderProgram::Sptr _shader;

};