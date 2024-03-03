#include <rx8025.h>
#include <config.h>

static const unsigned char CalibArray[] = {
//25   26   27   28   29   30   31   32   33   34   
  0,   0,   1,   3,   6,   9,   13,  17,  22,  28,
//35   36   37   38   39   40   41   42   43   44   
  35,  42,  50,  59,  69,  79,  90,  101, 113, 126,
//45   46   47   48   49   50   51   52   53   54   
  140, 154, 169, 185, 202, 219, 237, 255,
};
static reg8 GetWeight(reg8 RefStage, reg8 NowTemper, reg8 OffSet)
{
  reg8 residuals, weight;
  if (NowTemper & 0x80)
    RefStage = 0xFF;
  NowTemper &= 0x7F;
  if (NowTemper < 25)
    NowTemper = 25 - NowTemper;
  else
    NowTemper -= 25;
  residuals = ((CalibArray[NowTemper] + OffSet * 10) * 100) / 305;
  weight = residuals / 10;
  residuals = residuals % 10;
  weight += RefStage <= residuals;
  if (weight)
    weight = 0x80 - weight;
  return weight;
}

void RX8025_CalibProcess_0(reg8 NowTemper, reg8 OffSet)                 //must trigg x20(s), NowTemper & 0x7F: 0->52 (C), if (NowTemper & 0x00) : re-init
{
  static unsigned char ref_stage = 0;
  reg8 weight;
  if (NowTemper & 0x80)
    ref_stage = 0;
  NowTemper &= 0x7F;
  weight = GetWeight(ref_stage, NowTemper, OffSet);
  RX8025_I2C_WRITES_0(0x70, (const unsigned char*)&weight, 1);
  ref_stage++;
  if (ref_stage > 9)
    ref_stage = 0;
}
reg8 RX8025_CalibProcess_1(const SI2CFunction_TypeDef __gptr *SI2CFunction, reg8 RefStage, reg8 NowTemper, reg8 OffSet)         //RefStage: 0:9, return RefStage
{
  reg8 weight;
  if (NowTemper & 0x80)
    RefStage = 0;
  NowTemper &= 0x7F;
  weight = GetWeight(RefStage, NowTemper, OffSet);
  SI2C_WriteBytes_1(SI2CFunction, RX8025_I2C_ADDRESS, 0x70, (const unsigned char*)&weight, 1);
  RefStage++;
  if (RefStage > 9)
    RefStage = 0;
  return RefStage;
}