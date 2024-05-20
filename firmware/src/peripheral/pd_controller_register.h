#ifndef FIREWATERBURN_I2C_PD_REGISTER_H
#define FIREWATERBURN_I2C_PD_REGISTER_H

#define STUSB_BCD_TYPEC_REV_LOW 0x06
#define STUSB_BCD_TYPEC_REV_HIGH 0x07
#define STUSB_BCD_USBPD_REV_LOW 0x08
#define STUSB_BCD_USBPD_REV_HIGH 0x09
#define STUSB_DEVICE_CAPAB_HIGH 0x0A

#define STUSB_ALERT_STATUS 0x0B
typedef union
{
    uint8_t value;
    struct
    {
        uint8_t PHY_STATUS_AL 	    	: 1;
        uint8_t PRT_STATUS_AL 	    	: 1;
        uint8_t _Reserved   	    	: 1;
        uint8_t PD_TYPEC_STATUS_AL 		: 1;
        uint8_t HW_FAULT_STATUS_AL 		: 1;
        uint8_t MONITORING_STATUS_AL 	: 1;
        uint8_t CC_DETECTION_STATUS_AL 	: 1;
        uint8_t HARD_RESET_AL 	    	: 1;
    } bit;
} stusb_alert_status_reg;

#define STUSB_ALERT_STATUS_MASK 0x0C
typedef union
{
    uint8_t value;
    struct
    {
        uint8_t PHY_STATUS_AL_MASK          : 1;
        uint8_t PRT_STATUS_AL_MASK          : 1;
        uint8_t _Reserved_2                 : 1;
        uint8_t PD_TYPEC_STATUS_AL_MASK     : 1;
        uint8_t HW_FAULT_STATUS_AL_MASK     : 1;
        uint8_t MONITORING_STATUS_AL_MASK   : 1;
        uint8_t CC_DETECTION_STATUS_AL_MASK : 1;
        uint8_t HARD_RESET_AL_MASK          : 1;
    } bit;
} stusb_alert_status_mask_reg;

#define STUSB_PORT_STATUS_0 0x0D
#define STUSB_PORT_STATUS_1 0x0E
#define STUSB_TYPEC_MONITORING_STATUS_0 0x0F
#define STUSB_TYPEC_MONITORING_STATUS_1 0x10
#define STUSB_CC_STATUS 0x11
typedef union
{
    uint8_t value;
    struct
    {
        uint8_t CC1_STATE	           : 	2;
        uint8_t CC2_STATE	           : 	2;
        uint8_t CONNECT_RESULT	   : 	1;
        uint8_t LOOKING_FOR_CONNECTION : 	1;
        uint8_t _Reserved_4_7	   :	2;
    } bit;
} stusb_cc_status_reg;
#define STUSB_CC_HW_FAULT_STATUS_0 0x12
#define STUSB_CC_HW_FAULT_STATUS_1 0x13
#define STUSB_PD_TYPEC_STATUS 0x14
#define STUSB_TYPEC_STATUS 0x15
#define STUSB_PRT_STATUS 0x16
#define STUSB_PD_COMMAND_CTRL 0x1A
#define STUSB_MONITORING_CTRL_0 0x20
#define STUSB_MONITORING_CTRL_2 0x22
#define STUSB_RESET_CTRL 0x23
#define STUSB_VBUS_DISCHARGE_TIME_CTRL 0x25
#define STUSB_VBUS_DISCHARGE_CTRL 0x26
#define STUSB_VBUS_CTRL 0x27
#define STUSB_PE_FSM 0x29
#define STUSB_GPIO_SW_GPIO 0x2D
#define STUSB_Device_ID 0x2F
#define STUSB_RX_HEADER_LOW 0x31
#define STUSB_RX_HEADER_HIGH 0x32
#define STUSB_RX_DATA_OBJ1_0 0x33
#define STUSB_RX_DATA_OBJ1_1 0x34
#define STUSB_RX_DATA_OBJ1_2 0x35
#define STUSB_RX_DATA_OBJ1_3 0x36
#define STUSB_RX_DATA_OBJ2_0 0x37
#define STUSB_RX_DATA_OBJ2_1 0x38
#define STUSB_RX_DATA_OBJ2_2 0x39
#define STUSB_RX_DATA_OBJ2_3 0x3A
#define STUSB_RX_DATA_OBJ3_0 0x3B
#define STUSB_RX_DATA_OBJ3_1 0x3C
#define STUSB_RX_DATA_OBJ3_2 0x3D
#define STUSB_RX_DATA_OBJ3_3 0x3E
#define STUSB_RX_DATA_OBJ4_0 0x3F
#define STUSB_RX_DATA_OBJ4_1 0x40
#define STUSB_RX_DATA_OBJ4_2 0x41
#define STUSB_RX_DATA_OBJ4_3 0x42
#define STUSB_RX_DATA_OBJ5_0 0x43
#define STUSB_RX_DATA_OBJ5_1 0x44
#define STUSB_RX_DATA_OBJ5_2 0x45
#define STUSB_RX_DATA_OBJ5_3 0x46
#define STUSB_RX_DATA_OBJ6_0 0x47
#define STUSB_RX_DATA_OBJ6_1 0x48
#define STUSB_RX_DATA_OBJ6_2 0x49
#define STUSB_RX_DATA_OBJ6_3 0x4A
#define STUSB_RX_DATA_OBJ7_0 0x4B
#define STUSB_RX_DATA_OBJ7_1 0x4C
#define STUSB_RX_DATA_OBJ7_2 0x4D
#define STUSB_RX_DATA_OBJ7_3 0x4E
#define STUSB_TX_HEADER_LOW 0x51
#define STUSB_TX_HEADER_HIGH 0x52
#define STUSB_DPM_PDO_NUMB 0x70
#define STUSB_DPM_SNK_PDO1_0 0x85
#define STUSB_DPM_SNK_PDO1_1 0x86
#define STUSB_DPM_SNK_PDO1_2 0x87
#define STUSB_DPM_SNK_PDO1_3 0x88
#define STUSB_DPM_SNK_PDO2_0 0x89
#define STUSB_DPM_SNK_PDO2_1 0x8A
#define STUSB_DPM_SNK_PDO2_2 0x8B
#define STUSB_DPM_SNK_PDO2_3 0x8C
#define STUSB_DPM_SNK_PDO3_0 0x8D
#define STUSB_DPM_SNK_PDO3_1 0x8E
#define STUSB_DPM_SNK_PDO3_2 0x8F
#define STUSB_DPM_SNK_PDO3_3 0x90
typedef union
{
    uint32_t value;
    struct
    {
        uint32_t Operationnal_Current : 10;
        uint32_t Voltage :10;
        uint32_t Reserved_22_20  :3;
        uint32_t Fast_Role_Req_cur : 2;  /* must be set to 0 in 2.0*/
        uint32_t Dual_Role_Data    :1;
        uint32_t USB_Communications_Capable :1;
        uint32_t Unconstrained_Power :1;
        uint32_t Higher_Capability :1;
        uint32_t Dual_Role_Power :1;
        uint32_t Fixed_Supply :2;
    }pdo;
} stusb_pd_snk;

#define STUSB_RDO_REG_STATUS_0 0x91
#define STUSB_RDO_REG_STATUS_1 0x92
#define STUSB_RDO_REG_STATUS_2 0x93
#define STUSB_RDO_REG_STATUS_3 0x94
typedef union
{
    uint32_t value;
    struct
    {
        uint32_t MaxCurrent : 10;
        uint32_t OperatingCurrent : 10;
        uint32_t reserved_22_20 : 3;
        uint32_t UnchunkedMess_sup : 1;
        uint32_t UsbSuspend : 1;
        uint32_t UsbComCap : 1;
        uint32_t CapaMismatch : 1;
        uint32_t GiveBack : 1;
        uint32_t Object_Pos : 3;
        uint32_t reserved_31 : 1;

    } bit;
} stusb_rdo_status_reg;

#define STUSB_SOFT_RESET_MESSAGE 0x26
#define STUSB_SOFT_RESET_MESSAGE_TYPE 0x0D

#endif //FIREWATERBURN_I2C_PD_REGISTER_H
