#pragma once

#pragma region Core
	#include "Core/Macro.hpp"
	#include "Core/Log.hpp"
	#include "Core/Window.hpp"
	#include "Core/Asset.hpp"
	#include "Core/Application.hpp"
#pragma endregion

#pragma region Event
	#include "Event/Event.hpp"
	#include "Event/Event_Window.hpp"
	#include "Event/Event_Key.hpp"
	#include "Event/Event_Mouse.hpp"
#pragma endregion

#pragma region Geometry
	#include "Geometry/Cube.hpp"
	#include "Geometry/Quad.hpp"
	#include "Geometry/Sphere.hpp"
#pragma endregion

#pragma region IO
	#include "IO/LoadShader.hpp"
	#include "IO/LoadTexture.hpp"
#pragma endregion

#pragma region Pipeline
	#include "Pipeline/PP_PBRDeffered.hpp"
	#include "Pipeline/PP_PBRIBLForward.hpp"
#pragma endregion

#pragma region Render
	#include "Render/CommandBuffer.hpp"
	#include "Render/GraphicsCache.hpp"
	#include "Render/Material.hpp"
	#include "Render/Mesh.hpp"
	#include "Render/Renderer.hpp"
	#include "Render/RenderTarget.hpp"
	#include "Render/Shader.hpp"
	#include "Render/Texture.hpp"
	#include "Render/TextureCube.hpp"
	#include "Render/Pipeline.hpp"
	#include "Render/RenderHelper.hpp"
#pragma endregion

#pragma region Scene
	#include "Scene/Scene.hpp"
	#include "Scene/SceneNode.hpp"
	#include "Scene/SkyBox.hpp"
	#include "Scene/Camera.hpp"
	#include "Scene/FlyCamera.hpp"
	#include "Scene/Light.hpp"
#pragma endregion
