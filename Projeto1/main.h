#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#include "definitions.h"
#include "mygl.h"
#include "bitmapload.hpp"
#define GL_CLAMP_TO_EDGE 0x812F

GLuint tex;

//*****************************************************************************

void TeclasEspeciais(int key, int x, int y)
{
    switch (key)
    {
  	case GLUT_KEY_UP:
              cout<<"up"<<endl;
             ajusta_negativo(1); break; 
    	case GLUT_KEY_DOWN:
              cout<<"down"<<endl;
	      ajusta_negativo(-1); break; 
    	case GLUT_KEY_LEFT: 
              cout<<"left"<<endl;
		option--; if(option<0) option=5;
               break; 
   	case GLUT_KEY_RIGHT:  
              cout<<"right"<<endl;
		option++; if(option>5) option=0;
               break; 


	case GLUT_KEY_F1:
	cout<<"brilho-- ";
	ab(-1);
	cout<<"brilho:"<<(int)FBptr[3]<<endl;
	break;
 
	case GLUT_KEY_F2:
	cout<<"brilho++ ";
	ab(1);
	cout<<"brilho:"<<(int)FBptr[3]<<endl;
	break;
 
	case GLUT_KEY_F3:
	Mat mat(512, 512, CV_8UC4);
	createAlphaMat(mat);
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	compression_params.push_back(100);//qualidade da imagem entre 0 e 120
	    try {
        imwrite("output.jpeg", mat, compression_params);
    }
    catch (runtime_error& ex) {
        fprintf(stderr, "Exception converting image to JPEG format: %s\n", ex.what());
        break;
    }

    fprintf(stdout, "Saved JPEG file with alpha data.\n");
	cout<<"Arquivo Salvo";
	break;

	//default:
		//até agora nada
	//	break;
    }
    glutPostRedisplay();
}

//*****************************************************************************

void (*DrawFunc)(void);

//*****************************************************************************
void display(){
	DrawFunc();

	// Copia o framebuffer para a textura.
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, FBptr);
	
	glEnable(GL_TEXTURE_2D);

	// Desenha o quadrilátero com a textura mapeada
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glViewport(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);

	glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f( 1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f( 1.0f, 1.0f, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

//*****************************************************************************
void exitprog(void){
	// Libera a memória referente ao framebuffer.
	if (!FBptr)
		delete [] FBptr;
	if(!IMGptr)
		delete [] IMGptr;
	//if(!tmp)
	//	delete [] tmp;
	std::clog << "Exiting...\n";
}

//*****************************************************************************
void InitOpenGL(int *argc, char **argv)
{
	glutInit(argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(IMAGE_WIDTH, IMAGE_HEIGHT);
	glutInitWindowPosition(100,100);
	glutCreateWindow("My OpenGL");
	
	//fundo pra o alfa fazer diferença

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glEnable( GL_BLEND ); 
	glClearColor(0.0,0.0,0.0,0.0);

	// Ajusta a projeção ortográfica.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

//*****************************************************************************
void InitCallBacks(void)
{
	atexit( exitprog );
	glutDisplayFunc(display);
	//glutSpecialFunc(TeclasEspeciais);
}

//*****************************************************************************
void InitDataStructures(void)
{
	// Aloca o framebuffer e inicializa suas posições com 0.
	int size = IMAGE_WIDTH * IMAGE_HEIGHT;
	FBptr =  new unsigned char[size * 4];
	IMGptr = new unsigned char[size * 4];  

	IMGptr = readBMP();

	//if(IMGptr!=FBptr)cout<<"true"<<endl;
	
	for (unsigned int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT ; i++)
	{
		FBptr[i*4]   = 0;
		FBptr[i*4+1] = 0;
		FBptr[i*4+2] = 0;
		FBptr[i*4+3] = 255;
	}

	// Cria uma textura 2D, RGBA (8 bits por componente).
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
}
