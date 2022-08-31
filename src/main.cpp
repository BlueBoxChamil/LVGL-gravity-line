// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <Arduino_GFX_Library.h>
#include <Arduino.h>

#define GFX_BL 27
Arduino_DataBus *bus = new Arduino_ESP32SPI(12 /* DC */, 15 /* CS */, 14 /* SCK */, 13 /* MOSI */, -1 /* MISO */, HSPI /* spi_num */);
Arduino_GFX *gfx = new Arduino_ST7789(bus, 33 /* RST */, 0, true, 240, 320);

Adafruit_MPU6050 mpu;

enum Direction
{
  X = 0,
  Y = 1,
  Z = 2
};

float base_val[] = {10, 10, 10.5};
float z_offset = 0;

float Rad2Deg(float r)
{
  return (180 / 3.1415) * r;
}

float Deg2Rad(float d)
{
  return (3.1415 / 180) * d;
}

float GetDeg(float n, int direct)
{
  float prop = n / base_val[direct];
  prop = prop > 1 ? 1 : prop;
  prop = prop < -1 ? -1 : prop;
  return Rad2Deg(acos(prop));
}

void setup(void)
{
  Serial.begin(9600);

  gfx->begin();
  gfx->fillScreen(RED);
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);

  gfx->drawLine(0, 160, 240, 160, WHITE);

  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);

  // for (int i = 0; i < 90; i++)
  // {
  //   float tanti = tan(Deg2Rad(i));
  //   Serial.printf("tan%d = %f\r\n", i, tanti);
  // }
}

float x11 = 0;
float y11 = 160;
float x22 = 240;
float y22 = 160;
bool is_change = false;

void loop()
{

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float AccX = a.acceleration.x;
  float AccY = a.acceleration.y;
  float AccZ = a.acceleration.z;
  float AglX = GetDeg(AccX, X);
  float AglY = GetDeg(AccY, Y);
  float AglZ = GetDeg(AccZ, Z);

  // Serial.printf("AccY = %f\r\n", AccY);
  // Serial.printf("AglY = %f\r\n", AglY);

  float kk;

  if (AccX <= 0)
  {
    kk = -tan(Deg2Rad(AglY + 90));
  }
  else
  {
    kk = tan(Deg2Rad(AglY + 90));
  }

  gfx->drawLine(x11, y11, x22, y22, RED);

  x22 = 240;
  x11 = 0;

  y22 = kk * 240 + (160 - 120 * kk);
  y11 = kk * 0 + (160 - 120 * kk);

  if (y11 < 0)
  {
    y11 = 0;
    x11 = (y11 - (160 - 120 * kk)) / kk; // x = (y - b)/k   b = 160 - 120 * k
  }
  else if (y11 > 320)
  {
    y11 = 320;
    x11 = (y11 - (160 - 120 * kk)) / kk;
  }

  if (y22 < 0)
  {
    y22 = 0;
    x22 = (y22 - (160 - 120 * kk)) / kk;
  }
  else if (y22 > 320)
  {
    y22 = 320;
    x22 = (y22 - (160 - 120 * kk)) / kk;
  }

  gfx->drawLine(x11, y11, x22, y22, WHITE);

  delay(100);
}