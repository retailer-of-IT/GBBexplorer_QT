#include "DynamicData.h"
#include "detail.h"
#include "qdebug.h"

//DynamicData::DynamicData()
//{
//}

DynamicData::DynamicData()
{

	QFile configFile(ConfigPath);
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

void DynamicData::GetEntitiesIDs(int eEntityType){
	if (theMonitorManager.GetEntitiesIDs(eEntityType)) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfBuffer = *(int*)(ptr1); ptr1 += sizeof(int);//buffer长度

		//将此周期内的entity_id全部压入,-1表示结尾
		int Id = *(int*)(ptr1); ptr1 += sizeof(int);
		while (Id != -1) {
			EntitiesId.push_back(Id);
			Id = *(int*)(ptr1); ptr1 += sizeof(int);
		}
		//qDebug() << "hello";
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


void DynamicData::GetEntityDynamicData(id_t eEntityType, QVector<std::pair<int, std::string>> items, detail*& EntityGridView)
{
	m_nCurrentPos = 0;
	for each(StaticData::M_EntityInfo vecInfo in staticdata.vecEntityInfo)
	{
		if (vecInfo.EnumType == eEntityType)
		{
			//为每个描述符在分配的空间中占位，以enumtype作为标志，-1作为结束
			for each(auto var in items){
				//*(int*)(m_descriptorPtr + m_nCurrentPos) = staticdata.vecDescriptorsInfo[i].EnumType;
				*(int*)(m_descriptorPtr + m_nCurrentPos) = var.first;
				m_nCurrentPos += sizeof(int);
				for each(StaticData::M_DescriptorsInfo desInfo in staticdata.vecDescriptorsInfoInGBBEx)				{
					if (desInfo.EnumType == var.first){
						for each(StaticData::M_StructuresInfo structInfo in staticdata.vecStructuresInfo){
							if (structInfo.StructureName == desInfo.StructureName)
							{
								for each(StaticData::M_FieldInfo fieldInfo in structInfo.vecField)
								{
									FieldsList.push_back(fieldInfo);
									//if (fieldInfo.NestedName.empty())
									//{
									//	FieldsList.push_back(fieldInfo);
									//}
									//else {
									//	for each(StaticData::M_StructuresInfo structInfo2 in staticdata.vecStructuresInfo) {
									//		if (structInfo2.StructureName == fieldInfo.NestedName) {
									//			for each(StaticData::M_FieldInfo fieldInfo2 in structInfo2.vecField) {
									//				FieldsList.push_back(fieldInfo2);
									//			}
									//		}
									//	}
									//}
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
	QTableWidget* table = qobject_cast<QTableWidget*>(EntityGridView->findChild<QTableWidget*>("tableWidget"));
	if (table)
		qDebug() << "get table";
	//设置tablewiget中的单元格个数，行列
	int rowCount = EntitiesId.size();
	int columnCount = FieldsList.size() + 1;
	table->setRowCount(rowCount);
	table->setColumnCount(columnCount);
	//先用Met_id填充行
	for (int i = 0; i < rowCount; i++)	{
		QTableWidgetItem* item = new QTableWidgetItem();
		item->setData(Qt::DisplayRole, EntitiesId[i]);
		table->setItem(i, 0, item);
	}

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
			//EntityGridView = new detail();
			//QTableWidget* table;
			////用于读取对应id的所有field的值（一行）并进行切分，非数组array结构
			////传入表格视图,iscomparetab先预设为true
			bool flag = ReadRowFromIntPtr(ptr1, table, i, FieldsList, false, true, false, bufferLength);
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

void DynamicData::GetMessageWithAckTableData(enum_t eMessageType, detailMessage* MessageGridView, HT::HT_TIME & requireTime)
{
	m_nCurrentPos = 0;
	QTableWidget* table = qobject_cast<QTableWidget*>(MessageGridView->findChild<QTableWidget*>("tableWidget"));
	//table->setRowCount(100);
	//table->setColumnCount(200);
	StaticData::M_MessageInfo m_cCurrentMessage;//获取当前的消息对象
	for each(StaticData::M_MessageInfo msgInfo in staticdata.vecMessageInfoInGBBEx)
	{
		if (msgInfo.EnumType == eMessageType)
		{
			m_cCurrentMessage = msgInfo;
		}
	}
	//压入对应message的所有field
	//理论上还要压入enumtype为Creation Time的，如果是bIsDescAsMessage，还应有MET_ID,这里没有压入，在读取buffer时单独处理
	for each(StaticData::M_DescriptorsInfo desInfo in staticdata.vecDescriptorsInfo)
	{
		if (desInfo.DescriptorName == m_cCurrentMessage.DescriptorName)
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
	if (theMonitorManager.GetMessageDynamicData(eMessageType, requireTime)) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		//对应的DataBufferPtr
		char* ptr1 = ptr;
		int bufferLength = *(int*)(ptr1); ptr1 += sizeof(int);//buffer长度
		// (2)
		int NumberOfNewMessage = *(int*)(ptr1); ptr1 += sizeof(int);//Message数量
		if (NumberOfNewMessage > 0)
		{
			//设置行列
			table->setRowCount(NumberOfNewMessage);
			int columnCount = m_cCurrentMessage.m_bIsDescAsMessage ? FieldsList.size() + 2 : FieldsList.size() + 1;//列数，如果是描述符消息，会多2列MET_ID和creation time；如果不是，只增加一列creation time
			table->setColumnCount(columnCount);

			for (int i = 0; i < NumberOfNewMessage; ++i)
			{
				if (ReadAckRowFromIntPtr(ptr1, table, FieldsList, i, columnCount, bufferLength))
				{
				}
			}
		}
	}
	FieldsList.clear();
}

void DynamicData::GetMessageDynamicData(enum_t eMessageType, detailMessage*& MessageGridView, HT::HT_TIME & requireTime, QVector<CreationTime*> lst_LastCreationTime, int& NextCreationTimeIndex, bool WithAck)
{
	m_nCurrentPos = 0;
	QTableWidget* table = qobject_cast<QTableWidget*>(MessageGridView->findChild<QTableWidget*>("tableWidget"));
	table->setRowCount(100);
	table->setColumnCount(200);
	int n = GetMessageCount(eMessageType);
	StaticData::M_MessageInfo m_cCurrentMessage;//获取当前的消息对象
	for each(StaticData::M_MessageInfo msgInfo in staticdata.vecMessageInfoInGBBEx)
	{
		if (msgInfo.EnumType == eMessageType)
		{
			m_cCurrentMessage = msgInfo;
		}
	}
	//压入对应message的所有field
	for each(StaticData::M_DescriptorsInfo desInfo in staticdata.vecDescriptorsInfo)
	{
		if (desInfo.DescriptorName == m_cCurrentMessage.DescriptorName)
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
	// (1)
	if (theMonitorManager.GetMessageDynamicData(eMessageType, requireTime)) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		//对应的DataBufferPtr
		char* ptr1 = ptr;
		int bufferLength = *(int*)(ptr1); ptr1 += sizeof(int);//buffer长度

		// (2)
		int NumberOfNewMessage = *(int*)(ptr1); ptr1 += sizeof(int);//Message数量，和n应该是相等的
		if (NumberOfNewMessage > 0)
		{
			// Change all the previous messages BackColor to be "control" color 
			for (int j = 0; j < table->rowCount(); ++j)
			{
				QTableWidgetItem* item = table->item(j, 0);
				item->setBackground(QColor(255, 255, 255));
			}

			// Read the message fields
			for (int i = 0; i < NumberOfNewMessage; ++i)
			{
				if (table->rowCount() < m_cCurrentMessage.MaxMessageNum)
				{
					int rowPosition = table->rowCount();
					// Create new row
					table->insertRow(rowPosition);//插入一个新行
					//CreationTime timeRow(rowPosition);
					lst_LastCreationTime.push_back(new CreationTime(rowPosition));

					// Create all the ArrayDialogs for the new row TODO
					//CurrentMessageView.CreateNewArrayDialog();
					QMap<int, CArrayDetail *> ArrayDetailMap;
					bool flag = ReadRowFromIntPtr(ptr1, table, table->rowCount() - 1, FieldsList, false, false, WithAck, bufferLength);
					if (flag)
					{
						lst_LastCreationTime[table->rowCount() - 1]->TheCreationTime = table->item(table->rowCount() - 1, 0)->data(Tag).toLongLong();//注意qt中的table获取单元格是[row,column],c#中是先列后行
						table->item(table->rowCount() - 1, 0)->setBackground(QColor(82, 82, 82));
						if (m_cCurrentMessage.m_bWithAck)
						{
							bool ok;
							if ((table->item(table->rowCount() - 1, table->columnCount() - 1)->data(Tag).isNull())
								&& ((table->item(table->rowCount() - 1, table->columnCount() - 1)->data(Tag)).toInt(&ok) == 1000))
							{
								QString sUUID = (table->item(table->rowCount() - 1, table->columnCount() - 2)->data(Qt::DisplayRole)).toString();
								//判断这uuid是否存在
								if (!m_disAllAckWaitingRows.contains(sUUID))
								{
									m_disAllAckWaitingRows.insert(sUUID, table->item(table->rowCount() - 1, 0));//改写
								}
							}
						}
					}
				}
				else
				{
					QMap<int, CArrayDetail *> ArrayDetailMap;
					bool flag2 = ReadRowFromIntPtr(ptr1, table, lst_LastCreationTime[NextCreationTimeIndex]->IndexInTable, FieldsList, false, false, false, bufferLength, ArrayDetailMap);
					if (flag2)
					{
						lst_LastCreationTime[NextCreationTimeIndex]->TheCreationTime = table->item(lst_LastCreationTime[NextCreationTimeIndex]->IndexInTable, 0)->data(Tag).toLongLong();//注意qt中的table获取单元格是[row,column],c#中是先列后行
						table->item(lst_LastCreationTime[NextCreationTimeIndex]->IndexInTable, 0)->setBackground(QColor(82, 82, 82));
						table->setRowHidden(lst_LastCreationTime[NextCreationTimeIndex]->IndexInTable, false);//设置行可见
						if (m_cCurrentMessage.m_bWithAck)
						{
							bool ok;
							if ((table->item(lst_LastCreationTime[NextCreationTimeIndex]->IndexInTable, table->columnCount() - 1)->data(Tag).isNull())
								&& ((table->item(lst_LastCreationTime[NextCreationTimeIndex]->IndexInTable, table->columnCount() - 1)->data(Tag)).toInt(&ok) == 1000))
							{
								m_disAllAckWaitingRows.insert(table->item(lst_LastCreationTime[NextCreationTimeIndex]->IndexInTable, table->columnCount() - 2)->data(Qt::DisplayRole).toString(), table->item(lst_LastCreationTime[NextCreationTimeIndex]->IndexInTable, 0));//改写
							}
						}
						if (NextCreationTimeIndex < (m_cCurrentMessage.MaxMessageNum - 1))
						{
							++NextCreationTimeIndex;
						}
						else
						{
							NextCreationTimeIndex = 0;
						}
					}
				}
			}
			// (2.2) Set new requireTime for the next update cycle
			if ((NextCreationTimeIndex - 1) >= 0) // if this is not the first message
			{
				requireTime = lst_LastCreationTime[NextCreationTimeIndex - 1]->TheCreationTime;
			}
			else
			{
				requireTime = lst_LastCreationTime[lst_LastCreationTime.size() - 1]->TheCreationTime;
			}
			requireTime += 1;
		}
		m_nCurrentPos = 0;
	}
	FieldsList.clear();
}



bool DynamicData::ReadRowFromIntPtr(char * ptr, QTableWidget*& tableWidget, int ElementIndex, QVector<StaticData::M_FieldInfo> FieldsList, bool IsThisCompareTab, bool isThisEntity, bool WithAckMessage, int bufferLength)
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
			else{
				int rowCount = tableWidget->rowCount(), columnCount = tableWidget->columnCount();
				QTableWidgetItem* item = new QTableWidgetItem();
				if (item){ //不为空
					tableWidget->setItem(RowIndex, ColumnIndex, item);
					if (!ShowArrayField(ptr, tableWidget, LoopIndex,ColumnIndex, RowIndex, FieldsList[LoopIndex], ArrayDetailMap, FieldsList, IsThisCompareTab, bufferLength))	{
						FinishReadRow(item, FieldsList, LoopIndex, ColumnIndex, RowIndex, IsThisCompareTab, false);
						return false;
					}
				}
				else{
					qDebug() << "invalid item";
				}
			}
		}
		else{ //The descriptor is not Init OR descriptor is not show
		}
		IncreaseLoopIndex(false, IsThisCompareTab, RowIndex, ColumnIndex, LoopIndex);
	}
	tableWidget->update();
	return true;
}

bool DynamicData::ReadAckRowFromIntPtr(char * ptr, QTableWidget*& tableWidget, QVector<StaticData::M_FieldInfo> FieldsList, int nRowIndex, int columnCount, int bufferLength)
{
	//特判,前两位
	int n = columnCount - FieldsList.size();
	if (n == 1)//不是消息描述符,只读Creation Time
	{
		StaticData::M_FieldInfo fieldInfo;
		fieldInfo.FieldType = StaticData::FieldType::Time;
		int n = tableWidget->rowCount();
		int m = tableWidget->columnCount();
		QTableWidgetItem* item = new QTableWidgetItem();
		tableWidget->setItem(nRowIndex, 0, item);
		bool flag = ReadFieldFromPtr(ptr, item, fieldInfo, bufferLength);
	}
	else //是消息描述符,读Creation Time 和MET_ID
	{
		StaticData::M_FieldInfo fieldInfo1;
		fieldInfo1.FieldType = StaticData::FieldType::Time;
		QTableWidgetItem* item = new QTableWidgetItem();
		tableWidget->setItem(nRowIndex, 0, item);
		bool flag = ReadFieldFromPtr(ptr, item, fieldInfo1, bufferLength);

		StaticData::M_FieldInfo fieldInfo2;
		fieldInfo1.FieldType = StaticData::FieldType::MET_ID;
		QTableWidgetItem* item1 = new QTableWidgetItem();
		tableWidget->setItem(nRowIndex, 1, item);
		bool flag2 = ReadFieldFromPtr(ptr, item1, fieldInfo2, bufferLength);
	}
	
	for (int nColumnIndex = 0; nColumnIndex <FieldsList.size(); ++nColumnIndex)
	{
		// Regular field
		if (FieldsList[nColumnIndex].FieldType != StaticData::FieldType::Array)
		{
			QTableWidgetItem* item = new QTableWidgetItem();
			tableWidget->setItem(nRowIndex, nColumnIndex + n, item);
			if (!ReadFieldFromPtr(ptr, item, FieldsList[nColumnIndex], bufferLength))
			{
				// In case trying to read from the buffer out of bound of the pointer
				return false;
			}
		}
		// Array Field
		else
		{
			// TODO
		}
	}
	return true;
}


bool DynamicData::ReadFieldFromPtr(char*& fieldPtr, QTableWidgetItem*& item, StaticData::M_FieldInfo currentField,int bufferLength)
{
	//char* fieldPtr = ptr;
	//const int Tag = Qt::DisplayRole + 1;//单元格tag
	switch (currentField.FieldType)
	{
	case StaticData::FieldType::Alt:
		if (m_nCurrentPos + 8 <= bufferLength)
		{
			m_dDoubleValue = *(double*)fieldPtr;
			item->setData(Tag, m_dDoubleValue);
			//源代码是从GBBExplorerConfig.xml读出小数点后保留的位数,这里先把值写死
			double val = Mathround(GetAltData(m_dDoubleValue, 1), 2);
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
			double val = Mathround(GetAzimuth(m_dDoubleValue, 1), 5);
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
			QString val = GetEnum2String(value, 1, currentField.NestedName);
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
			QVariant val = GetTime(value, 2);
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
		return ConvertIntToEnum2String(Data, NestedName);
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

QString DynamicData::ConvertIntToEnum2String(int Data, std::string NestedName)
{
	QString nestedNameQStr = QString::fromStdString(NestedName);
	if (staticdata.mapValueToEnumToStringIS.contains(nestedNameQStr)) {
		const auto& innerMap = staticdata.mapValueToEnumToStringIS[nestedNameQStr];
		if (innerMap.contains(Data)) {
			return innerMap[Data];
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

void DynamicData::SaveOriginalPositions(int RowIndex, int ColumnIndex, int LoopIndex) {
	m_tmpPos[0] = RowIndex;
	m_tmpPos[1] = ColumnIndex;
	m_tmpPos[2] = LoopIndex;
	m_tmpPos[3] = m_nCurrentPos;
}
void DynamicData::ReturnOriginalPositions(int &m_nCurrentPos, int &ColumnIndex, int &RowIndex, int &LoopIndex) {
	RowIndex = m_tmpPos[0];
	ColumnIndex = m_tmpPos[1];
	LoopIndex = m_tmpPos[2];
	m_nCurrentPos = m_tmpPos[3];
}
bool DynamicData::ShowArrayField(char *&ptr, QTableWidget* &tableWidget, int &LoopIndex, int &ColumnIndex, int &RowIndex, StaticData::M_FieldInfo CurrentField, QMap<int, CArrayDetail*> ArraysDic, QVector<StaticData::M_FieldInfo> FieldsList, bool IsThisCompareTab, int bLen) {
	int ALen = *(int*)ptr;
	QTableWidgetItem *item = new QTableWidgetItem(QString(ALen));
	tableWidget->setItem(RowIndex, ColumnIndex, item);
	if (ALen < 0)  return 0;
	if (CurrentField.NestedName.empty()) { //jian dan lei xing
										   //2.1
		if (ArraysDic.find(ColumnIndex + 1) == ArraysDic.end()) {  //? why is CI+1
			if (!AppendArrayElementsToCell(ALen, tableWidget, ColumnIndex, RowIndex, FieldsList, LoopIndex, IsThisCompareTab, ptr, bLen))
				return 0;
		}
		else {
			//2.2.1
			SaveOriginalPositions(RowIndex, ColumnIndex, LoopIndex);
			if (!AppendArrayElementsToCell(ALen, tableWidget, ColumnIndex, RowIndex, FieldsList, LoopIndex, IsThisCompareTab, ptr, bLen))
				return 0;
			ReturnOriginalPositions(m_nCurrentPos, ColumnIndex, RowIndex, LoopIndex);
			//2.2.2
			ReadArrayFromIntPtr(ALen, ptr, ArraysDic[ColumnIndex + 1]);
			IncreaseLoopIndex(true, IsThisCompareTab, RowIndex, ColumnIndex, LoopIndex);
		}
	}
	else {//3.1
		if (ArraysDic.find(ColumnIndex) == ArraysDic.end()) {  //? why is CI+1
			if (!PushPointerToEndArray(ptr, ALen, CurrentField.NestedName)) return 0;
		}
		//3.2
		else {
			if (!ReadArrayFromIntPtr(ALen, ptr, ArraysDic[ColumnIndex])) return 0;
		}
	}
	return 1;
}
//DONE
bool DynamicData::AppendArrayElementsToCell(int ALen, QTableWidget*& tableWidget, int &ColumnIndex, int &RowIndex, QVector<StaticData::M_FieldInfo> &FieldsList, int &LoopIndex, bool IsThisCompareTab, char *&ptr, int bLen) {
	IncreaseLoopIndex(1, IsThisCompareTab, RowIndex, ColumnIndex, LoopIndex);
	QTableWidgetItem *item = new QTableWidgetItem("");
	tableWidget->setItem(RowIndex, ColumnIndex, item);
	if (ALen > 0) {
		QTableWidgetItem *_item = new QTableWidgetItem();
		for (int i = 0; i < ALen - 1; i++) {
			if (ReadFieldFromPtr(ptr, _item, FieldsList[LoopIndex], bLen))
			{
				if (_item->data(0) != QVariant(""))
				{
					item->setData(0, item->data(0).toString() + _item->data(0).toString() + ", ");
				}
			}
			else {
				FinishReadRow(item, FieldsList, LoopIndex, ColumnIndex, RowIndex, IsThisCompareTab, true);
				return 0;
			}
		}
		//write the last element
		if (ReadFieldFromPtr(ptr, _item, FieldsList[LoopIndex], bLen))
		{
			if (_item->data(0) != QVariant(""))
			{
				item->setData(0, item->data(0).toString() + _item->data(0).toString());
			}
		}
		else
		{
			FinishReadRow(item, FieldsList, LoopIndex, ColumnIndex, RowIndex, IsThisCompareTab, true);
			return false;
		}
	}
	else //In case the array descriptor is Init but the number of the elements  is 0
	{
		item->setData(0, QVariant(""));
	}
	return 1;
}
//TODO
bool DynamicData::ReadArrayFromIntPtr(int ALen, char *&ptr, CArrayDetail *CurrentArrayDetail) {
	/*
	CurrentArrayDialog.ctl_DataTable.RowCount = NumElements;
	foreach(DataGridViewRow row in CurrentArrayDialog.ctl_DataTable.Rows)
		row.Cells[0].Value = row.Index;
	for (int RowIndex = 0; RowIndex < NumElements; ++RowIndex)
		if (!ReadRowFromIntPtr(ref AllTheTablePtr, ref CurrentArrayDialog.ctl_DataTable, null, RowIndex, CurrentArrayDialog.AllFields, false, false, false))
			return false;
	Sorting(CurrentArrayDialog.ctl_DataTable);
	CurrentArrayDialog.ctl_DataTable.ClearSelection();
	*/
	QTableWidget *table = CurrentArrayDetail->table_ptr();
	table->setRowCount(ALen);
	for (int i = 0; i < ALen; i++) {
		QTableWidgetItem *item = table->item(i, 0);
		if (item == Q_NULLPTR) {
			item = new QTableWidgetItem();
			table->setItem(i, 0, item);
		}
		item->setData(Qt::DisplayRole, i);
		QMap<int, CArrayDetail *> ArrayDetailMap;
		if (!ReadRowFromIntPtr(ptr, table, i, FieldsList, 0, 0, 0, -1, ArrayDetailMap)) {
			return 0;
		}
	}
	return 1;
}
//TODO
bool DynamicData::PushPointerToEndArray(char *ptr, int ALen, std::string StructureName) {
	/*	// Move to pointer to the end of array data (use when don't need to display the array data
        // NumberOfElements number of Elements in the array 
	Structure temp = m_cStaticData.GetStructureByName(StructureName);
	List<Field> StructureFields;
	if (temp != null){
		StructureFields = temp.AllFields;
		for (int i = 0; i < NumberOfElements; ++i){
			for (int j = 0; j < StructureFields.Count; ++j){
				if (StructureFields[j].m_eCurrentType != FieldType.Array)
					IncreasePointer(ref AllTheTablePtr, StructureFields[j]);
				else{
					int nNumberOfElenemts = Get32Bit(ref AllTheTablePtr);
					if (StructureFields[j].m_sNestedName == ""){
						++j;
						for (int k = 0; k < nNumberOfElenemts; ++k)	
							IncreasePointer(ref AllTheTablePtr, StructureFields[j]);
					}

				}
			}
		}
		if (m_nCurrentPos > m_nBufferLength)
			return false;
	}
	return true;
	*/
	StaticData::M_StructuresInfo structure_info;
	QVector<StaticData::M_StructuresInfo> structureV = staticdata.vecStructuresInfo;
	for (auto structurei : structureV) {
		if (structurei.StructureName == StructureName) {
			structure_info = structurei;
			break;
		}
	}
	if (structure_info.StructureName == "") return 0;
	QVector<StaticData::M_FieldInfo> fieldV = structure_info.vecField;
	for (int i = 0; i < ALen; i++) {
		for (int j = 0; j < fieldV.size(); j++) {
			if (fieldV[j].FieldType != StaticData::FieldType::Array)
				;//todo	IncreasePointer(ptr, fieldV[j].FieldType);
			else {
				int nLen = *(int*)ptr;	ptr += sizeof(int);
				if (fieldV[j].NestedName == ""){
					j++;
					for (int k = 0; k < nLen; k++) {
						;//todo	IncreasePointer(ptr, fieldV[j].FieldType);
					}
				}
			}
		}
		if (1)	// m_nCurrentPos > m_nBufferLength ,后者cpp中无定义
			return 0;
	}
	return 1;

}