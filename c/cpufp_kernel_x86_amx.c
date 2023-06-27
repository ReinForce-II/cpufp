#include <immintrin.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_ROWS 16
#define MAX_COLS 64
#define ARCH_GET_XCOMP_PERM     0x1022
#define ARCH_REQ_XCOMP_PERM     0x1023
#define XFEATURE_XTILECFG       17
#define XFEATURE_XTILEDATA      18

extern void cpufp_kernel_x86_amx_int8(int64_t nloops);
extern void cpufp_kernel_x86_amx_bf16(int64_t nloops);

typedef struct __tile_config
{
    uint8_t palette_id;
    uint8_t start_row;
    uint8_t reserved_0[14];
    uint16_t colsb[8];
    uint8_t reserved_1[16];
    uint8_t rows[8];
    uint8_t reserved_2[8];
} __tilecfg;

static void init_tile_config(__tilecfg *tileinfo)
{
    int i;
    tileinfo->palette_id = 1;
    tileinfo->start_row = 0;

    for (i = 0; i < 8; ++i)
    {
        tileinfo->colsb[i] = MAX_COLS;
        tileinfo->rows[i] = MAX_ROWS;
    }

    _tile_loadconfig(tileinfo);
}

static bool set_tiledata_use()
{
    if (syscall(SYS_arch_prctl, ARCH_REQ_XCOMP_PERM, XFEATURE_XTILEDATA))
    {
        return false;
    }
    else
    {
        return true;
    }

    return true;
}

void cpufp_kernel_x86_amx_int8(int64_t nloops)
{
    __tilecfg tile_data = {0};
    // Request permission to linux kernel to run AMX
    if (!set_tiledata_use())
        return;

    // Load tile configuration
    init_tile_config(&tile_data);

    while (nloops--)
    {
        // Compute dot-product of bytes in tiles
        _tile_dpbuud(2, 0, 1);
    }
    _tile_release();
}

void cpufp_kernel_x86_amx_bf16(int64_t nloops)
{
    __tilecfg tile_data = {0};
    // Request permission to linux kernel to run AMX
    if (!set_tiledata_use())
        return;

    // Load tile configuration
    init_tile_config(&tile_data);

    while (nloops--)
    {
        // Compute dot-product of bytes in tiles
        _tile_dpbf16ps(2, 0, 1);
    }
    _tile_release();
}

