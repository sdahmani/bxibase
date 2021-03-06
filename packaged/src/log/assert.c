/* -*- coding: utf-8 -*-
 ###############################################################################
 # Author: Pierre Vigneras <pierre.vigneras@bull.net>
 # Created on: May 24, 2013
 # Contributors:
 ###############################################################################
 # Copyright (C) 2012  Bull S. A. S.  -  All rights reserved
 # Bull, Rue Jean Jaures, B.P.68, 78340, Les Clayes-sous-Bois
 # This is not Free or Open Source software.
 # Please contact Bull S. A. S. for details about its license.
 ###############################################################################
 */

#include <stdbool.h>
#include <sysexits.h>

#include "bxi/base/err.h"
#include "bxi/base/mem.h"
#include "bxi/base/str.h"
#include "bxi/base/time.h"
#include "bxi/base/zmq.h"

#include "bxi/base/log.h"



//*********************************************************************************
//********************************** Defines **************************************
//*********************************************************************************

//*********************************************************************************
//********************************** Types ****************************************
//*********************************************************************************


//*********************************************************************************
//********************************** Static Functions  ****************************
//*********************************************************************************


//*********************************************************************************
//********************************** Global Variables  ****************************
//*********************************************************************************


//*********************************************************************************
//********************************** Implementation    ****************************
//*********************************************************************************

void bxilog_assert(bxilog_logger_p logger, bool result,
                   char * file, size_t filelen,
                   const char * func, size_t funclen,
                   int line, char * expr) {
    if (!result) {
        bxierr_p err = bxierr_new(BXIASSERT_CODE,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  "From file %s:%d: assertion %s is false"\
                                  BXIBUG_STD_MSG,
                                  file, line, expr);
        bxilog_exit(EX_SOFTWARE, err, logger, BXILOG_CRITICAL,
                    file, filelen, func, funclen, line);
    }
}


void bxilog_abort_ifko(bxilog_logger_p logger, bxierr_p * err_p,
                       char * file, size_t filelen,
                       const char * func, size_t funclen,
                       int line) {

    if (bxierr_isko(*err_p)) {
        bxilog_exit(EX_SOFTWARE, *err_p, logger, BXILOG_CRITICAL,
                    file, filelen, func, funclen, line);
        bxierr_destroy(err_p);
    }
}
//*********************************************************************************
//********************************** Static Helpers Implementation ****************
//*********************************************************************************
