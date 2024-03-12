/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : mass_mal.c
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Medium Access Layer interface
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"
#include "SPI_MSD_Driver.h"
#include "nand_if.h"
#include "mass_mal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t Mass_Memory_Size[2];
uint32_t Mass_Block_Size[2];
uint32_t Mass_Block_Count[2];
__IO uint32_t Status = 0;

extern MSD_CARDINFO CardInfo;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : MAL_Init
* Description    : Initializes the Media on the STM32
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_Init(uint8_t lun)
{
  uint16_t status = MAL_OK;

  switch (lun)
  {
    case 0:  
	  status = MSD_Init();
	  if(status != 0)
	  {
		status = MAL_FAIL;
	  }
      break;
    case 1:
      break;
    default:
      return MAL_FAIL;
  }
  return status;
}

/*******************************************************************************
* Function Name  : MAL_Write
* Description    : Write sectors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_Write(uint8_t lun, uint32_t Memory_Offset, uint32_t *Writebuff, uint16_t Transfer_Length)
{

  switch (lun)
  {
    case 0:	   
      Status = MSD_WriteSingleBlock( Memory_Offset/512 , (uint8_t*)Writebuff );
      if ( Status != 0 )
      {
        return MAL_FAIL;
      }      
      break;
    case 1:
      break;
    default:
      return MAL_FAIL;
  }
  return MAL_OK;
}

/*******************************************************************************
* Function Name  : MAL_Read
* Description    : Read sectors
* Input          : None
* Output         : None
* Return         : Buffer pointer
*******************************************************************************/
uint16_t MAL_Read(uint8_t lun, uint32_t Memory_Offset, uint32_t *Readbuff, uint16_t Transfer_Length)
{

  switch (lun)
  {
    case 0:	   
      Status = MSD_ReadSingleBlock( Memory_Offset/512 , (uint8_t*)Readbuff );
      if ( Status != 0 )
      {
        return MAL_FAIL;
      }
      break;
    case 1:
      ;
      break;
    default:
      return MAL_FAIL;
  }
  return MAL_OK;
}

/*******************************************************************************
* Function Name  : MAL_GetStatus
* Description    : Get status
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_GetStatus (uint8_t lun)
{
  uint32_t DeviceSizeMul = 0,NumberOfBlocks = 0;;

  if (lun == 0)
  {
    MSD_GetCardInfo(&CardInfo);
    DeviceSizeMul = (CardInfo.CSD.DeviceSizeMul + 2);

    if(CardInfo.CardType == CARDTYPE_SDV2HC)
    {
      Mass_Block_Count[0] = (CardInfo.CSD.DeviceSize + 1) * 1024;
    }
    else
    {
      NumberOfBlocks  = ((1 << (CardInfo.CSD.RdBlockLen)) / 512);
      Mass_Block_Count[0] = ((CardInfo.CSD.DeviceSize + 1) * (1 << DeviceSizeMul) << (NumberOfBlocks/2));
    }
    Mass_Block_Size[0]  = 512;
     
    Mass_Memory_Size[0] = Mass_Block_Count[0] * Mass_Block_Size[0];
//  STM_EVAL_LEDOn(LED2);
    return MAL_OK;
  }
//  STM_EVAL_LEDOn(LED2);
  return MAL_FAIL;
}

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
