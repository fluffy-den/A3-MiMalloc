/*! @file   a3_fluffy_allocator.cpp
 *  @author Louis-Quentin Noé (noe.louis-quentin@hotmail.fr)
 *  @brief 
 *  @date   28-01-2023
 */

// Include: Fluffy
#include "fluffy/a3_fluffy_allocator.hpp"

// A3
// Functions
fy_nodiscard fy_allocator_api fy::size_t fy_stdcall 
MemTotalCommitted()
{
  return 0;
}
fy_nodiscard fy_allocator_api fy::size_t fy_stdcall 
MemTotalReserved()
{
  return 0;
}
fy_nodiscard fy_allocator_api fy::size_t fy_stdcall 
MemFlushCache(
  fy::size_t __size)
{
  return 0;
}
fy_allocator_api void fy_stdcall 
MemFlushCacheAll()
{
  mi_collect(true);
}
fy_nodiscard fy_allocator_api fy::size_t fy_stdcall 
MemSize(
  void *__mem)
{
  return mi_usable_size(__mem);
}
fy_nodiscard fy_allocator_api void *fy_stdcall 
MemAlloc(
  fy::size_t __size)
{
  if (__size > 16) return mi_malloc_aligned(__size, 16);
  return mi_malloc(__size);
}
fy_allocator_api void fy_stdcall 
MemFree(
  void *__mem)
{
  mi_free(__mem);
}
fy_nodiscard fy_allocator_api fy::size_t fy_stdcall 
MemSizeA( 
  void *__mem, 
  fy::size_t __alignment)
{
  return mi_usable_size(__mem);
}
fy_nodiscard fy_allocator_api void *fy_stdcall 
MemAllocA(
  fy::size_t __size, 
  fy::size_t __alignment)
{
  return mi_malloc_aligned(__size, __alignment);
}
fy_allocator_api void fy_stdcall 
MemFreeA(
  void *__mem)
{
  mi_free(__mem);
}
fy_allocator_api void fy_stdcall 
EnableHugePages()
{
  // mi_option large pages
  mi_option_enable(mi_option_reserve_huge_os_pages);
}

BOOL APIENTRY DllMain(
	HANDLE __module,
	DWORD __reason,
	LPVOID __reserved)
{
	return TRUE;
}