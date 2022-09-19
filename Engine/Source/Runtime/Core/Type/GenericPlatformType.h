#pragma once

template<typename T32bit, typename T64bit, int PointerSize>
struct SelectIntPointerType {};

template<typename T32bit, typename T64bit>
struct SelectIntPointerType<T32bit, T64bit, 8> {
    typedef T64bit TIntPointer;
};

template<typename T32bit, typename T64bit>
struct SelectIntPointerType<T32bit, T64bit, 4> {
    typedef T32bit TIntPointer;
};

struct GenericPlatformType {
    // Unsigned primitive types
    typedef unsigned char u8;
    typedef unsigned short int u16;
    typedef unsigned int u32;
    typedef unsigned long long u64;

    // Signed primitive types
    typedef signed char i8;
    typedef signed short int i16;
    typedef signed int i32;
    typedef signed long long i64;

    // Arch & Platform specific
    typedef unsigned long usize;
    typedef signed long isize;

    typedef SelectIntPointerType<u32, u64, sizeof(void*)>::TIntPointer uptr;
    typedef SelectIntPointerType<i32, i64, sizeof(void*)>::TIntPointer iptr;
    typedef uptr size_t;
    typedef iptr sszie_t;

};
