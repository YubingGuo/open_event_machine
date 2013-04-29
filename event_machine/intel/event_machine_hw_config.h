/*
 *   Copyright (c) 2012, Nokia Siemens Networks
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions are met:
 *       * Redistributions of source code must retain the above copyright
 *         notice, this list of conditions and the following disclaimer.
 *       * Redistributions in binary form must reproduce the above copyright
 *         notice, this list of conditions and the following disclaimer in the
 *         documentation and/or other materials provided with the distribution.
 *       * Neither the name of Nokia Siemens Networks nor the
 *         names of its contributors may be used to endorse or promote products
 *         derived from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY
 *   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/*  
 *  Copyright (c) 2012 Intel Corporation. All rights reserved.
 *
 *  Reduced priorities from five to four so as to enable use of multiqueue structs
 */


/**
 * @file
 *
 * Event Machine HW dependent constants and definitions.
 * 
 * @note Always use the defined names from this file instead of direct numerical values.
 *       The values are platform/implementation specific.
 */
 
#ifndef EVENT_MACHINE_HW_CONFIG_H
#define EVENT_MACHINE_HW_CONFIG_H



#ifdef __cplusplus
extern "C" {
#endif


#include <event_machine_config.h>



#define EM_INTEL  /**< Event Machine for Intel HW */



/*
 *
 * HW specific constants
 ***************************************
 */


/**
 * Invalid identifiers
 */
#define EM_UNDEF_U64       0xffffffffffffffff
#define EM_UNDEF_U32       0xffffffff
#define EM_UNDEF_U16       0xffff
#define EM_UNDEF_U8        0xff



/**
 * Major event types.
 * 
 */
typedef enum em_event_type_major_e
{
  EM_EVENT_TYPE_UNDEF  = 0,
  EM_EVENT_TYPE_SW     = 1 << 24, /**< event from SW (EO)   */
  EM_EVENT_TYPE_PACKET = 2 << 24, /**< event from packet HW */
  EM_EVENT_TYPE_TIMER  = 3 << 24, /**< event from timer HW  */
  EM_EVENT_TYPE_CRYPTO = 4 << 24  /**< event from crypto HW */

} em_event_type_major_e;


/**
 * Minor event types for the major EM_EVENT_TYPE_SW type.
 * 
 */
typedef enum em_event_type_sw_minor_e
{
  EM_EVENT_TYPE_SW_DEFAULT  = 0

} em_event_type_sw_minor_e;



/**
 * Get major event type.
 * 
 * Event type includes major and minor part. This function
 * returns the major part. It can be compared agains 
 * enumeration em_event_type_major_e.
 * 
 * @param type          Event type
 *
 * @return Major event type
 */
static inline em_event_type_t em_get_type_major(em_event_type_t type)
{
    return (type & 0xFF000000);
}


/**
 * Get minor event type.
 * 
 * Event type includes major and minor part. This function
 * returns the minor part. It can be compared agains 
 * the enumeration specified by the major part.
 * 
 * EM_EVENT_TYPE_SW_DEFAULT is reserved for (SW) events that are
 * generic and directly accessible buffers of memory. 
 * 
 * @param type          Event type
 *
 * @return Minor event type
 */
static inline em_event_type_t em_get_type_minor(em_event_type_t type)
{
    return (type & 0x00FFFFFF);
}






/**
 * Queue types
 */
typedef enum em_queue_type_e
{

  EM_QUEUE_TYPE_UNDEF            = 0,

  EM_QUEUE_TYPE_ATOMIC           = 1,  /**< Application receives events one by one,
                                            non-concurrently to guarantee exclusive processing and ordering */

  EM_QUEUE_TYPE_PARALLEL         = 2,  /**< Application may receive events fully concurrently,
                                            egress event ordering (when processed in parallel) not guaranteed */

  EM_QUEUE_TYPE_PARALLEL_ORDERED = 3   /**< Application may receive events concurrently,
                                            but system takes care of egress order (between two queues) */

} em_queue_type_e;




/**
 * Portable queue priorities.
 * Never directly use the numerical values as they may change from
 * one platform to the next; always use the enum names instead.
 */
#define EM_QUEUE_PRIO_NUM (4) // 4 priority levels used
 
typedef enum em_queue_prio_e
{
  EM_QUEUE_PRIO_UNDEF    = 0xFF, // Undefined
  EM_QUEUE_PRIO_LOWEST   = 0,
  EM_QUEUE_PRIO_LOW      = 0,
  EM_QUEUE_PRIO_NORMAL   = 1,
  EM_QUEUE_PRIO_HIGH     = 2,
  EM_QUEUE_PRIO_HIGHEST  = 3  

} em_queue_prio_e;




/**
 * Static EM queue IDs
 */
#define EM_QUEUE_STATIC_MIN        0
#define EM_QUEUE_STATIC_MAX        0xFF
#define EM_QUEUE_STATIC_NUM        (EM_QUEUE_STATIC_MAX - EM_QUEUE_STATIC_MIN + 1)


/**
 * Maximum number of EM queue groups
 */
#define EM_MAX_QUEUE_GROUPS        64

/**
 * Default queue group for EM
 */
#define EM_QUEUE_GROUP_DEFAULT     (EM_MAX_QUEUE_GROUPS - 1)

/**
 * Max queue group name length
 */
#define EM_QUEUE_GROUP_NAME_LEN    8

/**
 * Define default memory pool
 */
#define EM_POOL_DEFAULT            0

/**
 * Fatal error mask
 */
#define EM_ERROR_FATAL_MASK        0x80000000

/**
 * Test if error is fatal
 */
#define EM_ERROR_IS_FATAL(error)   (EM_ERROR_FATAL_MASK & (error))

/**
 * Set a fatal error code
 */
#define EM_ERROR_SET_FATAL(error)  (EM_ERROR_FATAL_MASK | (error))
#define EM_FATAL(error)             EM_ERROR_SET_FATAL((error)) // Alias, shorter name, backwards compatible



/**
 * Error/Status codes
 */
typedef enum em_status_e
{

    EM_ERR_BAD_CONTEXT      = 1,    /**< Illegal context for this function call */
    EM_ERR_BAD_STATE        = 2,    /**< Illegal (eo, queue, ...) state for this function call */
    EM_ERR_BAD_ID           = 3,    /**< ID not from a valid range */
    EM_ERR_ALLOC_FAILED     = 4,    /**< Resource allocation failed */
    EM_ERR_NOT_FREE         = 5,    /**< Resource already reserved by someone else */
    EM_ERR_NOT_FOUND        = 6,    /**< Resource not found */
    EM_ERR_TOO_LARGE        = 7,    /**< Value over the limit */
    EM_ERR_LIB_FAILED       = 8,    /**< Failure in a library function */
    EM_ERR_NOT_IMPLEMENTED  = 9,    /**< Implementation missing (placeholder) */
    EM_ERR_BAD_POINTER      = 10,   /**< Pointer from bad memory area (e.g. NULL) */

    EM_ERR                          /**< Other error. This is the last error code (for bounds checking). */

} em_status_e;



/**
 * EM Internal (non-public API) functions error scope & mask
 * (see also EM_ESCOPE_API_TYPE and EM_ESCOPE_API_MASK used by the public EM API).
 */
#define EM_ESCOPE_INTERNAL_TYPE     (0xFEu)
#define EM_ESCOPE_INTERNAL_MASK     (EM_ESCOPE_BIT | (EM_ESCOPE_INTERNAL_TYPE << 24))


/**
 * Test if the error scope identifies an EM Internal function
 */
#define EM_ESCOPE_INTERNAL(escope)  (((escope) & EM_ESCOPE_MASK) == EM_ESCOPE_INTERNAL_MASK)


/**
 * EM Internal Error scopes
 * See event_machine_types.h for escope types etc.
 */
 
/* First - for testing*/                                                         
#define EM_ESCOPE_INTERNAL_TEST                   (EM_ESCOPE_INTERNAL_MASK | 0x0000)

/* EM init escopes */
#define EM_ESCOPE_INIT                            (EM_ESCOPE_INTERNAL_MASK | 0x0001)
#define EM_ESCOPE_INIT_CORE                       (EM_ESCOPE_INTERNAL_MASK | 0x0002)
                              
/* EM-API escopes */

/* EM-API Event Group escopes */                  
#define EM_ESCOPE_EVENT_GROUP_DELETE              (EM_ESCOPE_INTERNAL_MASK | 0x0100)
#define EM_ESCOPE_EVENT_GROUP_APPLY               (EM_ESCOPE_INTERNAL_MASK | 0x0101)
#define EM_ESCOPE_EVENT_GROUP_INCREMENT           (EM_ESCOPE_INTERNAL_MASK | 0x0102)
#define EM_ESCOPE_EVENT_GROUP_UPDATE              (EM_ESCOPE_INTERNAL_MASK | 0x0103)
                                                  
                                                  
/* EM-API Queue Groups escopes */                 
#define EM_ESCOPE_QUEUE_GROUP_INIT_GLOBAL         (EM_ESCOPE_INTERNAL_MASK | 0x0200)
#define EM_ESCOPE_QUEUE_GROUP_INIT_LOCAL          (EM_ESCOPE_INTERNAL_MASK | 0x0201)
#define EM_ESCOPE_QUEUE_GROUP_DEFAULT             (EM_ESCOPE_INTERNAL_MASK | 0x0206)
                                                  
/* EM Packet I/O escopes */                       
#define EM_ESCOPE_PACKETIO_INTEL_ETH_INIT         (EM_ESCOPE_INTERNAL_MASK | 0x0300)
#define EM_ESCOPE_PACKETIO_INIT_PACKET_Q_HASH     (EM_ESCOPE_INTERNAL_MASK | 0x0301)
#define EM_ESCOPE_PACKETIO_ETH_TX_PACKET_ORDERED  (EM_ESCOPE_INTERNAL_MASK | 0x0302)
#define EM_ESCOPE_PACKETIO_ETH_TX_PACKET_BURST    (EM_ESCOPE_INTERNAL_MASK | 0x0303)
#define EM_ESCOPE_PACKETIO_ADD_IO_QUEUE           (EM_ESCOPE_INTERNAL_MASK | 0x0304)
#define EM_ESCOPE_PACKETIO_REM_IO_QUEUE           (EM_ESCOPE_INTERNAL_MASK | 0x0305)
                                                  
/* Other escopes - internal */                               
#define EM_ESCOPE_INIT_GLOBAL                     (EM_ESCOPE_INTERNAL_MASK | 0x0400)
#define EM_ESCOPE_EO_ALLOC                        (EM_ESCOPE_INTERNAL_MASK | 0x0401)
#define EM_ESCOPE_QUEUE_ALLOC                     (EM_ESCOPE_INTERNAL_MASK | 0x0402)
#define EM_ESCOPE_QUEUE_INIT                      (EM_ESCOPE_INTERNAL_MASK | 0x0403)
#define EM_ESCOPE_QUEUE_STATE_CHANGE              (EM_ESCOPE_INTERNAL_MASK | 0x0404)
#define EM_ESCOPE_EO_START_LOCAL__DONE_CALLBACK   (EM_ESCOPE_INTERNAL_MASK | 0x0405)
#define EM_ESCOPE_EO_STOP_LOCAL__DONE_CALLBACK    (EM_ESCOPE_INTERNAL_MASK | 0x0406)
#define EM_ESCOPE_EM_INIT_LOCAL                   (EM_ESCOPE_INTERNAL_MASK | 0x0407)
#define EM_ESCOPE_EO_LOCAL_FUNC_CALL_REQ          (EM_ESCOPE_INTERNAL_MASK | 0x0408)
                                                  
#define EM_ESCOPE_SCHED_QUEUE_INIT                (EM_ESCOPE_INTERNAL_MASK | 0x0500)
#define EM_ESCOPE_SCHEDULE_ATOMIC                 (EM_ESCOPE_INTERNAL_MASK | 0x0501)
#define EM_ESCOPE_SCHEDULE_PARALLEL               (EM_ESCOPE_INTERNAL_MASK | 0x0502)
#define EM_ESCOPE_SCHEDULE_PARALLEL_ORD           (EM_ESCOPE_INTERNAL_MASK | 0x0503)
#define EM_ESCOPE_PARALLEL_ORDERED_MAINTAIN_ORDER (EM_ESCOPE_INTERNAL_MASK | 0x0504)
#define EM_ESCOPE_SCHED_MASKS_ADD                 (EM_ESCOPE_INTERNAL_MASK | 0x0505)
#define EM_ESCOPE_SCHED_MASKS_REM                 (EM_ESCOPE_INTERNAL_MASK | 0x0506)
#define EM_ESCOPE_SEND_ATOMIC                     (EM_ESCOPE_INTERNAL_MASK | 0x0507)
#define EM_ESCOPE_SEND_PARALLEL                   (EM_ESCOPE_INTERNAL_MASK | 0x0508)
#define EM_ESCOPE_SEND_PARALLEL_ORD               (EM_ESCOPE_INTERNAL_MASK | 0x0509)
#define EM_ESCOPE_SEND_FROM_PARALLEL_ORD          (EM_ESCOPE_INTERNAL_MASK | 0x050A)
#define EM_ESCOPE_DISPATCH                        (EM_ESCOPE_INTERNAL_MASK | 0x050B)
#define EM_ESCOPE_DIRECT_DISPATCH__ATOMIC         (EM_ESCOPE_INTERNAL_MASK | 0x050C)
#define EM_ESCOPE_DIRECT_DISPATCH__PARALLEL       (EM_ESCOPE_INTERNAL_MASK | 0x050D)
#define EM_ESCOPE_DIRECT_DISPATCH__PARALLEL_ORD   (EM_ESCOPE_INTERNAL_MASK | 0x050E)

#define EM_ESCOPE_INTERNAL_NOTIF                  (EM_ESCOPE_INTERNAL_MASK | 0x0600)
#define EM_ESCOPE_INTERNAL_EVENT_RECEIVE_FUNC     (EM_ESCOPE_INTERNAL_MASK | 0x0601)
#define EM_ESCOPE_EVENT_INTERNAL_DONE             (EM_ESCOPE_INTERNAL_MASK | 0x0602)
#define EM_ESCOPE_EVENT_INTERNAL_LOCAL_FUNC_CALL  (EM_ESCOPE_INTERNAL_MASK | 0x0603)
#define EM_ESCOPE_INTERNAL_DONE_W_NOTIF_REQ       (EM_ESCOPE_INTERNAL_MASK | 0x0604)


#ifdef __cplusplus
}
#endif



#endif


