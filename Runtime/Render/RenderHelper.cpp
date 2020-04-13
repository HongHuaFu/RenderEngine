#include "RenderHelper.hpp"
#include "../Render/CommandBuffer.hpp"
#include "../Scene/SceneNode.hpp"

#include <stack>

namespace RE
{
	void RenderHelper::RenderToCubeMap(SceneNode* scene,TextureCube* target,glm::vec3 position,unsigned int mipLevel)
	{
		// 构建一个CommandBuffer
		CommandBuffer commandBuffer(m_Renderer);

		// 先压入父节点的渲染命令
		commandBuffer.Push(scene->Mesh, scene->Material, scene->GetTransform());
		
		// 先序遍历子节点 使用辅助栈压入
		std::stack<SceneNode*> childStack;
		for (unsigned int i = 0; i < scene->GetChildCount(); ++i)
			childStack.push(scene->GetChildByIndex(i));

		while (!childStack.empty())
		{
			SceneNode *child = childStack.top();
			childStack.pop();

			// 子节点网格压入渲染队列
			commandBuffer.Push(child->Mesh, child->Material, child->GetTransform());

			// 一次先序遍历
			for (unsigned int i = 0; i < child->GetChildCount(); ++i)
				childStack.push(child->GetChildByIndex(i));
		}
		commandBuffer.Sort();
		std::vector<RenderCommand> renderCommands = commandBuffer.GetCustomRenderCommands(nullptr);

		renderToCubemap(renderCommands, target, position, mipLevel);
	}
}
