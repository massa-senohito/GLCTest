#pragma once
//#include "Loadpng" http://lodev.org/lodepng/
//http://www21.atwiki.jp/opengl/?cmd=word&word=png&type=normal&page=PNG%E7%94%BB%E5%83%8F%E3%81%AE%E4%B8%80%E9%83%A8%E3%82%92%E3%82%B9%E3%83%88%E3%83%AC%E3%83%83%E3%83%81%E6%8F%8F%E7%94%BB%E3%81%99%E3%82%8B%28LodePNG%29
class ImageLoader
{
    //bitmap font generatorで作られたビットマップを読み出す
    void loadFont();
    //
    //glutBitmapStringなどで描画する
    void loadBitMap();
public:
    ImageLoader(void);
    ~ImageLoader(void);
};

