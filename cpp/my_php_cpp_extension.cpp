#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef __cplusplus 
extern "C" {
#endif
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#ifndef __cplusplus 
}
#endif

#include "my_php_cpp_extension.h"


static zend_class_entry * cgocppphp_class_entry_ptr;

static zend_function_entry cgocppphp_functions[] = {
	PHP_ME(CgoCppPhp, test, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{NULL, NULL, NULL}
};

zend_module_entry xchain_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"cgocppphp",
	NULL,
	PHP_MINIT(cgocppphp),
	PHP_MSHUTDOWN(cgocppphp),
	PHP_RINIT(cgocppphp),		
	PHP_RSHUTDOWN(cgocppphp),
	PHP_MINFO(cgocppphp),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_XCHAIN_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_CGOCPPPHP
ZEND_GET_MODULE(cgocppphp)
#endif


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(cgocppphp)
{
	/* 注册类 */
	zend_class_entry bd_xchain_class_entry;
	INIT_CLASS_ENTRY(bd_xchain_class_entry, CgoCppPhp, cgocppphp_functions);
	cgocppphp_class_entry_ptr = zend_register_internal_class(&bd_xchain_class_entry TSRMLS_CC);

	php_error(E_WARNING, "PHP_MINIT_FUNCTION(xchain) end");
	return SUCCESS;

}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(cgocppphp)
{
	if (g_xchain != NULL && g_xchain->xchain_handle != NULL) {
		php_error(E_WARNING, "PHP_MSHUTDOWN_FUNCTION(xchain) end2");
		dlclose(g_xchain->xchain_handle);
	}
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(cgocppphp)
{
	// 加载xuperchain的动态连接库
	void* so_handle = dlopen("my_go_capi.so", RTLD_LAZY);
    if ( so_handle == NULL ) {
		php_error(E_WARNING, "Failed load my_go_capi.so error");
		return SUCCESS;
    }
    char* pszErr = dlerror();
    if(pszErr != NULL) {
        php_error(E_WARNING, pszErr);
		return SUCCESS;
    }

	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(cgocppphp)
{
	php_error(E_WARNING, "PHP_RSHUTDOWN_FUNCTION(xchain)");  
	return SUCCESS;
}
/* }}} */


PHP_METHOD(CgoCppPhp, test)
{	
	
}


/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(cgocppphp)
{
	php_error(E_WARNING, "PHP_MINFO_FUNCTION(xchain)");
	php_info_print_table_start();
	php_info_print_table_header(2, "cgocppphp support", "enabled");
	php_info_print_table_header(2, "Version", PHP_CGOCPPPHP_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__);
	php_info_print_table_end();

}
/* }}} */