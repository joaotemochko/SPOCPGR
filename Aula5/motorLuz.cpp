#include <GL/glut.h>

// Variável para controlar qual luz está ativa (1 = Ambiente, 2 = Direcional, 3 = Pontual)
int tipoLuz = 2; 

void configuraLuz() {
    // Desativa a lâmpada 0 por padrão a cada frame para reconfigurar
    glDisable(GL_LIGHT0); 
    
    // Arrays de cores básicas
    GLfloat luzBranca[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat semLuz[]    = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat luzAmbienteForte[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat luzAmbienteFraca[] = { 0.2f, 0.2f, 0.2f, 1.0f };

    if (tipoLuz == 1) {
        // 1. LUZ AMBIENTE PURA
        // Aumentamos a luz global do cenário e deixamos a lâmpada 0 desligada
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbienteForte);
    } 
    else if (tipoLuz == 2) {
        // 2. LUZ DIRECIONAL (Ex: Sol)
        // Reduzimos a luz global para não ofuscar
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbienteFraca);
        
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, luzBranca);
        
        // O quarto parâmetro (w) é 0.0! Isso define uma luz vinda do infinito.
        // Os valores x,y,z (1.0, 1.0, 0.0) formam um VETOR de direção, não uma coordenada.
        GLfloat direcao[] = { 1.0f, 1.0f, 0.0f, 0.0f }; 
        glLightfv(GL_LIGHT0, GL_POSITION, direcao);
    } 
    else if (tipoLuz == 3) {
        // 3. LUZ PONTUAL (Ex: Lâmpada flutuando perto do objeto)
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbienteFraca);
        
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, luzBranca);
        
        // O quarto parâmetro (w) é 1.0! Isso define um PONTO no espaço (x,y,z).
        GLfloat posicao[] = { 0.0f, 2.0f, 2.0f, 1.0f }; 
        glLightfv(GL_LIGHT0, GL_POSITION, posicao);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Posiciona a câmera
    gluLookAt(0.0, 2.0, 5.0,  
              0.0, 0.0, 0.0,  
              0.0, 1.0, 0.0); 

    configuraLuz();

    // Desenha um "chão" simples para vermos como a luz bate nele
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f); // Normal apontando para cima
        glVertex3f(-3.0f, -1.0f,  3.0f);
        glVertex3f( 3.0f, -1.0f,  3.0f);
        glVertex3f( 3.0f, -1.0f, -3.0f);
        glVertex3f(-3.0f, -1.0f, -3.0f);
    glEnd();

    // Desenha uma esfera no centro
    glutSolidSphere(1.0, 32, 32);

    glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y) {
    if (key == '1') tipoLuz = 1;
    if (key == '2') tipoLuz = 2;
    if (key == '3') tipoLuz = 3;
    
    glutPostRedisplay(); // Atualiza a tela imediatamente após apertar a tecla
}

void inicializa() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL); // Permite usar glColor para definir a cor do material difuso
    glColor3f(0.2f, 0.6f, 0.8f); // Azul
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tipos de Luz: 1(Ambiente), 2(Direcional), 3(Pontual)");
    
    inicializa();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    
    glutMainLoop();
    return 0;
}