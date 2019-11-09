#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ESUCCESS 0
#define TRUE     1
#define FALSE    0

#define __CHK_FN__             { int _chk_hr = ESUCCESS;
#define CHK(_chk_hr_)          if ((_chk_hr = (_chk_hr_))) goto CHK_ERROR
#define CHKPRINT(_chk_hr_)     if ((_chk_hr = (_chk_hr_))) goto CHK_ERROR_PRINT
#define CHKEXIT(_chk_hr_)      if ((_chk_hr = (_chk_hr_))) goto CHK_EXIT
#define CHKB(b, _chk_hr_)      CHK((b) * _chk_hr_)
#define CHKBPRINT(b, _chk_hr_) CHKPRINT((b) * _chk_hr_)
#define CHKBEXIT(b, _chk_hr_)  CHKEXIT((b) * _chk_hr_)
#define CHK_EMPTY_ERROR_FN     { }

#define CHK_SUCCESS(_error_fn) \
    CHK_RETURN(_chk_hr, _error_fn)
#define CHK_VALUE(_value, _error_fn) \
    CHK_RETURN(_value, _error_fn)
#define CHK_VOID(_error_fn) \
    CHK_RETURN(, _error_fn)

#define CHK_RETURN(_default_return, _error_fn) \
    _default_return; \
    CHK_EXIT: \
        exit(EXIT_FAILURE); \
    CHK_ERROR_PRINT: \
        fprintf(stderr, "Error in %s:%d (%d %s)\n", \
                              __FILE__, __LINE__, _chk_hr, strerror(_chk_hr)); \
    CHK_ERROR: \
        _error_fn \
        errno = (errno == ESUCCESS) ? _chk_hr : errno; \
        return _default_return; }

#ifdef __cplusplus
}
#endif

