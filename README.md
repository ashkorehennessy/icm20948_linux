# ICM20948 linux driver

This is an userspace driver for the ICM20948 IMU, port from [icm20948_esp](https://github.com/ashkorehennessy/icm20948_esp)

Works: accelerometer, gyroscope, temperature

Tested on LS2K0300_99pai and EAIDK-310

Need root permission to access the device, or chmod 666 the device file

# Supports SPI and I2C

---

To use I2C:
```c
icm20948_i2c_bus_init(handle, "path_to_i2c");
```

To use SPI:
```c
icm20948_spi_bus_init(handle, "path_to_spi");
```

# Build example

Use CMake

```bash
mkdir build
cd build
cmake ..
make
```

Use gcc

```bash
gcc -o icm20948 icm20948.c main.c -lm
```

# Device tree configuration example:

---

For I2C:

```dts
&i2c1{
    status = "okay";
    clock-frequency = <400000>;
    pinctrl-names = "default";
    pinctrl-0 = <&i2c1_mux_m0>;
};
```

For SPI:

```dts
&spi1 {
	status = "okay";
	pinctrl-names = "default";
	pinctrl-0 = <&spi1_4bit>;
    spidev@0 {
        compatible = "rohm,dh2228fv";  // Remove warning
        reg = <0>;
        spi-max-frequency = <10000000>;
        spi-cpol;
        spi-cpha;
    };
};
```