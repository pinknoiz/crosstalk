/*
Copyright (c) 2012, Broadcom Europe Ltd
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef VC_VCHI_GENCMD_H
#define VC_VCHI_GENCMD_H
#include "vchost_platform_config.h"
#ifdef __circle__
#include <vc4/vchi/vchi.h>
#else
#include "interface/vchi/vchi.h"
#endif
#include "interface/vcos/vcos.h" //for VCHPRE_ abd VCHPOST_ macro's for func declaration

/* Initialise general command service. Returns it's interface number. This initialises
   the host side of the interface, it does not send anything to VideoCore. */

VCHPRE_ int VCHPOST_ vc_gencmd_init(void);

VCHPRE_ void VCHPOST_ vc_vchi_gencmd_init(VCHI_INSTANCE_T initialise_instance, VCHI_CONNECTION_T **connections, uint32_t num_connections );


/* Stop the service from being used. */

VCHPRE_ void VCHPOST_ vc_gencmd_stop(void);

/* Functions to support videocore suspend/resume for cases where vc_gencmd_send expects a response to
 * ensure videocore is not shut down (done internally in vc_gencmd / vc_gencmd_until) */

VCHPRE_ int VCHPOST_ use_gencmd_service(void);
VCHPRE_ int VCHPOST_ release_gencmd_service(void);

/******************************************************************************
Send commands to VideoCore.
These all return 0 for success. They return VC_MSGFIFO_FIFO_FULL if there is
insufficient space for the whole message in the fifo, and none of the message is
sent.
******************************************************************************/

/*  send command to general command serivce */
VCHPRE_ int VCHPOST_ vc_gencmd_send( const char *format, ... );

/*  get resonse from general command serivce */
VCHPRE_ int VCHPOST_ vc_gencmd_read_response(char *response, int maxlen);

/* convenience function to send command and receive the response */
VCHPRE_ int VCHPOST_ vc_gencmd(char *response, int maxlen, const char *format, ...);

/******************************************************************************
Utilities to help interpret the responses.
******************************************************************************/

/* Read the value of a property=value type pair from a string (typically VideoCore's
   response to a general command). Return non-zero if found. */
VCHPRE_ int VCHPOST_ vc_gencmd_string_property(char *text, const char *property, char **value, int *length);

/* Read the numeric value of a property=number field from a response string. Return
   non-zero if found. */
VCHPRE_ int VCHPOST_ vc_gencmd_number_property(char *text, const char *property, int *number);

/* Send a command until the desired response is received, the error message is detected, or the timeout */
VCHPRE_ int VCHPOST_ vc_gencmd_until( char        *cmd,
                                      const char  *property,
                                      char        *value,
                                      const char  *error_string,
                                      int         timeout);


#endif
