//
//  Definitions.h
//  Serial App
//
//  Created by Orlando Chen on 2021/4/29.
//

#ifndef Definitions_h
#define Definitions_h

/** packet version */
#define VERSION                 0x01    // 版本号，亦是帧头

/** request */
#define REQUEST_FALSE           0x00    // 返回用户发送请求，失败
#define REQUEST_TRUE            0x01    // 返回用户发送请求，成功
#define REQUEST_NONE            0x02    // 用户发送请求

/** device status */
#define DEVICE_ON               0x01    // 设备打开
#define DEVICE_OFF              0x00    // 设备关闭
#define DEVICE_IDLE             0x03    // 查询设备在线，此时空闲可用
#define DEVICE_BUSY             0x04    // 查询设备在线，此时繁忙不可用
#define DEVICE_BUG              0x0F    // 查询设备在线，但异常无法使用需要用户检查

/** voltage status */
#define VOLTAGE_OK              0x50    // 电池电压正常，设备可用
#define VOLTAGE_HIGH            0x51    // 电池电压异常，电压过高
#define VOLTAGE_LOW             0x52    // 电池电压异常，电压过低

/** servos */
#define SERVO_00                0x00    // 0号舵机
#define SERVO_01                0x01    // 1号舵机
#define SERVO_02                0x02    // 2号舵机
#define SERVO_03                0x03    // 3号舵机
#define SERVO_04                0x04    // 4号舵机
#define SERVO_05                0x05    // 5号舵机
#define SERVO_06                0x06    // 6号舵机
#define SERVO_07                0x07    // 7号舵机
#define SERVO_08                0x08    // 8号舵机
#define SERVO_09                0x09    // 9号舵机
#define SERVO_10                0x0A    // 10号舵机
#define SERVO_11                0x0B    // 11号舵机
#define SERVO_12                0x0C    // 12号舵机
#define SERVO_13                0x0D    // 13号舵机
#define SERVO_14                0x0E    // 14号舵机
#define SERVO_15                0x0F    // 15号舵机

/** 指令大类 */
#define CMD_PETOI               0x00    // Petoi主动发送的信号
#define CMD_DC                  0x01    // 控制器向设备发送指令，请求设备控制指令
#define CMD_MOTION              0x02    // 控制器向设备发送指令，请求动作指令
#define CMD_SERVO               0x03    // 控制器向设备发送指令，请求舵机指令

/** 指令分类 */
#define DC_PETOI_HELLO          0xF0    // 设备控制：建立与PETOI设备连结
#define DC_PETOI_BYE            0xFF    // 设备控制：断开与PETOI设备连结

#define DC_LEDS_OFF             0x00    // 设备控制：关闭PETOI的LED灯组
#define DC_LEDS_ON              0x01    // 设备控制：打开PETOI的LED灯组
#define DC_LEDS_FLASH_ON        0x02    // 设备控制：LED灯组开始闪烁
#define DC_LEDS_FLASH_OFF       0x03    // 设备控制：LED灯组停止闪烁
#define DC_LEDS_STATUS          0x0C    // 设备控制：询问LED灯组当前状态

#define DC_GYRO_OFF             0x10    // 设备控制：关闭陀螺仪
#define DC_GYRO_ON              0x11    // 设备控制：打开陀螺仪
#define DC_GYRO_STATUS          0x1C    // 设备控制：询问陀螺仪当前状态

#define DC_SERVOS_OFF           0x20    // 设备控制：关闭全部舵机
#define DC_SERVOS_ON            0x21    // 设备控制：打开全部舵机
#define DC_SERVOS_STATUS        0x2C    // 设备控制：询问舵机当前状态

#define DC_SPEAKER_RPT          0x30    // 设备控制：用户上传并覆盖喇叭旋律
#define DC_SPEAKER_PLY          0x31    // 设备控制：播放旋律

#define DC_BUZZER_BEE_STP       0x40    // 设备控制：蜂鸣器停止鸣叫
#define DC_BUZZER_BEE_PLY       0x41    // 设备控制：蜂鸣器鸣叫一次
#define DC_BUZZER_BEE_NTM       0x4F    // 设备控制：蜂鸣器持续鸣叫

/** defined motions */
#define MOTION_PAUSE            0x00    // 动作指令：暂停
#define MOTION_CONTINUE         0x01    // 动作指令：继续

#define MOTION_WALK_FRONT       0x10    // 动作指令：向前走
#define MOTION_WALK_BACK        0x11    // 动作指令：向后走
#define MOTION_WALK_LEFT        0x12    // 动作指令：向左走
#define MOTION_WALK_RIGHT       0x13    // 动作指令：向右走

#define MOTION_CRAWL_FRONT      0x20    // 动作指令：向前爬
#define MOTION_CRAWL_LEFT       0x22    // 动作指令：向左爬
#define MOTION_CRAWL_RIGHT      0x23    // 动作指令：向后爬

#define MOTION_TROT_FRONT       0x30    // 动作指令：向前小跑
#define MOTION_TROT_LEFT        0x32    // 动作指令：向左小跑
#define MOTION_TROT_RIGHT       0x33    // 动作指令：向后小跑

#define MOTION_RUN_FRONT        0x40    // 动作指令：向前跑
#define MOTION_RUN_LEFT         0x42    // 动作指令：向左跑
#define MOTION_RUN_RIGHT        0x44    // 动作指令：向右跑

#define MOTION_JUMP             0xA0    // 动作指令：跳
#define MOTION_BUNNY_JUMP       0xA1    // 动作指令：兔子跳
#define MOTION_RECOVER          0xA2    // 动作指令：恢复姿态

#define MOTION_BALANCE          0xFF    // 动作指令：恢复站立

/** servos */
#define SERVOS_CALIB_START      0x00    // ready for calibration
#define SERVOS_CALIB_SAVE       0x01    // save new calibration
#define SERVOS_CALIB_ZEROS      0x0A    // let all servos to zero
#define SERVOS_CALIB_STATUS     0x0F    // query calibration status
#define SERVOS_CALIB_ONE        0xC2    // adjust current servo with angle

#define SERVOS_DEFINE_ALL       0x10    // 全部舵机执行给定角度
#define SERVOS_DEFINE_IND       0x11    // 指定舵机执行给定角度

/** Petoi主动发送的信号 */
#define PETOI_INIT              0x00    // PETOI设备启动中，设备正在初始化
#define PETOI_IDLE              0x01    // PETOI设备在线，此时空闲可用
#define PETOI_BUSY              0x02    // PETOI设备在线，此时繁忙不可用
#define PETOI_BUG               0x0F    // PETOI设备在线，但异常无法使用需要用户检查

/** data types */
#define DATA_UCHAR              0x11
#define DATA_CHAR               0x12
#define DATA_UINT               0x13
#define DATA_INT                0x14
#define DATA_ULONG              0x15
#define DATA_LONG               0x16
#define DATA_FLOAT              0x17
#define DATA_DOUBLE             0x18

#define DATA_NONE               0x00

#endif /* Definitions_h */
