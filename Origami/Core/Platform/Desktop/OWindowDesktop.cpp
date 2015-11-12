#include <Core/Graphics/OWindow.h>
#include <Core/Inputs/OInputsManager.h>
namespace Origami {

		void window_resize(GLFWwindow* window, int width, int height)
		{
			OWindow *win = (OWindow*)glfwGetWindowUserPointer(window);
            win->setDimensions(width, height, 1);
		}

		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
		{
            if (action == GLFW_PRESS || action == GLFW_REPEAT) {
                OInputsManager::Manager()->pressKey(key);
            }
            else if (action == GLFW_RELEASE) {
                OInputsManager::Manager()->releaseKey(key);
            }
		}

		void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
		{
            if (action == GLFW_PRESS || action == GLFW_REPEAT) {
                OInputsManager::Manager()->pressKey(button);
            }
            else if (action == GLFW_RELEASE) {
                OInputsManager::Manager()->releaseKey(button);
            }
		}

		void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
		{
//			OWindow *win = (OWindow*)glfwGetWindowUserPointer(window);
//			win->mx = xpos;
//			win->my = ypos;
		}
        
        void window_focus_callback(GLFWwindow* window, int focused)
        {
//            OWindow *win = (OWindow*)glfwGetWindowUserPointer(window);
//            if (focused)
//            {
//                OLog("Focused");
//            }
//            else
//            {
//                OLog("Focus Lost");
//            }
        }

		bool OWindow::PlatformInit()
		{
            //get screen fbo
            OScenesManager::Manager()->m_screen_fbo = 0;
            //
            
            //init and create GLFW window
			if (!glfwInit())
			{
				OErrLog("Failed to initialize GLFW...");
				return false;
			}

            
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

			if (!m_Window)
			{
				OErrLog("Failed to create GLFW Window...");
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
            
			glfwSetWindowSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);
            glfwSetWindowFocusCallback(m_Window, window_focus_callback);
			

            // init GLEW
#ifdef O_TARGET_DESKTOP_WIN32
			glewExperimental = GL_TRUE;
			if (glewInit() != GLEW_OK)
			{
				OErrLog("Failed to initialize GLEW...");
				return false;
			}
#endif

			OGLUtils::printGLInfo();

			return true;
		}

        void OWindow::PlatformVsync(bool vsync)
        {
            glfwSwapInterval(vsync);
        }
        
		void OWindow::PlatformUpdate()
		{
			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

        
        bool OWindow::iscloseRequested() {
            return glfwWindowShouldClose(m_Window) == 1;
        }

		void OWindow::PlatformClean()
		{
			
		}
}