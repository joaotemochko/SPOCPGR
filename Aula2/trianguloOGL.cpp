#include <GL/glut.h>

// Função callback responsável por desenhar na tela
void desenhaCena() {
    // 1. Limpa a tela (por padrão, o fundo é preto)
    glClear(GL_COLOR_BUFFER_BIT);

    // 2. Inicia o modo de desenho de triângulos
    glBegin(GL_TRIANGLES);

    // Vértice 1: Esquerda-Inferior (Cor Vermelha)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);

    // Vértice 2: Direita-Inferior (Cor Verde)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.5f, -0.5f);

    // Vértice 3: Topo-Centro (Cor Azul)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.0f, 0.5f);

    // 3. Finaliza o desenho do triângulo
    glEnd();

    // 4. Garante que todos os comandos OpenGL sejam executados
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