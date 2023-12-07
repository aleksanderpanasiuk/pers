#ifndef OBJECT_LIST_WINDOW_CLASS_H
#define OBJECT_LIST_WINDOW_CLASS_H

#include "Window.h"


class ObjectListWindow : public Window
{
public:
	void Display(unsigned int& SelectedObjectID, std::vector<Object> &Objects);
};

#endif // !OBJECT_LIST_WINDOW_CLASS_H
