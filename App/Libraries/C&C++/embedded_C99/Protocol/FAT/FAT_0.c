#include <FAT.h>
#include <config.h>

reg8 FAT_GetInfo_0()
{
  unsigned char boot_data[36];
  FAT_BootSector_TypeDef* boot = (FAT_BootSector_TypeDef*)boot_data;
  FAT_READ_0(boot_data, 0, 36);
  FATInfo.SectorsPerCluster = boot->Common.SectorsPerCluster;
  if (HighBitCount[FATInfo.SectorsPerCluster] != 1)
    return 0;
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
#if (VARS_ORG == 0)
  FATInfo.SectorSize = *((unsigned short*)boot->Common.BytesPerSector);
#else
  FATInfo.SectorSize = (boot->Common.BytesPerSector[0] << 8) | boot->Common.BytesPerSector[1];
#endif
  if (FATInfo.SectorSize != 512 && FATInfo.SectorSize != 1024 && FATInfo.SectorSize != 2048 && FATInfo.SectorSize != 4096)
    return 0;
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  FATInfo.FATSectorID = boot->Common.NumReservedSectors[VARS_ORG];
  {
    if (FATInfo.FATSectorID == 32)                                   //FAT32
    {
      reg32 sectos_per_fat;
#if (VARS_ORG == 0)
      sectos_per_fat = *((unsigned long*)boot->FAT32.SectorsPerFAT);
#else
      sectos_per_fat = (boot->FAT32.SectorsPerFAT[0] << 24) | (boot->FAT32.SectorsPerFAT[1] << 16) | (boot->FAT32.SectorsPerFAT[2] << 8) | boot->FAT32.SectorsPerFAT[3];
#endif
      FATInfo.DataSectorID = FATInfo.FATSectorID + (sectos_per_fat * boot->Common.NumFATs);      
#if (VARS_ORG == 0)
      FATInfo.NumSectors = *((unsigned long*)boot->Common.NumSectors_32);
#else
      FATInfo.NumSectors = (boot->Common.NumSectors_32[0] << 24) | (boot->Common.NumSectors_32[1] << 16) | (boot->Common.NumSectors_32[2] << 8) | boot->Common.NumSectors_32[3];
#endif      
    }
    else if (FATInfo.FATSectorID == 1)                               //FAT12/16
    {
      reg16 sectos_per_fat;
      reg32 root_entries;
#if (VARS_ORG == 0)
      sectos_per_fat = *((unsigned short*)boot->Common.SectorsPerFAT);
#else
      sectos_per_fat = (boot->Common.SectorsPerFAT[0] << 8) | boot->Common.SectorsPerFAT[1];
#endif
#if (VARS_ORG == 0)
      root_entries = *((unsigned short*)boot->Common.SectorsPerFAT);
#else
      root_entries = (boot->Common.MaxRootDirEntries[0] << 8) | boot->Common.MaxRootDirEntries[1];
#endif
      root_entries = (root_entries * 32) / FATInfo.SectorSize;
      FATInfo.DataSectorID = 1 + (sectos_per_fat * boot->Common.NumFATs) + root_entries;
#if (VARS_ORG == 0)
      FATInfo.NumSectors = *((unsigned short*)boot->Common.NumSectors);
#else
      FATInfo.NumSectors = (boot->Common.NumSectors[0] << 8) | boot->Common.NumSectors[1];
#endif   
    }
    else return 0;
  }
  return 1;
}