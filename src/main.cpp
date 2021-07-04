#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//��������� ��� ��������� ������� ����
int g_windowSizeX = 640;
int g_windowSizeY = 480;

// ������� ��� ������������ ��������� ������� ����
void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int heigth)
{
    int g_windowSizeX = width;
    int g_windowSizeY = heigth;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY); // �������, ������������ OpelGL �����, ��� �� ����� �������� (�������� ���������� ������� ������ ����; ������; ������)

}

// ������� ��� ������������ ������� ������
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        //���� �������� ����
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE); // ��������� ����
    }
}
int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // ������ OpelGL � ���������
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// ������������ ������� OpelGL

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pwindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "BattleCity", nullptr, nullptr);// ������� ���� (������� ����)
    if (!pwindow) // ��������� ���������� �������� ����
    {
        std::cout << "glfwCreateWindow falled!" << std::endl;// �������� �� ������
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pwindow, glfwWindowSizeCallback); // ������������ ������� ��� ������������ �������� ����
    glfwSetKeyCallback(pwindow, glfwKeyCallback);


    /* Make the window's context current */
    glfwMakeContextCurrent(pwindow); // ������ �������� OpenGL ������� ��� �������� ���� (���� ����� ���� ���������)

    if (!gladLoadGL())
    {
        std::cout << "Can' load GLAD!" << std::endl;
        return -1;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl; // ���������� (�������� ����������)
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl; // ������ OpenGL
    //std::cout << "OpenGL " << GLVersion.major << " . " << GLVersion.minor << std::endl;

    glClearColor(1, 1, 0, 1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pwindow)) // �������� ��������� ����
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT); // ������� ����� �����

        /* Swap front and back buffers */
        glfwSwapBuffers(pwindow); // ����� (������ � ��������) ������ �������

        /* Poll for and process events */
        glfwPollEvents(); // ������������ ������ ������� �������� "�����" (������� ������, ����)
    }

    glfwTerminate();
    return 0;
}