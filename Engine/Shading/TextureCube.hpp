#ifndef ENGINE_TEXTURE_CUBE
#define ENGINE_TEXTURE_CUBE

#include <glad/glad.h>

namespace Engine
{
	class TextureCube
	{
	private:
		friend class PBR;
		friend class LoadTexture;
		friend class Renderer;
	private:
		unsigned int m_ID;
		unsigned int m_InternalFormat = GL_RGBA;           
		unsigned int m_Format         = GL_RGBA;           
		unsigned int m_Type           = GL_UNSIGNED_BYTE;
		unsigned int m_FilterMin      = GL_LINEAR;          
		unsigned int m_FilterMax      = GL_LINEAR;          
		unsigned int m_WrapS          = GL_CLAMP_TO_EDGE;  
		unsigned int m_WrapT          = GL_CLAMP_TO_EDGE;  
		unsigned int m_WrapR          = GL_CLAMP_TO_EDGE;   
		bool m_Mipmapping = false;

		unsigned int m_FaceWidth  = 0;
		unsigned int m_FaceHeight = 0;

	public:
		 TextureCube();
		~TextureCube();

		void DefaultInitialize(unsigned int width, 
							   unsigned int height, 
							   unsigned int format,
							   unsigned int type,
							   bool mipmap = false);


		void GenerateFace(unsigned int face, 
					      unsigned int width, 
						  unsigned int height, 
						  unsigned int format, 
						  unsigned int type, 
						  unsigned char* data);

		void SetMipFace(unsigned int face, 
					    unsigned int width, 
						unsigned int height, 
						unsigned int format, 
						unsigned int type, 
						unsigned int mipLevel, 
						unsigned char* data);

		void Resize(unsigned int width, unsigned int height);

		void Bind(int unit = -1);
		void UnBind();
	};
}

#endif // !ENGINE_TEXTURE_CUBE
