// GLCTest.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
// bulletが2010プロフィールでビルドしてるのでこれも2010で、他のライブラリも2010ビルドで

#include "stdafx.h"
#include "ExportDLL.h"
#include "GUIUtil.h"
#include "CgLoader.h"
#  pragma comment(lib, "glew32.lib")
extern "C"{
int _tmain(int argc, _TCHAR* argv[])
{
    
	return 0;
}

class WalkInfo
{
public:
        float HeadAngle;//カメラの回転（Ｙ軸中心）
        float PosX;//x
        float PosY;//y
        float PosZ;//z
        float WalkBias;//縦揺れ用バイアス値
        float weight;
        //コンストラクタ
        WalkInfo():HeadAngle(0),PosX(0),PosY(0),PosZ(0),WalkBias(0),weight(0.05f){}

};



bool quit=false;
//------------- プロトタイプ宣言 ------------------//
void display();
void reshape(int w, int h);
void timer(int value);

void specialkey(int key, int x, int y);
void SpecialKeyUp(int key, int x, int y);
    const int maru=1<<2;
    const int sankaku=1<<7;
    const int batu=1<<1;
    const int r1=1;
    const int r2=8;
    const int l1=32;
    const int l2=16;
    const int sel=512;
    const int sta=256;
    const int left=1000,down=1000;
void DrawXYZ();
void DrawField();
void CheckKeyStatus();

void joyStick(unsigned int,int,int,int);
//--------- 各種外部変数 ---------//
WalkInfo CurrentPos;
const float PI_OVER_180 = 0.0174532925f;
bool key_status[256];//キーの状態
float floormat[16];
float boxmat[16];
//---------- OpenGLの初期設定 ------------//
void GLUT_CALL_FUNCs()
{
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutTimerFunc(0,timer,17);
        glutSpecialFunc(specialkey);
        glutSpecialUpFunc(SpecialKeyUp); //キーを離した時の処理
        glutJoystickFunc(joyStick,10);
}
float ey=0.9f,ez=1.2f,ex=0.f;
bool toggleWindow=true;
void joyStick(unsigned int button,int x,int y,int z){
    //printf_s("bu=%d\n",button);
    //printf("ey=%d\nez=%d",ey,ez);
    if(x==left){  ;}
    if(y==down) { ey-=0.1f;}
    if(y==-down){ ey+=0.1f;}
    if(z==down){ ez+=0.1f;}
    if(z==-down){ ez-=0.1f;}
    //if(button & 1<<7){ey=1;}else{ey=0;}
    //if(button & 1<<1){ex=1;}else{ex=0;}
    //if(button & 1<<2){ez=1;}else{ez=0;}

    //printf_s("x=%d",x);
    //printf_s("y=%d",y);
    //printf_s("z=%d\n",z);

}
CgLoader* lo;
void MyOtherGLInit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
#if defined(WIN32)
    /* GLEW の初期化 */
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(1);
    }
    if(GLEW_ARB_point_parameters){
        ;
    }
#endif
    lo =new CgLoader("vtrans.cgo",VertexObj);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    //材質はglColorで設定する
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glutIgnoreKeyRepeat(GL_TRUE); //リピートを無視
}

Vector3 vec3(float x,float y,float z){
    Vector3 v;
    v.x=x;v.y=y;v.z=z;
    return v;
}

void GLUT_INITs(int *argcp,char**argvp)
{

    glutInit(argcp,argvp);
    glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutCreateWindow("Basic Walking Around without KeyRepeat");
    //glsl使えるようにwgl呼んだらいけるかも
  //  std::cout << "Vendor :"<<glGetString(GL_VENDOR)<<'\n';
  //std::cout << "GPU : "<<glGetString(GL_RENDERER) <<'\n';
  //std::cout << "OpenGL ver. " <<glGetString(GL_VERSION)<<'\n';
  //std::cout << "【拡張機能一覧】"<<std::endl;
    std::cout << glGetString(GL_EXTENSIONS) <<std::endl;
    Init(-9);
    MakeSpere(0,7,0,false);
    MakeBox(vec3(0,2,0),2,false,boxmat);
    MakeBox(vec3(-2,-3,0),1,false,boxmat);
    //MakeFloor(vec3(0,3,0),10,floormat);
    GLUT_CALL_FUNCs();
    MyOtherGLInit();
}


#include "TempleteUtil.h"

#include "ImageLoader.hpp"
//------------- メイン関数 ------------//
int main(int argc ,char **argv)
{
    //GLint v;
    //glGetIntegerv(GL_MAJOR_VERSION, *v);
    GLUT_INITs(&argc, argv);
    auto g=new GUIUtil();
    float roy[16] = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };
    g->addRot(roy);
    //auto il=ImageLoader();
    glutMainLoop();
    delete g;

    return 0;
}
void WindowUI(float width,float height){
    //- -
    //- +
    //+ +
    //+ -
#if _DEBUG

    bool e=lo->IsError();
#endif
    //lo.BindEnable([width,height](){
      auto he=height/2;
      auto uipos=-2.5666f;
      auto cpos=0.0f;//-0.5~0.5が適任
      glPushMatrix();
      glDepthMask(GL_FALSE);
      glColor4f(0.0f,0.0f,0.7f,0.4f);//blue
      glTranslatef(0,0,uipos);
      glRectf(-width,-height,width,height);
      //printf_s("%f\n",ez);
      glColor4f(0.2f,1.f,0.4f,0.4f);//glee
      glTranslatef(0.0f,cpos,0.1f);
      glRectf(-width,-0.1f,width,0.1f);
      

      glDepthMask(GL_TRUE);
      glPopMatrix();
    //});

}
void blendTest(){
    //if(ez> 1){glBlendFunc(GL_SRC_ONE, GL_ZERO);}
    // 通常転送（αあり）
    // つまりαブレンドのこと
    if(ez>2 ){glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);}
    // dst 反転
    if(ez> 3){glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);} // src = 1 固定}
    // 加算（αなし）
    if(ez> 4){glBlendFunc(GL_ONE, GL_ONE);}
    // 加算（αあり）
    if(ez> 5){glBlendFunc(GL_SRC_ALPHA, GL_ONE);}
    if(ez> 6){glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);} // src = 1 固定}
    if(ez> 7){glBlendFunc(GL_ONE, GL_ONE);}
    if(ez> 8){glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);} // src = 1 固定}
    if(ez> 9){glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);} // src = 1 固定}
    if(ez> 10){glBlendFunc(GL_SRC_ALPHA, GL_ONE);}
    if(ez> 11){glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);} // src = 1 固定}
    // 乗算（αなし）
    if(ez> 12){glBlendFunc(GL_ZERO, GL_SRC_COLOR);}
    // 乗算（αあり）
    // α値が小さくなればなるほど真っ黒になるので、
    // むしろαなしと言えるのかもしれない
    if(ez> 13){glBlendFunc(GL_ZERO, GL_SRC_COLOR);}
    if(ez> 14){glBlendFunc(GL_ZERO, GL_SRC_ALPHA);}
    // スクリーン（αなし）
    if(ez> 15){glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);}
    // 除外（αなし）
    if(ez> 16){glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR);}
    }
//------------- ここから各種コールバック --------------//
void display()
{
    static float LightPos[]= {10,10,10,0};
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();
    //glMatrixModeはMODELVIEW行列にしている
    glPushMatrix();
    if(toggleWindow){
        WindowUI(0.8f,0.8f);}
    //glRotatef(360 - CurrentPos.HeadAngle,0,1.0,0);
    //glTranslatef(-CurrentPos.PosX, -CurrentPos.PosY - 0.25, -CurrentPos.PosZ);
    gluLookAt(CurrentPos.PosX,CurrentPos.PosY+6+ey,CurrentPos.PosZ+2+ez,
        CurrentPos.PosX,CurrentPos.PosY,CurrentPos.PosZ,
        0,0,-1);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPos);

    DrawXYZ();

    DrawField();
    glPopMatrix();

    glutSwapBuffers();
    CheckKeyStatus();

}



void reshape(int w, int h)
{
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(30.0, (double)w / (double)h, 0.1, 1000.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

}

void Exit(){
    Quit();
    delete lo;
        glutExit();
}
//---  特殊キーによる制御  ----//
void specialkey(int key, int x, int y)
{
    
        switch (key) {
                case GLUT_KEY_UP:
                case GLUT_KEY_DOWN:
                case GLUT_KEY_RIGHT:
                case GLUT_KEY_LEFT:
                        key_status[key] = true;
                break;
                case GLUT_KEY_ALT_L:
                    toggleWindow = !toggleWindow;
		    break;
                case GLUT_KEY_SHIFT_L:
                    quit=true;
		    break;
                default: //ESCないらしい
                break;
        }
}

void SpecialKeyUp(int key, int x, int y)
{
        switch (key) {
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
        case GLUT_KEY_RIGHT:
        case GLUT_KEY_LEFT:
                key_status[key] = false;
        break;

        default:
        break;
        }
}
void timer(int value)
{
    static int count=0;
    count++;
    glutPostRedisplay();
    auto c=ObjectCount();
    if(count%1==0)    
        Step();
    if(quit){
	Exit();
    }
    glutTimerFunc(value,timer,17); //タイマー関数
}


//------------- ここから各種関数 ----------------//
void DrawXYZ()
{
        glBegin(GL_LINES);

        glColor3f(0,1,0);//x
        glVertex2f(-1000,0);
        glVertex2f(1000, 0);

        glColor3f(1,0,0);//y
        glVertex2f(0,0);
        glVertex2f(0,1000);

        glColor3f(0,0,1);//z
        glVertex3f(0,0,-1000);
        glVertex3f(0,0, 1000);
        glEnd();
}

void SetPosRocSca(){
    //下のコマンドから変換される
    glTranslatef(0,0,0);
    glRotatef(0,0,0,0);
    glScalef(0,0,0);
}
void DrawField()
{
    glColor3f(0,1,0);
    glPushMatrix();
    glTranslatef(1,0,-3);
    glutSolidCube(0.5);
    glPopMatrix();
 
    glPushMatrix();
    Render();
    glPopMatrix();
    
    glPushMatrix();
    glMultMatrixf(floormat);
    glScalef(1,0.5,1);
   // glutSolidCube(0.5);
    glPopMatrix();

    glColor3f(1,1,0);
    glPushMatrix();
    glTranslatef(-1,0,-3);
    glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(CurrentPos.PosX,CurrentPos.PosY,CurrentPos.PosZ);
    glutSolidCone(0.5,1,5,5);
    glPopMatrix();

    glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(1,0,5);
    glutSolidTeapot(0.3);
    glPopMatrix();

    glColor3f(1,0,1);
    glPushMatrix();
    glTranslatef(-1,0,5);
    glRotatef(90,-1,0,0);
    glutSolidCone(0.5,1,20,20);
    glPopMatrix();
}


void CheckKeyStatus()
{
        if(key_status[GLUT_KEY_UP] == true)
        {
                CurrentPos.PosX -= sin(CurrentPos.HeadAngle * PI_OVER_180) * CurrentPos.weight;
                CurrentPos.PosZ -= cos(CurrentPos.HeadAngle * PI_OVER_180) * CurrentPos.weight;
                CurrentPos.WalkBias += 10;
                if (CurrentPos.WalkBias >= 359.0f)
                {
                        CurrentPos.WalkBias = 0.0f;
                }
                CurrentPos.PosY= sin(CurrentPos.WalkBias*PI_OVER_180) / 20.0f;
        }

        if(key_status[GLUT_KEY_DOWN] == true)
        {
                CurrentPos.PosX += sin(CurrentPos.HeadAngle * PI_OVER_180) * CurrentPos.weight;
                CurrentPos.PosZ += cos(CurrentPos.HeadAngle * PI_OVER_180) * CurrentPos.weight;

                CurrentPos.WalkBias -= 10.f;
                if(CurrentPos.WalkBias <= 1.0)
                {
                        CurrentPos.WalkBias = 359.0f;
                }
                CurrentPos.PosY= sin(CurrentPos.WalkBias*PI_OVER_180) / 20.0f;
        }

	float xr=0.1f;
        if(key_status[GLUT_KEY_RIGHT] == true)
        {
                //CurrentPos.HeadAngle -= 2;
            CurrentPos.PosX+=xr;
        }

        if(key_status[GLUT_KEY_LEFT] == true)
        {
            CurrentPos.PosX-=xr;
                //CurrentPos.HeadAngle += 2;
        }
}
}