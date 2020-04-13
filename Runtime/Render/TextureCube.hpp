#pragma once

#include <glad/glad.h>

namespace RE
{
	class TextureCube
	{
	private:
		unsigned int m_ID;
		unsigned int m_InternalFormat = GL_RGBA;           
		unsigned int m_Format = GL_RGBA;           
		unsigned int m_Type = GL_UNSIGNED_BYTE;
		unsigned int m_FilterMin = GL_LINEAR;          
		unsigned int m_FilterMax = GL_LINEAR;          
		unsigned int m_WrapS = GL_CLAMP_TO_EDGE;  
		unsigned int m_WrapT = GL_CLAMP_TO_EDGE;  
		unsigned int m_WrapR = GL_CLAMP_TO_EDGE;   
		bool m_Mipmapping = false;

		unsigned int m_FaceWidth  = 0;
		unsigned int m_FaceHeight = 0;

	public:
		TextureCube();
		~TextureCube();

		void DefaultInitialize(unsigned int, unsigned int, unsigned int,unsigned int,bool mipmap = false);


		void GenerateFace(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned char*);

		void SetMipFace(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned char*);

		void Resize(unsigned int, unsigned int);

		void Bind(int unit = -1);
		void UnBind();
	private:
		friend class LoadTexture;
		friend class RenderHelper;
	};
}


