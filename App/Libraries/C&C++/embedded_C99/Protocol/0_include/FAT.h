#ifndef _FAT_H_
#define _FAT_H_

/**                   VALUE ALWAYS LOW BYTE FIRST
Disk organization of the FAT12 file system
                                                                        |  File clusters: 2:(max)2849
                |               |  FAT tables   |                       |------------------>>
                |  Boot Sector  |  FAT1 |  FAT2 |      Root directory   |   Data area
   Disk Sectors |      0        |   1:9 | 10:18 |         19:32         |   33:(max)2879
*/

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  RSTRUCT(Common, unsigned char,
    _JmpBoot                            [3],    //0:2           [0xEB, 0x??, 0x90]: Short Jump + NOP or [0xE9, 0x??, 0x??]: Near Jump
    _OEMName                            [8],    //3:10          "MSWIN4.1" or "MSDOS5.0"
    BytesPerSector                      [2],    //11-12                         Count of bytes per sector: (512, 1024, 2048 or 4096)
    SectorsPerCluster                   ,       //13                            Number of sectors per allocation unit: 1, 2, 4,... (BytesPerSector * SectorsPerCluster) <= 32KB
    NumReservedSectors                  [2],    //14-15                         Number of reserved sectors at the first sector of the volume
    NumFATs                             ,       //16            0x02            The count of FAT data structures on the volume
    MaxRootDirEntries                   [2],    //17-18                         sectors of root = (MaxRootDirEntries * 32) / BytesPerSector
    NumSectors                          [2],    //19-20                         This field is the old 16-bit total count of sectors on the volume
    _Media                              ,       //21            0xF8
    SectorsPerFAT                       [2],    //22-23
    _SectorsPerTrack                    [2],    //24-25                         only used for IBM PC
    _NumHeads                           [2],    //26-27                         only used for IBM PC
    _HiddSec                            [4],    //28:31                         only used for IBM PC
    NumSectors_32                       [4]);   //32:35                         FAT32: override NumSectors
  union
  {
    RSTRUCT(FAT1216, unsigned char,
    _DriveNumber                        ,       //36            0x00
    _reserved                           ,
    _BootSignature                      ,       //38            0x29
    VolumeID                            [4],    //39:42
    VolumeLabel                         [11],   //43:53
    FileSystemType                      [8]);   //54:61         "FAT12   " or "FAT16   " or "FAT     "
    struct
    {
      unsigned char SectorsPerFAT       [4];    //36:39                         override Common.SectorsPerFAT
      BUNION(ExtFlags, unsigned char,           //40-41
        ActiveFAT                       , 4,    //0:3
        _reserved                       , 3,
        OneFATActive                    , 1,    //7                             0: all FAT active, 1: only FAT at ActiveFAT is active
        _reserved1                      , 8);
      REGS(unsigned char,
        FSVersion                       [2],    //42-43
        RootCluster                     [4],    //44:47                         the cluster number of the first cluster of the root directory
        FSInfo                          [2],    //48-49                         Sector number of FSINFO structure
        BackupBootSector                [2],    //50-51                         If non-zero, indicates the sector number in the reserved area of the volume of a copy of the boot record, usually 6
        _reserved                       [12],
        _DriveNumber                    ,       //64
        _reserved1                      ,
        BootSignature                   ,       //66
        VolumeID                        [4],    //67:70
        VolumeLabel                     [11],   //71:81
        FileSystemType                  [8]);   //82:89         "FAT32   "
    } FAT32;
  };
} FAT_BootSector_TypeDef;
typedef RSTRUCT(FAT_Directory_TypeDef, unsigned char,
  FileName                              [8],    //0:7                           always uppercase
  Extension                             [3],    //8:10                          always uppercase
  Attributes                            ,       //11                            0x01: READ_ONLY
                                                //                              0x02: HIDDEN
                                                //                              0x04: SYSTEM
                                                //                              0x08: VOLUME_ID
                                                //                              0x10: DIRECTORY
                                                //                              0x20: ARCHIVE
                                                //                              0x0F: LONG_NAME
  _WinNT_NameType                       ,       //12                            only for windows NT, 0x08: all is lower case, 0x10: extension is lower case
  _CreationTimeMillis                   ,       //13                            CreationTime is in 2s --> _CreationTimeMillis 0:199 <=> 0:1.99s
  CreationTime                          [2],    //14-15
  CreationDate                          [2],    //16-17
  LastAccessDate                        [2],    //18-19
  FirstClusterHigh                      [2],    //20-21                         High word of this entry’s first cluster number (only FAT32)
  LastWriteTime                         [2],    //22-23
  LastWriteDate                         [2],    //24-25
  FirstLogicalCluster                   [2],    //26-27                         Low word of this entry’s first cluster number, at FAT32 mix FirstClusterHigh
  FileSize                              [4]);   //28:31                         32-bit DWORD holding this file’s size in bytes
typedef RSTRUCT(FAT_LongDirectory_TypeDef, unsigned char,
  Order                                 ,       //0                             index of this in entries, if (Order & 0x40) -> last entry
  Name                                  [10],   //1:10                          if name = "ABC" -> FileName = {Order, 'A', 0, 'B', 0, 'C', 0,...}
  Attributes                            ,       //11            0x0F: LONG_NAME
  _Type                                 ,       //12            0
  CheckSum                              ,       //13            
  Name2                                 [12],   //14:25
  _FirstLogicalCluster                  [2],    //26-27         {0, 0}
  Name3                                 [4]);   //28:31
typedef RSTRUCT(FAT32_FSInfo_TypeDef, unsigned char,
  LeadSignature                         [4],    //0:3           [0x52, 0x52, 0x61, 0x41]
  _reserved                             [480],
  StrucSignature                        [4],    //484:487       [0x72, 0x72, 0x41, 0x61]
  FreeClusters                          [4],    //488:491                       number of free clusters, 0xFFFFFFFF: unknown
  NextFreeCluster                       [4],    //492:495                       the driver should start looking for free clusters, 0xFFFFFFFF: unknown
  _reserved1                            [12],
  TrailSignature                        [4]);   //508:511       [0x00, 0x00, 0x55, 0xAA]


/** BUILD ON STM32F103C8T6 FATFS user-define-default
//MX_FATFS_Init();                    //code: 150, data: 15, ram: 38
//f_mount (NULL, NULL, 0);            //code: 1624, data: 0, ram: 42
//f_open(NULL, NULL, 0);              //code: 4778, data: 150, ram: 30
//f_close(NULL);                      //code: 680, data: 0, ram: 0
//f_read (NULL, NULL, 0, NULL);       //code: 620, data: 0, ram: 0
//f_write (NULL, NULL, 0, NULL);      //code: 672, data: 0, ram: 0
*/

typedef struct
{
  unsigned char SectorsPerCluster;      //1, 2, 4,... SectorsPerCluster * [SectorSize] <= 32KB
  unsigned char FATSectorID;
  unsigned short SectorSize;            //512, 1024, 2048, 4096
  unsigned long DataSectorID;
  unsigned long NumSectors;
} FATInfo_TypeDef;

extern __no_init FATInfo_TypeDef FATInfo;
reg8 FAT_GetInfo_0();

#endif