#pragma once

#include <Core/Utils/OGLUtils.h>
#include <Core/Graphics/Scenes/OScenesManager.h>

namespace Origami {

#define MAX_KEYS 512
#define MAX_BUTTONS 5

		class OWindow {
		private:
			const char* m_Title;

			bool m_Closed;
			bool m_Vsync;

#ifdef O_TARGET_DESKTOP
			GLFWwindow *m_Window;
#endif
            
            int m_Width, m_Height, m_Scale;
		public:
			OWindow(const char* title, uint width, uint height, uint scale);
			~OWindow();

            
			void clear() const;
            void refreshInput();
            
            
			void update(float deltaTime);
            void render(float interpolation);
            void swapBuffers();
            
            bool iscloseRequested();
			bool closed() const;

            void setDimensions(uint width, uint height, uint scale);
            inline uint getWidth() const { return m_Width; }
			inline uint getHeight() const { return m_Height; }
			inline uint getScale() const { return m_Scale; }

            void SetVsync(bool enabled);
            inline bool IsVsync() const { return m_Vsync; }
            
        private:
			bool init();

			bool PlatformInit();
			void PlatformUpdate();
			void PlatformClean();
            void PlatformVsync(bool vsync);
		};
}