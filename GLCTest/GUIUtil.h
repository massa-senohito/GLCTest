#pragma once
#include "glui.h"
class GUIUtil
{
    GLUI *glui;
    GLUI_CB *cb;
    int count;
public:
    GUIUtil(void);
    ~GUIUtil(void);
    GLUI_Rotation* addRot(float*);
};

