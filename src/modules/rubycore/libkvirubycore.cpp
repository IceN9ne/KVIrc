//=============================================================================
// TODO: Un1versal
//=============================================================================

#include "kvi_settings.h"
#include "KviModule.h"

#ifdef COMPILE_RUBY_SUPPORT

#include <ruby.h>

#endif

static bool rubycore_module_ctrl(KviModule *, const char * cmd, void * param)
{
#ifdef COMPILE_RUBY_SUPPORT
#endif //COMPILE_RUBY_SUPPORT

	return false;
}

static bool rubycore_module_init(KviModule *)
{
#ifdef COMPILE_RUBY_SUPPORT
	return true;
#else  //COMPILE_RUBY_SUPPORT
	return false;
#endif //COMPILE_RUBY_SUPPORT
}

static bool rubycore_module_cleanup(KviModule *)
{
#ifdef COMPILE_RUBY_SUPPORT
#endif //COMPILE_RUBY_SUPPORT

	return true;
}

static bool rubycore_module_can_unload(KviModule *)
{
#ifdef COMPILE_RUBY_SUPPORT
#endif //COMPILE_RUBY_SUPPORT

	return true;
}

KVIRC_MODULE(
	"RubyCore",
	"1.0.0",
	"Ruby Scripting Engine Core",
	rubycore_module_init,
	rubycore_module_can_unload,
	rubycore_module_ctrl,
	rubycore_module_cleanup,
	"ruby")
