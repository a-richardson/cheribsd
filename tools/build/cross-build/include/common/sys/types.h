#pragma once
#include_next <sys/types.h>
/*
 * elftoolchain includes sys/elf32.h which expects that uint32_t is defined
 * However, it only includes <sys/types.h> and not <stdint.h>
 */
#include <stdint.h>
