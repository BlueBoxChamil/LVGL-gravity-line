<!--
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-08-31 11:14:12
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-08-31 11:26:39
 * @FilePath: \20220824\README.md
 * @Description: 
 * 
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved. 
-->

# 使用esp32创建重力线

## 创建时间
20220831

## 目的
1. 添加重力线。

   
## 硬件
1. 开发板：esp32(devkitv1)
2. 电容触摸lcd显示屏
   
   1. lcd显示屏驱动ic： st7789， 像素240*320， spi接口
   <!-- 2. 触摸屏驱动ic：CST816S, 像素240*320， iic接口(SDA:21  SCL:22 addr: 0X15) -->
3. mpu6050 (iic接口 SDA:21 SCL:22 addr：0x68)

## 软件
platformIO IDE库：
1. GFX Library for Arduino
2. Adafruit MPU6050
<!-- 3. lvgl -->
<!-- 4. CST816S(非官方) -->
## 接线
|    esp32    | 触摸显示屏 | mpu6050 |
| :---------: | :--------: | :-----: |
|     GND     |    GND     |
|     3v3     |    3.3V    |
| D14(GPIO14) |    SCK     |
| D13(GPIO13) |    SDA     |
| D33(GPIO33) |    RES     |
| D12(GPIO12) |     DC     |
|    不接     |    BLK     |
| D21(GPIO21) |            | MPU_SDA |
| D22(GPIO22) |            | MPU_SCL |



 ## 编写流程


## 结果
<!-- ![img](https://github.com/BlueBoxChamil/LVGL-clock/blob/master/image/gif-2.gif) -->
![img](https://github.com/BlueBoxChamil/LVGL-gravity-line/blob/master/01.gif)
