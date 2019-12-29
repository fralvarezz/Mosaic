#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#define ANCHO 16
#define ALTO 16

int compararBloque(int i, int j, IplImage * origen, int k, int l, IplImage * fin);

void copiarBloque(int i, int j, IplImage * origen, int k, int l, IplImage * fin);

int main(int argc, char** argv) {
    
    OPENFILENAME ofn;
    char szFile[100];
    
    ZeroMemory(&ofn,sizeof( ofn));
    ofn.lStructSize =sizeof( ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile =sizeof( szFile);
    ofn.lpstrFilter = "All\0*.*\0JPEG\0*.jpg\0PNG\0*.png\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    GetOpenFileName(&ofn);
    
    
    if (argc != 3) {
        printf("Usage: %s image_file_name\n", argv[0]);
        return EXIT_FAILURE;
    }

    //CV_LOAD_IMAGE_COLOR = 1 forces the resultant IplImage to be colour.
    //CV_LOAD_IMAGE_GRAYSCALE = 0 forces a greyscale IplImage.
    //CV_LOAD_IMAGE_UNCHANGED = -1
    IplImage* inicial = cvLoadImage(ofn.lpstrFile, CV_LOAD_IMAGE_COLOR);
    IplImage* final = cvLoadImage(argv[2], CV_LOAD_IMAGE_UNCHANGED);
    
    
    // Always check if the program can find a file
    if (!inicial) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }
    if (!final) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }

    // a visualization window is created with title 'image'
    cvNamedWindow("Imagen", CV_WINDOW_AUTOSIZE);
    cvShowImage("Imagen",inicial);
    cvWaitKey(0);
    
    
    int fila,columna;
    int fila2,columna2;
    int filafinal,columnafinal;
    int diferencia=ANCHO*ALTO*255*3;
    int aux;
    
    /*
    for(fila=0;fila<inicial->height/ALTO;fila++){
        for(columna=0;columna<inicial->width/ANCHO;columna++){
            copiarBloque(fila*ALTO,columna*ANCHO,inicial,fila*ALTO,columna*ANCHO,final);
            cvShowImage("Imagen",inicial);
            cvWaitKey(10);
        }
    }
    */
    
    for(fila=0;fila<inicial->height/ALTO;fila++){
        for(columna=0;columna<inicial->width/ANCHO;columna++){
            
            for(fila2=0;fila2<final->height/ALTO;fila2++){
                for(columna2=0;columna2<final->width/ANCHO;columna2++){
                    aux=compararBloque(fila*ALTO,columna*ANCHO,inicial,fila2*ALTO,columna2*ANCHO,final);
                    if(aux<diferencia){
                        diferencia=aux;
                        filafinal=fila2*ALTO;
                        columnafinal=columna2*ANCHO;
                    }
                }
            }
            copiarBloque(fila*ALTO,columna*ANCHO,inicial,filafinal,columnafinal,final);
            
            diferencia=ANCHO*ALTO*255*3;
        }
    }
    cvShowImage("Imagen",inicial);
    cvWaitKey(0);
    
    // memory release for img before exiting the application
    cvReleaseImage(&inicial);

    // Self-explanatory
    cvDestroyWindow("Imagen");

    return EXIT_SUCCESS;

}

void copiarBloque(int i, int j, IplImage * origen, int k, int l, IplImage * fin){
    unsigned char* pOrigen;
    unsigned char* pFin;
    
    int fila, columna;
    
    for(fila=0;fila<ALTO;fila++){
        pOrigen = (unsigned char*) origen->imageData + (fila + i) * origen->widthStep + 3*j;
        pFin = (unsigned char*) fin->imageData + (fila + k) * fin->widthStep + 3*l;
        
        for(columna=0;columna<ANCHO;columna++){
            *pOrigen++=*pFin++;
            *pOrigen++=*pFin++;
            *pOrigen++=*pFin++;
        }
    }
    
}

int compararBloque(int i, int j, IplImage * origen, int k, int l, IplImage * fin){
    unsigned char* pOrigen;
    unsigned char* pFin;
    int toret=0;
    
    int fila, columna;
    
    for(fila=0;fila<ALTO;fila++){
        pOrigen = (unsigned char*) origen->imageData + (fila + i) * origen->widthStep + 3*j;
        pFin = (unsigned char*) fin->imageData + (fila + k) * fin->widthStep + 3*l;
        
        for(columna=0;columna<ANCHO;columna++){
            toret+= abs(*pOrigen++ - *pFin++);
            toret+= abs(*pOrigen++ - *pFin++);
            toret+= abs(*pOrigen++ - *pFin++);
        }
    }
    return toret;
}