#include <GL/glut.h>
#include <stdlib.h> // Necessário para a função exit()

// --- Variáveis Globais ---
// Animação do triângulo
float anguloTriangulo = 0.0f;

// Posição do nosso quadrado controlado pelo jogador
float jogadorX = 0.0f;
float jogadorY = 0.0f;
float velocidade = 0.05f; // O quanto o quadrado anda a cada toque na tecla

// --- Função de Desenho ---
void desenhaCena() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Triângulo Giratório (Animado automaticamente)
    glPushMatrix();
    glTranslatef(-0.5f, 0.5f, 0.0f); // Posicionado no canto superior esquerdo
    glRotatef(anguloTriangulo, 0.0f, 0.0f, 1.0f); 
    
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.2f, -0.2f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.2f, -0.2f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.2f);
    glEnd();
    glPopMatrix();


    // 2. Quadrado Controlado pelo Jogador
    glPushMatrix();
    // Usamos as variáveis que o teclado vai modificar
    glTranslatef(jogadorX, jogadorY, 0.0f); 
    
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.5f, 0.0f); // Laranja
        glVertex2f(-0.1f, -0.1f);
        glVertex2f( 0.1f, -0.1f);
        glVertex2f( 0.1f,  0.1f);
        glVertex2f(-0.1f,  0.1f);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

// --- Funções de Teclado ---

// Para teclas direcionais (Setas)
void tecladoEspecial(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            jogadorY += velocidade; // Sobe no eixo Y
            break;
        case GLUT_KEY_DOWN:
            jogadorY -= velocidade; // Desce no eixo Y
            break;
        case GLUT_KEY_LEFT:
            jogadorX -= velocidade; // Vai para esquerda no eixo X
            break;
        case GLUT_KEY_RIGHT:
            jogadorX += velocidade; // Vai para direita no eixo X
            break;
    }
    // Pede para redesenhar a tela imediatamente após mover
    glutPostRedisplay();
}

// Para teclas normais (letras, esc, espaço)
void tecladoNormal(unsigned char key, int x, int y) {
    // A tecla ESC tem o código ASCII 27
    if (key == 27) { 
        exit(0); // Fecha o programa
    }
}

// --- Função de Animação Contínua ---
void atualizaAnimacao(int valor) {
    anguloTriangulo += 2.0f;
    if (anguloTriangulo > 360.0f) {
        anguloTriangulo -= 360.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, atualizaAnimacao, 0);
}

// --- Função Principal ---
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Interacao com Teclado (Setas e ESC)");
    
    // Registrando os Callbacks
    glutDisplayFunc(desenhaCena);
    
    // NOSSOS NOVOS CALLBACKS DE TECLADO:
    glutSpecialFunc(tecladoEspecial);
    glutKeyboardFunc(tecladoNormal);
    
    glutTimerFunc(25, atualizaAnimacao, 0);
    
    glutMainLoop();
    return 0;
}