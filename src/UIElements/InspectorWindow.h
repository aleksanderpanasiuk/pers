#ifndef INSPECTOR_WINDOW_H
#define INSPECTOR_WINDOW_H

#include "Window.h"

class InspectorWindow : public Window
{
public:
	void Display(Object& SelectedObject);

private:
	void DisplayObjectInfo(Object& SelectedObject);
	std::string formatObjectInfo(Object& SelectedObject);

	void DisplayObjectPosition(Object& SelectedObject);
	void DisplayObjectOrientation(Object& SelectedObject);
	void DisplayObjectScale(Object& SelectedObject);
	void DisplayObjectColor(Object& SelectedObject);
	void DisplayObjectForcesCheckBox(Object& SelectedObject);
	void DisplayObjectVisibilityCheckBox(Object& SelectedObject);
};


#endif // !INSPECTOR_WINDOW_H

