/******************************************************************************************************
 *   ����˼�룺
 *   1. ����PLC�ϴ����źţ� �����ź�Ϊ1�� ����Ϊ0��
 *   2. ������һ������Ϊ����
 *   2.1 ��ǰ״̬Ϊ�����ӣ� �жϵ�ǰ״̬�뵱ǰ����״̬��ʱ���������ÿ��ʱ���������ǿ��̵ĳ����� ����ı�״̬��
 *   2.2 ��ǰ�Ŀ���״̬�ĳ���ʱ�����ĳ��ֵʱ�����жϸ��̵�״̬Ϊ���̣�������״̬��
 *   3. ���ݲ���2һ������;
 *   4. �ж��߼����£�����ʱ��������жϵ�ǰʱ�������״̬��ʱ������������ĳ��ֵʱ�����ж��п��̣�
 *   5. ����������
 *                                                 zhenbin, jiang
 * 												    2019-06-27
******************************************************************************************************/

#ifndef DISH_ANALYSE_H
#define DISH_ANALYSE_H

//���ӵ�״̬
typedef struct {
	int status;
	double currenceTime;
}DishStatus;

//ʱ�䷶Χ 
typedef struct {
	double startTime;
	double endTime;
}TimeRange;

//���ӷ�����
class DishAnalyse
{
public:
	DishAnalyse();
	~DishAnalyse();

public:
	void SetTimePara(double distance, double threshold, double judge);

	void Execute(DishStatus status);

	int GetResult(double curTime);
private:
	double m_timeDistance;                 /* ʱ���� */
	double m_timeThreshold;                /* ʱ����ֵ�� �����೤ʱ���������� */
	double m_judgeTime;

	int m_result;                          /* ��� */
	TimeRange m_curTimeRange[4];           /* ״̬��� */
	TimeRange m_lastTimeRange[4];          /* ���¿��̵���Ϣ */

private:
	void CodeDishStatus(DishStatus status, bool& valid1, bool& valid2, bool& valid3, bool& valid4);

	void ExeDish1(double curTime);

	void ExeDish2(double curTime);

	void ExeDish3(double curTime);

	void ExeDish4(double curTime);

	void ExeDist(double curTime);
};


#endif // !DISH_ANALYSE_H

