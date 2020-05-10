#ifndef __LIBGUI_RENDERER__
#define __LIBGUI_RENDERER__

#include "video.h"
#include "point.h"
#include "rect.h"

namespace LIBGUI {

struct lowRenderer;
typedef struct lowRenderer lowRenderer;
class Texture;

typedef enum
{
    RENDERER_SOFTWARE 		= 0x00000001,	/**< Software Fallback */
    RENDERER_ACCELERATED 	= 0x00000002,	/**< Hardware beschleunigter Renderer */
    RENDERER_PRESENTVSYNC 	= 0x00000004,	/**< VSYNC eingeschalten */
    RENDERER_TARGETTEXTURE 	= 0x00000008	/**< Renderer unterstützt rendern auf Texture */
} RendererFlags;

typedef enum
{
    FLIP_NONE		 	= 0x00000000,	/**< Keine Spiegelung */
    FLIP_HORIZONTAL		= 0x00000001,	/**< Horizontal Gespiegelt */
    FLIP_VERTICAL 		= 0x00000002	/**< Vertikal Gespiegelt */
} RendererFlip;

typedef struct RendererInfo
{
    const char *name;           /**< Name des Rendertreibers */
    Uint32 flags;               /**< Unterstützte ::RendererFlags */
    Uint32 num_texture_formats; /**< Anzahl unterstützer Texturformate */
    Uint32 texture_formats[16]; /**< Die verfügbaren Textureformate */
    int max_texture_width;      /**< Maximale Textur Briete */
    int max_texture_height;     /**< Maximale Textur Höhe */
} RendererInfo;

/**
 *  Anzahl der verfügbaren Treiber
 */
int GetNumRenderDrivers ( void );
	
/**
 *  \brief Info über spezifizierten Treiber.
 *
 *  \param index Index von dem Treiber von dem man die Information möchte.
 *  \param info  Zeiger auf Info struktur die mit den Treiberdaten gefüllt wird.
 *
 *  \return 0 wenn erfolgreich, -1 wenn es zu dem Index keinen Treiber gibt.
 *
 *  \sa CreateRenderer()
 */
int GetRenderDriverInfo(int index, RendererInfo * info);

/**
 * \brief Gibt die informationen zu einem Treiber mit LOG aus
 */
void PrintDriverInfo ( RendererInfo *info );

class Renderer {
private:
	RendererInfo *_info;
	lowRenderer *_renderer;
	RawWindow *_window;

	/**
	 * füllt die info struktur
	 */
	void Info( void );
public:
	Renderer ( RawWindow *win );
	Renderer ( RawWindow *win, int index, Uint32 flags );
	
	~Renderer ( void );
	
	lowRenderer* GetlowRenderer( void );
	int SetDrawColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	int GetDrawColor( Uint8 * r, Uint8 * g, Uint8 * b, Uint8 * a );
	int Clear( void );
	int DrawPoint( int x, int y);
	int DrawPoint( Point &point);
	int DrawLine( int x1, int y1, int x2, int y2);
	int DrawLine( Point &point1, Point &point2);
	int DrawRect( Rect *rect );
	int DrawFillRect( Rect * rect);
	void Present( void );
};



}//namespace LIBGUI

#endif //__LIBGUI_RENDERER__
