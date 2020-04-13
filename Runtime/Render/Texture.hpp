#pragma once

#include <glad/glad.h>
#include <string>

namespace RE
{
	// ��ͼ�������ͷž���FileSystem����
	class Texture
	{
	public:
		Texture() = default;
		~Texture() = default;

		// 1D
		void Create(unsigned int, unsigned int, unsigned int, unsigned int, void*);

		// 2D
		void Create(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, void*);

		// 3D
		void Create(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, void*);

		// �������óߴ磬���������ڴ�
		void ReSize(unsigned int, unsigned int height = 0, unsigned int depth = 0);


		void Bind(int unit = -1);
		void UnBind();


		void SetWrapMode(unsigned int,bool bind = false);
		void SetFilterMin(unsigned int,bool bind = false);
		void SetFilterMax(unsigned int,bool bind = false);

	public: // getter
		inline unsigned int GetID(){ return m_ID; }

	private:
		unsigned int m_ID;

		unsigned int m_Target = GL_TEXTURE_2D;		 
		unsigned int m_InternalFormat = GL_RGBA;				
		unsigned int m_Format = GL_RGBA;				
		unsigned int m_Type = GL_UNSIGNED_BYTE;

		// ���˸�ʽ
		unsigned int m_FilterMin = GL_LINEAR_MIPMAP_LINEAR; 
		unsigned int m_FilterMax = GL_LINEAR;        

		// S T R Wrapping
		unsigned int m_WrapS = GL_REPEAT;       
		unsigned int m_WrapT = GL_REPEAT;   
		unsigned int m_WrapR = GL_REPEAT; 

		bool m_Mipmapping = true;

		unsigned int m_Width  = 0;
		unsigned int m_Height = 0;
		unsigned int m_Depth  = 0;
	private:
		friend class Material;
		friend class LoadTexture;
		friend class Asset;
		friend class RenderTarget;
	};
}



