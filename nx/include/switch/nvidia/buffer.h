#pragma once

#include "../types.h"

typedef enum {
    NvBufferFlags_Writable=1,
    NvBufferFlags_Nintendo=0x20000,
} NvBufferFlags;

typedef enum {
    NvBufferKind_Pitch=0x0,
    NvBufferKind_Z16=0x1,
    NvBufferKind_Z16_2C=0x2,
    NvBufferKind_Z16_MS2_2C=0x3,
    NvBufferKind_Z16_MS4_2C=0x4,
    NvBufferKind_Z16_MS8_2C=0x5,
    NvBufferKind_Z16_MS16_2C=0x6,
    NvBufferKind_Z16_2Z=0x7,
    NvBufferKind_Z16_MS2_2Z=0x8,
    NvBufferKind_Z16_MS4_2Z=0x9,
    NvBufferKind_Z16_MS8_2Z=0xa,
    NvBufferKind_Z16_MS16_2Z=0xb,
    NvBufferKind_Z16_4CZ=0xC,
    NvBufferKind_Z16_MS2_4CZ=0xd,
    NvBufferKind_Z16_MS4_4CZ=0xe,
    NvBufferKind_Z16_MS8_4CZ=0xf,
    NvBufferKind_Z16_MS16_4CZ=0x10,
    NvBufferKind_S8Z24=0x11,
    NvBufferKind_S8Z24_1Z=0x12,
    NvBufferKind_S8Z24_MS2_1Z=0x13,
    NvBufferKind_S8Z24_MS4_1Z=0x14,
    NvBufferKind_S8Z24_MS8_1Z=0x15,
    NvBufferKind_S8Z24_MS16_1Z=0x16,
    NvBufferKind_S8Z24_2CZ=0x17,
    NvBufferKind_S8Z24_MS2_2CZ=0x18,
    NvBufferKind_S8Z24_MS4_2CZ=0x19,
    NvBufferKind_S8Z24_MS8_2CZ=0x1a,
    NvBufferKind_S8Z24_MS16_2CZ=0x1b,
    NvBufferKind_S8Z24_2CS=0x1C,
    NvBufferKind_S8Z24_MS2_2CS=0x1d,
    NvBufferKind_S8Z24_MS4_2CS=0x1e,
    NvBufferKind_S8Z24_MS8_2CS=0x1f,
    NvBufferKind_S8Z24_MS16_2CS=0x20,
    NvBufferKind_S8Z24_4CSZV=0x21,
    NvBufferKind_S8Z24_MS2_4CSZV=0x22,
    NvBufferKind_S8Z24_MS4_4CSZV=0x23,
    NvBufferKind_S8Z24_MS8_4CSZV=0x24,
    NvBufferKind_S8Z24_MS16_4CSZV=0x25,
    NvBufferKind_V8Z24_MS4_VC12=0x26,
    NvBufferKind_V8Z24_MS4_VC4=0x27,
    NvBufferKind_V8Z24_MS8_VC8=0x28,
    NvBufferKind_V8Z24_MS8_VC24=0x29,
    NvBufferKind_S8=0x2a,
    NvBufferKind_S8_2S=0x2b,
    NvBufferKind_V8Z24_MS4_VC12_1ZV=0x2e,
    NvBufferKind_V8Z24_MS4_VC4_1ZV=0x2f,
    NvBufferKind_V8Z24_MS8_VC8_1ZV=0x30,
    NvBufferKind_V8Z24_MS8_VC24_1ZV=0x31,
    NvBufferKind_V8Z24_MS4_VC12_2CS=0x32,
    NvBufferKind_V8Z24_MS4_VC4_2CS=0x33,
    NvBufferKind_V8Z24_MS8_VC8_2CS=0x34,
    NvBufferKind_V8Z24_MS8_VC24_2CS=0x35,
    NvBufferKind_V8Z24_MS4_VC12_2CZV=0x3a,
    NvBufferKind_V8Z24_MS4_VC4_2CZV=0x3b,
    NvBufferKind_V8Z24_MS8_VC8_2CZV=0x3C,
    NvBufferKind_V8Z24_MS8_VC24_2CZV=0x3d,
    NvBufferKind_V8Z24_MS4_VC12_2ZV=0x3e,
    NvBufferKind_V8Z24_MS4_VC4_2ZV=0x3f,
    NvBufferKind_V8Z24_MS8_VC8_2ZV=0x40,
    NvBufferKind_V8Z24_MS8_VC24_2ZV=0x41,
    NvBufferKind_V8Z24_MS4_VC12_4CSZV=0x42,
    NvBufferKind_V8Z24_MS4_VC4_4CSZV=0x43,
    NvBufferKind_V8Z24_MS8_VC8_4CSZV=0x44,
    NvBufferKind_V8Z24_MS8_VC24_4CSZV=0x45,
    NvBufferKind_Z24S8=0x46,
    NvBufferKind_Z24S8_1Z=0x47,
    NvBufferKind_Z24S8_MS2_1Z=0x48,
    NvBufferKind_Z24S8_MS4_1Z=0x49,
    NvBufferKind_Z24S8_MS8_1Z=0x4a,
    NvBufferKind_Z24S8_MS16_1Z=0x4b,
    NvBufferKind_Z24S8_2CS=0x4C,
    NvBufferKind_Z24S8_MS2_2CS=0x4d,
    NvBufferKind_Z24S8_MS4_2CS=0x4e,
    NvBufferKind_Z24S8_MS8_2CS=0x4f,
    NvBufferKind_Z24S8_MS16_2CS=0x50,
    NvBufferKind_Z24S8_2CZ=0x51,
    NvBufferKind_Z24S8_MS2_2CZ=0x52,
    NvBufferKind_Z24S8_MS4_2CZ=0x53,
    NvBufferKind_Z24S8_MS8_2CZ=0x54,
    NvBufferKind_Z24S8_MS16_2CZ=0x55,
    NvBufferKind_Z24S8_4CSZV=0x56,
    NvBufferKind_Z24S8_MS2_4CSZV=0x57,
    NvBufferKind_Z24S8_MS4_4CSZV=0x58,
    NvBufferKind_Z24S8_MS8_4CSZV=0x59,
    NvBufferKind_Z24S8_MS16_4CSZV=0x5a,
    NvBufferKind_Z24V8_MS4_VC12=0x5b,
    NvBufferKind_Z24V8_MS4_VC4=0x5C,
    NvBufferKind_Z24V8_MS8_VC8=0x5d,
    NvBufferKind_Z24V8_MS8_VC24=0x5e,
    NvBufferKind_Z24V8_MS4_VC12_1ZV=0x63,
    NvBufferKind_Z24V8_MS4_VC4_1ZV=0x64,
    NvBufferKind_Z24V8_MS8_VC8_1ZV=0x65,
    NvBufferKind_Z24V8_MS8_VC24_1ZV=0x66,
    NvBufferKind_Z24V8_MS4_VC12_2CS=0x67,
    NvBufferKind_Z24V8_MS4_VC4_2CS=0x68,
    NvBufferKind_Z24V8_MS8_VC8_2CS=0x69,
    NvBufferKind_Z24V8_MS8_VC24_2CS=0x6a,
    NvBufferKind_Z24V8_MS4_VC12_2CZV=0x6f,
    NvBufferKind_Z24V8_MS4_VC4_2CZV=0x70,
    NvBufferKind_Z24V8_MS8_VC8_2CZV=0x71,
    NvBufferKind_Z24V8_MS8_VC24_2CZV=0x72,
    NvBufferKind_Z24V8_MS4_VC12_2ZV=0x73,
    NvBufferKind_Z24V8_MS4_VC4_2ZV=0x74,
    NvBufferKind_Z24V8_MS8_VC8_2ZV=0x75,
    NvBufferKind_Z24V8_MS8_VC24_2ZV=0x76,
    NvBufferKind_Z24V8_MS4_VC12_4CSZV=0x77,
    NvBufferKind_Z24V8_MS4_VC4_4CSZV=0x78,
    NvBufferKind_Z24V8_MS8_VC8_4CSZV=0x79,
    NvBufferKind_Z24V8_MS8_VC24_4CSZV=0x7a,
    NvBufferKind_ZF32=0x7b,
    NvBufferKind_ZF32_1Z=0x7C,
    NvBufferKind_ZF32_MS2_1Z=0x7d,
    NvBufferKind_ZF32_MS4_1Z=0x7e,
    NvBufferKind_ZF32_MS8_1Z=0x7f,
    NvBufferKind_ZF32_MS16_1Z=0x80,
    NvBufferKind_ZF32_2CS=0x81,
    NvBufferKind_ZF32_MS2_2CS=0x82,
    NvBufferKind_ZF32_MS4_2CS=0x83,
    NvBufferKind_ZF32_MS8_2CS=0x84,
    NvBufferKind_ZF32_MS16_2CS=0x85,
    NvBufferKind_ZF32_2CZ=0x86,
    NvBufferKind_ZF32_MS2_2CZ=0x87,
    NvBufferKind_ZF32_MS4_2CZ=0x88,
    NvBufferKind_ZF32_MS8_2CZ=0x89,
    NvBufferKind_ZF32_MS16_2CZ=0x8a,
    NvBufferKind_X8Z24_X16V8S8_MS4_VC12=0x8b,
    NvBufferKind_X8Z24_X16V8S8_MS4_VC4=0x8C,
    NvBufferKind_X8Z24_X16V8S8_MS8_VC8=0x8d,
    NvBufferKind_X8Z24_X16V8S8_MS8_VC24=0x8e,
    NvBufferKind_X8Z24_X16V8S8_MS4_VC12_1CS=0x8f,
    NvBufferKind_X8Z24_X16V8S8_MS4_VC4_1CS=0x90,
    NvBufferKind_X8Z24_X16V8S8_MS8_VC8_1CS=0x91,
    NvBufferKind_X8Z24_X16V8S8_MS8_VC24_1CS=0x92,
    NvBufferKind_X8Z24_X16V8S8_MS4_VC12_1ZV=0x97,
    NvBufferKind_X8Z24_X16V8S8_MS4_VC4_1ZV=0x98,
    NvBufferKind_X8Z24_X16V8S8_MS8_VC8_1ZV=0x99,
    NvBufferKind_X8Z24_X16V8S8_MS8_VC24_1ZV=0x9a,
    NvBufferKind_X8Z24_X16V8S8_MS4_VC12_1CZV=0x9b,
    NvBufferKind_X8Z24_X16V8S8_MS4_VC4_1CZV=0x9C,
    NvBufferKind_X8Z24_X16V8S8_MS8_VC8_1CZV=0x9d,
    NvBufferKind_X8Z24_X16V8S8_MS8_VC24_1CZV=0x9e,
    NvBufferKind_X8Z24_X16V8S8_MS4_VC12_2CS=0x9f,
    NvBufferKind_X8Z24_X16V8S8_MS4_VC4_2CS=0xa0,
    NvBufferKind_X8Z24_X16V8S8_MS8_VC8_2CS=0xa1,
    NvBufferKind_X8Z24_X16V8S8_MS8_VC24_2CS=0xa2,
    NvBufferKind_X8Z24_X16V8S8_MS4_VC12_2CSZV=0xa3,
    NvBufferKind_X8Z24_X16V8S8_MS4_VC4_2CSZV=0xa4,
    NvBufferKind_X8Z24_X16V8S8_MS8_VC8_2CSZV=0xa5,
    NvBufferKind_X8Z24_X16V8S8_MS8_VC24_2CSZV=0xa6,
    NvBufferKind_ZF32_X16V8S8_MS4_VC12=0xa7,
    NvBufferKind_ZF32_X16V8S8_MS4_VC4=0xa8,
    NvBufferKind_ZF32_X16V8S8_MS8_VC8=0xa9,
    NvBufferKind_ZF32_X16V8S8_MS8_VC24=0xaa,
    NvBufferKind_ZF32_X16V8S8_MS4_VC12_1CS=0xab,
    NvBufferKind_ZF32_X16V8S8_MS4_VC4_1CS=0xaC,
    NvBufferKind_ZF32_X16V8S8_MS8_VC8_1CS=0xad,
    NvBufferKind_ZF32_X16V8S8_MS8_VC24_1CS=0xae,
    NvBufferKind_ZF32_X16V8S8_MS4_VC12_1ZV=0xb3,
    NvBufferKind_ZF32_X16V8S8_MS4_VC4_1ZV=0xb4,
    NvBufferKind_ZF32_X16V8S8_MS8_VC8_1ZV=0xb5,
    NvBufferKind_ZF32_X16V8S8_MS8_VC24_1ZV=0xb6,
    NvBufferKind_ZF32_X16V8S8_MS4_VC12_1CZV=0xb7,
    NvBufferKind_ZF32_X16V8S8_MS4_VC4_1CZV=0xb8,
    NvBufferKind_ZF32_X16V8S8_MS8_VC8_1CZV=0xb9,
    NvBufferKind_ZF32_X16V8S8_MS8_VC24_1CZV=0xba,
    NvBufferKind_ZF32_X16V8S8_MS4_VC12_2CS=0xbb,
    NvBufferKind_ZF32_X16V8S8_MS4_VC4_2CS=0xbC,
    NvBufferKind_ZF32_X16V8S8_MS8_VC8_2CS=0xbd,
    NvBufferKind_ZF32_X16V8S8_MS8_VC24_2CS=0xbe,
    NvBufferKind_ZF32_X16V8S8_MS4_VC12_2CSZV=0xbf,
    NvBufferKind_ZF32_X16V8S8_MS4_VC4_2CSZV=0xC0,
    NvBufferKind_ZF32_X16V8S8_MS8_VC8_2CSZV=0xC1,
    NvBufferKind_ZF32_X16V8S8_MS8_VC24_2CSZV=0xC2,
    NvBufferKind_ZF32_X24S8=0xC3,
    NvBufferKind_ZF32_X24S8_1CS=0xC4,
    NvBufferKind_ZF32_X24S8_MS2_1CS=0xC5,
    NvBufferKind_ZF32_X24S8_MS4_1CS=0xC6,
    NvBufferKind_ZF32_X24S8_MS8_1CS=0xC7,
    NvBufferKind_ZF32_X24S8_MS16_1CS=0xC8,
    NvBufferKind_SmskedMessage=0xCa,
    NvBufferKind_SmhostMessage=0xCb,
    NvBufferKind_C64_MS2_2CRA=0xCd,
    NvBufferKind_ZF32_X24S8_2CSZV=0xCe,
    NvBufferKind_ZF32_X24S8_MS2_2CSZV=0xCf,
    NvBufferKind_ZF32_X24S8_MS4_2CSZV=0xd0,
    NvBufferKind_ZF32_X24S8_MS8_2CSZV=0xd1,
    NvBufferKind_ZF32_X24S8_MS16_2CSZV=0xd2,
    NvBufferKind_ZF32_X24S8_2CS=0xd3,
    NvBufferKind_ZF32_X24S8_MS2_2CS=0xd4,
    NvBufferKind_ZF32_X24S8_MS4_2CS=0xd5,
    NvBufferKind_ZF32_X24S8_MS8_2CS=0xd6,
    NvBufferKind_ZF32_X24S8_MS16_2CS=0xd7,
    NvBufferKind_C32_2C=0xd8,
    NvBufferKind_C32_2CBR=0xd9,
    NvBufferKind_C32_2CBA=0xda,
    NvBufferKind_C32_2CRA=0xdb,
    NvBufferKind_C32_2BRA=0xdC,
    NvBufferKind_C32_MS2_2C=0xdd,
    NvBufferKind_C32_MS2_2CBR=0xde,
    NvBufferKind_C32_MS2_2CRA=0xCC,
    NvBufferKind_C32_MS4_2C=0xdf,
    NvBufferKind_C32_MS4_2CBR=0xe0,
    NvBufferKind_C32_MS4_2CBA=0xe1,
    NvBufferKind_C32_MS4_2CRA=0xe2,
    NvBufferKind_C32_MS4_2BRA=0xe3,
    NvBufferKind_C32_MS8_MS16_2C=0xe4,
    NvBufferKind_C32_MS8_MS16_2CRA=0xe5,
    NvBufferKind_C64_2C=0xe6,
    NvBufferKind_C64_2CBR=0xe7,
    NvBufferKind_C64_2CBA=0xe8,
    NvBufferKind_C64_2CRA=0xe9,
    NvBufferKind_C64_2BRA=0xea,
    NvBufferKind_C64_MS2_2C=0xeb,
    NvBufferKind_C64_MS2_2CBR=0xeC,
    NvBufferKind_C64_MS4_2C=0xed,
    NvBufferKind_C64_MS4_2CBR=0xee,
    NvBufferKind_C64_MS4_2CBA=0xef,
    NvBufferKind_C64_MS4_2CRA=0xf0,
    NvBufferKind_C64_MS4_2BRA=0xf1,
    NvBufferKind_C64_MS8_MS16_2C=0xf2,
    NvBufferKind_C64_MS8_MS16_2CRA=0xf3,
    NvBufferKind_C128_2C=0xf4,
    NvBufferKind_C128_2CR=0xf5,
    NvBufferKind_C128_MS2_2C=0xf6,
    NvBufferKind_C128_MS2_2CR=0xf7,
    NvBufferKind_C128_MS4_2C=0xf8,
    NvBufferKind_C128_MS4_2CR=0xf9,
    NvBufferKind_C128_MS8_MS16_2C=0xfa,
    NvBufferKind_C128_MS8_MS16_2CR=0xfb,
    NvBufferKind_X8C24=0xfC,
    NvBufferKind_PitchNoSwizzle=0xfd,
    NvBufferKind_Generic_16BX2=0xfe,
    NvBufferKind_Invalid=0xff,
} NvBufferKind;

typedef struct {
    u32   fd;
    u32   size;
    void* ptr;
    NvBufferKind kind;
    bool  has_init;
} NvBuffer;

Result nvbufInit(void);
void   nvbufExit(void);

Result nvbufCreate(NvBuffer* m, size_t size, u32 align, NvBufferKind kind);
Result nvbufCreateRw(NvBuffer* m, size_t size, u32 align, NvBufferKind kind);
void   nvbufFree(NvBuffer* m);

void*  nvbufGetAddr(NvBuffer* m);
