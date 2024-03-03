#include <USB_MASS.h>
#include <USB_UFI.h>
//==============================================================================================================================================================
__no_init USB_MASS_Manager_TypeDef USB_MASS_Manager;
//==============================================================================================================================================================
void USB_MASS_Init(void)
{
  for (reg8 i = 0; i < sizeof(USB_MASS_Manager); i++)
    ((unsigned char*)&USB_MASS_Manager)[i] = 0;
  USB_MASS_Manager.State = USB_MASS_STATE_READY;
}
//==============================================================================================================================================================
void USB_MASS_RespondStatus()
{
  unsigned char csw[13] = {'U', 'S', 'B', 'C', };
#if (VARS_ORG == 0)
  for (reg8 i = 0; i < 9; i++)
    (&csw[4])[i] = ((unsigned char*)&USB_MASS_Manager.dCBWTag)[i];
#else
   csw[4] = USB_MASS_Manager.dCBWTag[0]; csw[5] = USB_MASS_Manager.dCBWTag[1]; csw[6] = USB_MASS_Manager.dCBWTag[2]; csw[7] = USB_MASS_Manager.dCBWTag[3];
   csw[8] = ((unsigned char*)&USB_MASS_Manager.dCSWDataResidue)[3];
   csw[9] = ((unsigned char*)&USB_MASS_Manager.dCSWDataResidue)[3];
   csw[10] = ((unsigned char*)&USB_MASS_Manager.dCSWDataResidue)[3];
   csw[11] = ((unsigned char*)&USB_MASS_Manager.dCSWDataResidue)[3];
   csw[12] = USB_MASS_Manager.bCSWStatus;
#endif
  USBP_Send(1, csw, 13);
}
//==============================================================================================================================================================
void USBP_InterfaceSetup_Process(USBH_SETUP_TypeDef* Setup)
{
  USB_MASS_REQUEST_TypeDef* Setup_MASS = (USB_MASS_REQUEST_TypeDef*)Setup;
  switch (Setup_MASS->bmRequestType.BITS.Type)
  {
//    case USB_REQUEST_TYPE_STANDARD:
//      break;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
    case USB_REQUEST_TYPE_CLASS:
      switch (Setup_MASS->Class.bRequest)
      {
        case USB_MASS_INTERFACE_CLASS_REQUEST_GET_MAX_LUN:
          USB_MASS_Manager.State = USB_MASS_STATE_READY;
          USBP_Send(0, "\0", 1);
          break;
//        case USB_MASS_INTERFACE_CLASS_REQUEST_RESET:
//          USBP_Send(0, NULL, 0);
//          break;
      }
      break;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//    case USB_REQUEST_TYPE_VENDER:
//      break;
  }
}
//==============================================================================================================================================================
void USBP_EndpointSetup_Process(USBH_SETUP_TypeDef* Setup)
{
//  switch (Setup_CDC->bmRequestType.BITS.Type)
//  {
//    case USB_REQUEST_TYPE_STANDARD:
//      break;
//    case USB_REQUEST_TYPE_CLASS:
//      break;
//    case USB_REQUEST_TYPE_VENDER:
//      break;
//  }
}
//==============================================================================================================================================================
void USBP_UserSetup_Process(USBH_SETUP_TypeDef* Setup)
{
//  switch (Setup_CDC->bmRequestType.BITS.Type)
//  {
//    case USB_REQUEST_TYPE_STANDARD:
//      break;
//    case USB_REQUEST_TYPE_CLASS:
//      break;
//    case USB_REQUEST_TYPE_VENDER:
//      break;
//  }
}
//==============================================================================================================================================================
static void ReadProcess()
{
  unsigned char const __gptr* read_point = NULL;
  reg16 size;
  if (size = USB_MASS_PrepareRead(&read_point))
  {
    USB_MASS_Manager.bCSWStatus = !(read_point);
///Here for later response =====================================================================================================================================
    USB_MASS_Manager.ClusterAddress++;
    USB_MASS_Manager.State = (--USB_MASS_Manager.Length) ? USB_MASS_STATE_PREPARE_READ : USB_MASS_STATE_RESPOND_STATUS;
    USBP_Send(1, read_point, size);
///=============================================================================================================================================================
  }
  else USB_MASS_Manager.State = USB_MASS_STATE_PREPARE_READ;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 USBP_Received(reg8 EndpointIndex, const unsigned char* Data, reg16 Length)
{
  if (EndpointIndex)
  {
    if (USB_MASS_Manager.State)         //only at received data after command write
    {
      if (USB_MASS_PrepareWriteData(Data, Length))
      {
        if (!USB_MASS_Manager.Length)
        {
          USB_MASS_RespondStatus();
          USB_MASS_Manager.State = USB_MASS_STATE_READY;
          return 0;
        }
      }
      else
        return 0;
    }
    else                                //only at ready to received command block wrapper, refer usbmass-ufi10.pdf page 15
    {
#define cbw     ((USB_MASS_CBW_TypeDef*)Data)
      USB_UFI_Command_TypeDef* command;
      USB_MASS_Manager.dCBWTag[0] = cbw->dCBWTag[0]; USB_MASS_Manager.dCBWTag[1] = cbw->dCBWTag[1]; USB_MASS_Manager.dCBWTag[2] = cbw->dCBWTag[2]; USB_MASS_Manager.dCBWTag[3] = cbw->dCBWTag[3];
      command = (USB_UFI_Command_TypeDef*)cbw->CBWCB;
      if (command->Command == UFI_COMMAND_READ10 || command->Command == UFI_COMMAND_WRITE10)
      {
        reg32 address;
#if (VARS_ORG == 1)
        USB_MASS_Manager.Length = *((unsigned short*)command->READ_10.Length);
        address = *((unsigned long)command->READ_10.LogicalBlockAddress) * USB_MASS_BLOCK_SIZE;
#else
        USB_MASS_Manager.Length = (command->READ_10.Length[0] << 8) + command->READ_10.Length[1];
        address = command->READ_10.LogicalBlockAddress[0]; address <<= 8;
        address |= command->READ_10.LogicalBlockAddress[1]; address <<= 8;
        address |= command->READ_10.LogicalBlockAddress[2]; address <<= 8;
        address |= command->READ_10.LogicalBlockAddress[3];
        USB_MASS_Manager.ClusterAddress = address;
#endif
        if (command->Command == UFI_COMMAND_READ10)
          ReadProcess();
        else
        {
#if (VARS_ORG == 0)
          USB_MASS_Manager.dCSWDataResidue = *((unsigned long*)cbw->dCBWDataTransferLength);
#else
          {
            reg32 residue = cbw->dCBWDataTransferLength[0]; residue <<= 8;
            residue |= cbw->dCBWDataTransferLength[1]; residue <<= 8;
            residue |= cbw->dCBWDataTransferLength[2]; residue <<= 8;
            residue |= cbw->dCBWDataTransferLength[3];
            USB_MASS_Manager.dCSWDataResidue = residue;
          }
#endif
          if (USB_MASS_PrepareWrite())
          {
            USB_MASS_Manager.State = USB_MASS_STATE_PREPARE_WRITE;
            return 1;
          }
          return 0;
        }
      }
      else
      {
        const USB_MASS_Descriptors_TypeDef __code* des = (const USB_MASS_Descriptors_TypeDef __code*)USBDescriptors.Class;
        USB_MASS_Manager.State = USB_MASS_STATE_RESPOND_STATUS;
//          USB_MASS_Manager.dCSWDataResidue = 0;
        switch (command->Command)
        {
//            case UFI_COMMAND_FORMAT_UNIT:
//              break;
//            case UFI_COMMAND_VERIFY10:
//              break;
          case UFI_COMMAND_INQUIRY:
            USBP_Send(1, des->UFI_InquiryData, 36);
            break;
          case UFI_COMMAND_READ_CAPACITY10:
            {
              unsigned char capacity_data[8];
              if (USB_MASS_GetCapacityData(capacity_data))
                USBP_Send(1, capacity_data, 8);
              else
                USBP_Send(1, des->UFI_CapacityData, 8);
            }
            break;
          case UFI_COMMAND_READ_FORMAT_CAPACITIES:
            {
              unsigned char format_capacities_data[12];
              if (USB_MASS_GetFormatCapacitiesData(format_capacities_data))
                USBP_Send(1, format_capacities_data, 12);
              else
                USBP_Send(1, des->UFI_FormatCapacitiesData, 12);
            }
            break;
          case UFI_COMMAND_MODE_SENSE6:
            USBP_Send(1, "\0\0\0\0\0\0\0\0", 8);
            break;
          default:
            USB_MASS_RespondStatus();
            USB_MASS_Manager.State = USB_MASS_STATE_READY;
        }
      }
#undef cbw
      return 0;
    }
  }
  return 1;
}
//==============================================================================================================================================================
reg8 USBP_PIDIn(reg8 EndpointIndex)
{
  if (EndpointIndex)
  {
    if (USB_MASS_Manager.State == USB_MASS_STATE_RESPOND_STATUS)
    {
      USB_MASS_RespondStatus();
      USB_MASS_Manager.State = USB_MASS_STATE_READY;
    }
    else if (USB_MASS_Manager.State == USB_MASS_STATE_PREPARE_READ)
      ReadProcess();
    return 0;
  }
  return 1;
}
//==============================================================================================================================================================
void USBP_OpenAnotherEndpoint()
{
  USBP_OpenEndpoint(1, (USBEndpoint_TypeDef){
    .Address = 1,
    .Type = USB_ENDPOINT_TYPE_BULK,
    .TX = {.Status = USB_ENDPOINT_STATUS_NAK, .DataID = 0},
    .RX = {.Status = USB_ENDPOINT_STATUS_VALID, .DataID = 0},
  });
}