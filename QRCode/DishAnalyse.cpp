#include "stdafx.h"
#include "DishAnalyse.h"

DishAnalyse::DishAnalyse()
{
	/* code */
	for (int i = 0; i < 4; i++)
	{
		m_curTimeRange[i].startTime = -99999999.0f;
		m_curTimeRange[i].endTime = 0.0f;

		m_lastTimeRange[i].startTime = -99999999.0f;
		m_lastTimeRange[i].endTime = 0.0f;
	}

	m_timeDistance = 0.5f;
	m_timeThreshold = 2.0f;
	m_judgeTime = 3.0f;
}

DishAnalyse::~DishAnalyse()
{
	/* code */
}

void DishAnalyse::SetTimePara(double distance, double threshold, double judge)
{
	/*¡¡code */
	m_timeDistance = distance;
	m_timeThreshold = threshold;
	m_judgeTime = judge;
}

void DishAnalyse::Execute(DishStatus status)
{
	/* code */
	bool valid1 = false;
	bool valid2 = false;
	bool valid3 = false;
	bool valid4 = false;
	CodeDishStatus(status, valid1, valid2, valid3, valid4);

	if (valid1)  ExeDish1(status.currenceTime);

	if (valid2)  ExeDish2(status.currenceTime);

	if (valid3)  ExeDish3(status.currenceTime);

	if (valid4)  ExeDish4(status.currenceTime);

	ExeDist(status.currenceTime);
}

void DishAnalyse::ExeDist(double curTime)
{
	/* code */
	m_result = 0;

	double dt = curTime - m_lastTimeRange[0].endTime;
	if (dt < m_judgeTime)  m_result = m_result + 1;

	dt = curTime - m_lastTimeRange[1].endTime;
	if (dt < m_judgeTime)  m_result = m_result + 2;

	dt = curTime - m_lastTimeRange[2].endTime;
	if (dt < m_judgeTime)  m_result = m_result + 4;

	dt = curTime - m_lastTimeRange[3].endTime;
	if (dt < m_judgeTime)  m_result = m_result + 8;
}

void DishAnalyse::ExeDish4(double curTime)
{
	/* code */
	double dt = curTime - m_curTimeRange[3].endTime;
	if (dt < m_timeDistance)
	{
		m_curTimeRange[3].endTime = curTime;

		double dt = curTime - m_curTimeRange[3].startTime;

		if (dt > m_timeThreshold)
		{
			m_lastTimeRange[3].startTime = m_curTimeRange[3].startTime;
			m_lastTimeRange[3].endTime = m_curTimeRange[3].endTime;
		}
	}
	else
	{
		m_curTimeRange[3].startTime = curTime;
		m_curTimeRange[3].endTime = curTime;
	}

}

void DishAnalyse::ExeDish3(double curTime)
{
	/* code */
	double dt = curTime - m_curTimeRange[2].endTime;
	if (dt < m_timeDistance)
	{
		m_curTimeRange[2].endTime = curTime;

		double dt = curTime - m_curTimeRange[2].startTime;

		if (dt > m_timeThreshold)
		{
			m_lastTimeRange[2].startTime = m_curTimeRange[2].startTime;
			m_lastTimeRange[2].endTime = m_curTimeRange[2].endTime;
		}
	}
	else
	{
		m_curTimeRange[2].startTime = curTime;
		m_curTimeRange[2].endTime = curTime;
	}
}

void DishAnalyse::ExeDish2(double curTime)
{
	/* code */
	double dt = curTime - m_curTimeRange[1].endTime;
	if (dt < m_timeDistance)
	{
		m_curTimeRange[1].endTime = curTime;

		double dt = curTime - m_curTimeRange[1].startTime;

		if (dt > m_timeThreshold)
		{
			m_lastTimeRange[1].startTime = m_curTimeRange[1].startTime;
			m_lastTimeRange[1].endTime = m_curTimeRange[1].endTime;
		}
	}
	else
	{
		m_curTimeRange[1].startTime = curTime;
		m_curTimeRange[1].endTime = curTime;
	}
}

void DishAnalyse::ExeDish1(double curTime)
{
	/* code */
	double dt = curTime - m_curTimeRange[0].endTime;
	if (dt < m_timeDistance)
	{
		m_curTimeRange[0].endTime = curTime;

		double dt = curTime - m_curTimeRange[0].startTime;

		if (dt > m_timeThreshold)
		{
			m_lastTimeRange[0].startTime = m_curTimeRange[0].startTime;
			m_lastTimeRange[0].endTime = m_curTimeRange[0].endTime;
		}
	}
	else
	{
		m_curTimeRange[0].startTime = curTime;
		m_curTimeRange[0].endTime = curTime;
	}
}

int DishAnalyse::GetResult(double curTime)
{
	/* code */
	ExeDist(curTime);

	return m_result;
}

void DishAnalyse::CodeDishStatus(DishStatus status, bool& valid1, bool& valid2, bool& valid3, bool& valid4)
{
	/* code */
	valid1 = false;
	valid2 = false;
	valid3 = false;
	valid4 = false;

	int val = status.status % 2;
	if (val > 0)  valid1 = true;
	val = status.status % 4;
	if (val > 1)  valid2 = true;
	val = status.status % 8;
	if (val > 3)  valid3 = true;
	if (status.status > 7)  valid4 = true;
}