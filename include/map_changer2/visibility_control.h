#ifndef MAP_CHANGER2__VISIBILITY_CONTROL_H_
#define MAP_CHANGER2__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define MAP_CHANGER2_EXPORT __attribute__ ((dllexport))
    #define MAP_CHANGER2_IMPORT __attribute__ ((dllimport))
  #else
    #define MAP_CHANGER2_EXPORT __declspec(dllexport)
    #define MAP_CHANGER2_IMPORT __declspec(dllimport)
  #endif
  #ifdef MAP_CHANGER2_BUILDING_LIBRARY
    #define MAP_CHANGER2_PUBLIC MAP_CHANGER2_EXPORT
  #else
    #define MAP_CHANGER2_PUBLIC MAP_CHANGER2_IMPORT
  #endif
  #define MAP_CHANGER2_PUBLIC_TYPE MAP_CHANGER2_PUBLIC
  #define MAP_CHANGER2_LOCAL
#else
  #define MAP_CHANGER2_EXPORT __attribute__ ((visibility("default")))
  #define MAP_CHANGER2_IMPORT
  #if __GNUC__ >= 4
    #define MAP_CHANGER2_PUBLIC __attribute__ ((visibility("default")))
    #define MAP_CHANGER2_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define MAP_CHANGER2_PUBLIC
    #define MAP_CHANGER2_LOCAL
  #endif
  #define MAP_CHANGER2_PUBLIC_TYPE
#endif

#endif  // MAP_CHANGER2__VISIBILITY_CONTROL_H_
