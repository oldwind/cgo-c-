#include "my_go_cpi.h"
#include <string>

#if ECS == gnu
#include <cstring>
#define ECString string
using namespace std;
#else
#include <bstring.h>
#define ECString string
#endif


#ifndef PHP_CGOCPPPHP_H
#define PHP_CGOCPPPHP_H

extern zend_module_entry cgocppphp_module_entry;
#define phpext_example_ptr &cgocppphp_module_entry

#define PHP_CGOCPPPHP_VERSION "1.0.0.1" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_CGOCPPPHP_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_CGOCPPPHP_API __attribute__ ((visibility("default")))
#else
#	define PHP_CGOCPPPHP_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(cgocppphp);
PHP_MSHUTDOWN_FUNCTION(cgocppphp);
PHP_RINIT_FUNCTION(cgocppphp);
PHP_RSHUTDOWN_FUNCTION(cgocppphp);
PHP_MINFO_FUNCTION(cgocppphp);


// CgoCppPhp 类的方法定义
static PHP_METHOD(CgoCppPhp, test);


#ifdef ZTS
#define CGOCPPPHP_G(v) TSRMG(cgocppphp_globals_id, zend_cgocppphp_globals *, v)
#else
#define CGOCPPPHP_G(v) (cgocppphp_globals.v)
#endif

#endif	/* PHP_EXAMPLE_H */


/* {{{
	定义动态链接库提供的方法类型
*/
typedef struct myFunc_return (*myFunc)(GoString p0); // 
/* }}} */


// namespace cgoCppTest {

// class Xchain {

// public:
//     string my_str;

// public:
//   ~Xchain();

// };
// }