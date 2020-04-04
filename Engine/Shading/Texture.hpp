#ifndef ENGINE_TEXTURE_HPP
#define ENGINE_TEXTURE_HPP

#include <glad/glad.h>
#include <string>

namespace Engine
{
	class Texture
	{
	public:
		 Texture() = default;

		 // 使用手动GC
		~Texture() = default;

		// 1D texture
		void Create(unsigned int width, 
					unsigned int internalFormat, 
					unsigned int format, 
					unsigned int type,
					void* data);


		// 2D texture
		void Create(unsigned int width, 
					unsigned int height, 
					unsigned int internalFormat, 
					unsigned int format, 
					unsigned int type, 
					void* data);

		// 3D texture
		void Create(unsigned int width, 
					unsigned int height, 
					unsigned int depth, 
					unsigned int internalFormat, 
					unsigned int format, 
					unsigned int type, 
					void* data);

		// 重新设置尺寸，重新设置内存
		void ReSize(unsigned int width, unsigned int height = 0, unsigned int depth = 0);


		inline void Bind(int unit = -1) 
		{ 
			if(unit >= 0)
				glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(m_Target, m_ID);  
		}

		inline void UnBind() 
		{
			glBindTexture(m_Target, 0); 
		}

		void SetWrapMode(unsigned int wrapMode, bool bind = false);

		void SetFilterMin(unsigned int filter, bool bind = false);

		void SetFilterMax(unsigned int filter, bool bind = false);

	public: // getter


	private:
		unsigned int m_ID;

		unsigned int m_Target		  = GL_TEXTURE_2D;		     // 贴图类型
		unsigned int m_InternalFormat = GL_RGBA;				 // 颜色组件数
		unsigned int m_Format         = GL_RGBA;				 // 颜色存储格式
		unsigned int m_Type           = GL_UNSIGNED_BYTE;

		// 过滤格式
		unsigned int m_FilterMin      = GL_LINEAR_MIPMAP_LINEAR; 
		unsigned int m_FilterMax      = GL_LINEAR;        

		// S T R Wrapping
		unsigned int m_WrapS          = GL_REPEAT;       
		unsigned int m_WrapT          = GL_REPEAT;   
		unsigned int m_WrapR          = GL_REPEAT; 

		bool m_Mipmapping			    = true;

		unsigned int m_Width  = 0;
		unsigned int m_Height = 0;
		unsigned int m_Depth  = 0;

	private:
		friend Texture LoadTexture(std::string,unsigned int,unsigned int,bool);
	};
}



#endif 
