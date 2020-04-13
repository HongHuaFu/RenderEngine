#include "RenderHelper.hpp"
#include "../Render/CommandBuffer.hpp"
#include "../Scene/SceneNode.hpp"

#include <stack>

namespace RE
{
	void RenderHelper::RenderToCubeMap(SceneNode* scene,TextureCube* target,glm::vec3 position,unsigned int mipLevel)
	{
		// ����һ��CommandBuffer
		CommandBuffer commandBuffer(m_Renderer);

		// ��ѹ�븸�ڵ����Ⱦ����
		commandBuffer.Push(scene->Mesh, scene->Material, scene->GetTransform());
		
		// ��������ӽڵ� ʹ�ø���ջѹ��
		std::stack<SceneNode*> childStack;
		for (unsigned int i = 0; i < scene->GetChildCount(); ++i)
			childStack.push(scene->GetChildByIndex(i));

		while (!childStack.empty())
		{
			SceneNode *child = childStack.top();
			childStack.pop();

			// �ӽڵ�����ѹ����Ⱦ����
			commandBuffer.Push(child->Mesh, child->Material, child->GetTransform());

			// һ���������
			for (unsigned int i = 0; i < child->GetChildCount(); ++i)
				childStack.push(child->GetChildByIndex(i));
		}
		commandBuffer.Sort();
		std::vector<RenderCommand> renderCommands = commandBuffer.GetCustomRenderCommands(nullptr);

		renderToCubemap(renderCommands, target, position, mipLevel);
	}
}
