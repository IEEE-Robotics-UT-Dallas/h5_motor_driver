#include "unity.h"
#include "hal_usb.h"
#include <string.h>

extern void _hal_usb_mock_set_connected(bool connected);
extern void _hal_usb_mock_inject_init_fail(bool fail);
extern uint16_t _hal_usb_mock_get_tx_data(uint8_t *buf);

void setUp(void) {
    _hal_usb_mock_set_connected(false);
    _hal_usb_mock_inject_init_fail(false);
}

void tearDown(void) {}

void test_usb_initialization_success(void) {
    TEST_ASSERT_EQUAL_INT(USB_OK, hal_usb_init());
    TEST_ASSERT_TRUE(hal_usb_is_connected());
}

void test_usb_initialization_failure(void) {
    _hal_usb_mock_inject_init_fail(true);
    TEST_ASSERT_EQUAL_INT(USB_ERR_INIT, hal_usb_init());
    TEST_ASSERT_FALSE(hal_usb_is_connected());
}

void test_usb_transmit_data(void) {
    const char *test_msg = "Hello STM32H5 USBX!";
    uint8_t rx_buf[64];
    
    hal_usb_init();
    TEST_ASSERT_EQUAL_INT(USB_OK, hal_usb_transmit((uint8_t *)test_msg, strlen(test_msg)));
    
    uint16_t tx_len = _hal_usb_mock_get_tx_data(rx_buf);
    TEST_ASSERT_EQUAL_INT(strlen(test_msg), tx_len);
    TEST_ASSERT_EQUAL_MEMORY(test_msg, rx_buf, tx_len);
}

void test_usb_is_connected_state(void) {
    TEST_ASSERT_FALSE(hal_usb_is_connected());
    hal_usb_init();
    TEST_ASSERT_TRUE(hal_usb_is_connected());
    _hal_usb_mock_set_connected(false);
    TEST_ASSERT_FALSE(hal_usb_is_connected());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_usb_initialization_success);
    RUN_TEST(test_usb_initialization_failure);
    RUN_TEST(test_usb_transmit_data);
    RUN_TEST(test_usb_is_connected_state);
    return UNITY_END();
}
