🌈 Smart RGB Lamp with IR Remote Control
📌 Project Overview

This project is a smart LED lighting system controlled using an IR remote.
It features multiple lighting modes including rainbow effects, breathing animation, party mode, and synchronized lighting between an RGB LED and additional single LEDs.

The system is built using Arduino and demonstrates:

PWM color control

IR remote decoding

Non-blocking animation using millis()

Mode switching system

Synchronized multi-LED effects

🎮 Features
✨ Lighting Modes

🔴 Red Mode

🟢 Green Mode

🔵 Blue Mode

🟡 Yellow Mode

🌈 Rainbow Mode (Fully Synchronized)

🎲 Random Mode (Color Matching)

💨 Breathing Mode

🎉 Party Mode

🌙 Calm Mode

💡 Key Functionalities

All LEDs can operate in synchronized rhythm

Smooth rainbow animation

Non-blocking code (no freezing when switching modes)

Instant mode switching using IR remote

LCD display shows current mode

🔧 Hardware Requirements

Arduino board (Uno/Nano recommended)

IR Receiver Module

RGB LED

4 Single LEDs (Red, Green, Blue, Yellow)

LCD Display (16x2)

Resistors

Breadboard & jumper wires

IR Remote

📍 Pin Configuration
IR Receiver

Signal → Pin 2

RGB LED

Red → Pin 3 (PWM)

Green → Pin 5 (PWM)

Blue → Pin 6 (PWM)

Single LEDs

Red → Pin 8

Green → Pin 9

Blue → Pin 10

Yellow → Pin 11

LCD

Uses pins: 12, 4, A0, A1, A2, A3

🧠 How It Works

The IR remote sends signals to the Arduino.

The Arduino reads the command using the IRremote library.

The system changes the mode variable.

The loop() function runs animations based on the selected mode.

Animations use millis() for smooth performance (no blocking delays).

All LEDs can be synchronized to follow the same rhythm.

🌈 Rainbow Mode

Smooth color transition across the full RGB spectrum.

All LEDs change together in sync.

Uses timed updates for smooth animation.

Dimmed for better visual effect.

🎉 Party Mode

Rapid random colors.

All LEDs flash together.

Creates energetic lighting effects.

🌙 Calm Mode

Slow smooth color transitions.

Dimmed brightness.

Designed for relaxing ambient lighting.

🚀 Improvements Made

Removed blocking delay() in major modes

Implemented millis() timing system

Added synchronized LED behavior

Improved mode switching responsiveness

📚 Libraries Used

IRremote

LiquidCrystal

🛠 Future Improvements

Add brightness control via remote

Add music-reactive mode

Add speed control

Add fade effects for single LEDs

Add WiFi control (ESP version)
