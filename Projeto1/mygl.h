#ifndef _MYGL_H_
#define _MYGL_H_
#include <stdlib.h>
#include <math.h>
#include "definitions.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
//subrotinas simples
int mod_(int v){
if(v<0)v*=-1;
return v;
}
int max_(int a,int b){
if(a>=b)return a;
else return b;
}
int min_(int a,int b){
if(a<=b)return a;
else return b;
}

void ab(int v){
int tmp=0;
int x,y,offset;
for(x=0;x<IMAGE_WIDTH;x++){
for(y=0;y<IMAGE_HEIGHT;y++){
int offset = 4*x + 4*y*IMAGE_WIDTH;
tmp=FBptr[offset+3]+v;
if (tmp>255) tmp=255;
if (tmp<0) tmp=0;
IMGptr[offset+3]=(unsigned char)tmp;

}
}
}

void ajusta_negativo(unsigned char v){
unsigned char tmp=0;
int x,y,offset;
for(x=0;x<IMAGE_WIDTH;x++){
for(y=0;y<IMAGE_HEIGHT;y++){
int offset = 4*x + 4*y*IMAGE_WIDTH;
tmp=IMGptr[offset+0]+v;
if (tmp>255) tmp=255;
if (tmp<0) tmp=0;
IMGptr[offset+0]=tmp;
tmp=IMGptr[offset+1]+v;
if (tmp>255) tmp=255;
if (tmp<0) tmp=0;
IMGptr[offset+1]=tmp;
tmp=IMGptr[offset+2]+v;
if (tmp>255) tmp=255;
if (tmp<0) tmp=0;
IMGptr[offset+2]=tmp;

}
}
 
}


//
//========================= classes ============================
class cor{
private:
unsigned char r;
unsigned char g;
unsigned char b;
unsigned char a;
public:
cor(){
r=0;
g=0;
b=0;
a=0;
}
void set_color(unsigned char r_,unsigned char g_,unsigned char b_,unsigned char a_)
{
r=r_;
g=g_;
b=b_;
a=a_;
}
unsigned char get_r(){return r;}
unsigned char get_g(){return g;}
unsigned char get_b(){return b;}
unsigned char get_a(){return a;}
};

class ponto{
private:
int x;
int y;
public:
ponto()
{
    x=0;
    y=0;
}
void set_x_y(int x_,int y_)
{
x=x_;
y=y_;
}
int get_x(){return x;}
int get_y(){return y;}
};

//NÃO SEI SE VAI SER UTIL

class pixel{
private:
    ponto p;
    cor c;
public:
    pixel();
    ~pixel();
    cor get_color(){return c;}
    void set_color(cor a){
    c=a;
    }
    ponto get_ponto(){return p;}
    void set_ponto(ponto q){
        p=q;
        }
};

//==============================================================

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************
void PutPixel(cor color,ponto p0)
{
int _x = p0.get_x();
int _y = p0.get_y();
unsigned char red = color.get_r();
unsigned char green = color.get_g();
unsigned char blue = color.get_b();
unsigned char alfa = color.get_a();
int offset = 4*_x + 4*_y*IMAGE_WIDTH;
FBptr[offset + 0] = red;
FBptr[offset + 1] = green;
FBptr[offset + 2] = blue;
FBptr[offset + 3] = alfa;
}


int ni=4;

void PutPixel2(ponto p0)
{
int _x = p0.get_x();
int _y = p0.get_y();
int offset2 = ni*_y+ni*_x*IMAGE_WIDTH;
double red =  IMGptr[offset2+0];
double green = IMGptr[offset2+1];
double blue =  IMGptr[offset2+2];
double alfa = IMGptr[offset2+3];
//cout<<endl<<red<<","<<green<<","<<blue;
//_y=_y*(-1);
//_y=_y+511;//espelhando a imagem
//if(_x>27) _x=_x-28;
//else	_x=_x+483;
//NovaCorNaTela = CorDoObjeto * AlfaDoObjeto + CorAntigaNaTele * (1-AlfaDoObjeto)
//red = red+(red*(255-alfa))/255;
//green = green+(green*(255-alfa))/255;//ajuste de brilho a partir do alfa
//blue = blue+(blue*(255-alfa))/255;

//if(red>255)red=255;
//if(red<0)red=0;
//if(green>255)green=255;
//if(green<0)green=0;
//if(blue>255)blue=255;
//if(blue<0)blue=0;

int offset = 4*_x + 4*_y*IMAGE_WIDTH;
FBptr[offset + 0] = (unsigned char)red;
FBptr[offset + 1] = (unsigned char)green;
FBptr[offset + 2] = (unsigned char)blue;
FBptr[offset + 3] = (unsigned char)alfa;
}

void PutPixelRed(ponto p0)
{
int _x = p0.get_x();
int _y = p0.get_y();
int offset2 = ni*_y+ni*_x*IMAGE_WIDTH;
unsigned char red =  IMGptr[offset2+0];
//unsigned char green = IMGptr[offset2+1];
//unsigned char blue =  IMGptr[offset2+2];
unsigned char alfa = IMGptr[offset2+3];
//cout<<endl<<red<<","<<green<<","<<blue;
//_y=_y*(-1);
//_y=_y+511;//espelhando a imagem
//if(_x>27) _x=_x-28;
//else	_x=_x+483;

int offset = 4*_x + 4*_y*IMAGE_WIDTH;
FBptr[offset + 0] = red;
FBptr[offset + 1] = 0;
FBptr[offset + 2] = 0;
FBptr[offset + 3] = alfa;
}

void PutPixelGreen(ponto p0)
{
int _x = p0.get_x();
int _y = p0.get_y();
int offset2 = ni*_y+ni*_x*IMAGE_WIDTH;
//unsigned char red =  IMGptr[offset2+0];
unsigned char green = IMGptr[offset2+1];
//unsigned char blue =  IMGptr[offset2+2];
unsigned char alfa = IMGptr[offset2+3];
//cout<<endl<<red<<","<<green<<","<<blue;
//_y=_y*(-1);
//_y=_y+511;//espelhando a imagem
//if(_x>27) _x=_x-28;
//else	_x=_x+483;

int offset = 4*_x + 4*_y*IMAGE_WIDTH;
FBptr[offset + 0] = 0;
FBptr[offset + 1] = green;
FBptr[offset + 2] = 0;
FBptr[offset + 3] = alfa;
}

void PutPixelBlue(ponto p0)
{
int _x = p0.get_x();
int _y = p0.get_y();
int offset2 = ni*_y+ni*_x*IMAGE_WIDTH;
//unsigned char red =  IMGptr[offset2+0];
//unsigned char green = IMGptr[offset2+1];
unsigned char blue =  IMGptr[offset2+2];
unsigned char alfa = IMGptr[offset2+3];
//cout<<endl<<red<<","<<green<<","<<blue;
//_y=_y*(-1);
//_y=_y+511;//espelhando a imagem
//if(_x>27) _x=_x-28;
//else	_x=_x+483;

int offset = 4*_x + 4*_y*IMAGE_WIDTH;
FBptr[offset + 0] = 0;
FBptr[offset + 1] = 0;
FBptr[offset + 2] = blue;
FBptr[offset + 3] = alfa;
}


void PutPixelGrayScale(ponto p0)
{
int _x = p0.get_x();
int _y = p0.get_y();
int offset2 = ni*_y+ni*_x*IMAGE_WIDTH;
unsigned char red =  IMGptr[offset2+0];
unsigned char green = IMGptr[offset2+1];
unsigned char blue =  IMGptr[offset2+2];
unsigned char alfa = IMGptr[offset2+3];
unsigned char gs=floor((float)(red+green+blue)/3);
//cout<<endl<<red<<","<<green<<","<<blue;
//_y=_y*(-1);
//_y=_y+511;//espelhando a imagem
//if(_x>27) _x=_x-28;
//else	_x=_x+483;

int offset = 4*_x + 4*_y*IMAGE_WIDTH;
FBptr[offset + 0] = gs;
FBptr[offset + 1] = gs;
FBptr[offset + 2] = gs;
FBptr[offset + 3] = alfa;
}

void PutPixelNegativo(ponto p0)
{
int _x = p0.get_x();
int _y = p0.get_y();
int offset2 = ni*_y+ni*_x*IMAGE_WIDTH;
unsigned char red =   255 - IMGptr[offset2+0];
unsigned char green = 255 - IMGptr[offset2+1];
unsigned char blue =  255 - IMGptr[offset2+2];
unsigned char alfa = IMGptr[offset2+3];
//cout<<endl<<red<<","<<green<<","<<blue;
//_y=_y*(-1);
//_y=_y+511;//espelhando a imagem
//if(_x>27) _x=_x-28;
//else	_x=_x+483;

int offset = 4*_x + 4*_y*IMAGE_WIDTH;
FBptr[offset + 0] = red;
FBptr[offset + 1] = green;
FBptr[offset + 2] = blue;
FBptr[offset + 3] = alfa;
}

void DrawTela(){
    ponto px;
for(int x=0;x<IMAGE_HEIGHT;x++){
    for(int y=0;y<IMAGE_WIDTH;y++){
    px.set_x_y(x,y);
    PutPixel2(px);
    }
}
}

void DrawTelaR(){
    ponto px;
for(int x=0;x<IMAGE_HEIGHT;x++){
    for(int y=0;y<IMAGE_WIDTH;y++){
    px.set_x_y(x,y);
    PutPixelRed(px);
    }
}
}

void DrawTelaG(){
    ponto px;
for(int x=0;x<IMAGE_HEIGHT;x++){
    for(int y=0;y<IMAGE_WIDTH;y++){
    px.set_x_y(x,y);
    PutPixelGreen(px);
    }
}
}

void DrawTelaB(){
    ponto px;
for(int x=0;x<IMAGE_HEIGHT;x++){
    for(int y=0;y<IMAGE_WIDTH;y++){
    px.set_x_y(x,y);
    PutPixelBlue(px);
    }
}
}

void DrawTelaGS(){
    ponto px;
for(int x=0;x<IMAGE_HEIGHT;x++){
    for(int y=0;y<IMAGE_WIDTH;y++){
    px.set_x_y(x,y);
    PutPixelGrayScale(px);
    }
}
}

void DrawTelaN(){
    ponto px;
for(int x=0;x<IMAGE_HEIGHT;x++){
    for(int y=0;y<IMAGE_WIDTH;y++){
    px.set_x_y(x,y);
    PutPixelNegativo(px);
    }
}
}

void DrawLine(ponto p0,cor c0,ponto p1,cor c1)//p0 e sua respectiva cor cor, p1 e suacor.
{
    //para espelhar defini alguns ifs com algumas condições especificas para determinar
    //o quadrante que a reta se encontrava e setei um valor especifico de flag, para realizar
    //as operações inversas antes de passar as coordenadas x,y para o putpixel e o calculo do
    //offset para ser impresso no local aproximado em que sua reta é descrita matematicamente.

//variaveis para os casos de dx<dy para poder usar o segundo octante
int flag=0;
int temp;
int ft=0;//se mudar os pontos, muda as cores, muda as cores dos pixel iniciais pintados na tela
cor ct;//caso precise inverter a cor
//cores de entrada
float ri,gi,bi,ai,rf,gf,bf,af;
//variacao da cor da linha
float r_var,g_var,b_var,a_var;

ponto pxy;//para o loop
    //Po(x0,y0)
int x0=p0.get_x();
int y0=p0.get_y();
    //P1(x1,y1)
int x1=p1.get_x();
int y1=p1.get_y();
    //variação de x e de y
int dx = x1 - x0;
int dy = y1 - y0;

if(dy<0){
temp=x0;
x0=x1;
x1=temp;
temp=y0;
y0=y1;
y1=temp;
dx = x1 - x0;
dy = y1 - y0;
ct=c0;
c0=c1;
c1=ct;
ft=1;//flag de mudança de cor
}

if(dx<0&&dy>=0&&mod_(dx)>=mod_(dy)){flag+=2;
x0*=-1;
x1*=-1;
dx = x1 - x0;
dy = y1 - y0;
}

if(dx<dy&&dx>=0){
flag++;//caso o dx>dy, com x e y positivos, temos o segundo octante,
//flag serve para inverter o x pelo y na hora de chamar PutPixel(cor,ponto);
//troca x por y nos dois pontos e recalcula tudo normal
temp=x0;/**troca x pelo y**/
x0=y0;//x0 recebe y0
y0=temp;//y0 recebe x0
temp=x1;
x1=y1;//x1 recebe y1
y1=temp;//y1 recebe x1
dx = x1 - x0;// recalcula os valores de dx e dy
dy = y1 - y0;
}

if(dx<0&&dy>=0&&mod_(dx)<mod_(dy)){
flag+=5;
temp=x0;/**troca x pelo y**/
x0=y0;//x0 recebe y0
y0=temp;//y0 recebe x0
temp=x1;
x1=y1;//x1 recebe y1
y1=temp;//y1 recebe x1
x0*=-1;
x1*=-1;
x1+=512;
x0+=512;
dx = x1 - x0;
dy = y1 - y0;
if(dy<0){
temp=x0;
x0=x1;
x1=temp;
temp=y0;
y0=y1;
y1=temp;
dx = x1 - x0;
dy = y1 - y0;
ct=c0;
c0=c1;
c1=ct;
ft=1;//flag de mudança de cor
}
}
//cor de p0
ri=c0.get_r();
gi=c0.get_g();
bi=c0.get_b();
ai=c0.get_a();
//cor de p1
rf=c1.get_r();
gf=c1.get_g();
bf=c1.get_b();
af=c1.get_a();
//variação de cor
r_var=(float)(rf-ri)/(dx+0.00001);//+0.00001para evitar divisão por zero
g_var=(float)(gf-gi)/(dx+0.00001);
b_var=(float)(bf-bi)/(dx+0.00001);
a_var=(float)(af-ai)/(dx+0.00001);
//variavel de decisão para acender o pixel d
int dnew=2*dy-dx;//primeira variavel de decisão
int d_new;
int inc_e=2*dy;
int inc_ne=2*(dy-dx);
d_new=2*dy-dx;//primeiro dold
int x=x0;int y=y0;
cor cl;ponto pl;
//pinta pontos limite com cores invertidas ou não, dependendo do valor da flag de cor
if(ft==0){
PutPixel(c0,p0);
PutPixel(c1,p1);}
if(ft==1&&flag!=5){
PutPixel(c0,p1);
PutPixel(c1,p0);}
for(int i=x;i<x1;i++){
   if(d_new<=0){
    d_new+=inc_e;
    x++;
   }
   else{
    d_new+=inc_ne;
    x++;
    y++;
   }
   //variação das cores
    ri+=r_var;
    gi+=g_var;
    bi+=b_var;
    ai+=a_var;
   cl.set_color(ri,gi,bi,ai);
   if(flag==0){
    pl.set_x_y(x,y);
   }
   if(flag==1){
    pl.set_x_y(y,x);
   }
   if(flag==2){
    pl.set_x_y(-x,y);
   }
   if(flag==5){
    pl.set_x_y(y,-x+512);
   }
   PutPixel(cl,pl);
}
}




#endif // _MYGL_H_

