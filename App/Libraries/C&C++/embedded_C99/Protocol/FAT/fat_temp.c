
/*
void FAT_StageProcess_0()
{
  switch (FATManager.Stage.State)
  {
    case FAT_STAGE_STATE_BREAK_CHECK_ERASE:
      break;
    case FAT_STAGE_STATE_ERASE:
      break;
    case FAT_STAGE_STATE_WRITE:
      break;
    case FAT_STAGE_STATE_CHECK_TRIGGER:
      break;
    case FAT_STAGE_STATE_CHECK_ERASE:
      break;
  }
  
  
  
  
  
  
  
  
  
  
  
  switch (SDManager.State.Stage)
  {
    case SD_STAGE_BREAK_CHECK_ERASE:
      if (!FlashIC_IsBusy_0())
      {
        SDManager.State.Stage = SD_STAGE_ERASE;
        USB_MASS_Manager.State = USB_MASS_STATE_PREPARE_WRITE;
        USBP_ConfigEndpoint(1, USB_ENDPOINT_STATUS_NAK, USB_ENDPOINT_STATUS_VALID);
      }
      break;
    case SD_STAGE_ERASE:
      if (FlashIC_IsBusy_0())
        break;
      if (SDManager.Eraser.Length)
      {
        if (SDManager.Eraser.Cluster > 6 && SD_CheckRewriteDir(SDManager.Eraser.Cluster))
          re_write_dir = SDManager.Eraser.Cluster;
        else if (SDManager.Eraser.Cluster > 2)
          re_write_dir = SDManager.Eraser.Cluster;
        if (SDManager.Eraser.Cluster < 7 || SD_CheckOccupied(SDManager.Eraser.Cluster))
          FlashIC_EraseSector_0(SDManager.Eraser.Cluster * 4096);
        SDManager.Eraser.Length--;
        SDManager.Eraser.Cluster++;
      }
      else
      {
        GPIOA_BITBAND.ODR.b15 = 0;
        SDManager.State.Stage = SD_STAGE_WRITE;
        GPIOA_BITBAND.ODR.b15 = 1;
      }
      break;
    case SD_STAGE_WRITE:
      if (FlashIC_IsBusy_0())
        break;
      if (SDManager.Writer.OutIndex == 4096)
      {
        USB_MASS_Manager.ClusterAddress++;
        USB_MASS_Manager.dCSWDataResidue -= 4096;
        USB_MASS_Manager.Length--;
        SDManager.Writer.OutIndex = 0;
        SDManager.Writer.InIndex = 0;
        if (USB_MASS_Manager.Length)
          USBP_ConfigEndpoint(1, USB_ENDPOINT_STATUS_NAK, USB_ENDPOINT_STATUS_VALID);
        else
        {
          SDManager.State.Stage = SD_STAGE_CHECK_TRIGGER;
          SDManager.State.EraseCheckTrigger = System.Variables.MsTime;
          GPIOB_BITBAND.ODR.b7 = 1;
          USB_MASS_Manager.State = USB_MASS_STATE_READY;
          GPIOB_BITBAND.ODR.b7 = 0;
          USB_MASS_RespondStatus();
        }
      }
      else if (SDManager.Writer.InIndex >= (SDManager.Writer.OutIndex + 256))
      {
        FlashIC_WriteDMA_0(&System.Temp.USB_Data[SDManager.Writer.OutIndex], USB_MASS_Manager.ClusterAddress * 4096 + SDManager.Writer.OutIndex, 256);
        SDManager.Writer.OutIndex += 256;
      }
      break;
    case SD_STAGE_CHECK_TRIGGER:
      if (re_write_dir)
      {
        if ((System.Variables.MsTime - SDManager.State.EraseCheckTrigger) > 1000)
        {
          SDManager.State.Stage = SD_STAGE_CHECK_ERASE;
          SD_InitEraseChecker(re_write_dir);
          re_write_dir = 0;
        }
      }
      else
        SDManager.State.Stage = SD_STAGE_NONE;
      break;
    case SD_STAGE_CHECK_ERASE:
      if (SD_ProcessEraseChecker())
        SDManager.State.Stage = SD_STAGE_NONE;
      break;
  }
}
*/

/*
#include <sd_interface.h>

static SDChecker_TypeDef* SDChecker;




//void SDProcess(



void SD_CheckWrite(SDChecker_TypeDef* SDChecker, reg8 SectorID, void SDProcess())
{
  
}





static reg8 LoopCheckDirData(reg32 BackupAddress)
{
  if (SDChecker->Result)
    return 0;
  if (SDChecker->File.FileName[0] == 0x00 || SDChecker->File.FileName[0] == 0xFF)
    return 0;
  if (SDChecker->File.FileName[0] != 0xE5)
  {
    unsigned int cluster = *((unsigned short*)SDChecker->File.FirstLogicalCluster);
    if (cluster)
    {
      cluster += 5;
      if (cluster == (BackupAddress / FATManager.SectorSize))
        return 0;
      if (SDChecker->File.Attributes & 0x10)                //is directory
      {
        if (cluster == SDChecker->SectorID.Len8)
        {
          SDChecker->Result = 1;
          return 0;
        }
        else
        {
          cluster *= 4096;
          SD_Read((unsigned char*)&SDChecker->File, cluster, sizeof(SDChecker->File));
          while (LoopCheckDirData(cluster))
            cluster += sizeof(SDChecker->File);
        }
      }
    }
  }
  SD_Read((unsigned char*)&SDChecker->File, BackupAddress + sizeof(SDChecker->File), sizeof(SDChecker->File));
  return 1;
}
reg8 SD8_SectorIsDirData(SDChecker_TypeDef* SDChecker, reg8 SectorID)
{
  
}
*/

/*

typedef struct
{
  unsigned long LSNAddress;                     //in byte
  unsigned long SFNAddress;                     //in byte
  unsigned long SizeInBytes;
} SDFile_TypeDef;




reg8 SDFile_Import(unsigned long Address, SDFile_TypeDef* OutSDFile);
reg8 SDFile_GetName(const SDFile_TypeDef __gptr* SDFile, unsigned char* OutName);
reg8 SDFile_GetOccupied(const SDFile_TypeDef __gptr* SDFile, unsigned short* OutSectors);


typedef struct
{
  unsigned char Result;
  union
  {
    unsigned char Len8;
    unsigned short Len16;
    unsigned long Len32;
  } SectorID;
  FAT_Directory_TypeDef File;
} SDChecker_TypeDef;

void SD_CheckWrite(SDChecker_TypeDef* SDChecker, reg8 SectorID, void Process());




reg8 SD8_SectorIsDirData(SDChecker_TypeDef* SDChecker, reg8 SectorID);
reg8 SD16_SectorIsDirData(SDChecker_TypeDef* SDChecker, reg16 SectorID);
reg8 SD32_SectorIsDirData(SDChecker_TypeDef* SDChecker, reg32 SectorID);


unsigned int SD_CheckOccupied(unsigned int ClusterID);
unsigned int SD_CheckRewriteDir(unsigned int Cluster);
*/
/*
reg8 SDFile_Open(const unsigned char __gptr* FileName, SDFile_TypeDef* OutSDFile)
{
  return 1;
}
reg8 SDFile_Import(reg32 Address, SDFile_TypeDef* OutSDFile)
{
  union
  {
    unsigned char Buffer[32];
    FAT_Directory_TypeDef sfn;
    FAT_LongDirectory_TypeDef lfn;
  } file;
  OutSDFile->LSNAddress = Address;
  while (1)
  {
    SD_Read(file.Buffer, Address, sizeof(FAT_Directory_TypeDef));
    if (file.sfn.FileName[0] == 0 || file.sfn.FileName[0] == 0xE5 || file.sfn.FileName[0] == 0xFF)
      return 0;
    if (file.sfn.Attributes == 0x0F && !file.lfn.Name[3])       //is long file name and not(end long file name entry is short file name entry)
      Address += sizeof(FAT_Directory_TypeDef);
    else
      goto DETECTED;
  }
DETECTED:
  OutSDFile->SFNAddress = Address;
#if (VARS_ORG == 0)
  OutSDFile->SizeInBytes = *((unsigned long*)file.sfn.FileSize);
#else
  {
    reg32 size = file.sfn.FileSize[0]; size <<= 8;
    size |= file.sfn.FileSize[1]; size <<= 8;
    size |= file.sfn.FileSize[2]; size <<= 8;
    size |= file.sfn.FileSize[3];
    OutSDFile->SizeInBytes = size;
  }
#endif
  return 1;
}
reg8 SDFile_GetName(const SDFile_TypeDef __gptr* SDFile, unsigned char* OutName)
{
  union
  {
    unsigned char Buffer[32];
    FAT_Directory_TypeDef sfn;
    FAT_LongDirectory_TypeDef lfn;
  } file;
  reg32 address = SDFile->SFNAddress;
  if (address != SDFile->LSNAddress)
  {
    do
    {
      static const unsigned char __code char_index[] = {1, 3, 5, 7, 9, 14, 16, 18, 20, 22, 24, 28, 30};
      reg8 i;
      address -= sizeof(FAT_Directory_TypeDef);
      SD_Read(file.Buffer, address, sizeof(FAT_Directory_TypeDef));
      if (file.sfn.FileName[0] == 0 || file.sfn.FileName[0] == 0xE5 || file.sfn.FileName[0] == 0xFF)
        return 0;
      for (i = 0; i < sizeof(char_index); i++)
      {
        reg8 c = file.Buffer[char_index[i]];
        if (c)
          *OutName++ = c;
        else goto END;
      }
    } while (address != SDFile->LSNAddress);
  }
  else
  {
    reg8 i;
    SD_Read(file.Buffer, address, sizeof(FAT_Directory_TypeDef));
    if (file.sfn.FileName[0] == 0 || file.sfn.FileName[0] == 0xE5 || file.sfn.FileName[0] == 0xFF)
      return 0;
    for (i = 0; i < 11; i++)
      *OutName++ = file.Buffer[i];
  }
END:
  *OutName = 0;
  return 1;
}
reg8 SDFile_GetOccupied(const SDFile_TypeDef __gptr* SDFile, unsigned short* OutSectors)
{
  return 1;
}





unsigned int SD_CheckOccupied(unsigned int ClusterID)
{
  for (unsigned int i = 0; i < 4096; i += 512)
  {
    SD_Read(System.Temp.USB_Temp, ClusterID * 4096 + i, 512);
    for (unsigned int j = 0; j < 512 / 4; j++)
    {
      if (((unsigned int*)System.Temp.USB_Temp)[j] != 0xFFFFFFFF)
        return 1;
    }
  }
  return 0;
}

static __no_init struct
{
  unsigned char Result;
  unsigned int Cluster;
  FAT_Directory_TypeDef File;
} Checker;
static unsigned int GetNextClusterInFAT(unsigned int ClusterID)
{
  unsigned int next_cluster = 0;
  FlashIC_Read_0((unsigned char*)&next_cluster, 4096 + ((ClusterID * 3) / 2), 2);
  if (ClusterID & 1)
    next_cluster >>= 4;
  else
    next_cluster &= 0xFFF;
  return next_cluster;
}
static unsigned int LoopCheckBeUsed(unsigned int BackupAddress)
{
  if (Checker.Result)
    return 0;
  if (Checker.File.FileName[0] == 0x00 || Checker.File.FileName[0] == 0xFF)
    return 0;
  if (Checker.File.FileName[0] != 0xE5)
  {
    unsigned int cluster = *((unsigned short*)Checker.File.FirstLogicalCluster);
    if (cluster)
    {
      cluster += 5;
      if (cluster == (BackupAddress / 4096))
        return 0;
      if (Checker.File.Attributes & 0x10)                //is directory
      {
        if (cluster == Checker.Cluster)
        {
          Checker.Result = 1;
          return 0;
        }
        else
        {
          cluster *= 4096;
          SD_Read((unsigned char*)&Checker.File, cluster, sizeof(Checker.File));
          while (LoopCheckBeUsed(cluster))
            cluster += sizeof(Checker.File);
        }
      }
      else
      {
        cluster -= 5;
        do
        {
          if ((cluster + 5) == Checker.Cluster)
          {
            Checker.Result = 1;
            return 0;
          }
          cluster = GetNextClusterInFAT(cluster);
        } while (cluster && (cluster < 0xFF0));
      }
    }
  }
  SD_Read((unsigned char*)&Checker.File, BackupAddress + sizeof(Checker.File), sizeof(Checker.File));
  return 1;
}
unsigned int SD_CheckBeUsed(unsigned int Cluster)
{
  unsigned int addr = 3 * 4096;
  Checker.Cluster = Cluster;
  Checker.Result = 0;
  SD_Read((unsigned char*)&Checker.File, addr, sizeof(Checker.File));
  while (LoopCheckBeUsed(addr))
    addr += sizeof(Checker.File);
  return Checker.Result;
}
static unsigned int LoopCheckDirCluster(unsigned int BackupAddress)
{
  if (Checker.Result)
    return 0;
  if (Checker.File.FileName[0] == 0x00 || Checker.File.FileName[0] == 0xFF)
    return 0;
  if (Checker.File.FileName[0] != 0xE5)
  {
    unsigned int cluster = *((unsigned short*)Checker.File.FirstLogicalCluster);
    if (cluster)
    {
      cluster += 5;
      if (cluster == (BackupAddress / 4096))
        return 0;
      if (Checker.File.Attributes & 0x10)                //is directory
      {
        if (cluster == Checker.Cluster)
        {
          Checker.Result = 1;
          return 0;
        }
        else
        {
          cluster *= 4096;
          SD_Read((unsigned char*)&Checker.File, cluster, sizeof(Checker.File));
          while (LoopCheckDirCluster(cluster))
            cluster += sizeof(Checker.File);
        }
      }
    }
  }
  SD_Read((unsigned char*)&Checker.File, BackupAddress + sizeof(Checker.File), sizeof(Checker.File));
  return 1;
}
unsigned int SD_CheckRewriteDir(unsigned int Cluster)
{
  unsigned int addr = 3 * 4096;
  Checker.Cluster = Cluster;
  Checker.Result = 0;
  SD_Read((unsigned char*)&Checker.File, addr, sizeof(Checker.File));
  while (LoopCheckDirCluster(addr))
    addr += sizeof(Checker.File);
  return Checker.Result;
}

void SD_InitEraseChecker(unsigned int Cluster)
{
  SDManager.EraseChecker.Level = 0;
  SDManager.EraseChecker.File[0].Cluster = Cluster;
  Cluster *= 4096;
  SDManager.EraseChecker.File[0].Index = Cluster;
  SD_Read((unsigned char*)&Checker.File, Cluster, sizeof(Checker.File));
}
unsigned int SD_ProcessEraseChecker()
{       
  if (Checker.File.FileName[0] == 0x00 || Checker.File.FileName[0] == 0xFF)             //break directory, make sure lower level is directory or quit
  {
    if (SDManager.EraseChecker.Level)
      SDManager.EraseChecker.Level--;
    else
      return 1;
  }
  else
  {
    if (SDManager.EraseChecker.File[SDManager.EraseChecker.Level].Index == 0xFFFF)      //is deleting file
    {
      if (FlashIC_IsBusy_0())
        return 0;
      {
        unsigned int cluster = GetNextClusterInFAT(SDManager.EraseChecker.File[SDManager.EraseChecker.Level].Cluster);
        if (cluster && (cluster < 0xFF0) && !SD_CheckBeUsed(cluster + 5))
        {
          SD_Read((unsigned char*)&Checker.File, SDManager.EraseChecker.File[SDManager.EraseChecker.Level - 1].Index, sizeof(Checker.File));
          SDManager.EraseChecker.File[SDManager.EraseChecker.Level].Cluster = cluster;
          cluster += 5;
          if (SD_CheckOccupied(cluster))
            FlashIC_EraseSector_0(cluster * 4096);
          return 0;
        }
        else
          SDManager.EraseChecker.Level--;
      }
    }
    else if (Checker.File.FileName[0] == 0xE5)                                          //file is erased
    {
      unsigned int cluster = *((unsigned short*)Checker.File.FirstLogicalCluster);
      if (cluster && !SD_CheckBeUsed(cluster + 5))
      {
        SD_Read((unsigned char*)&Checker.File, SDManager.EraseChecker.File[SDManager.EraseChecker.Level].Index, sizeof(Checker.File));
        SDManager.EraseChecker.Level++;
        cluster += 5;
        if (Checker.File.Attributes & 0x10)                                             //is directory
        {
          SDManager.EraseChecker.File[SDManager.EraseChecker.Level].Cluster = cluster;
          cluster *= 4096;
          SDManager.EraseChecker.File[SDManager.EraseChecker.Level].Index = cluster;
          SD_Read((unsigned char*)&Checker.File, cluster, sizeof(Checker.File));
        }
        else
        {
          SDManager.EraseChecker.File[SDManager.EraseChecker.Level].Index = 0xFFFF;
          SDManager.EraseChecker.File[SDManager.EraseChecker.Level].Cluster = cluster - 5;
          if (SD_CheckOccupied(cluster))
            FlashIC_EraseSector_0(cluster * 4096);
        }
        return 0;
      }
    }
  }
  {
    SDManager.EraseChecker.File[SDManager.EraseChecker.Level].Index += sizeof(Checker.File);
    SD_Read((unsigned char*)&Checker.File, SDManager.EraseChecker.File[SDManager.EraseChecker.Level].Index, sizeof(Checker.File));
  }
  return 0;
}
*/

/*

void FAT_StageProcess_0();






void FAT_Open(FAT_Directory_TypeDef* File, const char* Name);
void FAT_Next(FAT_Directory_TypeDef* File);






//FAT_Directory_TypeDef* get_occupied_cluster_by_dir(FAT_Directory_TypeDef* File, unsigned int FileClusterAddress)
//{
//  if (File->FileName[0] == 0x00 || File->FileName[0] == 0xFF)
//    return NULL;
//  if (File->FileName[0] != 0xE5)
//  {
//    unsigned int cluster = *((unsigned short*)File->FirstLogicalCluster);
//    if (cluster)
//    {
//      cluster += 5;
//      if (!occupied.data[occupied.index][cluster])
//      {
//        if (File->Attributes & 0x10)                    //is directory
//        {
//          occupied.data[occupied.index][cluster] = 1;
//          cluster *= 4096;
//          FlashIC_Read_0(buffer, cluster, 4096);
//          FAT_Directory_TypeDef* file = (FAT_Directory_TypeDef*)buffer;
//          do
//          {
//            file = get_occupied_cluster_by_dir(file, cluster);
//          } while (file);
//          FlashIC_Read_0(buffer, FileClusterAddress, 4096);
//        }
//        else
//        {
//          cluster -= 5;
//          do
//          {
//            occupied.data[occupied.index][cluster + 5] = 1;
//            cluster = get_next_cluster_in_fat(cluster);
//          } while (cluster && (cluster < 0xFF0));
//        }
//      }
//    }
//  }
//  return ++File;
//}
//void get_occupied(unsigned int index)
//{
//  occupied.index = index;
//  for (unsigned int i = 0; i < 512 / 4; i++)
//    ((unsigned int*)occupied.data[index])[i] = 0;
//  FlashIC_Read_0(buffer, 3 * 4096, 4096);
//  FAT_Directory_TypeDef* File = (FAT_Directory_TypeDef*)buffer;
//  do
//  {
//    File = get_occupied_cluster_by_dir(File, 3 * 4096);
//  } while (File);
//}
//unsigned int get_next_cluster_in_fat(unsigned int cluster_id)
//{
//  unsigned int next_cluster = 0;
//  FlashIC_Read_0((unsigned char*)&next_cluster, 4096 + ((cluster_id * 3) / 2), 2);
//  if (cluster_id & 1)
//    next_cluster >>= 4;
//  else
//    next_cluster &= 0xFFF;
//  return next_cluster;
//  
////  if (next_cluster && (next_cluster < 0xFF0 || next_cluster >= 0xFF8))
////  {
////    if (next_cluster < 0xFF0)
////      (*cluster_id) = next_cluster;
////    return next_cluster;
////  }
////  return 0;
//}
//void get_occupied_cluster_by_fat()
//{
//  FlashIC_Read_0(buffer, 1 * 4096, 768);
//  for (unsigned int i = 7; i < 512; i++)
//  {
//    unsigned int index = ((i - 5) * 3) / 2;
//    unsigned int occ = buffer[index];
//    occ += buffer[index + 1] << 8;
//    if (i & 1)
//      occ >>= 4;
//    else
//      occ &= 0xFFF;
//    occupied.data[1][i] = 0;
//    if (occ && (occ < 0xFF0 || occ >= 0xFF8))
//      occupied.data[1][i] = 1;
//  }
//}
*/
/*
typedef enum
{
  FAT_STAGE_STATE_NONE                  = 0,
  FAT_STAGE_STATE_ERASE                 = 1,
  FAT_STAGE_STATE_WRITE                 = 2,
  FAT_STAGE_STATE_BREAK_CHECK_ERASE     = 3,
  
  FAT_STAGE_STATE_CHECK_TRIGGER         = 4,
  FAT_STAGE_STATE_CHECK_ERASE           = 5,
} FAT_STAGE_STATE;

typedef struct
{
  FATInfo_TypeDef Info;
  struct
  {
    FAT_STAGE_STATE State;
    unsigned char ResponseEnable;
    unsigned short EraseCheckTrigger;
    struct
    {
      unsigned short InIndex;
      unsigned short OutIndex;
    } Writer;
    struct
    {
      unsigned short Sector;
      unsigned short Length;
    } Eraser;
  } Stage;
} FATManager_TypeDef;
extern __no_init FATManager_TypeDef FATManager;
*/

/*
  if (FlashIC_GetInfo_0())
  {
    if (!FAT_GetInfo_0())
    {
      static const FAT_BootSector_TypeDef boot = {
        .Common = {
          ._JmpBoot = {0xEB, 0x3C, 0x90},
          ._OEMName = {'M', 'S', 'D', 'O', 'S', '5', '.', '0'},
          .BytesPerSector = {0x00, 0x10},
          .SectorsPerCluster = 1,
          .NumReservedSectors = {1, 0},
          .NumFATs = 1,
          .MaxRootDirEntries = {32, 0},
          .NumSectors = {32, 0},
          ._Media = 0xF8,
          .SectorsPerFAT = {1, 0},
          ._SectorsPerTrack = {0, 0},
          ._NumHeads =  {0, 0},
          ._HiddSec = {0, 0, 0, 0},
          .NumSectors_32 = {0, 0, 0, 0},
        },
        .FAT1216 = {
          ._DriveNumber = 0x00,
          ._reserved = 0,
          ._BootSignature = 0x29,
          .VolumeID = {0, 0, 0, 0},
          .VolumeLabel = {'N', 'O', ' ', 'N', 'A', 'M', 'E', ' ', ' ', ' ', ' '},
          .FileSystemType = {'F', 'A', 'T', '1', '2', ' ', ' ', ' '},
        },
      };
      FlashIC_EraseMass_0();
      while (FlashIC_IsBusy_0());
      FlashIC_WriteDMA_0((const unsigned char*)&boot, 0, sizeof(boot));
      while (FlashIC_IsBusy_0());
      static const unsigned char end_boot[] = {0x55, 0xAA, };
      FlashIC_Write_0(end_boot, 510, sizeof(end_boot));
      while (FlashIC_IsBusy_0());
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      static const unsigned char fat_begin[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, };
      FlashIC_Write_0(fat_begin, 4096, sizeof(fat_begin));
      while (FlashIC_IsBusy_0());
      FlashIC_Write_0(NULL, 4096 + sizeof(fat_begin), 42);
      while (FlashIC_IsBusy_0());
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      static const FAT_Directory_TypeDef root_dir = {
        .FileName = {'S', 'Y', 'S', 'T', 'E', 'M', '~', '1'},
        .Extension = {' ', ' ', ' '},
        .Attributes = 0x16,
        ._WinNT_NameType = 0,
        ._CreationTimeMillis = 0,
        .CreationTime = {0, 0},
        .CreationDate = {0, 0},
        .LastAccessDate = {0, 0},
        .FirstClusterHigh = {0, 0},
        .LastWriteTime = {0, 0},
        .LastWriteDate = {0, 0},
        .FirstLogicalCluster = {0, 0},
        .FileSize = {0, 0, 0, 0},
      };
      FlashIC_WriteDMA_0((const unsigned char*)&root_dir, 2 * 4096, sizeof(root_dir));
      while (FlashIC_IsBusy_0());
      FlashIC_Write_0(NULL, 2 * 4096 + sizeof(root_dir), 256 - sizeof(root_dir));
      while (FlashIC_IsBusy_0());
    }
  }
  else while (1)
  {
    
  }
*/