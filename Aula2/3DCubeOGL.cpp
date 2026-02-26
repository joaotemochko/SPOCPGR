#include <GL/glut.h>

// Variável para a animação do cubo
float anguloCubo = 0.0f;

// --- Função para desenhar as 6 faces do Cubo ---
void desenhaCubo() {
    glBegin(GL_QUADS);

    // Face Frontal (Vermelha)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // Face Traseira (Verde)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Face Superior (Azul)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    // Face Inferior (Amarela)
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Face Direita (Magenta)
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Face Esquerda (Ciano)
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    glEnd();
}

// --- Função de Desenho Principal ---
void desenhaCena() {
    // ATENÇÃO: Agora limpamos também o GL_DEPTH_BUFFER_BIT (o Z-Buffer)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reinicia a matriz de transformação atual
    glLoadIdentity();

    // Movemos a "câmera" para trás no eixo Z para ver o cubo (que está no 0,0,0)
    glTranslatef(0.0f, 0.0f, -6.0f);

    // Rotacionamos o cubo nos eixos X, Y e Z ao mesmo tempo para um efeito legal
    glRotatef(anguloCubo, 1.0f, 1.0f, 1.0f);

    // Chamamos a função que constrói o cubo
    desenhaCubo();

    glutSwapBuffers();
}

// --- Função para Configurar a Câmera e a Janela ---
void redimensiona(int largura, int altura) {
    if (altura == 0) altura = 1; // Evita divisão por zero
    float proporcao = (float)largura / (float)altura;

    // Define a área de desenho na janela
    glViewport(0, 0, largura, altura);

    // Entra no modo de configuração da Câmera (Projeção)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Configura a Perspectiva: Ângulo de visão de 45 graus, proporção da tela, e limites de visão (perto e longe)
    gluPerspective(45.0f, proporcao, 0.1f, 100.0f);

    // Volta para o modo de desenho de modelos (ModelView)
    glMatrixMode(GL_MODELVIEW);
}

// --- Função de Animação ---
void atualizaAnimacao(int valor) {
    anguloCubo += 1.5f;
    if (anguloCubo > 360.0f) anguloCubo -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(16, atualizaAnimacao, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    // ATENÇÃO: Adicionamos o GLUT_DEPTH para ativar o Z-Buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Meu Primeiro Cubo 3D");

    // ATIVA O TESTE DE PROFUNDIDADE (Z-BUFFER) - Sem isso o 3D quebra!
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(desenhaCena);

    // Registra a função que configura a câmera quando a janela é criada ou redimensionada
    glutReshapeFunc(redimensiona);

    glutTimerFunc(25, atualizaAnimacao, 0);

    glutMainLoop();
    return 0;
}