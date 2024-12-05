/* Define the alignment attribute for externally callable functions. */
#define FORCE_ALIGN 

/* Define if HRTF data is embedded in the library */
#define ALSOFT_EMBED_HRTF_DATA

/* Define if we have the proc_pidpath function */
/* #undef HAVE_PROC_PIDPATH */

/* Define if we have dlfcn.h */
#define HAVE_DLFCN_H

/* Define if we have pthread_np.h */
/* #undef HAVE_PTHREAD_NP_H */

/* Define if we have cpuid.h */
#define HAVE_CPUID_H

/* Define if we have intrin.h */
/* #undef HAVE_INTRIN_H */

/* Define if we have guiddef.h */
/* #undef HAVE_GUIDDEF_H */

/* Define if we have GCC's __get_cpuid() */
#define HAVE_GCC_GET_CPUID

/* Define if we have the __cpuid() intrinsic */
/* #undef HAVE_CPUID_INTRINSIC */

/* Define if we have pthread_setschedparam() */
#define HAVE_PTHREAD_SETSCHEDPARAM

/* Define if we have pthread_setname_np() */
/* #undef HAVE_PTHREAD_SETNAME_NP */

/* Define if we have pthread_set_name_np() */
/* #undef HAVE_PTHREAD_SET_NAME_NP */

/* Define the installation data directory */
/* #undef ALSOFT_INSTALL_DATADIR */

/* Define to 1 if we have DBus/RTKit, else 0 */
#define HAVE_RTKIT 1

/* Define to 1 if building for winuwp, else 0 */
#define ALSOFT_UWP 0

/* Define to 1 if building with legacy EAX API support, else 0 */
#define ALSOFT_EAX 0
