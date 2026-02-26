#include <GL/glut.h>

// Variáveis globais para controlar a animação
float anguloTriangulo = 0.0f;
float posicaoQuadradoX = -1.0f; // Começa na extremidade esquerda
float direcaoQuadrado = 1.0f;   // 1 para a direita, -1 para a esquerda

void desenhaCena() {
    // Limpa o ecrã
    glClear(GL_COLOR_BUFFER_BIT);

    // --- OBJETO 1: Triângulo Rotativo ---
    glPushMatrix(); // Guarda o estado original do ecrã (centro em 0,0)
    
    // Movemos o triângulo um pouco para a esquerda
    glTranslatef(-0.4f, 0.0f, 0.0f);
    // Rodamos o triângulo no eixo Z (o eixo que aponta para fora do ecrã)
    glRotatef(anguloTriangulo, 0.0f, 0.0f, 1.0f); 
    
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); // Vermelho
        glVertex2f(-0.3f, -0.3f);
        glColor3f(0.0f, 1.0f, 0.0f); // Verde
        glVertex2f(0.3f, -0.3f);
        glColor3f(0.0f, 0.0f, 1.0f); // Azul
        glVertex2f(0.0f, 0.3f);
    glEnd();
    
    glPopMatrix(); // Restaura o estado original (cancela o translate e rotate)


    // --- OBJETO 2: Quadrado em Movimento ---
    glPushMatrix(); // Guarda novamente o estado original
    
    // Movemos o quadrado no eixo X usando a nossa variável que muda com o tempo
    glTranslatef(posicaoQuadradoX, 0.0f, 0.0f);
    
    glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 0.0f); // Amarelo
        glVertex2f(-0.1f, -0.1f);
        glVertex2f( 0.1f, -0.1f);
        glVertex2f( 0.1f,  0.1f);
        glVertex2f(-0.1f,  0.1f);
    glEnd();
    
    glPopMatrix(); // Restaura o estado original

    // Troca os buffers (exibe o que acabou de ser desenhado)
    glutSwapBuffers();
}

// Função chamada continuamente baseada num temporizador
void atualizaAnimacao(int valor) {
    // 1. Atualiza o ângulo do triângulo
    anguloTriangulo += 2.0f;
    if (anguloTriangulo > 360.0f) {
        anguloTriangulo -= 360.0f;
    }

    // 2. Atualiza a posição do quadrado (vai e volta)
    posicaoQuadradoX += 0.02f * direcaoQuadrado;
    if (posicaoQuadradoX > 1.0f || posicaoQuadradoX < -1.0f) {
        direcaoQuadrado *= -1.0f; // Inverte a direção quando bate nas bordas
    }

    // Pede ao GLUT para redesenhar o ecrã com os novos valores
    glutPostRedisplay();

    // Regista o temporizador para ser chamado novamente daqui a 16 milissegundos (aprox. 60 FPS)
    glutTimerFunc(16, atualizaAnimacao, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    
    // ATENÇÃO: Mudamos para GLUT_DOUBLE para evitar cintilação
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    
    glutInitWindowSize(800, 600);
    glutCreateWindow("Animacao com OpenGL e GLUT");
    
    // Registar as funções
    glutDisplayFunc(desenhaCena);
    
    // Iniciar o temporizador pela primeira vez (chama atualizaAnimacao em 25ms)
    glutTimerFunc(25, atualizaAnimacao, 0);
    
    glutMainLoop();
    
    return 0;
}