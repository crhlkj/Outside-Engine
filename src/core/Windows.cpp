#include "../../include/core/Windows.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../libs/stb_image.h"

Windows::Windows() : imguiRender()
{
    if (!glfwInit())
    {
        std::cerr << "Error: Could not initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

Windows::~Windows()
{
    imguiRender.Shutdown();
    if (window)
    {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void Windows::setWindowIcon(GLFWwindow *window, const char *iconPath)
{
    int width, height, channels;
    unsigned char *data = stbi_load(iconPath, &width, &height, &channels, 4);

    if (data)
    {
        GLFWimage images[1];
        images[0].width = width;
        images[0].height = height;
        images[0].pixels = data;

        glfwSetWindowIcon(window, 1, images);
        stbi_image_free(data);
        std::cout << "Icon loaded successfully: " << iconPath << " (" << width << "x" << height << ")\n";
    }
    else
    {
        std::cerr << "Failed to load icon: " << iconPath << '\n';
    }
}

void Windows::createWindow(int width, int height, const char *title)
{
    this->window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!this->window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1); // Enable vsync

    setWindowIcon(this->window, "../../assets/logo_128x128.png");

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    imguiRender.Initialize(this->window);

    glViewport(0, 0, width, height);

    float triangleVertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    unsigned int triangleIndices[] = {2, 1, 0};

    rendering.setupBuffers(triangleVertices, sizeof(triangleVertices),
                          triangleIndices, sizeof(triangleIndices));
}

bool Windows::running() const
{
    return !glfwWindowShouldClose(window);
}

void Windows::run_loop()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rendering.useShader(3);

    glfwPollEvents();
    fpsCounter.Update();
    imguiRender.BeginFrame();

    fpsCounter.Render();
    ImGui::ShowDemoWindow(); // Show demo window ImGui

    imguiRender.EndFrame();
    glfwSwapBuffers(window);
}

GLFWwindow *Windows::getWindow() const
{
    return window;
}
