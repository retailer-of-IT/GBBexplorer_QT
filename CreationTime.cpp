#include "CreationTime.h"

CreationTime::CreationTime(int indexInTable, QObject *parent)
	: QObject(parent), IndexInTable(indexInTable)
{
}

CreationTime::~CreationTime()
{
}

int CreationTime::indexInTable() const
{
	return IndexInTable;
}

void CreationTime::setIndexInTable(int indexInTable)
{
	IndexInTable = indexInTable;
}

HT::HT_TIME CreationTime::theCreationTime() const
{
	return TheCreationTime;
}

void CreationTime::setTheCreationTime(HT::HT_TIME theCreationTime)
{
	TheCreationTime = theCreationTime;
}

bool CreationTime::operator<(const CreationTime &other) const
{
	return TheCreationTime < other.TheCreationTime;
}