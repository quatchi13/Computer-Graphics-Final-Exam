#include "DebugWindow.h"
#include "Application/Application.h"
#include "Application/ApplicationLayer.h"
#include "Application/Layers/RenderLayer.h"

DebugWindow::DebugWindow() :
	IEditorWindow()
{
	Name = "Debug";
	SplitDirection = ImGuiDir_::ImGuiDir_None;
	SplitDepth = 0.5f;
	Requirements = EditorWindowRequirements::Menubar;
}

DebugWindow::~DebugWindow() = default;

void DebugWindow::RenderMenuBar() 
{
	Application& app = Application::Get();
	RenderLayer::Sptr renderLayer = app.GetLayer<RenderLayer>(); 

	BulletDebugMode physicsDrawMode = app.CurrentScene()->GetPhysicsDebugDrawMode();
	if (BulletDebugDraw::DrawModeGui("Physics Debug Mode:", physicsDrawMode)) { 
		app.CurrentScene()->SetPhysicsDebugDrawMode(physicsDrawMode);
	}

	ImGui::Separator();

	RenderFlags flags = renderLayer->GetRenderFlags();
	bool changed = false;

	bool temp = *(flags & RenderFlags::NoAmbient);
	if (ImGui::Checkbox("Disable Ambient", &temp)) {
		changed = true;
		flags = (flags & ~*RenderFlags::NoAmbient) | (temp ? RenderFlags::NoAmbient : RenderFlags::None);
	}

	temp = *(flags & RenderFlags::NoDiffuse);
	if (ImGui::Checkbox("Enable Diffuse", &temp)) {
		changed = true;
		flags = (flags & ~*RenderFlags::NoDiffuse) | (temp ? RenderFlags::NoDiffuse : RenderFlags::None);
	}

	temp = *(flags & RenderFlags::NoSpecular);
	if (ImGui::Checkbox("Enable Specular", &temp)) {
		changed = true;
		flags = (flags & ~*RenderFlags::NoSpecular) | (temp ? RenderFlags::NoSpecular : RenderFlags::None);
	}

	if (changed) {
		renderLayer->SetRenderFlags(flags);
	}
}
