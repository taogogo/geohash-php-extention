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

#ifndef PHP_GEOHASH_H
#define PHP_GEOHASH_H

extern zend_module_entry geohash_module_entry;
#define phpext_geohash_ptr &geohash_module_entry

#ifdef PHP_WIN32
#	define PHP_GEOHASH_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_GEOHASH_API __attribute__ ((visibility("default")))
#else
#	define PHP_GEOHASH_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(geohash);
PHP_MSHUTDOWN_FUNCTION(geohash);
PHP_RINIT_FUNCTION(geohash);
PHP_RSHUTDOWN_FUNCTION(geohash);
PHP_MINFO_FUNCTION(geohash);

PHP_METHOD(Geohash,encode);
PHP_METHOD(Geohash,decode);


#ifdef ZTS
#define GEOHASH_G(v) TSRMG(geohash_globals_id, zend_geohash_globals *, v)
#else
#define GEOHASH_G(v) (mpl_globals.v)
#endif

#endif	/* PHP_GEOHASH_H */

#define GEOHASH_VERSION "1.0.1"

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
