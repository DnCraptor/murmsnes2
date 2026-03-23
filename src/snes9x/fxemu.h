/* SuperFX (GSU) emulator for murmsnes
 * Based on snes9x2005 reference, optimized for RP2350 */

#ifndef _FXEMU_H_
#define _FXEMU_H_

#include "snes9x.h"

#define FX_RAM_BANKS 4

typedef struct
{
   uint8_t*  pvRegisters;
   uint32_t  nRamBanks;
   uint8_t*  pvRam;
   uint32_t  nRomBanks;
   uint8_t*  pvRom;
} FxInit_s;

typedef struct
{
   uint32_t    avReg[16];
   uint32_t    vColorReg;
   uint32_t    vPlotOptionReg;
   uint32_t    vStatusReg;
   uint32_t    vPrgBankReg;
   uint32_t    vRomBankReg;
   uint32_t    vRamBankReg;
   uint32_t    vCacheBaseReg;
   uint32_t    vLastRamAdr;
   uint32_t*   pvDreg;
   uint32_t*   pvSreg;
   uint8_t     vRomBuffer;
   uint8_t     vPipe;
   uint8_t     vCurrentOp;

   uint32_t    vSign;
   uint32_t    vZero;
   uint32_t    vCarry;
   int32_t     vOverflow;

   uint8_t*    pvRegisters;
   uint32_t    nRamBanks;
   uint8_t*    pvRam;
   uint32_t    nRomBanks;
   uint8_t*    pvRom;
   uint32_t    vMode;
   uint32_t    vPrevMode;
   uint8_t*    pvScreenBase;
   uint8_t*    apvScreen[32];
   int32_t     x[32];
   uint32_t    vScreenHeight;
   uint32_t    vScreenRealHeight;
   uint32_t    vPrevScreenHeight;
   uint32_t    vScreenSize;
   void      (*pfPlot)(void);
   void      (*pfRpix)(void);
   uint8_t*    pvRamBank;
   uint8_t*    pvRomBank;
   uint8_t*    pvPrgBank;
   uint8_t*    apvRamBank[FX_RAM_BANKS];
   uint8_t*    apvRomBank[256];
   uint8_t     bCacheActive;
   uint32_t    vCounter;
   uint32_t    vInstCount;
   uint32_t    vSCBRDirty;
} FxRegs_s;

/* GSU register offsets in pvRegisters space */
#define GSU_SFR      0x030
#define GSU_BRAMR    0x033
#define GSU_PBR      0x034
#define GSU_ROMBR    0x036
#define GSU_CFGR     0x037
#define GSU_SCBR     0x038
#define GSU_CLSR     0x039
#define GSU_SCMR     0x03a
#define GSU_VCR      0x03b
#define GSU_RAMBR    0x03c
#define GSU_CBR      0x03e

/* SFR status flag register bits */
#define FLG_Z    (1 << 1)
#define FLG_CY   (1 << 2)
#define FLG_S    (1 << 3)
#define FLG_OV   (1 << 4)
#define FLG_G    (1 << 5)
#define FLG_R    (1 << 6)
#define FLG_ALT1 (1 << 8)
#define FLG_ALT2 (1 << 9)
#define FLG_IL   (1 << 10)
#define FLG_IH   (1 << 11)
#define FLG_B    (1 << 12)
#define FLG_IRQ  (1 << 15)

extern FxRegs_s GSU;

void FxReset(FxInit_s* psFxInfo);
int32_t FxEmulate(uint32_t nInstructions);
void FxFlushCache(void);
void fx_dirtySCBR(void);
void fx_updateRamBank(uint8_t Byte);
void fx_computeScreenPointers(void);

#endif
