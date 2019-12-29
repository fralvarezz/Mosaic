#include <stdio.h>
#include <stdlib.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char** argv) {

    if (argc != 3) {
        printf("Usage: %s image_file_name\n", argv[0]);
        return EXIT_FAILURE;
    }

    //CV_LOAD_IMAGE_COLOR = 1 forces the resultant IplImage to be colour.
    //CV_LOAD_IMAGE_GRAYSCALE = 0 forces a greyscale IplImage.
    //CV_LOAD_IMAGE_UNCHANGED = -1
    IplImage* inicial = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
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
    
    
    unsigned char* pInicial;
    unsigned char* pFinal;
    unsigned char* pInicialF;
    unsigned char* pFinalF;
    
    int fila,columna;
    
    for(fila=0;fila<inicial->height/2;fila++){
        
        pInicial = (unsigned char*) inicial->imageData + fila * inicial->widthStep;
        pFinal = (unsigned char*) final->imageData + fila * final->widthStep;
        
        
        for(columna=0;columna<inicial->width;columna++){
            *pInicial++=*pFinal++;
            *pInicial++=*pFinal++;
            *pInicial++=*pFinal++;
        }
        pInicial = (unsigned char*) inicial->imageData + (inicial->height - fila) * inicial->widthStep;
        pFinal = (unsigned char*) final->imageData + (final->height - fila) * final->widthStep;
        
        for(columna=0;columna<final->width;columna++){
            *pInicial++=*pFinal++;
            *pInicial++=*pFinal++;
            *pInicial++=*pFinal++;
        }
        
        cvShowImage("Imagen", inicial);
        
        cvWaitKey(10);
                
    }
    
    
    // memory release for img before exiting the application
    cvReleaseImage(&inicial);

    // Self-explanatory
    cvDestroyWindow("Imagen");

    return EXIT_SUCCESS;

}