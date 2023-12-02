#ifndef OBJECT_LIST_WINDOW
#define OBJECT_LIST_WINDOW

#include "Window.h"
#include "../Objects/Object.h"


class ObjectListWindow : public Window
{
public:
	void Display(unsigned int& Selectedobject, std::vector<Object> &Objects);
};

#endif // !OBJECT_LIST_WINDOW
