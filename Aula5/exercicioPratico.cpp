#include <GL/glut.h>

void inicializa() {
    // Habilita luz e teste de profundidade para o 3D funcionar corretamente
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    
    // Posiciona uma luz padrão
    GLfloat posicaoLuz[] = { 5.0f, 5.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    
    // Define a cor do material (um azul claro)
    GLfloat mat_diffuse[] = { 0.2f, 0.6f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    glShadeModel(GL_FLAT); // Teste 1: Bola de discoteca (Facetado)
    // glShadeModel(GL_SMOOTH); // Teste 2: Arredondado (Gouraud)
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Afasta a câmera para podermos ver a esfera inteira
    glTranslatef(0.0f, 0.0f, -3.5f);
    
    // ==========================================================
    // PASSO 1: DESENHAR A ESFERA DE BAIXA RESOLUÇÃO
    // ==========================================================
    // Raio 1.0, 16 fatias (slices), 16 pilhas (stacks)
    glutSolidSphere(1.0, 16, 16);
    
    glutSwapBuffers();
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
    glutInitWindowSize(600, 600);
    glutCreateWindow("Teste de Interpolação: Flat vs Smooth");
    
    inicializa();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    return 0;
}