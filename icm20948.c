#include <stdio.h>
#include <math.h>
#include "icm20948.h"
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <fcntl.h>

#define RAD_TO_DEG 57.27272727f /*!< Radians to degrees */



const uint32_t spi_speed = 10000000;
const uint8_t spi_bits = 8;
const uint16_t spi_delay = 0;
const uint8_t spi_mode = SPI_MODE_3;
static int icm20948_write_i2c(icm20948_handle_t sensor,
                                const uint8_t reg_start_addr,
                                const uint8_t data_buf) {
	int ret;
	const icm20948_dev_t *sens = sensor;
	uint8_t write_buf[2];

	write_buf[0] = reg_start_addr;
	write_buf[1] = data_buf;
    ret = write(sens->fd, write_buf, 2);
    if (ret != 2) {
        fprintf(stderr, "%s Failed to write to the i2c bus.\n", sens->tag);
        return -1;
    }
    
	return 0;
}

static int icm20948_read_i2c(icm20948_handle_t sensor,
								const uint8_t reg_start_addr,
								uint8_t *const data_buf,
								const uint8_t data_len) {
	int ret;
	const icm20948_dev_t *sens = sensor;
    ret = write(sens->fd, &reg_start_addr, 1);
    if (ret != 1) {
        fprintf(stderr, "%s Failed to write to the i2c bus.\n", sens->tag);
        return -1;
    }
    ret = read(sens->fd, data_buf, data_len);
    if (ret != data_len) {
        fprintf(stderr, "%s Failed to read from the i2c bus.\n", sens->tag);
        return -1;
    }
	return 0;
}

static int icm20948_write_spi(icm20948_handle_t sensor,
								const uint8_t reg_start_addr,
								const uint8_t data_buf) {
	int ret;
	uint8_t write_buf[2];
	write_buf[0] = reg_start_addr;
	write_buf[1] = data_buf;
	const icm20948_dev_t *sens = sensor;

    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)write_buf,
        .rx_buf = 0,
        .len = 2,
        .speed_hz = spi_speed,
        .delay_usecs = spi_delay,
        .bits_per_word = spi_bits,
        .cs_change = 0,
    };
    
    ret = ioctl(sens->fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret < 0) {
        fprintf(stderr, "%s Failed to write to the SPI bus.\n", sens->tag);
        return -1;
    }
    
	return 0;
}

static int icm20948_read_spi(icm20948_handle_t sensor,
								const uint8_t reg_start_addr,
								uint8_t * data_buf,
								const uint8_t data_len) {
	int ret;
    uint8_t tx_buf[2] = {reg_start_addr | 0x80, 0x00};
    uint8_t rx_buf[7] = {0};
	const icm20948_dev_t *sens = sensor;

    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx_buf,
        .rx_buf = (unsigned long)rx_buf,
        .len = data_len + 1,
        .speed_hz = spi_speed,
        .delay_usecs = spi_delay,
        .bits_per_word = spi_bits,
        .cs_change = 0,
    };
    
    ret = ioctl(sens->fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret < 0) {
        fprintf(stderr, "%s Failed to read from the SPI bus.\n", sens->tag);
        return -1;
    }
    memcpy(data_buf, rx_buf + 1, data_len);
	return 0;
}

int icm20948_i2c_bus_init(icm20948_handle_t sensor, const char *dev_path, uint8_t dev_addr) {
	icm20948_dev_t *sens = sensor;
    int ret;
    sens->fd = open(dev_path, O_RDWR);
    if (sens->fd < 0) {
        fprintf(stderr, "%s Failed to open I2C device\n", sens->tag);
        return -1;
    }
    ret = ioctl(sens->fd, I2C_SLAVE, dev_addr);
    if(ret < 0) {
        fprintf(stderr, "%s Failed to set I2C device address\n", sens->tag);
        close(sens->fd);
        return -1;
    }
	sens->mode = ICM20948_MODE_I2C;
	sens->icm20948_read = icm20948_read_i2c;
	sens->icm20948_write = icm20948_write_i2c;
    fprintf(stdout, "%s I2C bus and device initialized successfully\n", sens->tag);
	return ret;
}
int icm20948_spi_bus_init(icm20948_handle_t sensor, const char *dev_path) {
	icm20948_dev_t *sens = sensor;
	// 配置 SPI 总线
	int ret;
    sens->fd = open(dev_path, O_RDWR);
    if (sens->fd < 0) {
        fprintf(stderr, "%s Failed to open SPI device\n", sens->tag);
        return -1;
    }
    ret = ioctl(sens->fd, SPI_IOC_WR_MODE, &spi_mode);
    if (ret < 0) {
        fprintf(stderr, "%s Failed to set SPI mode\n", sens->tag);
        close(sens->fd);
        return -1;
    }
    ret = ioctl(sens->fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bits);
    if (ret < 0) {
        fprintf(stderr, "%s Failed to set SPI bits per word\n", sens->tag);
        close(sens->fd);
        return -1;
    }
    ret = ioctl(sens->fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed);
    if (ret < 0) {
        fprintf(stderr, "%s Failed to set SPI speed\n", sens->tag);
        close(sens->fd);
        return -1;
    }
	sens->mode = ICM20948_MODE_SPI;
	sens->icm20948_read = icm20948_read_spi;
	sens->icm20948_write = icm20948_write_spi;
    fprintf(stdout, "%s SPI bus and device initialized successfully\n", sens->tag);
	return ret;
}

icm20948_handle_t icm20948_create(icm20948_data_t *data, char* tag) {
	icm20948_dev_t *sensor = (icm20948_dev_t *)calloc(1, sizeof(icm20948_dev_t));
	if (!sensor) {
		fprintf(stderr,"%s Memory allocation failed\n", tag);
		return NULL;
	}

	// 参数初始化
    sensor->tag = tag;
	sensor->data = data;
	sensor->bank = -1;
	sensor->KalmanX = (Kalman_t){.Q_angle = 0.001f,.Q_bias = 0.003f,.R_measure = 0.03f};
	sensor->KalmanY = (Kalman_t){.Q_angle = 0.001f,.Q_bias = 0.003f,.R_measure = 0.03f};
	sensor->KalmanZ = (Kalman_t){.Q_angle = 0.001f,.Q_bias = 0.003f,.R_measure = 0.03f};

	return (icm20948_handle_t)sensor;
}

void icm20948_delete(icm20948_handle_t sensor)
{
	icm20948_dev_t *sens = sensor;
	free(sens);
}

int icm20948_configure(icm20948_handle_t icm20948, icm20948_acce_fs_t acce_fs, icm20948_gyro_fs_t gyro_fs)
{
    int ret;
	icm20948_dev_t *sens = icm20948;

    ret = icm20948_reset(icm20948);
    if (ret != 0){
        fprintf(stderr, "%s Reset failed!\n", sens->tag);
        return ret;
    }

    usleep(20000);

    ret = icm20948_wake_up(icm20948);
    if (ret != 0) {
        fprintf(stderr, "%s Wake up failed!\n", sens->tag);
        return ret;
    }

    ret = icm20948_set_bank(icm20948, 0);
    if (ret != 0) {
        fprintf(stderr, "%s Set bank failed!\n", sens->tag);
        return ret;
    }

    uint8_t device_id;
    ret = icm20948_get_deviceid(icm20948, &device_id);
    if (ret != 0){
        fprintf(stderr, "%s Get device id failed!\n", sens->tag);
        return ret;
    }
    fprintf(stdout, "%s Device ID:0x%02X\n", sens->tag, device_id);
    if (device_id != ICM20948_WHO_AM_I_VAL){
        fprintf(stderr, "%s Device id mismatch!\n", sens->tag);
        return -1;
    }

    fprintf(stderr, "%s Device id correct!\n", sens->tag);

    ret = icm20948_set_gyro_fs(icm20948, gyro_fs);
    if (ret != 0){
        return ret;
    }

    ret = icm20948_set_acce_fs(icm20948, acce_fs);
    if (ret != 0){
        return ret;
    }

	ret = icm20948_set_bank(icm20948, 0);
	if (ret != 0) {
		return ret;
	}
    return ret;
}

int icm20948_get_deviceid(icm20948_handle_t sensor, uint8_t *const deviceid)
{
	icm20948_dev_t *sens = sensor;
	return sens->icm20948_read(sensor, ICM20948_WHO_AM_I, deviceid, 1);
}

int icm20948_wake_up(icm20948_handle_t sensor)
{
	icm20948_dev_t *sens = sensor;
	int ret;
	uint8_t tmp;
	ret = sens->icm20948_read(sensor, ICM20948_PWR_MGMT_1, &tmp, 1);
	if (0 != ret) {
		return ret;
	}
	tmp &= (~0x40);
	ret = sens->icm20948_write(sensor, ICM20948_PWR_MGMT_1, tmp);
	return ret;
}

int icm20948_sleep(icm20948_handle_t sensor)
{
	icm20948_dev_t *sens = sensor;
	int ret;
	uint8_t tmp;
	ret = sens->icm20948_read(sensor, ICM20948_PWR_MGMT_1, &tmp, 1);
	if (0 != ret) {
		return ret;
	}
	tmp |= 0x40;
	ret = sens->icm20948_write(sensor, ICM20948_PWR_MGMT_1, tmp);
	return ret;
}

int icm20948_reset(icm20948_handle_t sensor)
{
	int ret;
	uint8_t tmp;
	icm20948_dev_t *sens = sensor;

	ret = sens->icm20948_read(sensor, ICM20948_PWR_MGMT_1, &tmp, 1);
	if (ret != 0)
		return ret;
	tmp |= 0x80;
	ret = sens->icm20948_write(sensor, ICM20948_PWR_MGMT_1, tmp);
	if (ret != 0)
		return ret;

	return ret;
}

int icm20948_set_bank(icm20948_handle_t sensor, uint8_t bank)
{
	int ret;
	icm20948_dev_t *sens = sensor;
	if (bank > 3)
		return -1;
	bank = (bank << 4) & 0x30;
	ret = sens->icm20948_write(sensor, ICM20948_REG_BANK_SEL, bank);
	if (ret != 0)
		return ret;
	sens->bank = bank;
	return ret;
}

float icm20948_get_acce_sensitivity(icm20948_handle_t sensor)
{
	icm20948_dev_t *sens = sensor;
	icm20948_acce_fs_t acce_fs = sens->acce_fs;
	switch (acce_fs){
	case ACCE_FS_2G:
		return 16384;
	case ACCE_FS_4G:
		return 8192;
	case ACCE_FS_8G:
		return 4096;
	case ACCE_FS_16G:
		return 2048;
	}
	return 16384;
}

float icm20948_get_gyro_sensitivity(icm20948_handle_t sensor){
	icm20948_dev_t *sens = sensor;
	icm20948_gyro_fs_t gyro_fs = sens->gyro_fs;
	switch (gyro_fs){
	case GYRO_FS_250DPS:
		return 131;
	case GYRO_FS_500DPS:
		return 65.5f;
	case GYRO_FS_1000DPS:
		return 32.8f;
	case GYRO_FS_2000DPS:
		return 16.4f;
	}
	return 131;
}

int icm20948_get_acce(icm20948_handle_t sensor)
{
	icm20948_dev_t *sens = (icm20948_dev_t *)sensor;
	uint8_t data_rd[6];
	float acce_sensitivity = icm20948_get_acce_sensitivity(sensor);
	if (sens->bank != 0){
		icm20948_set_bank(sensor, 0);
	}
	int ret = sens->icm20948_read(sensor, ICM20948_ACCEL_OUT, data_rd, sizeof(data_rd));

	sens->data->ax_raw = (int16_t)((data_rd[0] << 8) + (data_rd[1]));
	sens->data->ay_raw = (int16_t)((data_rd[2] << 8) + (data_rd[3]));
	sens->data->az_raw = (int16_t)((data_rd[4] << 8) + (data_rd[5]));

	sens->data->ax = (float)sens->data->ax_raw / acce_sensitivity;
	sens->data->ay = (float)sens->data->ay_raw / acce_sensitivity;
	sens->data->az = (float)sens->data->az_raw / acce_sensitivity;

	return ret;
}

int icm20948_get_gyro(icm20948_handle_t sensor)
{
	icm20948_dev_t *sens = (icm20948_dev_t *)sensor;
	uint8_t data_rd[6];
	float gyro_sensitivity = icm20948_get_gyro_sensitivity(sensor);
	if (sens->bank != 0){
		icm20948_set_bank(sensor, 0);
	}
	int ret = sens->icm20948_read(sensor, ICM20948_GYRO_OUT, data_rd, sizeof(data_rd));

	sens->data->gx_raw = (int16_t)((data_rd[0] << 8) + (data_rd[1]));
	sens->data->gy_raw = (int16_t)((data_rd[2] << 8) + (data_rd[3]));
	sens->data->gz_raw = (int16_t)((data_rd[4] << 8) + (data_rd[5]));

	sens->data->gx = (float)sens->data->gx_raw / gyro_sensitivity;
	sens->data->gy = (float)sens->data->gy_raw / gyro_sensitivity;
	sens->data->gz = (float)sens->data->gz_raw / gyro_sensitivity;

	return ret;
}

void icm20948_get_angle(icm20948_handle_t sensor, float dt)
{
	icm20948_dev_t *sens = sensor;
	float roll;
	float roll_sqrt = sqrtf(powf(sens->data->ax_raw, 2) + powf(sens->data->az_raw, 2));
	if (roll_sqrt != 0.0)
	{
		roll = atanf((float)sens->data->ay_raw / roll_sqrt) * RAD_TO_DEG;
	}
	else
	{
		roll = 0.0f;
	}
	float pitch = atan2f((float)-sens->data->ax_raw, (float)sens->data->az_raw) * RAD_TO_DEG;
	if ((pitch < -90 && sens->data->angley > 90) || (pitch > 90 && sens->data->angley < -90))
	{
		sens->KalmanY.angle = pitch;
		sens->data->angley = pitch;
	}
	else
	{
		sens->data->angley = icm20948_kalman_get_angle(&sens->KalmanY, pitch, sens->data->gy, dt);
	}
	if (fabsf(sens->data->angley) > 90)
		sens->data->gx = -sens->data->gx;
	sens->data->anglex = icm20948_kalman_get_angle(&sens->KalmanX, roll, sens->data->gx, dt);

	float yaw_inc = sens->data->gz * dt;
	if(fabsf(yaw_inc) < 1000) {  // drop abnormal value
		sens->data->anglez = icm20948_kalman_get_angle(&sens->KalmanZ, sens->data->anglez + yaw_inc, sens->data->gz, dt);
	}
}

float icm20948_kalman_get_angle(Kalman_t *Kalman, float newAngle, float newRate, float dt)
{
	float rate = newRate - Kalman->bias;
	Kalman->angle += dt * rate;

	Kalman->P[0][0] += dt * (dt * Kalman->P[1][1] - Kalman->P[0][1] - Kalman->P[1][0] + Kalman->Q_angle);
	Kalman->P[0][1] -= dt * Kalman->P[1][1];
	Kalman->P[1][0] -= dt * Kalman->P[1][1];
	Kalman->P[1][1] += Kalman->Q_bias * dt;

	float S = Kalman->P[0][0] + Kalman->R_measure;
	float K[2];
	K[0] = Kalman->P[0][0] / S;
	K[1] = Kalman->P[1][0] / S;

	float y = newAngle - Kalman->angle;
	Kalman->angle += K[0] * y;
	Kalman->bias += K[1] * y;

	float P00_temp = Kalman->P[0][0];
	float P01_temp = Kalman->P[0][1];

	Kalman->P[0][0] -= K[0] * P00_temp;
	Kalman->P[0][1] -= K[0] * P01_temp;
	Kalman->P[1][0] -= K[1] * P00_temp;
	Kalman->P[1][1] -= K[1] * P01_temp;

	return Kalman->angle;
}

int icm20948_get_temp(icm20948_handle_t sensor)
{
	icm20948_dev_t *sens = sensor;
	if (sens->bank != 0){
		icm20948_set_bank(sensor, 0);
	}
	uint8_t data_rd[2];
	int ret = sens->icm20948_read(sensor, ICM20948_TEMP_OUT, data_rd, sizeof(data_rd));

	int16_t temp_raw = (int16_t)((data_rd[0] << 8) + (data_rd[1]));
	float temp = (float)temp_raw / 333.87f + 21.0f;
	// lowpass filter
	sens->data->temp = 0.9f * sens->data->temp + (1 - 0.9f) * temp;

	return ret;
}

void icm20948_get_all(icm20948_handle_t sensor, float dt)
{
	icm20948_get_acce(sensor);
	icm20948_get_gyro(sensor);
	icm20948_get_angle(sensor, dt);
	icm20948_get_temp(sensor);
}

int icm20948_check_online(icm20948_handle_t sensor)
{
    icm20948_dev_t *sens = sensor;
    uint8_t device_id;
    icm20948_get_deviceid(sensor, &device_id);
    if (device_id != ICM20948_WHO_AM_I_VAL) {
        fprintf(stderr, "%s Device offline!\n", sens->tag);
        return -1;
    }
    return 0;
}

int icm20948_set_gyro_fs(icm20948_handle_t sensor, icm20948_gyro_fs_t gyro_fs)
{
	int ret;
	uint8_t tmp;
	icm20948_dev_t *sens = sensor;

	ret = icm20948_set_bank(sensor, 2);
	if (ret != 0)
		return ret;

	ret = sens->icm20948_read(sensor, ICM20948_GYRO_CONFIG_1, &tmp, 1);

	if (ret != 0)
		return ret;
	tmp &= 0x09;
	tmp |= (gyro_fs << 1);

	ret = sens->icm20948_write(sensor, ICM20948_GYRO_CONFIG_1, tmp);
	if (ret != 0) {
		fprintf(stderr, "%s Set gyro fs failed!\n", sens->tag);
		return ret;
	}
	// if set gyro fs success, record to sensor
	sens->gyro_fs = gyro_fs;
	return ret;
}

int icm20948_set_acce_fs(icm20948_handle_t sensor, icm20948_acce_fs_t acce_fs)
{
	int ret;
	uint8_t tmp;
	icm20948_dev_t *sens = sensor;

	ret = icm20948_set_bank(sensor, 2);
	if (ret != 0)
		return ret;

	ret = sens->icm20948_read(sensor, ICM20948_ACCEL_CONFIG, &tmp, 1);


	if (ret != 0)
		return ret;
	tmp &= 0x09;
	tmp |= (acce_fs << 1);


	ret = sens->icm20948_write(sensor, ICM20948_ACCEL_CONFIG, tmp);
	if (ret != 0) {
		fprintf(stderr, "%s Set acce fs failed!\n", sens->tag);
		return ret;
	}
	// if set acce fs success, record to sensor
	sens->acce_fs = acce_fs;
	return ret;
}

int icm20948_get_acce_fs(icm20948_handle_t sensor, icm20948_acce_fs_t *acce_fs)
{
	int ret;
	uint8_t tmp;
	icm20948_dev_t *sens = sensor;

	ret = icm20948_set_bank(sensor, 2);
	if (ret != 0)
		return ret;

	ret = sens->icm20948_read(sensor, ICM20948_ACCEL_CONFIG, &tmp, 1);

	tmp &= 0x06;
	tmp >>= 1;
	*acce_fs = tmp;
	return ret;
}


int icm20948_set_acce_dlpf(icm20948_handle_t sensor, icm20948_dlpf_t dlpf_acce)
{
	int ret;
	uint8_t tmp;
	icm20948_dev_t *sens = sensor;

	ret = icm20948_set_bank(sensor, 2);
	if (ret != 0)
		return -1;

	ret = sens->icm20948_read(sensor, ICM20948_ACCEL_CONFIG, &tmp, 1);
	if (ret != 0)
		return -1;

	tmp &= 0xC7;
	tmp |= dlpf_acce << 3;

	ret = sens->icm20948_write(sensor, ICM20948_ACCEL_CONFIG, tmp);
	if (ret != 0)
		return -1;

	return ret;
}

int icm20948_set_gyro_dlpf(icm20948_handle_t sensor, icm20948_dlpf_t dlpf_gyro)
{
	int ret;
	uint8_t tmp;
	icm20948_dev_t *sens = sensor;

	ret = icm20948_set_bank(sensor, 2);
	if (ret != 0)
		return -1;

	ret = sens->icm20948_read(sensor, ICM20948_GYRO_CONFIG_1, &tmp, 1);
	if (ret != 0)
		return -1;

	tmp &= 0xC7;
	tmp |= dlpf_gyro << 3;

	ret = sens->icm20948_write(sensor, ICM20948_GYRO_CONFIG_1, tmp);
	if (ret != 0)
		return -1;

	return ret;
}

int icm20948_enable_dlpf(icm20948_handle_t sensor, bool enable)
{
	int ret;
	uint8_t tmp;
	icm20948_dev_t *sens = sensor;

	ret = icm20948_set_bank(sensor, 2);
	if (ret != 0)
		return -1;

	ret = sens->icm20948_read(sensor, ICM20948_ACCEL_CONFIG, &tmp, 1);
	if (ret != 0)
		return -1;

	if (enable)
		tmp |= 0x01;
	else
		tmp &= 0xFE;

	ret = sens->icm20948_write(sensor, ICM20948_ACCEL_CONFIG, tmp);
	if (ret != 0)
		return -1;

	ret = sens->icm20948_read(sensor, ICM20948_GYRO_CONFIG_1, &tmp, 1);
	if (ret != 0)
		return -1;

	if (enable)
		tmp |= 0x01;
	else
		tmp &= 0xFE;

	ret = sens->icm20948_write(sensor, ICM20948_GYRO_CONFIG_1, tmp);
	if (ret != 0)
		return -1;

	return ret;
}
