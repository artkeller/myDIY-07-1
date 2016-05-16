//
//      FILE: lib_ex_Spin_B_32x32_3/utils.ino
//    AUTHOR: Thomas Walloschke
//   VERSION: 0.3.2
//   PURPOSE: 32x32 LED Matrix Application (16x8x8 MC) - Utilities - Spinning Clock 
//      DATE: 2016-03-05
//   CONTACT: artkeller(at)gmx.de
// COPYRIGHT: © 2016 Thomas Walloschke
//   LICENSE: The MIT License (MIT)
//            Permission is hereby granted, free of charge, to any person obtaining a copy of this software and 
//            associated documentation files (the “Software”), to deal in the Software without restriction, including 
//            without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
//            copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the 
//            following conditions:
//
//            The above copyright notice and this permission notice shall be included in all copies or substantial 
//            portions of the Software.
//
//            THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
//            LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
//            IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
//            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE  
//            SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

//////////////////////////////////////////////////////////////////////////////////////////

// Binary to BCD Conversion
// Stolen from  http://www.idreammicro.com/svn/idreammicro-arduino/trunk/libraries/AdafruitRTClib/RTClib.cpp
// Released to the public domain!
static byte bin2bcd (byte val) { 
  return val + 6 * (val / 10);
}

//////////////////////////////////////////////////////////////////////////////////////////

/* end-of-inotab-file */

