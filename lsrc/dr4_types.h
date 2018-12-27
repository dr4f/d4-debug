#ifndef DR4_TYPES_H
#define DR4_TYPES_H

/**
 * Header specifies the data types supported within a dr4 row body.
 */

// Stop type
#define DR4_TYPE_STOP 0
// state type
#define DR4_TYPE_NONE 1
#define DR4_TYPE_BOOL 2
// unsigned integer types
#define DR4_TYPE_UI08 3
#define DR4_TYPE_UI16 4
#define DR4_TYPE_UI32 5
#define DR4_TYPE_UI64 6
// signed integer types
#define DR4_TYPE_SI08 7
#define DR4_TYPE_SI16 8
#define DR4_TYPE_SI32 9
#define DR4_TYPE_SI64 10
// floating point types
#define DR4_TYPE_SGFN 11
#define DR4_TYPE_DBFN 12
// unix time type
#define DR4_TYPE_UNXT 13
// c string and raw bytes type.
#define DR4_TYPE_CSTR 14
#define DR4_TYPE_RAWB 15
// pair type.
#define DR4_TYPE_PAIR 16


#endif // DR4_TYPES_H
