/**
 * Copyright (c) 2011-2018 Bill Greiman
 * This file is part of the SdFat library for SD memory cards.
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
/**
 * @file
 * @brief Fast Digital Pin functions
 *
 * @defgroup digitalPin Fast Pin I/O
 * @details  Fast Digital I/O functions and template class.
 * @{
 */
#ifndef DigitalPin_h
#define DigitalPin_h

//------------------------------------------------------------------------------
/** read pin value
 * @param[in] pin Arduino pin number
 * @return value read
 */
static inline __attribute__((always_inline))
bool fastDigitalRead(uint8_t pin) {
  return *portInputRegister(pin);
}
//------------------------------------------------------------------------------
/** Set pin value
 * @param[in] pin Arduino pin number
 * @param[in] level value to write
 */
static inline __attribute__((always_inline))
void fastDigitalWrite(uint8_t pin, bool value) {
  if (value) {
    *portSetRegister(pin) = 1;
  } else {
    *portClearRegister(pin) = 1;
  }
}

//------------------------------------------------------------------------------
inline void fastDigitalToggle(uint8_t pin) {
  fastDigitalWrite(pin, !fastDigitalRead(pin));
}
//------------------------------------------------------------------------------
inline void fastPinMode(uint8_t pin, uint8_t mode) {
  pinMode(pin, mode);
}

//------------------------------------------------------------------------------
/** set pin configuration
 * @param[in] pin Arduino pin number
 * @param[in] mode mode INPUT or OUTPUT.
 * @param[in] level If mode is output, set level high/low.
 *                  If mode is input, enable or disable the pin's 20K pullup.
 */
#define fastPinConfig(pin, mode, level)\
  {fastPinMode(pin, mode); fastDigitalWrite(pin, level);}
//==============================================================================
/**
 * @class DigitalPin
 * @brief Fast digital port I/O
 */
template<uint8_t PinNumber>
class DigitalPin {
 public:
  //----------------------------------------------------------------------------
  /** Constructor */
  DigitalPin() {}
  //----------------------------------------------------------------------------
  /** Asignment operator.
   * @param[in] value If true set the pin's level high else set the
   *  pin's level low.
   *
   * @return This DigitalPin instance.
   */
  inline DigitalPin & operator = (bool value) __attribute__((always_inline)) {
    write(value);
    return *this;
  }
  //----------------------------------------------------------------------------
  /** Parenthesis operator.
   * @return Pin's level
   */
  inline operator bool () const __attribute__((always_inline)) {
    return read();
  }
  //----------------------------------------------------------------------------
  /** Set pin configuration.
   * @param[in] mode: INPUT or OUTPUT.
   * @param[in] level If mode is OUTPUT, set level high/low.
   *                  If mode is INPUT, enable or disable the pin's 20K pullup.
   */
  inline __attribute__((always_inline))
  void config(uint8_t mode, bool level) {
    fastPinConfig(PinNumber, mode, level);
  }
  //----------------------------------------------------------------------------
  /**
   * Set pin level high if output mode or enable 20K pullup if input mode.
   */
  inline __attribute__((always_inline))
  void high() {write(true);}
  //----------------------------------------------------------------------------
  /**
   * Set pin level low if output mode or disable 20K pullup if input mode.
   */
  inline __attribute__((always_inline))
  void low() {write(false);}
  //----------------------------------------------------------------------------
  /**
   * Set pin mode.
   * @param[in] mode: INPUT, OUTPUT, or INPUT_PULLUP.
   *
   * The internal pullup resistors will be enabled if mode is INPUT_PULLUP
   * and disabled if the mode is INPUT.
   */
  inline __attribute__((always_inline))
  void mode(uint8_t mode) {
    fastPinMode(PinNumber, mode);
  }
  //----------------------------------------------------------------------------
  /** @return Pin's level. */
  inline __attribute__((always_inline))
  bool read() const {
    return fastDigitalRead(PinNumber);
  }
  //----------------------------------------------------------------------------
  /** Toggle a pin.
   *
   * If the pin is in output mode toggle the pin's level.
   * If the pin is in input mode toggle the state of the 20K pullup.
   */
  inline __attribute__((always_inline))
  void toggle() {
    fastDigitalToggle(PinNumber);
  }
  //----------------------------------------------------------------------------
  /** Write the pin's level.
   * @param[in] value If true set the pin's level high else set the
   *  pin's level low.
   */
  inline __attribute__((always_inline))
  void write(bool value) {
    fastDigitalWrite(PinNumber, value);
  }
};
#endif  // DigitalPin_h
/** @} */
