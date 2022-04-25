#include "Pixelation.h"
#include "Utils/ResourceManager/ResourceManager.h"
#include "Utils/JsonGlmHelpers.h"
#include "Utils/ImGuiHelper.h"

Pixelation::Pixelation() :
	PostProcessingLayer::Effect(),
	_shader(nullptr)
{
	Name = "Pixelation";
	_format = RenderTargetType::ColorRgb8;

	_shader = ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string>{
		{ ShaderPartType::Vertex, "shaders/vertex_shaders/fullscreen_quad.glsl" },
		{ ShaderPartType::Fragment, "shaders/fragment_shaders/post_effects/pixelation.glsl" }
	});
}

Pixelation::~Pixelation() = default;

void Pixelation::Apply(const Framebuffer::Sptr & gBuffer)
{
	_shader->Bind();
	gBuffer->BindAttachment(RenderTargetAttachment::Depth, 1);
	gBuffer->BindAttachment(RenderTargetAttachment::Color1, 2); 
	_shader->SetUniform("u_Scale", _scale);
	_shader->SetUniform("u_Amount", _amount);
	
}

void Pixelation::RenderImGui()
{
	LABEL_LEFT(ImGui::SliderFloat, "Scale", &_scale, 1, 100);

	LABEL_LEFT(ImGui::SliderFloat, "Amount", &_amount, 1, 10000);
}

Pixelation::Sptr Pixelation::FromJson(const nlohmann::json & data)
{
	Pixelation::Sptr result = std::make_shared<Pixelation>();
	result->Enabled = JsonGet(data, "enabled", false);

	result->_scale = JsonGet(data, "scale", result->_scale);

	result->_amount = JsonGet(data, "amount", result->_amount);
	return result;
}

nlohmann::json Pixelation::ToJson() const
{
	return
	{
		{ "enabled", Enabled },
		{ "scale", _scale },
		{ "amount", _amount}
	};
}