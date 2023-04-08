#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include "pd_controller.h"
#include "pd_controller_register.h"

#define PD_ALERT_NODE	DT_ALIAS(pdalert)
#define STUSB_I2C_ADDR 0x28

LOG_MODULE_REGISTER(PD_CTRL, CONFIG_LOG_DEFAULT_LEVEL);

//static pd_controller pdController;

static const struct device *i2c_device;

stusb_pd_snk pdo[3] = {0};
stusb_cc_status_reg cc_status = {0};
stusb_rdo_status_reg rdo_status = {0};
stusb_alert_status_reg status_reg = {0};
stusb_alert_status_mask_reg status_mask = {0};

static int pd_controller_read_bytes(uint8_t addr, uint8_t *data, uint32_t num_bytes);
static int pd_controller_write_bytes(uint8_t addr, uint8_t *data, uint32_t num_bytes);
static int pd_controller_pdo_number_is_valid(uint8_t pdo_number);
static int pd_controller_pdo_set_voltage(uint8_t pdo_number, float voltage);
static int pd_controller_pdo_set_current(uint8_t pdo_number, float current);
static int pd_controller_setup_alert();

static const struct gpio_dt_spec pd_alert = GPIO_DT_SPEC_GET_OR(PD_ALERT_NODE, gpios, {0});
static struct gpio_callback pd_alert_cb_data;

void alert_occurred(const struct device *dev, struct gpio_callback *cb,
                    uint32_t pins)
{
    LOG_INF("Alert occurred at %" PRIu32"", k_cycle_get_32());
}

int pd_controller_init()
{
    int err;

    pd_controller_setup_alert();

    i2c_device = DEVICE_DT_GET(DT_NODELABEL(i2c0));

    err = device_is_ready(i2c_device);
    if (!err) {
        LOG_ERR("PD device is not ready.");
        return -EBUSY;
    }
    LOG_INF("Initializing PD Controller:");
    LOG_INF("\t- wait for NVM to be reloaded.");

    uint8_t id_ok = 0;
    uint8_t device_id = 0;
    do {
        err = pd_controller_read_bytes(STUSB_Device_ID, &device_id, 1);
        if(device_id == 0x25)
        {
            id_ok = 1;
        }
    } while (id_ok == 0);

    uint8_t data[10] = { 0 };
    LOG_INF("\t- clearing all interrupts.");
    // clearing all interrupts by reading all registers from 0x0D to 0x16
    err += pd_controller_read_bytes(STUSB_PORT_STATUS_0, data, 10);

    LOG_INF("\t- configuring interrupts register.");
    // configure interrupt mask register

    status_mask.value = 0xFF;
    status_mask.bit.CC_DETECTION_STATUS_AL_MASK = 0;
    status_mask.bit.PD_TYPEC_STATUS_AL_MASK = 1;
    status_mask.bit.PRT_STATUS_AL_MASK = 0;
    status_mask.bit.MONITORING_STATUS_AL_MASK = 1;
    status_mask.bit.HARD_RESET_AL_MASK = 1;

    err += pd_controller_write_bytes(STUSB_ALERT_STATUS_MASK, &(status_mask.value), 1);

    if (!err) {
        LOG_INF("PD controller initilization done.");
    }

    return err;
}

int pd_controller_soft_reset() {

    int err;
    uint8_t data = STUSB_SOFT_RESET_MESSAGE_TYPE;
    err = pd_controller_write_bytes(STUSB_TX_HEADER_LOW, &data, 1);

    data = STUSB_SOFT_RESET_MESSAGE;
    err += pd_controller_write_bytes(STUSB_PD_COMMAND_CTRL, &data, 1);

    return err;
}

int pd_controller_read_pdo_snk()
{
    int err;
    uint8_t pdo_data[12] = {0};

    err = pd_controller_read_bytes(STUSB_DPM_SNK_PDO1_0, pdo_data, 12);

    for (int i = 0; i < 3; ++i) {
        pdo[i].value = ((uint32_t*)pdo_data)[i];
    }

    return err;
}

int pd_controller_write_pdo_snk() {

    uint8_t pdo_data[12];

    for (int i = 0; i < 3; ++i)
    {
        ((uint32_t*)pdo_data)[i] = pdo[i].value;
    }

    pd_controller_write_bytes(STUSB_DPM_SNK_PDO1_0, pdo_data, 12);

    return 0;
}

int pd_controller_get_typec_status() {
    int err;
    uint8_t data[2];

    err = pd_controller_read_bytes(STUSB_PORT_STATUS_1, &data[0], 1);
    err += pd_controller_read_bytes(STUSB_CC_STATUS, &data[1], 1);

    cc_status.value = data[1];

    LOG_HEXDUMP_INF(data, 2, "CC status value");

    return err;
}

int pd_controller_get_rdo_status() {
    uint8_t rdo_data[4] = {0};
    int err = pd_controller_read_bytes(STUSB_RDO_REG_STATUS_0, rdo_data, 4);
    rdo_status.value = (uint32_t) rdo_data;
    return err;
}

int pd_controller_print_rdo_status() {
    static uint8_t CC_Status_resume, Vbus_select;
    pd_controller_read_bytes(0x21, &Vbus_select, 1);
    pd_controller_read_bytes(STUSB_TYPEC_STATUS, &CC_Status_resume, 1);

    if(rdo_status.value != 0)
    {
        LOG_INF("----------- CONNECTION STATUS   ----------");
        LOG_INF("- CONTRACT        \t: EXPLICIT");
        LOG_INF("- Requested PDO # \t: %d", rdo_status.bit.Object_Pos);
//
//        LOG_INF("- Voltage requested \t: %4.2fV" ,(float ) PDO_FROM_SRC[Nego_RDO[Usb_Port].b.Object_Pos - 1].fix.Voltage/20.0 );
//
//
//        LOG_INF("- PIN \t\t\t: CC%i" , ((CC_Status_resume >> 7 ) & 1 )+1);
//        LOG_INF("- Max Current \t\t: %4.2fA \r\n - Operating Current \t: %4.2fA \r\n - Capability Mismatch \t: %d ",(float )Nego_RDO[Usb_Port].b.MaxCurrent/100.0,(float )Nego_RDO[Usb_Port].b.OperatingCurrent/100,Nego_RDO[Usb_Port].b.CapaMismatch);
//        LOG_INF("- Give back \t\t: %d ",rdo_status.bit.GiveBack);
//        LOG_INF("- USB Com Capable \t: %d ",rdo_status.bit.UsbComCap);
//        LOG_INF("- USB suspend \t\t: %d \r\n",rdo_status.bit.UsbSuspend);
    }
    else
    {

    }
    return 0;
}

int pd_controller_set_pdo_number(uint8_t number)
{
    uint8_t buffer;

    if(number > 3)
    {
        number = 3;
    }

    //load PDO number to volatile memory
    buffer = number;
    pd_controller_write_bytes(STUSB_DPM_PDO_NUMB, &buffer, 1);

    return 0;
}

int pd_controller_set_pdo(uint8_t pdo_number, float voltage, float current)
{
    pd_controller_pdo_set_voltage(pdo_number, voltage);
    pd_controller_pdo_set_current(pdo_number, current);
    return 0;
}

int pd_controller_print_pdo()
{
    LOG_HEXDUMP_INF(&pdo[0].value, 4, "PDO 1: Data");
    LOG_HEXDUMP_INF(&pdo[1].value, 4, "PDO 2: Data");
    LOG_HEXDUMP_INF(&pdo[2].value, 4, "PDO 3: Data");
    return 0;
}

int pd_controller_read_rdo_snk() {

    return 0;
}

int pd_controller_read_bytes(uint8_t addr, uint8_t *data, uint32_t num_bytes)
{
    struct i2c_msg msgs[2];

    msgs[0].buf = &addr;
    msgs[0].len = 1U;
    msgs[0].flags = I2C_MSG_WRITE;

    /* Read from device. STOP after this. */
    msgs[1].buf = data;
    msgs[1].len = num_bytes;
    msgs[1].flags = I2C_MSG_READ | I2C_MSG_STOP;

    return i2c_transfer(i2c_device, &msgs[0], 2, STUSB_I2C_ADDR);
}

int pd_controller_write_bytes(uint8_t addr, uint8_t *data, uint32_t num_bytes)
{
    struct i2c_msg msgs[2];

    /* Setup I2C messages */
    /* Send the address to write to */
    msgs[0].buf = &addr;
    msgs[0].len = 1U;
    msgs[0].flags = I2C_MSG_WRITE;

    /* Data to be written, and STOP after this. */
    msgs[1].buf = data;
    msgs[1].len = num_bytes;
    msgs[1].flags = I2C_MSG_WRITE | I2C_MSG_STOP;

    return i2c_transfer(i2c_device, &msgs[0], 2, STUSB_I2C_ADDR);
}

static inline int pd_controller_pdo_number_is_valid(uint8_t pdo_number)
{
    return pdo_number != 2 && pdo_number != 3 ? false : true;
}

static int pd_controller_pdo_set_voltage(uint8_t pdo_number, float voltage)
{
    if (pdo_number < 1) pdo_number = 1;
    else if (pdo_number > 3) pdo_number = 3;
    --pdo_number;

    if (voltage < 5) voltage = 5;
    else if (voltage > 20) voltage = 20;

    pdo[pdo_number].pdo.Voltage = (uint32_t)(voltage * 20);

    return 0;
}

static int pd_controller_pdo_set_current(uint8_t pdo_number, float current)
{
    if (pdo_number < 1) pdo_number = 1;
    else if (pdo_number > 3) pdo_number = 3;
    --pdo_number;

    if (current < 5) current = 5;
    else if (current > 20) current = 20;

    pdo[pdo_number].pdo.Operationnal_Current = (uint32_t)(current * 10);

    return 0;
}

int pd_controller_setup_alert() {
    int err;

    if (!device_is_ready(pd_alert.port)) {
        LOG_INF("Error: button device %s is not ready",
               pd_alert.port->name);
        return -EBUSY;;
    }

    err = gpio_pin_configure_dt(&pd_alert, GPIO_INPUT);
    if (err != 0) {
        LOG_INF("Error %d: failed to configure %s pin %d",
               err, pd_alert.port->name, pd_alert.pin);
        return err;
    }

    err = gpio_pin_interrupt_configure_dt(&pd_alert,
                                          GPIO_INT_EDGE_TO_ACTIVE);
    if (err != 0) {
        LOG_INF("Error %d: failed to configure interrupt on %s pin %d",
               err, pd_alert.port->name, pd_alert.pin);
        return err;
    }

    gpio_init_callback(&pd_alert_cb_data, alert_occurred, BIT(pd_alert.pin));
    gpio_add_callback(pd_alert.port, &pd_alert_cb_data);
    LOG_INF("Set up Alert at %s pin %d", pd_alert.port->name, pd_alert.pin);

    return err;
}


