#include "StdAfx.h"
#include "GUIUtil.h"
#include "glui.h"

void updatecb(int num){
    //ƒRƒ“ƒgƒ[ƒ‹‚Ìid‚ª‚©‚¦‚é
}

GUIUtil::GUIUtil(void):cb(new GLUI_CB(updatecb)),count(0)
{
    glui=GLUI_Master.create_glui("cont");
    
}
GLUI_Rotation* GUIUtil::addRot(float* rotate)
{
    count++;
    return glui->add_rotation("",rotate,count,*cb);
}

void sync(GLUI* glui){
    glui->sync_live();
}
void gluiCallBack(int num){
  exit(0);
}
GUIUtil::~GUIUtil(void)
{
    delete glui;
}
