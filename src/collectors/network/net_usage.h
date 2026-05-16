#pragma once

#include <stdint.h>

typedef struct {
    uint64_t rx_bytes;
    uint64_t tx_bytes;
} NetInfo;

NetInfo getNetUsage();