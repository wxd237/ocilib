/*
   +----------------------------------------------------------------------+   
   |                                                                      |
   |                     OCILIB - C Driver for Oracle                     |
   |                                                                      |
   |                      (C Wrapper for Oracle OCI)                      |
   |                                                                      |
   +----------------------------------------------------------------------+
   |                      Website : http://ocilib.net                     |
   +----------------------------------------------------------------------+
   |               Copyright (c) 2007-2008 Vincent ROGIER                 |
   +----------------------------------------------------------------------+
   | This library is free software; you can redistribute it and/or        |
   | modify it under the terms of the GNU Library General Public          |
   | License as published by the Free Software Foundation; either         |
   | version 2 of the License, or (at your option) any later version.     |
   |                                                                      |
   | This library is distributed in the hope that it will be useful,      |
   | but WITHOUT ANY WARRANTY; without even the implied warranty of       |
   | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    |
   | Library General Public License for more details.                     |
   |                                                                      |
   | You should have received a copy of the GNU Library General Public    |
   | License along with this library; if not, write to the Free           |
   | Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.   |
   +----------------------------------------------------------------------+
   |          Author: Vincent ROGIER <vince.rogier@gmail.com>             |
   +----------------------------------------------------------------------+ 
*/

/* ------------------------------------------------------------------------ *
 * $Id: ref.c, v 3.1.0 2008/10/26 07:50 Vince $
 * ------------------------------------------------------------------------ */

#include "ocilib_internal.h"

/* ************************************************************************ *
 *                             PRIVATE FUNCTIONS
 * ************************************************************************ */

/* ------------------------------------------------------------------------ *
 * OCI_RefInit
 * ------------------------------------------------------------------------ */

OCI_Ref * OCI_RefInit(OCI_Connection *con, OCI_Schema *schema, OCI_Ref **pref, 
                      void *handle)
{
    boolean res   = TRUE;
    OCI_Ref * ref = NULL;
    
    OCI_CHECK(pref == NULL, NULL);

    if (*pref == NULL)
        *pref = (OCI_Ref *) OCI_MemAlloc(OCI_IPC_REF, sizeof(*ref), 1, TRUE);

    if (*pref != NULL)
    {
        ref = *pref;

        ref->handle = handle;
        ref->con    = con;
        ref->nty    = schema;

        if (ref->handle == NULL)
        {
            /* allocates handle for non fetched object */

            ref->hstate = OCI_OBJECT_ALLOCATED;

            OCI_CALL2
            (
                res, ref->con, 
                
                OCI_ObjectNew(OCILib.env,  con->err, con->cxt, 
                              (OCITypeCode) SQLT_REF, 
                              (OCIType*) NULL,
                              (dvoid *) NULL, 
                              (OCIDuration) OCI_DURATION_SESSION,
                              (boolean) FALSE, 
                              (dvoid **) &ref->handle)
           )
        }
        else
        {
            ref->hstate = OCI_OBJECT_FETCHED_CLEAN;
            
            OCI_RefUnpin(ref);
        }
    }

    /* check for failure */

    if (res == FALSE)
    {
        OCI_RefFree(ref);
        ref = NULL;
    }

    return ref;
}

/* ------------------------------------------------------------------------ *
 * OCI_RefPin
 * ------------------------------------------------------------------------ */

boolean OCI_RefPin(OCI_Ref *ref)
{
    boolean res      = TRUE;
    void *obj_handle = NULL;

    OCI_CHECK(ref == NULL, FALSE);

    OCI_RefUnpin(ref);

    OCI_CALL2
    (
        res, ref->con, 
        
        OCIObjectPin(OCILib.env, ref->con->err, ref->handle,
                     (OCIComplexObject *) 0, OCI_PIN_ANY, OCI_DURATION_SESSION,
                     OCI_LOCK_NONE, &obj_handle)
    )

    if (res == TRUE)
    {
        OCI_Object *obj = NULL;

        if (res == TRUE)
        {
            obj =  OCI_ObjectInit(ref->con, (OCI_Object **) &ref->obj,
                                  obj_handle, ref->nty, NULL, -1);
        }

        if (obj != NULL)
            ref->pinned = TRUE;
        else
            res = FALSE;
    }

    return res;
}

/* ------------------------------------------------------------------------ *
 * OCI_RefUnpin
 * ------------------------------------------------------------------------ */

boolean OCI_RefUnpin(OCI_Ref *ref)
{
    boolean res = TRUE;

    OCI_CHECK(ref == NULL, FALSE);

    if (ref->pinned == TRUE)
    {
        OCI_CALL2
        (
            res, ref->con, 
            
            OCIObjectUnpin(OCILib.env, ref->con->err, ref->obj->handle)
        )

        ref->pinned = FALSE;
    }

    if (ref->obj != NULL)
    {
        ref->obj->hstate = OCI_OBJECT_FETCHED_DIRTY;
        OCI_ObjectFree(ref->obj);
        ref->obj = NULL;
    }

    return res;           
}

/* ************************************************************************ *
 *                            PUBLIC FUNCTIONS
 * ************************************************************************ */

/* ------------------------------------------------------------------------ *
 * OCI_RefCreate
 * ------------------------------------------------------------------------ */

OCI_Ref * OCI_API OCI_RefCreate(OCI_Connection *con, OCI_Schema *schema)
{
    OCI_Ref *ref = NULL;
    
    OCI_CHECK_INITIALIZED(NULL);

    OCI_CHECK_PTR(OCI_IPC_CONNECTION, con, NULL);
    OCI_CHECK_PTR(OCI_IPC_SCHEMA, schema, NULL);

    ref = OCI_RefInit(con, schema, &ref, NULL);

    OCI_RESULT(ref != NULL);

    return ref;
}

/* ------------------------------------------------------------------------ *
 * OCI_RefFree
 * ------------------------------------------------------------------------ */

boolean OCI_API OCI_RefFree(OCI_Ref *ref)
{
    OCI_CHECK_PTR(OCI_IPC_REF, ref, FALSE);

    OCI_CHECK_OBJECT_FETCHED(ref, FALSE);

    OCI_RefUnpin(ref);

    if (ref->hstate == OCI_OBJECT_ALLOCATED)
    {
        OCI_OCIObjectFree(OCILib.env, ref->con->err,  ref->handle, 
                          OCI_OBJECTFREE_NONULL);
    }

    OCI_FREE(ref);

    OCI_RESULT(TRUE);

    return TRUE;
}

/* ------------------------------------------------------------------------ *
 * OCI_RefGetObject
 * ------------------------------------------------------------------------ */

OCI_Object * OCI_API OCI_RefGetObject(OCI_Ref *ref)
{
    OCI_Object *obj = NULL;

    if (OCI_RefIsNull(ref) == FALSE)
    {
        boolean res = TRUE;

        res = OCI_RefPin(ref);

        OCI_RESULT(res);
    
        obj = ref->obj;
    }

	return obj;
}

/* ------------------------------------------------------------------------ *
 * OCI_RefAssign
 * ------------------------------------------------------------------------ */

boolean OCI_API OCI_RefAssign(OCI_Ref *ref, OCI_Ref *ref_src)
{
    boolean res = TRUE;

    OCI_CHECK_PTR(OCI_IPC_REF, ref,     FALSE);
    OCI_CHECK_PTR(OCI_IPC_REF, ref_src, FALSE);

    OCI_CHECK_COMPAT(ref->con, ref->nty == ref_src->nty, FALSE);

    OCI_CALL2
    (
        res, ref->con, 

        OCIRefAssign(OCILib.env, ref->con->err, ref_src->handle, &ref->handle)
    )

    if (res == TRUE)
    {
        if (ref->obj != NULL)
        {
            OCI_ObjectFree(ref->obj);
            ref->obj = NULL;
        }

        ref->nty    = ref_src->nty;
        ref->pinned = ref_src->pinned;

    }


    OCI_RESULT(res);

    return res;
}

/* ------------------------------------------------------------------------ *
 * OCI_RefIsNull
 * ------------------------------------------------------------------------ */

boolean OCI_API OCI_RefIsNull(OCI_Ref *ref)
{
    OCI_CHECK_PTR(OCI_IPC_REF, ref, TRUE);

    OCI_RESULT(TRUE);

    return OCIRefIsNull(OCILib.env, ref->handle);
}

/* ------------------------------------------------------------------------ *
 * OCI_RefSetNull
 * ------------------------------------------------------------------------ */

boolean OCI_API OCI_RefSetNull(OCI_Ref *ref)
{
    boolean res = TRUE;

    OCI_CHECK_PTR(OCI_IPC_REF, ref, FALSE);

    res = OCI_RefUnpin(ref);

    if (res == TRUE)
    {
        OCIRefClear(OCILib.env, ref->handle);

        if (ref->obj != NULL)
        {
            OCI_ObjectFree(ref->obj);
            ref->obj = NULL;
        }
    }

    OCI_RESULT(res);
   
    return res;
}

/* ------------------------------------------------------------------------ *
 * OCI_RefToText
 * ------------------------------------------------------------------------ */

boolean OCI_API OCI_RefToText(OCI_Ref *ref, int size, mtext *str)
{
    boolean res = TRUE;
    void *ostr  = NULL;
    int osize   = size * sizeof(mtext);

    OCI_CHECK_PTR(OCI_IPC_REF, ref, FALSE);
    OCI_CHECK_PTR(OCI_IPC_STRING, str, FALSE);
 
    /* init output buffer in case of OCI failure */
    
    str[0] = 0;

    ostr = OCI_GetInputMetaString(str, &osize);
 
    OCI_CALL2
    (
        res, ref->con,
        
        OCIRefToHex((dvoid *) OCILib.env, ref->con->err, ref->handle, 
                    (OraText *) ostr, (ub4 *) &osize)
    )
 
    OCI_GetOutputMetaString(ostr, str, &osize);
    OCI_ReleaseMetaString(ostr);

    /* set null string terminator */

    str[osize/sizeof(mtext)] = 0;

    OCI_RESULT(res);
   
    return res;
}

/* ------------------------------------------------------------------------ *
 * OCI_RefGetHexSize
 * ------------------------------------------------------------------------ */

unsigned int OCI_API OCI_RefGetHexSize(OCI_Ref *ref)
{
    ub4 size = 0;

    OCI_CHECK_PTR(OCI_IPC_REF, ref, 0);

    size = OCIRefHexSize(OCILib.env, (const OCIRef *) ref->handle);

    size /= sizeof(mtext);

    OCI_RESULT(TRUE);

    return (unsigned int) size;
}

/* ------------------------------------------------------------------------ *
 * OCI_CollRefSchema
 * ------------------------------------------------------------------------ */

OCI_Schema * OCI_API OCI_RefGetSchema(OCI_Ref *ref)
{
    OCI_CHECK_PTR(OCI_IPC_REF, ref, NULL);

    OCI_RESULT(TRUE);

    return ref->nty;
}


