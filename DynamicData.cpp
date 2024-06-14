#include "DynamicData.h"
#include "detail.h"
#include "qdebug.h"

//DynamicData::DynamicData()
//{
//}

DynamicData::DynamicData()
{
	QFile configFile(configPath);
	configFile.open(QIODevice::ReadOnly | QIODevice::Text);
	QDomDocument configDoc;
	if (!configDoc.setContent(&configFile)) {
		// 处理解析XML失败的情况
		configDoc.clear();
		configFile.close();
		return;
	}
	configFile.close();
	QDomElement gbbExplorerElement = configDoc.documentElement();
	QDomElement dataElement = gbbExplorerElement.firstChildElement("Data");
	QString descriptorBufferSizeStr = dataElement.firstChildElement("DescriptorBufferSize").text();
	m_descriptorBufferSize = descriptorBufferSizeStr.toInt();
	 
	// 分配内存
	m_descriptorPtr = static_cast<char*>(malloc(m_descriptorBufferSize));
	qDebug() << m_descriptorBufferSize;
}

int DynamicData::GetEntityCount(int eEntityType)
{
	if (theMonitorManager.GetEntityCount(eEntityType)) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfBuffer = *(int*)(ptr1); ptr1 += sizeof(int);
		int entityCount = *(int*)(ptr1);
		return entityCount;
	}
}

void DynamicData::GetEntitiesIDs(int eEntityType)
{
	if (theMonitorManager.GetEntitiesIDs(eEntityType)) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfBuffer = *(int*)(ptr1); ptr1 += sizeof(int);//buffer长度

															 //将此周期内的entity_id全部压入
		EntitiesId.push_back(*(int*)(ptr1)); ptr1 += sizeof(int);
		int n = GetEntityCount(eEntityType);
		for (int i = 1; i < n; i++) {
			EntitiesId.push_back(*(int*)(ptr1));
			ptr1 += sizeof(int);
		}
//		qDebug() << "hello";
	}
}

int DynamicData::GetEntityEnumType(long pEntityMet_ID)
{
	if (theMonitorManager.GetEntityEnumType(pEntityMet_ID)) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfBuffer = *(int*)(ptr1); ptr1 += sizeof(int);
		int enumType = *(int*)(ptr1);
		return enumType;
	}
}

int DynamicData::GetMessageCount(int eMessageType)
{
	if (theMonitorManager.GetMessageCount(eMessageType)) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfBuffer = *(int*)(ptr1); ptr1 += sizeof(int);//buffer长度
		int messageCount = *(int*)(ptr1);
		return messageCount;
	}
}

int DynamicData::GetDescriptorCount(int eDescriptorType)
{
	if (theMonitorManager.GetDescriptorCount(eDescriptorType)) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfBuffer = *(int*)(ptr1); ptr1 += sizeof(int);//buffer长度
		int descriptorCount = *(int*)(ptr1);
		return descriptorCount;
	}
}


void DynamicData::GetEntityDynamicData(int eEntityType, detail*& GridView)
{
	staticdata.InitEntities();
	staticdata.InitDescriptors();
	staticdata.InitStructures();
	staticdata.InitMessages();
	m_nCurrentPos = 0;
	for each(StaticData::M_EntityInfo vecInfo in staticdata.vecEntityInfo)
	{
		if (vecInfo.EnumType == eEntityType)
		{
			//为每个描述符在分配的空间中占位，以enumtype作为标志，-1作为结束
			for (const auto& key : vecInfo.mapDescriptores.keys()) {
				//*(int*)(m_descriptorPtr + m_nCurrentPos) = staticdata.vecDescriptorsInfo[i].EnumType;
				*(int*)(m_descriptorPtr + m_nCurrentPos) = key;
				m_nCurrentPos += sizeof(int);
				for each(StaticData::M_DescriptorsInfo desInfo in staticdata.vecDescriptorsInfoInGBBEx)
				{
					if (desInfo.EnumType == key)
					{
						for each(StaticData::M_StructuresInfo structInfo in staticdata.vecStructuresInfo)
						{
							if (structInfo.StructureName == desInfo.StructureName)
							{
								for each(StaticData::M_FieldInfo fieldInfo in structInfo.vecField)
								{
									FieldsList.push_back(fieldInfo);
								}
							}
						}
					}
				}
			}
			*(int*)(m_descriptorPtr + m_nCurrentPos) = -1;
		}
	}
	//staticdata.InitDescriptors();
	//int num = staticdata.vecDescriptorsInfo.size();
	//int m_nCurrentPos = 0;
	////为每个描述符在分配的空间中占位，以enumtype
	//for (int i = 0; i < num; ++i) {
	//	*(int*)(m_descriptorPtr + m_nCurrentPos) = staticdata.vecDescriptorsInfo[i].EnumType;
	//	m_nCurrentPos += sizeof(int);
	//}
	//*(int*)(m_descriptorPtr + m_nCurrentPos) = -1;

	GetEntitiesIDs(eEntityType);//每个周期，获取对应id实体的所有metid
	int num2 = EntitiesId.size();
	QTableWidget* table = qobject_cast<QTableWidget*>(GridView->findChild<QTableWidget*>("tableWidget"));
	if (table)
		qDebug() << "get table";
	//设置tablewiget中的单元格个数，行列
	//table->setRowCount(100);
	//table->setColumnCount(200);
	for (int i = 0; i < num2; i++) {
		if (theMonitorManager.GetEntityDynamicData(EntitiesId[i], m_descriptorPtr)) {
			GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
			char* ptr = (char*)p->GetBuffer();
			//对应的DataBufferPtr
			char* ptr1 = ptr;
			int bufferLength = *(int*)(ptr1); ptr1 += sizeof(int);//buffer长度
			m_nCurrentPos = 0;
			//用于标识是开头的描述符
			bool DescriptorInitialized = *(bool*)ptr1; ptr1 += sizeof(bool);
			//int met_id = *(int*)ptr1; ptr1 += sizeof(int);
			//std::string network_name;
			//ptr1 += SetStringFromPtr(ptr1, network_name);
			//std::string network_obj;
			//ptr1 += SetStringFromPtr(ptr1, network_obj);
			////TODO dynamicdata.cs中 GetEntityTableData等函数使用到的 ReadRowFromIntPtr函数功能
			//GridView = new detail();
			//QTableWidget* table;
			////用于读取对应id的所有field的值（一行）并进行切分，非数组array结构
			////传入表格视图,iscomparetab先预设为true
			bool flag = ReadRowFromIntPtr(ptr1, table, i, FieldsList, false, true, bufferLength);
			//qDebug() << "hello";
		}
	}
	table->show();
	m_nCurrentPos = 0;
	//每次获取后清空vector
	FieldsList.clear();
	EntitiesId.clear();
	//qDebug() << "hello";
}

bool DynamicData::ReadRowFromIntPtr(char * ptr, QTableWidget*& tableWidget, int ElementIndex, QVector<StaticData::M_FieldInfo> FieldsList, bool IsThisCompareTab, bool isThisEntity, int bufferLength)
{
	int RowIndex = 0, ColumnIndex = 0, LoopIndex = 0;
	bool DescriptorInitialized = false;
	SetElementIndex(IsThisCompareTab, ElementIndex, RowIndex, ColumnIndex, LoopIndex);
	if (IsThisCompareTab)
	{
		++ColumnIndex;
	}
	//都加1，第一行和第一列都不是数据
	RowIndex;
	++ColumnIndex;
	//循环，读取一整行field的数据
	for (LoopIndex = 0; LoopIndex < FieldsList.size(); ++LoopIndex)
	{
		if (isThisEntity)
		{
			DescriptorInitialized = true;

		}
		// In case the (descriptor is Init AND DescriptorShow) OR (this is message)
		if (DescriptorInitialized || !isThisEntity)
		{
			//普通的field(非数组array)
			if (FieldsList[LoopIndex].FieldType != StaticData::FieldType::Array)
			{
				int rowCount = tableWidget->rowCount();
				int columnCount = tableWidget->columnCount();
				//QTableWidgetItem* item = tableWidget->item(RowIndex, ColumnIndex);//获取单元格
				QTableWidgetItem* item = new QTableWidgetItem();
				if (item)//不为空
				{
					tableWidget->setItem(RowIndex, ColumnIndex, item);
					if (!ReadFieldFromPtr(ptr, item, FieldsList[LoopIndex], bufferLength))
					{
						FinishReadRow(item, FieldsList, LoopIndex, ColumnIndex, RowIndex, IsThisCompareTab, false);
						//tableWidget->update();
						return false;
						//tableWidget->setItem(RowIndex, ColumnIndex, item);
					}
				}
				else
				{
					qDebug() << "invalid item";
				}
			}
			//array类型，单独展示
			else
			{
				//
			}
		}
		else //The descriptor is not Init OR descriptor is not show
		{
			
		}
		IncreaseLoopIndex(false, IsThisCompareTab, RowIndex, ColumnIndex, LoopIndex);
	}
	tableWidget->update();
	return true;
}


bool DynamicData::ReadFieldFromPtr(char*& fieldPtr, QTableWidgetItem*& item, StaticData::M_FieldInfo currentField,int bufferLength)
{
	//char* fieldPtr = ptr;
	const int Tag = Qt::DisplayRole + 1;//单元格tag
	switch (currentField.FieldType)
	{
	case StaticData::FieldType::Alt:
		if (m_nCurrentPos + 8 <= bufferLength)
		{
			m_dDoubleValue = *(double*)fieldPtr;
			item->setData(Tag, m_dDoubleValue);
			//源代码是从GBBExplorerConfig.xml读出小数点后保留的位数,这里先把值写死
			double val = Mathround(GetAltData(m_dDoubleValue, 0), 2);
			item->setData(Qt::DisplayRole, val);
			fieldPtr += 8;
			m_nCurrentPos += 8;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Azimuth:
		if (m_nCurrentPos + 8 <= bufferLength)
		{
			m_dDoubleValue = *(double*)fieldPtr;
			item->setData(Tag, m_dDoubleValue);
			//源代码是从GBBExplorerConfig.xml读出小数点后保留的位数
			double val = Mathround(GetAzimuth(m_dDoubleValue, 0), 5);
			item->setData(Qt::DisplayRole, val);
			fieldPtr += 8;
			m_nCurrentPos += 8;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Boolean:
		if (m_nCurrentPos + 1 <= bufferLength)
		{
			//bool a = *(bool*)(fieldPtr + m_nCurrentPos);
			//m_nCurrentPos += 1;
			bool value = *(bool*)fieldPtr;
			QString val = GetBoolean(std::to_string(value), 1);//to_string会转换成“0”/“1”
			item->setData(Qt::DisplayRole, val);
			fieldPtr += 1;
			m_nCurrentPos += 1;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Char:
		if (m_nCurrentPos + 1 <= bufferLength)
		{
			char val = *(char*)fieldPtr;
			item->setData(Qt::DisplayRole, val);
			fieldPtr += 1;
			m_nCurrentPos += 1;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Double:
		if (m_nCurrentPos + 8 <= bufferLength)
		{
			m_dDoubleValue = *(double*)fieldPtr;
			double val = Mathround(m_dDoubleValue, 3);
			item->setData(Qt::DisplayRole, val);
			fieldPtr += 8;
			m_nCurrentPos += 8;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Enum2String:
		if (m_nCurrentPos + 4 <= bufferLength)
		{
			int value = *(int*)fieldPtr;
			item->setData(Tag, value);
			QString val = GetEnum2String(value, 0, currentField.NestedName);
			item->setData(Qt::DisplayRole, val);
			fieldPtr += 4;
			m_nCurrentPos += 4;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Integer:
		if (m_nCurrentPos + 4 <= bufferLength)
		{
			int val = *(int*)(fieldPtr);
			item->setData(Qt::DisplayRole, val);
			fieldPtr += 4;
			m_nCurrentPos += 4;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Latitude:
		if (m_nCurrentPos + 8 <= bufferLength)
		{
			m_dDoubleValue = *(double*)fieldPtr;
			item->setData(Tag, m_dDoubleValue);
			QVariant val = GetLatLong(m_dDoubleValue, 1, Utils::Latitude);
			item->setData(Qt::DisplayRole, val);
			fieldPtr += 8;
			m_nCurrentPos += 8;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Longitude:
		if (m_nCurrentPos + 8 <= bufferLength)
		{
			m_dDoubleValue = *(double*)fieldPtr;
			item->setData(Tag, m_dDoubleValue);
			QVariant val = GetLatLong(m_dDoubleValue, 1, Utils::Longitude);
			item->setData(Qt::DisplayRole, val);
			fieldPtr += 8;
			m_nCurrentPos += 8;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Long:
		if (m_nCurrentPos + 4 <= bufferLength)
		{
			long val = *(long*)(fieldPtr);
			item->setData(Qt::DisplayRole, val);
			fieldPtr += 4;
			m_nCurrentPos += 4;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::LongLong:
		if (m_nCurrentPos + 8 <= bufferLength)
		{
			long long val = *(long long*)(fieldPtr);
			item->setData(Qt::DisplayRole, val);
			fieldPtr += 8;
			m_nCurrentPos += 8;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::MET_ID:
		if (m_nCurrentPos + 4 <= bufferLength)
		{
			int val = *(int*)(fieldPtr);
			item->setData(Qt::DisplayRole, val);
			fieldPtr += 4;
			m_nCurrentPos += 4;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Reference:
		if (m_nCurrentPos + 4 <= bufferLength)
		{
			int val = *(int*)(fieldPtr);
			item->setData(Qt::DisplayRole, val);
			fieldPtr += 4;
			m_nCurrentPos += 4;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Short:
		if (m_nCurrentPos + 2 <= bufferLength)
		{
			short val = *(short*)(fieldPtr);
			item->setData(Qt::DisplayRole, val);
			fieldPtr += 2;
			m_nCurrentPos += 2;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Speed:
		if (m_nCurrentPos + 1 <= bufferLength)
		{
			m_dSpeedValue = *(double*)fieldPtr;
			item->setData(Tag, m_dSpeedValue);
			QVariant val = GetSpeed(m_dSpeedValue, 1);
			item->setData(Qt::DisplayRole, val);
			fieldPtr += 8;
			m_nCurrentPos += 8;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::String:
		if (m_nCurrentPos + 1 <= bufferLength)
		{
			std::string s;
			int n = SetStringFromPtr(fieldPtr, s);
			fieldPtr += n;
			m_nCurrentPos += n;
			QString val = QString::fromStdString(s);
			item->setData(Qt::DisplayRole, val);
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Time:
		if (m_nCurrentPos + 8 <= bufferLength)
		{
			long long value = *(long long*)(fieldPtr);
			item->setData(Tag, value);
			QVariant val = GetTime(value, 1);
			item->setData(Qt::DisplayRole, val);
			fieldPtr += 8;
			m_nCurrentPos += 8;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Range:
		if (m_nCurrentPos + 8 <= bufferLength)
		{
			m_dDoubleValue = *(double*)fieldPtr;
			item->setData(Tag, m_dDoubleValue);
			double val = GetRange(m_dDoubleValue, 1, 3);
			item->setData(Qt::DisplayRole, val);
			fieldPtr += 8;
			m_nCurrentPos += 8;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Default:
		break;
	default:
		break;
	}
	return true;
}

void DynamicData::FinishReadRow(QTableWidgetItem *& item, QVector<StaticData::M_FieldInfo> FieldsList, int LoopIndex, int ColumnIndex, int RowIndex, bool IsThisCompareTab, bool AlsoLoop)
{
	for (int j = LoopIndex; j < FieldsList.size(); ++j)
	{
		//item[ColumnIndex, RowIndex].setBackground(QColor(255, 0, 0));//设置为红色
		IncreaseLoopIndex(AlsoLoop, IsThisCompareTab, RowIndex, ColumnIndex, LoopIndex);
	}
}

void DynamicData::SetElementIndex(bool IsThisCompareTab, int ElementIndex, int & RowIndex, int & ColumnIndex, int & LoopIndex)
{
	if (IsThisCompareTab)
	{
		ColumnIndex = ElementIndex;
	}
	else
	{
		RowIndex = ElementIndex;
	}
}

void DynamicData::IncreaseLoopIndex(bool AlsoLoopIndex, bool IsVertical, int & RowIndex, int & ColumnIndex, int & LoopIndex)
{
	if (IsVertical)
	{
		++RowIndex;
	}
	else
	{
		++ColumnIndex;
	}

	if (AlsoLoopIndex)
	{
		++LoopIndex;
	}
}

double DynamicData::GetAltData(double Data, int DisplayState) {
	if (DisplayState == 0) 
	{
		return Data;
	}
	return Utils::ConvertFromMeterToFt(Data);
}
double DynamicData::GetAzimuth(double Data, int DisplayState)
{
	if (DisplayState == 0)
	{
		return Data;
	}
	return Utils::ConvertFromRadToDeg(Data);
}

QString DynamicData::GetBoolean(std::string Data, int DisplatState)
{
	if (DisplatState != 0)
	{
		// Change from 0\1 to False\True
		return Utils::ConvertFromBooleanValue(Data, DisplatState);
	}
	return QString::fromStdString(Data);
}

QString DynamicData::GetEnum2String(int Data, int DislayState, std::string NestedName)
{
	if (DislayState != 0)
	{
		return QString::fromStdString(ConvertIntToEnum2String(Data, NestedName));
	}
	return QString::number(Data);
}

QVariant DynamicData::GetLatLong(double Data, int DisplayState, Utils::CoordinateType Type)
{
	return Utils::ConvertToLatLongRequire(Data, DisplayState, Type, 3);
}

QVariant DynamicData::GetSpeed(double Data, int DisplayState)
{
	return Utils::GetSpeed(Data, DisplayState, 3);
}

QVariant DynamicData::GetTime(long long Data, int DisplayState)
{
	return Utils::ConvertToDateTime(Data, DisplayState);
}

double DynamicData::GetRange(double Data, int DisplayState, int DecimalPlaces)
{
	return Utils::ConvertToRequireRange(Data, DisplayState, DecimalPlaces);
}


std::string DynamicData::GetString(char* currentPtr)
{
	std::string StringName = std::string(currentPtr);
	qDebug() << StringName.length();
	currentPtr += StringName.length() + 1;
	m_nCurrentPos += StringName.length() + 1;
	return StringName;
}

void DynamicData::getAfterString(char* currentPtr ,int bufferLength)
{
	int len = 0;
	if (!currentPtr || *currentPtr == '\0')
		return;

	while (*currentPtr != '\0')
	{
		++currentPtr;
		len++;
		if (*currentPtr == '\0' || len > bufferLength)
			return;
	}
}

std::string DynamicData::ConvertIntToEnum2String(int Data, std::string NestedName)
{
	auto it = staticdata.ValueToEnumToStringIS.find(NestedName);
	if (it != staticdata.ValueToEnumToStringIS.end()) {
		auto innerMap = it->second;
		auto innerIt = innerMap.find(Data);
		if (innerIt != innerMap.end()) {
			return innerIt->second;
		}
	}
	return "N/A";
}

int DynamicData::SetStringFromPtr(char* CurrentIntPtr, std::string &StringName)
{
	StringName = std::string(CurrentIntPtr);
	return StringName.length() + 1;
}

double DynamicData::Mathround(double Data, int DecimalPlaces)
{
	return std::round(Data * pow(10, DecimalPlaces)) / pow(10, DecimalPlaces);
}

DynamicData::~DynamicData()
{
}
