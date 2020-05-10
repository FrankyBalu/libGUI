#ifndef __LIBGUI_PRIV_VIDEO__
#define __LIBGUI_PRIV_VIDEO__

namespace LIBGUI {

#include <SDL2/SDL.h>

typedef enum
{
    WINDOW_FULLSCREEN = 0x00000001,         /**< fullscreen window */
    WINDOW_OPENGL = 0x00000002,             /**< window usable with OpenGL context */
    WINDOW_SHOWN = 0x00000004,              /**< window is visible */
    WINDOW_HIDDEN = 0x00000008,             /**< window is not visible */
    WINDOW_BORDERLESS = 0x00000010,         /**< no window decoration */
    WINDOW_RESIZABLE = 0x00000020,          /**< window can be resized */
    WINDOW_MINIMIZED = 0x00000040,          /**< window is minimized */
    WINDOW_MAXIMIZED = 0x00000080,          /**< window is maximized */
    WINDOW_INPUT_GRABBED = 0x00000100,      /**< window has grabbed input focus */
    WINDOW_INPUT_FOCUS = 0x00000200,        /**< window has input focus */
    WINDOW_MOUSE_FOCUS = 0x00000400,        /**< window has mouse focus */
    WINDOW_FULLSCREEN_DESKTOP = ( SDL_WINDOW_FULLSCREEN | 0x00001000 ),
    WINDOW_FOREIGN = 0x00000800,            /**< window not created by SDL */
    WINDOW_ALLOW_HIGHDPI = 0x00002000,      /**< window should be created in high-DPI mode if supported.
                                                     On macOS NSHighResolutionCapable must be set true in the
                                                     application's Info.plist for this to have any effect. */
    WINDOW_MOUSE_CAPTURE = 0x00004000,      /**< window has mouse captured (unrelated to INPUT_GRABBED) */
    WINDOW_ALWAYS_ON_TOP = 0x00008000,      /**< window should always be above others */
    WINDOW_SKIP_TASKBAR  = 0x00010000,      /**< window should not be added to the taskbar */
    WINDOW_UTILITY       = 0x00020000,      /**< window should be treated as a utility window */
    WINDOW_TOOLTIP       = 0x00040000,      /**< window should be treated as a tooltip */
    WINDOW_POPUP_MENU    = 0x00080000,      /**< window should be treated as a popup menu */
    WINDOW_VULKAN        = 0x10000000       /**< window usable for Vulkan surface */
} WindowFlags;


class _privateVideo {

public:
	_privateVideo(void)
	{
		if (SDL_Init ( SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO ) != 0 );
		{
			
		}
	}


} //namespace LIBGUI
	
#endif //__LIBGUI_PRIV_VIDEO__
