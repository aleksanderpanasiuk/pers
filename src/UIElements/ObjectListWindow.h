#ifndef OBJECT_LIST_WINDOW
#define OBJECT_LIST_WINDOW

#include "Window.h"
#include "../Objects/Object.h"


class ObjectListWindow : Window
{
public:
	void Display(std::vector<Object> &Objects);
};

#endif // !OBJECT_LIST_WINDOW
