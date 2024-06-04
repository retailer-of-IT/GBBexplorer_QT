#include "Utils.h"

Utils::Utils()
{
}

//类外定义
double Utils::NM_TO_METERS = 1852.0;
double Utils::METERS_TO_NM = 1.0 / NM_TO_METERS;
double Utils::YARD_TO_METER = 0.9144000002824;
double Utils::METERS_TO_YARDS = 1.0 / YARD_TO_METER;
double Utils::FEET_TO_METERS = 0.3048000000012;
double Utils::METERS_TO_FEET = 1.0 / FEET_TO_METERS;
double Utils::KNOTS_TO_METERS_PER_SEC = 0.5144444;
double Utils::METERS_PER_SEC_TO_KNOTS = 1.0 / KNOTS_TO_METERS_PER_SEC;
double Utils::METERS_PER_SEC_TO_KM_PER_HOUR = 3600.0 / 1000.0;
double Utils::KNOTS_TO_METERS_PER_HOUR = 1.852;
double Utils::KM_PER_HOUR_TO_METERS_PER_SEC = 1000.0 / 3600.0;
double Utils::PI = 3.1415926535897932384626433832795;
double Utils::RADIANS_TO_DEGREES = 180.0 / PI;
double Utils::DEGREES_TO_RADIANS = PI / 180.0;
double Utils::deg, Utils::min, Utils::sec = 0.0;
std::string Utils::sSec, Utils::dms = "";
QDateTime Utils::UTCTime(QDateTime::currentDateTime());

QVariant Utils::GetSpeed(double Data, int DisplatState, int DecimalPlaces)
{
	switch (DisplatState)
	{
	case 1:// convert from m/s to kts
		return std::round(ConvertFromMStoknot(Data) * pow(10, DecimalPlaces)) / pow(10, DecimalPlaces);
	case 2:// convert from m/s to kph
		return std::round(ConvertFromMStoKph(Data) * pow(10, DecimalPlaces)) / pow(10, DecimalPlaces);
	default: // m/s
		return std::round(Data * pow(10, DecimalPlaces)) / pow(10, DecimalPlaces);
	}
}

QVariant Utils::ConvertToLatLongRequire(double Data, int requireState, CoordinateType Type, int DecimalPlaces)
{
	switch (requireState)
	{
	case 1:// return Deg
		return std::round(ConvertFromRadToDeg(Data) * pow(10, DecimalPlaces)) / pow(10, DecimalPlaces);
	case 2:// return DMS
		return ConvertFromRadToDDMMSS(Data, Type);
	case 3:// return DM
		return ConvertFromRadToDDMM(Data, Type, DecimalPlaces);
	default: // return Rad
		return std::round(Data * pow(10, DecimalPlaces)) / pow(10, DecimalPlaces);
	}
}

double Utils::ConvertFromMStoKph(double Data)
{
	return Data * METERS_PER_SEC_TO_KM_PER_HOUR;
}

double Utils::ConvertFromMStoknot(double Data)
{
	return Data * METERS_PER_SEC_TO_KNOTS;
}

double Utils::ConvertFromMetersToKm(double Data)
{
	return static_cast<double>(Data / 1000.0);
}

double Utils::ConvertFromMetersToNM(double Data)
{
	return Data * METERS_TO_NM;
}

double Utils::ConvertFromMetersToYards(double Data)
{
	return Data * METERS_TO_YARDS;
}

double Utils::ConvertFromknotToKph(double Data)
{
	return Data * KNOTS_TO_METERS_PER_HOUR;
}

double Utils::ConvertFromKphToMS(double Data)
{
	return Data * KM_PER_HOUR_TO_METERS_PER_SEC;
}

double Utils::ConvertFromMeterToFt(double Data)
{
	return Data * METERS_TO_FEET;
}

double Utils::ConvertFromFtToMeter(double Data)
{
	return Data * FEET_TO_METERS;
}

double Utils::ConvertFromRadToDeg(double Data)
{
	return Data * RADIANS_TO_DEGREES;
}

double Utils::ConvertFromDegToRad(double Data)
{
	return Data * DEGREES_TO_RADIANS;
}

QString Utils::ConvertFromRadToDDMMSS(double Data, CoordinateType Type)
{
	Data = ConvertFromRadToDeg(Data);
	return ConvertFromDegToDDMMSS(Data, Type);
}

QString Utils::ConvertFromRadToDDMM(double Data, CoordinateType Type, int DecimalPlaces)
{
	Data = ConvertFromRadToDeg(Data);
	return ConvertFromDegToDDMM(Data, Type, DecimalPlaces);
}

QString Utils::ConvertFromDegToDDMMSS(double Data, CoordinateType Type)
{
	std::string sLettter = "";
	switch (Type)
	{
	case CoordinateType::Longitude:
		sLettter = (Data < 0.0) ? " W" : " E";
		break;
	case CoordinateType::Latitude:
		sLettter = (Data < 0.0) ? " S" : " N";
		break;
	}

	// Work with a positive number
	Data = std::abs(Data);

	// Get d/m/s components
	deg = static_cast<int>(Data);
	Data -= deg;
	Data *= 60;
	min = static_cast<int>(Data);
	Data -= min;
	Data *= 60;
	sec = static_cast<int>(std::round(Data));

	// Append d/m/s
	char pad = '0';
	std::ostringstream oss;
	oss << std::setw(2) << std::setfill(pad) << deg << ""
		<< std::setw(2) << std::setfill(pad) << min << "'"
		<< std::setw(2) << std::setfill(pad) << sec << "\""
		<< sLettter;
	dms = oss.str();
	return QString::fromStdString(dms);
}

QString Utils::ConvertFromDegToDDMM(double Data, CoordinateType Type, int DecimalPlaces)
{
	std::string sLettter = "";
	switch (Type)
	{
	case CoordinateType::Longitude:
		sLettter = (Data < 0.0) ? " W" : " E";
		break;
	case CoordinateType::Latitude:
		sLettter = (Data < 0.0) ? " S" : " N";
		break;
	}

	// Work with a positive number
	Data = std::abs(Data);

	// Get d/m/s components
	deg = static_cast<int>(Data);
	Data -= deg;
	Data *= 60;
	min = static_cast<int>(Data);
	Data -= min;
	//保留特定位数
	double factor = pow(10, DecimalPlaces);
	sec = std::round(Data * factor) / factor;
	sSec = std::to_string(sec);
	if (sSec.length() > 2) 
	{
		sSec = sSec.substr(2); // C++中用substr来截取字符串
	}
	char pad = '0';
	std::ostringstream oss;
	oss << std::setw(2) << std::setfill(pad) << deg << ""
		<< std::setw(2) << std::setfill(pad) << min << "."
		<< sSec
		<< sLettter;
	dms = oss.str();
	return QString::fromStdString(dms);
}

QString Utils::ConvertFromBooleanValue(std::string Data, int DisplayState)
{
	switch (DisplayState)
	{
	case 0:
		if (Data == "False")
		{
			return "0";
		}
		return "1";
	case 1:
		if (Data == "0")
		{
			return "False";
		}
		return "True";
	default:
		return "Error";
	}
}

QVariant Utils::ConvertToDateTime(qint64 Time, int State)
{
	try {
		// 将时间戳转换为UTC的QDateTime
		UTCTime = QDateTime::fromMSecsSinceEpoch(Time + 504911232000000000, Qt::UTC);
	}
	catch (...) {
		return "Error";
	}
	// 根据状态码设置日期时间格式
	switch (State) 
	{
	case 0:
		return UTCTime.toString("MM/dd/yyyy HH:mm:ss.zzz");
	case 1:
		return UTCTime.toString("HH:mm:ss.zzz");
	case 2:
		return UTCTime.toString("MM/dd/yyyy");
	default:
		return QString::number(Time);
	}
}

double Utils::ConvertToRequireRange(double Data, int DisplatState, int DecimalPlaces)
{
	switch (DisplatState)
	{
	case 1:// convert from m to km
		return std::round(ConvertFromMetersToKm(Data) * pow(10, DecimalPlaces)) / pow(10, DecimalPlaces);
	case 2:// convert from m to yard
		return std::round(ConvertFromMetersToYards(Data) * pow(10, DecimalPlaces)) / pow(10, DecimalPlaces);
	case 3:// convert from m to NM
		return std::round(ConvertFromMetersToNM(Data) * pow(10, DecimalPlaces)) / pow(10, DecimalPlaces);
	default:
		return std::round(Data * pow(10, DecimalPlaces)) / pow(10, DecimalPlaces); // m
	}
}

Utils::~Utils()
{

}

