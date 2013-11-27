
#include "StdAfx.h"
#include "ImageLoader.hpp"
//namespace ShaderUtil{
  void Load(GLchar* file){
  }
//}
//namespace Asset{

ImageLoader::ImageLoader(void)
{
    FILE* fp;
    fopen_s(&fp,"Shader\\phone.vertex","r");
    GLchar buf[1024];
    while(fp!=nullptr)
      fread(buf,sizeof(GLchar),10,fp);
    ::Load(buf);
    fclose(fp);
}


ImageLoader::~ImageLoader(void)
{
}
//}