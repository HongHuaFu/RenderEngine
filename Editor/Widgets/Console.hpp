#pragma once
#include "../Widget.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

#ifdef ERROR
#undef ERROR
#endif // ERROR


namespace Widgets
{
	enum class Log_Type
	{
		INFO = 0,
		WARN = 1,
		ERROR = 2
	};

	class EditorLogger
	{
		friend class Console;
	public:
		EditorLogger()
		{
			m_AutoScroll = true;
			Clear();
		}

		~EditorLogger()
		{
			Clear();
		}

		inline void AddLog(Log_Type type,const char* fmt, ...) IM_FMTARGS(2)
		{
			int old_size = m_Buf.size();
			va_list args;
			va_start(args, fmt);
			m_Buf.appendfv(fmt, args);
			va_end(args);
			for(int new_size = m_Buf.size(); old_size < new_size; old_size++)
			{
				if(m_Buf[old_size]=='\n')
				{
					m_LineOffsets.push_back(old_size + 1);
					m_TypesLayout.push_back(type);

					m_LogTypeMaxWidth[static_cast<int>(type)] = std::max(m_LogTypeMaxWidth[static_cast<int>(type)],  static_cast<float>(new_size - old_size + 1));
					m_LogTypeCount[static_cast<int>(type)] ++;
				}	
			}
		}

	private:
		void Clear();
		void Draw();

	private:
		ImGuiTextBuffer m_Buf;
		ImGuiTextFilter m_Filter;

		ImVector<int> m_LineOffsets;   
		std::vector<Log_Type> m_TypesLayout;
		unsigned int m_LogTypeCount[3]{ 0, 0, 0 };
		const std::vector<ImVec4> m_LogTypeColor
		{
			ImVec4(1.0f,1.0f, 1.0f, 1.0f),	// Info
			ImVec4(1.0f, 1.0f, 0.0f, 1.0f),	// Warning
			ImVec4(1.0f, 0.4f, 0.4f, 1.0f)	// Error
		};

		bool m_AutoScroll; 

		// 警告类型可见
		bool m_LogTypeVisibility[3]{ true, true, true };

		// 最大长度
		float m_LogTypeMaxWidth[3]{ 0, 0, 0 };
	};

	class Console: public Widget
	{
	public:
		Console();
		virtual void Tick() override;

		static std::shared_ptr<EditorLogger> m_Logger;
	};

	inline static void Log_Info(std::string str)
	{
		if(Console::m_Logger)
		{
			auto builder = u8"[讯息]: " + str + " \n";
			
			Console::m_Logger->AddLog(Log_Type::INFO,builder.c_str());
		}
		else
		{
			std::cout << u8"[讯息]: " + str + " \n";
		}
		
	}

	inline static void Log_Warn(std::string str)
	{
		if(Console::m_Logger)
		{
			auto builder = u8"[警告]: " + str + " \n";
			Console::m_Logger->AddLog(Log_Type::WARN,builder.c_str());
		}
		else
		{
			std::cout << u8"[警告]: " + str + " \n";
		}
	}

	inline static void Log_Error(std::string str)
	{
		if(Console::m_Logger)
		{
			auto builder = u8"[错误]: " + str + " \n";
			Console::m_Logger->AddLog(Log_Type::ERROR,builder.c_str());
		}
		else
		{
			std::cout << u8"[错误]: " + str + " \n";
		}
	}
}

#define E_INFO(a)  ::Widgets::Log_Info(a);
#define E_WARN(a)  ::Widgets::Log_Warn(a);
#define E_ERROR(a) ::Widgets::Log_Error(a);