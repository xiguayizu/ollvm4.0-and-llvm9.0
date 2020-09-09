// REQUIRES: target-is-powerpc64le
// RUN: %clang_builtins %s %librt -o %t && %run %t
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include "DD.h"

struct testVector { double xhi; double xlo; int64_t result; };

#define INFINITY __builtin_inf()
#define HUGE 0x1.fffffffffffffp1023
#define QNAN __builtin_nan("")

const struct testVector testCases[] = {
// Edge cases
// {	HUGE,					0.0,					INT64_MAX	},
// {	INFINITY,				0.0,					INT64_MAX	},
// {  -HUGE,					0.0,					INT64_MIN	},
// {  -INFINITY,				0.0,					INT64_MIN	},
// {	QNAN,					0.0,					INT64_MIN	},

// Exact cases:
{   0.0,					0.0,					0LL			},
{  -0.0,					0.0,					0LL			},
{   1.0,					0.0,					1LL			},
{  -1.0,					0.0,				   -1LL			},
{   2.0,					0.0,					2LL			},
{  -2.0,					0.0,				   -2LL			},
{   3.0,					0.0,					3LL			},
{  -3.0,					0.0,				   -3LL			},
{   4.0,					0.0,					4LL			},
{  -4.0,					0.0,				   -4LL			},
{   5.0,					0.0,					5LL			},
{  -5.0,					0.0,				   -5LL			},
{   6.0,					0.0,					6LL			},
{  -6.0,					0.0,				   -6LL			},
{   7.0,					0.0,					7LL			},
{  -7.0,					0.0,				   -7LL			},
{   8.0,					0.0,					8LL			},
{  -8.0,					0.0,				   -8LL			},
{   9.0,					0.0,					9LL			},
{  -9.0,					0.0,				   -9LL			},

// Near integer cases:
{	1.0,				   -0x1.0p-54,				0LL			},
{	1.0,				   -0.0,					1LL			},
{	1.0,					0x1.0p-54,				1LL			},
{	0x1.0000000000001p0,   -0x1.0p-54,				1LL			},
{	0x1.0000000000001p0,   -0.0,					1LL			},
{	0x1.0000000000001p0,    0.0,					1LL			},
{	0x1.0000000000001p0,    0x1.0p-54,				1LL			},
{  -1.0,				    0x1.0p-54,				0LL			},
{  -1.0,				    0.0,				   -1LL			},
{  -1.0,				    0.0,				   -1LL			},
{  -1.0,				   -0x1.0p-54,			   -1LL			},
{  -0x1.0000000000001p0,    0x1.0p-54,			   -1LL			},
{  -0x1.0000000000001p0,   -0.0,				   -1LL			},
{  -0x1.0000000000001p0,   -0x1.0p-54,			   -1LL			},

// Close to 32-bit overflow boundaries:
{   0x1.fffffffcp30,	   -0x1.0p-24,				INT64_C(0x7ffffffe)		},
{   0x1.fffffffcp30,		0.0,					INT64_C(0x7fffffff)		},
{   0x1.fffffffcp30,		0x1.0p-24,				INT64_C(0x7fffffff)		},
{   0x1.fffffffffffffp30,  -0x1.0p-24,				INT64_C(0x7fffffff)		},
{   0x1.fffffffffffffp30,   0.0,					INT64_C(0x7fffffff)		},
{   0x1.fffffffffffffp30,   0x1.fffffffffffffp-24,	INT64_C(0x7fffffff)		},
{   0x1.0p31,			   -0x1.fffffffffffffp-24,	INT64_C(0x7fffffff)		},
{   0x1.0p31,			    0.0,					INT64_C(0x80000000)		},
{   0x1.0p31,			    0x1.fffffffffffffp-24,	INT64_C(0x80000000)		},
{   0x1.0000000000001p31,  -0x1.fffffffffffffp-24,	INT64_C(0x80000000)		},
{   0x1.0000000000001p31,	0.0,					INT64_C(0x80000000)		},
{   0x1.0000000000001p31,	0x1.fffffffffffffp-24,	INT64_C(0x80000000)		},
{	0x1.00000002p31,	   -0x1.fffffffffffffp-24,	INT64_C(0x80000000)		},
{	0x1.00000002p31,	    0.0,					INT64_C(0x80000001)		},
{	0x1.00000002p31,	    0x1.fffffffffffffp-24,	INT64_C(0x80000001)		},

{   0x1.fffffffep31,	   -0x1.0p-24,				INT64_C(0xfffffffe)		},
{   0x1.fffffffep31,		0.0,					INT64_C(0xffffffff)		},
{   0x1.fffffffep31,		0x1.0p-24,				INT64_C(0xffffffff)		},
{   0x1.fffffffffffffp31,  -0x1.0p-24,				INT64_C(0xffffffff)		},
{   0x1.fffffffffffffp31,   0.0,					INT64_C(0xffffffff)		},
{   0x1.fffffffffffffp31,   0x1.fffffffffffffp-24,	INT64_C(0xffffffff)		},
{   0x1.0p32,			   -0x1.fffffffffffffp-24,	INT64_C(0xffffffff)		},
{   0x1.0p32,			    0.0,					INT64_C(0x100000000)	},
{   0x1.0p32,			    0x1.fffffffffffffp-24,	INT64_C(0x100000000)	},
{   0x1.0000000000001p32,  -0x1.fffffffffffffp-24,	INT64_C(0x100000000)	},
{   0x1.0000000000001p32,	0.0,					INT64_C(0x100000000)	},
{   0x1.0000000000001p32,	0x1.fffffffffffffp-24,	INT64_C(0x100000000)	},
{	0x1.00000001p32,	   -0x1.fffffffffffffp-24,	INT64_C(0x100000000)	},
{	0x1.00000001p32,	    0.0,					INT64_C(0x100000001)	},
{	0x1.00000001p32,	    0x1.fffffffffffffp-24,	INT64_C(0x100000001)	},

{  -0x1.fffffffcp30,	    0x1.0p-24,				INT64_C(0xffffffff80000002)	},
{  -0x1.fffffffcp30,		0.0,					INT64_C(0xffffffff80000001)	},
{  -0x1.fffffffcp30,	   -0x1.0p-24,				INT64_C(0xffffffff80000001)	},
{  -0x1.fffffffffffffp30,   0x1.0p-24,				INT64_C(0xffffffff80000001)	},
{  -0x1.fffffffffffffp30,   0.0,					INT64_C(0xffffffff80000001)	},
{  -0x1.fffffffffffffp30,  -0x1.fffffffffffffp-24,	INT64_C(0xffffffff80000001)	},
{  -0x1.0p31,			    0x1.fffffffffffffp-24,	INT64_C(0xffffffff80000001)	},
{  -0x1.0p31,			    0.0,					INT64_C(0xffffffff80000000)	},
{  -0x1.0p31,			   -0x1.fffffffffffffp-24,	INT64_C(0xffffffff80000000)	},
{  -0x1.0000000000001p31,   0x1.fffffffffffffp-24,	INT64_C(0xffffffff80000000)	},
{  -0x1.0000000000001p31,	0.0,					INT64_C(0xffffffff80000000)	},
{  -0x1.0000000000001p31,  -0x1.fffffffffffffp-24,	INT64_C(0xffffffff80000000)	},
{  -0x1.00000002p31,	    0x1.fffffffffffffp-24,	INT64_C(0xffffffff80000000)	},
{  -0x1.00000002p31,	    0.0,					INT64_C(0xffffffff7fffffff)	},
{  -0x1.00000002p31,	   -0x1.fffffffffffffp-24,	INT64_C(0xffffffff7fffffff)	},

{  -0x1.fffffffep31,	    0x1.0p-24,				INT64_C(0xffffffff00000002)	},
{  -0x1.fffffffep31,		0.0,					INT64_C(0xffffffff00000001)	},
{  -0x1.fffffffep31,	   -0x1.0p-24,				INT64_C(0xffffffff00000001)	},
{  -0x1.fffffffffffffp31,   0x1.0p-24,				INT64_C(0xffffffff00000001)	},
{  -0x1.fffffffffffffp31,   0.0,					INT64_C(0xffffffff00000001)	},
{  -0x1.fffffffffffffp31,  -0x1.fffffffffffffp-24,	INT64_C(0xffffffff00000001)	},
{  -0x1.0p32,			    0x1.fffffffffffffp-24,	INT64_C(0xffffffff00000001)	},
{  -0x1.0p32,			    0.0,					INT64_C(0xffffffff00000000)	},
{  -0x1.0p32,			   -0x1.fffffffffffffp-24,	INT64_C(0xffffffff00000000)	},
{  -0x1.0000000000001p32,   0x1.fffffffffffffp-24,	INT64_C(0xffffffff00000000)	},
{  -0x1.0000000000001p32,	0.0,					INT64_C(0xffffffff00000000)	},
{  -0x1.0000000000001p32,  -0x1.fffffffffffffp-24,	INT64_C(0xffffffff00000000)	},
{  -0x1.00000001p32,	    0x1.fffffffffffffp-24,	INT64_C(0xffffffff00000000)	},
{  -0x1.00000001p32,	    0.0,					INT64_C(0xfffffffeffffffff)	},
{  -0x1.00000001p32,	   -0x1.fffffffffffffp-24,	INT64_C(0xfffffffeffffffff)	},

// Randomly generated in-range values:
{0x1.00ffc00ffff00p+11, 0x1.fe0007fffff00p-45, INT64_C(0x0000000000000807)},
{-0x1.00001fffff800p+38, -0x1.fffffffe00000p-36, INT64_C(0xffffffbffff80001)},
{0x1.000003fffc002p+48, -0x1.0000000000000p-57, INT64_C(0x0001000003fffc00)},
{-0x1.000003ffffffep+3, 0x1.ffe0080000000p-81, INT64_C(0xfffffffffffffff8)},
{0x1.0800000000000p+21, -0x1.0000000000000p-75, INT64_C(0x000000000020ffff)},
{-0x1.007fffffe0000p+61, 0x0.0000000000000p+0, INT64_C(0xdff0000004000000)},
{0x1.3fe0000100000p+33, -0x1.0000000000000p-40, INT64_C(0x000000027fc00001)},
{-0x1.0001fff800000p+1, -0x1.ffffff0000ffep-53, INT64_C(0xfffffffffffffffe)},
{0x1.0000800000000p+54, -0x1.ffffffe400000p-9, INT64_C(0x0040001fffffffff)},
{-0x1.007fffffffc00p+15, -0x1.fffffc0000000p-56, INT64_C(0xffffffffffff7fc1)},
{0x1.0080000000000p+13, -0x1.0000000000000p-60, INT64_C(0x000000000000200f)},
{-0x1.00f3ffffff000p+56, -0x1.fff8000000000p-12, INT64_C(0xfeff0c0000010000)},
{0x1.3dfffffffc000p+47, 0x1.ff000003ffe00p-14, INT64_C(0x00009efffffffe00)},
{-0x1.0000001ffff80p+12, -0x1.fffffdfffff8ep-42, INT64_C(0xfffffffffffff000)},
{0x1.0000000000000p+4, -0x1.0000000000000p-66, INT64_C(0x000000000000000f)},
{-0x1.001fffffffe00p+39, 0x0.0000000000000p+0, INT64_C(0xffffff7ff0000001)},
{0x1.00000007ff800p+5, 0x1.ffff800000000p-83, INT64_C(0x0000000000000020)},
{-0x1.000ffffff8000p+57, -0x1.ffffffffffc00p+2, INT64_C(0xfdffe000000ffff9)},
{0x1.007fbfffffcf0p+43, 0x1.ffff803ffe000p-12, INT64_C(0x00000803fdfffffe)},
{-0x1.01ffffffc0004p+24, 0x1.fffc100000000p-37, INT64_C(0xfffffffffefe0001)},
{0x1.0000001000000p+19, -0x1.ffffff0000800p-45, INT64_C(0x0000000000080000)},
{-0x1.00000003ff800p+25, -0x1.ffffe00000000p-61, INT64_C(0xfffffffffe000000)},
{0x1.0000001000000p+23, -0x1.fffffff804000p-44, INT64_C(0x0000000000800000)},
{-0x1.0008000000000p+20, 0x1.0000000000000p-48, INT64_C(0xffffffffffefff81)},
{0x1.0000183ffffc0p+60, 0x1.fff07fcfffffcp+6, INT64_C(0x10000183ffffc07f)},
{-0x1.0001000000000p+42, 0x1.fffffff800400p-21, INT64_C(0xfffffbfffc000001)},
{0x1.0000800000000p+11, -0x1.fffff80100000p-62, INT64_C(0x0000000000000800)},
{-0x1.1fffffff00000p+28, -0x1.fffffff000000p-49, INT64_C(0xffffffffee000001)},
{0x1.fffffc0000100p+59, -0x1.fffe000040000p-12, INT64_C(0x0fffffe000007fff)},
{-0x1.0000800000000p+39, 0x1.c000fffffffd0p-18, INT64_C(0xffffff7fffc00001)},
{0x1.3ff8007ffffc0p+61, 0x1.e0007ff000000p-5, INT64_C(0x27ff000fffff8000)},
{-0x1.ffffffe000000p+13, 0x1.ff80000020000p-43, INT64_C(0xffffffffffffc001)},
{0x1.7fffe00800000p+35, -0x1.0000000000000p-70, INT64_C(0x0000000bffff003f)},
{-0x1.0000400000000p+62, 0x1.0000000000000p-29, INT64_C(0xbffff00000000001)},
{0x1.4000000000000p+31, -0x1.ffffffff00020p-27, INT64_C(0x000000009fffffff)},
{-0x1.0000010000000p+29, 0x1.8000000000020p-29, INT64_C(0xffffffffdfffffe1)},
{0x1.7fffffffc0000p+45, 0x1.fffc000000000p-25, INT64_C(0x00002ffffffff800)},
{-0x1.0000001fe0000p+46, -0x1.fffffc0001f00p-15, INT64_C(0xffffbffffff80800)},
{0x1.0000004000000p+54, -0x1.0000000000000p-4, INT64_C(0x004000000fffffff)},
{-0x1.8000000000000p+48, 0x1.ffe7ffc001000p-17, INT64_C(0xfffe800000000001)},
{0x1.007fc00007800p+34, 0x1.e0000f80001e0p-24, INT64_C(0x0000000401ff0000)},
{-0x1.3fffff0000000p+8, -0x1.fffffe0000000p-55, INT64_C(0xfffffffffffffec1)},
{0x1.0000200000000p+14, -0x1.0000000000000p-91, INT64_C(0x0000000000004000)},
{-0x1.00000fffffff8p+1, -0x1.fffffffc00000p-58, INT64_C(0xfffffffffffffffe)},
{0x1.001fffc000400p+34, -0x1.e000000001000p-31, INT64_C(0x00000004007fff00)},
{-0x1.0200000000000p+41, 0x1.0000000000000p-62, INT64_C(0xfffffdfc00000001)},
{0x1.03ffffffe0000p+55, 0x1.ff80000000000p-34, INT64_C(0x0081fffffff00000)},
{-0x1.0010000000000p+45, 0x1.0000000000000p-32, INT64_C(0xffffdffe00000001)},
{0x1.0000008000000p+31, -0x1.fff0000000100p-28, INT64_C(0x000000008000003f)},
{-0x1.0000c00400000p+26, 0x1.ff80800000000p-55, INT64_C(0xfffffffffbfffd00)},
{0x1.0000007fff000p+48, 0x1.ffffff8000000p-27, INT64_C(0x00010000007fff00)},
{-0x1.3ffffff800200p+60, 0x1.0000000000000p-17, INT64_C(0xec0000007ffe0001)},
{0x1.0000200000000p+8, -0x1.ffffffffffc40p-51, INT64_C(0x0000000000000100)},
{-0x1.007ffffffff80p+54, -0x1.fffffffe00000p-20, INT64_C(0xffbfe00000000200)},
{0x1.00003ffffff00p+25, 0x1.ffc003ffffe00p-30, INT64_C(0x000000000200007f)},
{-0x1.0200000000000p+26, 0x1.c000000000008p-30, INT64_C(0xfffffffffbf80001)},
{0x1.1fffffc000000p+8, 0x1.ffffffffffff0p-49, INT64_C(0x000000000000011f)},
{-0x1.007fc00000800p+2, 0x1.fffff03fff000p-58, INT64_C(0xfffffffffffffffc)},
{0x1.00007fffff000p+31, 0x1.ffffffff00000p-41, INT64_C(0x0000000080003fff)},
{-0x1.0000003ffff80p+54, -0x1.fffffefff8000p-14, INT64_C(0xffbffffff0000200)},
{0x1.00007ffc00000p+46, 0x1.ffffe00000000p-23, INT64_C(0x000040001fff0000)},
{-0x1.3fffffc004000p+8, 0x1.ffffe00010000p-56, INT64_C(0xfffffffffffffec1)},
{0x1.01fffffffe000p+49, 0x1.fffc000000000p-39, INT64_C(0x000203fffffffc00)},
{-0x1.07ffffff80000p+54, -0x1.8007ffffc0000p-17, INT64_C(0xffbe000000200000)},
{0x1.00003ff810000p+56, -0x1.fffffffc00800p-8, INT64_C(0x0100003ff80fffff)},
{-0x1.01ffffff00004p+25, 0x1.0000000000000p-65, INT64_C(0xfffffffffdfc0001)},
{0x1.000000ffffff8p+11, 0x1.ffe0000000000p-61, INT64_C(0x0000000000000800)},
{-0x1.001f03f07ff00p+10, -0x1.ffffff8000000p-63, INT64_C(0xfffffffffffffc00)},
{0x1.00003fffffffcp+9, 0x1.ffe0000700000p-64, INT64_C(0x0000000000000200)},
{-0x1.0000100000000p+27, 0x1.0000000000000p-55, INT64_C(0xfffffffff7ffff81)},
{0x1.0000020000000p+62, -0x1.0000000000000p-30, INT64_C(0x4000007fffffffff)},
{-0x1.00001fffcffc0p+52, 0x1.fffe000000004p-3, INT64_C(0xffeffffe00030041)},
{0x1.03fffff800000p+47, 0x1.fffffe0000000p-21, INT64_C(0x000081fffffc0000)},
{-0x1.000fff8000000p+0, -0x1.fffffe0000000p-62, INT64_C(0xffffffffffffffff)},
{0x1.0003fc0000000p+57, 0x1.ffff80ffffc00p+0, INT64_C(0x020007f800000001)},
{-0x1.0300000001f00p+61, -0x1.fffffff800000p-15, INT64_C(0xdf9fffffffc20000)},
{0x1.fffff1ff80000p+43, 0x1.ffffc000fe000p-12, INT64_C(0x00000fffff8ffc00)},
{-0x1.000001d000000p+33, 0x1.ff80000200000p-22, INT64_C(0xfffffffdfffffc61)},
{0x1.000007fffffc0p+24, 0x1.fc0003fc00000p-36, INT64_C(0x0000000001000007)},
{-0x1.0000004000000p+23, 0x1.fff0000004000p-44, INT64_C(0xffffffffff800000)},
{0x1.0fc007c004000p+9, -0x1.fffe100000000p-55, INT64_C(0x000000000000021f)},
{-0x1.00007fffffe00p+13, -0x1.ffffffc003f00p-48, INT64_C(0xffffffffffffe000)},
{0x1.0080000000000p+24, -0x1.0000000000000p-34, INT64_C(0x0000000001007fff)},
{-0x1.00000ffffff80p+60, -0x1.ffffff0007ff8p+4, INT64_C(0xefffff0000007fe1)},
{0x1.01e0000000002p+44, -0x1.fffffffffc200p-15, INT64_C(0x0000101e00000000)},
{-0x1.0000080000000p+35, 0x1.0000000000000p-70, INT64_C(0xfffffff7ffffc001)},
{0x1.000000f1fe001p+23, -0x1.0000000000000p-60, INT64_C(0x0000000000800000)},
{-0x1.00003fffffff0p+40, -0x1.fc00000000000p-37, INT64_C(0xfffffeffffc00001)},
{0x1.00001ffff0000p+16, 0x1.ffff80001f000p-41, INT64_C(0x0000000000010000)},
{-0x1.0000100000000p+12, 0x1.0000000000000p-93, INT64_C(0xfffffffffffff000)},
{0x1.0038000800000p+41, -0x1.fffffe0000080p-19, INT64_C(0x0000020070000fff)},
{-0x1.00003fe008000p+14, 0x1.fffdff0000080p-45, INT64_C(0xffffffffffffc000)},
{0x1.0000100000000p+42, -0x1.0000000000000p-52, INT64_C(0x00000400003fffff)},
{-0x1.00003ff002010p+17, 0x1.0000020000000p-48, INT64_C(0xfffffffffffe0000)},
{0x1.00ffffffc0000p+8, 0x1.fffffe00003f0p-47, INT64_C(0x0000000000000100)},
{-0x1.1fffffffff020p+39, 0x1.ffff000400000p-36, INT64_C(0xffffff7000000001)},
{0x1.0200000000000p+33, -0x1.0000000000000p-20, INT64_C(0x0000000203ffffff)},
{-0x1.0000700000000p+0, -0x1.ffffffe000000p-71, INT64_C(0xffffffffffffffff)},
{0x1.00000ffffffd0p+33, -0x1.ffffff8200000p-33, INT64_C(0x0000000200001fff)},
{-0x1.00000c0000004p+59, 0x1.ff80000800000p-9, INT64_C(0xf7ffff9ffffffe01)},
{0x1.1ffff80000040p+5, -0x1.0000000000000p-85, INT64_C(0x0000000000000023)},
{-0x1.0ffffff9ffff0p+58, -0x1.f800008200000p-12, INT64_C(0xfbc0000018000400)},
{0x1.000000ffffff8p+13, 0x1.ff0000007ffc0p-46, INT64_C(0x0000000000002000)},
{-0x1.0000008000000p+6, 0x1.fffffc0000008p-50, INT64_C(0xffffffffffffffc0)},
{0x1.0000200000000p+25, -0x1.fffffff804000p-42, INT64_C(0x000000000200003f)},
{-0x1.0000080000000p+61, 0x1.0000000000000p-34, INT64_C(0xdfffff0000000001)},
{0x1.03ffff0000010p+42, -0x1.fffc010000000p-34, INT64_C(0x0000040ffffc0000)},
{-0x1.7ffffffc00000p+38, -0x1.fff80000fc000p-23, INT64_C(0xffffffa000000100)},
{0x1.0010000000000p+23, -0x1.ffffffffc4000p-44, INT64_C(0x00000000008007ff)},
{-0x1.000007fffc004p+7, 0x1.8000004000000p-52, INT64_C(0xffffffffffffff80)},
{0x1.7fe000001ff00p+11, 0x1.f000000000000p-90, INT64_C(0x0000000000000bff)},
{-0x1.0ffffff000000p+0, -0x1.fffffff000000p-70, INT64_C(0xffffffffffffffff)},
{0x1.0000010000000p+45, -0x1.ffffffffe4000p-17, INT64_C(0x00002000001fffff)},
{-0x1.0000020000000p+50, 0x1.ff80000100000p-23, INT64_C(0xfffbfffff8000001)},
{0x1.1ffffffff8000p+8, 0x1.fe001ffffffe0p-48, INT64_C(0x000000000000011f)},
{-0x1.0000000fffe00p+44, -0x1.3fffff87fc000p-16, INT64_C(0xffffefffffff0002)},
{0x1.0000000800000p+3, -0x1.0000000000000p-102, INT64_C(0x0000000000000008)},
{-0x1.00fffffff8000p+3, -0x1.fffe000000000p-71, INT64_C(0xfffffffffffffff8)},
{0x1.0007ffffffff0p+60, 0x1.fffffc0000000p-23, INT64_C(0x10007ffffffff000)},
{-0x1.0003800000080p+32, 0x1.0000000000000p-73, INT64_C(0xfffffffefffc8000)},
{0x1.000001fffff80p+14, 0x1.ff00000000000p-70, INT64_C(0x0000000000004000)},
{-0x1.000007ffffe00p+52, 0x1.fe0c000004000p-6, INT64_C(0xffefffff80000201)},
{0x1.00000003f0000p+56, 0x1.ffffffe000000p-22, INT64_C(0x0100000003f00000)},
{-0x1.0100000000000p+5, 0x1.fffffff000080p-55, INT64_C(0xffffffffffffffe0)},
{0x1.007fffffffc00p+16, 0x1.fffffe0000000p-66, INT64_C(0x000000000001007f)},
{-0x1.007ffffffc000p+11, -0x1.ffffff8000000p-56, INT64_C(0xfffffffffffff7fd)},
{0x1.0003fffffffe0p+61, 0x1.fffffff000780p+1, INT64_C(0x20007fffffffc003)},
{-0x1.1ffff00800000p+3, 0x1.0000000000000p-94, INT64_C(0xfffffffffffffff8)},
{0x1.000003fff8000p+9, 0x1.ffff00000003cp-46, INT64_C(0x0000000000000200)},
{-0x1.000001ffff020p+48, 0x1.fff0000200000p-22, INT64_C(0xfffefffffe0000ff)},
{0x1.00ffe00000000p+43, 0x1.fe00000000000p-17, INT64_C(0x00000807ff000000)},
{-0x1.0000100000000p+29, 0x1.ffff800010000p-40, INT64_C(0xffffffffdffffe01)},
{0x1.0100000000000p+52, -0x1.0000000000000p-35, INT64_C(0x00100fffffffffff)},
{-0x1.000003fff8001p+19, 0x1.0000000000000p-64, INT64_C(0xfffffffffff80000)},
{0x1.00f8000200000p+40, -0x1.ff80000100000p-33, INT64_C(0x00000100f80001ff)},
{-0x1.003ffffffe000p+23, -0x1.f007fffffc000p-36, INT64_C(0xffffffffff7fe001)},
{0x1.0000080000000p+55, -0x1.0000000000000p-50, INT64_C(0x00800003ffffffff)},
{-0x1.0200000000000p+52, 0x1.0000000000000p-18, INT64_C(0xffefe00000000001)},
{0x1.03fffffc00000p+6, 0x1.fe0000c000000p-54, INT64_C(0x0000000000000040)},
{-0x1.7ff0000040000p+38, 0x1.0000000000000p-37, INT64_C(0xffffffa003fffff1)},
{0x1.0000018000010p+16, -0x1.fffffe0200000p-58, INT64_C(0x0000000000010000)},
{-0x1.001ffffffff00p+30, -0x1.ffffffe000000p-25, INT64_C(0xffffffffbff80001)},
{0x1.07fc000007ffep+52, 0x1.8000000010000p-17, INT64_C(0x00107fc000007ffe)},
{-0x1.0007fffffff00p+11, -0x1.fffe000000000p-79, INT64_C(0xfffffffffffff800)},
{0x1.0000003fffffcp+31, 0x1.fffff8007fff0p-26, INT64_C(0x000000008000001f)},
{-0x1.0000003f000f8p+4, -0x1.fffc03fffe000p-54, INT64_C(0xfffffffffffffff0)},
{0x1.00000007ffe00p+2, 0x1.ffffe000007f8p-54, INT64_C(0x0000000000000004)},
{-0x1.00001fffc0000p+12, -0x1.fffffffffe1f0p-45, INT64_C(0xfffffffffffff000)},
{0x1.00001fffff801p+23, -0x1.80003f0000040p-36, INT64_C(0x000000000080000f)},
{-0x1.00001ffffe000p+23, -0x1.f00001f000000p-41, INT64_C(0xffffffffff7ffff1)},
{0x1.0000007007f80p+38, 0x1.c00ffffffe000p-27, INT64_C(0x0000004000001c01)},
{-0x1.0000010000000p+26, 0x1.0000000000000p-79, INT64_C(0xfffffffffbfffffd)},
{0x1.0000002000000p+7, -0x1.0000000000000p-98, INT64_C(0x0000000000000080)},
{-0x1.00001ffe00010p+13, 0x1.0000000000000p-69, INT64_C(0xffffffffffffe000)},
{0x1.0fe0000008000p+30, -0x1.c00007fffc100p-31, INT64_C(0x0000000043f80000)},
{-0x1.0000001fc0000p+0, -0x1.ffc003ffff000p-65, INT64_C(0xffffffffffffffff)},
{0x1.00007e3fffff0p+44, 0x1.ffff000000000p-28, INT64_C(0x0000100007e3ffff)},
{-0x1.ffffff0002000p+56, 0x1.ffffc00000040p+2, INT64_C(0xfe000000fffe0008)},
{0x1.0000ffffffc00p+21, 0x1.ffffffffffe00p-41, INT64_C(0x000000000020001f)},
{-0x1.07ffff0000000p+35, -0x1.ffff0003ffffep-19, INT64_C(0xfffffff7c0000800)},
{0x1.0000040000000p+18, -0x1.0000000000000p-74, INT64_C(0x0000000000040000)},
{-0x1.0003ffffffe00p+55, -0x1.ffff800000000p-13, INT64_C(0xff7ffe0000001000)},
{0x1.001fc00000300p+30, -0x1.ffff000040000p-41, INT64_C(0x000000004007f000)},
{-0x1.07fffffc01000p+11, 0x1.ffffffe002000p-46, INT64_C(0xfffffffffffff7c1)},
{0x1.03ffff81f8001p+55, -0x1.f800800000000p-22, INT64_C(0x0081ffffc0fc0007)},
{-0x1.0040000000000p+4, 0x1.fffffffffffe0p-54, INT64_C(0xfffffffffffffff0)},
{0x1.0008000000000p+47, -0x1.ffffffff01000p-18, INT64_C(0x00008003ffffffff)},
{-0x1.0000010000000p+23, 0x1.0000000000000p-82, INT64_C(0xffffffffff800000)},
{0x1.0000007fffff4p+62, -0x1.f800003ffffe0p+4, INT64_C(0x4000001fffffcfe0)},
{-0x1.0000001ff8000p+12, -0x1.8003fffff0c00p-51, INT64_C(0xfffffffffffff000)},
{0x1.00000007ffff8p+62, 0x1.ffffffffff000p+7, INT64_C(0x40000001ffffe0ff)},
{-0x1.03ffffffffff8p+5, -0x1.fffffffc00000p-70, INT64_C(0xffffffffffffffe0)},
{0x1.0003f00000040p+58, -0x1.fffffe0800000p-18, INT64_C(0x04000fc000000fff)},
{-0x1.07fffffc00100p+55, 0x1.0000000000000p-27, INT64_C(0xff7c000001fff801)},
{0x1.fffffe0000000p+57, 0x1.ffffffff00000p-16, INT64_C(0x03fffffc00000000)},
{-0x1.0000000ffffe0p+53, -0x1.fffffff000000p-16, INT64_C(0xffdffffffe000040)},
{0x1.0001fffff8000p-1, 0x1.fffffff800000p-69, INT64_C(0x0000000000000000)},
{-0x1.001fffffff000p+45, -0x1.fffffc0000000p-13, INT64_C(0xffffdffc00000020)},
{0x1.000f00007fff8p+2, 0x1.ffffff8000000p-60, INT64_C(0x0000000000000004)},
{-0x1.0080000000000p+46, 0x1.0000000000000p-37, INT64_C(0xffffbfe000000001)},
{0x1.7fffffffffffep+34, 0x0.0000000000000p+0, INT64_C(0x00000005ffffffff)},
{-0x1.00000007ffffep+2, -0x1.ff003f8000380p-53, INT64_C(0xfffffffffffffffc)},
{0x1.0067ffffe0000p+19, 0x1.fffffff800000p-52, INT64_C(0x000000000008033f)},
{-0x1.1ff1000000000p+12, 0x1.fff0000100000p-61, INT64_C(0xffffffffffffee01)},
{0x1.0000100000000p+46, -0x1.0000000000000p-33, INT64_C(0x0000400003ffffff)},
{-0x1.0000ffe000080p+14, 0x1.fffffe0002000p-50, INT64_C(0xffffffffffffc000)},
{0x1.0000100000000p+22, -0x1.ffffff0020000p-36, INT64_C(0x0000000000400003)},
{-0x1.001fffff01f00p+22, -0x1.fffffff800000p-44, INT64_C(0xffffffffffbff801)},
{0x1.0000ffc000000p+35, 0x1.ff003fffffe00p-27, INT64_C(0x000000080007fe00)},
{-0x1.07c0000001ff8p+54, -0x1.fffff00000000p-26, INT64_C(0xffbe0fffffff8020)},
{0x1.0000400000000p+12, -0x1.8000000400000p-60, INT64_C(0x0000000000001000)},
{-0x1.0000000300000p+30, 0x0.0000000000000p+0, INT64_C(0xffffffffc0000000)},
{0x1.00ff000008000p+29, -0x1.fffff02000000p-38, INT64_C(0x00000000201fe000)},
{-0x1.000fffff80000p+29, -0x1.3ffffffc00000p-46, INT64_C(0xffffffffdffe0001)},
{0x1.007f8000007fcp+9, 0x1.fffffe0000000p-58, INT64_C(0x0000000000000200)},
{-0x1.1ffffffffc004p+23, 0x1.0000000000000p-75, INT64_C(0xffffffffff700001)},
{0x1.0000001f00010p+29, -0x1.0000000000000p-45, INT64_C(0x0000000020000003)},
{-0x1.0007fffffe000p+5, -0x1.fffff80000300p-56, INT64_C(0xffffffffffffffe0)},
{0x1.00003f0000800p+41, -0x1.ffffff8000080p-13, INT64_C(0x00000200007e0000)},
{-0x1.000001ffffff0p+0, -0x1.fffc000000000p-80, INT64_C(0xffffffffffffffff)},
{0x1.00007ffc00080p+24, -0x1.ffffffc000100p-30, INT64_C(0x000000000100007f)},
{-0x1.0ffe000100000p+38, 0x1.fff8200000000p-48, INT64_C(0xffffffbc007fffc1)},
{0x1.fffffff000008p+5, -0x1.8001000000000p-67, INT64_C(0x000000000000003f)},
{-0x1.0000000800000p+32, 0x1.ffffc00200000p-24, INT64_C(0xfffffffefffffff9)},
{0x1.7fffc00000000p+58, 0x1.ffffe00000000p-28, INT64_C(0x05ffff0000000000)},
{-0x1.00fffffffff80p+40, 0x0.0000000000000p+0, INT64_C(0xfffffeff00000001)},
{0x1.0010000000000p+28, -0x1.0000000000000p-61, INT64_C(0x000000001000ffff)},
{-0x1.00ffffe07fc00p+30, -0x1.fffffc3000000p-24, INT64_C(0xffffffffbfc00008)},
{0x1.000ffe0fffffep+38, 0x1.ffffc00000000p-49, INT64_C(0x0000004003ff83ff)},
{-0x1.0000003ff0000p+24, -0x1.fffffff080000p-42, INT64_C(0xffffffffff000000)},
{0x1.0000e00003ff8p+34, 0x1.ffffff8ffc000p-33, INT64_C(0x0000000400038000)},
{-0x1.0080000000000p+47, 0x1.0000000000000p-58, INT64_C(0xffff7fc000000001)},
{0x1.0008000000000p+19, 0x0.0000000000000p+0, INT64_C(0x0000000000080040)},
{-0x1.0001fe0000002p+49, 0x1.fff0000080008p-7, INT64_C(0xfffdfffc04000000)},
{0x1.03c03c0000020p+39, -0x1.0000000000000p-40, INT64_C(0x00000081e01e0000)},
{-0x1.0001fff9c0008p+0, 0x1.ffffff0002000p-56, INT64_C(0xffffffffffffffff)},
{0x1.ffffffff80000p+49, 0x1.fffffffffe000p-17, INT64_C(0x0003ffffffff0000)},
{-0x1.0000fffc00000p+3, -0x1.1ffffe0000000p-60, INT64_C(0xfffffffffffffff8)},
{0x1.0000020000000p+56, -0x1.0000000000000p-40, INT64_C(0x01000001ffffffff)},
{-0x1.007fffffffffcp+41, -0x1.fffefffffff80p-19, INT64_C(0xfffffdff00000001)},
{0x1.007ffffffffc0p+15, 0x1.ffffff8000000p-52, INT64_C(0x000000000000803f)},
{-0x1.ffffff0000000p+60, -0x1.fffffffff0000p-2, INT64_C(0xe000001000000000)},
{0x1.00000003f81ffp+0, 0x1.ffc0000000000p-82, INT64_C(0x0000000000000001)},
{-0x1.0000001ff8039p+45, 0x1.ffff800080000p-27, INT64_C(0xffffdffffffc0100)},
{0x1.0008000000000p+32, -0x1.f000000000080p-28, INT64_C(0x000000010007ffff)},
{-0x1.00c1fffc00000p+21, -0x1.ffff800000000p-67, INT64_C(0xffffffffffdfe7c1)},
{0x1.1fe0000080000p+15, -0x1.fffffe0000008p-39, INT64_C(0x0000000000008ff0)},
{-0x1.01ffffff00000p+55, -0x1.ffffffe000000p-22, INT64_C(0xff7f000000800000)},
{0x1.0000003ffffe0p+45, 0x0.0000000000000p+0, INT64_C(0x000020000007ffff)},
{-0x1.003ffffe00000p+21, 0x0.0000000000000p+0, INT64_C(0xffffffffffdff801)},
{0x1.00007fc000000p+54, 0x1.fffffff000000p-3, INT64_C(0x0040001ff0000000)},
{-0x1.0000000000000p+58, 0x1.0000000000000p-14, INT64_C(0xfc00000000000001)},
{0x1.0400000000000p+23, -0x1.0000000000000p-39, INT64_C(0x000000000081ffff)},
{-0x1.000003fffff00p+32, -0x1.ffc00003c0000p-39, INT64_C(0xfffffffefffffc01)},
{0x1.7ffffffffffe0p+9, 0x0.0000000000000p+0, INT64_C(0x00000000000002ff)},
{-0x1.0000fffff0400p+59, 0x1.f000000fe0020p+1, INT64_C(0xf7fff800007e0004)},
{0x1.0000000400000p+45, -0x1.fffe000010200p-17, INT64_C(0x0000200000007fff)},
{-0x1.0ffe000008000p+41, 0x1.ffffffff80100p-20, INT64_C(0xfffffde003fffff1)},
{0x1.4000000000000p+34, -0x1.0000000000000p-71, INT64_C(0x00000004ffffffff)},
{-0x1.0000010000000p+54, 0x1.0000000000000p-16, INT64_C(0xffbfffffc0000001)},
{0x1.fffffffc00000p+21, 0x1.fffff801ffffep-33, INT64_C(0x00000000003fffff)},
{-0x1.00001ff7fc000p+60, -0x1.8000000001f80p+0, INT64_C(0xeffffe00803fffff)},
{0x1.3e00001000000p+52, -0x1.e07ff80001000p-6, INT64_C(0x0013e00000ffffff)},
{-0x1.0000000400000p+38, 0x1.0000000000000p-67, INT64_C(0xffffffbfffffff01)},
{0x1.0000010000000p+62, -0x1.0000000000000p-12, INT64_C(0x4000003fffffffff)},
{-0x1.000000ffc0008p+59, 0x1.0000000000000p-23, INT64_C(0xf7fffff801fffc01)},
{0x1.0000002000000p+55, -0x1.ffffffffff004p+0, INT64_C(0x008000000ffffffe)},
{-0x1.000001fffc000p+62, -0x1.fffffffffe000p+1, INT64_C(0xbfffff8000fffffd)},
{0x1.001ffff800002p+36, -0x1.c3fe800000000p-33, INT64_C(0x0000001001ffff80)},
{-0x1.00000ffffffe0p+26, -0x1.fff8000000000p-61, INT64_C(0xfffffffffbffffc1)},
{0x1.00007fe080000p+59, -0x1.ff00040000000p-1, INT64_C(0x080003ff03ffffff)},
{-0x1.0000001000000p+39, 0x1.0000000000000p-60, INT64_C(0xffffff7ffffff801)},
{0x1.0000003f80002p+48, -0x1.0000000000000p-52, INT64_C(0x00010000003f8000)},
{-0x1.0800000000000p+28, 0x1.0000000000000p-26, INT64_C(0xffffffffef800001)},
{0x1.0000004000000p+4, -0x1.fc000000fff08p-52, INT64_C(0x0000000000000010)},
{-0x1.0000ff8000000p+55, -0x1.f803ff0000000p-26, INT64_C(0xff7fff8040000000)},

// Out-of-range values:
{0x1.3fffffff80000p+666, 0x1.ffffffff00000p+593, INT64_C(0x7fffffffffffffff)},
{-0x1.007fffffe0000p+756, 0x0.0000000000000p+0, INT64_C(0x8000000000000000)},
{0x1.00001ffff8000p+939, 0x1.00007f001e000p+884, INT64_C(0x7fffffffffffffff)},
{-0x1.3dfffffffc000p+294, -0x1.ff000003ffe00p+233, INT64_C(0x8000000000000000)},
{0x1.0000000000000p+1023, -0x1.0000000000000p+953, INT64_C(0x7fffffffffffffff)},
{-0x1.001fffffffe00p+730, 0x0.0000000000000p+0, INT64_C(0x8000000000000000)},
{0x1.0000002000000p+702, -0x1.0000000000000p+602, INT64_C(0x7fffffffffffffff)},
{-0x1.01ffffffe0000p+902, -0x1.c000000200000p+841, INT64_C(0x8000000000000000)},
{0x1.00003fe0c4000p+973, -0x1.fffc032000000p+910, INT64_C(0x7fffffffffffffff)},
{-0x1.000ffffff8000p+593, -0x1.ffffffffffc00p+538, INT64_C(0x8000000000000000)},
{0x1.0007ffff00000p+383, 0x1.fffff80000000p+313, INT64_C(0x7fffffffffffffff)},
{-0x1.01ffffffc0004p+997, 0x1.fffc100000000p+936, INT64_C(0x8000000000000000)},
{0x1.0000001000000p+62, -0x1.ffffff0000800p-2, INT64_C(0x40000003ffffffff)},
{-0x1.00000003ff800p+64, -0x1.ffffe00000000p-22, INT64_C(0x8000000000000000)},
{0x1.003ffffff8000p+696, 0x1.f00000007fc00p+638, INT64_C(0x7fffffffffffffff)},
{-0x1.1ffff80000000p+591, -0x1.ffffff7ff8000p+532, INT64_C(0x8000000000000000)},
{0x1.00ff000000004p+69, -0x1.ffffff0000400p+6, INT64_C(0x7fffffffffffffff)},
{-0x1.0008000000000p+75, 0x1.0000000000000p+7, INT64_C(0x8000000000000000)},
{0x1.0000183ffffc0p+670, 0x1.fff07fcfffffcp+616, INT64_C(0x7fffffffffffffff)},
{-0x1.0000010000000p+363, 0x1.0000000000000p+288, INT64_C(0x8000000000000000)},
{0x1.1fffffff00000p+890, 0x1.fffffff000000p+813, INT64_C(0x7fffffffffffffff)},
{-0x1.0000ffffff000p+38, -0x1.ffe000003ffe0p-20, INT64_C(0xffffffbfffc00001)},
{0x1.000003fffff80p+967, 0x1.f007ffe00fc00p+904, INT64_C(0x7fffffffffffffff)},
{-0x1.0000ffffff81fp+121, -0x1.ffc7fff800000p+57, INT64_C(0x8000000000000000)},
{0x1.0000400000000p+600, -0x1.0000000000000p+509, INT64_C(0x7fffffffffffffff)},
{-0x1.0000004000000p+707, 0x1.0000000000000p+649, INT64_C(0x8000000000000000)},
{0x1.8000000000000p+850, -0x1.ffe7ffc001000p+785, INT64_C(0x7fffffffffffffff)},
{-0x1.0000000800000p+842, 0x1.fffffff400000p+767, INT64_C(0x8000000000000000)},
{0x1.007fc00007800p+448, 0x1.e0000f80001e0p+390, INT64_C(0x7fffffffffffffff)},
{-0x1.3fffff0000000p+131, -0x1.fffffe0000000p+68, INT64_C(0x8000000000000000)},
{0x1.0000200000000p+733, -0x1.0000000000000p+628, INT64_C(0x7fffffffffffffff)},
{-0x1.7fe0000000008p+383, 0x1.fffff3ff80200p+321, INT64_C(0x8000000000000000)},

// Values smaller than one:
{0x1.00001ffffff00p-784, 0x1.fffff83ff8000p-839, INT64_C(0x0000000000000000)},
{-0x1.00ffc00ffff00p-771, -0x1.fe0007fffff00p-827, INT64_C(0x0000000000000000)},
{0x1.00001fffff800p-705, 0x1.fffffffe00000p-779, INT64_C(0x0000000000000000)},
{-0x1.0000000800000p-800, 0x1.0000000000000p-872, INT64_C(0x0000000000000000)},
{0x1.000003fffc002p-916, -0x1.0000000000000p-1021, INT64_C(0x0000000000000000)},
{-0x1.000003ffffffep-19, 0x1.ffe0080000000p-103, INT64_C(0x0000000000000000)},
{0x1.0800000000000p-211, -0x1.0000000000000p-307, INT64_C(0x0000000000000000)},
{-0x1.0000007fffc00p-464, -0x1.efe0000000000p-558, INT64_C(0x0000000000000000)},
{0x1.3fe0000100000p-20, -0x1.0000000000000p-93, INT64_C(0x0000000000000000)},
{-0x1.3fffffffffe00p-397, -0x1.fe00040000000p-472, INT64_C(0x0000000000000000)},
{0x1.0001fff800000p-371, 0x1.ffffff0000ffep-425, INT64_C(0x0000000000000000)},
{-0x1.00ff000000800p-806, 0x1.0000000800000p-872, INT64_C(0x0000000000000000)},
{0x1.0000800000000p-723, -0x1.ffffffe400000p-786, INT64_C(0x0000000000000000)},
{-0x1.000001ffffffap-94, 0x1.ffe1f80400000p-169, INT64_C(0x0000000000000000)},
{0x1.0000010000000p-343, -0x1.0000000000000p-448, INT64_C(0x0000000000000000)},
{-0x1.007fffffffc00p-425, -0x1.fffffc0000000p-496, INT64_C(0x0000000000000000)},
{0x1.0080000000000p-417, -0x1.0000000000000p-490, INT64_C(0x0000000000000000)},
{-0x1.001ffffffc000p-985, -0x1.0000000000000p-1039, INT64_C(0x0000000000000000)},
{0x1.000001fffff80p-758, 0x1.fffffc001fffcp-813, INT64_C(0x0000000000000000)},
{-0x1.00f3ffffff000p-189, -0x1.fff8000000000p-257, INT64_C(0x0000000000000000)},
{0x1.0000001ffff80p-98, 0x1.fffffdfffff8ep-152, INT64_C(0x0000000000000000)},
{-0x1.0001fff800ffep-251, -0x1.c000000000000p-354, INT64_C(0x0000000000000000)},
{0x1.00000007ff800p-179, 0x1.ffff800000000p-267, INT64_C(0x0000000000000000)},
{-0x1.000001fff8008p-475, 0x1.0000000000000p-557, INT64_C(0x0000000000000000)},
{0x1.007fbfffffcf0p-964, 0x1.ffff803ffe000p-1019, INT64_C(0x0000000000000000)},
{-0x1.0000001fc4000p-493, 0x1.fe003ffe00000p-549, INT64_C(0x0000000000000000)},
{0x1.0007e3ffe0000p-845, 0x1.fe0ffffffe000p-909, INT64_C(0x0000000000000000)},
{-0x1.0000200000000p-1021, 0x0.0000000000000p+0, INT64_C(0x0000000000000000)},
{0x1.0000001000000p-487, -0x1.fffffff804000p-554, INT64_C(0x0000000000000000)},
{-0x1.000000ffff800p-309, -0x1.fffffc0000000p-392, INT64_C(0x0000000000000000)},
{0x1.0001000000000p-455, -0x1.fffffff800400p-518, INT64_C(0x0000000000000000)},
{-0x1.0000800000000p-998, 0x1.0000000000000p-1070, INT64_C(0x0000000000000000)},
};

const int numTestCases = sizeof(testCases) / sizeof(struct testVector);

int64_t __fixtfdi(long double x);

int main(int argc, char *argv[]) {
	
	int i;
	DD input;
	int64_t expected_result, computed_result;
	
	for (i=0; i<numTestCases; ++i) {
		input.hi = testCases[i].xhi;
		input.lo = testCases[i].xlo;
		expected_result = testCases[i].result;
		
		computed_result = __fixtfdi(input.ld);
		
		if (computed_result != expected_result) {
			printf("Error for __fixtfdi at %La = ( %a , %a ):\n", input.ld, input.hi, input.lo);
			printf("\tExpected %016llx ( %lld )\n", expected_result, expected_result);
			printf("\tComputed %016llx ( %lld )\n", computed_result, computed_result);
			
			return 1;
		}
	}
	
	return 0;
}
