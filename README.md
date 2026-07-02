# Smart RGB Lamp with IR Remote Control

## Project Description

This project is an Arduino-based smart lighting system controlled using an IR remote.  
It features multiple lighting modes, synchronized animations, and smooth transitions between colors.

The system controls:
- An RGB LED
- Four single LEDs (Red, Green, Blue, Yellow)
- An LCD display for mode feedback

The project demonstrates PWM control, IR communication, non-blocking animations using `millis()`, and synchronized multi-LED effects.

---
## Demo Video

Check out the demo of the lamp in action:

[![Watch the Demo](https://img.youtube.com/vi/TwzFgdyrvng/0.jpg)](https://www.youtube.com/watch?v=TwzFgdyrvng)

## Features

### Lighting Modes

- 🔴 Red Mode
- 🟢 Green Mode
- 🔵 Blue Mode
- 🟡 Yellow Mode
- 🌈 Rainbow Mode (Fully Synchronized)
- 🎲 Random Mode
- 💨 Breathing Mode
- 🎉 Party Mode
- 🌙 Calm Mode

All modes can be switched instantly using the IR remote.

---

## Hardware Requirements

- Arduino Uno (or compatible board)
- IR Receiver Module
- RGB LED
- 4 Single LEDs
- Resistors
- 16x2 LCD Display
- Breadboard and jumper wires
- IR Remote Control

---

## Pin Configuration

### IR Receiver
- Signal → Pin 2

### RGB LED (PWM Pins)
- Red → Pin 3
- Green → Pin 5
- Blue → Pin 6

### Single LEDs
- Red → Pin 8
- Green → Pin 9
- Blue → Pin 10
- Yellow → Pin 11

### LCD Display
- Uses pins: 12, 4, A0, A1, A2, A3

---

## How It Works

1. The IR receiver reads signals from the remote.
2. Each button changes the system `mode`.
3. The `loop()` function runs animations based on the selected mode.
4. Animations use `millis()` instead of `delay()` to prevent blocking.
5. All LEDs can operate in synchronized rhythm with the RGB LED.

---

## Rainbow Mode

- Smooth transition across the full color spectrum.
- All LEDs change color together in sync.
- Uses non-blocking timing.
- Dimmed for a visually pleasant effect.

---

## Party Mode

- Rapid dynamic color changes.
- All LEDs flash together.
- Creates energetic lighting effects.

---

## Calm Mode

- Slow smooth color transitions.
- Lower brightness for a relaxing atmosphere.
- Designed for ambient lighting.

---

## Improvements Made

- Replaced blocking `delay()` with `millis()`
- Enabled instant mode switching
- Synchronized all LEDs in animation modes
- Improved responsiveness and performance

---

## Libraries Used

- IRremote
- LiquidCrystal

---

## Future Enhancements

- Brightness control via remote
- Speed adjustment for animations
- Music-reactive lighting
- WiFi / Bluetooth control
- Custom color selection mode

---

## Author

Minh Anh
