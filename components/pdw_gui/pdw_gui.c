#include "pdw_gui.h"

#include <esp_log.h>

#include "driver/spi_master.h"
#include "esp_lcd_gc9a01.h"
#include "esp_lvgl_port.h"

const char *TAG = "pdw_gui";

#define PDW_GUI_SPI_HOST SPI2_HOST
#define PDW_GUI_CLK_PIN CONFIG_PDW_LCD_CLK_PIN_NUM
#define PDW_GUI_MOSI_PIN CONFIG_PDW_LCD_MOSI_PIN_NUM
#define PDW_GUI_H_RES CONFIG_PDW_LCD_H_RES
#define PDW_GUI_CS_PIN CONFIG_PDW_LCD_CS_PIN_NUM
#define PDW_GUI_DC_PIN CONFIG_PDW_LCD_DC_PIN_NUM
#define PDW_GUI_PIXEL_CLK_HZ CONFIG_PDW_LCD_PIXEL_CLK_FREQ
#define PDW_GUI_CMD_BITS (8)
#define PDW_GUI_PARAM_BITS (8)

int pdw_gui_create(void) {
  ESP_LOGI(TAG, "Initialize SPI bus");

  const spi_bus_config_t bus_config = GC9A01_PANEL_BUS_SPI_CONFIG(
      CONFIG_PDW_LCD_CLK_PIN_NUM, CONFIG_PDW_LCD_MOSI_PIN_NUM,
      CONFIG_PDW_LCD_H_RES * 80 * sizeof(uint16_t));

  ESP_ERROR_CHECK(
      spi_bus_initialize(PDW_GUI_SPI_HOST, &bus_config, SPI_DMA_CH_AUTO));

  ESP_LOGI(TAG, "Install pannel IO");

  esp_lcd_panel_io_handle_t io_handle = NULL;

  const esp_lcd_panel_io_spi_config_t io_config = {
      .dc_gpio_num = PDW_GUI_DC_PIN,
      .cs_gpio_num = PDW_GUI_CS_PIN,
      .pclk_hz = PDW_GUI_PIXEL_CLK_HZ,
      .lcd_cmd_bits = PDW_GUI_CMD_BITS,
      .lcd_param_bits = PDW_GUI_PARAM_BITS,
      .spi_mode = 0,
      .trans_queue_depth = 10,
  };
  ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi(
      (esp_lcd_spi_bus_handle_t)PDW_GUI_SPI_HOST, &io_config, &io_handle));

  return 0;
}

int pdw_gui_destroy(void) { return 0; }
