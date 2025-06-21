#include "esp_err.h"
#include "pdw_gui.h"

void app_main(void) { ESP_ERROR_CHECK(pdw_gui_create()); }
