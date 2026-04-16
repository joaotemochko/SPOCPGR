#include <GL/glut.h>

// Configura a iluminação inicial
void inicializaLuz() {
    // Habilita o motor de iluminação do OpenGL e o Z-Buffer (teste de profundidade)
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    // Habilita a Lâmpada 0
    glEnable(GL_LIGHT0);

    // Luz Ambiente Global (luz fraca que preenche todo o ambiente)
    GLfloat luzAmbiente[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Configuração da LUZ DIRECCIONAL (w = 0.0 significa que é luz direcional / Sol)
    GLfloat posicaoLuz[] = {0.0f, 10.0f, 10.0f, 0.0f}; 
    GLfloat luzDifusa[]  = {1.0f, 1.0f, 1.0f, 1.0f}; // Luz branca padrão
    
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
}

// Configura o material "Ouro" baseado no modelo de Phong
void aplicaMaterialOuro() {
    GLfloat mat_ambient[]  = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
    GLfloat mat_diffuse[]  = { 0.75164f, 0.60648f, 0.22648f, 1.0f };
    GLfloat mat_specular[] = { 0.62828f, 0.5558f, 0.366065f, 1.0f };
    GLfloat shininess[]    = { 51.2f }; // Intensidade do brilho

    // Aplica o material na frente do polígono
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Move a câmera um pouco para trás
    glTranslatef(0.0f, 0.0f, -5.0f);
    
    aplicaMaterialOuro();
    
    // Desenha o Bule (função nativa do GLUT que já calcula as Normais para nós)
    glutSolidTeapot(1.5);
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Aula 1 e 2 - Iluminação e Material (Ouro)");
    
    inicializaLuz();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}