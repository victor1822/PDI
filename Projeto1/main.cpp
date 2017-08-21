//#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include "bitmapload.hpp"
#include <iostream>
#include "main.h"
#include "mygl.h"
#include "definitions.h"
#include <stdlib.h>
#include <vector>

//-----------------------------------------------------------------------------


void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
/**Cores para testes*/

switch(option){
case 0:
DrawTela();
break;
case 1:
DrawTelaN();
break;
case 2:
DrawTelaGS();
break;
case 3:
DrawTelaR();
break;
case 4:
DrawTelaG();
break;
case 5:
DrawTelaB();
}

}

//-----------------------------------------------------------------------------
int main(int argc, char **argv){
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	glutSpecialFunc(TeclasEspeciais);
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

