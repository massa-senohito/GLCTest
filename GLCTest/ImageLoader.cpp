
#include "StdAfx.h"
#include "ImageLoader.hpp"
#include "TypeUtil.h"
#include <map>
#include <algorithm>
#include <functional>
namespace ShaderUtil{
  void Load(GLchar* file){
  }
}
//namespace Asset{
struct TextAtras{
    //Types::str Tex;
    Types::Vec2 Atras;
    Types::Vec2 Size;
};
class TextureMap{
    //={Offset:Cordinate;Map:Cordinate list}
    Types::Vec2 Offset;
    
public:
    TextAtras& Query (Types::str str);
    const std::map<Types::str,TextAtras*> Map;
};
/*
TextAtras& TextureMap::Query(Types::str str){
    //std::bind2nd(std::mem_fun1_t(&TextureMap::finder),str)
    //const std::map<Types::str,TextAtras*> atlas=Map[str]; //.at(str);
    //if(atlas==map.Map.end()) std::cerr<< "cant find atlas: " << str <<std::endl;
    return atlas;
}
*/
ImageLoader::ImageLoader(void)
{
    FILE* fp;
    fopen_s(&fp,"Shader\\phone.vertex","r");
    GLchar buf[1024];
    while(fp!=nullptr)
      fread(buf,sizeof(GLchar),10,fp);
    ShaderUtil::Load(buf);
    fclose(fp);
}


ImageLoader::~ImageLoader(void)
{
}
//}