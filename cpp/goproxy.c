/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_goproxy.h"
#include "php_ini.h"
#include "my_go_capi.h"




/* If you declare any globals in php_goproxy.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(goproxy)
*/

/* True global resources - no need for thread safety here */
static int le_goproxy;
static void* so_handle;
typedef struct myFunc_return (* go_func)(GoString p0);
go_func my_func = NULL;


/* {{{ goproxy_functions[]
 *
 * Every user visible function must have an entry in goproxy_functions[].
 */
const zend_function_entry goproxy_functions[] = {
	PHP_FE(confirm_goproxy_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in goproxy_functions[] */
};
/* }}} */

/* {{{ goproxy_module_entry
 */
zend_module_entry goproxy_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"goproxy",
	goproxy_functions,
	PHP_MINIT(goproxy),
	PHP_MSHUTDOWN(goproxy),
	PHP_RINIT(goproxy),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(goproxy),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(goproxy),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_GOPROXY_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_GOPROXY
ZEND_GET_MODULE(goproxy)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini*/
PHP_INI_BEGIN()
	PHP_INI_ENTRY("cometest.goextpath", "/home/users/yebin02/php-5.4/bin/", PHP_INI_ALL, NULL)
	PHP_INI_ENTRY("cometest.gosoname", "my_go_capi.so", PHP_INI_ALL, NULL)
    // STD_PHP_INI_ENTRY("goproxy.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_goproxy_globals, goproxy_globals)
    // STD_PHP_INI_ENTRY("goproxy.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_goproxy_globals, goproxy_globals)
PHP_INI_END()

/* }}} */

/* {{{ php_goproxy_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_goproxy_init_globals(zend_goproxy_globals *goproxy_globals)
{
	goproxy_globals->global_value = 0;
	goproxy_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(goproxy)
{
	REGISTER_INI_ENTRIES();
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(goproxy)
{
	UNREGISTER_INI_ENTRIES();
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(goproxy)
{
	char go_so_path[256];
	char *goextpath = INI_STR("cometest.goextpath");
	char *gosoname  = INI_ORIG_STR("cometest.gosoname");
	
	strcpy(go_so_path, goextpath);

	if (gosoname != NULL) {
		strcat(go_so_path, gosoname);
	}

	// 加载xuperchain的动态连接库
	so_handle = dlopen(go_so_path, RTLD_LAZY);
    if ( so_handle == NULL ) {
		php_error(E_WARNING, "Failed load my_go_capi.so error");
		return SUCCESS;
    }
    
	char* pszErr = dlerror();
    if(pszErr != NULL) {
        php_error(E_WARNING, pszErr);
		return SUCCESS;
    }

	// init
	void *m_function = dlsym(so_handle, "myFunc");
	my_func = (go_func)m_function;
	
	pszErr  = dlerror();
    if (pszErr != NULL) {
        php_error(E_WARNING, pszErr);
        dlclose(so_handle);
    }

	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(goproxy)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(goproxy)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "goproxy support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_goproxy_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_goproxy_compiled)
{

	struct myFunc_return ret;

	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	if (my_func == NULL) {
		php_error(E_WARNING, "go_func point is NULL");
		RETURN_FALSE;
	}

	GoString params = {arg, arg_len};
	ret = my_func(params);

	char res[128];
	strncpy(res, ret.r0, ret.r1);

	if (ret.r0 != NULL) {
		RETURN_STRINGL(res, ret.r1, 1);
	} else {
		RETURN_FALSE;
	}


	// len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "goproxy", arg);
	// RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
