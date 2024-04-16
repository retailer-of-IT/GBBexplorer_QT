#include "EntityFunc.h"

EntityFunc::EntityFunc(QWidget *parent)
{

}

void SetStringFromPtr(const char* CurrentIntPtr, std::string& StringName)
{
	StringName.clear();
	char temp;
	while (true)
	{
		temp = static_cast<char>(*(CurrentIntPtr + CurrentPos));
		if (temp != '\0')
		{
			StringName += temp;
			++CurrentPos;
		}
		else
		{
			++CurrentPos;
			break;
		}
	}
}

EntityFunc::~EntityFunc()
{
}
