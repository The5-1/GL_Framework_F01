#define GLEW_STATIC //Using the static lib, so we need to enable it

#include <iostream>

#include "Logging.h"
#include "Application.h"
#include "GL_init.h"
#include "imgui_init.h"

#include "Mesh.h"
#include "Shader.h"

using namespace The5;
using namespace std;
using namespace glm;

std::string RESOURCE_PATH = "D:/Dev/Projects/GL_Framework_F01/GL_Framework_F01/";
std::string GLOBAL_RESOURCE_PATH = "D:/Dev/Assets/";

std::string SHADER_PATH = "D:/Dev/Projects/GL_Framework_F01/GL_Framework_F01/Assets/Shaders/";

std::string DEFAULT_SHADER_FRAG = SHADER_PATH + "default.frag.glsl";
std::string DEFAULT_SHADER_VERT = SHADER_PATH + "default.vert.glsl";


int main(int argc, char *argv[])
{
	/*
	Application appliation;
	GLFWwindow* window = appliation.makeWindow(1024,720,"Epos");
	appliation.startInputManager();
	appliation.startGameLoop();
	*/

	Application* application = new Application();
	application->initWindow(1024, 720, "Epos");
	application->initInputManager();
	application->startGameLoop();

	string file_model_sponza = GLOBAL_RESOURCE_PATH + "Sponza_Atrium/sponza.obj";
	string file_model_nanosuit = GLOBAL_RESOURCE_PATH + "Nanosuit/nanosuit.obj";

	//Model model = Model(file_model_nanosuit);

	vec3List positions = { vec3(0.0,0.0,0.0), vec3(1.0,0.0,0.0), vec3(1.0,1.0,0.0), vec3(0.0,1.0,0.0) };
	uintList indices = { 0,1,2,0,2,3 };

	Mesh mesh01(positions, indices);
	Shader shader01(DEFAULT_SHADER_VERT, DEFAULT_SHADER_FRAG);

	shader01.uniform("modelMatrix", mat4(1.0f));
	shader01.uniform("viewMatrix", mat4(1.0f));
	shader01.uniform("projMatrix", mat4(1.0f));

	shader01.use();
	mesh01.draw();

	//std::cin.get();

	application->terminate();
	return 1;
}


/*
#include <imgui.h>
#include "imgui_impl_glfw_gl3.h"

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}

int main(int, char**)
{
	// Setup window
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		return 1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
	gladLoadGL();

	// Setup ImGui binding
	ImGui_ImplGlfwGL3_Init(window, true);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them. 
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple. 
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'extra_fonts/README.txt' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//ImGuiIO& io = ImGui::GetIO();
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../extra_fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../extra_fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../extra_fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);

	bool show_test_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();

		// 1. Show a simple window.
		// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug".
		{
			static float f = 0.0f;
			ImGui::Text("Hello, world!");
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			ImGui::ColorEdit3("clear color", (float*)&clear_color);
			if (ImGui::Button("Test Window")) show_test_window ^= 1;
			if (ImGui::Button("Another Window")) show_another_window ^= 1;
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

		// 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name the window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);
			ImGui::Text("Hello from another window!");
			ImGui::End();
		}

		// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow().
		if (show_test_window)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
			ImGui::ShowTestWindow(&show_test_window);
		}

		// Rendering
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplGlfwGL3_Shutdown();
	glfwTerminate();

	return 0;
}
*/