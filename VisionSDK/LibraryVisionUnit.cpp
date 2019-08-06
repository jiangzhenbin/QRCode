#include "stdafx.h"
#include "LibraryVisionUnit.h"

void FreeBarcode2DModelApi(HalconCpp::HTuple& hvModelID)
{
	/* code */
	try {
		HalconCpp::ClearDataCode2dModel(hvModelID);

	} catch (HalconCpp::HException&) {
		return;
	} catch (const std::exception&) {
		return;
	}
}

void CreateCodeDMModelApi(int codeMode, HalconCpp::HTuple& hvModelID) {
	/* code */
	hvModelID = -1;

	int id = -1;
	try {
		if (DEFAULT_DM_TYPE == codeMode) {
			HalconCpp::CreateDataCode2dModel("Data Matrix ECC 200", HalconCpp::HTuple(), HalconCpp::HTuple(), &hvModelID);
		}
		else if (LOW_DM_TYPE == codeMode) {
			HalconCpp::CreateDataCode2dModel("Data Matrix ECC 200", "default_parameters", "enhanced_recognition", &hvModelID);
			HalconCpp::SetDataCode2dParam(hvModelID, "contrast_tolerance", "low");
		}
		else if (HIGH_DM_TYPE == codeMode) {
			HalconCpp::CreateDataCode2dModel("Data Matrix ECC 200", "default_parameters", "enhanced_recognition", &hvModelID);
			HalconCpp::SetDataCode2dParam(hvModelID, "contrast_tolerance", "high");
		}
	} catch (HalconCpp::HException&) {
		return;
	} catch (const std::exception&) {
		return;
	}
}

void ExecuteDataCode2DApi(HalconCpp::HObject& hObject, HalconCpp::HObject& hTarget, HalconCpp::HTuple& idModel, std::string& codeString, RoiRegion& region) {
	/* code */
	region.pt0.x = -1;
	region.pt0.y = -1;
	region.pt1.x = -1;
	region.pt1.y = -1;
	try {
		HalconCpp::HTuple hvResultHandles, hvDataStrings;
		HalconCpp::FindDataCode2d(hObject, &hTarget, idModel, HalconCpp::HTuple(), HalconCpp::HTuple(), &hvResultHandles, &hvDataStrings);

		HalconCpp::HTuple hvLength;
		hvLength = hvDataStrings.TupleLength();
		int iLength = hvLength[0].I();
		HalconCpp::HTuple hvY1, hvX1, hvY2, hvX2;
		if (0 == iLength) {
			HalconCpp::GenEmptyObj(&hTarget);
			codeString = "";
		} else {
			HalconCpp::GenRegionContourXld(hTarget, &hTarget, "filled");
			HalconCpp::SmallestRectangle1(hTarget, &hvY1, &hvX1, &hvY2, &hvX2);

			double xCenter = 0.5 * (hvX1[0].I() + hvX2[0].I());
			double yCenter = 0.5 * (hvY1[0].I() + hvY2[0].I());

			region.pt0.x = xCenter + 2 * (hvX1[0].I() - xCenter);
			region.pt0.y = yCenter + 2 * (hvY1[0].I() - yCenter);
			region.pt1.x = xCenter + 2 * (hvX2[0].I() - xCenter);
			region.pt1.y = yCenter + 2 * (hvY2[0].I() - yCenter);

			codeString = hvDataStrings[0].S();
		}
	} catch (HalconCpp::HException&) {
		HalconCpp::GenEmptyObj(&hTarget);
		codeString = "";
	} catch (const std::exception&) {
		HalconCpp::GenEmptyObj(&hTarget);
		codeString = "";
	}
}

void ImageCopyApi(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget) {
	/* code */
	try {
		HalconCpp::CopyImage(hObject, hTarget);
	} catch (HalconCpp::HException&) {
		HalconCpp::GenEmptyObj(hTarget);
	} catch (const std::exception&) {
		HalconCpp::GenEmptyObj(hTarget);
	}
}

void ImageMedianApi(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, double szRadius) {
	/* code */
	HalconCpp::HTuple hvCount;
	HalconCpp::CountObj(hObject, &hvCount);
	if (hvCount[0].I() < 0) {
		HalconCpp::GenEmptyObj(hTarget);
		return;
	}


	try {
		HalconCpp::MedianImage(hObject, hTarget, "circle", szRadius, "mirrored");
	} catch (HalconCpp::HException&) {
		HalconCpp::CopyImage(hObject, hTarget);
	} catch (const std::exception&) {
		HalconCpp::CopyImage(hObject, hTarget);
	}
}

void ImageFilterProcessApi(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, FilterPara para) {
	/* code */
	HalconCpp::HTuple hvCount;
	HalconCpp::CountObj(hObject, &hvCount);
	if (hvCount[0].I() < 0) {
		HalconCpp::GenEmptyObj(hTarget);
		return;
	}

	try {
		switch (para.type) {
		case DEFAULT_FILTER_TYPE:
			HalconCpp::CopyImage(hObject, hTarget);
			break;

		case MEAN_FILTER_TYPE:
			HalconCpp::MeanImage(hObject, hTarget, para.maskWidth, para.maskHeight);
			break;

		case BINOMIAL_FILTER_TYPE:
			HalconCpp::BinomialFilter(hObject, hTarget, para.maskWidth, para.maskHeight);
			break;

		default:
			HalconCpp::CopyImage(hObject, hTarget);
			break;
		}
	} catch (HalconCpp::HException&) {
		HalconCpp::CopyImage(hObject, hTarget);
	} catch (const std::exception&) {
		HalconCpp::CopyImage(hObject, hTarget);
	}
}

void ImageZoomApi(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, double rate) {
	/* code */
	HalconCpp::HTuple hvCount;
	HalconCpp::CountObj(hObject, &hvCount);
	if (hvCount[0].I() < 0) {
		HalconCpp::GenEmptyObj(hTarget);
		return;
	}

	try {
		HalconCpp::ZoomImageFactor(hObject, hTarget, rate, rate, "constant");
	} catch (HalconCpp::HException&) {
		HalconCpp::CopyImage(hObject, hTarget);
	} catch (const std::exception&) {
		HalconCpp::CopyImage(hObject, hTarget);
	}
}

void CountObjectApi(HalconCpp::HObject& hObject, int* countResult) {
	/* code */
	*countResult = 0;
	try {
		HalconCpp::HTuple hvCount;
		HalconCpp::CountObj(hObject, &hvCount);

		*countResult = hvCount[0].I();
	} catch (HalconCpp::HException&) {

	} catch (const std::exception&) {

	}
}

void RegionZooomApi(HalconCpp::HObject& hRegion, HalconCpp::HObject* hTarget, double rate) {
	/* code */
	HalconCpp::HTuple hvCount;
	HalconCpp::CountObj(hRegion, &hvCount);
	if (hvCount[0].I() < 0) {
		HalconCpp::GenEmptyObj(hTarget);
		return;
	}

	try {
		HalconCpp::ZoomRegion(hRegion, hTarget, rate, rate);

	} catch (HalconCpp::HException&) {
		HalconCpp::GenEmptyObj(hTarget);
	} catch (const std::exception&) {
		HalconCpp::GenEmptyObj(hTarget);
	}
}

void GetImageSizeApi(HalconCpp::HObject& hObject, int* width, int* height) {
	/* code */
	*width = 0;
	*height = 0;
	HalconCpp::HTuple hvCount;
	HalconCpp::CountObj(hObject, &hvCount);
	if (hvCount[0].I() < 0) return;

	try {
		HalconCpp::HTuple hvWidth, hvHeight;
		HalconCpp::GetImageSize(hObject, &hvWidth, &hvHeight);

		*width = hvWidth[0].I();
		*height = hvHeight[0].I();;

	} catch (HalconCpp::HException&) {
	
	} catch (const std::exception&) {
		
	}

}

void GenContourRegionApi(HalconCpp::HObject& hRegion, HalconCpp::HObject* hTarget) {
	/* code */
	HalconCpp::HTuple hvCount;
	HalconCpp::CountObj(hRegion, &hvCount);
	if (hvCount[0].I() < 0) {
		HalconCpp::GenEmptyObj(hTarget);
		return;
	}

	try {
		HalconCpp::GenContourRegionXld(hRegion, hTarget, "border_holes");
	}
	catch (HalconCpp::HException&) {
		HalconCpp::GenEmptyObj(hTarget);
	}
	catch (const std::exception&) {
		HalconCpp::GenEmptyObj(hTarget);
	}
}

void CreateCodeQRModelApi(int codeMode, HalconCpp::HTuple& hvModelID) {
	/* code */
	hvModelID = -1;
	try {
		if (OPT_QR_TYPE == codeMode) {
			HalconCpp::CreateDataCode2dModel("QR Code", HalconCpp::HTuple(), HalconCpp::HTuple(), &hvModelID);
			HalconCpp::SetDataCode2dParam(hvModelID, "version", 1);
			HalconCpp::SetDataCode2dParam(hvModelID, "model_type", 2);
			HalconCpp::SetDataCode2dParam(hvModelID, "module_size_min", 5);
			HalconCpp::SetDataCode2dParam(hvModelID, "module_size_max", 6);
			HalconCpp::SetDataCode2dParam(hvModelID, "module_gap", "no");
			HalconCpp::SetDataCode2dParam(hvModelID, "mirrored", "no");
			HalconCpp::SetDataCode2dParam(hvModelID, "contrast_min", 10);
		} else {
			HalconCpp::CreateDataCode2dModel("QR Code", HalconCpp::HTuple(), HalconCpp::HTuple(), &hvModelID);
		}
	} catch (HalconCpp::HException&) {
		
	} catch (const std::exception&) {
		
	}
}

void ExeBarcodeData2DApi(HalconCpp::HObject& hObject, HalconCpp::HObject& hTarget, int codeType, int codeMode, std::string& codeString, RoiRegion& region)
{
	/* code */
	region.pt0.x = -1;
	region.pt0.y = -1;
	region.pt1.x = -1;
	region.pt1.y = -1;
	try {
		//1. 创建条码模式 
		HalconCpp::HTuple hvModelID;
		if (QR_BARCODE_TYPE == codeType)
		{
			if (OPT_QR_TYPE == codeMode) {
				HalconCpp::CreateDataCode2dModel("QR Code", HalconCpp::HTuple(), HalconCpp::HTuple(), &hvModelID);
				HalconCpp::SetDataCode2dParam(hvModelID, "version", 1);
				HalconCpp::SetDataCode2dParam(hvModelID, "model_type", 2);
				HalconCpp::SetDataCode2dParam(hvModelID, "module_size_min", 5);
				HalconCpp::SetDataCode2dParam(hvModelID, "module_size_max", 6);
				HalconCpp::SetDataCode2dParam(hvModelID, "module_gap", "no");
				HalconCpp::SetDataCode2dParam(hvModelID, "mirrored", "no");
				HalconCpp::SetDataCode2dParam(hvModelID, "contrast_min", 10);
			} else {
				HalconCpp::CreateDataCode2dModel("QR Code", HalconCpp::HTuple(), HalconCpp::HTuple(), &hvModelID);
			}
		} else {
			if (DEFAULT_DM_TYPE == codeMode) {
				HalconCpp::CreateDataCode2dModel("Data Matrix ECC 200", HalconCpp::HTuple(), HalconCpp::HTuple(), &hvModelID);
			} else if (LOW_DM_TYPE == codeMode) {
				HalconCpp::CreateDataCode2dModel("Data Matrix ECC 200", "default_parameters", "enhanced_recognition", &hvModelID);
				HalconCpp::SetDataCode2dParam(hvModelID, "contrast_tolerance", "low");
			} else if (HIGH_DM_TYPE == codeMode) {
				HalconCpp::CreateDataCode2dModel("Data Matrix ECC 200", "default_parameters", "enhanced_recognition", &hvModelID);
				HalconCpp::SetDataCode2dParam(hvModelID, "contrast_tolerance", "high");
			}
		}

		//2. 识别条码
		HalconCpp::HTuple hvResultHandles, hvDataStrings;
		HalconCpp::FindDataCode2d(hObject, &hTarget, hvModelID, HalconCpp::HTuple(), HalconCpp::HTuple(), &hvResultHandles, &hvDataStrings);

		//3. 输出结果 
		HalconCpp::HTuple hvLength;
		hvLength = hvDataStrings.TupleLength();
		int iLength = hvLength[0].I();
		HalconCpp::HTuple hvY1, hvX1, hvY2, hvX2;
		if (0 == iLength) {
			HalconCpp::GenEmptyObj(&hTarget);
			codeString = "";
		} else {
			HalconCpp::GenRegionContourXld(hTarget, &hTarget, "filled");
			HalconCpp::SmallestRectangle1(hTarget, &hvY1, &hvX1, &hvY2, &hvX2);

			double xCenter = 0.5 * (hvX1[0].I() + hvX2[0].I());
			double yCenter = 0.5 * (hvY1[0].I() + hvY2[0].I());

			region.pt0.x = xCenter + 2 * (hvX1[0].I() - xCenter);
			region.pt0.y = yCenter + 2 * (hvY1[0].I() - yCenter);
			region.pt1.x = xCenter + 2 * (hvX2[0].I() - xCenter);
			region.pt1.y = yCenter + 2 * (hvY2[0].I() - yCenter);

			codeString = hvDataStrings[0].S();
		}

		//4.释放模板
		HalconCpp::ClearDataCode2dModel(hvModelID);
	}
	catch (HalconCpp::HException&) {
		HalconCpp::GenEmptyObj(&hTarget);
		codeString = "";
	}
	catch (const std::exception&) {
		HalconCpp::GenEmptyObj(&hTarget);
		codeString = "";
	}
}

void CreateNccModelApi(HalconCpp::HObject& hObject, double angleLimit, int& idResult)
{
	/* code */
	idResult = -1;
	try {
		double angle = abs(angleLimit);
		if (angle > 90.0f)  angle = 90.0f;

		double angleStart = 0.0f;
		double angleRange = 0.0f;
		angleRange = PI * angle / 180.0f;
		angleStart = -0.5 * angleRange;

		HalconCpp::HTuple hvModelID;
		HalconCpp::CreateNccModel(hObject, "auto", angleStart, angleRange, "auto", "use_polarity", &hvModelID);

		idResult = hvModelID[0].I();
	}
	catch (HalconCpp::HException&) {
		idResult = -1;
	}
	catch (const std::exception&) {
		idResult = -1;
	}
}

void FindNccModelApi(HalconCpp::HObject& hObject, int idModel, double minScore, double& xResult, double& yResult, double& angleResult, double& scoreResult)
{
	/* code */
	xResult = 0.0f;
	yResult = 0.0f;
	angleResult = 0.0f;
	scoreResult = 0.0f;
	try {
		HalconCpp::HTuple hvLevel, hvAngleStart, hvAngleRange, hvAngleStep, hvMetric;
		HalconCpp::GetNccModelParams(idModel, &hvLevel, &hvAngleStart, &hvAngleRange, &hvAngleStep, &hvMetric);

		HalconCpp::HTuple hvRow, hvColumn, hvAngle, hvScore;
		HalconCpp::FindNccModel(hObject, idModel, hvAngleStart, hvAngleRange, minScore, 1, 0.5f, "false", hvMetric, &hvRow, &hvColumn, &hvAngle, &hvScore);

		if (hvScore.TupleLength() > 0)
		{
			xResult = hvColumn[0].D();
			yResult = hvRow[0].D();
			angleResult = 180.0f * hvAngle[0].D() / PI;
			scoreResult = hvScore[0].D();
		}
	}
	catch (HalconCpp::HException&) {
	}
	catch (const std::exception&) {
	}
}

void ClearNccModelApi(int idModel)
{
	/* code */
	try {
		HalconCpp::ClearNccModel(idModel);
	}
	catch (HalconCpp::HException&) {
	}
	catch (const std::exception&) {
	}
}