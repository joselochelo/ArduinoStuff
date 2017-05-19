/**************************************************************************/
/*!
    @file     sinewave.pde
    @author   Adafruit Industries
    @license  BSD (see license.txt)

    This example will generate a sine wave with the MCP4725 DAC.

    This is an example sketch for the Adafruit MCP4725 breakout board
    ----> http://www.adafruit.com/products/935

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!
*/
/**************************************************************************/
#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

// Set this value to 9, 8, 7, 6 or 5 to adjust the resolution
#define DAC_RESOLUTION    (9)

/* Note: If flash space is tight a quarter sine wave is enough
   to generate full sine and cos waves, but some additional
   calculation will be required at each step after the first
   quarter wave.                                              */

const PROGMEM uint16_t DACLookup_FullSine_9Bit[500] =
{
0, 8, 16, 24, 32, 40, 49, 57, 65, 73, 81, 90, 98, 106, 114, 122, 131, \
139, 147, 155, 163, 171, 180, 188, 196, 204, 212, 221, 229, 237, 245, \
253, 262, 270, 278, 286, 294, 303, 311, 319, 327, 335, 343, 352, 360, \
368, 376, 384, 393, 401, 409, 417, 425, 434, 442, 450, 458, 466, 475, \
483, 491, 499, 507, 515, 524, 532, 540, 548, 556, 565, 573, 581, 589, \
597, 606, 614, 622, 630, 638, 647, 655, 663, 671, 679, 687, 696, 704, \
712, 720, 728, 737, 745, 753, 761, 769, 778, 786, 794, 802, 810, 819, \
827, 835, 843, 851, 859, 868, 876, 884, 892, 900, 909, 917, 925, 933, \
941, 950, 958, 966, 974, 982, 990, 999, 1007, 1015, 1023, 1031, 1040, \
1048, 1056, 1064, 1072, 1081, 1089, 1097, 1105, 1113, 1122, 1130, \
1138, 1146, 1154, 1162, 1171, 1179, 1187, 1195, 1203, 1212, 1220, \
1228, 1236, 1244, 1253, 1261, 1269, 1277, 1285, 1294, 1302, 1310, \
1318, 1326, 1334, 1343, 1351, 1359, 1367, 1375, 1384, 1392, 1400, \
1408, 1416, 1425, 1433, 1441, 1449, 1457, 1466, 1474, 1482, 1490, \
1498, 1506, 1515, 1523, 1531, 1539, 1547, 1556, 1564, 1572, 1580, \
1588, 1597, 1605, 1613, 1621, 1629, 1638, 1646, 1654, 1662, 1670, \
1678, 1687, 1695, 1703, 1711, 1719, 1728, 1736, 1744, 1752, 1760, \
1769, 1777, 1785, 1793, 1801, 1809, 1818, 1826, 1834, 1842, 1850, \
1859, 1867, 1875, 1883, 1891, 1900, 1908, 1916, 1924, 1932, 1941, \
1949, 1957, 1965, 1973, 1981, 1990, 1998, 2006, 2014, 2022, 2031, \
2039, 2047, 2055, 2063, 2072, 2080, 2088, 2096, 2104, 2113, 2121, \
2129, 2137, 2145, 2153, 2162, 2170, 2178, 2186, 2194, 2203, 2211, \
2219, 2227, 2235, 2244, 2252, 2260, 2268, 2276, 2285, 2293, 2301, \
2309, 2317, 2325, 2334, 2342, 2350, 2358, 2366, 2375, 2383, 2391, \
2399, 2407, 2416, 2424, 2432, 2440, 2448, 2457, 2465, 2473, 2481, \
2489, 2497, 2506, 2514, 2522, 2530, 2538, 2547, 2555, 2563, 2571, \
2579, 2588, 2596, 2604, 2612, 2620, 2628, 2637, 2645, 2653, 2661, \
2669, 2678, 2686, 2694, 2702, 2710, 2719, 2727, 2735, 2743, 2751, \
2760, 2768, 2776, 2784, 2792, 2800, 2809, 2817, 2825, 2833, 2841, \
2850, 2858, 2866, 2874, 2882, 2891, 2899, 2907, 2915, 2923, 2932, \
2940, 2948, 2956, 2964, 2972, 2981, 2989, 2997, 3005, 3013, 3022, \
3030, 3038, 3046, 3054, 3063, 3071, 3079, 3087, 3095, 3104, 3112, \
3120, 3128, 3136, 3144, 3153, 3161, 3169, 3177, 3185, 3194, 3202, \
3210, 3218, 3226, 3235, 3243, 3251, 3259, 3267, 3276, 3284, 3292, \
3300, 3308, 3316, 3325, 3333, 3341, 3349, 3357, 3366, 3374, 3382, \
3390, 3398, 3407, 3415, 3423, 3431, 3439, 3447, 3456, 3464, 3472, \
3480, 3488, 3497, 3505, 3513, 3521, 3529, 3538, 3546, 3554, 3562, \
3570, 3579, 3587, 3595, 3603, 3611, 3619, 3628, 3636, 3644, 3652, \
3660, 3669, 3677, 3685, 3693, 3701, 3710, 3718, 3726, 3734, 3742, \
3751, 3759, 3767, 3775, 3783, 3791, 3800, 3808, 3816, 3824, 3832, \
3841, 3849, 3857, 3865, 3873, 3882, 3890, 3898, 3906, 3914, 3923, \
3931, 3939, 3947, 3955, 3963, 3972, 3980, 3988, 3996, 4004, 4013, \
4021, 4029, 4037, 4045, 4054, 4062, 4070, 4078, 4086
};

void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello!");
  dac.begin(0x62);

  Serial.println("Generating a sine wave");
  pinMode(A0,INPUT);
}

void loop(void) {
  uint16_t i;
  int val = map(analogRead(A0),0,1023,1,88);
  // Push out the right lookup table, depending on the selected resolution
  for (i = 0; i < 500; i += 1)
  {
    dac.setVoltage(pgm_read_word(&(DACLookup_FullSine_9Bit[i])), false);
  }
}
