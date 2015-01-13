/*
    +-----------------------------------------------------------------------------------------+
    |                                                                                         |
    |                               OCILIB - C Driver for Oracle                              |
    |                                                                                         |
    |                                (C Wrapper for Oracle OCI)                               |
    |                                                                                         |
    |                              Website : http://www.ocilib.net                            |
    |                                                                                         |
    |             Copyright (c) 2007-2015 Vincent ROGIER <vince.rogier@ocilib.net>            |
    |                                                                                         |
    +-----------------------------------------------------------------------------------------+
    |                                                                                         |
    |             This library is free software; you can redistribute it and/or               |
    |             modify it under the terms of the GNU Lesser General Public                  |
    |             License as published by the Free Software Foundation; either                |
    |             version 2 of the License, or (at your option) any later version.            |
    |                                                                                         |
    |             This library is distributed in the hope that it will be useful,             |
    |             but WITHOUT ANY WARRANTY; without even the implied warranty of              |
    |             MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU           |
    |             Lesser General Public License for more details.                             |
    |                                                                                         |
    |             You should have received a copy of the GNU Lesser General Public            |
    |             License along with this library; if not, write to the Free                  |
    |             Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.          |
    |                                                                                         |
    +-----------------------------------------------------------------------------------------+
*/

/* --------------------------------------------------------------------------------------------- *
 * $Id: event.c, Vincent Rogier $
 * --------------------------------------------------------------------------------------------- */

#include "ocilib_internal.h"

/* ********************************************************************************************* *
*                             PRIVATE VARIABLES
* ********************************************************************************************* */

static unsigned int VisibilityModeValues[] = { OCI_AMV_IMMEDIATE, OCI_AMV_ON_COMMIT };
static unsigned int EnqueueModeValues[] = { OCI_ASD_BEFORE, OCI_ASD_TOP };

/* ********************************************************************************************* *
 *                            PUBLIC FUNCTIONS
 * ********************************************************************************************* */

/* --------------------------------------------------------------------------------------------- *
 * OCI_EnqueueCreate
 * --------------------------------------------------------------------------------------------- */

OCI_Enqueue * OCI_API OCI_EnqueueCreate
(
    OCI_TypeInfo *typinf,
    const otext  *name
)
{
    OCI_Enqueue *enqueue = NULL;
    boolean res          = TRUE;

    OCI_CHECK_INITIALIZED(NULL);

    OCI_CHECK_PTR(OCI_IPC_TYPE_INFO, typinf, NULL);
    OCI_CHECK_PTR(OCI_IPC_STRING, name, NULL);

    /* allocate enqueue structure */

    enqueue = (OCI_Enqueue *) OCI_MemAlloc(OCI_IPC_ENQUEUE, sizeof(*enqueue), (size_t) 1, TRUE);

    if (enqueue)
    {
        enqueue->typinf = typinf;
        enqueue->name   = ostrdup(name);

        /* allocate enqueue options descriptor */

        res = OCI_SUCCESSFUL(OCI_DescriptorAlloc((dvoid * ) enqueue->typinf->con->env,
                                                 (dvoid **) &enqueue->opth,
                                                 OCI_DTYPE_AQENQ_OPTIONS,
                                                 (size_t) 0, (dvoid **) NULL));
    }
    else
    {
        res = FALSE;
    }

    /* check for failure */

    if (!res)
    {
        OCI_EnqueueFree(enqueue);
        enqueue = NULL;
    }

    return enqueue;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_EnqueueFree
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_EnqueueFree
(
    OCI_Enqueue *enqueue
)
{
    OCI_CHECK_PTR(OCI_IPC_ENQUEUE, enqueue, FALSE);

    /* free OCI descriptor */

    OCI_DescriptorFree((dvoid *) enqueue->opth, OCI_DTYPE_AQENQ_OPTIONS);

    OCI_FREE(enqueue->name);
    OCI_FREE(enqueue);

    return TRUE;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_EnqueuePut
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_EnqueuePut
(
    OCI_Enqueue *enqueue,
    OCI_Msg     *msg
)
{
    boolean res     = TRUE;
    dbtext *dbstr   = NULL;
    int     dbsize  = -1;

    void *payload  = NULL;
    void *ind      = NULL;

    OCI_CHECK_PTR(OCI_IPC_ENQUEUE, enqueue, FALSE);
    OCI_CHECK_PTR(OCI_IPC_MSG, msg, FALSE);

    OCI_CHECK_COMPAT(enqueue->typinf->con, enqueue->typinf->tdo == msg->typinf->tdo, FALSE);

    dbstr = OCI_StringGetOracleString(enqueue->name, &dbsize);

    /* get payload */

    if (OCI_UNKNOWN != enqueue->typinf->typecode)
    {
        if (OCI_IND_NULL != msg->ind)
        {
            payload = msg->obj->handle;
            ind     = msg->obj->tab_ind;
        }
    }
    else
    {
        payload =  msg->payload;
        ind     = &msg->ind;
    }

    /* enqueue message */

    OCI_CALL2
    (
        res, enqueue->typinf->con,

        OCIAQEnq(enqueue->typinf->con->cxt, enqueue->typinf->con->err,
                 (OraText *) dbstr, enqueue->opth, msg->proph, enqueue->typinf->tdo,
                 &payload, &ind, NULL, OCI_DEFAULT);
    )

    OCI_StringReleaseOracleString(dbstr);

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_EnqueueGetVisibility
 * --------------------------------------------------------------------------------------------- */

unsigned int OCI_API OCI_EnqueueGetVisibility
(
    OCI_Enqueue *enqueue
)
{
    boolean res = TRUE;
    ub4 ret     = 0;

    OCI_CHECK_PTR(OCI_IPC_ENQUEUE, enqueue, FALSE);

    OCI_CALL2
    (
        res, enqueue->typinf->con,

        OCIAttrGet((dvoid *) enqueue->opth,
                   (ub4    ) OCI_DTYPE_AQENQ_OPTIONS,
                   (dvoid *) &ret,
                   (ub4   *) NULL,
                   (ub4    ) OCI_ATTR_VISIBILITY,
                   enqueue->typinf->con->err)
    )

    OCI_RESULT(res);

    return (int) ret;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_EnqueueSetVisibility
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_EnqueueSetVisibility
(
    OCI_Enqueue *enqueue,
    unsigned int visibility
)
{
    boolean res = TRUE;
    ub4 value   = (ub4) visibility;

    OCI_CHECK_PTR(OCI_IPC_ENQUEUE, enqueue, FALSE);

    OCI_CHECK_ENUM_VALUE(NULL, NULL, visibility, VisibilityModeValues, OTEXT("Visibility Mode"), FALSE);

    OCI_CALL2
    (
        res, enqueue->typinf->con,

        OCIAttrSet((dvoid *) enqueue->opth,
                   (ub4    ) OCI_DTYPE_AQENQ_OPTIONS,
                   (dvoid *) &value,
                   (ub4    ) 0,
                   (ub4    ) OCI_ATTR_VISIBILITY,
                   enqueue->typinf->con->err)
    )

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_EnqueueGetSequenceDeviation
 * --------------------------------------------------------------------------------------------- */

unsigned int OCI_API OCI_EnqueueGetSequenceDeviation
(
    OCI_Enqueue *enqueue
)
{
    boolean res = TRUE;
    ub4 ret     = 0;

    OCI_CHECK_PTR(OCI_IPC_ENQUEUE, enqueue, FALSE);

    OCI_CALL2
    (
        res, enqueue->typinf->con,

        OCIAttrGet((dvoid *) enqueue->opth,
                   (ub4    ) OCI_DTYPE_AQENQ_OPTIONS,
                   (dvoid *) &ret,
                   (ub4   *) NULL,
                   (ub4    ) OCI_ATTR_SEQUENCE_DEVIATION,
                   enqueue->typinf->con->err)
    )

    OCI_RESULT(res);

    return (int) ret;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_EnqueueSetDeviation
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_EnqueueSetSequenceDeviation
(
    OCI_Enqueue *enqueue,
    unsigned int sequence
)
{
    boolean res = TRUE;
    ub4 value   = (ub4) sequence;

    OCI_CHECK_PTR(OCI_IPC_ENQUEUE, enqueue, FALSE);

    OCI_CHECK_ENUM_VALUE(NULL, NULL, sequence, EnqueueModeValues, OTEXT("Sequence Deviation"), FALSE);

    OCI_CALL2
    (
        res, enqueue->typinf->con,

        OCIAttrSet((dvoid *) enqueue->opth,
                   (ub4    ) OCI_DTYPE_AQENQ_OPTIONS,
                   (dvoid *) &value,
                   (ub4    ) 0,
                   (ub4    ) OCI_ATTR_SEQUENCE_DEVIATION,
                   enqueue->typinf->con->err)
    )

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_EnqueueSetRelativeMsgID
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_EnqueueGetRelativeMsgID
(
    OCI_Enqueue  *enqueue,
    void         *id,
    unsigned int *len
)
{
    boolean res   = TRUE;
    OCIRaw *value = NULL;

    OCI_CHECK_PTR(OCI_IPC_ENQUEUE, enqueue, FALSE);
    OCI_CHECK_PTR(OCI_IPC_VOID,    id,      FALSE);
    OCI_CHECK_PTR(OCI_IPC_VOID,    len,     FALSE);

    OCI_CALL2
    (
        res, enqueue->typinf->con,

        OCIAttrGet((dvoid *) enqueue->opth,
                   (ub4    ) OCI_DTYPE_AQENQ_OPTIONS,
                   (dvoid *) &value,
                   (ub4   *) NULL,
                   (ub4    ) OCI_ATTR_RELATIVE_MSGID,
                   enqueue->typinf->con->err)
    )

    if (value)
    {
        ub4 raw_len = OCIRawSize(enqueue->typinf->con->env, value);

        if (*len > raw_len)
        {
            *len = raw_len;
        }

        memcpy(id, OCIRawPtr(enqueue->typinf->con->env, value), (size_t) (*len));
    }
    else
    {
        *len = 0;
    }

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_EnqueueSetRelativeMsgID
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_EnqueueSetRelativeMsgID
(
    OCI_Enqueue  *enqueue,
    const void   *id,
    unsigned int  len
)
{
    boolean res   = TRUE;
    OCIRaw *value = NULL;

    OCI_CHECK_PTR(OCI_IPC_ENQUEUE, enqueue, FALSE);

    OCI_CALL2
    (
        res, enqueue->typinf->con,

        OCIRawAssignBytes(enqueue->typinf->con->env, enqueue->typinf->con->err,
                          (ub1*) id, (ub4) len, (OCIRaw **) &value)
    )

    OCI_CALL2
    (
        res, enqueue->typinf->con,

        OCIAttrSet((dvoid *) enqueue->opth,
                   (ub4    ) OCI_DTYPE_AQENQ_OPTIONS,
                   (dvoid *) &value,
                   (ub4    ) 0,
                   (ub4    ) OCI_ATTR_RELATIVE_MSGID,
                   enqueue->typinf->con->err)
    )

    OCI_RESULT(res);

    return res;
}

