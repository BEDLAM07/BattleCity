#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//переменны для изменения размера окна
int g_windowSizeX = 640;
int g_windowSizeY = 480;

// функция для отслеживания изменений размера окна
void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int heigth)
{
    int g_windowSizeX = width;
    int g_windowSizeY = heigth;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY); // команда, показывающая OpelGL место, где мы хотим рисовать (передаем координаты нижнего левого угла; ширина; высота)

}

// функция для отслеживания нажатия клавиш
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        //флаг закрытия окна
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE); // закрываем окно
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // версия OpelGL в программе
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// подмножество функций OpelGL

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pwindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "BattleCity", nullptr, nullptr);// создаем окно (размеры окна)
    if (!pwindow) // проверяем успешность создания окна
    {
        std::cout << "glfwCreateWindow falled!" << std::endl;// проверка на ошибки
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pwindow, glfwWindowSizeCallback); // регистрируем команду для отслеживания размеров окна
    glfwSetKeyCallback(pwindow, glfwKeyCallback);


    /* Make the window's context current */
    glfwMakeContextCurrent(pwindow); // делаем контекст OpenGL текущим для текущего окна (окон может быть несколько)

    if (!gladLoadGL())
    {
        std::cout << "Can' load GLAD!" << std::endl;
        return -1;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl; // видеокарта (параметр видеокарты)
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl; // версия OpenGL
    //std::cout << "OpenGL " << GLVersion.major << " . " << GLVersion.minor << std::endl;

    glClearColor(1, 1, 0, 1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pwindow)) // проверка состояния окна
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT); // очищаем буфер цвета

        /* Swap front and back buffers */
        glfwSwapBuffers(pwindow); // буфер (задний и передний) меняем местами

        /* Poll for and process events */
        glfwPollEvents(); // обрабатываем ивенты которые поступют "извне" (нажатия клавиш, окна)
    }

    glfwTerminate();
    return 0;
}