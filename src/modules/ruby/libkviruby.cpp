#include "kvi_settings.h"
#include "KviModule.h"
#include "KviModuleManager.h"
#include "KviLocale.h"

#ifdef COMPILE_RUBY_SUPPORT

#include "../rubycore/rubycoreinterface.h"
#include <ruby.h>

static KviModule * g_pRubyCoreModule = nullptr;

#define KVS_CHECK_RUBYCORE(_m, _c)                                   \
	g_pRubyCoreModule = g_pModuleManager->getModule("rubycore"); \
	if(!g_pRubyCoreModule)                                       \
	{                                                            \
		if(!_c->switches()->find('q', "quiet"))              \
		{                                                    \
			_c->warning(__tr2qs_ctx("The rubycore module can't be loaded: Ruby support not available", "ruby")); \
			_c->warning(__tr2qs_ctx("To see more details about loading failure try /rubycore.load", "ruby"));    \
		}                                                    \
	}

#define KVS_CHECK_MODULE_STATE(_m, _c) KVS_CHECK_RUBYCORE(_m, _c)

#else  //COMPILE_RUBY_SUPPORT

static KviModule * g_pRubyCoreModule = nullptr;

#define KVS_CHECK_RUBYCORE(_m, _c)

#define KVS_CHECK_MODULE_STATE(_m, _c)          \
	if(!_c->switches()->find('q', "quiet")) \
		_c->warning(__tr2qs_ctx("This KVIrc executable has been compiled without Ruby scripting support", "ruby")); \
	return true;

#endif //COMPILE_RUBY_SUPPORT

/*
	@doc: ruby_and_kvs
	@type:
		language
	@title:
		Using Ruby from KVS and vice-versa.
	@short:
		How to use Ruby from KVS and KVS from Ruby.
	@body:
		[big]Introduction[/big][br]
		Starting from version 4.9.2 you can include Ruby code snippets
		in KVS code and you can use KVS commands from within Ruby.
		This feature is present only if a working Ruby installation
		has been found at build time.[br]
*/

/*
	@doc: ruby.begin
	@type:
		command
	@title:
		ruby.begin
	@keyterms:
		Including Ruby code snippets in KVS
	@short:
		Starts a Ruby code snippet
	@syntax:
		ruby.begin [-n] [-q] [(<ruby_context>[,<arg0>[,<arg1>[...]]])]
		<ruby code>
		ruby.end
	@switches:
		!sw: -q | --quiet
		Prevents the command from printing any warnings.
		!sw: -n | --no-return
		Prevents the Ruby script return value to be propogated
		to the current context.
		!sw: -f | --fail-on-error
		Treat Ruby errors as KVS errors and abort execution of the
		current script. Incompatible with -q
	@description:
		TODO: Un1versal
	@examples:
		[example]
			ruby.begin
			kvirc.eval("puts \"Hello World from Ruby!\"");
			ruby.end
		[/example]
	@seealso:
*/

static bool ruby_kvs_cmd_begin(KviKvsModuleCommandCall * c)
{
	QString szCode, szContext;
	KviKvsVariantList vList;
	KVSM_PARAMETERS_BEGIN(c)
	KVSM_PARAMETER("code", KVS_PT_STRING, 0, szCode)
	KVSM_PARAMETER("context", KVS_PT_STRING, KVS_PF_OPTIONAL, szContext)
	KVSM_PARAMETER("args", KVS_PT_VARIANTLIST, KVS_PF_OPTIONAL, vList)
	KVSM_PARAMETERS_END(c)

	KVS_CHECK_MODULE_STATE(m, c)

#ifdef COMPILE_RUBY_SUPPORT
#endif //COMPILE_RUBY_SUPPORT

	return true;
}

/*
	@doc: ruby.destroy
	@type:
		command
	@title:
		ruby.destroy
	@short:
		Destroys a Ruby execution context
	@syntax:
		ruby.destroy [-q] <context_name:string>
	@description:
		TODO: Un1versal
	@seealso:
		[cmd]ruby.begin[/cmd]
*/

static bool ruby_kvs_cmd_destroy(KviKvsModuleCommandCall * c)
{
	QString szContext;
	KVSM_PARAMETERS_BEGIN(c)
	KVSM_PARAMETER("context", KVS_PT_NONEMPTYSTRING, 0, szContext)
	KVSM_PARAMETERS_END(c)

	KVS_CHECK_MODULE_STATE(m, c)

#ifdef COMPILE_RUBY_SUPPORT
#endif //COMPILE_RUBY_SUPPORT

	return true;
}

/*
	@doc: ruby.isAvailable
	@type:
		function
	@title:
		$ruby.isAvailable
	@short:
		Check if Ruby scripting support is available
	@syntax:
		$ruby.isAvailable
	@description:
		Returns [b]1[/b] if the Ruby scripting support is available and [b]0[/b] otherwise.
*/

static bool ruby_kvs_fnc_isAvailable(KviKvsModuleFunctionCall * c)
{
#ifdef COMPILE_RUBY_SUPPORT
	g_pRubyCoreModule = g_pModuleManager->getModule("rubycore");
	c->returnValue()->setBoolean(g_pRubyCoreModule ? true : false);
#else  //COMPILE_PERL_SUPPORT
	c->returnValue()->setBoolean(false);
#endif //COMPILE_RUBY_SUPPORT

	return true;
}

static bool ruby_module_init(KviModule * m)
{
	KVSM_REGISTER_SIMPLE_COMMAND(m, "begin", ruby_kvs_cmd_begin);
	KVSM_REGISTER_SIMPLE_COMMAND(m, "destroy", ruby_kvs_cmd_destroy);

	KVSM_REGISTER_FUNCTION(m, "isAvailable", ruby_kvs_fnc_isAvailable);

#ifdef COMPILE_RUBY_SUPPORT
	g_pRubyCoreModule = g_pModuleManager->getModule("rubycore");
#endif //COMPILE_RUBY_SUPPORT

	return true;
}

static bool ruby_module_cleanup(KviModule *)
{
	return true;
}

KVIRC_MODULE(
    "Ruby",
    "1.0.0",
    "Copyright (C) 2016 IceN9ne",
    "Ruby scripting engine",
    ruby_module_init,
    0,
    0,
    ruby_module_cleanup,
    "ruby")
