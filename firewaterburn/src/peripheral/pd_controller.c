#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include "pd_controller.h"
#include "pd_controller_register.h"

#define PD_ALERT_NODE    DT_ALIAS(pdalert)
#define STUSB_I2C_ADDR 0x28

LOG_MODULE_REGISTER(USB_PD, CONFIG_LOG_DEFAULT_LEVEL);

struct stusb_pd_controller pd_controller = {
        .i2c_device = DEVICE_DT_GET(DT_NODELABEL(i2c1)),
        .pd_alert = GPIO_DT_SPEC_GET_OR(PD_ALERT_NODE, gpios, { 0 }),
        .pdo = {{0},
                {0},
                {0}},
        .cc_status = {0},
        .rdo_status = {0},
        .status_reg = {0},
        .status_mask = {0}
};

static int pd_controller_read_bytes(uint8_t addr, uint8_t *data, uint32_t num_bytes);

static int pd_controller_write_bytes(uint8_t addr, uint8_t *data, uint32_t num_bytes);

static int pd_controller_setup_alert();

static struct gpio_callback pd_alert_cb_data;

void alert_occurred(const struct device *dev, struct gpio_callback *cb,
                    uint32_t pins)
{
    LOG_INF("Alert occurred at %" PRIu32"", k_cycle_get_32());
}

int pd_controller_init()
{
    int err;
    //wait 200ms to ensure that the pd controller is powered up
    k_msleep(500);

    pd_controller_setup_alert();

    err = device_is_ready(pd_controller.i2c_device);
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
        if (device_id == 0x25) {
            id_ok = 1;
        }
        else {
            LOG_INF("nvm has not been reloaded yet");
        }
    } while (id_ok == 0);

    uint8_t data[10] = {0};
    LOG_INF("\t- clearing all interrupts.");
    // clearing all interrupts by reading all registers from 0x0D to 0x16
    err += pd_controller_read_bytes(STUSB_PORT_STATUS_0, data, 10);

    LOG_INF("\t- configuring interrupts register.");
    // configure interrupt mask register

    pd_controller.status_mask.value = 0xFF;
    pd_controller.status_mask.bit.CC_DETECTION_STATUS_AL_MASK = 0;
    pd_controller.status_mask.bit.PD_TYPEC_STATUS_AL_MASK = 1;
    pd_controller.status_mask.bit.PRT_STATUS_AL_MASK = 0;
    pd_controller.status_mask.bit.MONITORING_STATUS_AL_MASK = 1;
    pd_controller.status_mask.bit.HARD_RESET_AL_MASK = 1;

    err += pd_controller_write_bytes(STUSB_ALERT_STATUS_MASK, &(pd_controller.status_mask.value), 1);

    if (!err) {
        LOG_INF("PD controller initilization done.");
    }

    return err;
}

int pd_controller_soft_reset()
{

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
        pd_controller.pdo[i].value = ((uint32_t *) pdo_data)[i];
    }

    return err;
}

int pd_controller_write_pdo_snk()
{

    uint8_t pdo_data[12];

    for (int i = 0; i < 3; ++i) {
        ((uint32_t *) pdo_data)[i] = pd_controller.pdo[i].value;
    }

    pd_controller_write_bytes(STUSB_DPM_SNK_PDO1_0, pdo_data, 12);

    return 0;
}

int pd_controller_set_pdo_number(uint8_t number)
{
    uint8_t buffer;

    if (number > 3) {
        number = 3;
    }

    //load PDO number to volatile memory
    buffer = number;
    pd_controller_write_bytes(STUSB_DPM_PDO_NUMB, &buffer, 1);

    return 0;
}

int pd_controller_pdo_set(uint8_t pdo_number, float voltage, float current)
{
    pd_controller_pdo_set_voltage(pdo_number, voltage);
    pd_controller_pdo_set_current(pdo_number, current);
    return 0;
}

int pd_controller_pdo_set_voltage(uint8_t pdo_number, float voltage)
{
    if (pdo_number < 1) { pdo_number = 1; }
    else if (pdo_number > 3) { pdo_number = 3; }
    --pdo_number;

    if (voltage < 5) { voltage = 5; }
    else if (voltage > 20) { voltage = 20; }

    pd_controller.pdo[pdo_number].pdo.Voltage = (uint32_t) (voltage * 20);

    return 0;
}

int pd_controller_pdo_set_current(uint8_t pdo_number, float current)
{
    if (pdo_number < 1) { pdo_number = 1; }
    else if (pdo_number > 3) { pdo_number = 3; }
    --pdo_number;

    if (current < 5) { current = 5; }
    else if (current > 20) { current = 20; }

    pd_controller.pdo[pdo_number].pdo.Operationnal_Current = (uint32_t) (current * 10);

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

    return i2c_transfer(pd_controller.i2c_device, &msgs[0], 2, STUSB_I2C_ADDR);
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

    return i2c_transfer(pd_controller.i2c_device, &msgs[0], 2, STUSB_I2C_ADDR);
}

static inline int pd_controller_pdo_number_is_valid(uint8_t pdo_number)
{
    return pdo_number != 2 && pdo_number != 3 ? false : true;
}

int pd_controller_setup_alert()
{
    int err;

    if (!device_is_ready(pd_controller.pd_alert.port)) {
        LOG_INF("Error: button device %s is not ready",
                pd_controller.pd_alert.port->name);
        return -EBUSY;;
    }

    err = gpio_pin_configure_dt(&pd_controller.pd_alert, GPIO_INPUT);
    if (err != 0) {
        LOG_INF("Error %d: failed to configure %s pin %d",
                err, pd_controller.pd_alert.port->name, pd_controller.pd_alert.pin);
        return err;
    }

    err = gpio_pin_interrupt_configure_dt(&pd_controller.pd_alert,
                                          GPIO_INT_EDGE_TO_ACTIVE);
    if (err != 0) {
        LOG_INF("Error %d: failed to configure interrupt on %s pin %d",
                err, pd_controller.pd_alert.port->name, pd_controller.pd_alert.pin);
        return err;
    }

    gpio_init_callback(&pd_alert_cb_data, alert_occurred, BIT(pd_controller.pd_alert.pin));
    gpio_add_callback(pd_controller.pd_alert.port, &pd_alert_cb_data);
    LOG_INF("Set up Alert at %s pin %d", pd_controller.pd_alert.port->name, pd_controller.pd_alert.pin);

    return err;
}


