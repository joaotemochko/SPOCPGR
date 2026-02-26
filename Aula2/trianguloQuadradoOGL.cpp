#include <GL/glut.h>

void desenhaCena() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Desenhando um Quadrado (GL_QUADS) no canto superior esquerdo
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f); // Cor Amarela
    glVertex2f(-0.8f, 0.2f);    // Canto Inferior Esquerdo
    glVertex2f(-0.2f, 0.2f);    // Canto Inferior Direito
    glVertex2f(-0.2f, 0.8f);    // Canto Superior Direito
    glVertex2f(-0.8f, 0.8f);    // Canto Superior Esquerdo
    glEnd();

    // 2. Desenhando o nosso Triângulo (GL_TRIANGLES) no canto inferior direito
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 1.0f, 0.0f); // Cor Verde
    glVertex2f(0.2f, -0.8f);     // Esquerda
    glVertex2f(0.8f, -0.8f);     // Direita
    glVertex2f(0.5f, -0.2f);     // Topo
    glEnd();

    // 3. Desenhando Linhas (GL_LINES) no centro da tela
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f); // Cor Branca

    // Linha 1: Horizontal
    glVertex2f(-0.9f, 0.0f);
    glVertex2f(0.9f, 0.0f);

    // Linha 2: Vertical
    glVertex2f(0.0f, -0.9f);
    glVertex2f(0.0f, 0.9f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    // Inicializa a biblioteca GLUT
    glutInit(&argc, argv);

    // Configura o modo do display: Single Buffer (desenho direto) e cores RGB
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Configura o tamanho e a posição inicial da janela
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);

    // Cria a janela e define o título
    glutCreateWindow("Triangulo Clássico com GLUT");

    // Registra a função "desenhaCena" para ser chamada sempre que a tela precisar ser atualizada
    glutDisplayFunc(desenhaCena);

    // Entrega o controle do programa para o GLUT (inicia o loop infinito)
    glutMainLoop();

    return 0;
}