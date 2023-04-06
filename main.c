#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float position[4][2] = {
    {0, 0},
    {0, 10},
    {10, 10},
    {10, 0}
};

int centroide[2] = {5, 5};

int isTranslate = 0;
int isRotate = 0;
int isScale = 0;

int translateValue[2] = {0, 0};
int rotateValue = 0;
float scaleValue = 0; 

char mode = 't';

void moveSquare(char dir) {
    switch (dir) {
        case 'u':
            translateValue[1] = 1;
            break;
        case 'd':
            translateValue[1] = -1;
            break;
        case 'l':
            translateValue[0] = -1;
            break;
        case 'r':
            translateValue[0] = 1;
            break;
    }

    isTranslate = 1;
    glutPostRedisplay();
}

void scale(char sing) {
    switch (sing) {
        case 'd':
            scaleValue = 0.9;
            break;
        case 'u':
            scaleValue = 1.1;        
            break;
    }

    isScale = 1;
    glutPostRedisplay();
}

void rotatePoints(float points[][2], int numPoints, float centerX, float centerY, float angle) {
    float rad = angle * M_PI / 180.0;
    float cosTheta = cos(rad);
    float sinTheta = sin(rad);

    for(int i = 0; i < numPoints; i++) {
        float x = points[i][0] - centerX;
        float y = points[i][1] - centerY;

        points[i][0] = x * cosTheta - y * sinTheta + centerX;
        points[i][1] = x * sinTheta + y * cosTheta + centerY;
    }
}

void rotate(char dir) {
    switch (dir) {
        case 'l':
            rotateValue = 10;
            break;
        case 'r':
            rotateValue = -10;
            break;
    }

    isRotate = 1;
    glutPostRedisplay();
}

void getArrowsOnKeyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            if (mode == 't') moveSquare('u');
            
            if (mode == 's') scale('u');
            
            break;
        case GLUT_KEY_DOWN:
            if (mode == 't') moveSquare('d');
            
            if (mode == 's') scale('d');

            break;
        case GLUT_KEY_LEFT:
            if (mode == 't') moveSquare('l');
            
            if (mode == 'r') rotate('l');

            break;
        case GLUT_KEY_RIGHT:
            if (mode == 't') moveSquare('r');

            if (mode == 'r') rotate('r');

            break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 't':
            mode = 't';
            break;
        case 'r':
            mode = 'r';
            break;
        case 's':
            mode = 's';
            break;
        case 'q':
            exit(0);
            break;
    }
}

int init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);   // define a cor de fundo
    glMatrixMode(GL_PROJECTION);        // carrega a matriz de projeção
    gluOrtho2D(0.0, 100.0, 0.0, 100.0); // define projeção ortogonal 2D 
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT); // desenha o fundo (limpa a janela)
    glColor3f(1.0, 0.0, 0.0);     // altera o atributo de cor
    

    if(isTranslate) {
        glTranslatef(translateValue[0], translateValue[1], 0);
        translateValue[0] = 0;
        translateValue[1] = 0;
        isTranslate = 0;
    }

    if(isScale) {
        GLfloat centerX = 0.0f, centerY = 0.0f;
        for (int i = 0; i < 4; i++) {
            centerX += position[i][0];
            centerY += position[i][1];
        }
        centerX /= 4.0f;
        centerY /= 4.0f;

        glTranslatef(centerX, centerY, 0);

        glScalef(scaleValue, scaleValue, 0);

        glTranslatef(-centerX, -centerY, 0);
        scaleValue = 0;
        isScale = 0;
    }

    if(isRotate) {
        float centerX = 0.0f, centerY = 0.0f;
        for (int i = 0; i < 4; i++) {
            centerX += position[i][0];
            centerY += position[i][1];
        }
        centerX /= 4.0f;
        centerY /= 4.0f;

        rotatePoints(position, 4, centerX, centerY, rotateValue);

        rotateValue = 0;
        isRotate = 0;
    }

    glBegin(GL_QUADS);            // desenha uma linha
    glVertex2f(position[0][0], position[0][1]);
    glVertex2f(position[1][0], position[1][1]);
    glVertex2f(position[2][0], position[2][1]);
    glVertex2f(position[3][0], position[3][1]);
    glEnd();

    glutPostRedisplay();
    glFlush(); // desenha os comandos não executados
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);                       // inicializa o GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // configura o modo de display
    glutInitWindowSize(500, 500);                // configura a largura e altura da janela de exibição
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Um programa OpenGL Exemplo"); // cria a janela de exibição

    init(); // executa função de inicialização
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(getArrowsOnKeyboard);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0); // define a matriz de projeção

    glutDisplayFunc(display); // estabelece a função "display" como a função callback de exibição.
    glutMainLoop();           // mostre tudo e espere
    return 0;
}