#include "Filmgrain.h"
#include "Utils/ResourceManager/ResourceManager.h"
#include "Utils/ImGuiHelper.h"
#include "Utils/JsonGlmHelpers.h"


Filmgrain::Filmgrain() :
	PostProcessingLayer::Effect(),
	_shader(nullptr)
{
	Name = "Film Grain";
	_format = RenderTargetType::ColorRgb8;

	_shader = ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string>{
		{ ShaderPartType::Vertex, "shaders/vertex_shaders/fullscreen_quad.glsl" },
		{ ShaderPartType::Fragment, "shaders/fragment_shaders/post_effects/filmgrain.glsl" }
	});
}

Filmgrain::~Filmgrain() = default;

void Filmgrain::Apply(const Framebuffer::Sptr & gBuffer)
{
	_shader->Bind();
	gBuffer->BindAttachment(RenderTargetAttachment::Depth, 1);
	gBuffer->BindAttachment(RenderTargetAttachment::Color1, 2); 
	_shader->SetUniform("u_Strength", _strength);
	_shader->SetUniform("u_Scale", _scale);
	_shader->SetUniform("u_Amount", _amount);
}

void Filmgrain::RenderImGui()
{
	LABEL_LEFT(ImGui::SliderFloat, "Strength", &_strength, 0, 5);
	LABEL_LEFT(ImGui::SliderFloat, "Scale", &_scale, 1, 1000);
	LABEL_LEFT(ImGui::SliderFloat, "Amount", &_amount, 0, 50);
}

Filmgrain::Sptr Filmgrain::FromJson(const nlohmann::json & data)
{
	Filmgrain::Sptr result = std::make_shared<Filmgrain>();
	result->Enabled = JsonGet(data, "enabled", false);

	result->_strength = JsonGet(data, "strength", result->_strength);
	result->_scale = JsonGet(data, "scale", result->_scale);

	result->_amount = JsonGet(data, "amount", result->_amount);
	return result;
}

nlohmann::json Filmgrain::ToJson() const
{
	return
	{
		{ "enabled", Enabled },
		{ "strength", _strength },
		{ "scale", _scale },
		{ "amount", _amount }
	};
}