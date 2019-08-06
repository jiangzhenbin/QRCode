#ifndef TYPES_DEF_H
#define TYPES_DEF_H

#include <stdlib.h>
#include <time.h>
#include <vector>
#include <HalconCpp.h>

#define  VERSION_NO    "V1.0.0.2"

//二维持码类型
typedef enum BARCODE_RESULT_STATUS {
	OK_STATUS = 0,                            /* OK状态 */
	NO_STATUS = 1,                            /* 无条码 */
	LENGTH_STUTAS = 2,                        /* 长度缺陷 */
	BATCH_STUTAS = 3                          /* 批次缺陷 */
}BARCODE_RESULT_STATUS;

//二维持码类型
typedef enum BARCODE_2D_TYPE {
	DM_BARCODE_TYPE = 0,                      /* DM二维码 */
	QR_BARCODE_TYPE = 1,                      /* QR二维码 */
	PDF_BARCODE_TYPE = 2                      /* PDF二维码 */
}BARCODE_2D_TYPE;

typedef enum CODE_DM_TYPE {
	DEFAULT_DM_TYPE = 0,                      /* 默认模式 */
	LOW_DM_TYPE = 1,                          /* 低通模式 */
    HIGH_DM_TYPE = 2                          /* 高通模式 */
}CODE_DM_TYPE;

typedef enum CODE_QR_TYPE {
	DEFAULT_QR_TYPE = 0,                      /* 默认模式 */
	OPT_QR_TYPE = 1,                          /* 优化模式 */
}CODE_QR_TYPE;

//算法执行模式
typedef enum ALGORITHM_EXECUTE_MODE {
	TEST_EXECUTE_MODE = 0,           /* 测试模式 */
	DEBUG_EXECUTE_MODE = 1,          /* 调试模式 */
	PARAM_EXECUTE_MODE = 2,          /* 生成标准 */
}ALGORITHM_EXECUTE_MODE;

//图像预处理类型
typedef enum IMAGE_FILTER_TYPE {
	DEFAULT_FILTER_TYPE = 0,                      /* 不做处理 */
	MEAN_FILTER_TYPE = 1,                         /* 均值滤波 */
	BINOMIAL_FILTER_TYPE = 2                      /* 二项式滤波 */
}IMAGE_FILTER_TYPE;

typedef enum CODE2D_VIEW_TYPE {
	ORIGINE_CODE2D_VIEW_TYPE = 0,              /* 原图 */
	PROC_CODE2D_VIEW_TYPE = 1,                 /* 预处理图 */
	REGION_CODE2D_VIEW_TYPE = 2                /* 结果区域 */
}CODE2D_VIEW_TYPE;

//图像模式
typedef enum IMAGE_DATA_TYPE {
	DEFAULT_DATE_TYPE = 0,        /* 图像数据 */
	REGION_DATA_TYPE = 1          /* 区域数据 */
}IMAGE_DATA_TYPE;

//图像返回结果值
typedef struct {
	HalconCpp::HObject hObject;   /* 图像数据， 或区域数据 */
	HalconCpp::HObject hRegion;   /* 区域数据 */
	int tyMode;                   /* 模式， 0表示图像， 1表示区域 */
	int width;                    /* 图像的宽度 */
	int height;                   /* 图像的高度 */
}ImageData;

//AOI的检测参数 
typedef struct {
	int idd;                    /* 子id值*/
	int id;                     /* 主id值 */
	int iType;                  /* 算法模式 */
	int int0;                   /* 条码模式 */
	int int1;
	int int2;
	int int3;
	int int4;
	int int5;
	int int6;
	int int7;
	int int8;
	int int9;
	int int10;
}AoiParams;

//图像预处理参数
typedef struct {
	int type;                   /* 预处理类型 */
	int maskWidth;              /* 滤波宽度 */
	int maskHeight;             /* 滤波高度 */
}FilterPara;

//输出方位
typedef struct {
	double x;
	double y;
}Point2f;

//输出范围
typedef struct {
	Point2f pt0;
	Point2f pt1;
}RoiRegion;



#endif // !TYPES_DEF_H

