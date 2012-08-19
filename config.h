/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */


#ifndef GNUPG_CONFIG_H_INCLUDED
#define GNUPG_CONFIG_H_INCLUDED


/* Define this to an absolute name of <stdint.h>. */
#define ABSOLUTE_STDINT_H "///usr/lib/gcc/x86_64-unknown-linux-gnu/4.7.1/include/stdint.h"

/* Defined if the host has big endian byte ordering */
/* #undef BIG_ENDIAN_HOST */

/* an Apple OSXism */
/* #undef BIND_8_COMPAT */

/* Define to the number of bits in type 'ptrdiff_t'. */
/* #undef BITSIZEOF_PTRDIFF_T */

/* Define to the number of bits in type 'sig_atomic_t'. */
/* #undef BITSIZEOF_SIG_ATOMIC_T */

/* Define to the number of bits in type 'size_t'. */
/* #undef BITSIZEOF_SIZE_T */

/* Define to the number of bits in type 'wchar_t'. */
/* #undef BITSIZEOF_WCHAR_T */

/* Define to the number of bits in type 'wint_t'. */
/* #undef BITSIZEOF_WINT_T */

/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
/* #undef CRAY_STACKSEG_END */

/* Define to 1 if using `alloca.c'. */
/* #undef C_ALLOCA */

/* define to disable keyserver helpers */
/* #undef DISABLE_KEYSERVER_HELPERS */

/* Defined to disable exec-path for keyserver helpers */
/* #undef DISABLE_KEYSERVER_PATH */

/* define to disable photo viewing */
/* #undef DISABLE_PHOTO_VIEWER */

/* Define to disable regular expression support */
/* #undef DISABLE_REGEX */

/* Define to 1 if translation of program messages to the user's native
   language is requested. */
#define ENABLE_NLS 1

/* Define to enable SELinux support */
/* #undef ENABLE_SELINUX_HACKS */

/* The executable file extension, if any */
#define EXEEXT ""

/* if set, restrict photo-viewer to this */
/* #undef FIXED_PHOTO_VIEWER */

/* version of the libbassuan library */
#define GNUPG_LIBASSUAN_VERSION "2.0.3"

/* Define to 1 if you have the `adns_free' function. */
/* #undef HAVE_ADNS_FREE */

/* Define to 1 if you have the <adns.h> header file. */
/* #undef HAVE_ADNS_H */

/* Define to 1 if you have `alloca' after including <alloca.h>, a header that
   may be supplied by this distribution. */
#define HAVE_ALLOCA 1

/* Define HAVE_ALLOCA_H for backward compatibility with older code that
   includes <alloca.h> only if HAVE_ALLOCA_H is defined. */
#define HAVE_ALLOCA_H 1

/* Define to 1 if you have the `atexit' function. */
#define HAVE_ATEXIT 1

/* Defined if a `byte' is typedef'd */
/* #undef HAVE_BYTE_TYPEDEF */

/* Defined if the bz2 compression library is available */
#define HAVE_BZIP2 1

/* Define to 1 if you have the MacOS X function CFLocaleCopyCurrent in the
   CoreFoundation framework. */
/* #undef HAVE_CFLOCALECOPYCURRENT */

/* Define to 1 if you have the MacOS X function CFPreferencesCopyAppValue in
   the CoreFoundation framework. */
/* #undef HAVE_CFPREFERENCESCOPYAPPVALUE */

/* Define to 1 if you have the `clock_gettime' function. */
/* #undef HAVE_CLOCK_GETTIME */

/* Define to 1 if you have the `ctermid' function. */
#define HAVE_CTERMID 1

/* Define if the GNU dcgettext() function is already present or preinstalled.
   */
#define HAVE_DCGETTEXT 1

/* Define to 1 if you have the declaration of `getpagesize', and to 0 if you
   don't. */
#define HAVE_DECL_GETPAGESIZE 1

/* Define to 1 if you have the declaration of `sys_siglist', and to 0 if you
   don't. */
#define HAVE_DECL_SYS_SIGLIST 1

/* Define to 1 if you have the <direct.h> header file. */
/* #undef HAVE_DIRECT_H */

/* Define to 1 if you don't have `vprintf' but do have `_doprnt.' */
/* #undef HAVE_DOPRNT */

/* Defined if we run on some of the PCDOS like systems (DOS, Windoze. OS/2)
   with special properties like no file modes */
/* #undef HAVE_DOSISH_SYSTEM */

/* defined if we must run on a stupid file system */
/* #undef HAVE_DRIVE_LETTERS */

/* Define if you have the declaration of environ. */
/* #undef HAVE_ENVIRON_DECL */

/* Define to 1 if you have the `fcntl' function. */
#define HAVE_FCNTL 1

/* Define to 1 if you have the `flockfile' function. */
#define HAVE_FLOCKFILE 1

/* Define to 1 if you have the `fopencookie' function. */
#define HAVE_FOPENCOOKIE 1

/* Define to 1 if you have the `fork' function. */
#define HAVE_FORK 1

/* Define to 1 if fseeko (and presumably ftello) exists and is declared. */
#define HAVE_FSEEKO 1

/* Define to 1 if you have the `fsync' function. */
#define HAVE_FSYNC 1

/* Define to 1 if you have the `ftello' function. */
#define HAVE_FTELLO 1

/* Define to 1 if you have the `ftruncate' function. */
#define HAVE_FTRUNCATE 1

/* Define to 1 if you have the `funlockfile' function. */
#define HAVE_FUNLOCKFILE 1

/* Define to 1 if you have the `funopen' function. */
/* #undef HAVE_FUNOPEN */

/* Define to 1 if you have the `getaddrinfo' function. */
#define HAVE_GETADDRINFO 1

/* Define to 1 if you have the <getopt.h> header file. */
#define HAVE_GETOPT_H 1

/* Define to 1 if you have the `getpagesize' function. */
#define HAVE_GETPAGESIZE 1

/* Define to 1 if you have the `getpwnam' function. */
#define HAVE_GETPWNAM 1

/* Define to 1 if you have the `getpwuid' function. */
#define HAVE_GETPWUID 1

/* Define to 1 if you have the `getrlimit' function. */
#define HAVE_GETRLIMIT 1

/* Define to 1 if you have the `getrusage' function. */
#define HAVE_GETRUSAGE 1

/* Define if the GNU gettext() function is already present or preinstalled. */
#define HAVE_GETTEXT 1

/* Define to 1 if you have the `gettimeofday' function. */
#define HAVE_GETTIMEOFDAY 1

/* Define to 1 if you have the `gmtime_r' function. */
#define HAVE_GMTIME_R 1

/* Define if you have the iconv() function and it works. */
#define HAVE_ICONV 1

/* Define to 1 if the system has the type `intmax_t'. */
#define HAVE_INTMAX_T 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `isascii' function. */
#define HAVE_ISASCII 1

/* Define if you have <langinfo.h> and nl_langinfo(CODESET). */
#define HAVE_LANGINFO_CODESET 1

/* Define to 1 if you have the <langinfo.h> header file. */
#define HAVE_LANGINFO_H 1

/* Define if you have <langinfo.h> and nl_langinfo(THOUSANDS_SEP). */
#define HAVE_LANGINFO_THOUSANDS_SEP 1

/* Define if your <locale.h> file defines LC_MESSAGES. */
#define HAVE_LC_MESSAGES 1

/* Define to 1 if you have the `ldap_get_option' function. */
#define HAVE_LDAP_GET_OPTION 1

/* Define if the LDAP library supports ld_errno */
/* #undef HAVE_LDAP_LD_ERRNO */

/* Define to 1 if you have the `ldap_set_option' function. */
#define HAVE_LDAP_SET_OPTION 1

/* Define to 1 if you have the `ldap_start_tls_s' function. */
#define HAVE_LDAP_START_TLS_S 1

/* Define to 1 if you have the `ldap_start_tls_sA' function. */
/* #undef HAVE_LDAP_START_TLS_SA */

/* Define to 1 if you have a functional curl library. */
#define HAVE_LIBCURL 1

/* Define to 1 if you have a fully functional readline library. */
#define HAVE_LIBREADLINE 1

/* defined if libusb is available */
#define HAVE_LIBUSB 1

/* defined if libutil is available */
#define HAVE_LIBUTIL 1

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if the system has the type `long double'. */
#define HAVE_LONG_DOUBLE 1

/* Define to 1 if the system has the type `long long int'. */
#define HAVE_LONG_LONG_INT 1

/* Define to 1 if you have the `memicmp' function. */
/* #undef HAVE_MEMICMP */

/* Define to 1 if you have the `memmove' function. */
#define HAVE_MEMMOVE 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memrchr' function. */
#define HAVE_MEMRCHR 1

/* Define to 1 if you have the `mkdtemp' function. */
#define HAVE_MKDTEMP 1

/* Define to 1 if you have the `mmap' function. */
#define HAVE_MMAP 1

/* Define to 1 if you have the `nl_langinfo' function. */
#define HAVE_NL_LANGINFO 1

/* Define to 1 if you have the `pipe' function. */
#define HAVE_PIPE 1

/* Defined if the GNU Pth is available */
#define HAVE_PTH 1

/* Define to 1 if the system has the type `ptrdiff_t'. */
#define HAVE_PTRDIFF_T 1

/* Define to 1 if you have the <pty.h> header file. */
#define HAVE_PTY_H 1

/* Define to 1 if you have the <pwd.h> header file. */
#define HAVE_PWD_H 1

/* Define to 1 if you have the `raise' function. */
#define HAVE_RAISE 1

/* Define to 1 if you have the `rand' function. */
#define HAVE_RAND 1

/* Define to 1 if you have the <search.h> header file. */
/* #undef HAVE_SEARCH_H */

/* Define to 1 if you have the `setenv' function. */
#define HAVE_SETENV 1

/* Define to 1 if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define to 1 if you have the `setrlimit' function. */
#define HAVE_SETRLIMIT 1

/* Define to 1 if you have the `sigaction' function. */
#define HAVE_SIGACTION 1

/* Define to 1 if 'sig_atomic_t' is a signed integer type. */
/* #undef HAVE_SIGNED_SIG_ATOMIC_T */

/* Define to 1 if 'wchar_t' is a signed integer type. */
/* #undef HAVE_SIGNED_WCHAR_T */

/* Define to 1 if 'wint_t' is a signed integer type. */
/* #undef HAVE_SIGNED_WINT_T */

/* Define to 1 if you have the `sigprocmask' function. */
#define HAVE_SIGPROCMASK 1

/* Define to 1 if the system has the type `sigset_t'. */
#define HAVE_SIGSET_T 1

/* Define to 1 if you have the `stat' function. */
#define HAVE_STAT 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `stpcpy' function. */
#define HAVE_STPCPY 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the `strftime' function. */
#define HAVE_STRFTIME 1

/* Define to 1 if you have the `stricmp' function. */
/* #undef HAVE_STRICMP */

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strlwr' function. */
/* #undef HAVE_STRLWR */

/* Define to 1 if you have the `strncasecmp' function. */
#define HAVE_STRNCASECMP 1

/* Define to 1 if you have the `strpbrk' function. */
#define HAVE_STRPBRK 1

/* Define to 1 if you have the `strsep' function. */
#define HAVE_STRSEP 1

/* Define to 1 if you have the `strtol' function. */
#define HAVE_STRTOL 1

/* Define to 1 if you have the `strtoul' function. */
#define HAVE_STRTOUL 1

/* Define to 1 if the system has the type `struct sigaction'. */
#define HAVE_STRUCT_SIGACTION 1

/* Define to 1 if you have the <sys/bitypes.h> header file. */
/* #undef HAVE_SYS_BITYPES_H */

/* Define to 1 if you have the <sys/inttypes.h> header file. */
/* #undef HAVE_SYS_INTTYPES_H */

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the `tcgetattr' function. */
#define HAVE_TCGETATTR 1

/* Define to 1 if you have the <termio.h> header file. */
#define HAVE_TERMIO_H 1

/* Define to 1 if you have the `timegm' function. */
#define HAVE_TIMEGM 1

/* Define to 1 if you have the `times' function. */
#define HAVE_TIMES 1

/* Define to 1 if you have the <time.h> header file. */
/* #undef HAVE_TIME_H */

/* Define to 1 if you have the `tsearch' function. */
/* #undef HAVE_TSEARCH */

/* Define to 1 if you have the `ttyname' function. */
#define HAVE_TTYNAME 1

/* Defined if a `u16' is typedef'd */
/* #undef HAVE_U16_TYPEDEF */

/* Defined if a `u32' is typedef'd */
/* #undef HAVE_U32_TYPEDEF */

/* Define to 1 if the system has the type `uintmax_t'. */
#define HAVE_UINTMAX_T 1

/* Defined if a `ulong' is typedef'd */
#define HAVE_ULONG_TYPEDEF 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `unsetenv' function. */
#define HAVE_UNSETENV 1

/* Define to 1 if the system has the type `unsigned long long int'. */
#define HAVE_UNSIGNED_LONG_LONG_INT 1

/* Define to 1 if you have the `usb_create_match' function. */
/* #undef HAVE_USB_CREATE_MATCH */

/* Defined if a `ushort' is typedef'd */
#define HAVE_USHORT_TYPEDEF 1

/* Define to 1 if you have the <utmp.h> header file. */
#define HAVE_UTMP_H 1

/* Define to 1 if you have the `vfork' function. */
#define HAVE_VFORK 1

/* Define to 1 if you have the <vfork.h> header file. */
/* #undef HAVE_VFORK_H */

/* Define to 1 if you have the `vprintf' function. */
#define HAVE_VPRINTF 1

/* Defined if we run on a W32 API based system */
/* #undef HAVE_W32_SYSTEM */

/* Define to 1 if you have the `wait4' function. */
#define HAVE_WAIT4 1

/* Define to 1 if you have the `waitpid' function. */
#define HAVE_WAITPID 1

/* Define to 1 if you have the <wchar.h> header file. */
#define HAVE_WCHAR_H 1

/* Define to 1 if you have the <winsock2.h> header file. */
/* #undef HAVE_WINSOCK2_H */

/* Define to 1 if `fork' works. */
#define HAVE_WORKING_FORK 1

/* Define to 1 if `vfork' works. */
#define HAVE_WORKING_VFORK 1

/* Define to 1 if you have the <ws2tcpip.h> header file. */
/* #undef HAVE_WS2TCPIP_H */

/* Define as const if the declaration of iconv() needs const. */
#define ICONV_CONST 

/* Defined if this is not a regular release */
/* #undef IS_DEVELOPMENT_VERSION */

/* Defined if libcurl supports AsynchDNS */
#define LIBCURL_FEATURE_ASYNCHDNS 1

/* Defined if libcurl supports IDN */
/* #undef LIBCURL_FEATURE_IDN */

/* Defined if libcurl supports IPv6 */
#define LIBCURL_FEATURE_IPV6 1

/* Defined if libcurl supports KRB4 */
/* #undef LIBCURL_FEATURE_KRB4 */

/* Defined if libcurl supports libz */
#define LIBCURL_FEATURE_LIBZ 1

/* Defined if libcurl supports NTLM */
#define LIBCURL_FEATURE_NTLM 1

/* Defined if libcurl supports SSL */
#define LIBCURL_FEATURE_SSL 1

/* Defined if libcurl supports SSPI */
/* #undef LIBCURL_FEATURE_SSPI */

/* Defined if libcurl supports DICT */
#define LIBCURL_PROTOCOL_DICT 1

/* Defined if libcurl supports FILE */
#define LIBCURL_PROTOCOL_FILE 1

/* Defined if libcurl supports FTP */
#define LIBCURL_PROTOCOL_FTP 1

/* Defined if libcurl supports FTPS */
#define LIBCURL_PROTOCOL_FTPS 1

/* Defined if libcurl supports HTTP */
#define LIBCURL_PROTOCOL_HTTP 1

/* Defined if libcurl supports HTTPS */
#define LIBCURL_PROTOCOL_HTTPS 1

/* Defined if libcurl supports LDAP */
/* #undef LIBCURL_PROTOCOL_LDAP */

/* Defined if libcurl supports TELNET */
#define LIBCURL_PROTOCOL_TELNET 1

/* Defined if libcurl supports TFTP */
#define LIBCURL_PROTOCOL_TFTP 1

/* Defined if the host has little endian byte ordering */
#define LITTLE_ENDIAN_HOST 1

/* If malloc(0) is != NULL, define this to 1. Otherwise define this to 0. */
#define MALLOC_0_IS_NONNULL 1

/* Defined if mkdir() does not take permission flags */
/* #undef MKDIR_TAKES_ONE_ARG */

/* Required version of Libksba */
#define NEED_KSBA_VERSION "1.0.7"

/* Define if the LDAP library requires including lber.h before ldap.h */
/* #undef NEED_LBER_H */

/* Required version of Libgcrypt */
#define NEED_LIBGCRYPT_VERSION "1.4.0"

/* Define to disable all external program execution */
/* #undef NO_EXEC */

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Name of this package */
#define PACKAGE "gnupg"

/* Bug report address */
#define PACKAGE_BUGREPORT "http://bugs.gnupg.org"

/* Name of this package for gettext */
#define PACKAGE_GT "gnupg2"

/* Define to the full name of this package. */
#define PACKAGE_NAME "gnupg"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "gnupg 2.0.19"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "gnupg"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "2.0.19"

/* Size of the key and UID caches */
#define PK_UID_CACHE_SIZE 4096

/* A human readable text with the name of the OS */
#define PRINTABLE_OS_NAME "GNU/Linux"

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'ptrdiff_t'. */
/* #undef PTRDIFF_T_SUFFIX */

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* defines the filename of the shred program */
#define SHRED "/usr/bin/shred"

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'sig_atomic_t'. */
/* #undef SIG_ATOMIC_T_SUFFIX */

/* The size of `time_t', as computed by sizeof. */
#define SIZEOF_TIME_T 8

/* The size of `uint64_t', as computed by sizeof. */
#define SIZEOF_UINT64_T 8

/* The size of `unsigned int', as computed by sizeof. */
#define SIZEOF_UNSIGNED_INT 4

/* The size of `unsigned long', as computed by sizeof. */
#define SIZEOF_UNSIGNED_LONG 8

/* The size of `unsigned long long', as computed by sizeof. */
#define SIZEOF_UNSIGNED_LONG_LONG 8

/* The size of `unsigned short', as computed by sizeof. */
#define SIZEOF_UNSIGNED_SHORT 2

/* The size of `void *', as computed by sizeof. */
#define SIZEOF_VOID_P 8

/* Define as the maximum value of type 'size_t', if the system doesn't define
   it. */
/* #undef SIZE_MAX */

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'size_t'. */
/* #undef SIZE_T_SUFFIX */

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at runtime.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
/* #undef STACK_DIRECTION */

/* Define to 1 if the `S_IS*' macros in <sys/stat.h> do not work properly. */
/* #undef STAT_MACROS_BROKEN */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Use ADNS as resolver library. */
/* #undef USE_ADNS */

/* define to use DNS CERT */
#define USE_DNS_CERT 1

/* define to use our experimental DNS PKA */
#define USE_DNS_PKA 1

/* define to use DNS SRV */
#define USE_DNS_SRV 1

/* Defined if the GNU Portable Thread Library should be used */
#define USE_GNU_PTH 1

/* set this to limit filenames to the 8.3 format */
/* #undef USE_ONLY_8DOT3 */

/* because the Unix gettext has too much overhead on MingW32 systems and these
   systems lack Posix functions, we use a simplified version of gettext */
/* #undef USE_SIMPLE_GETTEXT */

/* Use a standard socket for the agent by default */
/* #undef USE_STANDARD_SOCKET */

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Version of this package */
#define VERSION "2.0.19"

/* Define if unsetenv() returns void, not int. */
/* #undef VOID_UNSETENV */

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'wchar_t'. */
/* #undef WCHAR_T_SUFFIX */

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'wint_t'. */
/* #undef WINT_T_SUFFIX */

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define to 1 to make fseeko visible on some hosts (e.g. glibc 2.2). */
/* #undef _LARGEFILE_SOURCE */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define curl_free() as free() if our version of curl lacks curl_free. */
/* #undef curl_free */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to the widest signed integer type if <stdint.h> and <inttypes.h> do
   not define. */
/* #undef intmax_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef mode_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* type to use in place of socklen_t if not defined */
/* #undef socklen_t */

/* Define to the widest unsigned integer type if <stdint.h> and <inttypes.h>
   do not define. */
/* #undef uintmax_t */

/* Define as `fork' if `vfork' does not work. */
/* #undef vfork */

/* Define to empty if the keyword `volatile' does not work. Warning: valid
   code using `volatile' can become incorrect without. Disable with care. */
/* #undef volatile */


/* This is the major version number of GnuPG so that
   source included files can test for this.  Note, that
   we use 2 here even for GnuPG 1.9.x. */
#define GNUPG_MAJOR_VERSION 2

/* Now to separate file name parts.
   Please note that the string version must not contain more
   than one character because the code assumes strlen()==1 */
#ifdef HAVE_DOSISH_SYSTEM
#define DIRSEP_C '\\'
#define DIRSEP_S "\\"
#define EXTSEP_C '.'
#define EXTSEP_S "."
#define PATHSEP_C ';'
#define PATHSEP_S ";"
#define EXEEXT_S ".exe"
#else
#define DIRSEP_C '/'
#define DIRSEP_S "/"
#define EXTSEP_C '.'
#define EXTSEP_S "."
#define PATHSEP_C ':'
#define PATHSEP_S ":"
#define EXEEXT_S ""
#endif

/* This is the same as VERSION, but should be overridden if the
   platform cannot handle things like dots '.' in filenames. Set
   SAFE_VERSION_DOT and SAFE_VERSION_DASH to whatever SAFE_VERSION
   uses for dots and dashes. */
#define SAFE_VERSION VERSION
#define SAFE_VERSION_DOT  '.'
#define SAFE_VERSION_DASH '-'

/* Some global constants. */
#ifdef HAVE_DRIVE_LETTERS
#define GNUPG_DEFAULT_HOMEDIR "c:/gnupg"
#elif defined(__VMS)
#define GNUPG_DEFAULT_HOMEDIR "/SYS\$LOGIN/gnupg"
#else
#define GNUPG_DEFAULT_HOMEDIR "~/.gnupg"
#endif
#define GNUPG_PRIVATE_KEYS_DIR "private-keys-v1.d"

/* For some systems (DOS currently), we hardcode the path here.  For
   POSIX systems the values are constructed by the Makefiles, so that
   the values may be overridden by the make invocations; this is to
   comply with the GNU coding standards. */
#ifdef HAVE_DRIVE_LETTERS
 /* FIXME: We need to use a function to determine these values depending
    on the actual installation directory. */
#define GNUPG_BINDIR      "c:\\gnupg"
#define GNUPG_LIBEXECDIR  "c:\\gnupg"
#define GNUPG_LIBDIR      "c:\\gnupg"
#define GNUPG_DATADIR     "c:\\gnupg"
#define GNUPG_SYSCONFDIR  "c:\\gnupg"
#endif

/* Derive some other constants. */
#if !(defined(HAVE_FORK) && defined(HAVE_PIPE) && defined(HAVE_WAITPID))
#define EXEC_TEMPFILE_ONLY
#endif


/* We didn't define endianness above, so get it from OS macros.  This
   is intended for making fat binary builds on OS X. */
#if !defined(BIG_ENDIAN_HOST) && !defined(LITTLE_ENDIAN_HOST)
#if defined(__BIG_ENDIAN__)
#define BIG_ENDIAN_HOST 1
#elif defined(__LITTLE_ENDIAN__)
#define LITTLE_ENDIAN_HOST 1
#else
#error "No endianness found"
#endif
#endif


/* Hack used for W32: ldap.m4 also tests for the ASCII version of
   ldap_start_tls_s because that is the actual symbol used in the
   library.  winldap.h redefines it to our commonly used value,
   thus we define our usual macro here.  */
#ifdef HAVE_LDAP_START_TLS_SA
# ifndef HAVE_LDAP_START_TLS_S
#  define HAVE_LDAP_START_TLS_S 1
# endif
#endif


/* Tell libgcrypt not to use its own libgpg-error implementation. */
#define USE_LIBGPG_ERROR 1

/* We use jnlib, so tell other modules about it.  */
#define HAVE_JNLIB_LOGGING 1

/* Our HTTP code is used in estream mode.  */
#define HTTP_USE_ESTREAM 1

/* Under W32 we do an explicit socket initialization, thus we need to
   avoid the on-demand initialization which would also install an atexit
   handler.  */
#define HTTP_NO_WSASTARTUP

/* We always include support for the OpenPGP card.  */
#define ENABLE_CARD_SUPPORT 1

/* We don't want the old assuan codes anymore. */
#define _ASSUAN_ONLY_GPG_ERRORS 1

/* We explicitly need to disable PTH's soft mapping as Debian
   currently enables it by default for no reason. */
#define PTH_SYSCALL_SOFT 0

/* We want to use the libgcrypt provided memory allocation for
   asprintf.  */
#define _ESTREAM_PRINTF_MALLOC        gcry_malloc
#define _ESTREAM_PRINTF_FREE          gcry_free
#define _ESTREAM_PRINTF_EXTRA_INCLUDE "util.h"

#endif /*GNUPG_CONFIG_H_INCLUDED*/

