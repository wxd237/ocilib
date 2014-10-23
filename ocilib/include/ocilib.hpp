/*
    +-----------------------------------------------------------------------------------------+
    |                                                                                         |
    |                                                                                         |
    |                          OCILIB ++ - C++ wrapper around OCILIB                          |
    |                                                                                         |
    |                                (C Wrapper for Oracle OCI)                               |
    |                                                                                         |
    |                              Website : http://www.ocilib.net                            |
    |                                                                                         |
    |             Copyright (c) 2007-2014 Vincent ROGIER <vince.rogier@ocilib.net>            |
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

    +-----------------------------------------------------------------------------------------+
    |                                     IMPORTANT NOTICE                                    |
    +-----------------------------------------------------------------------------------------+
    |                                                                                         |
    |            This C++ header defines C++ wrapper classes around the OCILIB C API          |
    |            It requires a compatible version of OCILIB                                   |
    +-----------------------------------------------------------------------------------------+

 */

/* --------------------------------------------------------------------------------------------- *
 * $Id: ocilib.hpp, Vincent Rogier $
 * --------------------------------------------------------------------------------------------- */

#ifndef OCILIBCPP_H_INCLUDED
#define OCILIBCPP_H_INCLUDED

/* includes */

#include <string>
#include <list>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

#include "ocilib.h"

/**
 * @namespace ocilib
 * @brief OCILIB ++ Namespace
 *
 */
namespace ocilib
{

/**
 * @defgroup OcilibCppApi C++ API
 * @{
 */

/**
 * @defgroup OcilibCppApiOverview Overview
 * @{
 * OCILIB++ is a C++ API for Oracle built on top of the C OCILIB API:
 *  - Full C API ported  to C++
 *  - Implemented as a small set of header files, no library compilation needed
 *  - Based on STL paradigms (templates, stack objects, STL classes)
 *  - Based on design patterns (RAII, delegation, reference counting, smart pointers, proxies, singleton)
 *  - No dynamic object allocation
 *  - The only dependences are : STL and OCILIB C API
 *
 * API usage is very simple, based on stack objects wrapping OCILIB handles using reference counting.
 * OCILIB handles are automatically allocated internally by C++ objects constructors or methods.
 * They are also automatically freed when the last C++ object referencing it goes out of scope.
 * Dynamic memory allocation is not required at all.
 * OCILIB++ allows simple and safe usage of Oracle client wihtout the worries of memory leakages.
 * Using stack objects also makes error handling easier and program logic more robust
 *
 * @par Exception model
 * Any failure occuring within an OCILIB C API call will throw a ocilib::Exception
 * For conformance reasons, this class derives from std::Exception
 *
 * @note
 *  - OCILIB++ wraps the whole OCILIB C API.
 *  - Each C OCILIB object handle has its C++ class counter part.
 *  - The whole OCILIB C Documentation (concepts, use cases, features and functionalities) is still valid for OCILIB++
 *
 * @}
 */

/**
*
* @}
*/

/**
 * @typedef ocilib::ostring
 *
 * @brief
 * string class wrapping the OCILIB otext * type and OTEXT() macros ( see @ref OcilibCApiSupportedCharsets )
 *
 * @note
 * - for ANSI builds, ocilib::ostring is equivalent to std::string
 * - for UNICODE builds, ocilib::ostring is equivalent to std::wstring
 *
 */
typedef std::basic_string<otext, std::char_traits<otext>, std::allocator<otext> > ostring;

/**
 * @typedef ocilib::AnyPointer
 *
 * @brief
 * Alias for the generic void pointer
 *
 */
typedef void * AnyPointer;

/**
* @typedef ocilib::Raw
*
* @brief
* C++ counterpart of SQL RAW datatype
*
*/
typedef std::vector<unsigned char> Raw;

/**
 * @typedef ocilib::UnknownHandle
 *
 * @brief
 * Alias used for manipulating unknown handle types
 *
 */
typedef const void * UnknownHandle;

/**
 * @typedef ocilib::MutexHandle
 *
 * @brief
 * Alias for an OCI_Mutex pointer
 *
 */
typedef OCI_Mutex *  MutexHandle ;

/**
 * @typedef ocilib::ThreadHandle
 *
 * @brief
 * Alias for an OCI_Thread pointer
 *
 */
typedef OCI_Thread * ThreadHandle;

/**
 * @typedef ocilib::CallbackPointer
 *
 * @brief
 * Alias used for storing user callback method pointers
 *
 */
typedef void * CallbackPointer;

}

/* Including core classes  */

#include "ocilib_core.hpp"

/* Defining public classes  */

namespace ocilib
{


/**
* @brief
* Data type enumerated values
*
*/
enum DataTypeValues
{
	/** NUMERIC */
	TypeNumeric = OCI_CDT_NUMERIC,
	/** DATE */
	TypeDate = OCI_CDT_DATETIME,
	/** TEXT */
	TypeString = OCI_CDT_TEXT,
	/** LONG / LONG RAW */
	TypeLong = OCI_CDT_LONG,
	/** SQL CURSOR */
	TypeStatement = OCI_CDT_CURSOR,
	/** CLOB or BLOB */
	TypeLob = OCI_CDT_LOB,
	/** FILE */
	TypeFile = OCI_CDT_FILE,
	/** TIMESTAMP */
	TypeTimestamp = OCI_CDT_TIMESTAMP,
	/** INTERVAL */
	TypeInterval = OCI_CDT_INTERVAL,
	/** RAW */
	TypeRaw = OCI_CDT_RAW,
	/** Object type */
	TypeObject = OCI_CDT_OBJECT,
	/** Collection  */
	TypeCollection = OCI_CDT_COLLECTION,
	/** Object REF */
	TypeReference = OCI_CDT_REF
};

/**
* @brief
* Column data type
*
* Possible values are DataTypeValues
*
*/
typedef Enum<DataTypeValues> DataType;

/**
* @brief
* Numeric type enumerated values
*
*/
enum NumericTypeValues
{
	/** Signed short */
	NumericShort = OCI_NUM_SHORT,
	/** Signed Integer */
	NumericInt = OCI_NUM_INT,
	/** Signed Big Integer (Integer or Long Integer depending on the compiler )*/
	NumericBigInt = OCI_NUM_BIGINT,
	/** Unsigned short */
	NumericUnsignedShort = OCI_NUM_USHORT,
	/** Unsigned Integer */
	NumericUnsignedInt = OCI_NUM_UINT,
	/** Unsigned Big Integer (Integer or Long Integer depending on the compiler )*/
	NumericUnsignedBigInt = OCI_NUM_BIGUINT,
	/** Double  */
	NumericDouble = OCI_NUM_DOUBLE,
	/** Float */
	NumericFloat = OCI_NUM_FLOAT
};

/**
* @brief
* Numeric data type
*
* Possible values are NumericTypeValues
*
*/
typedef Enum<NumericTypeValues> NumericType;

/**
 *
 * @brief
 * Exception class handling all OCILIB erors
 *
 * This class wraps the OCILIB object handle OCI_Error and its related methods
 *
 */
class Exception : public HandleHolder<OCI_Error *>, public std::exception
{
    friend void Check();
    friend class Statement;

public:

	/**
	* @brief
	* Exception type enumerated values
	*
	*/
	enum ExceptionTypeValues
	{
        /** Unknown exception type */
        Unknown = OCI_UNKNOWN,
        /** Exception caused by an Oracle error */
        OracleError  = OCI_ERR_ORACLE,
        /** Exception caused by an Ocilib error */
        OcilibError = OCI_ERR_OCILIB,
        /** Exception caused by an Oracle Warning */
        OracleWarning = OCI_ERR_WARNING
    };

	/**
	* @brief
	* Type of Exception
	*
	* Possible values are Exception::ExceptionTypeValues
	*
	*/
	typedef Enum<ExceptionTypeValues>  ExceptionType;

	/**
     * @brief
     * Retrieve the error message
     *
     */
    ostring GetMessage() const;

    /**
     *
     * @brief
     * Return the Exception type
     *
     */
    ExceptionType GetType() const;

    /**
     * @brief
     * Return the Oracle error code
     *
     */
    int GetOracleErrorCode() const;

    /**
     * @brief
     * Return the OCILIB error code
     *
     */
    int GetInternalErrorCode() const;

    /**
     * @brief
     * Return the statement within the error occurred
     *
     */
    Statement GetStatement() const;

    /**
     * @brief
     * Return the connection within the error occurred
     *
     */
    Connection GetConnection() const;

    /**
     * @brief
     * Return the row index which caused an error during statement execution
     *
     * @warning
     * Row index start at 1.
     *
     * @return
     *  - 0 if the error is not related to array DML
     *  - otherwise the index of the given row which caused the error
     *
     */
    unsigned int GetRow() const;

	/**
	* @brief
	* Override the std::exception::what() method
	*
	* @return
	*  - The same content as GetMessage() but as using const char * type
	*
	*/
	virtual const char *what() const throw();

	/**
	* @brief
	* Virtual destructor required for deriving from std::exception
	*
	*/
	virtual ~Exception() throw ();

private:

    Exception();
    Exception(OCI_Error *err);

	std::string _what;
};

/**
 * @brief
 * Static class in charge of library initialization / cleanup
 *
 */
class Environment
{
    friend class Connection;
    friend class Subscription;
    friend class Dequeue;
    template<class THandleType>
    friend class HandleHolder;

public:

	/**
	* @brief
	* HA Event sources enumerated values
	*
	*/
	enum HAEventSourceValues
	{
		/** The event has been generated by an Oracle instance */
		SourceInstance = OCI_HES_INSTANCE,
		/** The event has been generated by an Oracle dabatase */
		SourceDatabase = OCI_HES_DATABASE,
		/** The event has been generated by an Oracle Node */
		SourceNode = OCI_HES_NODE,
		/** The event has been generated by an Oracle service */
		SourceService = OCI_HES_SERVICE,
		/** The event has been generated by an Oracle service memeber */
		SourceServiceMember = OCI_HES_SERVICE_MEMBER,
		/** The event has been generated by an Oracle ASM instance */
		SourceASMInstance = OCI_HES_ASM_INSTANCE,
		/** The event has been generated at service pre-connecting stage */
		SourcePreConnect = OCI_HES_PRECONNECT
	};

	/**
	* @brief
	* Source of HA events
	*
	* Possible values are Environment::HAEventSourceValues
	*
	*/
	typedef Enum<HAEventSourceValues>  HAEventSource;

	/**
	* @brief
	* HA Event types enumerated values
	*
	*/
	enum HAEventTypeValues
	{
		/** The source of the event is down */
		EventDown = OCI_HET_DOWN,
		/** The source of the event is up (not generated yet by Oracle) */
		EventUp = OCI_HET_UP
	};

	/**
	* @brief
	* Type of HA events
	*
	* Possible values are Environment::HAEventTypeValues
	*
	*/
	typedef Enum<HAEventTypeValues>  HAEventType;

	/**
	* @brief
	* Environment Flags enumerated values
	*
	*/
	enum EnvironmentFlagsValues
	{
		/** Default mode */
		Default = OCI_ENV_DEFAULT,
		/** Enable support for multithreading */
		Threaded  = OCI_ENV_THREADED,
		/** Enable support for events related to subscriptions, HA and AQ notifications */
		Events = OCI_ENV_EVENTS
	};

	/**
	* @brief
	* Environment Flags
	*
	* Possible values are Environment::EnvironmentFlagsValues
	*
	*/
	typedef Flags<EnvironmentFlagsValues> EnvironmentFlags;

	/**
	* @brief
	* OCI libraries import mode enumerated values
	*
	*/
	enum ImportModeValues
	{
		/** OCI libraires are linked at compile time */
		ImportLinkage = OCI_IMPORT_MODE_LINKAGE,
		/** OCI libraires are dynamically loaded at runtime */
		ImportRuntime  = OCI_IMPORT_MODE_RUNTIME
	};

	/**
	* @brief
	* OCI libraries import mode
	*
	* Possible values are Environment::ImportMode
	*
	*/
	typedef Enum<ImportModeValues> ImportMode;

	/**
	* @brief
	* Charset mode enumerated values
	*
	*/
	enum CharsetModeValues
	{
		/** Environment is Ansi string or UTF8 string */
		CharsetAnsi = OCI_CHAR_ANSI,
		/** Environment is Unicode using wide character string  */
		CharsetWide  = OCI_CHAR_WIDE
	};

	/**
	* @brief
	* Environment charset mode
	*
	* Possible values are Environment::CharsetModeValues
	*
	*/
	typedef Enum<CharsetModeValues> CharsetMode;

	/**
	* @brief
	* Session flags enumerated values
	*
	*/
	enum SessionFlagsValues
	{
		/** Default session mode */
		SessionDefault = OCI_SESSION_DEFAULT,
		/** Requested session will be created through the XA interface */
		SessionXa  = OCI_SESSION_XA,
		/** the user is authenticated for SYSDBA access. */
		SessionSysDba = OCI_SESSION_SYSDBA,
		/** the user is authenticated for SYSOPER access */
		SessionSysOper = OCI_SESSION_SYSOPER
	};

	/**
	* @brief
	* Sessions flags
    *
	* Possible values are Environment::SessionFlagsValues
	*
	*/
	typedef Flags<SessionFlagsValues> SessionFlags;

	/**
	* @brief
	* Oracle instance start modes enumerated values
	*
	*/
	enum StartModeValues
	{
		/** Start the instance wihtout mouting and opening it */
		StartOnly = OCI_DB_SPM_START,
		/** Mount (only) the instance */
		StartMount  = OCI_DB_SPM_MOUNT,
		/** Open (only)  the instance */
		StartOpen = OCI_DB_SPM_OPEN,
		/** Start, mount and open the instance */
		StartFull = OCI_DB_SPM_FULL
	};

	/**
	* @brief
	* Oracle instance start modes
	*
	* Possible values are Environment::StartModeValues
	*
	*/
	typedef Enum<StartModeValues> StartMode;

	/**
	* @brief
	* Oracle instance start flags enumerated values
	*
	*/
	enum StartFlagsValues
	{
		/** Default start flags */
		StartDefault = OCI_DB_SPF_DEFAULT,
		/** Shuts down a running instance (if needed) using ABORT command and starts a new instance */
		StartForce  = OCI_DB_SPF_FORCE,
		/** Allows database access only to users with both CREATE SESSION and RESTRICTED SESSION privileges */
		StartRestrict = OCI_DB_SPF_RESTRICT
	};

	/**
	* @brief
	* Oracle instance start flags
	*
	* Possible values are Environment::StartFlagsValues
	*
	*/
	typedef Flags<StartFlagsValues> StartFlags;

	/**
	* @brief
	* Oracle instance shutdown modes enumerated values
	*
	*/
	enum ShutdownModeValues
	{
		/** Shutdown the instance */
		ShutdownOnly = OCI_DB_SDM_SHUTDOWN,
		/** Close (only) the instance */
		ShutdownClose  = OCI_DB_SDM_CLOSE,
		/** Dismount (only)  the instance */
		ShutdownDismount = OCI_DB_SDM_DISMOUNT,
		/** Shutdown, close and dismount the instance */
		ShutdownFull = OCI_DB_SDM_FULL
	};

	/**
	* @brief
	* Oracle instance shutdown modes
	*
	* Possible values are Environment::ShutdownModeValues
	*
	*/
	typedef Enum<ShutdownModeValues> ShutdownMode;

	/**
	* @brief
	* Oracle instance shutdown flags enumerated values
	*
	*/
    enum ShutdownFlagsValues
    {
        /**  - Further connects are prohibited.
          *  - Waits for users to disconnect from the database */
        ShutdowntDefault = OCI_DB_SDF_DEFAULT,
        /**  - Further connects are prohibited
          *  - No new transactions are allowed. */
        ShutdowTrans  = OCI_DB_SDF_TRANS,
		/**  - Further connects are prohibited
		  *  - No new transactions are allowed.
		  *  - Waits for active transactions to complete */
		ShutdownTransLocal = OCI_DB_SDF_TRANS_LOCAL,
		/**  - Does not wait for current calls to complete or users to disconnect from the database.
	      *  - All uncommitted transactions are terminated and rolled back */
		ShutdownImmediate = OCI_DB_SDF_IMMEDIATE,
		/**  - Does not wait for current calls to complete or users to disconnect from the database.
		  *  - All uncommitted transactions are terminated and are not rolled back.
		  *  - This is the fastest possible way to shut down the database, but the next
		  *    database startup may require instance recovery.
		  *  - Therefore, this option should be used only in unusual circumstances */
		ShutdownAbort = OCI_DB_SDF_ABORT
	};

	/**
	* @brief
	* Oracle instance shutdown flags
	*
	* Possible values are Environment::ShutdownFlagsValues
	*
	*/
	typedef Flags<ShutdownFlagsValues> ShutdownFlags;

	/**
	* @brief
	* Charset form enumerated values
	*
	*/
	enum CharsetFormValues
	{
		/** Database character set will be converted to the server national character set */
		CharsetFormDefault = OCI_CSF_DEFAULT,
		/** Client national character set will be converted to the server national character set */
		CharsetFormNational = OCI_CSF_NATIONAL
	};
	/**
	* @brief
	* Type of Exception
	*
	* Possible values are Environment::CharsetFormValues
	*
	*/
	typedef Enum<CharsetFormValues> CharsetForm;

	/**
	* @typedef HAHandlerProc
	*
	* @brief
	* User callback for HA event notifications
	*
	*/
	typedef void(*HAHandlerProc) (Connection &con, HAEventSource eventSource, HAEventType eventType, Timestamp  &time);

    /**
     * @brief
     * Initialize the OCILIB environment
     *
     * @param mode         - Environment mode
     * @param libpath      - Oracle shared library path (optional)
     *
     * @note
     * This function must be called before any other OCILIB library function.
     *
     * @warning
     * It should be called <b>ONCE</b> per application
     *
     * @warning
     * - The parameter 'libpath' is only used if OCILIB has been built with the option OCI_IMPORT_RUNTIME
     * - If the parameter 'lib_path' is NULL, the Oracle library is loaded from system environment variables
     *
     */
    static void Initialize(EnvironmentFlags mode = Environment::Default, ostring libpath = OTEXT(""));

    /**
     * @brief
     * Clean up all resources allocated by the environment
     *
     * @note
     * This function must be the last OCILIB library function call.
     * - It deallocates objects not explicitly freed by the program (connections, statements, ...)
     * - It unloads the Oracle shared library if it has been dynamically loaded
     *
     * @warning
     * It should be called <b>ONCE</b> per application
     *
     */
    static void Cleanup();

    /**
     * @brief
     * Return the Enviroment mode flags
     *
     * @note
     * It returns the value of the parameter 'mode' passed to Initialize()
     *
     */
    static Environment::EnvironmentFlags GetMode();

    /**
     * @brief
     * Return the Oracle shared library import mode
     *
     */
    static Environment::ImportMode GetImportMode();

    /**
     * @brief
     * Return the OCILIB charset type
     *
     */
    static Environment::CharsetMode GetCharset();

    /**
     * @brief
     * Return the version of OCI used for compiling OCILIB
     *
     * @note
     * - with linkage build option, the version is determined from the oci.h header through different ways
     * - with runtime loading build option, the version is set to the highest version
     *   of OCI needed by OCILIB, not necessarily the real OCI version
     *
     */
    static unsigned int GetCompileVersion();

    /**
     * @brief
     * Return the version of OCI used at runtime
     *
     * @note
     * - with linkage build option, the version is determined from the oci.h header through different ways
     * - with runtime loading build option, the version determined from the symbols dynamically loaded.
     *
     */
    static unsigned int GetRuntimeVersion();

    /**
     * @brief
     * Enable or disable Oracle warning notifications
     *
     * @param value  - enable/disable warnings
     *
     * @note
     * Default value is false
     *
     */
    static void EnableWarnings(bool value);

    /**
     * @brief
     * Start a database instance
     *
     * @param db           - Oracle Service Name
     * @param user         - Oracle User name
     * @param pwd          - Oracle User password
     * @param startFlags   - Start flags
     * @param startMode    - Start mode
     * @param sessionFlags - Session Flags
     * @param spfile       - Client-side spfile to start up the database (optionnal)
     *
     * @note
     * The only valid modes for sessionFlags are SessionSysDba and SessionSysOper.
     *
     * @note
     * Start modes and flags parameters values can be combined.
     *
     * @note
     * External credentials are supported by supplying a empty strings for the 'user' and 'pwd' parameters
     * If the param 'db' is empty then a connection to the default local DB is done.
     *
     * @note
     * If the client side spfile is not provided, the database is started with its server-side spfile.
     *
     */
    static void StartDatabase(ostring db, ostring user, ostring pwd,
                              Environment::StartFlags startFlags,
                              Environment::StartMode startMode,
                              Environment::SessionFlags sessionFlags = SessionSysDba,
                              ostring spfile = OTEXT(""));

    /**
     * @brief
     * Shutdown a database instance
     *
     * @param db            - Oracle Service Name
     * @param user          - Oracle User name
     * @param pwd           - Oracle User password
     * @param shutdownFlags - Shutdown flags
     * @param shutdownMode  - Shutdown mode
     * @param sessionFlags  - Session flags
     *
     * @note
     * The only valid modes for sessionFlags are SessionSysDba and SessionSysOper.
     *
     * @note
     * Shutdown modes values can be combined.
     *
     * @note
     * Shutdown flag values are exclusive.
     *
     * @note
     * External credentials are supported by supplying a empty strings for the 'user' and 'pwd' parameters
     * If the param 'db' is empty then a connection to the default local DB is done.
     *
     */
    static void ShutdownDatabase(ostring db, ostring user, ostring pwd,
                                 Environment::ShutdownFlags shutdownFlags,
                                 Environment::ShutdownMode shutdownMode,
                                 Environment::SessionFlags sessionFlags = SessionSysDba);

    /**
     * @brief
     * Change the password of the given user on the given database
     *
     * @param db      - Oracle Service Name
     * @param user    - Oracle User name
     * @param pwd     - Oracle User password
     * @param newPwd  - Oracle User New password
     *
     */
    static void ChangeUserPassword(ostring db, ostring user, ostring pwd, ostring newPwd);

    /**
     * @brief
     * Set the High availabality (HA) user handler
     *
     * @param handler - HA handler procedure
     *
     * @note
     * See POCI_HA_HANDLER documentation for more details
     *
     * @note
     * EnvMode::Events flag must be passed to Initialize() to be able to use HA events
     *
     * @warning
     * This call is supported from Oracle 10gR2.
     *
     */
    static void SetHAHandler(HAHandlerProc handler);

private:

    static void HAHandler(OCI_Connection *pConnection, unsigned int source, unsigned int event, OCI_Timestamp  *pTimestamp);
    static unsigned int TAFHandler(OCI_Connection *pConnection, unsigned int type, unsigned int event);
    static void NotifyHandler(OCI_Event *pEvent);
    static void NotifyHandlerAQ(OCI_Dequeue *pDequeue);

    typedef ConcurrentPool<UnknownHandle, Handle *> HandlePool;
    typedef ConcurrentPool<UnknownHandle, CallbackPointer> CallbackPool;

    class EnvironmentHandle : public HandleHolder<UnknownHandle>
    {
        friend class Connection;

    public:

        HandlePool   Handles;
        CallbackPool Callbacks;
        unsigned int Mode;

        void Initialize(UnknownHandle pEnv, unsigned int envMode);
        void Finalize();
    };

    static EnvironmentHandle& GetEnvironmentHandle();
};

/**
 * @brief
 * static class allowing to manipulate threads
 *
 * This class wraps the OCILIB object handle OCI_Thread and its related methods
 *
 * @note
 * See @ref OcilibCApiThreading for more details on Oracle multithreading support
 *
 */
class Thread
{
public:

    /**
     * @typedef ThreadProc
     *
     * @brief
     *
     */
    typedef POCI_THREAD ThreadProc;

    /**
     * @brief
     * Create a Thread
     *
     * @return
     * Thread handle on success or NULL on failure
     *
     */
    static ThreadHandle Create();

    /**
     * @brief
     * Destroy a thread
     *
     * @param handle - Thread handle
     *
     */
    static void Destroy(ThreadHandle handle);

    /**
     * @brief
     * Execute the given routine within the given thread
     *
     * @param handle - Thread handle
     * @param func   - routine to execute
     * @param args   - parameter to pass to the routine
     *
     */
    static void Run(ThreadHandle handle, ThreadProc func, void *args);

    /**
     * @brief
     * Join the given thread
     *
     * @param handle - Thread handle
     *
     * @note
     * This function waits for the given thread to finish
     *
     */
    static void Join(ThreadHandle handle);
};

/**
 * @brief
 * Static class allowing managing mutexes
 *
 * This class wraps the OCILIB object handle OCI_Mutex and its related methods
 *
 * See @ref OcilibCApiThreading for more details on Oracle multithreading support
 *
 */
class Mutex
{
public:

    /**
     * @brief
     * Create a Mutex handle
     *
     * @return
     * Mutex handle on success or NULL on failure
     *
     */
    static MutexHandle Create();

    /**
     * @brief
     * Destroy a mutex handle
     *
     * @param handle - Mutex handle
     *
     */
    static void Destroy(MutexHandle handle);

    /**
     * @brief
     * Acquire a mutex lock
     *
     * @param handle - Mutex handle
     *
     */
    static void Acquire(MutexHandle handle);

    /**
     * @brief
     * Release a mutex lock
     *
     * @param handle - Mutex handle
     *
     */
    static void Release(MutexHandle handle);
};

/**
 * @brief
 * Static class allowing to set/get thread local storage (TLS) values for a given unique key
 *
 * This class wraps the OCILIB object handle OCI_ThreadKey and its related methods
 *
 * @note
 * See @ref OcilibCApiThreading for more details on Oracle multithreading support
 *
 */
class ThreadKey
{
public:

    /**
     * @typedef ThreadKeyFreeProc
     *
     * @brief
     *
     */
    typedef POCI_THREADKEYDEST ThreadKeyFreeProc;

    /**
     * @brief
     * Create a thread key object
     *
     * @param name     - Thread key name
     * @param freeProc - Thread key value destructor function
     *
     * @note
     * Parameter freeProc is optional. It's called when the thread terminates to allow
     * the program to deal with the thread specific value of the key
     *
     */
    static void Create(ostring name, ThreadKeyFreeProc freeProc = 0);

    /**
     * @brief
     * Set a thread key value
     *
     * @param name  - Thread key name
     * @param value - user value to set
     *
     */
	static void SetValue(ostring name, AnyPointer value);

    /**
     * @brief
     * Get a thread key value
     *
     * @param name - Thread key name
     *
     * @return
     * Thread key value on success otherwise FALSE
     *
     */
	static AnyPointer GetValue(ostring name);
};

/**
  * @brief
  * A connection or session Pool.
  *
  * This class wraps the OCILIB object handle OCI_Pool and its related methods
  *
  */
class Pool : public HandleHolder<OCI_Pool *>
{
public:

    /**
     * @brief
     * Pool type enumerated values
     *
     */
    enum PoolTypeValues
    {
        /** Pool of Connections */
        ConnectionPool = OCI_POOL_CONNECTION,
        /** Pool of stateless sessions */
        SessionPool  = OCI_POOL_SESSION
    };

	/**
	* @brief
	* Type of Pool
	*
	* Possible values are Pool::PoolTypeValues
	*
	*/
    typedef Enum<PoolTypeValues> PoolType;

    /**
     * @brief
     * Default constructor
     *
     */
    Pool();

    /**
     * @brief
     * Contructor that creates an underlying pool with the given information
     *
     * @param db           - Oracle Service Name
     * @param user         - Oracle User name
     * @param pwd          - Oracle User password
     * @param poolType     - Type of pool
     * @param sessionFlags - session Flags
     * @param minSize      - minimum number of  connections/sessions that can be opened.
     * @param maxSize      - maximum number of  connections/sessions that can be opened.
     * @param increment    - next increment for connections/sessions to be opened
     *
     *  @note
     * it calls Open() with the given parameters
     *
     */
    Pool(ostring db, ostring user, ostring pwd, Pool::PoolType poolType,
         unsigned int minSize, unsigned int maxSize, unsigned int increment = 1,
         Environment::SessionFlags sessionFlags = Environment::SessionDefault);

    /**
     * @brief
     * Create an Oracle pool of connections or sessions
     *
     * @param db           - Oracle Service Name
     * @param user         - Oracle User name
     * @param pwd          - Oracle User password
     * @param poolType     - Type of pool
     * @param sessionFlags - session Flags
     * @param minSize      - minimum number of  connections/sessions that can be opened.
     * @param maxSize      - maximum number of  connections/sessions that can be opened.
     * @param increment    - next increment for connections/sessions to be opened
     *
     * @note
     * External credentials are supported by supplying an emtpy string for the 'user' and 'pwd' parameters
     * If the param 'db' is empty then a connection to the default local DB is done
     *
     */
    void Open(ostring db, ostring user, ostring pwd, Pool::PoolType poolType,
              unsigned int minSize, unsigned int maxSize, unsigned int increment = 1,
              Environment::SessionFlags sessionFlags = Environment::SessionDefault);

    /**
     * @brief
     * Destroy the current Oracle pool of connections or sessions
     *
     */
    void Close();

    /**
     * @brief
     * Get a connection from the pool
     *
     * @param sessionTag  - Session user tag string
     *
     * @par Session tagging
     *
     * Session pools have a nice feature called 'session tagging'
     * It's possible to tag a session with a string identifier
     * when the session is returned to the pool, it keeps its tags.
     * When requesting a connection from the session pool, it's
     * possible to request a session that has the given 'tag' parameter
     * If one exists, it is returned. If not and if an untagged session
     * is available, it is then returned. So check the connection tag
     * property with OCI_GetSessionTag() to find out if the returned
     * connection is tagged or not.
     *
     * This features is described in the OCI developper guide as the following :
     *
     *  "The tags provide a way for users to customize sessions in the pool.
     *   A client may get a default or untagged session from a pool, set certain
     *   attributes on the session (such as NLS settings), and return the session
     *   to the pool, labeling it with an appropriate tag.
     *   The user may request a session with the same tags in order to have a
     *   session with the same attributes"
     *
     */
    Connection GetConnection(ostring sessionTag = OTEXT(""));

    /**
     * @brief
     * Get the idle timeout for connections/sessions in the pool
     *
     * @note
     * Connections/sessions idled for more than this time value (in seconds) are terminated
     *
     * @note
     * Timeout is not available for internal pooling implementation (client < 9i)
     *
     */
    unsigned int GetTimeout() const;

    /**
     * @brief
     * Set the connections/sessions idle timeout
     *
     * @param value - Timeout value
     *
     * @note
     * connections/sessions idle for more than this time value (in seconds) are terminated
     *
     * @note
     * This call has no effect if pooling is internally implemented (client < 9i)
     *
     */
    void SetTimeout(unsigned int value);

    /**
     * @brief
     * Get the waiting mode used when no more connections/sessions are available from the pool
     *
     * @return
     * - true to wait for an available object if the pool is saturated
     * - false to not wait for an available object
     *
     */
    bool GetNoWait() const;

    /**
     * @brief
     * Set the waiting mode used when no more connections/sessions are available from the pool
     *
     * @param value - wait for object
     *
     * @note
     * For paramter value, pass :
     * - true to wait for an available object if the pool is saturated
     * - false to not wait for an available object
     *
     */
    void SetNoWait(bool value);

    /**
     * @brief
     * Return the current number of busy connections/sessions
     *
     */
    unsigned int GetBusyConnectionsCount() const;

    /**
     * @brief
     * Return the current number of opened connections/sessions
     *
     */
    unsigned int GetOpenedConnectionsCount() const;

    /**
     * @brief
     * Return the minimum number of connections/sessions that can be opened to the database
     *
     */
    unsigned int GetMinSize() const;

    /**
     * @brief
     * Return the maximum number of connections/sessions that can be opened to the database
     *
     */
    unsigned int GetMaxSize() const;

    /**
     * @brief
     * Return the increment for connections/sessions to be opened to the database when the pool is not full
     *
     */
    unsigned int GetIncrement() const;

    /**
     * @brief
     * Return the maximum number of statements to keep in the pool's statement cache
     *
     * @note
     * Default value is 20 (value from Oracle Documentation)
     *
     */
    unsigned int GetStatementCacheSize() const;

    /**
     * @brief
     * Set the maximum number of statements to keep in the pool's statement cache
     *
     * @param value - maximun number of statements in the cache
     *
     */
    void SetStatementCacheSize(unsigned int value);
};

/**
 * @brief
 * A connection or session with a specific database.
 *
 * This class wraps the OCILIB object handle OCI_Connection and its related methods
 *
 */
class Connection : public HandleHolder<OCI_Connection *>
{
    friend class Environment;
    friend class Exception;
    friend class Statement;
    friend class Clob;
    friend class Blob;
    friend class File;
    friend class Timestamp;
    friend class Pool;
    friend class Object;
    friend class TypeInfo;
    friend class Reference;
    friend class Resultset;
	template <class TDataType>
    friend class Collection;
    friend class Subscription;

public:

	/**
	* @brief
	* Failover request enumerated values
	*
	*/
	enum FailoverRequestValues
    {
		/** User has requested only session failover */
		FailoverRequestSession = OCI_FOT_SESSION,
		/** User has requested select failover as well */
		FailoverRequestSelect = OCI_FOT_SELECT
    };

	/**
	* @brief
	* Failover requests
	*
	* Possible values are Connection::FailoverRequestValues
	*
	*/
	typedef Enum<FailoverRequestValues> FailoverRequest;

	/**
	* @brief
	* Failover events enumerated values
	*
	*/
    enum FailoverEventValues
    {
		/** Successful completion of failover */
        FailoverEventEnd = OCI_FOE_END,
		/** Failover was unsuccessful. Retrying is not allowed */
        FailoverEventAbort = OCI_FOE_ABORT,
		/** Multiple authentication and failover has occurred after the original authentication. User has been reauthenticated */
        FailoverEventReauthentificate = OCI_FOE_REAUTH,
		/** Failover has detected a lost connection and failover is starting */
        FailoverEventBegin = OCI_FOE_BEGIN,
		/** Failover was unsuccessful. Retrying is allowed */
        FailoverEventError = OCI_FOE_ERROR
    };

	/**
	* @brief
	* Failover events
	*
	* Possible values are Connection::FailoverEventValues
	*
	*/
    typedef Enum<FailoverEventValues> FailoverEvent;

	/**
	* @brief
	* Failover callback results enumerated values
	*
	*/
    enum FailoverResultValues
    {
		/** Default acknowledgement of a failover event */
		FailoverOk = OCI_FOC_OK,
		/** Triggers a new failover attempt */
        FailoverRetry = OCI_FOC_RETRY
    };

	/**
	* @brief
	* Failover callback results
	*
	* Possible values are Connection::FailoverResultValues
	*
	*/
    typedef Enum<FailoverResultValues> FailoverResult;

    /**
     * @brief
     * Session trace enumerated values
     *
     */
    enum SessionTraceValues
    {
        /** Specifies the user defined identifier in the session. It's recorded in the column CLIENT_IDENTIFIER of the system view V$SESSION */
        TraceIdentity = OCI_TRC_IDENTITY,
        /** Name of the current module in the client application. It's recorded in the column MODULE of the system view V$SESSION */
        TraceModule  = OCI_TRC_MODULE,
        /** Name of the current action within the current module. It's recorded in the column ACTION of the system view V$SESSION */
        TraceAction = OCI_TRC_ACTION,
        /** Client application additional information. It's recorded in the column CLIENT_INFO of the system view V$SESSION */
        TraceDetail  = OCI_TRC_DETAIL
    };

	/**
	* @brief
	* Session traces
	*
	* Possible values are Connection::SessionTraceValues
	*
	*/
    typedef Enum<SessionTraceValues> SessionTrace;

	/**
	* @typedef TAFHandlerProc
	*
	* @brief
	* User callback for TAF event notifications
	*
	*/
	typedef FailoverResult(*TAFHandlerProc) (Connection &con, FailoverRequest failoverRequest, FailoverEvent failoverEvent);

    /**
     * @brief
     * Default constructor
     *
     */
    Connection();

    /**
     * @brief
     * Contructor that creates an opens an underlying DB connection with the given information
     *
     * @param db           - Oracle Service Name
     * @param user         - Oracle User name
     * @param pwd          - Oracle User password
     * @param sessionFlags - Session Flags
     *
     *  @note
     * it calls Open() with the given parameters
     *
     */
    Connection(ostring db, ostring user, ostring pwd, Environment::SessionFlags sessionFlags = Environment::SessionDefault);

    /**
     * @brief
     * Create a physical connection to an Oracle database server
     *
     * @param db           - Oracle Service Name
     * @param user         - Oracle User name
     * @param pwd          - Oracle User password
     * @param sessionFlags - Session Flags
     * *
     * @note
     * External credentials are supported by supplying an emtpy string for the 'user' and 'pwd' parameters
     * If the param 'db' is empty then a connection to the default local DB is done
     *
     * @par Oracle XA support
     * OCILIB supports Oracle XA connectivity. In order to get a connection using
     * the XA interface :
     *   - For parameter 'db' : pass the value of the 'DB' parameter of the given
     *    XA connection string pased to the Transaction Processing Monitor (TPM)
     *   - Pass emtpy strings for 'user' and 'pwd' parameters
     *   - Use SessionFlags::SessionXa for parameter 'sessionFlags'
     *
     * @par Oracle XA Connection String
     *
     * The XA connection string used in a transaction monitor to connect to Oracle must
     * be compatible with OCILIB :
     *   - the XA parameter 'Objects' MUST be set to 'true'
     *   - If EnvMode::Threaded is passed to Environment::Initialize(), the XA parameter 'Threads' must
     *     be set to 'true', otherwise to 'false'
     *   - If EnvMode::Events is passed to Environment::Initialize(), the XA parameter 'Events' must
     *     be set to 'true', otherwise to 'false'
     *   - As Oracle does not support Unicode UTF16 characterset through the XA interface,
     *     Only OCI_CHARSET_ANSI builds of OCILIB can be used
     *   - You still can use UTF8 if the NLS_LANG environment variable is set with a valid
     *     UTF8 NLS value
     *   - DO NOT USE UNICODE OCILIB builds with XA connections
     *
     * @note
     * On success, a local transaction is automatically created and started ONLY for regular
     * standalone connections and connections retrieved from connection pools.
     * No transaction is created for a XA connection or q connection retrieved from session pools.
     *
     */
    void Open(ostring db, ostring user, ostring pwd,  Environment::SessionFlags sessionFlags = Environment::SessionDefault);

    /**
     * @brief
     * Close the physical connection to the DB server
     *
     */
    void Close();

    /**
     * @brief
     * Commit current pending changes
     *
     */
    void Commit();

   /**
     * @brief
     * Cancel current pending changes
     *
     */
    void Rollback();

    /**
     * @brief
     * Perform an immediate abort of any currently Oracle OCI call on the given connection
     *
     * @note
     * The current call will abort and will raise an exception
     *
     */
    void Break();

    /**
     * @brief
     * Enable or disable auto commit mode (implicit commits after every SQL execution)
     *
     * @param enabled - auto commit new status
     *
     */
    void SetAutoCommit(bool enabled);

    /**
     * @brief
     * Indicates if autocommit is currently activated
     *
     */
    bool GetAutoCommit() const;

    /**
    * @brief
    * Indiciated if the connection is still connected to the server
    *
    * @note
    * the returned value is not realtime and is  based on client libray last heart beat status
    *
    */
    bool IsServerAlive() const;

    /**
     * @brief
     * Performs a round trip call to the server to confirm that the connection to the server is still valid.
     *
     * @warning
     * This call is supported from Oracle 10g.
     *
     */
    bool PingServer() const;

    /**
     * @brief
     * Return the name of the connected database/service name
     *
     * @note
     * The returned value is the value of the 'db' parameter of the Open() method
     *
     */
    ostring GetConnectionString() const;

    /**
     * @brief
     * Return the current logged user name
     *
     * @note
     * The returned value is the value of the 'user' parameter of the Open() method
     *
     */
    ostring GetUserName() const;

    /**
     * @brief
     * Return the current logged user password
     *
     * @note
     * The returned value is the value of the 'pwd' parameter of the Open() method
     *
     */
    ostring GetPassword() const;

    /**
     * @brief
     * Return the connected database server string version
     *
     * @note
     * The returned value is the server version banner displayed by SQL*PLUS when connected to a DB server
     *
     */
    ostring GetServerVersion() const;

    /**
     * @brief
     * Return the Oracle version supported by the connection
     *
     * @note
     * The supported version is the lower version between client and server:
     *  - OCI_UNKNOWN
     *  - OCI_8_0
     *  - OCI_8_1
     *  - OCI_9_0
     *  - OCI_9_2
     *  - OCI_10_1
     *  - OCI_10_2
     *  - OCI_11_1
     *  - OCI_11_2
     *  - OCI_12_1
     *
     */
    unsigned int GetVersion() const;

    /**
     * @brief
     * Return the major version number of the connected database server
     *
     */
    unsigned int GetServerMajorVersion() const;

    /**
     * @brief
     * Return the minor version number of the connected database server
     *
     */
    unsigned int GetServerMinorVersion() const;

    /**
     * @brief
     * Return the revision version number of the connected database server
     *
     */
    unsigned int GetServerRevisionVersion() const;

    /**
     * @brief
     * Change the password of the logged user
     *
     * @param newPwd - New password
     *
     */
    void ChangePassword(ostring newPwd);

    /**
     * @brief
     * Return the tag associated the the given connection
     *
     */
    ostring GetSessionTag() const;

    /**
     * @brief
     * Associate a tag to the given connection/session
     *
     * @param tag - user tag string
     *
     * @note
     * Use this call only for connections retrieved from a session pool
     * See Pool::GetConnection() for more details
     *
     * @note
     * To untag a session, call SetSessionTag() with an empty 'tag' parameter
     *
     */
    void SetSessionTag(ostring tag);

    /**
     * @brief
     * Return the current transaction of the connection
     *
     */
    Transaction GetTransaction() const;

    /**
     * @brief
     * Set a transaction to a connection
     *
     * @param transaction - Transaction to assign
     *
     * @note
     * The current transaction (if any) is automatically stopped but the newly assigned is not started or resumed
     *
     * @warning
     * Do not set a transaction to a XA connection or a connection retrieved from a session pool
     *
     */
    void SetTransaction(const Transaction &transaction);

    /**
     * @brief
     * Set the date format for implicit string / date conversions
     *
     * @param format - Date format
     *
     * @note
     * Default format is 'YYYY-MM-DD' defined by the public constant OCI_STRING_FORMAT_DATE
     *
     * @note
     * Conversions are performed by Oracle builtin functions.
     * Possible values are string date formats supported by Oracle.
     * See documentation of Oracle SQL to_date() function for more details
     *
     */
    void SetDefaultDateFormat(ostring format);

    /**
     * @brief
     * Return the current date format for implicit string / date conversions
     *
     * @note
     *  See SetDefaultDateFormat() for possible values
     *
     */
    ostring  GetDefaultDateFormat() const;

    /**
     * @brief
     * Set the numeric format for implicit string / numeric conversions
     *
     * @param format - Numeric format
     *
     * @note
     * Conversions are performed by Oracle builtin functions.
     * Possible format values are the numeric formats supported by Oracle.
     * See documentation of Oracle SQL to_number() function for more details
     *
     * @note
     * Default format is 'FM99999999999999999999999999999999999990.999999999999999999999999'
     * defined by the public constant OCI_STRING_FORMAT_NUM
     *
     * @warning
     * It does not applies to binary double and binary floats data types that
     * are converted from/to strings using the standard C library
     *
     */
    void SetDefaultNumericFormat(ostring format);

    /**
     * @brief
     * Return the current numeric format for implicit string / numeric conversions
     *
     * @note
     *  See SetDefaultNumericFormat() for possible values
     *
     */
    ostring  GetDefaultNumericFormat() const;

    /**
     * @brief
     * Enable the server output
     *
     * @param bufsize - server buffer max size (server side)
     * @param arrsize - number of lines to retrieve per server roundtrip
     * @param lnsize  - maximum size of one line
     *
     * @note
     * This call is equivalent to the command 'set serveroutput on' in SQL*PLUS
     *
     * @note
     *  - 'bufsize' minimum value is 2000, maximum 1000000 with Oracle < 10.2g and can be unlimited above
     *  -'lnsize' maximum value is 255 with Oracle < 10g R2 and 32767 above
     *
     * @warning
     * If EnableServerOutput() is not called, GetServerOutput() will return false
     *
     */
    void EnableServerOutput(unsigned int bufsize, unsigned int arrsize, unsigned int lnsize);

    /**
     * @brief
     * Disable the server output
     *
     * @note
     * After this call, GetServerOutput() will return false.
     *
     */
    void DisableServerOutput();

    /**
     * @brief
     * Retrieve one line of the server buffer
     *
     * @return
     * true if a line has been retrieved otherwise false (server buffer is empty or all lines have been retrieved)
     *
     */
    bool GetServerOutput(ostring &line) const;

    /**
     * @brief
     * Retrieve all remaining lines of the server buffer
     *
     */
    void GetServerOutput(std::vector<ostring> &lines) const;


    /**
     * @brief
     * Set tracing information for the session
     *
     * @param trace - trace type
     * @param value - trace content
     *
     * Store current trace information to the given connection handle.
     * These information:
     *
     * - is stored in the system view V$SESSION
     * - can be retrieved from the connection property of an OCI_Error handle
     *
     * system view V$SESSION
     *
     * @warning
     * The system view V$SESSION is updated on Oracle versions >= 10g
     *
     * @warning
     * Oracle limits the size of these traces content and thus OCILIB will truncate
     * the given values if needed :
     *
     * - TraceIdentity : 64 bytes
     * - TraceModule   : 48 bytes
     * - TraceAction   : 32 bytes
     * - TraceDetail   : 64 bytes
     *
     */
    void SetTrace(SessionTrace trace, ostring value);

    /**
     * @brief
     * Get the current trace for the trace type from the given connection.
     *
     * @param trace - trace type
     *
     * @note
     * See SetTrace() for more details.
     *
     */
    ostring GetTrace(SessionTrace trace) const;

    /**
     * @brief
     * Return the Oracle server database name of the connected database/service name
     *
     * @warning
     * This call is supported from Oracle 10gR2.
     *
     */
    ostring GetDatabase() const;

    /**
     * @brief
     * Return the Oracle server Instance name of the connected database/service name
     *
     * @warning
     * This call is supported from Oracle 10gR2.
     *
     */
    ostring GetInstance() const;

    /**
     * @brief
     * Return the Oracle server Service name of the connected database/service name
     *
     * @warning
     * This call is supported from Oracle 10gR2.
     *
     */
    ostring GetService() const;

    /**
     * @brief
     * Return the Oracle server Hos name of the connected database/service name
     *
     * @warning
     * This call is supported from Oracle 10gR2.
     *
     */
    ostring GetServer() const;

    /**
     * @brief
     * Return the Oracle server Domain name of the connected database/service name
     *
     * @warning
     * This call is supported from Oracle 10gR2.
     *
     */
    ostring GetDomain() const;

    /**
     * @brief
     * Return the date and time (Timestamp) server instance start of the
     *
     * @warning
     * This call is supported from Oracle 10gR2.
     *
     */
    Timestamp GetInstanceStartTime() const;

    /**
     * @brief
     * Return the maximum number of statements to keep in the statement cache
     *
     * @note
     * Default value is 20 (value from Oracle Documentation)
     *
     * @warning
     * Requires Oracle Client 9.2 or above
     *
     */
    unsigned int GetStatementCacheSize() const;

    /**
     * @brief
     * Set the maximum number of statements to keep in the statement cache
     *
     * @param value - maximum number of statements in the cache
     *
     * @warning
     * Requires Oracle Client 9.2 or above
     *
     */
    void SetStatementCacheSize(unsigned int value);

    /**
     * @brief
     * Return the default LOB prefetch buffer size for the connection
     *
     * @warning
     * Requires Oracle Client AND Server 11gR1 or above
     *
     * @note
     * Prefetch size is:
     * - number of bytes for BLOBs and BFILEs
     * - number of characters for CLOBs.
     *
     * @note
     * Default is 0 (prefetching disabled)
     *
     */
    unsigned int GetDefaultLobPrefetchSize() const;

    /**
     * @brief
     * Enable or disable prefetching for all LOBs fetched in the connection
     *
     * @param value - default prefetch buffer size
     *
     * @note
     * If parameter 'value':
     * - is == 0, it disables prefetching for all LOBs fetched in the connection.
     * - is >  0, it enables prefetching for all LOBs fetched in the connection
     * and the given buffer size is used for prefetching LOBs
     *
     * @note
     * LOBs prefetching is disabled by default
     *
     * @warning
     * Requires Oracle Client AND Server 11gR1 or above.
     *
     * @note
     * Prefetch size is:
     * - number of bytes for BLOBs and BFILEs
     * - number of characters for CLOBs.
     *
     */
    void SetDefaultLobPrefetchSize(unsigned int value);

    /**
     * @brief
     * Verifiy if the connection support TAF events
     *
     * @warning
     * This call is supported from Oracle 10gR2.
     *
     */
    bool IsTAFCapable() const;

    /**
     * @brief
     * Set the Transparent Application Failover (TAF) user handler
     *
     * @param handler - TAF handler procedure
     *
     * @note
     * See TAFHandlerProc documentation for more details
     *
     * @warning
     * This call is supported from Oracle 10gR2.
     *
     */
    void SetTAFHandler(TAFHandlerProc handler);

    /**
     * @brief
     * Return the pointer to user data previously associated with the connection
     *
     */
	AnyPointer GetUserData();

    /**
     * @brief
     * Associate a pointer to user data to the given connection
     *
     * @param value - User data pointer
     *
     * @return
     * TRUE on success otherwise FALSE
     *
     */
	void SetUserData(AnyPointer value);

private:

    Connection(OCI_Connection *con, Handle *parent);
};

/**
 * @brief
 * Oracle Transaction object
 *
 * This class wraps the OCILIB object handle OCI_Transaction and its related methods
 *
 */
class Transaction : public HandleHolder<OCI_Transaction *>
{
    friend class Connection;

public:

    /**
     * @brief
     * Transaction flags enumerated values
     *
     */
    enum TransactionFlagsValues
    {
        Unknown = OCI_UNKNOWN,
        /** (Global) Specifies tightly coupled and migratable branch */
        New = OCI_TRS_NEW,
        /** (Global) Specifies a tightly coupled branch */
        Tight  = OCI_TRS_TIGHT,
        /** (Global) Specifies a loosely coupled branch */
        Loose = OCI_TRS_LOOSE,
        /** (Global and local) start a read-only transaction */
        ReadOnly  = OCI_TRS_READONLY,
        /** (Global and local) start a read-write transaction */
        ReadWrite = OCI_TRS_READWRITE,
        /** (Global and local) start a serializable transaction */
        Serializable  = OCI_TRS_SERIALIZABLE
    };

	/**
	* @brief
	* Transaction flags
	*
	* Possible values are Transaction::TransactionFlagsValues
	*
	*/
    typedef Flags<TransactionFlagsValues> TransactionFlags;

    /**
     * @brief
     * Create a new global transaction or a serializable/read-only local transaction
     *
     * @param connection - Connection
     * @param timeout    - Time that a transaction stays inactive after being stopped
     * @param flags      - Transaction flags
     * @param pxid       - pointer to a global transaction identifier structure
     *
     * @note
     * For local transaction,  don't use the 'pxid' parameter
     *
     */
   Transaction(const Connection &connection, unsigned int timeout, TransactionFlags flags, OCI_XID *pxid = NULL);

   /**
     * @brief
     * Prepare a global transaction validation
     *
     */
   void Prepare();

   /**
     * @brief
     * Start global transaction
     *
     */
   void Start();

    /**
     * @brief
     * Stop current global transaction
     *
     */
   void Stop();

    /**
     * @brief
     * Resume a stopped global transaction
     *
     */
   void Resume();

    /**
     * @brief
     * Cancel the prepared global transaction validation
     *
     */
   void Forget();

    /**
     * @brief
     * Return the transaction mode.
     *
     * @note:
     * see Transaction() for possible values
     *
     */
   TransactionFlags GetFlags() const;

   /**
     * @brief
     * Return the transaction Timeout
     *
     */
   unsigned int GetTimeout() const;

private:

    Transaction(OCI_Transaction *trans);
};

/**
 * @brief
 * Object identififying the SQL datatype DATE.
 *
 * This class wraps the OCILIB object handle OCI_Date and its related methods
 *
 */
class Date : public HandleHolder<OCI_Date *>
{
    friend class Statement;
    friend class Resultset;
    friend class BindArray;
    friend class Object;
	template <class TDataType>
    friend class Collection;
    friend class Message;

public:

    /**
     * @brief
     * Create an empty date object
     *
     */
    Date();

    /**
     * @brief
     * Check if the given date is valid
     *
     */
    bool IsValid() const;

    /**
     * @brief
     * Return the date year value
     *
     */
    int GetYear() const;

    /**
     * @brief
     * Set the date year value
     *
     */
    void SetYear(int value);

    /**
     * @brief
     * Return the date month value
     *
     */
    int GetMonth() const;

    /**
     * @brief
     * Set the date month value
     *
     */
    void SetMonth(int value);

    /**
     * @brief
     * Return the date day value
     *
     */
    int GetDay() const;

    /**
     * @brief
     * Set the date day value
     *
     */
    void SetDay(int value);

    /**
     * @brief
     * Return the date hours value
     *
     */
    int GetHours() const;

    /**
     * @brief
     * Set the date hours value
     *
     */
    void SetHours(int value);

    /**
     * @brief
     * Return the date minutes value
     *
     */
    int GetMinutes() const;

    /**
     * @brief
     * Set the date minutes value
     *
     */
    void SetMinutes(int value);

    /**
     * @brief
     * Return the date seconds value
     *
     */
    int GetSeconds() const;

    /**
     * @brief
     * Set the date seconds value
     *
     */
    void SetSeconds(int value);

    /**
     * @brief
     * Return the number of days with the given date
     *
     * @param other - date to compare
     *
     */
    int DaysBetween(const Date& other) const;

    /**
     * @brief
     * Set the date part
     *
     * @param year  - Year value
     * @param month - Month value
     * @param day   - Day value
     *
     */
    void SetDate(int year, int month, int day);

    /**
     * @brief
     * Set the time part
     *
     * @param hour  - Hour value
     * @param min   - Minute value
     * @param sec   - Second value
     *
     */
    void SetTime(int hour, int min,   int sec);

    /**
     * @brief
     * Set the date and time part
     *
     * @param year  - Year value
     * @param month - Month value
     * @param day   - Day value
     * @param hour  - Hour value
     * @param min   - Minute value
     * @param sec   - Second value
     *
     */
    void SetDateTime(int year, int month, int day, int hour, int min, int sec);

    /**
     * @brief
     * Extract the date parts
     *
     * @param year  - Place holder for year value
     * @param month - Place holder for month value
     * @param day   - Place holder for day value
     *
     */
    void GetDate(int *year, int *month, int *day) const;

    /**
     * @brief
     * Extract time parts
     *
     * @param hour  - Place holder for hour value
     * @param min   - Place holder for minute value
     * @param sec   - Place holder for second value
     *
     */
    void GetTime(int *hour, int *min,   int *sec) const;

    /**
     * @brief
     * Extract the date and time parts
     *
     * @param year  - Place holder for year value
     * @param month - Place holder for month value
     * @param day   - Place holder for day value
     * @param hour  - Place holder for hour value
     * @param min   - Place holder for minute value
     * @param sec   - Place holder for second value
     *
     */
    void GetDateTime(int *year, int *month, int *day, int *hour, int *min, int *sec) const;

    /**
     * @brief
     * Add or subtract days
     *
     * @param days   - Number of days to add/remove
     *
     */
    void AddDays(int days);

    /**
     * @brief
     * Add or subtract months
     *
     * @param months   - Number of months to add/remove
     *
     */
    void AddMonths(int months);

    /**
     * @brief
     * Assign the current system datetime to the current date object
     *
     */
    void SysDate();

    /**
     * @brief
     *  Return the date of next day of the week, after the current date object
     *
     * @param day - Day of the week
     *
     */
    Date NextDay(ostring day) const;

    /**
     * @brief
     * Return the last day of month from the current date object
     *
     */
    Date LastDay() const;

    /**
     * @brief
     * Convert the date from one zone to another zone
     *
     * @param tzSrc - Source zone
     * @param tzDst - Destination zone
     *
     */
    void ChangeTimeZone(ostring tzSrc, ostring tzDst);

	/**
	* @brief
	* Assign to the date object with the value provied by the input date time string
	*
	* @param str    - String date time
	* @param format - format of the date time provided in parameter 'str'
	*
	* @note
	* For date time formats, refer to the Oracle SQL documentation
	*
	*/
    void FromString(ostring str, ostring format = OCI_STRING_FORMAT_DATE);

	/**
	* @brief
	* Convert the date object value to a string
	*
	* @param format - date time format to use
	*
	* @note
	* For date time formats, refer to the Oracle SQL documentation
	*
	*/
	ostring ToString(ostring format = OCI_STRING_FORMAT_DATE) const;

	/**
	* @brief
	* Clone the current instance to a new one performing deep copy
	*
	*/
	Date Clone() const;

	/**
	* @brief
	* Convert the date object value to a string
	*
	* @note
	* It calls ToString() with default date time format
	*
	*/
    operator ostring() const;

    /**
     * @brief
     * Increment the date by 1 day
     *
     */
	Date& operator ++ (int);

    /**
     * @brief
     * Decrement the date by 1 day
     *
     */
	Date& operator -- (int);

    /**
     * @brief
     * Return a new date holding the current date value incremented by the given number of days
     *
     */
	Date operator + (int value);

    /**
     * @brief
	 * Return a new date holding the current date value decremented by the given number of days
	 *
     */
	Date operator - (int value);

    /**
     * @brief
     * Increment the date by the given number of days
     *
     */
	Date& operator += (int value);

    /**
     * @brief
     * Decrement the date by the given number of days
     *
     */
	Date& operator -= (int value);

	/**
	* @brief
	* Indicates if the current date value is equal to the given date value
	*
	*/
	bool operator == (const Date& other) const;

	/**
	* @brief
	* Indicates if the current date value is not equal the given date value
	*
	*/
	bool operator != (const Date& other) const;

	/**
	* @brief
	* Indicates if the current date value is superior to the given date value
	*
	*/
	bool operator > (const Date& other) const;

	/**
	* @brief
	* Indicates if the current date value is inferior to the given date value
	*
	*/
	bool operator < (const Date& other) const;

	/**
	* @brief
	* Indicates if the current date value is superior or equal to the given date value
	*
	*/
	bool operator >= (const Date& other) const;

	/**
	* @brief
	* Indicates if the current date value is inferior or equal to the given date value
	*
	*/
	bool operator <= (const Date& other) const;

private:

    int Compare(const Date& other) const;

    Date(OCI_Date *pDate, Handle *parent = 0);
};

/**
 * @brief
 * Object identififying the SQL datatype INTERVAL.
 *
 * This class wraps the OCILIB object handle OCI_Interval and its related methods
 *
 */
class Interval : public HandleHolder<OCI_Interval *>
{
    friend class Environment;
    friend class Statement;
    friend class Resultset;
    friend class BindArray;
    friend class Object;
	template <class TDataType>
    friend class Collection;

public:

	 /**
	 * @brief
	 * Interval types enumerated values
     *
     */
    enum IntervalTypeValues
    {
		/** Interval unit range is months -> years */
		YearMonth = OCI_INTERVAL_YM,
		/** Interval unit range is seconds -> days */
		DaySecond = OCI_INTERVAL_DS
    };

	/**
	* @brief
	* Interval types
	*
	* Possible values are Interval::IntervalTypeValues
	*
	*/
    typedef Enum<IntervalTypeValues> IntervalType;

	/**
	* @brief
	* Create a new instance of the given type
	*
	* @param type - Interval type to create
	*
	*/

    Interval(IntervalType type);

    IntervalType GetType() const;

    bool IsValid() const;

    int GetYear() const;
    void SetYear(int value);

    int GetMonth() const;
    void SetMonth(int value);

    int GetDay() const;
    void SetDay(int value);

    int GetHours() const;
    void SetHours(int value);

    int GetMinutes() const;
    void SetMinutes(int value);

    int GetSeconds() const;
    void SetSeconds(int value);

    int GetMilliSeconds() const;
    void SetMilliSeconds(int value);

    void GetDaySecond(int *day, int *hour, int *min, int *sec, int *fsec) const;
    void SetDaySecond(int day, int hour, int min, int sec, int fsec);

    void GetYearMonth(int *year, int *month) const;
    void SetYearMonth(int year, int month);

    void FromTimeZone(ostring timeZone);

    void FromString(ostring data);
    ostring ToString(int leadingPrecision = 10, int fractionPrecision = 10) const;

	/**
	* @brief
	* Clone the current instance to a new one performing deep copy
	*
	*/
	Interval Clone() const;

    operator ostring() const;

	/**
	* @brief
	* Return a new Interval holding the sum of the current Interval value and the given Interval value
	*
	*/
	Interval operator + (const Interval& other);

	/**
	* @brief
	* Return a new Interval holding the difference of the current Interval value and the given Interval value
	*
	*/
	Interval operator - (const Interval& other);

	/**
	* @brief
	* Increment the current Value with the given Interval value
	*
	*/
	Interval& operator += (const Interval& other);

	/**
	* @brief
	* Decrement the current Value with the given Interval value
	*
	*/
	Interval& operator -= (const Interval& other);

	/**
	* @brief
	* Indicates if the current Interval value is equal to the given Interval value
	*
	*/
	bool operator == (const Interval& other) const;

	/**
	* @brief
	* Indicates if the current Interval value is not equal the given Interval value
	*
	*/
	bool operator != (const Interval& other) const;

	/**
	* @brief
	* Indicates if the current Interval value is superior to the given Interval value
	*
	*/
	bool operator > (const Interval& other) const;

	/**
	* @brief
	* Indicates if the current Interval value is inferior to the given Interval value
	*
	*/
	bool operator < (const Interval& other) const;

	/**
	* @brief
	* Indicates if the current Interval value is superior or equal to the given Interval value
	*
	*/
	bool operator >= (const Interval& other) const;

	/**
	* @brief
	* Indicates if the current Interval value is inferior or equal to the given Interval value
	*
	*/
	bool operator <= (const Interval& other) const;

private:

	int Compare(const Interval& other) const;

    Interval(OCI_Interval *pInterval, Handle *parent = 0);
};

/**
 *
 * @brief
 * Object identififying the SQL datatype TIMESTAMP.
 *
 * This class wraps the OCILIB object handle OCI_Timestamp and its related methods
 *
 */
class Timestamp : public HandleHolder<OCI_Timestamp *>
{
    friend class Environment;
    friend class Statement;
    friend class Resultset;
    friend class BindArray;
    friend class Object;
    friend class Connection;
	template <class TDataType>
    friend class Collection;

public:

	/**
	* @brief
	* Interval types enumerated values
	*
	*/
    enum TimestampTypeValues
    {
		/** Timestamp does not contains any time zone information */
		NoTimeZone = OCI_TIMESTAMP,
		/** Timestamp contains a given time zone */
		WithTimeZone = OCI_TIMESTAMP_TZ,
		/** Timestamp contains the user's local session tim zone */
		WithLocalTimeZone = OCI_TIMESTAMP_LTZ
    };

	/**
	* @brief
	* Type of Exception
	*
	* Possible values are Timestamp::TimestampTypeValues
	*
	*/
    typedef Enum<TimestampTypeValues> TimestampType;

    Timestamp(TimestampType type);

    TimestampType GetType() const;

    void Construct(int year, int month, int day, int hour, int min, int sec, int fsec, ostring timeZone = OTEXT(""));
    void Convert(const Timestamp& other);

    bool IsValid() const;

    int GetYear() const;
    void SetYear(int value);

    int GetMonth() const;
    void SetMonth(int value);

    int GetDay() const;
    void SetDay(int value);

    int GetHours() const;
    void SetHours(int value);

    int GetMinutes() const;
    void SetMinutes(int value);

    int GetSeconds() const;
    void SetSeconds(int value);

    int GetMilliSeconds() const;
    void SetMilliSeconds(int value);

    void GetDate(int *year, int *month, int *day) const;
    void GetTime(int *hour, int *min,   int *sec, int *fsec) const;
    void GetDateTime(int *year, int *month, int *day, int *hour, int *min, int *sec, int *fsec) const;

    ostring GetTimeZone() const;
    void GetTimeZoneOffset(int *hour, int *min) const;

	static void Substract(const Timestamp &lsh, const Timestamp &rsh, Interval &result);

    void SysTimestamp();

    void FromString(ostring data, ostring format = OCI_STRING_FORMAT_DATE);
    ostring ToString(ostring format = OCI_STRING_FORMAT_DATE, int precision = 0) const;

	/**
	* @brief
	* Clone the current instance to a new one performing deep copy
	*
	*/
	Timestamp Clone() const;

    operator ostring() const;

	/**
	* @brief
	* Increment the timestamp by 1 day
	*
	*/
	Timestamp& operator ++ (int);

	/**
	* @brief
	* Decrement the Timestamp by 1 day
	*
	*/
	Timestamp& operator -- (int);

	/**
	* @brief
	* Return a new Timestamp holding the current Timestamp value incremented by the given number of days
	*
	*/
	Timestamp operator + (int value);

	/**
	* @brief
	* Return a new Timestamp holding the current Timestamp value decremented by the given number of days
	*
	*/
	Timestamp operator - (int value);

	/**
	* @brief
	* Increment the Timestamp by the given number of days
	*
	*/
	Timestamp& operator += (int value);

	/**
	* @brief
	* Decrement the Timestamp by the given number of days
	*
	*/
	Timestamp& operator -= (int value);

	/**
	* @brief
	* Return a new Timestamp holding the sum of the current Timestamp value and the given Interval value
	*
	*/
	Timestamp operator + (const Interval& other);

	/**
	* @brief
	* Return a new Timestamp holding the difference of the current Timestamp value and the given Interval value
	*
	*/
	Timestamp operator - (const Interval& other);

	/**
	* @brief
	* Increment the current Value with the given Interval value
	*
	*/
	Timestamp& operator += (const Interval& other);

	/**
	* @brief
	* Decrement the current Value with the given Interval value
	*
	*/
	Timestamp& operator -= (const Interval& other);

	/**
	* @brief
	* Indicates if the current Timestamp value is equal to the given Timestamp value
	*
	*/
	bool operator == (const Timestamp& other) const;

	/**
	* @brief
	* Indicates if the current Timestamp value is not equal the given Timestamp value
	*
	*/
	bool operator != (const Timestamp& other) const;

	/**
	* @brief
	* Indicates if the current Timestamp value is superior to the given Timestamp value
	*
	*/
	bool operator > (const Timestamp& other) const;

	/**
	* @brief
	* Indicates if the current Timestamp value is inferior to the given Timestamp value
	*
	*/
	bool operator < (const Timestamp& other) const;

	/**
	* @brief
	* Indicates if the current Timestamp value is superior or equal to the given Timestamp value
	*
	*/
	bool operator >= (const Timestamp& other) const;

	/**
	* @brief
	* Indicates if the current Timestamp value is inferior or equal to the given Timestamp value
	*
	*/
	bool operator <= (const Timestamp& other) const;

private:

	int Compare(const Timestamp& other) const;

    Timestamp(OCI_Timestamp *pTimestamp, Handle *parent = 0);
};

/**
 * @brief
 * Object identififying the SQL datatype CLOB.
 *
 * This class wraps the OCILIB object handle OCI_Lob of type OCI_CLOB and its related methods
 *
 */
class Clob : public HandleHolder<OCI_Lob *>
{
    friend class Statement;
    friend class Resultset;
    friend class BindArray;
    friend class Object;
	template <class TDataType>
    friend class Collection;

public:

	/**
	* @brief
	* Seek Modes enumerated values
	*
	*/
	enum SeekModeValues
    {
		/** Set the current position within the stream to the given position */
        Set = OCI_SEEK_SET,
		/** Set the current position within the stream end position */
        End = OCI_SEEK_END,
		/** Set the current position within the stream to the given value offset from the current position */
		Current = OCI_SEEK_CUR
    };

	/**
	* @brief
	* Seek Modes
	*
	* Possible values are Clob::SeekModeValues
	*
	*/
    typedef Enum<SeekModeValues> SeekMode;

	/**
	* @brief
	* Open Modes enumerated values
	*
	*/
	enum OpenModeValues
    {
		/** Stream is opened for read access */
        ReadOnly = OCI_LOB_READONLY,
		/** Stream is opened for read / write access */
		ReadWrite = OCI_LOB_READWRITE
    };

	/**
	* @brief
	* Open Modes
	*
	* Possible values are Clob::OpenModeValues
	*
	*/
	typedef Enum<OpenModeValues> OpenMode;

    Clob(const Connection &connection);

    ostring Read(unsigned int size);
    unsigned int Write(ostring content);
    unsigned int Append(ostring content);
    bool Seek(SeekMode seekMode, big_uint offset);

    big_uint GetOffset() const;
    big_uint GetLength() const;
    big_uint GetMaxSize() const;
    big_uint GetChunkSize() const;

	Connection GetConnection() const;

    void Truncate(big_uint size);
    big_uint Erase(big_uint offset, big_uint size);
    void Copy(Clob &dest, big_uint offset, big_uint offsetDest, big_uint size) const;

    bool IsTemporary() const;

    void Open(OpenMode mode);
    void Flush();
    void Close();

    void EnableBuffering(bool value);

	/**
	* @brief
	* Clone the current instance to a new one performing deep copy
	*
	*/
	Clob Clone() const;
    operator ostring() const;

	Clob& operator += (const Clob& other);
	bool operator == (const Clob& other) const;
	bool operator != (const Clob& other) const;

private:

	void Append(const Clob &other);
	bool Equals(const Clob &other) const;

    Clob(OCI_Lob *pLob, Handle *parent = 0);
};

/**
 *
 * @brief
 * Object identififying the SQL datatype BLOB.
 *
 * This class wraps the OCILIB object handle OCI_Lob of type OCI_BLOB and its related methods
 *
 */
class Blob : public HandleHolder<OCI_Lob *>
{
    friend class Statement;
    friend class Resultset;
    friend class BindArray;
    friend class Object;
	template <class TDataType>
    friend class Collection;

public:

	/**
	* @brief
	* Seek Modes enumerated values
	*
	*/
	enum SeekModeValues
	{
		/** Set the current position within the stream to the given position */
		Set = OCI_SEEK_SET,
		/** Set the current position within the stream end position */
		End = OCI_SEEK_END,
		/** Set the current position within the stream to the given value offset from the current position */
		Current = OCI_SEEK_CUR
	};

	/**
	* @brief
	* Seek Modes
	*
	* Possible values are Blob::SeekModeValues
	*
	*/
	typedef Enum<SeekModeValues> SeekMode;

	/**
	* @brief
	* Open Modes enumerated values
	*
	*/
	enum OpenModeValues
	{
		/** Stream is opened for read access */
		ReadOnly = OCI_LOB_READONLY,
		/** Stream is opened for read / write access */
		ReadWrite = OCI_LOB_READWRITE
	};

	/**
	* @brief
	* Open Modes
	*
	* Possible values are Blob::OpenModeValues
	*
	*/
	typedef Enum<OpenModeValues> OpenMode;

    Blob(const Connection &connection);

	Raw Read(unsigned int size);
	unsigned int Write(const Raw &value);
	unsigned int Append(const Raw &value);
    bool Seek(SeekMode seekMode, big_uint offset);

    big_uint GetOffset() const;
    big_uint GetLength() const;
    big_uint GetMaxSize() const;
    big_uint GetChunkSize() const;

	Connection GetConnection() const;

    void Truncate(big_uint size);
    big_uint Erase(big_uint offset, big_uint size);
    void Copy(Blob &dest, big_uint offset, big_uint offsetDest, big_uint size) const;

    bool IsTemporary() const;

    void Open(OpenMode mode);
    void Flush();
    void Close();

    void EnableBuffering(bool value);

	/**
	* @brief
	* Clone the current instance to a new one performing deep copy
	*
	*/
	Blob Clone() const;

	Blob& operator += (const Blob& other);
	bool operator == (const Blob& other) const;
	bool operator != (const Blob& other) const;

private:

	void Append(const Blob &other);
	bool Equals(const Blob &other) const;

    Blob(OCI_Lob *pLob, Handle *parent = 0);
};

/**
 *
 * @brief
 * Object identififying the SQL datatype BFILE.
 *
 * This class wraps the OCILIB object handle OCI_File and its related methods
 *
 */
class File : public HandleHolder<OCI_File *>
{
    friend class Statement;
    friend class Resultset;
    friend class BindArray;
    friend class Object;
	template <class TDataType>
    friend class Collection;

public:

	/**
	* @brief
	* Seek Modes enumerated values
	*
	*/
	enum SeekModeValues
	{
		/** Set the current position within the stream to the given position */
		Set = OCI_SEEK_SET,
		/** Set the current position within the stream end position */
		End = OCI_SEEK_END,
		/** Set the current position within the stream to the given value offset from the current position */
		Current = OCI_SEEK_CUR
	};

	/**
	* @brief
	* Seek Modes
	*
	* Possible values are File::SeekModeValues
	*
	*/
	typedef Enum<SeekModeValues> SeekMode;

    File(const Connection &connection);
    File(const Connection &connection, ostring directory, ostring name);

	Raw Read(unsigned int size);
    bool Seek(SeekMode seekMode, big_uint offset);

    bool Exists() const;

    big_uint GetOffset() const;
    big_uint GetSize() const;

	Connection GetConnection() const;

    void SetInfos(ostring directory, ostring name);

    ostring GetName() const;
    ostring GetDirectory() const;

    void Open();
    void Close();
    bool IsOpened() const;

	/**
	* @brief
	* Clone the current instance to a new one performing deep copy
	*
	*/
	File Clone() const;

	bool operator == (const File& other) const;
	bool operator != (const File& other) const;

private:

	bool Equals(const File &other) const;

    File(OCI_File *pFile, Handle *parent = 0);
};

/**
 * @brief
 * Provides type information on Oracle Database objects
 *
 * This class wraps the OCILIB object handle OCI_TypeInfo and its related methods
 *
 */
class TypeInfo : public HandleHolder<OCI_TypeInfo *>
{
    friend class Object;
    friend class Reference;
	template <class TDataType>
    friend class Collection;
    friend class Column;
public:

	/**
	* @brief
	* Type of object information enumerated values
	*
	*/
    enum TypeInfoTypeValues
    {
		/** Database Table information */
        Table = OCI_TIF_TABLE,
		/** Database View information */
		View = OCI_TIF_VIEW,
		/** Database type information */
		Type = OCI_TIF_TYPE
    };

	/**
	* @brief
	* Type of object information
	*
	* Possible values are TypeInfo::TypeInfoTypeValues
	*
	*/
    typedef Enum<TypeInfoTypeValues> TypeInfoType;

    TypeInfo(const Connection &connection, ostring name, TypeInfoType type);

    TypeInfoType GetType() const;
    ostring GetName() const;
    Connection GetConnection() const;

    unsigned int GetColumnCount() const;
    Column GetColumn(unsigned int index) const;

private:

    TypeInfo(OCI_TypeInfo *pTypeInfo);
};

/**
 * @brief
 * Object identififying the SQL datatype OBJECT.
 *
 * This class wraps the OCILIB object handle OCI_Object and its related methods
 *
 */
class Object : public HandleHolder<OCI_Object *>
{
    friend class Statement;
    friend class Resultset;
    friend class BindArray;
    friend class Reference;
	template <class TDataType>
    friend class Collection;
	friend class Message;

public:

	/**
	* @brief
	* Object Type enumerated values
	*
	*/
    enum ObjectTypeValues
    {
		/** The object is persistent in the database  */
        Persistent = OCI_OBJ_PERSISTENT,
		/** The object is Transient */
		Transient = OCI_OBJ_TRANSIENT,
		/** The object is a value member of another object	*/
		Value = OCI_OBJ_VALUE
    };

	/**
	* @brief
	* Object Type
	*
	* Possible values are Object::ObjectTypeValues
	*
	*/
    typedef Enum<ObjectTypeValues> ObjectType;

    Object(const TypeInfo &typeInfo);

    bool IsAttributeNull(ostring name) const;
    void SetAttributeNull(ostring name);

    TypeInfo GetTypeInfo() const;
    Reference GetReference() const;

    ObjectType GetType() const;

    template<class TDataType>
    TDataType Get(ostring name) const;

    template<class TDataType>
    void Set(ostring name, const TDataType &value);

	/**
	* @brief
	* Clone the current instance to a new one performing deep copy
	*
	*/
	Object Clone() const;

    ostring ToString() const;
    operator ostring() const;

private:

    Object(OCI_Object *pObject, Handle *parent = 0);
};

/**
 * @brief
 * Object identififying the SQL datatype REF.
 *
 * This class wraps the OCILIB object handle OCI_Ref and its related methods
 *
 */
class Reference : public HandleHolder<OCI_Ref *>
{
    friend class Statement;
    friend class Resultset;
    friend class BindArray;
    friend class Object;
	template <class TDataType>
    friend class Collection;

public:

    Reference(const TypeInfo &typeInfo);

    TypeInfo GetTypeInfo() const;
    Object GetObject() const;

    bool IsReferenceNull() const;
    void SetReferenceNull();

	/**
	* @brief
	* Clone the current instance to a new one performing deep copy
	*
	*/
	Reference Clone() const;

    ostring ToString() const;
    operator ostring() const;

private:

    Reference(OCI_Ref *pRef, Handle *parent = 0);
};

/**
 * @brief
 * Object identififying the SQL datatype VARRAY and NESTED TABLE.
 *
 * This class wraps the OCILIB object handle OCI_Coll and its related methods
 *
 */
template <class TDataType>
class Collection : public HandleHolder<OCI_Coll *>
{
    friend class Statement;
    friend class Resultset;
    friend class BindArray;
    friend class Object;
	template <class TDataType>
    friend class CollectionIterator;

	template <class TOtherDataType>
	friend class Collection;
public:

	/**
	* @brief
	* Collection type enumerated values
	*
	*/
    enum CollectionTypeValues
    {
		/** Collection is a VARRAY */
        Varray = OCI_COLL_VARRAY,
		/** Collection is a NESTED TABLE */
		NestedTable = OCI_COLL_NESTED_TABLE
    };

	/**
	* @brief
	* Collection type
	*
	* Possible values are Collection::CollectionTypeValues
	*
	*/
    typedef Enum<CollectionTypeValues> CollectionType;

    Collection(const TypeInfo &typeInfo);

    CollectionType GetType() const;
    unsigned int GetMax() const;
    unsigned int GetSize() const;
    unsigned int GetCount() const;

    void Truncate(unsigned int size);
    void Clear();

    bool IsElementNull(unsigned int index) const;
    void SetElementNull(unsigned int index);

    bool Delete(unsigned int index) const;

    TDataType Get(unsigned int index) const;

	void Set(unsigned int index, const TDataType &value);

    void Append(const TDataType &data);

    TypeInfo GetTypeInfo() const;

	/**
	* @brief
	* Clone the current instance to a new one performing deep copy
	*
	*/
	Collection Clone() const;

    ostring ToString() const;
    operator ostring() const;

	class Element
	{
		friend class Iterator;

	public:
		Element(Collection &coll, unsigned int pos);
		operator TDataType() const;
		Element& operator = (TDataType value);
		bool IsNull() const;
		void SetNull();

	private:
		typename Collection & _coll;
		unsigned int _pos;
	};

	class Iterator : public std::iterator<std::bidirectional_iterator_tag, TDataType>
	{

	public:
			
		Iterator(Collection &collection, unsigned int pos);
		Iterator(const Iterator& other);

		bool operator== (const Iterator& other);
		bool operator!= (const Iterator& other);

		Element& operator*();

		Iterator &operator--();
		Iterator operator--(int);

		Iterator &operator++();
		Iterator operator++(int);

	private:
		Element _elem;
	};
	
    typedef Iterator iterator;

	Iterator begin();
	Iterator end();

	Element operator [] (int index);

private:

    static TDataType GetElem(OCI_Elem *elem, Handle *parent);

	static void SetElem(OCI_Elem *elem, const TDataType &value);

    Collection(OCI_Coll *pColl, Handle *parent = 0);
};

/**
 * @brief
 * Object identififying the SQL datatype LONG.
 *
 * This class wraps the OCILIB object handle OCI_LONG of type OCI_CLONG and its related methods
 *
 */
class Clong : public HandleHolder<OCI_Long *>
{
    friend class Statement;
    friend class Resultset;
    friend class BindArray;

public:

	/**
	* @brief
	* Contructor
	*
	* @param statement - statement object that will handle operations on the Clong buffer
	*
	*/
    Clong(const Statement &statement);

	/**
	* @brief
	* Write the given string into the Clong Object
	*
	* @param content - string to write
	*
	* @return
	* Number of character written
	*
	*/
	unsigned int Write(ostring content);

	/**
	* @brief
	* Return the buffer length
	*
	*/
	unsigned int GetLength() const;

	/**
	* @brief
	* Return the string read from a fetch sequence
	*
	*/
	ostring GetContent() const;

private:

    Clong(OCI_Long *pLong, Handle *parent = 0);
};

/**
 * @brief
 * Object identififying the SQL datatype LONG RAW
 *
 * This class wraps the OCILIB object handle OCI_LONG of type OCI_BLONG and its related methods
 *
 */
class Blong : public HandleHolder<OCI_Long *>
{
    friend class Statement;
    friend class Resultset;
    friend class BindArray;

public:

	/**
	* @brief
	* Contructor
	*
	* @param statement - statement object that will handle operations on the Blong buffer
	*
	*/
    Blong(const Statement &statement);

	/**
	* @brief
	* Write the given raw buffer into the Blong Object
	*
	* @param buffer - the pointer to a buffer
	* @param len    - Number of bytes to write from the given buffer
	*
	* @return
	* Number of bytes written
	*
	*/
	unsigned int Write(const Raw &value);

	/**
	* @brief
	* Return the buffer size
	*
	*/
    unsigned int GetSize() const;

	/**
	* @brief
	* Return the internal raw buffer read from a fetch sequence
	*
	*/
	Raw GetContent() const;

private:

    Blong(OCI_Long *pLong, Handle *parent = 0);
};

/**
 * @brief
 * Provides SQL bind informations
 *
 * This class wraps the OCILIB object handle OCI_Bind and its related methods
 *
 */
class BindInfo : public HandleHolder<OCI_Bind *>
{
    friend class Statement;

public:

	/**
	* @brief
	* Bind direction enumerated values
	*
	*/
    enum BindDirectionValues
    {
		/** Input bind variable (will be not modified as it is an input value for the server) */
        In = OCI_BDM_IN,
		/** Output bind variable (will be modified  as it is an output vaule by the server ) */
		Out = OCI_BDM_OUT,
		/** Input / Output bind variable (can be modified as it is an input value that can be modified by the server) */
		InOut = OCI_BDM_IN_OUT
    };

	/**
	* @brief
	* Bind direction
	*
	* Possible values are BindInfo::BindDirectionValues
	*
	*/
    typedef Enum<BindDirectionValues> BindDirection;

	/**
	* @brief
	* Return the name of the bind object
	*
	*/
    ostring GetName() const;

	/**
	* @brief
	* Return the OCILIB type of the data associated with the bind object
	*
	*/
	DataType GetType() const;

	/**
	* @brief
	* Return the OCILIB object subtype of a column
	*
	* @note
	* This call is valid for the following OCILIB types:
	* - Scalar numeric types
	* - Clong and Blong
	* - Clob and Blob
	* - File
	* - Timestamp
	* - Interval
	*
	* @warning
	* - The returned values must be casted to the matching C++ class GetType() property type.
	* - For scalar numeric types, returned value must be casted to ocilib::NumericType.
	* - For a non valid type, it returns 0.
	*
	*/
    unsigned int GetSubType() const;

	/**
	* @brief
	* Return the number of elements associated with the bind object
	*
	* @return
	* - For single binds, it returns 1
	* - For vector binds, it returns the number of element in the bind array
	*
	*/
    unsigned int GetDataCount() const;

	/**
	* @brief
	* Return the statement associated with the bind object
	*
	*/
    Statement GetStatement() const;

	/**
	* @brief
	* Mark as null or not null the current bind real value(s) used in SQL statements
	*
	* @param index - Only valid for vectors : index of the element to check
	*
	* @note
	* There is no notion of null value in C C++ for scalar types.
	* It's necessary to explicitly tell Oracle that the bind has a null value.
	* It must be done before an Execute() call
	*
	* @warning
	* For handled based datatypes (non scalar types), OCILIB performs an extra
	* check on handles and set the bind status to null is the handle is null
	*
	* @warning
	* Index starts with 1
	*
	*/
	void SetDataNull(bool value, unsigned int index = 1);

	/**
	* @brief
	* Check if the current bind value(s) used in SQL statements is marked as NULL
	*
	* @param index - Only valid for vectors : index of the element to check
	*
	* @note
	* If the bind is related to a single host variable, don't use the parameter index
	* If the bind is related to host vectors, the parameter 'index' refers to the index in the vector
	*
	* @warning
	* Index starts with 1
	*
	*/
	bool IsDataNull(unsigned int index = 1) const;

	/**
	* @brief
	* Set the charset form of the given character based bind object
	*
	* @param value - charset form
	*
	* @note
	* This call has to be made after Statement::Prepare() but before Statement::Execute()
	*
	* @warning
	* This call does nothing the bind datatype is not ocilib::TypeString or ocilib::TypeLong
	*
	*/
    void SetCharsetForm(Environment::CharsetForm value);

	/**
	* @brief
	* Get the direction mode
  	*
	*/
    BindDirection GetDirection() const;

private:

    BindInfo(OCI_Bind *pBind, Handle *parent);
};

/**
* @brief
* Object used for executing SQL or PL/SQL statement and returning the produced results.
*
* This class wraps the OCILIB object handle OCI_Statement and its related methods
*
*/
class Statement : public HandleHolder<OCI_Statement *>
{
    friend class Exception;
    friend class Resultset;
    friend class Clong;
    friend class Blong;
    friend class BindInfo;
	friend class BindObject;

public:

	/**
	* @brief
	* Statement Type enumerated values
    *
	*/
    enum StatementTypeValues
    {
		/** SELECT statement */
        TypeSelect = OCI_CST_SELECT,
		/** UPDATE statement */
		TypeUpdate = OCI_CST_UPDATE,
		/** DELETE statement */
		TypeDelete = OCI_CST_DELETE,
		/** INSERT statement */
		TypeInsert = OCI_CST_INSERT,
		/** CREATE statement */
		TypeCreate = OCI_CST_CREATE,
		/** DROP statement */
		TypeDrop = OCI_CST_DROP,
		/** ALTER statement */
		TypeAlter = OCI_CST_ALTER,
		/** BEGIN statement */
		TypeBegin = OCI_CST_BEGIN,
		/** DECLARE statement */
		TypeDeclare = OCI_CST_DECLARE,
		/** CALL statement */
		TypeCall = OCI_CST_CALL,
    };

	/**
	* @brief
	* Statement Type
	*
	* Possible values are Statement::StatementTypeValues
	*
	*/
    typedef Enum<StatementTypeValues> StatementType;

	/**
	* @brief
	* Fetch Modes enumerated values
	*
	*/
    enum FetchModeValues
    {
		/** Statement is forward only */
        FetchForward = OCI_SFM_DEFAULT,
		/** Statement is scrollable */
		FetchScrollable = OCI_SFM_SCROLLABLE
    };

	/**
	* @brief
	* Fetch Modes
	*
	* Possible values are Statement::FetchModeValues
	*
	*/
    typedef Enum<FetchModeValues> FetchMode;

	/**
	* @brief
	* Bind Modes enumerated values
	*
	*/
    enum BindModeValues
    {
		/** Bind variables are binded by name */
        BindByPosition =  OCI_BIND_BY_POS,
		/** Bind variables are binded by position */
		BindByName = OCI_BIND_BY_NAME
    };

	/**
	* @brief
	* Bind Modes
	*
	* Possible values are Statement::BindModeValues
	*
	*/
    typedef Enum<BindModeValues> BindMode;

	/**
	* @brief
	* LONG datatype mapping modes enumerated values
	*
	*/
    enum LongModeValues
    {
		/** LONG and LONG RAW are mapped to Long objects */
        LongExplicit = OCI_LONG_EXPLICIT,
		/** LONG and LONG RAW are mapped to ostring objects */
		LongImplicit = OCI_LONG_IMPLICIT
    };

	/**
	* @brief
	* LONG datatype mapping modes
	*
	* Possible values are Statement::LongModeValues
	*
	*/
    typedef Enum<LongModeValues> LongMode;

    Statement(const Connection &connection);
    ~Statement();

	/**
	* @brief
	* Return the connection handle associated with a statement handle
	*
	*/
    Connection GetConnection() const;

	/**
	* @brief
	* Describe the select list of a SQL select statement.
	*
	* @param sql  - SELECT sql statement
	*
	* @note
	* This call sends the SELECT SQL order to the server for retrieving the
	* description of the select order only.
	* The command is not executed.
	* This call is only useful to retreive information on the associated resultet
	* Call GetResultet() after Describe() to access to SELECT list information
	*
	* @note
	* This call prepares the statement (internal call to Prepare()) and ask
	* the Oracle server to describe the output SELECT list.
	* Execute() can be called after Desbribe() in order to execute the
	* statement, which means that the server will parse, and describe again the SQL
	* order.
	*
	* @warning
	* Do not use Desbribe() unless you're only interested in the resultset
	* information because the statement will be parsed again when executed and thus
	* leading to unnecessary server roundtrips and less performance
	*
	*/
    void Describe(ostring sql);

	/**
	* @brief
	* Parse a SQL statement or PL/SQL block.
	*
	* @param sql  - SQL order - PL/SQL block
	*
	* @note
	* This call sends the SQL or PL/SQL command to the server for parsing only.
	* The command is not executed.
	* This call is only useful to check is a command is valid or not.
	*
	* @note
	* This call prepares the statement (internal call to Prepare()) and ask
	* the Oracle server to parse its SQL or PL/SQL command.
	* Execute() can be call after Parse() in order to execute the
	* statement, which means that the server will reparse again the command.
	*
	* @warning
	* Do not use Parse() unless you're only interested in the parsing result
	* because the statement will be parsed again when executed and thus leading to
	* unnecessary server roundtrips and less performance
	*
	*/
    void Parse(ostring sql);

	/**
	* @brief
	* Prepare a SQL statement or PL/SQL block.
	*
	* @param sql  - SQL order or PL/SQL block
	*
	* @note
	* With version 1.3.0 and above, do not call this function for fetched statements (REF cursors)
	*
	*/
    void Prepare(ostring sql);

	/**
	* @brief
	* Execute a prepared SQL statement or PL/SQL block.
	*
	*/
    void Execute();

	/**
	* @brief
	* Prepare and execute a SQL statement or PL/SQL block.
	*
	* @param sql  - SQL order - PL/SQL block
	*
	*/
    void Execute(ostring sql);

	/**
	* @brief
	* Return the number of rows affected by the SQL statement
    *
	*
	* The returned value is :
	*  - For UPDATEs : number of rows updated
	*  - For INSERTs : number of rows inserted
	*  - For DELETEs : number of rows deleted
	*
	* @note
	* For SELECTs  statements, use GetRowCount() instead
	*
	*/
    unsigned int GetAffectedRows() const;

	/**
	* @brief
	* Return the last SQL or PL/SQL statement prepared or executed by the statement
	*
	*/
    ostring GetSql()  const;

	/**
	* @brief
	* Retrieve the resultset from an executed statement
	*
	* @note
	* See @ref OcilibCApiFetching for more details about what statements can return resultsets
	*
	* @warning
	* If the statement has not been prepared and executed, null resultset object will be returned
	*
	*/
    Resultset GetResultset();

	/**
	* @brief
	* Retrieve the next available resultset
	*
	* @note
	* it is only valid for the following statements:
	* - Statements executing SQL UPDATE/DELETE using a RETURNING INTO clause
	* - Statements implicitly returned from PL/SQL procedure or blocks (new feature in Oracle 12cR1) using
	*   DBMS_SQL.RETURN_RESULT()
	*
	* @note
	* SQL statements with a 'returning' clause can return multiple resultsets.
	* When arrays of program variables are binded to the statement, Oracle will
	* execute the statement for every row (iteration).
	* Each iteration generates a resultset that can be fetched like regular ones.
	*
	* @note
	* Starting withOracle 12cR1, PL/SQ procedure and blocks ca return return multiple implicit resultsets
	* Refer to  Oracle documentation for more informationb.
	*
	*/
    Resultset GetNextResultset();

	/**
	* @brief
	* Set the input array size for bulk operations
	*
	* @param size - Array size
	*
	* @warning
	* Do not use SetBindArraySize() for PL/SQL tables binding
	*
	* @note
	* SetBindArraySize() is used to set the size of input bind array when using
	* arrays for DML statements.
	* SetBindArraySize() MUST be called to set the maximum size of the arrays
	* to bind to the statement before any of its execution. This initial call must
	* be bone AFTER OPrepare() and BEFORE any Bind() call taking vectors as parameter.
	*
	* @note
	* SetBindArraySize() can optionally be called before any later Execute()
	* call in order to notify the statement of the exact number of elements
	* populating the input arrays for the next execution. The array size passed to
	* later SetBindArraySize() calls cannot be greater than the initial size
	* otherwise an exception will be thrown.
	*
	*/
    void SetBindArraySize(unsigned int size);

	/**
	* @brief
	* Return the current input array size for bulk operations
	*
	*/
    unsigned int GetBindArraySize() const;

	/**
	* @brief
	* Allow different host variables to be binded using the same bind name or
	* position between executions of a prepared statement
    *
	* @param value - Rebinding mode allowed
	*
	* @note
	* Default value is false
	*
	* @warning
	* When using rebinding feature, host variable rebinded to a previously allocated
	* bind MUST be of the same datatype !
	*
	*/
    void AllowRebinding(bool value);

	/**
	* @brief
	* Indicate if rebinding is allowed on the statement
	*
	* @note
	* See AllowRebinding() for more details
	*
	*/
    bool IsRebindingAllowed() const;

	/**
	* @brief
	* Return the index of the bind from its name belonging to the statement
	*
	* @param name - Bind variable name
	*
	* @warning
	* The bind name is case insensitive
	*
	* @note
	* Bind indexes start with 1 in OCILIB
	*
	* @return
	* Bind index on success or zero if the bind does not exists
	*
	*/
	unsigned int GetBindIndex(ostring name) const;

	/**
	* @brief
	* Return the number of binds currently associated to a statement
	*
	*/
    unsigned int GetBindCount() const;

	/**
	* @brief
	* Return the bind at the given index in the internal array of bind objects
	*
	* @param index - Bind position
	*
	* @warning
	* Index starts at 1.
	*
	* @note
	* Bind handle are created sequentially. For example, the third call to a
	* Bind() call generates a bind object of index 3.
	*
	*/
    BindInfo GetBind(unsigned int index) const;

	/**
	* @brief
	* Return a bind handle from its name
	*
	* @param name - Bind variable name
	*
	* @note
	* Bind names must include a semicolon at the beginning.
	*
	*/
    BindInfo GetBind(ostring name) const;

	/**
	* @brief
	* Bind an host variable
	*
	* @tparam TDataType - C++ type of the host variable
    *
	* @param name  - Bind name
	* @param value - Host variable
	* @param mode  - bind direction mode
	*
	* @warning
	* This method has builtin specialized versions for all supported types except ostring, Clong and Blong variables.
	* For binding ostring, Clong and Blong variables, use the version with an extra parameter.
	*
	* @note
	* It is not necessary to specify the template datatype in the bind call as all possible specializations can be resolved
	* automatically from the arguments.
	*
	*/	
    template <class TDataType>
	void Bind(ostring name, TDataType &value, BindInfo::BindDirection mode);

	/**
	* @brief
	* Bind an host variable with more information
	*
	* @tparam TDataType  - C++ type of the host variable
	* @tparam TExtraInfo - C++ type if the extra information needed for the bind call
	*
	* @param name      - Bind name
	* @param value     - Host variable
	* @param extraInfo - Extra information needed for the bind call
	* @param mode      - bind direction mode
	*
	* @warning
	* This method has builtin specialized versions for ostring, Clong and Blong variables.
	* Pass the maximum length/size of the variable in the parameter extraInfo
	*
	* @note
	* It is not necessary to specify the template datatype in the bind call as all possible specializations can be resolved
	* automatically from the arguments.
	*
	*/
    template <class TDataType, class TExtraInfo>
    void Bind(ostring name, TDataType &value, TExtraInfo extraInfo, BindInfo::BindDirection mode);

	/**
	* @brief
	* Bind a vector of host variables
	*
	* @tparam TDataType - C++ type of the host variable
	*
	* @param name   - Bind name
	* @param values - Vector of host variables
	* @param mode   - bind direction mode
	*
	* @warning
	* This method has builtin specialized versions for all C++ native scalar types, Datetime and Statement objects.
	* For others types (ostring, Clong, Blong, RawPointer , Object, Reference, Collection, Timestamp, Interval), use versions with extra parameters.
	*
	* @note
	* It is not necessary to specify the template datatype in the bind call as all possible specializations can be resolved
	* automatically from the arguments.
	*
	*/
    template <class TDataType>
    void Bind(ostring name, std::vector<TDataType> &values, BindInfo::BindDirection mode);

	/**
	* @brief
	* Bind a vector of host variables with Oracle type information
	*
	* @tparam TDataType  - C++ type of the host variable
	*
	* @param name     - Bind name
	* @param values   - Vector of host variables
	* @param typeInfo - Object type information
	* @param mode     - bind direction mode
	*
	* @warning
	* This method has builtin specialized versions for Object, Reference, Collection.
	*
	* @note
	* It is not necessary to specify the template datatype in the bind call as all possible specializations can be resolved
	* automatically from the arguments.
	*
	*/
	template <class TDataType>
	void Bind(ostring name, std::vector<TDataType> &values, TypeInfo &typeInfo, BindInfo::BindDirection mode);

	/**
	* @brief
	* Bind a vector of host variables with more information
	*
	* @tparam TDataType  - C++ type of the host variable
	* @tparam TExtraInfo - C++ type if the extra information needed for the bind call
	*
	* @param name      - Bind name
	* @param value     - Vector of host variables
	* @param extraInfo - Extra information needed for the bind call
	* @param mode      - bind direction mode
	*
	* @warning
	* This method has builtin specialized versions for ostring, RawPointer , Clong, Blong, Timestamp, Interval variables.
	* - For ostring, Clong, Blong, RawPointer : Pass the maximum length/size of variables in the parameter extraInfo
	* - For Timestamp, Interval : Pass a value of the matching C++ class GetType() property type OR the underlying enumeration type.
	*
	* @note
	* It is not necessary to specify the template datatype in the bind call as all possible specializations can be resolved
	* automatically from the arguments.
	*
	*/
    template <class TDataType, class TExtraInfo>
    void Bind(ostring name, std::vector<TDataType> &values, TExtraInfo extraInfo, BindInfo::BindDirection mode);

	/**
	* @brief
	* Register a host variable as an output for a column present in a SQL RETURNING INTO  clause
	*
	* @tparam TDataType - C++ type of the host variable
	*
	* @param name  - Bind name
	*
	* @warning
	* This method has builtin specialized versions for all supported types except:
	* - Timestamp and Interval, Object and Reference : use the version that takes a TypeInfo parameter
    * - ostring and RawPointer : use the version that takes an extraInfo parameter
	*
	* @note
	* Statement, Blong and Clong are not supported for register calls
	*
	* @warning
	* It is necessary to specify the template datatype in the register call
	*
	*/
    template <class TDataType>
    void Register(ostring name);

	/**
	* @brief
	* Register a host variable with Oracle type information as an output for a column present in a SQL RETURNING INTO  clause
	*
	* @tparam TDataType  - C++ type of the host variable
	* @tparam TExtraInfo - C++ type if the extra information needed for the bind call
    *
	* @param name     - Bind name
	* @param extraInfo - Extra information needed for the bind call
	*
	* @warning
	* This method has builtin specialized versions for Object and Reference.
	*
	* @warning
	* It is necessary to specify the template datatype in the register call
	*
	*/
    template <class TDataType, class TExtraInfo>
	void Register(ostring name, TExtraInfo& extraInfo);

	/**
	* @brief
	* Register a host variable with more information as an output for a column present in a SQL RETURNING INTO  clause
	*
	* @tparam TDataType  - C++ type of the host variable
	* @tparam TExtraInfo - C++ type if the extra information needed for the bind call
	*
	* @param name      - Bind name
	* @param extraInfo - Extra information needed for the bind call
	*
	* @warning
	* This method has builtin specialized versions for ostring and RawPointer variables.
	*  Pass the maximum length/size of variables in the parameter extraInfo
	*
	* @note
	* It is necessary to specify the template datatype in the register call
	*
	*/
	template <class TDataType, class TExtraInfo>
    void Register(ostring name, TExtraInfo extraInfo);

	/**
	* @brief
	* Return the type of a SQL statement
	*
	*/
    StatementType GetStatementType() const;

	/**
	* @brief
	* Return the error position (in terms of characters) in the SQL statement
	* where the error occurred in case of SQL parsing error
	*
	* @note
	* Positions start at 1.
	*
	*/
    unsigned int GetSqlErrorPos() const;

	/**
	* @brief
	* Set the fetch mode of a SQL statement
	*
	* @param value - fetch mode value
	*
	* @warning
	* SetFetchMode() MUST be called before any Execute() call
	*
	*/
    void SetFetchMode(FetchMode value);

	/**
	* @brief
	* Return the fetch mode of a SQL statement
	*
	* @param stmt - Statement handle
	*
	* @note
	* Default value is Statment::FetchForward
	*
	*/
    FetchMode GetFetchMode() const;

	/**
	* @brief
	* Set the binding mode of a SQL statement
	*
	* @param value - binding mode value
	*
	*/
    void SetBindMode(BindMode value);

	/**
	* @brief
	* Return the binding mode of a SQL statement
	*
	* @note
	* Default value is Statment::BindByName
	*
	*/
    BindMode GetBindMode() const;

	/**
	* @brief
	* Set the number of rows fetched per internal server fetch call
	*
	* @param size - number of rows to fetch
	*
	*/
    void SetFetchSize(unsigned int value);

	/**
	* @brief
	* Return the number of rows fetched per internal server fetch call
	*
	* @note
	* Default value is set to constant OCI_FETCH_SIZE
	*
	*/
    unsigned int GetFetchSize() const;

	/**
	* @brief
	* Set the number of rows pre-fetched by OCI Client
	*
	* @param size - number of rows to pre-fetch
	*
	* @note
	* To turn off pre-fetching, set both attributes (size and memory) to 0.
	*
	*/
    void SetPrefetchSize(unsigned int value);

	/**
	* @brief
	* Return the number of rows pre-fetched by OCI Client
	*
	* @note
	* Default value is set to constant OCI_PREFETCH_SIZE
	*
	*/
    unsigned int GetPrefetchSize() const;

	/**
	* @brief
	* Set the amount of memory pre-fetched by OCI Client
	*
	* @param value - amount of memory to fetch
	*
	* @note
	* Default value is 0 and the pre-fetch size attribute is used instead.
	* When both attributes are set (pre-fetch size and memory) and pre-fetch memory
	* value can hold more rows than specified by pre-fetch size, OCI uses pre-fetch
	* size instead.
	*
	* @note
	* OCILIB set pre-fetch attribute to OCI_PREFETCH_SIZE when a statement is created.
	* To setup a big value for SetPrefetchMemory(), you must call
	* SetPrefetchSize() to 0 to make OCI consider this attribute.
	*
	*/
    void SetPrefetchMemory(unsigned int value);

	/**
	* @brief
	* Return the amount of memory used to retrieve rows pre-fetched by OCI Client
    *
	* @note
	* Default value is 0
	*
	*/
    unsigned int GetPrefetchMemory() const;

	/**
	* @brief
	* Set the LONG datatype piece buffer size
	*
	* @param value - maximum size for long buffer
	*
	*/
    void SetLongMaxSize(unsigned int value);

	/**
	* @brief
	* Return the LONG datatype piece buffer size
	*
	* @note
	* Default value is set to constant OCI_SIZE_LONG
	*
	*/
    unsigned int GetLongMaxSize() const;

	/**
	* @brief
	* Set the long datatype handling mode of a SQL statement
	*
	* @param value - long mode value
	*
	* @note
	* LONG RAWs can't be handled with Statement::LongImplicit mode
	*
	*/
    void SetLongMode(LongMode value);

	/**
	* @brief
	* Return the long datatype handling mode of a SQL statement
	*
	*/
    LongMode GetLongMode() const;

	/**
	* @brief
	* Return the Oracle SQL code the command held by the statement
	*
	* @warning
	* GetSQLCommand() must be called after the statement has be executed
	* because that's the server engine that computes the SQL command code
	*
	* @note
	* The SQL command list is available in Oracle documentations and guides
    *
	*/
    unsigned int GetSQLCommand() const;

	/**
	* @brief
	* Return the verb of the SQL command held by the statement
	*
	* @warning
	* GetSQLVerb() must be called after the statement has been executed
	* because that's the server engine that computes the SQL verb
	*
	* @note
	* The SQL verb list is available in Oracle documentations and guides
	*
	*/
    ostring GetSQLVerb() const;

	/**
	* @brief
	* Returns all errors that occurred within a DML array statement execution
	*
	*/
    void GetBatchErrors(std::vector<Exception> &exceptions);

private:

    Statement(OCI_Statement *stmt, Handle *parent = 0);

    BindsHolder *GetBindsHolder(bool allocate);

    void ReleaseResultsets();

    void SetLastBindMode(BindInfo::BindDirection mode);

    void SetInData();
    void SetOutData();
    void ClearBinds();

    template <typename TBindMethod, class TDataType>
    void Bind (TBindMethod &method, ostring name, TDataType& value, BindInfo::BindDirection mode);

    template <typename TBindMethod, class TObjectType, class TDataType>
    void Bind (TBindMethod &method, ostring name, TObjectType &value, BindValue<TDataType> datatype, BindInfo::BindDirection mode);

    template <typename TBindMethod, class TObjectType, class TDataType>
    void Bind (TBindMethod &method, ostring name, std::vector<TObjectType> &values, BindValue<TDataType> datatype, BindInfo::BindDirection mode);

    template <typename TBindMethod, class TObjectType, class TDataType, class TElemType>
    void Bind (TBindMethod &method, ostring name, std::vector<TObjectType> &values, BindValue<TDataType> datatype, BindInfo::BindDirection mode, TElemType type);
};

/**
 * @brief
 * Database resultset
 *
 * This class wraps the OCILIB object handle OCI_Resultset and its related methods
 *
 */
class Resultset : public HandleHolder<OCI_Resultset *>
{
    friend class Statement;
public:

	/**
	* @brief
	* Seek Modes enumerated values
	*
	*/
    enum SeekModeValues
    {
		/** Seek is performed using a given absolute offset. The statement must be scrollable */
        SeekAbsolute = OCI_SFD_ABSOLUTE,
		/** Seek is performed using a given relative offset from the current position. The statement must be scrollable */
		SeekRelative = OCI_SFD_RELATIVE
    };

	/**
	* @brief
	* Seek Modes
	*
	* Possible values are Resultset::SeekModeValues
	*
	*/
	typedef Enum<SeekModeValues> SeekMode;

	/**
	* @brief
	* Return the current value of the column at the given index in the resultset
	*
	* @tparam TDataType - C++ type of the value to retrieve
	*
	* @param index - Column position
	*
	* @warning
	* This method has builtin specialized versions for all supported types except RAW based types.
	* For RAWS, use the version with extra parameters
	*
	* @note
	* Column position starts at 1.
	*
	*/
    template<class TDataType>
    TDataType Get(unsigned int index) const;
	
	/**
	* @brief
	* Return the current value of the column from its name in the resultset
	*
	* @tparam TDataType - C++ type of the value to retrieve
	*
	* @param name  - Column name
	*
	* @warning
	* This method has builtin specialized versions for all supported types except RAW based types.
	* For RAWS, use the version with extra parameters
	*
	* @note
	* The column name is case insensitive.
	*
	*/
    template<class TDataType>
    TDataType Get(ostring name) const;

	/**
	* @brief
	* Return the current value of the column at the given index in the resultset
	*
	* @tparam TDataType - C++ type of the value to retrieve
	*
	* @param index - Column position
	* @param value - User value to fill out
	* @param size  - number of bytes written in the user value
	*
	* @warning
	* this version of Get() is currently used for RAW based values that
	* need to copy data to a given buffer
	* Thus, Use RawPointer as TDataType
	*
	* @note
	* Column position starts at 1.
	*
	*/
    template<class TDataType>
    void Get(unsigned int index, TDataType value, unsigned int &size) const;

	/**
	* @brief
	* Retrieve the current value of the column from its name in the resultset
	*
	* @tparam TDataType - C++ type of the value to retrieve
	*
	* @param name  - Column name
	* @param value - User value to fill out
	* @param size  - number of bytes written in the user value
	*
	* @warning
	* this version of Get() is currently used for RAW based values that
	* need to copy data to a given buffer.
	* Thus, Use RawPointer as TDataType
    *
	* @note
	* The column name is case insensitive.
	*
	*/
    template<class TDataType>
    void Get(ostring name, TDataType value, unsigned int &size) const;

	/**
	* @brief
	* Fetch the next row of the resultset
	*
	* @note
	* Next() works for normal and scrollable resultsets
	*
	* @return
	* true on success otherwise false if :
	* - Empty resultset
	* - Last row already fetched
	*
	*/
    bool Next();

	/**
	* @brief
	* Fetch the previous row of the resultset
	*
	* @note
	* Prev() works ONLY for scrollable resultsets
	*
	* @return
	* true on success otherwise false if :
	* - Empty resultset
	* - First row already fetched
	*
	*/
    bool Prev();

	/**
	* @brief
	* Fetch the first row of the resultset
	*
	* @note
	* First() works ONLY for scrollable resultsets
	*
	* @return
	* true on success otherwise false if  the resultset is empty
	*
	*/
    bool First();

	/**
	* @brief
	* Fetch the last row of the resultset
	*
	* @note
	* Last() works ONLY for scrollable resultsets
	*
	* @return
	* true on success otherwise false if  the resultset is empty
	*
	*/
    bool Last();

	/**
	* @brief
	* Custom Fetch of the resultset
	*
	* @param mode    - Fetch direction
	* @param offset  - Fetch offset
	*
	* @warning
	* hSeek() works ONLY for scrollable resultsets
	*
	* @note
	* If you intend to use Seek() on a scrollable statement and if any of the
	* selected columns is a ref cursor or a nested table, you must set the fetching size
	* to 1 using Statement::SetFetchSize() before calling Statement::GetResultset()
	* Otherwise Seek() will fails with a OCI-10002 error
	*
	* @return
	* true on success otherwise false the resultset is empty or seek offset out of bounds
	*
	*/
    bool Seek(SeekMode mode, int offset);

	/**
	* @brief
	* Retrieve the number of rows fetched so far
	*
	*/
    unsigned int GetCount() const;

	/**
	* @brief
	* Retrieve the current row index
	*
	* @note
	* - GetCurrentRow() returns the current row number starting from 1
	* - If the resultset has not been fetched or if the resultset is empty, it returns 0
	* - If the resultset has been fully fetched, it returns the last fetched row number
	*
	*/
    unsigned int GetCurrentRow() const;

	/**
	* @brief
	* Return the index of the column in the result from its name
	*
	* @param name  - Column name
	*
	* @warning
	* The column name is case insensitive
	*
	* @note
	* Column position starts at 1.
	*
	*/
	unsigned int GetColumnIndex(ostring name) const;

	/**
	* @brief
	* Return the number of columns in the resultset
	*
	*/
	unsigned int GetColumnCount() const;


	/**
	* @brief
	* Return the column from its name in the resultset
	*
	* @param index  - Column index
	*
	* @note
	* Column position starts at 1.
	*
	* @warning
	* The column name is case insensitive
	*
	*/
	Column GetColumn(unsigned int index) const;

	/**
	* @brief
	* Return the column from its name in the resultset
	*
	* @param name  - Column name
	*
	* @note
	* The column name is case insensitive
	*
	*/
    Column GetColumn(ostring name) const;

	/**
	* @brief
	* Check if the current row value is null for the column at the given index
	*
	* @param index  - Column index
	*
	* @note
	* Column position starts at 1.
	*
	*/
    bool IsColumnNull(unsigned int index) const;

	/**
	* @brief
	* Check if the current row value is null for the column of the given name
	*
	* @param name  - Column name
	*
	*/
    bool IsColumnNull(ostring name) const;

	/**
	* @brief
	* Return the statement associated with the resultset
	*
	*/
    Statement GetStatement() const;

	/**
	* @brief
	* Convenient operator overloading that performs a call to Next()
	*
	*/
    bool operator ++ (int);

	/**
	* @brief
	* Convenient operator overloading that performs a call to Prev()
	*
	*/
	bool operator -- (int);

	/**
	* @brief
	* Convenient operator overloading that performs a call to Seek()
	* with Resultset::SeekRelative and the given offset
	*
	*/
    bool operator += (int offset);

	/**
	* @brief
	* Convenient operator overloading that performs a call to Seek()
	* with Resultset::SeekRelative and the given offset that is internally negated
	*
	*/
	bool operator -= (int offset);

private:

   Resultset(OCI_Resultset *resultset, Handle *parent);
};

/**
 * @brief
 * Encapsulate a Resultset column or object member properties
 *
 * This class wraps the OCILIB object handle OCI_Column and its related methods
 *
 */
class Column : public HandleHolder<OCI_Column *>
{
    friend class TypeInfo;
    friend class Resultset;

public:

	/**
	* @brief
	* Column properties flags values
	*
	*/
    enum PropertyFlagsValues
    {
		/** The column has no flags or the OCI client does not support it */
		NoFlags = OCI_CPF_NONE,
		/** - If Set, the column is an IDENTITY column
            - Otherwise, it is not an IDENTITY column */
        IsIdentity = OCI_CPF_IS_IDENTITY,
		/** Only valid when IsIdentity is set:
	           - If set, means that the value is "ALWAYS GENERATED"
	           - Otherwise mens that the value is "GENERATED BY" */
        IsGeneratedAlways = OCI_CPF_IS_GEN_ALWAYS,
		/** Only valid when IsIdentity is set:
	           - If set, means that the value is generated by default on NULL */
        IsGeneratedByDefaultOnNull = OCI_CPF_IS_GEN_BY_DEFAULT_ON_NULL
    };

	/**
	* @brief
	* Column properties flags
	*
	* Possible values are Column::PropertyFlagsValues
	*
	*/
    typedef Flags<PropertyFlagsValues> PropertyFlags;

    ostring GetName() const;

	/**
	* @brief
	* Return the Oracle SQL type name of the column datatype
	*
	* @note
	* For possible values, consults Oracle Documentation
	*
	*/
    ostring GetSQLType() const;

	/**
	* @brief
	* Return the Oracle SQL Full name including precision and size of the
	* column datatype
	*
	* @note
	* This function returns a description that matches the one given by SQL*Plus
	*
	*/
    ostring GetFullSQLType() const;

	/**
	* @brief
	* Return the type of the given column
	*
	*/
	DataType GetType() const;

	/**
	* @brief
	* Return the OCILIB object subtype of a column
	*
	* @note
	* This call is valid for the following OCILIB types:
	* - Clong and Blong
	* - Clob and Blob
	* - File
	* - Timestamp
	* - Interval
	*
	* @warning
	* - The returned values must be casted to the matching C++ class GetType() property type.
	* - For a non valid type, it returns 0.
	*
	*/
    unsigned int GetSubType() const;

	/**
	* @brief
	* Return the charset form of the given column
	*
	*/
    Environment::CharsetForm GetCharsetForm() const;

	/**
	* @brief
	* Return the size of the column
	*
	* @note
	* For all types, the size is expressed is bytes, excepted for character
	* based columns that were created with a character based size or of type NCHAR/NVARCHAR
	*
	*/
    unsigned int GetSize() const;

	/**
	* @brief
	* Return the scale of the column for numeric columns
	*
	*/
    int GetScale() const;

	/**
	* @brief
	* Return the precision of the column for numeric columns
	*
	*/
    int GetPrecision() const;

	/**
	* @brief
	* Return the fractional precision of the column for Timestamp and Interval columns
    *
	*/
    int GetFractionalPrecision() const;

	/**
	* @brief
	* Return the leading precision of the column for Interval columns
	*
	*/
    int GetLeadingPrecision() const;

	/**
	* @brief
	* Return the column property flags
	*
	* @note
	* This was introduced in Oracle 12cR1.
	* It is currently used for identifying Identity columns.
	* For earlier versions, it always return Columns::NoFlags
	*
	*/
    PropertyFlags GetPropertyFlags() const;

	/**
	* @brief
	* Return true if the column is nullable otherwise false
	*
	*/
    bool IsNullable() const;

	/**
	* @brief
	* Return true if the length of the column is character-length or  false if it is byte-length
    *
	* @note
	* This was introduced in Oracle 9i. So for version that are not supporting this
	* property, it always return false
	*
	*/
    bool IsCharSemanticUsed() const;

	/**
	* @brief
	* Return the type information object associated to the column
	*
	* @note
	* This call is used only for Named Object typed and collection columns.
	* It returns a null object if the column is not a Named Object or a collection.
	*
	*/
    TypeInfo GetTypeInfo() const;

private:

    Column(OCI_Column *pColumn, Handle *parent);
};

/**
* @brief
* Subscription to database or objects changes
*
* This class wraps the OCILIB object handle OCI_Subscription and its related methods
*
* @warning
* Environment::Events flag must be passed to Environment::Initialize() to be able to use subscriptions

*/
class Subscription : public HandleHolder<OCI_Subscription *>
{
    friend class Event;

public:

    /**
     * @typedef NotifyHandlerProc
     *
     * @brief
	 * User callback for subscriptions event notifications
     *
     */
    typedef void (*NotifyHandlerProc) (Event &evt);


	/**
	* @brief
	* Subscription changes flags values
	*
	*/
    enum ChangeTypesValues
    {
		/**  Request for changes at objects (eg. tables) level (DDL / DML) */
		ObjectChanges = OCI_CNT_OBJECTS,
		/**  Request for changes at rows level (DML) */
		RowChanges = OCI_CNT_ROWS,
		/**  Request for changes at database level (startup, shutdown) */
        DatabaseChanges = OCI_CNT_DATABASES,
		/**  Request for all changes */
		AllChanges = OCI_CNT_ALL
    };

	/**
	* @brief
	* Subscription changes flags
	*
	* Possible values are Subscription::ChangeTypesValues
	*
	*/
    typedef Flags<ChangeTypesValues> ChangeTypes;

	/**
	* @brief
	* Default constructor
	*
	*/
    Subscription();

	/**
	* @brief
	* Register a notification against the given database
	*
	* @param connection  - Connection handle
	* @param name        - Notification name
	* @param changeTypes - Subscription type
	* @param handler     - User handler callback
	* @param port        - Port to use for notifications
	* @param timeout     - notification timeout
	*
	* @note
	* Requires Oracle Client 10gR2 or above
	*
	*/
    void Register(const Connection &connection, ostring name, ChangeTypes changeTypes, NotifyHandlerProc handler, unsigned int port = 0, unsigned int timeout = 0);

	/**
	* @brief
	* Deregister a previously registered notification
	*
	* @note
	* Environment::Cleanup() will automatically deregister any non
	* deregistered subscriptions
	*
	* @note
	* If the database connection passed to Register()
	* has been closed by the time that the application calls
	* Unregister(), the library internally reconnects
	* to the given database, performs the deregistration and then disconnects
	*
	*/
    void Unregister();

	/**
	* @brief
	* Add a SQL query to monitor
    *
	*/
    void Watch(ostring sql);

	/**
	* @brief
	* Return the name of the given registered subscription
	*
	*/
    ostring GetName() const;

	/**
	* @brief
	* Return the timeout of the given registered subscription
	*
	*/
    unsigned int GetTimeout() const;

	/**
	* @brief
	* Return the port used by the notification
	*
	*/
    unsigned int GetPort() const;

	/**
	* @brief
	* Return the connection  associated with a subscription handle
	*
	* @note
	* It may return a null connection object if the connection used at Register() time has been closed
	*
	*/
    Connection GetConnection() const;

private:

    Subscription(OCI_Subscription *pSubcription);
};

/**
* @brief
* Subscription Event
*
* This class wraps the OCILIB object handle OCI_Event and its related methods
*
* @warning
* Environment::Events flag must be passed to Environment::Initialize() to be able to use subscriptions
*
*/
class Event : public HandleHolder<OCI_Event *>
{
    friend class Subscription;
    friend class Environment;

public:

	/**
	* @brief
	* Event type enumerated values
	*
	*/
    enum EventTypeValues
    {
		/** A database has been started up */
		DatabaseStart = OCI_ENT_STARTUP,
		/** A database has been shut down */
		DatabaseShutdown = OCI_ENT_SHUTDOWN,
		/** A database has been shut down (RAC) */
		DatabaseShutdownAny = OCI_ENT_SHUTDOWN_ANY,
		/** A database has been dropped */
		DatabaseDrop = OCI_ENT_DROP_DATABASE,
		/** The notification is timed out */
		Unregister = OCI_ENT_DEREGISTER,
		/** A database object has been modified */
        ObjectChanged = OCI_ENT_OBJECT_CHANGED
    };

	/**
	* @brief
	* Event type
	*
	* Possible values are Event::EventTypeValues
	*
	*/
    typedef Enum<EventTypeValues> EventType;

	/**
	* @brief
	* Object events enumerated values
	*
	*/
    enum ObjectEventValues
    {
		/** An insert has been performed */
        ObjectInserted = OCI_ONT_INSERT,
		/** An update has been performed */
		ObjectUpdated = OCI_ONT_UPDATE,
		/** A delete has been performed */
		ObjectDeleted = OCI_ONT_DELETE,
		/** An alter has been performed */
		ObjectAltered = OCI_ONT_ALTER,
		/** A drop has been performed */
		ObjectDropped = OCI_ONT_DROP,
		/** Generic undefined action * */
		ObjectGeneric = OCI_ONT_GENERIC
    };

	/**
	* @brief
	* Object events
	*
	* Possible values are Event::ObjectEventValues
	*
	*/
    typedef Enum<ObjectEventValues> ObjectEvent;

	/**
	* @brief
	* Return the type of event reported by a notification
	*
	*/
    EventType GetType() const;

	/**
	* @brief
	* Return the type of operation reported by a notification

	* @note
	* Thi call is only valid when GetType() reports the event type Event::ObjectChanged
	*
	*/
    ObjectEvent GetObjectEvent() const;

	/**
	* @brief
	* Return the name of the database that generated the event
	*
	*/
    ostring GetDatabaseName() const;

	/**
	* @brief
	* Return the name of the object that generated the event
	*
	* @note
	* Database object name follows the pattern "[schema_name].object_name"
	*
	*/
    ostring GetObjectName() const;

	/**
	* @brief
	* Return the rowid of the altered database object row
	*
	*/
    ostring GetRowID() const;

	/**
	* @brief
	* Return the subscription that generated this event
	*
	*/
    Subscription GetSubscription() const;

private:

    Event(OCI_Event *pEvent);
};


/**
* @brief
* AQ identified agent for messages delivery
*
* This class wraps the OCILIB object handle OCI_Agent and its related methods
*
*/
class Agent : public HandleHolder<OCI_Agent *>
{
    friend class Message;
    friend class Dequeue;

public:

	/**
	* @brief
	* Create an AQ agent object
	*
	* @param connection - Connection object
	* @param name       - Agent name
	* @param address    - Agent address
	*
	* @note
	* An AQ agent object is :
	* - used as recipient information when enqueuing a message
	* - used as sender information when dequeuing a message
	* - used for listening message only from identified senders
	*
	* @note
	* the AQ agent address can be any Oracle identifier, up to 128 bytes.
	* the AQ agent name    can be any Oracle identifier, up to 30  bytes.
	*
	*/
    Agent(const Connection &connection, ostring name = OTEXT(""), ostring address = OTEXT(""));

	/**
	* @brief
	* Get the given AQ agent name
	*
	*/
    ostring GetName() const;

	/**
	* @brief
	* Set the given AQ agent name
	*
	* @param value  - AQ agent name
	*
	* @note
	* the AQ agent name is used to identified an message send or recipient when enqueuing/dequeuing a message
	*
	* @note
	* the AQ agent name can be any Oracle identifier, up to 30 bytes.
	*
	*/
    void SetName(ostring value);

	/**
	* @brief
	* Get the given AQ agent address
	*
	* @note
	* See SetAddress() ffor more details
	*
	*/
	ostring GetAddress() const;

	/**
	* @brief
	* Set the given AQ agent address
	*
	* @param value - AQ agent address
	*
	* @note
	* the parameter 'address' must be of the form : [schema.]queue_name[\@dblink]
	*
	* @note
	* the AQ agent address can be any Oracle identifier, up to 128 bytes.
	*
	*/
    void SetAddress(ostring value);

private:

    Agent(OCI_Agent *pAgent, Handle *parent);
};

/**
* @brief
* AQ message
*
* This class wraps the OCILIB object handle OCI_Msg and its related methods
*
*/
class Message : public HandleHolder<OCI_Msg *>
{
	friend class Dequeue;

public:

	/**
	* @brief
	* Message state enumerated values
	*
	*/
    enum MessageStateValues
    {
		/** The message is ready to be processed */
		Ready = OCI_AMS_READY,
		/** The message delay has not yet completed */
		Waiting = OCI_AMS_WAITING,
		/** The message has been processed */
        Processed = OCI_AMS_PROCESSED,
		/** The message has moved to exception queue */
		Expired = OCI_AMS_EXPIRED
    };

	/**
	* @brief
	* Message state
	*
	* Possible values are Message::MessageStateValues
	*
	*/
    typedef Enum<MessageStateValues> MessageState;

	/**
	* @brief
	* Create a message object based on the given payload type
	*
	* @param typeInfo - Type info object
	*
	* @note
	* OCILIB supports 2 type of message payload :
	* - Oracle types (UDT)
	* - RAW data
	*
	* @note
	* Oracle Type AnyData is not supported in the current version of OCILIB
	*
	* @note
	* the parameter 'typinf' indicates the type of payload :
	* - For object payload, retrieve the object type information object from the given type name
	* - For RAW payload, you MUST pass the object type information object from the type name "SYS.RAW" as object type name
	*
	* @warning
	* Newly created Message handles have NULL payloads.
	* For Message handling Objects payloads, Get() returns a null Object until an object is assigned to the message.
	*
	* @note
	* When a local Message object handle is enqueued, it keeps its attributes. If it's enqeued again, another
	* identical message is posted into the queue.
	* To reset a message and empty all its properties, call Reset()
	*
	*/
    Message(const TypeInfo &typeInfo);

	/**
	* @brief
	* Reset all attributes of the message
	*
	* @warning
	* Reset() clears the message payload and set it to NULL
	*
	*/
    void Reset();

	/**
	* @brief
	* Get the object payload of the message
	*
	*/
	template <class TPayloadType>
	TPayloadType GetPayload();

	/**
	* @brief
	* Set the object payload of the message
	*
	* @param value - Object payload
	*
	*/
	template <class TPayloadType>
	void SetPayload(const TPayloadType &value);

	/**
	* @brief
	* return the time the message was enqueued
	*
	* @note
	* Only use this function for message dequeued from queues
	*
	*/
    Date GetEnqueueTime() const;

	/**
	* @brief
	* Return the number of attempts that have been made to dequeue the message
	*
	*/
    int GetAttemptCount() const;

	/**
	* @brief
	* Return the state of the message at the time of the dequeue
	*
	*/
    MessageState GetState() const;

	/**
	* @brief
	* Return the ID of the message
	*
	* @param value - Input buffer
	* @param size  - Input buffer maximum size
	*
	* @note
	* The message ID is :
	*  - generated when the message is enqueued in the queue
	*  - retrieved when the message is dequeued from the queue
	*
	* @note
	* On output, parameter 'size' holds the number of bytes copied into the given buffer
	*
	*/
	Raw GetID() const;

	/**
	* @brief
	* Return the duration that the message is available for dequeuing
	*
	* @note
	* see SetExpiration() for more details
	*
	*/
    int GetExpiration() const;

	/**
	* @brief
	* set the duration that the message is available for dequeuing
	*
	* @param value - duration in seconds
	*
	* @note
	* This parameter is an offset from the delay (see SetEnqueueDelay())
	* While waiting for expiration, the message state is set to Message::Ready.
	* If the message is not dequeued before it expires, it will be moved to the exception queue
	* with the state Message::Expired.
	*
	* @note
	* If parameter 'value' is set to -1 (default value), the message will not expire
	*
	* @warning
	* Expiration processing requires the queue monitor to be started.
	*
	*/
    void SetExpiration(int value);

	/**
	* @brief
	* Return the number of seconds that a message is delayed for dequeuing
	*
	* @note
	* see SetEnqueueDelay() for more details
	*
	*/
    int GetEnqueueDelay() const;

	/**
	* @brief
	* set the number of seconds to delay the enqueued message
	*
	* @param value - Delay in seconds
	*
	* @note
	* The delay represents the number of seconds after which a message is available for dequeuing.
	* When the message is enqueued, its state is set to Message::Waiting.
	* When the delay expires, its state is set to Message::Ready.
	*
	* @note
	* If parameter 'value' is set to zero (default value), the message will be immediately available
	* for dequeuing
	*
	* @warning
	* Dequeuing by Message ID overrides the delay specification.
	*
	* @warning
	* Delaying processing requires the queue monitor to be started.
	*
	*/
    void SetEnqueueDelay(int value);

	/**
	* @brief
	* Return the priority of the message
    *
	* @note
	* see SetPriority() for more details
	*
	*/
    int GetPriority() const;

	/**
	* @brief
	* Set the priority of the message
	*
	* @param value - Message priority
	*
	* @note
	*   - The priority can be any number, including negative numbers.
	*   - A smaller number indicates higher priority.
	*   - Default value is zero.
	*
	*/
    void SetPriority(int value);

	/**
	* @brief
	* Return the original ID of the message in the last queue that generated this message
	*
	* @param value  - Input buffer
	* @param size   - Input buffer maximum size
	*
	* @warning
	* When a message is propagated from/to differents queues, this ID is the one generated for the
	* message in the previous queue.
	*
	* @note
	* On output, parameter 'size' holds the number of bytes copied into the given buffer
	*
	*/
	Raw GetOriginalID() const;

	/**
	* @brief
	* Set the original ID of the message in the last queue that generated this message
	*
	* @param value - Message ID
	* @param size  - Message ID size
	*
	* @warning
	* When a message is propagated from/to differents queues, this ID is the one generated for the
	* message in the previous queue.
	*
	*/
	void SetOriginalID(const Raw &value);

	/**
	* @brief
	* Get the correlation identifier of the message
	*
	* @note
	* see SetCorrelation() for more details
	*
	*/
    ostring GetCorrelation() const;

	/**
	* @brief
	* Set the correlation identifier of the message
	*
	* @param value - Message correlation text
	*
	* @note
	* see Dequeue::SetCorrelation() for more details
	*
	*/
    void SetCorrelation(ostring value);

	/**
	* @brief
	* Get the Exception queue name of the message
	*
	* @warning
	* When calling this function on a message retrieved with Dequeue::Get(), the returned value is
	* empty if the default exception queue associated with the current queue is used (eg. no user
	* defined specified at enqueue time for the message)
	*
	* @note
	* see SetExceptionQueue() for more details
	*
	*/
    ostring GetExceptionQueue() const;

	/**
	* @brief
	* Set the name of the queue to which the message is moved to if it cannot be
	* processed successfully
	*
	* @param value - Exception queue name
	*
	* @warning
	* From Oracle Documentation :
	*
	* "Messages are moved into exception queues in two cases :
	*  - If the number of unsuccessful dequeue attempts has exceeded the attribute 'max_retries' of
	*    given queue
	*  - if the message has expired.
	*
	* All messages in the exception queue are in the EXPIRED state.
	*
	* The default is the exception queue associated with the queue table.
	*
	* If the exception queue specified does not exist at the time of the move the message will be
	* moved to the default exception queue associated with the queue table and a warning will be
	* logged in the alert file.
	*
	* This attribute must refer to a valid queue name."
	*
	*/
    void SetExceptionQueue(ostring value);

	/**
	* @brief
	* Return the original sender of the message
	*
	* @return
	* Valid agent object if set at enqueue time otherwise a null agent object
	*
	*/
    Agent GetSender() const;

	/**
	* @brief
	* Set the original sender of the message
	*
	* @param agent - Message sender
	*
	*/
    void SetSender(const Agent &agent);

	/**
	* @brief
	* Set the recipient list of a message to enqueue
	*
	* @param agents - Recipients list
	*
	* @warning
	* This function should only be used for queues which allow multiple consumers.
	* The default recipients are the queue subscribers.
	*
	*/
    void SetConsumers(std::vector<Agent> &agents);

private:

    Message(OCI_Msg *pMessage, Handle *parent);
};

/**
* @brief
* Enqueue object for queuing messages into an Oracle Queue
*
* This class wraps the OCILIB object handle OCI_Enqueue and its related methods
*
*/
class Enqueue : public HandleHolder<OCI_Enqueue *>
{
public:

	/**
	* @brief
	* Message enqueuing mode enumerated values
	*
	*/
    enum EnqueueModeValues
    {
		/** Enqueue message before another message */
        Before = OCI_ASD_BEFORE,
		/** Enqueue message before all messages */
        OnTop  = OCI_ASD_TOP
    };

	/**
	* @brief
	* Message enqueuing mode
	*
	* Possible values are Enqueue::EnqueueModeValues
	*
	*/
    typedef Enum<EnqueueModeValues> EnqueueMode;

	/**
	* @brief
	* Message visibility enumerated values
	*
	*/
    enum EnqueueVisibilityValues
    {
		/** Enqueue is an independent transaction */
        Immediate = OCI_AMV_IMMEDIATE,
		/** Enqueue is part of current transaction */
        OnCommit  = OCI_AMV_ON_COMMIT
    };

	/**
	* @brief
	* Message visibility after begin queued
	*
	* Possible values are Enqueue::EnqueueVisibilityValues
	*
	*/
    typedef Enum<EnqueueVisibilityValues> EnqueueVisibility;

	/**
	* @brief
	* Create a Enqueue object for the given queue
	*
	* @param typeInfo  - Type info handle
	* @param queueName - Queue name
	*
	* @note
	* OCILIB supports 2 types of message payload :
	* - Oracle types (UDT)
	* - RAW data
	*
	* @note
	* Oracle Type AnyData is not supported in the current version of OCILIB
	*
	* @note
	* the parameter 'typeInfo' indicates the type of payload to enqueue to the given queue :
	* - For object payload, retrieve the object type information object from the given type name
	* - For RAW payload, you MUST pass the object type information object from the type name "SYS.RAW" as object type name
	*
	*/
	Enqueue(const TypeInfo &typeInfo, ostring queueName);

	/**
	* @brief
	* Enqueue a message the on queue associated to the Enqueue object
	*
	* @param message  - Message  to enqueue
	*
	*/
    void Put(const Message &message);

	/**
	* @brief
	* Get the enqueueing/locking behavior
	*
	* @note
	* see SetVisibility() for more details
	*
	*/
    EnqueueVisibility GetVisibility() const;

	/**
	* @brief
	* Set whether the new message is enqueued as part of the current transaction
	*
	* @param value - Enqueueing visibility
	*
	* @note
	* Default value is Enqueue::OnCommit
	*
	*/
    void SetVisibility(EnqueueVisibility value);

	/**
	* @brief
	* Return the enqueing mode of messages to enqueue
	*
	* @note
	* see SetMode() for more details
	*
	*/
    EnqueueMode GetMode() const;

	/**
	* @brief
	* Set the enqueing mode of messages to put in the queue
	*
	* @param value - enqueing mode
	*
	* @note
	* Default value is Enqueue::OnTop
	*
	* @note
	* if the parameter 'value' is set to Enqueue::Before, the application must
	* call SetRelativeMsgID() before enqueuing the next message in the queue.
	*
	* @note
	* In order to stop enqueuing message using a sequence deviation, call
	* SetMode() with the value Enqueue::OnTop
	*
	*/
    void SetMode(EnqueueMode value);

	/**
	* @brief
	* Get the current associated message identifier used for enqueuing messages
	* using a sequence deviation
	*
	* @param value    - buffer to receive the message identifier
	* @param size     - pointer to buffer max length
	*
	* @warning
	* When the function returns, parameter 'size' hold the number of bytes assigned to parameter 'value'
	*
	* @note
	* see SetRelativeMsgID() for more details
	*
	*/

	Raw GetRelativeMsgID() const;

	/**
	* @brief
	* Set a message identifier to use for enqueuing messages using a sequence deviation
	*
	* @param value    - message identifier
	* @param size     - pointer to message identifier length
	*
	* @note
	* This call is only valid if SetMode() has been called with the value Enqueue::Before
	*
	* @warning
	* if the function cannot assign the message id, the content of the parameter 'size' is set to zero.
	*
	* @note
	* see SetMode() for more details
	*
	*/
	void SetRelativeMsgID(const Raw &value);
};

/**
* @brief
* Dequeue object for dequeuing messages into an Oracle Queue
*
* This class wraps the OCILIB object handle OCI_Dequeue and its related methods
*
*/
class Dequeue : public HandleHolder<OCI_Dequeue *>
{
    friend class Environment;

public:

    /**
     * @typedef NotifyAQHandlerProc
     *
     * @brief
	 * User callback for dequeue event notifications
	 *
     */
    typedef void (*NotifyAQHandlerProc) (Dequeue &dequeue);

	/**
	* @brief
	* Dequeue mode enumerated values
	*
	*/
    enum DequeueModeValues
    {
		/** Read message without acquiring a lock */
        Browse =  OCI_ADM_BROWSE,
		/** Read and obtain write lock on message */
        Locked = OCI_ADM_LOCKED,
		/** Read the message and delete it */
        Remove = OCI_ADM_REMOVE,
		/** Confirm receipt of the message, but do not deliver the actual message content */
        Confirm = OCI_ADM_REMOVE_NODATA
    };

	/**
	* @brief
	* Dequeue mode
	*
	* Possible values are Dequeue::DequeueModeValues
	*
	*/
    typedef Enum<DequeueModeValues> DequeueMode;

	/**
	* @brief
	* Message visibility enumerated values
	*
	*/
    enum DequeueVisibilityValues
    {
		/** Dequeue is an independent transaction */
        Immediate = OCI_AMV_IMMEDIATE,
		/** Dequeue is part of current transaction */
        OnCommit  = OCI_AMV_ON_COMMIT
    };

	/**
	* @brief
	* Message visibility after begin dequeued
	*
	* Possible values are Dequeue::DequeueVisibilityValues
	*
	*/
    typedef Enum<DequeueVisibilityValues> DequeueVisibility;

	/**
	* @brief
	* Navigation Mode enumerated values
	*
	*/
    enum NavigationModeValues
    {
		/** Retrieves the first message which is available */
        FirstMessage = OCI_ADN_FIRST_MSG,
		/** Retrieves the next message which is available */
        NextMessage = OCI_ADN_NEXT_MSG,
		/** Skips the remainder of the current transaction  group (if any)
		    and retrieves the first message of the next transactiong group.*/
        NextTransaction = OCI_ADN_NEXT_TRANSACTION,
    };

	/**
	* @brief
	* Navigation Mode
	*
	* Possible values are Dequeue::NavigationModeValues
	*
	*/
    typedef Enum<NavigationModeValues> NavigationMode;

	/**
	* @brief
	* Parametrized constructor
	*
	* @param typeInfo  - Payload type info
	* @param queueName - Queue name
	*
	*/
    Dequeue(const TypeInfo &typeInfo, ostring queueName);

	/**
	* @brief
	* Dequeue messages from the given queue
	*
	* @warning
	* When dequeuing from a multiple consumer queue, you need
	* to set the navigation mode to NavigationMode::FirstMessage using
	* SetNavigation()
	*
	* @return
	* A valid Message handle on success otherwise a null Message on timeout
	*
	*/
    Message Get();

	/**
	* @brief
	* Listen for messages that match any recipient of the associated Agent list
	*
	* @param timeout - Timeout in second
	*
	* @note
	* If an Agent handle is returned, messages are available for this agent.
	* In order to retrieve its messsages :
	* - call SetConsumer() with the name of agent using Agent::GetName()
	* - call Get() to dequeue it's pending messages
	*
	* @return
	* An Agent handle for who messages are available on success otherwise an null agent object
	*/
    Agent Listen(int timeout);

	/**
	* @brief
	* Get the current consumer name associated with the dequeueing process.
	*
	* @note
	* see SetConsumer() for more details
	*
	*/
    ostring GetConsumer() const;

	/**
	* @brief
	* Set the current consumer name to retrieve message for.
	*
	* @param value - consumer name
	*
	* @warning
	* If a queue is not set up for multiple consumers, SetConsumer()
	* should not be called or called with an empty value
	*
	*/
    void SetConsumer(ostring value);

	/**
	* @brief
	* Get the correlation identifier of the message to be dequeued
	*
	* @note
	* see SetCorrelation() for more details
	*
	*/
    ostring GetCorrelation() const;

	/**
	* @brief
	* set the correlation identifier of the message to be dequeued
	*
	* @param value - correlation identifier
	*
	* @note
	* Special pattern matching characters, such as "%" or "_" can be used.
	* If more than one message satisfies the pattern, the order of dequeuing is undetermined.
	*
	*/
    void SetCorrelation(ostring value);

	/**
	* @brief
	* Get the message identifier of the message to be dequeued
	*
	* @param value   - message identitier
	* @param size    - size of the message identitier
	*
	* @note
	* see SetRelativeMsgID() for more details
	*
	*/
	Raw GetRelativeMsgID() const;

	/**
	* @brief
	* Set the message identifier of the message to be dequeued
	*
	* @param value    - message identitier
	* @param size     - size of the message identitier
	*
	*/
	void SetRelativeMsgID(const Raw &value);

	/**
	* @brief
	* Get the dequeueing/locking behavior
	*
	* @note
	* see SetVisibility() for more details
	*
	*/
    DequeueVisibility GetVisibility() const;

	/**
	* @brief
	* Set whether the new message is dequeued as part of the current transaction
	*
	* @param value - dequeueing mode
	*
	* @warning
	* The visibility parameter is ignored when using the dequeuing
	* mode is Dequeue::Browse
	*
	* @note
	* Default value is Dequeue::OnCommit
	*
	*/
    void SetVisibility(DequeueVisibility value);

	/**
	* @brief
	* Get the dequeueing/locking behavior
	*
	* @note
	* see SetMode() for more details
	*
	*/
    DequeueMode GetMode() const;

	/**
	* @brief
	* Set the dequeueing/locking behavior
	*
	* @param value - dequeueing mode
	*
	* @note
	* Default value is Dequeue::Remove
	*
	*/
    void SetMode(DequeueMode value);

	/**
	* @brief
	* Return the navigation position of messages to retrieve from the queue
	*
	* @note
	* see SetNavigation() for more details
	*
	*/
    NavigationMode GetNavigation() const;

	/**
	* @brief
	* Set the position of messages to be retrieved.
	*
	* @param value - navigation position
	*
	* @note
	* The dequeuing uses the following sequence :
	*   - find messages using the navigation position
	*   - apply search criterias (message correlation)
	*   - get message
	*
	* @note
	* Default value is Dequeue::NextMessage
	*
	* @warning
	* Dequeue::NextTransaction can only be used if message grouping is enabled for the given queue.
	*
	*/
    void SetNavigation(NavigationMode value);

	/**
	* @brief
	* Return the time that Get() waits for messages if no messages are currently available
	*
	* @note
	* see SetWaitTime() for more details
	*
	*/
    int GetWaitTime() const;

	/**
	* @brief
	* Set the time that Get() waits for messages if no messages are currently available
	*
	* @param value - timeout in seconds
	*
	*@note
	* - Any positive values in seconds are valid.
	* - The value 0  is accepted and means Get() does not wait for
	*   messages and returns immediately if no messages are available
	* - The value -1 is accepted and means Get() waits for ever (until
	*   a message is available in the queue)
	*
	* @note
	* Default value is -1 (wait for ever)
	*
	*/
    void SetWaitTime(int value);

    /**
     * @brief
     * Set the Agent list to listen to message for
     *
     * @param agents - vector of agents
     *
     */
    void SetAgents(std::vector<Agent> &agents);

    /**
     * @brief
     * Subscribe for asynchronous messages notifications
     *
     * @param port     - Port to use for notifications
     * @param timeout  - notification timeout
     * @param handler  - User handler callback fired when messages are ready to be dequeued
     *
     * @note
     * Environment::Events flag must be passed to Environment::Initialize() to be able to use
     * asynchronous messages notifications
     *
     * @note
     * Requires Oracle Client 10gR2 or above
     *
     */
    void Subscribe(unsigned int port, unsigned int timeout, NotifyAQHandlerProc handler);

    /**
     * @brief
     * Unsubscribe for asynchronous messages notifications
     *
     * @note
     * Requires Oracle Client 10gR2 or above
     *
     */
    void Unsubscribe();

private:

    Dequeue(OCI_Dequeue *pDequeue);
};

/**
* @brief
* Class allowing the administration of Oracle Queues
*
*/
class Queue
{
public:

	/**
	* @brief
	* Queue Type enumerated values
	*
	*/
    enum QueueTypeValues
    {
        /** Normal queue */
        NormalQueue = OCI_AQT_NORMAL,
        /** Exception queue */
        ExceptionQueue = OCI_AQT_EXCEPTION,
        /** Non persistent queue */
        NonPersistentQueue = OCI_AQT_NON_PERSISTENT
    };

	/**
	* @brief
	* Queue Type
	*
	* Possible values are Queue::QueueTypeValues
	*
	*/
    typedef Enum<QueueTypeValues> QueueType;

    /**
     * @brief
     * Create a queue
     *
     * @param connection         - Database connection
     * @param queue              - Queue name
     * @param table              - Queue table name
     * @param type               - Queue type
     * @param maxRetries         - Maximum number of attempts to dequeue a message
     * @param retryDelay         - Number of seconds between attempts to dequeue a message
     * @param retentionTime      - number of seconds a message is retained in the queue table after
     *                             being dequeued from the queue
     * @param dependencyTracking - Parameter reserved for future use by Oracle (MUST be set to FALSE)
     * @param comment            - Description of the queue
     *
     * @note
     * Parameter 'queue' can specify the shema where to create to queue ([schema.]queue_name)
     * Queue names cannot be longer than 24 characters (Oracle limit for user queues)
     *
     * @note
     * this call wraps the PL/SQL procedure DBMS_AQADM.CREATE_QUEUE().
     * Refer to Oracle Streams - Advanced Queuing User's Guide for more details
     *
     */
    static void Create(const Connection &connection, ostring queue, ostring table, QueueType type = NormalQueue,
                       unsigned int maxRetries = 0, unsigned int retryDelay = 0, unsigned int retentionTime = 0,
                       bool dependencyTracking = false, ostring comment = OTEXT(""));

    /**
     * @brief
     * Alter the given queue
     *
     * @param connection      - Database connection
     * @param queue           - Queue name
     * @param maxRetries      - Maximum number of attempts to dequeue a message
     * @param retryDelay      - Number of seconds between attempts to dequeue a message
     * @param retentionTime   - number of seconds a message is retained in the queue table after
     *                          being dequeued from the queue
     * @param comment         - Description of the queue
     *
     * @note
     * See Create() for more details
     *
     * @note
     * this call wraps the PL/SQL procedure DBMS_AQADM.ALTER_QUEUE().
     * Refer to Oracle Streams - Advanced Queuing User's Guide for more details
     *
     */
    static void Alter (const Connection &connection, ostring queue,
                       unsigned int maxRetries= 0, unsigned int retryDelay= 0,
                       unsigned int retentionTime= 0, ostring comment = OTEXT(""));

    /**
     * @brief
     * Drop the given queue
     *
     * @param connection - Database connection
     * @param queue      - Queue name
     *
     * @warning
     * A queue can be dropped only if it has been stopped before.
     *
     * @note
     * this call wraps the PL/SQL procedure DBMS_AQADM.DROP_QUEUE().
     * Refer to Oracle Streams - Advanced Queuing User's Guide for more details
     *
     */
    static void Drop  (const Connection &connection, ostring queue);

    /**
     * @brief
     * Start the given queue
     *
     * @param connection     - Database connection
     * @param queue          - Queue name
     * @param enableEnqueue  - Enable enqueue
     * @param enableDequeue  - Enable dequeue
     *
     * @warning
     * For exception queues, only enqueuing is allowed
     *
     * @note
     * this call wraps the PL/SQL procedure DBMS_AQADM.START_QUEUE().
     * Refer to Oracle Streams - Advanced Queuing User's Guide for more details
     *
     */
    static void Start (const Connection &connection, ostring queue, bool enableEnqueue = true, bool enableDequeue = true);

    /**
    * @brief
    * Stop enqueuing or dequeuing or both on the given queue
    *
    * @param connection  - Database connection
    * @param queue       - Queue name
    * @param stopEnqueue - Disable enqueue
    * @param stopDequeue - Disable dequeue
    * @param wait        - Wait for current pending enqueuues/dequeues
    *
    * @warning
    * A queue cannot be stopped if there are pending transactions against the queue.
    *
    * @note
    * this call wraps the PL/SQL procedure DBMS_AQADM.STOP_QUEUE().
    * Refer to Oracle Streams - Advanced Queuing User's Guide for more details
    *
    */
    static void Stop  (const Connection &connection, ostring queue, bool stopEnqueue = true, bool stopDequeue = true, bool wait = true);
};

/**
* @brief
* Class allowing the administration of Oracle Queue tables
*
*/
class QueueTable
{
public:

    /**
     *
     * @brief
     * Grouping mode enumerated values
     *
     */
    enum GroupingModeValues
    {
        /** Each message is treated individually */
        None = OCI_AGM_NONE,
        /** All messages enqueued in one transaction are considered part of
            the same group and can be dequeued as a group of related messages */
        Transactionnal = OCI_AGM_TRANSACTIONNAL
    };

	/**
	* @brief
	* Grouping Mode
	*
	* Possible values are QueueTable::GroupingModeValues
	*
	*/
    typedef Enum<GroupingModeValues> GroupingMode;

    /**
     *
     * @brief
     * Purge mode enumerated values
     *
     */
    enum PurgeModeValues
    {
        /** Purge only buffered   messages */
        Buffered = OCI_APM_BUFFERED,
        /** Purge only persistent messages */
        Persistent = OCI_APM_PERSISTENT,
        /** Purge all messages */
        All = OCI_APM_ALL
    };

	/**
	* @brief
	* Purge mode
	*
	* Possible values are QueueTable::PurgeModeValues
	*
	*/
    typedef Enum<PurgeModeValues> PurgeMode;

    /**
     * @brief
     * Create a queue table for messages of the given type
     *
     * @param connection         - Database connection
     * @param table              - Queue table name
     * @param payloadType        - Message type name
     * @param multipleConsumers  - Enable multiple consumers for each messages
     * @param storageClause      - Optional Additionnal clauses for the table storage
     * @param sortList           - Optional Additional columns name to use for sorting
     * @param groupingMode       - Optional Specifies if messages are grouped within a transaction
     * @param comment            - Optional Description of the queue table
     * @param primaryInstance    - Optional primary owner (instance) of the queue table
     * @param secondaryInstance  - Optional Owner of the queue table if the primary instance is not available
     * @param compatible         - Optional lowest database version with which the queue table is compatible
     *
     * @note
     * Parameter 'table' can specify the shema where to create to queue table ([schema.]queue_table)
     * Queue table names cannot be longer than 24 characters (Oracle limit for user queue tables)
     *
     * @note
     * Possible values for parameter 'payloadType' :
     * - For Oracle types (UDT) : use the type name ([schema.]type_name)
     * - For RAW data           : use "SYS.RAW" or "RAW"
     *
     * @note
     * Possible values for parameter 'compatible' :
     * - "8.0", "8.1", "10.0"
     *
     * @note
     * this call wraps the PL/SQL procedure DBMS_AQADM.CREATE_QUEUE_TABLE().
     * Refer to Oracle Streams - Advanced Queuing User's Guide for more details
     *
     */
    static void Create (const Connection &connection, ostring table, ostring payloadType, bool multipleConsumers,
                        ostring storageClause = OTEXT(""), ostring sortList = OTEXT(""),
                        GroupingMode groupingMode = None, ostring comment = OTEXT(""),
                        unsigned int primaryInstance = 0, unsigned int secondaryInstance = 0,
                        ostring compatible = OTEXT(""));

    /**
    * @brief
    * Alter the given queue table
    *
    * @param connection           - Database connection
    * @param table                - Queue table name
    * @param comment              - Optional Description of the queue table
    * @param primaryInstance      - Optional primary owner (instance) of the queue table
    * @param secondaryInstance    - Optional Owner of the queue table if the primary instance is not available
    *
    * @note
    * See Create() from more details
    *
    * @note
    * this call wraps the PL/SQL procedure DBMS_AQADM.ALTER_QUEUE_TABLE().
    * Refer to Oracle Streams - Advanced Queuing User's Guide for more details
    *
    */
    static void Alter  (const Connection &connection, ostring table, ostring comment, unsigned int primaryInstance = 0, unsigned int secondaryInstance = 0);

     /**
     * @brief
     * Drop the given queue table
     *
     * @param connection   - Database connection
     * @param table        - Queue table name
     * @param force        - Force the deletion of objects related to the queue table
     *
     * @note
     * Possible values for 'force' :
     *  - true  : all queues using the queue table and their associated propagation schedules are
     *            dropped automatically
     *  - false : All the queues using the giben queue table must be stopped and dropped before the
     *            queue table can be dropped.
     *
     * @note
     * this call wraps the PL/SQL procedure DBMS_AQADM.DROP_QUEUE_TABLE().
     * Refer to Oracle Streams - Advanced Queuing User's Guide for more details
     *
     */
    static void Drop  (const Connection &connection, ostring table, bool force = true);

    /**
     * @brief
     * Purge messages from the given queue table
     *
     * @param connection - Database connection
     * @param table      - Queue table name
     * @param mode       - Type of message to purge
     * @param block      - Lock all queues using the queue table while doing the purge
     * @param condition  - Optionnal SQL based conditions (see notes)
     *
     * @note
     * For more information about the SQL purge conditions, refer to
     * Oracle Streams - Advanced Queuing User's Guide for more details
     *
     * @warning
     * This feature is onyl available from ORacle 10gR2.
     * This function does nothing and returns TRUE is the server version is < Oracle 10gR2
     *
     * @note
     * this call wraps the PL/SQL procedure DBMS_AQADM.PURGE_QUEUE_TABLE().
     * Refer to Oracle Streams - Advanced Queuing User's Guide for more details
     *
     */
    static void Purge  (const Connection &connection, ostring table, PurgeMode mode, ostring condition = OTEXT(""), bool block = true);

    /**
     * @brief
     * Migrate a queue table from one version to another
     *
     * @param connection - Database connection
     * @param table      - Queue table name
     * @param compatible - Optional database version with witch the queue table has to migrate
     *
     * @note
     * Possible values for parameter 'compatible' :
     * - "8.0", "8.1", "10.0"
     *
     * @note
     * this call wraps the PL/SQL procedure DBMS_AQADM.MIGRATE_QUEUE_TABLE().
     * Refer to Oracle Streams - Advanced Queuing User's Guide for more details
     *
     */
    static void Migrate(const Connection &connection, ostring table, ostring compatible = OTEXT(""));
};

/**
* @brief
* Oracle Direct path loading encapsulation
*
* This class wraps the OCILIB object handle OCI_DirPath and its related methods
*
*/
class DirectPath : public HandleHolder<OCI_DirPath *>
{
public:

    /**
     * @brief
     * Conversion mode enumerated  values
     *
     */
    enum ConversionModeValues
    {
        /** Conversion fails on error */
        Default = OCI_DCM_DEFAULT,
        /** Conversion does not fail on error */
        Force = OCI_DCM_FORCE
    };

	/**
	* @brief
	* Conversion Mode
	*
	* Possible values are DirectPath::ConversionModeValues
	*
	*/
    typedef Enum<ConversionModeValues> ConversionMode;

	/**
	* @brief
	* Direct Operation operation Result enumerated values
	*
	*/
    enum ResultValues
    {
        /** Conversion/load has been successful */
        ResultComplete = OCI_DPR_COMPLETE,
        /** An error happened while converting/loading data */
        ResultError = OCI_DPR_ERROR,
        /** The internal stream is full*/
        ResultFull = OCI_DPR_FULL ,
        /** A ccolumn has not been fully filled yet */
        ResultPartial = OCI_DPR_PARTIAL,
        /** No data was found to convert/load */
        ResultEmpty = OCI_DPR_EMPTY
    };

	/**
	* @brief
	* Direct Operation operation Result
	*
	* Possible values are DirectPath::ResultValues
	*
	*/
    typedef Enum<ResultValues> Result;

    /**
     * @brief
     * Constructor
     *
     * @param typeInfo  - Table type info object
     * @param nbCols    - Number of columns to load
     * @param nbRows    - Maximum of rows to handle per load operation
     * @param partition - Partition name
     *
     * @note
     * The partition name is not mandatory
     *
     * @note
     * Parameter 'nbRows' is ignored for Oracle 8i. Prior to Oracle 9i, it's the
     * OCI client that decides of the number of rows to process per convert/load calls.
     * From Oracle 9i, OCI allows application to specify this value. Note that, the
     * OCI client might not accept the input value. After Prepare() has
     * been successfully called, GetMaxRows() returns the final number
     * of rows used for the given direct path operation.
     *
     */
    DirectPath(const TypeInfo &typeInfo, unsigned int nbCols, unsigned int  nbRows, ostring partition = OTEXT(""));

    /**
     * @brief
     * Describe a column to load into the given table
     *
     * @param colIndex - Column index
     * @param name     - Column name
     * @param maxSize  - Maximum input value size for a column entry
     * @param format   - Date or numeric format to use
     *
     * @note
     * An error is thrown if :
     * - If the column specified by the 'name' parameter is not found in the table
     *   referenced by the type info handle passed to the constructor
     * - the index is out of bounds (= 0 or >= number of columns)
     *
     */
    void SetColumn(unsigned int colIndex, ostring name, unsigned int maxSize,  ostring format = OTEXT(""));

    /**
     * @brief
     * Set the value of the given row/column array entry from the given string
     *
     * @param rowIndex  - Row index
     * @param colIndex  - Column index
     * @param value     - Value to set
     * @param complete  - Is the entry content fully provided ?
     *
     * @note
     * Rows and columns indexes start at 1.
     *
     * @note
     * Direct path support piece loading for LONGs and LOBs columns. When filling
     * these columns, it's possible to provide input buffer piece by piece. In order
     * to do so :
     * - set the 'complete' parameter to false
     * - Repeat calls to SetEntry() until the data is totally provided
     * - The last call that set the last piece or an entry must specify the value
     *   true for the 'complete' parameter
     *
     * @warning
     * Current Direct Path OCILIB implementation DOES NOT support setting entry
     * content piece by piece as mentionned above. It was planned in the original design
     * but not supported yet. So, always set the complete parameter to true.
     * Setting entries content piece by piece may be supported in future releases
     *
     */
    void SetEntry(unsigned int rowIndex, unsigned int colIndex,  const ostring &value,  bool complete = true);


    /**
     * @brief
     * Set the value of the given row/column array entry from the giben buffer pointer
     *
     * @param rowIndex  - Row index
     * @param colIndex  - Column index
     * @param value     - Value to set
     * @param size      - Value size
     * @param complete  - Is the entry content fully provided ?
     *
     * @note
     * Rows and columns indexes start at 1.
     *
     * @note
     * Direct path support piece loading for LONGs and LOBs columns. When filling
     * these columns, it's possible to provide input buffer piece by piece. In order
     * to do so :
     * - set the 'complete' parameter to false
     * - Repeat calls to SetEntry() until the data is totally provided
     * - The last call that set the last piece or an entry must specify the value
     *   true for the 'complete' parameter
     *
     * @warning
     * Current Direct Path OCILIB implementation DOES NOT support setting entry
     * content piece by piece as mentionned above. It was planned in the original design
     * but not supported yet. So, always set the complete parameter to true.
     * Setting entries content piece by piece may be supported in future releases
     *
     */
	void SetEntry(unsigned int rowIndex, unsigned int colIndex, const Raw &value, bool complete = true);

    /**
     * @brief
     * Reset internal arrays and streams to prepare another load
     *
     * @note
     * Once some data have been converted or loaded, Reset() resets
     * internal OCI structures in order to prepare another load operation
     * (set entries, convert and load)
     *
     */
    void Reset();

    /**
     * @brief
     * Prepares the OCI direct path load interface before any rows can be converted or loaded
     *
     */
    void Prepare();

    /**
     * @brief
     * Convert provided user data to the direct path stream format
     *
     * @par Behavior
     * - When using conversion mode DirectPath::Default, Convert() stops when
     *   any error is encountered and returns ResultError
     * - When using conversion mode DirectPath::Force, Convert() does not stop
     *   on errors. Instead it discards any erred rows and returns ResultComplete once
     *   all rows are processed.
     *
     * @note
     * List of faulted rows and columns can be retrieved using GetErrorRow() and GetErrorColumn()
     *
     * @note
     * GetAffectedRows() returns the number of rows converted in the last call.
     *
     */
    DirectPath::Result Convert();

    /**
     * @brief
     * Loads the data converted to direct path stream format
     *
     * @note
     * List of faulted rows can be retrieved using GetErrorRow()
     *
     * @note
     * GetAffectedRows() returns the number of rows successfully loaded in the last call.
     *
     */
    DirectPath::Result Load();

    /**
     * @brief
     * Terminate a direct path operation and commit changes into the database
     *
     * @warning
     * The direct path object cannot be used anymore after this call for any more loading operations
     *
     */
    void Finish();

    /**
     * @brief
     * Terminate a direct path operation without committing changes
     *
     * @note
     * Any pending loaded data are cancelled.
     * Any load completion operations, such as index maintenance operations, are not performed.
     *
     * @warning
     * The direct path object cannot be used anymore after this call for any more loading operations
     *
     */
    void Abort();

    /**
     * @brief
     * Execute a data savepoint (server side)
     *
     * @note
     * Executing a data savepoint is not allowed for LOBs
     *
     */
    void Save();

    /**
     * @brief
     * Flushes a partially loaded row from server
     *
     */
    void FlushRow();

    /**
     * @brief
     * Set the current number of rows to convert and load
     *
     * @param value - Number of row to process
     *
     * @warning
     * An OCILIB error will be thrown if the value exceeds the maximum number of
     * rows in the internals arrays
     *
     */
    void SetCurrentRows(unsigned int value);

    /**
     * @brief
     * Return the current number of rows used in the OCILIB internal arrays of rows
     *
     * @return
     * Internal current array size on SUCCESS otherwise 0
     *
     */
    unsigned int GetCurrentRows() const;

    /**
     * @brief
     * Return the maximum number of rows allocated in the OCI and OCILIB internal arrays of rows
     *
     * @return
     * Internal maximum array size on SUCCESS otherwise 0
     *
     */
    unsigned int GetMaxRows() const;

    /**
     * @brief
     * Return the number of rows successfully loaded into the database so far
     *
     * @note
     * Insertions are committed with Finish()
     *
     */
    unsigned int GetRowCount() const;

    /**
     * @brief
     * return the number of rows successfully processed during in the last
     * conversion or loading call
     *
     * @note
     * This function called after :
     *
     * - Convert(), returns the number of converted rows
     * - Load(), returns the number of loaded rows
     *
     */
    unsigned int GetAffectedRows() const;

    /**
     * @brief
     * Set the default date format string for input conversion
     *
     * @param format - date format
     *
     * @note
     * For string to date conversion, Oracle uses :
     * - Column date format
     * - Default date format (modified by this call)
     * - Default global support environment setting
     *
     */
    void SetDateFormat(ostring format);

    /**
     * @brief
     * Set the parallel loading mode
     *
     * @param value - enable/disable parallel mode
     *
     * @note
     * Default value is false.
     *
     * @note
     * Setting the value to TRUE allows multiple load sessions to load the same
     * segment concurrently
     *
     * @par Parallel loading mode (From Oracle documentation)
     *
     * A direct load operation requires that the object being loaded is locked to
     * prevent DML on the object.
     * Note that queries are lock-free and are allowed while the object is being loaded.
     * - For a table load, if the option is set to:
     *   - false, then the table DML X-Lock is acquired.
     *   - true, then the table DML S-Lock is acquired.
     * - For a partition load, if the option is set to:
     *   - false, then the table DML SX-Lock and partition DML X-Lock is acquired.
     *   - true, then the table DML SS-Lock and partition DML S-Lock is acquired.
     *
     */
    void SetParallel(bool value);

    /**
     * @brief
     * Set the logging mode for the loading operation
     *
     * @param value - enable/disable logging
     *
     * @par Logging mode (from Oracle Documentation)
     *
     * The NOLOG attribute of each segment determines whether image redo or
     * invalidation redo is generated:
     * - false : Use the attribute of the segment being loaded.
     * - true  : No logging. Overrides DDL statement, if necessary.
     *
     */
    void SetNoLog(bool value);

    /**
     * @brief
     * Set number of elements in the date cache
     *
     * @param value - Buffer size
     *
     * @note
     * Default value is 0.
     *
     * @note
     * Setting the value to 0 disables the cache
     *
     */
    void SetCacheSize(unsigned int value);

    /**
     * @brief
     * Set the size of the internal stream transfer buffer
     *
     * @param value - Buffer size
     *
     * @note
     * Default value is 64KB.
     *
     */
    void SetBufferSize(unsigned int value);

    /**
     * @brief
     * Set the direct path conversion mode
     *
     * @param value - Conversion mode
     *
     * @note
     * See Convert() for conversion mode details
     *
     * @note
     * Default value is ConversionMode::Default
     *
     */
    void SetConversionMode(ConversionMode value);

    /**
     * @brief
     * Return the index of a column which caused an error during data conversion
     *
     * @warning
     * Direct path colmun indexes start at 1.
     *
     * @note
     * Errors may happen while data is converted to direct path stream format
     * using Convert().
     *
	 * @par Usage after a Convert() call
     * - When using conversion mode DirectPath::Default, Convert() returns
     * DirectPath::ResultError on error and GetErrorColumn() returns the column index that
     * caused the error.
     * - When using conversion mode DirectPath::Force, Convert() returns
     * DirectPath::ResultComplete even on errors. In order to retrieve the list of all column
     * indexes that have erred, the application can call GetErrorColumn()
     * repeatedly until it returns 0.
     *
     * @note
     * The internal value is reset to 0 when calling Convert()
     *
     * @return
     * 0 is no error occurs otherwise the index of the given column which caused an
     * error
     *
     */
    unsigned int GetErrorColumn();

    /**
     * @brief
     * Return the index of a row which caused an error during data conversion
     *
     * @warning
     * Direct path row indexes start at 1.
     *
     * @note
     * Errors may happen :
     * - while data is converted to direct path stream format using Convert()
     * - while data is loaded to database using Load()
     *
	 * @par Usage after a Convert() call
     * - When using conversion mode DirectPath::Default, Convert() returns
     *   DirectPath::ResultError on error and GetErrorRow() returns the row index that
     *   caused the error.
     * - When using conversion mode DirectPath::Force, Convert() returns
     *   DirectPath::ResultComplete even on errors. In order to retrieve the list of all row
     *   indexes that have erred, the application can call GetErrorRow() repeatedly until it returns 0.
     *
     * @par  Usage after a Load() call
     * After a call to Load(), in order to retrieve the list of all faulted rows
     * indexes, the application can call GetErrorRow() repeatedly until it returns 0.
     *
     * @note
     * The internal value is reset to 0 when calling Convert(),Reset() or Load()
     *
     * @return
     * 0 is no error occurs otherwise the index of the given row which caused an
     * error
     *
     */

    unsigned int GetErrorRow();
};

}

#include "ocilib_impl.hpp"


#endif

