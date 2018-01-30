#pragma once

#define atomic_fetchadd_long(ptr, val) __sync_fetch_and_add(ptr, val)
#define atomic_add_long(ptr, val) __sync_fetch_and_add(ptr, val)