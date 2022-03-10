/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: taogogo love@taogogo.info                                    |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_geohash.h"
//hash map struct
#include "geohash_lib.c"
//struct StrHashTable tbl = {{0},NULL,NULL,simple_strhash,strcmp};
  zval *cfg_value_uhm;
  zval *cfg_value;

/* If you declare any globals in php_geohash.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(geohash)
*/

/* True global resources - no need for thread safety here */
static int le_geohash;

/* {{{ geohash_methods[]
 */
const zend_function_entry geohash_methods[] = {
	PHP_ME(Geohash, decode, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Geohash, encode, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END	/* Must be the last line in geohash_methods[] */
};
/* }}} */

/* {{{ geohash_module_entry
 */
zend_module_entry geohash_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"Geohash",
	geohash_methods,
	PHP_MINIT(geohash),
	PHP_MSHUTDOWN(geohash),
	PHP_RINIT(geohash),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(geohash),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(geohash),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_GEOHASH
ZEND_GET_MODULE(geohash)
#endif

zend_class_entry *Geohash_ce;

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(geohash)
{
	REGISTER_STRING_CONSTANT("GEOHASH_VERSION", GEOHASH_VERSION, CONST_CS | CONST_PERSISTENT);
    //REGISTER_INI_ENTRIES();
	zend_class_entry Geohash_entry;
	INIT_CLASS_ENTRY(Geohash_entry, "Geohash", geohash_methods);
    Geohash_ce = zend_register_internal_class_ex(&Geohash_entry, NULL);//注册类
    
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(geohash)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(geohash)
{
	return SUCCESS;
}

/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(geohash)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(geohash)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "geohash(php geohash extension) support", "enabled");

	php_info_print_table_row(2, "version", GEOHASH_VERSION);

	php_info_print_table_end();
}
/* }}} */


/* {{{ Geohash::encode
 */
PHP_METHOD(Geohash, decode) {

	char *arg = NULL;
	int arg_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}
	coord_struct result=geohash_decode(arg);
	array_init(return_value);
	add_assoc_double(return_value,"latitude",result.latitude);
	add_assoc_double(return_value,"longitude",result.longitude);
	//zend_printf("gaga");
}

/* }}} */

/* {{{ Geohash::encode
 */
PHP_METHOD(Geohash, encode) {

	double lat,lon;
	long precision=0;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd|l", &lat, &lon, &precision) == FAILURE) {
		return;
	}
	if(lat>90.0 || lat<-90.0){
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Argument #1 range from -90.0 to 90.0");
		return;
	}
	if(lon>180.0 || lon<-180.0){
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Argument #2 range from -180.0 to 180.0");
		return;
	}
	if(precision!=0){
		if(precision<0){
			php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Argument #3 should be a positive number");
			return;
		}
	}else{
		precision=12;
	}
	RETVAL_STRING(geohash_encode(lat,lon,precision));
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
