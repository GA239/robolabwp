#pragma once

#include <wrl.h>

// Вспомогательный класс для базовых операций со временем.
ref class BasicTimer sealed
{
public:
	// Инициализирует внутренние значения таймера.
	BasicTimer()
	{
		if (!QueryPerformanceFrequency(&m_frequency))
		{
			throw ref new Platform::FailureException();
		}
		Reset();
	}
	
	// Сброс таймера к начальным значениям.
	void Reset()
	{
		Update();
		m_startTime = m_currentTime;
		m_total = 0.0f;
		m_delta = 1.0f / 60.0f;
	}
	
	// Обновление внутренних значений таймера.
	void Update()
	{
		if (!QueryPerformanceCounter(&m_currentTime))
		{
			throw ref new Platform::FailureException();
		}
		
		m_total = static_cast<float>(
			static_cast<double>(m_currentTime.QuadPart - m_startTime.QuadPart) /
			static_cast<double>(m_frequency.QuadPart)
			);
		
		if (m_lastTime.QuadPart == m_startTime.QuadPart)
		{
			// Непосредственно после сброса таймера сообщает о временном интервале, эквивалентном времени кадра частотою 60 Гц.
			m_delta = 1.0f / 60.0f;
		}
		else
		{
			m_delta = static_cast<float>(
				static_cast<double>(m_currentTime.QuadPart - m_lastTime.QuadPart) /
				static_cast<double>(m_frequency.QuadPart)
				);
		}
		
		m_lastTime = m_currentTime;
	}
	
	// Длительность в секундах между последним вызовом Reset() и последним вызовом Update().
	property float Total
	{
		float get() { return m_total; }
	}
	
	// Длительность в секундах между двумя последними вызовами Update().
	property float Delta
	{
		float get() { return m_delta; }
	}

private:
	LARGE_INTEGER m_frequency;
	LARGE_INTEGER m_currentTime;
	LARGE_INTEGER m_startTime;
	LARGE_INTEGER m_lastTime;
	float m_total;
	float m_delta;
};
