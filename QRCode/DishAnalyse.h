/******************************************************************************************************
 *   方案思想：
 *   1. 接收PLC上传的信号， 空盘信号为1， 否则为0；
 *   2. 以其中一个格子为例：
 *   2.1 当前状态为空盘子， 判断当前状态与当前空盘状态的时间差，如果低于每个时间间隔，则是空盘的持续； 否则改变状态；
 *   2.2 当前的空盘状态的持续时间大于某阈值时，则判断该盘的状态为空盘，并更新状态；
 *   3. 根据步骤2一次类推;
 *   4. 判断逻辑如下：输入时间参数，判断当前时间与空盘状态的时间间隔，当低于某阈值时，则判断有空盘；
 *   5. 方案结束。
 *                                                 zhenbin, jiang
 * 												    2019-06-27
******************************************************************************************************/

#ifndef DISH_ANALYSE_H
#define DISH_ANALYSE_H

//盘子的状态
typedef struct {
	int status;
	double currenceTime;
}DishStatus;

//时间范围 
typedef struct {
	double startTime;
	double endTime;
}TimeRange;

//盘子分析类
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
	double m_timeDistance;                 /* 时间间隔 */
	double m_timeThreshold;                /* 时间阈值， 持续多长时间才算空盘子 */
	double m_judgeTime;

	int m_result;                          /* 结果 */
	TimeRange m_curTimeRange[4];           /* 状态结果 */
	TimeRange m_lastTimeRange[4];          /* 最新空盘的信息 */

private:
	void CodeDishStatus(DishStatus status, bool& valid1, bool& valid2, bool& valid3, bool& valid4);

	void ExeDish1(double curTime);

	void ExeDish2(double curTime);

	void ExeDish3(double curTime);

	void ExeDish4(double curTime);

	void ExeDist(double curTime);
};


#endif // !DISH_ANALYSE_H

