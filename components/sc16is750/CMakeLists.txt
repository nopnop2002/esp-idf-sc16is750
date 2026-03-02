set(component_srcs "sc16is750.c")

idf_component_register(
	SRCS "${component_srcs}"
	PRIV_REQUIRES driver esp_driver_spi esp_driver_i2c esp_driver_gpio
	INCLUDE_DIRS "."
)
