#pragma once



namespace Rulomi {

	class TimeInterval
	{
	public:
		TimeInterval(float time = 0.0f)
			:m_Time(time)
		{

		}

		operator float() const {
			return m_Time;
		}

		float getTimeMilliseconds() const{ return m_Time * 1000.0f; }

	private:
		float m_Time;

	};

}