#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"

// массив vertex
GLfloat point[] = {
     0.0f, 0.5f, 0.0f,
     0.5f,-0.5f, 0.0f,
    -0.5f,-0.5f, 0.0f
};

// массив цвета
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

//переменны для изменения размера окна
int g_windowSizeX = 640;
int g_windowSizeY = 480;

// функция для отслеживания изменений размера окна
void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int heigth)
{
    g_windowSizeX = width;
    g_windowSizeY = heigth;
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
int main(int argc, char** argv)
{
    ResourceManager resourceManager(argv[0]);


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

    std::string vertexShader;// (vertex_shader);
    std::string fragmentShader;// (fragment_shader);
    Renderer::ShaderProgram shaderProgram(vertexShader, fragmentShader);
    if (!shaderProgram.idCompiled())
    {
        std::cerr << "Can't create shader program!" << std::endl;
        return -1;
    }

    //передаем позицию видеокарте
    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo); // генерирует значение и передает значение по указателю
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    // заполняем буфер информацией для видеокарты
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW); // вид буффера, размер буфера в байтах, указатель на буфер, подсказка для драйвера

    // передает информацию для массива цвета
    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // обработка данных для видеокарты
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // включаем нулевую позицию
    glEnableVertexAttribArray(0);
    //включаем текущей буфер
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    // связываем данные
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // данная команда выполняется только для текущего забиндинованного буфера

    // включаем цвет
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pwindow)) // проверка состояния окна
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT); // очищаем буфер цвета

        // подключаем шейдеры для рисования
        shaderProgram.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3); // команда отрисовки

        /* Swap front and back buffers */
        glfwSwapBuffers(pwindow); // буфер (задний и передний) меняем местами

        /* Poll for and process events */
        glfwPollEvents(); // обрабатываем ивенты которые поступют "извне" (нажатия клавиш, окна)
    }

    glfwTerminate();
    return 0;
}