#pragma once
#include "TypeUtil.h"

#include "EffectStrategy.h"
#include "Cg\cg.h"
enum Shader{
  EffectObj,
  VertexObj,
  FragmentObj,
};
class CgUtil{
public:
    static CGcontext InitCg();
    
};
//http://tip.sakura.ne.jp/htm/gl_chp20frame.htm#c_1_0_0_0_0
//�|�X�g�G�t�F�N�g����ɂ́A��ʑS�̂Ƀe�N�X�`�����͂�΂���
void ForEachPath(Types::action,CGtechnique);
class CgLoader
{
    IShaderStrategy* _shader;//pimpl���Ȃɂ����g��Ȃ��Ə����Ȃ�
    bool _err;
public:
    CgLoader(Types::str,Shader);
    bool IsError();
    void BindEnable(Types::action);
    void SendTextureToFlagment(Types::str,int);
    ~CgLoader(void);
};

