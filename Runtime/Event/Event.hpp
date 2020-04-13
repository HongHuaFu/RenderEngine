#pragma once

#include <string>

namespace RE
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication    = 1 << 0
	};

	// �¼�Ӧ������Ҫ����Ϣ
	// ��Ҫ�����߼�������������
	class Event
	{
	public:
		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName()    const = 0;
		virtual int GetCategoryFlags()   const = 0;
		virtual std::string ToString()   const { return GetName(); }

		// �ж��Ƿ�Ϊ�����¼�
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	// ��GLFW�а󶨸������͵��¼����磺EventWindowClose��EventWindowResize...
	// Application��������Window�е��¼��ص����� EventCallBackFn(Event&)
	// ���Application�е��¼�OnEvent��
	// ÿ���¼��ص�������EventCallBackFn������Event�����ִ�ж�Ӧ�ĺ���F��
	// ��Ȼÿ��F������Ϊ�麯������ô����Ϳ���������ʵ���¼�����
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// ����F�����ɱ������ƶ�
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// ��F�Ĳ���������func��������������������
				m_Event.Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	// ����¼����
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}