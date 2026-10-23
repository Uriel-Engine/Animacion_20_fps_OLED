#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "AgnesCafe.h"
//#include "jojo_video_frames.h"
//#include "VentoAureo_20s.h"

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

#define OLED_SDA 8
#define OLED_SCL 9

#define OLED_ADDRESS 0x3C

#define VIDEO_FPS 20
#define FRAME_TIME (1000 / VIDEO_FPS)

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

uint16_t currentFrame = 0;
uint32_t previousFrameTime = 0;

void setup() {

  Serial.begin(115200);

  Wire.begin(OLED_SDA, OLED_SCL);
  Wire.setClock(400000);

  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDRESS
      )) {

    Serial.println("Error iniciando SSD1306");

    while (true) {
      delay(1000);
    }
  }

  display.invertDisplay(false);

  display.clearDisplay();
  display.display();

  Serial.println("OLED iniciada");
  Serial.print("Frames: ");
  Serial.println(VIDEO_FRAME_COUNT);

  previousFrameTime = millis();
}

void loop() {

  uint32_t now = millis();

  if (now - previousFrameTime >= FRAME_TIME) {

    previousFrameTime += FRAME_TIME;

    // Limpiar el frame anterior
    display.clearDisplay();

    // Dibujar UN SOLO frame
    display.drawBitmap(
      0,
      0,
      videoFrames[currentFrame],
      VIDEO_WIDTH,
      VIDEO_HEIGHT,
      SSD1306_WHITE
    );

    // Enviar framebuffer completo a la OLED
    display.display();

    // Siguiente frame
    currentFrame++;

    if (currentFrame >= VIDEO_FRAME_COUNT) {
      currentFrame = 0;
    }
  }
}