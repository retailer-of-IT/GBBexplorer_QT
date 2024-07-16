#pragma once

#include <QObject>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <exception>
#include <qvariant.h>
#include <qstring.h>
#include <qdatetime.h>

class Utils : public QObject
{
	Q_OBJECT

public:
	Utils();
	~Utils();

public :
	enum CoordinateType { Longitude, Latitude };
private:
	static double NM_TO_METERS;
	static double METERS_TO_NM;
	static double YARD_TO_METER;
	static double METERS_TO_YARDS;
	static double FEET_TO_METERS;
	static double METERS_TO_FEET;
	static double KNOTS_TO_METERS_PER_SEC;
	static double METERS_PER_SEC_TO_KNOTS;
	static double METERS_PER_SEC_TO_KM_PER_HOUR;
	static double KNOTS_TO_METERS_PER_HOUR;
	static double KM_PER_HOUR_TO_METERS_PER_SEC;
	static double PI;
	static double RADIANS_TO_DEGREES;
	static double DEGREES_TO_RADIANS;
	static char pad; // Create padding character, using to insert 0 when necessary 
	static double deg, min, sec; // Using to DMS convertion
	static std::string sSec, dms;
	static QDateTime UTCTime; // Use for field from the type "Time"

public:

	static QVariant GetSpeed(double Data, int DisplatState, int DecimalPlaces);
	static QVariant ConvertToLatLongRequire(double Data, int requireState, CoordinateType Type, int DecimalPlaces);
	static double ConvertFromMStoKph(double Data);
	static double ConvertFromMStoknot(double Data);
	static double ConvertFromMetersToKm(double Data);
	static double ConvertFromMetersToNM(double Data);
	static double ConvertFromMetersToYards(double Data);
	static double ConvertFromknotToKph(double Data);
	static double ConvertFromKphToMS(double Data);
	static double ConvertFromMeterToFt(double Data);
	static double ConvertFromFtToMeter(double Data);
	static double ConvertFromRadToDeg(double Data);
	static double ConvertFromDegToRad(double Data);
	static QString ConvertFromRadToDDMMSS(double Data, CoordinateType Type);
	static QString ConvertFromRadToDDMM(double Data, CoordinateType Type, int DecimalPlaces);
	static QString ConvertFromDegToDDMMSS(double Data, CoordinateType Type);
	static QString ConvertFromDegToDDMM(double Data, CoordinateType Type, int DecimalPlaces);
	static QString ConvertFromBooleanValue(std::string Data, int DisplayState);
	static QVariant ConvertToDateTime(qint64 Time, int State);//c#ÖÐÊÇlong
	static double ConvertToRequireRange(double Data, int DisplatState, int DecimalPlaces);

};

