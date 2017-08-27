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

#define zero 0
#define um 1
#define dois 2
#define tres 3 

GLuint tex;

//*****************************************************************************

void TeclasEspeciais(int key, int x, int y)
{	Mat mat(512, 512, CV_8UC4);
	int offset;
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
		option--; if(option<0) option=5;//altera valor da opção, para alterar o modo de exibição
               break; 
   	case GLUT_KEY_RIGHT:  
              cout<<"right"<<endl;
		option++; if(option>5) option=0;//altera o valor da opção, para alterar o modo de exibição
               break; 


	case GLUT_KEY_F1://diminui brilho somando o valor no canal alfa
	cout<<"brilho-- ";
	ab(-1);
	cout<<"brilho:"<<(int)FBptr[3]<<endl;
	/*alfa--;
	if(alfa<1)alfa=1;
	createAlphaMat(mat);
	mat.convertTo(mat, -1, alfa, beta);
  for (int i = 0; i < IMAGE_WIDTH; ++i) {
        for (int j = 0; j < IMAGE_HEIGHT; ++j) {
		offset=4*i+4*j*IMAGE_WIDTH;
		Point3_<uchar>* p = mat.ptr<Point3_<uchar> >(i,j);

			int offset= 4*i + 4*j*IMAGE_WIDTH;	
		IMGptr[offset+0]=(unsigned char)p->z;//red
		IMGptr[offset+1]=(unsigned char)p->y;//green
		IMGptr[offset+2]=(unsigned char)p->x;//blue
		IMGptr[offset+3]=(unsigned char)255;//alfa
		
		
        }
    }*/
	
	break;
 
	case GLUT_KEY_F2://aumenta brilho subtraindo o valor no canal alfa
	cout<<"brilho++ ";
	ab(1);
	cout<<"brilho:"<<(int)FBptr[3]<<endl;
	/*alfa++;
	if(alfa>3)alfa=3;
	createAlphaMat(mat);
	mat.convertTo(mat, -1, alfa, beta);
  for (int i = 0; i < IMAGE_WIDTH; ++i) {
        for (int j = 0; j < IMAGE_HEIGHT; ++j) {
		offset=4*i+4*j*IMAGE_WIDTH;
		Point3_<uchar>* p = mat.ptr<Point3_<uchar> >(i,j);

			int offset= 4*i + 4*j*IMAGE_WIDTH;	
		IMGptr[offset+0]=(unsigned char)p->z;//red
		IMGptr[offset+1]=(unsigned char)p->y;//green
		IMGptr[offset+2]=(unsigned char)p->x;//blue
		IMGptr[offset+3]=(unsigned char)255;//alfa
		
		
        }
    }*/
	break;

	case GLUT_KEY_F3://diminui brilho dividindo o valor no canal alfa por 2
	cout<<"brilhom--(/) ";
	abm(-1);
	cout<<"brilho:"<<(int)FBptr[3]<<endl;
	/*beta--;
	if(beta<0)beta=0;

	mat.convertTo(mat, -1, alfa, beta);
  for (int i = 0; i < IMAGE_WIDTH; ++i) {
        for (int j = 0; j < IMAGE_HEIGHT; ++j) {
		offset=4*i+4*j*IMAGE_WIDTH;
		Point3_<uchar>* p = mat.ptr<Point3_<uchar> >(i,j);

			int offset= 4*i + 4*j*IMAGE_WIDTH;	
		IMGptr[offset+0]=(unsigned char)p->z;//red
		IMGptr[offset+1]=(unsigned char)p->y;//green
		IMGptr[offset+2]=(unsigned char)p->x;//blue
		IMGptr[offset+3]=(unsigned char)255;//alfa
		
		
        }
    }*/
	break;
 
	case GLUT_KEY_F4://aumenta o brilho multiplicando o valor do canal por 2
	cout<<"brilhom++(*) ";
	abm(1);
	cout<<"brilho:"<<(int)FBptr[3]<<endl;
	/*beta++;
	if(beta>100)beta=100;
	createAlphaMat(mat);
	mat.convertTo(mat, -1, alfa, beta);
  for (int i = 0; i < IMAGE_WIDTH; ++i) {
        for (int j = 0; j < IMAGE_HEIGHT; ++j) {
		offset=4*i+4*j*IMAGE_WIDTH;
		Point3_<uchar>* p = mat.ptr<Point3_<uchar> >(i,j);

			int offset= 4*i + 4*j*IMAGE_WIDTH;	
		IMGptr[offset+0]=(unsigned char)p->z;//red
		IMGptr[offset+1]=(unsigned char)p->y;//green
		IMGptr[offset+2]=(unsigned char)p->x;//blue
		IMGptr[offset+3]=(unsigned char)255;//alfa
		
		
        }
    }*/
	break;
 
	case GLUT_KEY_F5://salva a imagem normal, converte em yuv e salva com cada canal separado: Y,U e V
	Mat mat(512, 512, CV_8UC4);
	Mat matyuv(512, 512, CV_8UC4);
	Mat maty(512, 512, CV_8UC4);
	Mat matu(512, 512, CV_8UC4);
	Mat matv(512, 512, CV_8UC4);
	Mat inputImage(512, 512, CV_8UC4);

//=========== 
	
    //Conver a imagem para o espaço de cor YCrCb e salva os resultados separados em arquivos distintos.

	createAlphaMat(mat);
	//mat.convertTo(mat, -1, 1, 255-FBptr[3]);
	inputImage=mat.clone();

	//Salva YUV
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	compression_params.push_back(100);//qualidade da imagem entre 0 e 120

	    try {
	 
        imwrite("yuv.jpeg", mat, compression_params);
    }
    catch (runtime_error& ex) {
        fprintf(stderr, "Exception converting image to JPEG format: %s\n", ex.what());
        break;
    }

    fprintf(stdout, "Saved JPEG file with alpha data.\n");
	cout<<"Arquivo Salvo"<<endl;


	Mat channel[3];

	cvtColor(inputImage, inputImage, COLOR_BGR2YCrCb);
	split(inputImage, channel);
	//showChannels(channel, hsv_labels, std_values, COLOR_YCrCb2BGR);

	Mat outputImage(512, 512, CV_8UC4);
	Mat aux[3];

//y
		aux[0] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 1;    //retorna matriz de 1=Mat[3]= {1,1,1}
		aux[1] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 127.5;//{127.5,127.5,127.5}
		aux[2] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 127.5;//{127.5,127.5,127.5}
		aux[0] = channel[0];//canal y  
		// merge() une os canais de volta em output
		merge(aux, 3, outputImage);
//output image recebe os valores de aux[0] para seu primeiro canal, aux[1] para o segundo e aux[2] para o terceiro
		// convert from output color space to BGR
		cvtColor(outputImage, maty, COLOR_YCrCb2BGR);

	    try {
        imwrite("y.jpeg", maty, compression_params);
    }
    catch (runtime_error& ex) {
        fprintf(stderr, "Exception converting image to JPEG format: %s\n", ex.what());
        break;
    }

    fprintf(stdout, "Saved JPEG file with y data.\n");
	cout<<"Arquivo y Salvo"<<endl;

//u
		aux[0] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 127.5;
		aux[1] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 1;
		aux[2] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 127.5;
		aux[1] = channel[1];  

		merge(aux, 3, outputImage);
		
		cvtColor(outputImage, matu, COLOR_YCrCb2BGR);
	    try {
        imwrite("u.jpeg", matu, compression_params);
    }
    catch (runtime_error& ex) {
        fprintf(stderr, "Exception converting image to JPEG format: %s\n", ex.what());
        break;
    }

    fprintf(stdout, "Saved JPEG file with u data.\n");
	cout<<"Arquivo u Salvo"<<endl;

//v


		aux[0] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 127.5;
		aux[1] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 127.5;
		aux[2] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 1;
		aux[2] = channel[2];  

		merge(aux, 3, outputImage);

		cvtColor(outputImage, matv, COLOR_YCrCb2BGR);

	    try {
        imwrite("v.jpeg", matv, compression_params);
    }
    catch (runtime_error& ex) {
        fprintf(stderr, "Exception converting image to JPEG format: %s\n", ex.what());
        break;
    }

    fprintf(stdout, "Saved JPEG file with v data.\n");
	cout<<"Arquivo v Salvo"<<endl;

	break;
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
	// Libera a memória referente ao framebuffer e ao buffer auxiliar.
	if (!FBptr)
		delete [] FBptr;
	if(!IMGptr)
		delete [] IMGptr;
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
