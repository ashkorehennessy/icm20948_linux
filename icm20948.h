#ifndef __ICM20948_H__
#define __ICM20948_H__

#include <stdbool.h>
#include "stdint.h"
#define ICM20948_I2C_ADDRESS          0x69
#define ICM20948_I2C_ADDRESS_1        0x68
#define ICM20948_WHO_AM_I_VAL         0xEA
#define ICM20948_MAG_ADDRESS          0x0C
#define ICM20948_MAG_WHO_AM_I_1       0x4809
#define ICM20948_MAG_WHO_AM_I_2       0x0948

/* Registers ICM20948 USER BANK 0*/
#define ICM20948_WHO_AM_I             0x00
#define ICM20948_USER_CTRL            0x03
#define ICM20948_LP_CONFIG            0x05
#define ICM20948_PWR_MGMT_1           0x06
#define ICM20948_PWR_MGMT_2           0x07
#define ICM20948_INT_PIN_CFG          0x0F
#define ICM20948_INT_ENABLE           0x10
#define ICM20948_INT_ENABLE_1         0x11
#define ICM20948_INT_ENABLE_2         0x12
#define ICM20948_INT_ENABLE_3         0x13
#define ICM20948_I2C_MST_STATUS       0x17
#define ICM20948_INT_STATUS           0x19
#define ICM20948_INT_STATUS_1         0x1A
#define ICM20948_INT_STATUS_2         0x1B
#define ICM20948_INT_STATUS_3         0x1C
#define ICM20948_DELAY_TIME_H         0x28
#define ICM20948_DELAY_TIME_L         0x29
#define ICM20948_ACCEL_OUT            0x2D // accel data registers begin
#define ICM20948_GYRO_OUT             0x33 // gyro data registers begin
#define ICM20948_TEMP_OUT             0x39
#define ICM20948_EXT_SLV_SENS_DATA_00 0x3B
#define ICM20948_EXT_SLV_SENS_DATA_01 0x3C
#define ICM20948_FIFO_EN_1            0x66
#define ICM20948_FIFO_EN_2            0x67
#define ICM20948_FIFO_RST             0x68
#define ICM20948_FIFO_MODE            0x69
#define ICM20948_FIFO_COUNT           0x70
#define ICM20948_FIFO_R_W             0x72
#define ICM20948_DATA_RDY_STATUS      0x74
#define ICM20948_FIFO_CFG             0x76

/* Registers ICM20948 USER BANK 1*/
#define ICM20948_SELF_TEST_X_GYRO     0x02
#define ICM20948_SELF_TEST_Y_GYRO     0x03
#define ICM20948_SELF_TEST_Z_GYRO     0x04
#define ICM20948_SELF_TEST_X_ACCEL    0x0E
#define ICM20948_SELF_TEST_Y_ACCEL    0x0F
#define ICM20948_SELF_TEST_Z_ACCEL    0x10
#define ICM20948_XA_OFFS_H            0x14
#define ICM20948_XA_OFFS_L            0x15
#define ICM20948_YA_OFFS_H            0x17
#define ICM20948_YA_OFFS_L            0x18
#define ICM20948_ZA_OFFS_H            0x1A
#define ICM20948_ZA_OFFS_L            0x1B
#define ICM20948_TIMEBASE_CORR_PLL    0x28

/* Registers ICM20948 USER BANK 2*/
#define ICM20948_GYRO_SMPLRT_DIV      0x00
#define ICM20948_GYRO_CONFIG_1        0x01
#define ICM20948_GYRO_CONFIG_2        0x02
#define ICM20948_XG_OFFS_USRH         0x03
#define ICM20948_XG_OFFS_USRL         0x04
#define ICM20948_YG_OFFS_USRH         0x05
#define ICM20948_YG_OFFS_USRL         0x06
#define ICM20948_ZG_OFFS_USRH         0x07
#define ICM20948_ZG_OFFS_USRL         0x08
#define ICM20948_ODR_ALIGN_EN         0x09
#define ICM20948_ACCEL_SMPLRT_DIV_1   0x10
#define ICM20948_ACCEL_SMPLRT_DIV_2   0x11
#define ICM20948_ACCEL_INTEL_CTRL     0x12
#define ICM20948_ACCEL_WOM_THR        0x13
#define ICM20948_ACCEL_CONFIG         0x14
#define ICM20948_ACCEL_CONFIG_2       0x15
#define ICM20948_FSYNC_CONFIG         0x52
#define ICM20948_TEMP_CONFIG          0x53
#define ICM20948_MOD_CTRL_USR         0x54

/* Registers ICM20948 USER BANK 3*/
#define ICM20948_I2C_MST_ODR_CFG      0x00
#define ICM20948_I2C_MST_CTRL         0x01
#define ICM20948_I2C_MST_DELAY_CTRL   0x02
#define ICM20948_I2C_SLV0_ADDR        0x03
#define ICM20948_I2C_SLV0_REG         0x04
#define ICM20948_I2C_SLV0_CTRL        0x05
#define ICM20948_I2C_SLV0_DO          0x06
#define ICM20948_I2C_SLV4_ADDR        0x13
#define ICM20948_I2C_SLV4_REG         0x14
#define ICM20948_I2C_SLV4_CTRL        0x15
#define ICM20948_I2C_SLV4_DO          0x16
#define ICM20948_I2C_SLV4_DI          0x17

/* Registers AK09916 */
#define ICM20948_MAG_WIA_1                 0x00 // Who I am, Company ID
#define ICM20948_MAG_WIA_2                 0x01 // Who I am, Device ID
#define ICM20948_MAG_STATUS_1              0x10
#define ICM20948_MAG_HXL                   0x11
#define ICM20948_MAG_HXH                   0x12
#define ICM20948_MAG_HYL                   0x13
#define ICM20948_MAG_HYH                   0x14
#define ICM20948_MAG_HZL                   0x15
#define ICM20948_MAG_HZH                   0x16
#define ICM20948_MAG_STATUS_2              0x18
#define ICM20948_MAG_CNTL_2                0x31
#define ICM20948_MAG_CNTL_3                0x32

/* Register Bits */
#define ICM20948_RESET                     0x80
#define ICM20948_I2C_MST_EN                0x20
#define ICM20948_SLEEP                     0x40
#define ICM20948_LP_EN                     0x20
#define ICM20948_BYPASS_EN                 0x02
#define ICM20948_GYR_EN                    0x07
#define ICM20948_ACC_EN                    0x38
#define ICM20948_FIFO_EN                   0x40
#define ICM20948_INT1_ACTL                 0x80
#define ICM20948_INT_1_LATCH_EN            0x20
#define ICM20948_ACTL_FSYNC                0x08
#define ICM20948_INT_ANYRD_2CLEAR          0x10
#define ICM20948_FSYNC_INT_MODE_EN         0x06
#define ICM20948_I2C_SLVX_EN               0x80
#define ICM20948_MAG_16_BIT                     0x10
#define ICM20948_MAG_OVF                        0x08
#define ICM20948_MAG_READ                       0x80

/* Registers ICM20948 ALL BANKS */
#define ICM20948_REG_BANK_SEL              0x7F

typedef enum {
	ACCE_FS_2G = 0,  /*!< Accelerometer full scale range is +/- 2g */
	ACCE_FS_4G = 1,  /*!< Accelerometer full scale range is +/- 4g */
	ACCE_FS_8G = 2,  /*!< Accelerometer full scale range is +/- 8g */
	ACCE_FS_16G = 3, /*!< Accelerometer full scale range is +/- 16g */
} icm20948_acce_fs_t;

typedef enum {
	GYRO_FS_250DPS = 0,  /*!< Gyroscope full scale range is +/- 250 degree per sencond */
	GYRO_FS_500DPS = 1,  /*!< Gyroscope full scale range is +/- 500 degree per sencond */
	GYRO_FS_1000DPS = 2, /*!< Gyroscope full scale range is +/- 1000 degree per sencond */
	GYRO_FS_2000DPS = 3, /*!< Gyroscope full scale range is +/- 2000 degree per sencond */
} icm20948_gyro_fs_t;

typedef enum {
	INTERRUPT_PIN_ACTIVE_HIGH = 0, /*!< The icm20948 sets its INT pin HIGH on interrupt */
	INTERRUPT_PIN_ACTIVE_LOW = 1   /*!< The icm20948 sets its INT pin LOW on interrupt */
} icm20948_int_pin_active_level_t;

typedef enum {
	INTERRUPT_PIN_PUSH_PULL = 0, /*!< The icm20948 configures its INT pin as push-pull */
	INTERRUPT_PIN_OPEN_DRAIN = 1 /*!< The icm20948 configures its INT pin as open drain*/
} icm20948_int_pin_mode_t;

typedef enum {
	INTERRUPT_LATCH_50US = 0,         /*!< The icm20948 produces a 50 microsecond pulse on interrupt */
	INTERRUPT_LATCH_UNTIL_CLEARED = 1 /*!< The icm20948 latches its INT pin to its active level, until
	                                     interrupt is cleared */
} icm20948_int_latch_t;

typedef enum {
	INTERRUPT_CLEAR_ON_ANY_READ = 0,   /*!< INT_STATUS register bits are cleared on any register read */
	INTERRUPT_CLEAR_ON_STATUS_READ = 1 /*!< INT_STATUS register bits are cleared
	                                      only by reading INT_STATUS value*/
} icm20948_int_clear_t;

typedef enum {
	ICM20948_DLPF_0,
	ICM20948_DLPF_1,
	ICM20948_DLPF_2,
	ICM20948_DLPF_3,
	ICM20948_DLPF_4,
	ICM20948_DLPF_5,
	ICM20948_DLPF_6,
	ICM20948_DLPF_7,
	ICM20948_DLPF_OFF
} icm20948_dlpf_t;

typedef enum
{
    ICM20948_MAG_PWR_DOWN           = 0x00,
    ICM20948_MAG_TRIGGER_MODE       = 0x01,
    ICM20948_MAG_CONT_MODE_10HZ     = 0x02,
    ICM20948_MAG_CONT_MODE_20HZ     = 0x04,
    ICM20948_MAG_CONT_MODE_50HZ     = 0x06,
    ICM20948_MAG_CONT_MODE_100HZ    = 0x08
} icm20948_mag_mode_t;

typedef enum {
	ICM20948_MODE_I2C,
	ICM20948_MODE_SPI
} icm20948_mode_t;

extern const uint8_t icm20948_DATA_RDY_INT_BIT;      /*!< DATA READY interrupt bit */
extern const uint8_t icm20948_I2C_MASTER_INT_BIT;    /*!< I2C MASTER interrupt bit               */
extern const uint8_t icm20948_FIFO_OVERFLOW_INT_BIT; /*!< FIFO Overflow interrupt bit */
extern const uint8_t icm20948_MOT_DETECT_INT_BIT;    /*!< MOTION DETECTION interrupt bit         */
extern const uint8_t icm20948_ALL_INTERRUPTS;        /*!< All interrupts supported by icm20948    */

typedef struct {
	int16_t ax_raw;
	int16_t ay_raw;
	int16_t az_raw;
	int16_t gx_raw;
	int16_t gy_raw;
	int16_t gz_raw;
	float ax;
	float ay;
	float az;
	float gx;
	float gy;
	float gz;
	float anglex;
	float angley;
	float anglez;
	float temp;

} icm20948_data_t;

typedef void *icm20948_handle_t;

typedef int (*icm20948_write_function_t)(icm20948_handle_t sensor, const uint8_t reg_start_addr, const uint8_t data_buf);
typedef int (*icm20948_read_function_t)(icm20948_handle_t sensor, const uint8_t reg_start_addr, uint8_t *const data_buf, const uint8_t data_len);


// Kalman structure
typedef struct
{
	float Q_angle;
	float Q_bias;
	float R_measure;
	float angle;
	float bias;
	float P[2][2];
} Kalman_t;

typedef struct {
    int fd;
	char *tag;
	uint16_t dev_addr;
	int bank;
	Kalman_t KalmanX;
	Kalman_t KalmanY;
	Kalman_t KalmanZ;
	icm20948_acce_fs_t acce_fs;
	icm20948_gyro_fs_t gyro_fs;
	icm20948_data_t *data;
	icm20948_mode_t mode;
	icm20948_read_function_t icm20948_read;
	icm20948_write_function_t icm20948_write;
} icm20948_dev_t;


/**
 * @brief Initialize the I2C bus and device
*
 * @param sensor object handle of icm20948
 * @param dev_path I2C device path
 * @param dev_addr I2C device address, 0x68 or 0x69
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_i2c_bus_init(icm20948_handle_t sensor, const char *dev_path, uint8_t dev_addr);

/**
 * @brief Initialize the SPI bus and device
 *
 * @param sensor object handle of icm20948
 * @param dev_path SPI device path
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_spi_bus_init(icm20948_handle_t sensor, const char *dev_path);

/**
 * @brief Create and init sensor object and return a sensor handle
 *
 * @param data sensor data structure
 * @param tag sensor tag for logging
 *
 * @return
 *     - NULL Fail
 *     - Others Success
 */
icm20948_handle_t icm20948_create(icm20948_data_t *data, char* tag);

/**
 * @brief Configure the sensor with the given full scale range
 *
 * @param icm20948 object handle of icm20948
 * @param acce_fs accelerometer full scale range
 * @param gyro_fs gyroscope full scale range
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_configure(icm20948_handle_t icm20948, icm20948_acce_fs_t acce_fs, icm20948_gyro_fs_t gyro_fs);

/**
 * @brief Delete and release a sensor object
 *
 * @param sensor object handle of icm20948
 */
void icm20948_delete(icm20948_handle_t sensor);

/**
 * @brief Get device identification of icm20948
 *
 * @param sensor object handle of icm20948
 * @param deviceid a pointer of device ID
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_get_deviceid(icm20948_handle_t sensor, uint8_t *deviceid);

/**
 * @brief Wake up icm20948
 *
 * @param sensor object handle of icm20948
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_wake_up(icm20948_handle_t sensor);

/**
 * @brief Enter sleep mode
 *
 * @param sensor object handle of icm20948
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_sleep(icm20948_handle_t sensor);

/**
 * @brief Set gyroscope full scale range
 *
 * @param sensor object handle of icm20948
 * @param gyro_fs gyroscope full scale range
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_set_gyro_fs(icm20948_handle_t sensor, icm20948_gyro_fs_t gyro_fs);

/**
 * @brief Get gyroscope full scale range
 *
 * @param sensor object handle of icm20948
 * @param gyro_fs gyroscope full scale range
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_get_gyro_fs(icm20948_handle_t sensor, icm20948_gyro_fs_t *gyro_fs);

/**
 * @brief Get gyroscope sensitivity
 *
 * @param sensor object handle of icm20948
 *
 * @return gyroscope sensitivity
 */
float icm20948_get_gyro_sensitivity(icm20948_handle_t sensor);

/**
 * @brief Read gyro values
 *
 * @param sensor object handle of icm20948
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_get_gyro(icm20948_handle_t sensor);

/**
 * @brief Set accelerometer full scale range
 *
 * @param sensor object handle of icm20948
 * @param acce_fs accelerometer full scale range
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_set_acce_fs(icm20948_handle_t sensor, icm20948_acce_fs_t acce_fs);

/**
 * @brief Get accelerometer full scale range
 *
 * @param sensor object handle of icm20948
 * @param acce_fs accelerometer full scale range
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_get_acce_fs(icm20948_handle_t sensor, icm20948_acce_fs_t *acce_fs);

/**
 * @brief Get accelerometer sensitivity
 *
 * @param sensor object handle of icm20948
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
float icm20948_get_acce_sensitivity(icm20948_handle_t sensor);
/**
 * @brief Read accelerometer measurements
 *
 * @param sensor object handle of icm20948
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_get_acce(icm20948_handle_t sensor);

/**
 * @brief get euler angle
 *
 * @param sensor object handle of icm20948
 * @param dt time interval per sample
 *
 */
void icm20948_get_angle(icm20948_handle_t sensor, float dt);

/**
 * @brief filter the angle using kalman filter
 *
 * @param Kalman kalman filter object
 * @param newAngle euler angle
 * @param newRate real gyroscope value
 * @param dt time interval per sample
 *
 */
float icm20948_kalman_get_angle(Kalman_t *Kalman, float newAngle, float newRate, float dt);

/**
 * @brief Read the temperature value
 *
 * @param sensor object handle of icm20948
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_get_temp(icm20948_handle_t sensor);

/**
 * @brief Read all sensor values
 *
 * @param sensor object handle of icm20948
 * @param dt time interval per sample
 *
 */
void icm20948_get_all(icm20948_handle_t sensor, float dt);

/**
 * @brief Reset the internal registers and restores the default settings
 *
 * @param sensor object handle of icm20948
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_reset(icm20948_handle_t sensor);

/**
 * @brief Waking the chip from sleep mode.
 *
 * @param sensor object handle of icm20948
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_wakeup(icm20948_handle_t sensor);

/**
 * @brief Select USER BANK.
 * 0: Select USER BANK 0.
 * 1: Select USER BANK 1.
 * 2: Select USER BANK 2.
 * 3: Select USER BANK 3.
 *
 * @param sensor object handle of icm20948
 * @param bank   user bank number
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_set_bank(icm20948_handle_t sensor, uint8_t bank);

/**
 * @brief Enable low pass filter for gyroscope and accelerometer.
 * true:  enable low pass filter.
 * false: bypass low pass filter.
 *
 * @param sensor object handle of icm20948
 * @param enable boolean variable whether to turn on or bypass the filter
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_enable_dlpf(icm20948_handle_t sensor, bool enable);

/**
 * @brief Configure low pass filter for accelerometer
 *
 * @param sensor      object handle of icm20948
 * @param dlpf_acce   dlpf configuration for accelerometer
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_set_acce_dlpf(icm20948_handle_t sensor, icm20948_dlpf_t dlpf_acce);

/**
 * @brief Configure low pass filter for gyroscope
 *
 * @param sensor      object handle of icm20948
 * @param dlpf_gyro   dlpf configuration for gyroscope
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_set_gyro_dlpf(icm20948_handle_t sensor, icm20948_dlpf_t dlpf_gyro);

/**
 * @brief Check if the sensor is online
 *
 * @param sensor object handle of icm20948
 *
 * @return
 *     - 0 Success
 *     - not 0 Fail
 */
int icm20948_check_online(icm20948_handle_t sensor);



#endif // !__ICM20948_H__
