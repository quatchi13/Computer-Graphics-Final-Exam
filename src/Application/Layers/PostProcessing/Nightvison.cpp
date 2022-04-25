#include "Nightvision.h"
#include "Utils/ResourceManager/ResourceManager.h"
#include "Utils/JsonGlmHelpers.h"
#include "Utils/ImGuiHelper.h"




Nightvision::Nightvision() :
	PostProcessingLayer::Effect(),
	_shader(nullptr)
{
	Name = "Night Vision";
	_format = RenderTargetType::ColorRgb8;

	_shader = ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string>{
		{ ShaderPartType::Vertex, "shaders/vertex_shaders/fullscreen_quad.glsl" },

		{ ShaderPartType::Fragment, "shaders/fragment_shaders/post_effects/Night_vision.glsl" }
	});
}

Nightvision::~Nightvision() = default;

void Nightvision::Apply(const Framebuffer::Sptr & gBuffer)
{
	_shader->Bind();
	gBuffer->BindAttachment(RenderTargetAttachment::Depth, 1);
	gBuffer->BindAttachment(RenderTargetAttachment::Color1, 3); 
}

void Nightvision::RenderImGui()
{
}

Nightvision::Sptr Nightvision::FromJson(const nlohmann::json & data)
{
	Nightvision::Sptr result = std::make_shared<Nightvision>();
	result->Enabled = JsonGet(data, "enabled", true);
	return result;
}

nlohmann::json Nightvision::ToJson() const
{
	return
	{
		{ "enabled", true },
	};
}