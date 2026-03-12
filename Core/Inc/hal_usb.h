#ifndef HAL_USB_H
#define HAL_USB_H

#include <stdint.h>
#include <stdbool.h>

/* USB Status */
typedef enum {
    USB_OK = 0,
    USB_ERR_INIT,
    USB_ERR_TX,
    USB_ERR_RX
} usb_status_t;

/* Initialize USBX CDC Device stack */
usb_status_t hal_usb_init(void);

/* Transmit data over Virtual COM Port (CDC) */
usb_status_t hal_usb_transmit(const uint8_t *data, uint16_t len);

/* Receive data from Virtual COM Port (CDC) - Non-blocking */
usb_status_t hal_usb_receive(uint8_t *data, uint16_t *len);

/* Check if USB is connected and enumerated */
bool hal_usb_is_connected(void);

#endif /* HAL_USB_H */
