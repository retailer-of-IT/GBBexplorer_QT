#ifndef CREATION_TIME_H
#define CREATION_TIME_H

#include <QObject>
#include "Inc\GeneralTypes.h"

//typedef long long HT_TIME;

class CreationTime : public QObject
{
	Q_OBJECT

public:
	explicit CreationTime(int indexInTable);
	~CreationTime();

	int indexInTable() const;
	void setIndexInTable(int indexInTable);

	HT::HT_TIME theCreationTime() const;
	void setTheCreationTime(HT::HT_TIME theCreationTime);

	bool operator<(const CreationTime &other) const;

public:
	int IndexInTable;
	HT::HT_TIME TheCreationTime;
};

#endif // CREATION_TIME_H