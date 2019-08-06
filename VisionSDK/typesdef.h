#ifndef TYPES_DEF_H
#define TYPES_DEF_H

#include <stdlib.h>
#include <time.h>
#include <vector>
#include <HalconCpp.h>

#define  VERSION_NO    "V1.0.0.2"

//��ά��������
typedef enum BARCODE_RESULT_STATUS {
	OK_STATUS = 0,                            /* OK״̬ */
	NO_STATUS = 1,                            /* ������ */
	LENGTH_STUTAS = 2,                        /* ����ȱ�� */
	BATCH_STUTAS = 3                          /* ����ȱ�� */
}BARCODE_RESULT_STATUS;

//��ά��������
typedef enum BARCODE_2D_TYPE {
	DM_BARCODE_TYPE = 0,                      /* DM��ά�� */
	QR_BARCODE_TYPE = 1,                      /* QR��ά�� */
	PDF_BARCODE_TYPE = 2                      /* PDF��ά�� */
}BARCODE_2D_TYPE;

typedef enum CODE_DM_TYPE {
	DEFAULT_DM_TYPE = 0,                      /* Ĭ��ģʽ */
	LOW_DM_TYPE = 1,                          /* ��ͨģʽ */
    HIGH_DM_TYPE = 2                          /* ��ͨģʽ */
}CODE_DM_TYPE;

typedef enum CODE_QR_TYPE {
	DEFAULT_QR_TYPE = 0,                      /* Ĭ��ģʽ */
	OPT_QR_TYPE = 1,                          /* �Ż�ģʽ */
}CODE_QR_TYPE;

//�㷨ִ��ģʽ
typedef enum ALGORITHM_EXECUTE_MODE {
	TEST_EXECUTE_MODE = 0,           /* ����ģʽ */
	DEBUG_EXECUTE_MODE = 1,          /* ����ģʽ */
	PARAM_EXECUTE_MODE = 2,          /* ���ɱ�׼ */
}ALGORITHM_EXECUTE_MODE;

//ͼ��Ԥ��������
typedef enum IMAGE_FILTER_TYPE {
	DEFAULT_FILTER_TYPE = 0,                      /* �������� */
	MEAN_FILTER_TYPE = 1,                         /* ��ֵ�˲� */
	BINOMIAL_FILTER_TYPE = 2                      /* ����ʽ�˲� */
}IMAGE_FILTER_TYPE;

typedef enum CODE2D_VIEW_TYPE {
	ORIGINE_CODE2D_VIEW_TYPE = 0,              /* ԭͼ */
	PROC_CODE2D_VIEW_TYPE = 1,                 /* Ԥ����ͼ */
	REGION_CODE2D_VIEW_TYPE = 2                /* ������� */
}CODE2D_VIEW_TYPE;

//ͼ��ģʽ
typedef enum IMAGE_DATA_TYPE {
	DEFAULT_DATE_TYPE = 0,        /* ͼ������ */
	REGION_DATA_TYPE = 1          /* �������� */
}IMAGE_DATA_TYPE;

//ͼ�񷵻ؽ��ֵ
typedef struct {
	HalconCpp::HObject hObject;   /* ͼ�����ݣ� ���������� */
	HalconCpp::HObject hRegion;   /* �������� */
	int tyMode;                   /* ģʽ�� 0��ʾͼ�� 1��ʾ���� */
	int width;                    /* ͼ��Ŀ�� */
	int height;                   /* ͼ��ĸ߶� */
}ImageData;

//AOI�ļ����� 
typedef struct {
	int idd;                    /* ��idֵ*/
	int id;                     /* ��idֵ */
	int iType;                  /* �㷨ģʽ */
	int int0;                   /* ����ģʽ */
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

//ͼ��Ԥ�������
typedef struct {
	int type;                   /* Ԥ�������� */
	int maskWidth;              /* �˲���� */
	int maskHeight;             /* �˲��߶� */
}FilterPara;

//�����λ
typedef struct {
	double x;
	double y;
}Point2f;

//�����Χ
typedef struct {
	Point2f pt0;
	Point2f pt1;
}RoiRegion;



#endif // !TYPES_DEF_H

