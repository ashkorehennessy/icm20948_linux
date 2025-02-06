#include "icm20948.h"
#include <stdio.h>
#include <unistd.h>


int main() {
    int ret;
    icm20948_data_t icm20948_data;
    icm20948_handle_t icm20948 = icm20948_create(&icm20948_data, "icm20948");
//     ret = icm20948_i2c_bus_init(icm20948, "/dev/i2c-0", 0x68);
    ret = icm20948_spi_bus_init(icm20948, "/dev/spidev1.0");
    if(ret != 0) goto OUT;
    ret = icm20948_configure(icm20948, ACCE_FS_8G, GYRO_FS_2000DPS);
    if(ret != 0) goto OUT;

    for(int i = 0; i < 10000; i++){
        icm20948_get_acce(icm20948);
        icm20948_get_gyro(icm20948);
        icm20948_get_angle(icm20948, 0.01f);  // dt 10ms
        icm20948_get_temp(icm20948);
        printf("Angle:%f,%f,%f\n", icm20948_data.anglex, icm20948_data.angley, icm20948_data.anglez);
        if(icm20948_check_online(icm20948) != 0){
            icm20948_configure(icm20948, ACCE_FS_8G, GYRO_FS_2000DPS);
        }
        usleep(10000);  // 10ms
    }
OUT:
    icm20948_delete(icm20948);
    return 0;
}
