#include "components/VideoVlcComponent.h"

#include "renderers/Renderer.h"
#include "resources/TextureResource.h"
#include "utils/StringUtil.h"
#include "PowerSaver.h"
#include "Settings.h"
#include <SDL_mutex.h>

#ifdef WIN32
#include <codecvt>
#endif

libvlc_instance_t* VideoVlcComponent::mVLC = NULL;

// VLC prepares to render a video frame.
static void *lock(void *data, void **p_pixels) {
	struct VideoContext *c = (struct VideoContext *)data;
	SDL_LockMutex(c->mutex);
	SDL_LockSurface(c->surface);
	*p_pixels = c->surface->pixels;
	return NULL; // Picture identifier, not needed here.
}

// VLC just rendered a video frame.
static void unlock(void *data, void* /*id*/, void *const* /*p_pixels*/) {
	struct VideoContext *c = (struct VideoContext *)data;
	SDL_UnlockSurface(c->surface);
	SDL_UnlockMutex(c->mutex);
}

// VLC wants to display a video frame.
static void display(void* /*data*/, void* /*id*/) {
	//Data to be displayed
}