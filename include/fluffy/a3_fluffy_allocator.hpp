/*! @file   a3_fluffy_allocator.hpp
 *  @author Louis-Quentin Noé (noe.louis-quentin@hotmail.fr)
 *  @brief 
 *  @date   28-01-2023
 */

#ifndef A3_FLUFFY_ALLOCATOR_HPP
#define A3_FLUFFY_ALLOCATOR_HPP 1

// Include: MiMalloc
#include "mimalloc.h"

// Include: Windows
#include "windows.h"
# define WIN32_LEAN_AND_MEAN 1
# define VC_EXTRALEAN        1
# define NOMINMAX            1

// Defines
#define fy_stdcall       __stdcall
#define fy_import        __declspec(dllimport)
#define fy_export        __declspec(dllexport)
#ifdef A3_FLUFFY_ALLOCATOR_CONSTRUCT
#define fy_allocator_api fy_export
#else
#define fy_allocator_api fy_import
#endif
#define fy_nodiscard     [[nodiscard]]

// Fluffy
namespace fy
{
  using size_t = size_t;
}

// A3
extern "C" {
  // Functions
	fy_nodiscard fy_allocator_api fy::size_t fy_stdcall MemTotalCommitted(); // _MemTotalCommitted@0 on x86
	fy_nodiscard fy_allocator_api fy::size_t fy_stdcall MemTotalReserved(); // _MemTotalReserved@0 on x86
	fy_nodiscard fy_allocator_api fy::size_t fy_stdcall MemFlushCache(fy::size_t size); // _MemFlushCache@4 on x86
	fy_allocator_api void fy_stdcall MemFlushCacheAll(); // _MemFlushCacheAll@0 on x86
	fy_nodiscard fy_allocator_api fy::size_t fy_stdcall MemSize(void *mem); // _MemSize@4 on x86
	fy_nodiscard fy_allocator_api void *fy_stdcall MemAlloc(fy::size_t size); // _MemAlloc@4 on x86
	fy_allocator_api void fy_stdcall MemFree(void *mem); // _MemFree@4 on x86
	fy_nodiscard fy_allocator_api fy::size_t fy_stdcall MemSizeA( void *mem, fy::size_t aligment); // _MemSizeA@8 on x86
	fy_nodiscard fy_allocator_api void *fy_stdcall MemAllocA(fy::size_t size, fy::size_t aligment); // _MemAllocA@8 on x86
	fy_allocator_api void fy_stdcall MemFreeA(void *mem); // _MemFreeA@4 on x86
	fy_allocator_api void fy_stdcall EnableHugePages(); // _EnableHugePages@0 on x86
};

#endif // !A3_FLUFFY_ALLOCATOR_HPP