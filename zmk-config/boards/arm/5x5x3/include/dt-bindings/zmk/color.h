/*
 * Copyright (c) 2025 by Willem Dijkstra <wpd@xs4all.nl>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of the auhor nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define HSV(Hue, Saturation, Value) (Hue * 0x100) Saturation Value

#define HUE_SEXTANT                 0x100
#define SEXTANT_MAX                 6
#define HUE_MAX                     ((SEXTANT_MAX * HUE_SEXTANT) - 1)

/*
 * Basic hues, 15° increments
 */

#define HUE_RED                       0
#define HUE_VERMILION                15
#define HUE_ORANGE                   30
#define HUE_AMBER                    45
#define HUE_YELLOW                   60
#define HUE_LIME                     75
#define HUE_CHARTREUSE               90
#define HUE_DDAHAL                  105
#define HUE_GREEN                   120
#define HUE_ERIN                    135
#define HUE_SPRING                  150
#define HUE_GASHYANTA               165
#define HUE_CYAN                    180
#define HUE_CAPRI                   195
#define HUE_AZURE                   210
#define HUE_CERULEAN                225
#define HUE_BLUE                    240
#define HUE_VOLTA                   255
#define HUE_VIOLET                  270
#define HUE_PURPLE                  285
#define HUE_MAGENTA                 300
#define HUE_CERISE                  315
#define HUE_ROSE                    330
#define HUE_CRIMSON                 345

/*
 * Basic colors, CSS 1-2.0, HTML 3.2-4, VGA color names
 */
#define HSV_WHITE                   HSV(HUE_RED,           0, 0xff) // #ffffff
#define HSV_SILVER                  HSV(HUE_RED,           0, 0xc0) // #c0c0c0
#define HSV_GRAY                    HSV(HUE_RED,           0, 0x80) // #808080
#define HSV_BLACK                   HSV(HUE_RED,           0, 0)    // #000000
#define HSV_RED                     HSV(HUE_RED,        0xff, 0xff) // #ff0000
#define HSV_MAROON                  HSV(HUE_RED,        0xff, 0x80) // #800000
#define HSV_YELLOW                  HSV(HUE_YELLOW,     0xff, 0xff) // #ffff00
#define HSV_OLIVE                   HSV(HUE_YELLOW,     0xff, 0x80) // #808000
#define HSV_BLIME                   HSV(HUE_GREEN,      0xff, 0xff) // #00ff00
#define HSV_GREEN                   HSV(HUE_GREEN,      0xff, 0x80) // #008000
#define HSV_AQUA                    HSV(HUE_CYAN,       0xff, 0xff) // #00ffff
#define HSV_TEAL                    HSV(HUE_CYAN,       0xff, 0x80) // #008080
#define HSV_BLUE                    HSV(HUE_BLUE,       0xff, 0xff) // #0000ff
#define HSV_NAVY                    HSV(HUE_BLUE,       0xff, 0x80) // #000080
#define HSV_FUCHSIA                 HSV(HUE_MAGENTA,    0xff, 0xff) // #ff00ff
#define HSV_PURPLE                  HSV(HUE_MAGENTA,    0xff, 0x80) // #800080

/*
 * Add 15° increments
 */
#define HSV_VERMILION               HSV(HUE_VERMILION,  0xff, 0xff) // #ff4000
#define HSV_AMBER                   HSV(HUE_AMBER,      0xff, 0xff) // #ffc000
#define HSV_LIME                    HSV(HUE_LIME,       0xff, 0xff) // #c0ff00
#define HSV_ORANGE                  HSV(HUE_ORANGE,     0xff, 0xff) // #ff8000
#define HSV_CHARTREUSE              HSV(HUE_CHARTREUSE, 0xff, 0xff) // #80ff00
#define HSV_DDAHAL                  HSV(HUE_DDAHAL,     0xff, 0xff) // #40ff00
#define HSV_ERIN                    HSV(HUE_ERIN,       0xff, 0xff) // #00ff40
#define HSV_SPRING                  HSV(HUE_SPRING,     0xff, 0xff) // #00ff80
#define HSV_GASHYANTA               HSV(HUE_GASHYANTA,  0xff, 0xff) // #00ffc0
#define HSV_CYAN                    HSV(HUE_CYAN,       0xff, 0xff) // #00ffff
#define HSV_CAPRI                   HSV(HUE_CAPRI,      0xff, 0xff) // #00c0ff
#define HSV_AZURE                   HSV(HUE_AZURE,      0xff, 0xff) // #0080ff
#define HSV_CERULEAN                HSV(HUE_CERULEAN,   0xff, 0xff) // #0040ff
#define HSV_VOLTA                   HSV(HUE_VOLTA,      0xff, 0xff) // #4000ff
#define HSV_VIOLET                  HSV(HUE_VIOLET,     0xff, 0xff) // #8000ff
#define HSV_MAGENTA                 HSV(HUE_MAGENTA,    0xff, 0xff) // #ff00ff
#define HSV_CERISE                  HSV(HUE_CERISE,     0xff, 0xff) // #ff00c0
#define HSV_ROSE                    HSV(HUE_ROSE,       0xff, 0xff) // #ff0080
#define HSV_CRIMSON                 HSV(HUE_CRIMSON,    0xff, 0xff) // #ff0040

/*
 * Bang's RGB color names
 * https://www.perbang.dk/color-names/
 * Copyright 2004-2025 Per Bang
 *
 * These data are FREE and distributed in the hope that they will be useful, but
 * WITHOUT ANY WARRANTY. Permission is granted to copy, distribute and/or
 * modify the data under the terms of the Creative Commons
 * Attribution-ShareAlike 3.0.
 */
#define HSV_PINKISH_WHITE                            HSV(000, 0x08, 0xff) // #fff6f6
#define HSV_VERY_PALE_PINK                           HSV(000, 0x1d, 0xff) // #ffe2e2
#define HSV_PALE_PINK                                HSV(000, 0x3d, 0xff) // #ffc2c2
#define HSV_LIGHT_PINK                               HSV(000, 0x61, 0xff) // #ff9e9e
#define HSV_LIGHT_BRILLIANT_RED                      HSV(000, 0x9a, 0xff) // #ff6565
#define HSV_LUMINOUS_VIVID_RED                       HSV(000, 0xff, 0xff) // #ff0000
#define HSV_PINKISH_GRAY                             HSV(000, 0x0e, 0xe7) // #e7dada
#define HSV_PALE__GRAYISH_PINK                       HSV(000, 0x33, 0xe7) // #e7b8b8
#define HSV_PINK                                     HSV(000, 0x65, 0xe7) // #e78b8b
#define HSV_BRILLIANT_RED                            HSV(000, 0xa5, 0xe7) // #e75151
#define HSV_VIVID_RED                                HSV(000, 0xff, 0xe7) // #e70000
#define HSV_REDDISH_GRAY                             HSV(000, 0x12, 0xa8) // #a89c9c
#define HSV_GRAYISH_RED                              HSV(000, 0x41, 0xa8) // #a87d7d
#define HSV_MODERATE_RED                             HSV(000, 0x8e, 0xa8) // #a84a4a
#define HSV_STRONG_RED                               HSV(000, 0xff, 0xa8) // #a80000
#define HSV_REDDISH_BROWNISH_GRAY                    HSV(000, 0x11, 0x59) // #595353
#define HSV_DARK_GRAYISH_REDDISH_BROWN               HSV(000, 0x41, 0x59) // #594242
#define HSV_REDDISH_BROWN                            HSV(000, 0x8f, 0x59) // #592727
#define HSV_DEEP_REDDISH_BROWN                       HSV(000, 0xff, 0x59) // #590000
#define HSV_REDDISH_BROWNISH_BLACK                   HSV(000, 0x1a, 0x1d) // #1d1a1a
#define HSV_VERY_DARK_REDDISH_BROWN                  HSV(000, 0x69, 0x1d) // #1d1111
#define HSV_VERY_DEEP_REDDISH_BROWN                  HSV(000, 0xff, 0x1d) // #1d0000
#define HSV_PALE_SCARLET                             HSV(006, 0x3d, 0xff) // #ffc9c2
#define HSV_VERY_LIGHT_SCARLET                       HSV(007, 0x61, 0xff) // #ffaa9e
#define HSV_LIGHT_BRILLIANT_SCARLET                  HSV(007, 0x9a, 0xff) // #ff7865
#define HSV_LUMINOUS_VIVID_SCARLET                   HSV(007, 0xff, 0xff) // #ff2000
#define HSV_LIGHT_SCARLET                            HSV(007, 0x65, 0xe7) // #e7968b
#define HSV_BRILLIANT_SCARLET                        HSV(007, 0xa5, 0xe7) // #e76451
#define HSV_VIVID_SCARLET                            HSV(007, 0xff, 0xe7) // #e71d00
#define HSV_MODERATE_SCARLET                         HSV(007, 0x8e, 0xa8) // #a8554a
#define HSV_STRONG_SCARLET                           HSV(007, 0xff, 0xa8) // #a81500
#define HSV_DARK_SCARLET                             HSV(007, 0x8f, 0x59) // #592d27
#define HSV_DEEP_SCARLET                             HSV(007, 0xff, 0x59) // #590b00
#define HSV_VERY_PALE_VERMILION                      HSV(014, 0x1d, 0xff) // #ffe9e2
#define HSV_PALE_VERMILION                           HSV(014, 0x3d, 0xff) // #ffd1c2
#define HSV_VERY_LIGHT_VERMILION                     HSV(014, 0x61, 0xff) // #ffb69e
#define HSV_LIGHT_BRILLIANT_VERMILION                HSV(014, 0x9a, 0xff) // #ff8b65
#define HSV_LUMINOUS_VIVID_VERMILION                 HSV(015, 0xff, 0xff) // #ff4000
#define HSV_PALE__LIGHT_GRAYISH_VERMILION            HSV(015, 0x33, 0xe7) // #e7c4b8
#define HSV_LIGHT_VERMILION                          HSV(015, 0x65, 0xe7) // #e7a28b
#define HSV_BRILLIANT_VERMILION                      HSV(015, 0xa5, 0xe7) // #e77751
#define HSV_VIVID_VERMILION                          HSV(015, 0xff, 0xe7) // #e73a00
#define HSV_GRAYISH_VERMILION                        HSV(015, 0x41, 0xa8) // #a8887d
#define HSV_MODERATE_VERMILION                       HSV(014, 0x8e, 0xa8) // #a8614a
#define HSV_STRONG_VERMILION                         HSV(015, 0xff, 0xa8) // #a82a00
#define HSV_DARK_GRAYISH_VERMILION                   HSV(015, 0x41, 0x59) // #594842
#define HSV_DARK_VERMILION                           HSV(015, 0x8f, 0x59) // #593427
#define HSV_DEEP_VERMILION                           HSV(014, 0xff, 0x59) // #591600
#define HSV_PALE_TANGELO                             HSV(022, 0x3d, 0xff) // #ffd9c2
#define HSV_VERY_LIGHT_TANGELO                       HSV(022, 0x61, 0xff) // #ffc29e
#define HSV_LIGHT_BRILLIANT_TANGELO                  HSV(022, 0x9a, 0xff) // #ff9f65
#define HSV_LUMINOUS_VIVID_TANGELO                   HSV(022, 0xff, 0xff) // #ff6000
#define HSV_LIGHT_TANGELO                            HSV(022, 0x65, 0xe7) // #e7ae8b
#define HSV_BRILLIANT_TANGELO                        HSV(022, 0xa5, 0xe7) // #e78951
#define HSV_VIVID_TANGELO                            HSV(022, 0xff, 0xe7) // #e75700
#define HSV_MODERATE_TANGELO                         HSV(022, 0x8e, 0xa8) // #a86d4a
#define HSV_STRONG_TANGELO                           HSV(022, 0xff, 0xa8) // #a83f00
#define HSV_DARK_TANGELO                             HSV(022, 0x8f, 0x59) // #593a27
#define HSV_DEEP_TANGELO                             HSV(022, 0xff, 0x59) // #592100
#define HSV_VERY_PALE_ORANGE                         HSV(028, 0x1d, 0xff) // #fff0e2
#define HSV_PALE_ORANGE                              HSV(029, 0x3d, 0xff) // #ffe0c2
#define HSV_VERY_LIGHT_ORANGE                        HSV(030, 0x61, 0xff) // #ffcf9e
#define HSV_LIGHT_BRILLIANT_ORANGE                   HSV(030, 0x9a, 0xff) // #ffb265
#define HSV_LUMINOUS_VIVID_ORANGE                    HSV(030, 0xff, 0xff) // #ff8000
#define HSV_PALE__LIGHT_GRAYISH_BROWN                HSV(030, 0x33, 0xe7) // #e7d0b8
#define HSV_LIGHT_ORANGE                             HSV(030, 0x65, 0xe7) // #e7b98b
#define HSV_BRILLIANT_ORANGE                         HSV(030, 0xa5, 0xe7) // #e79c51
#define HSV_VIVID_ORANGE                             HSV(030, 0xff, 0xe7) // #e77400
#define HSV_GRAYISH_BROWN                            HSV(030, 0x41, 0xa8) // #a8937d
#define HSV_MODERATE_ORANGE                          HSV(029, 0x8e, 0xa8) // #a8794a
#define HSV_STRONG_ORANGE                            HSV(030, 0xff, 0xa8) // #a85400
#define HSV_DARK_GRAYISH_BROWN                       HSV(031, 0x41, 0x59) // #594e42
#define HSV_BROWN                                    HSV(030, 0x8f, 0x59) // #594027
#define HSV_DEEP_BROWN                               HSV(030, 0xff, 0x59) // #592d00
#define HSV_VERY_BROWN                               HSV(030, 0x69, 0x1d) // #1d1711
#define HSV_VERY_DEEP_BROWN                          HSV(028, 0xff, 0x1d) // #1d0e00
#define HSV_PALE_GAMBOGE                             HSV(037, 0x3d, 0xff) // #ffe8c2
#define HSV_VERY_LIGHT_GAMBOGE                       HSV(037, 0x61, 0xff) // #ffdb9e
#define HSV_LIGHT_BRILLIANT_GAMBOGE                  HSV(037, 0x9a, 0xff) // #ffc565
#define HSV_LUMINOUS_VIVID_GAMBOGE                   HSV(037, 0xff, 0xff) // #ff9f00
#define HSV_LIGHT_GAMBOGE                            HSV(037, 0x65, 0xe7) // #e7c58b
#define HSV_BRILLIANT_GAMBOGE                        HSV(037, 0xa5, 0xe7) // #e7af51
#define HSV_VIVID_GAMBOGE                            HSV(037, 0xff, 0xe7) // #e79100
#define HSV_MODERATE_GAMBOGE                         HSV(037, 0x8e, 0xa8) // #a8854a
#define HSV_STRONG_GAMBOGE                           HSV(037, 0xff, 0xa8) // #a86900
#define HSV_DARK_GAMBOGE                             HSV(037, 0x8f, 0x59) // #594627
#define HSV_DEEP_GAMBOGE                             HSV(037, 0xff, 0x59) // #593800
#define HSV_VERY_PALE_AMBER                          HSV(045, 0x1d, 0xff) // #fff8e2
#define HSV_PALE_AMBER                               HSV(045, 0x3d, 0xff) // #fff0c2
#define HSV_VERY_LIGHT_AMBER                         HSV(045, 0x61, 0xff) // #ffe79e
#define HSV_LIGHT_BRILLIANT_AMBER                    HSV(044, 0x9a, 0xff) // #ffd865
#define HSV_LUMINOUS_VIVID_AMBER                     HSV(044, 0xff, 0xff) // #ffbf00
#define HSV_PALE__LIGHT_GRAYISH_AMBER                HSV(045, 0x33, 0xe7) // #e7dcb8
#define HSV_LIGHT_AMBER                              HSV(045, 0x65, 0xe7) // #e7d08b
#define HSV_BRILLIANT_AMBER                          HSV(045, 0xa5, 0xe7) // #e7c251
#define HSV_VIVID_AMBER                              HSV(045, 0xff, 0xe7) // #e7ae00
#define HSV_GRAYISH_AMBER                            HSV(046, 0x41, 0xa8) // #a89e7d
#define HSV_MODERATE_AMBER                           HSV(045, 0x8e, 0xa8) // #a8914a
#define HSV_STRONG_AMBER                             HSV(045, 0xff, 0xa8) // #a87e00
#define HSV_DARK_GRAYISH_AMBER                       HSV(046, 0x41, 0x59) // #595442
#define HSV_DARK_AMBER                               HSV(045, 0x8f, 0x59) // #594d27
#define HSV_DEEP_AMBER                               HSV(045, 0xff, 0x59) // #594300
#define HSV_PALE_GOLD                                HSV(052, 0x3d, 0xff) // #fff7c2
#define HSV_VERY_LIGHT_GOLD                          HSV(052, 0x61, 0xff) // #fff39e
#define HSV_LIGHT_BRILLIANT_GOLD                     HSV(052, 0x9a, 0xff) // #ffec65
#define HSV_LUMINOUS_VIVID_GOLD                      HSV(052, 0xff, 0xff) // #ffdf00
#define HSV_LIGHT_GOLD                               HSV(052, 0x65, 0xe7) // #e7dc8b
#define HSV_BRILLIANT_GOLD                           HSV(052, 0xa5, 0xe7) // #e7d551
#define HSV_VIVID_GOLD                               HSV(052, 0xff, 0xe7) // #e7ca00
#define HSV_MODERATE_GOLD                            HSV(052, 0x8e, 0xa8) // #a89c4a
#define HSV_STRONG_GOLD                              HSV(052, 0xff, 0xa8) // #a89300
#define HSV_DARK_GOLD                                HSV(052, 0x8f, 0x59) // #595327
#define HSV_DEEP_GOLD                                HSV(052, 0xff, 0x59) // #594e00
#define HSV_YELLOWISH_WHITE                          HSV(060, 0x08, 0xff) // #fffff6
#define HSV_VERY_PALE_YELLOW                         HSV(060, 0x1d, 0xff) // #ffffe2
#define HSV_PALE_YELLOW                              HSV(060, 0x3d, 0xff) // #ffffc2
#define HSV_VERY_LIGHT_YELLOW                        HSV(060, 0x61, 0xff) // #ffff9e
#define HSV_LIGHT_BRILLIANT_YELLOW                   HSV(060, 0x9a, 0xff) // #ffff65
#define HSV_LUMINOUS_VIVID_YELLOW                    HSV(060, 0xff, 0xff) // #ffff00
#define HSV_LIGHT_YELLOWISH_GRAY                     HSV(060, 0x0e, 0xe7) // #e7e7da
#define HSV_PALE__LIGHT_GRAYISH_OLIVE                HSV(060, 0x33, 0xe7) // #e7e7b8
#define HSV_LIGHT_YELLOW                             HSV(060, 0x65, 0xe7) // #e7e78b
#define HSV_BRILLIANT_YELLOW                         HSV(060, 0xa5, 0xe7) // #e7e751
#define HSV_VIVID_YELLOW                             HSV(060, 0xff, 0xe7) // #e7e700
#define HSV_YELLOWISH_GRAY                           HSV(060, 0x12, 0xa8) // #a8a89c
#define HSV_GRAYISH_OLIVE                            HSV(060, 0x41, 0xa8) // #a8a87d
#define HSV_MODERATE_OLIVE                           HSV(060, 0x8e, 0xa8) // #a8a84a
#define HSV_STRONG_OLIVE                             HSV(060, 0xff, 0xa8) // #a8a800
#define HSV_DARK_OLIVISH_GRAY                        HSV(060, 0x11, 0x59) // #595953
#define HSV_DARK_GRAYISH_OLIVE                       HSV(060, 0x41, 0x59) // #595942
#define HSV_DARK_OLIVE                               HSV(060, 0x8f, 0x59) // #595927
#define HSV_DEEP_OLIVE                               HSV(060, 0xff, 0x59) // #595900
#define HSV_YELLOWISH_BLACK                          HSV(060, 0x1a, 0x1d) // #1d1d1a
#define HSV_VERY_DARK_OLIVE                          HSV(060, 0x69, 0x1d) // #1d1d11
#define HSV_VERY_DEEP_OLIVE                          HSV(060, 0xff, 0x1d) // #1d1d00
#define HSV_PALE_APPLE_GREEN                         HSV(067, 0x3d, 0xff) // #f7ffc2
#define HSV_VERY_LIGHT_APPLE_GREEN                   HSV(067, 0x61, 0xff) // #f3ff9e
#define HSV_LIGHT_BRILLIANT_APPLE_GREEN              HSV(067, 0x9a, 0xff) // #ecff65
#define HSV_LUMINOUS_VIVID_APPLE_GREEN               HSV(067, 0xff, 0xff) // #dfff00
#define HSV_LIGHT_APPLE_GREEN                        HSV(067, 0x65, 0xe7) // #dce78b
#define HSV_BRILLIANT_APPLE_GREEN                    HSV(067, 0xa5, 0xe7) // #d5e751
#define HSV_VIVID_APPLE_GREEN                        HSV(067, 0xff, 0xe7) // #cae700
#define HSV_MODERATE_APPLE_GREEN                     HSV(067, 0x8e, 0xa8) // #9ca84a
#define HSV_STRONG_APPLE_GREEN                       HSV(067, 0xff, 0xa8) // #93a800
#define HSV_DARK_APPLE_GREEN                         HSV(067, 0x8f, 0x59) // #535927
#define HSV_DEEP_APPLE_GREEN                         HSV(067, 0xff, 0x59) // #4e5900
#define HSV_VERY_PALE_LIME_GREEN                     HSV(074, 0x1d, 0xff) // #f8ffe2
#define HSV_PALE_LIME_GREEN                          HSV(074, 0x3d, 0xff) // #f0ffc2
#define HSV_VERY_LIGHT_LIME_GREEN                    HSV(074, 0x61, 0xff) // #e7ff9e
#define HSV_LIGHT_BRILLIANT_LIME_GREEN               HSV(075, 0x9a, 0xff) // #d8ff65
#define HSV_LUMINOUS_VIVID_LIME_GREEN                HSV(075, 0xff, 0xff) // #bfff00
#define HSV_PALE__LIGHT_GRAYISH_LIME_GREEN           HSV(074, 0x33, 0xe7) // #dce7b8
#define HSV_LIGHT_LIME_GREEN                         HSV(075, 0x65, 0xe7) // #d0e78b
#define HSV_BRILLIANT_LIME_GREEN                     HSV(074, 0xa5, 0xe7) // #c2e751
#define HSV_VIVID_LIME_GREEN                         HSV(074, 0xff, 0xe7) // #aee700
#define HSV_GRAYISH_LIME_GREEN                       HSV(073, 0x41, 0xa8) // #9ea87d
#define HSV_MODERATE_LIME_GREEN                      HSV(074, 0x8e, 0xa8) // #91a84a
#define HSV_STRONG_LIME_GREEN                        HSV(075, 0xff, 0xa8) // #7ea800
#define HSV_DARK_GRAYISH_LIME_GREEN                  HSV(073, 0x41, 0x59) // #545942
#define HSV_DARK_LIME_GREEN                          HSV(074, 0x8f, 0x59) // #4d5927
#define HSV_DEEP_LIME_GREEN                          HSV(074, 0xff, 0x59) // #435900
#define HSV_PALE_SPRING_BUD                          HSV(082, 0x3d, 0xff) // #e8ffc2
#define HSV_VERY_LIGHT_SPRING_BUD                    HSV(082, 0x61, 0xff) // #dbff9e
#define HSV_LIGHT_BRILLIANT_SPRING_BUD               HSV(082, 0x9a, 0xff) // #c5ff65
#define HSV_LUMINOUS_VIVID_SPRING_BUD                HSV(082, 0xff, 0xff) // #9fff00
#define HSV_LIGHT_SPRING_BUD                         HSV(082, 0x65, 0xe7) // #c5e78b
#define HSV_BRILLIANT_SPRING_BUD                     HSV(082, 0xa5, 0xe7) // #afe751
#define HSV_VIVID_SPRING_BUD                         HSV(082, 0xff, 0xe7) // #91e700
#define HSV_MODERATE_SPRING_BUD                      HSV(082, 0x8e, 0xa8) // #85a84a
#define HSV_STRONG_SPRING_BUD                        HSV(082, 0xff, 0xa8) // #69a800
#define HSV_DARK_SPRING_BUD                          HSV(082, 0x8f, 0x59) // #465927
#define HSV_DEEP_SPRING_BUD                          HSV(082, 0xff, 0x59) // #385900
#define HSV_VERY_PALE_CHARTREUSE_GREEN               HSV(091, 0x1d, 0xff) // #f0ffe2
#define HSV_PALE_CHARTREUSE_GREEN                    HSV(090, 0x3d, 0xff) // #e0ffc2
#define HSV_VERY_LIGHT_CHARTREUSE_GREEN              HSV(089, 0x61, 0xff) // #cfff9e
#define HSV_LIGHT_BRILLIANT_CHARTREUSE_GREEN         HSV(090, 0x9a, 0xff) // #b2ff65
#define HSV_LUMINOUS_VIVID_CHARTREUSE_GREEN          HSV(089, 0xff, 0xff) // #80ff00
#define HSV_PALE__LIGHT_GRAYISH_CHARTREUSE_GREEN     HSV(089, 0x33, 0xe7) // #d0e7b8
#define HSV_LIGHT_CHARTREUSE_GREEN                   HSV(090, 0x65, 0xe7) // #b9e78b
#define HSV_BRILLIANT_CHARTREUSE_GREEN               HSV(090, 0xa5, 0xe7) // #9ce751
#define HSV_VIVID_CHARTREUSE_GREEN                   HSV(089, 0xff, 0xe7) // #74e700
#define HSV_GRAYISH_CHARTREUSE_GREEN                 HSV(089, 0x41, 0xa8) // #93a87d
#define HSV_MODERATE_CHARTREUSE_GREEN                HSV(090, 0x8e, 0xa8) // #79a84a
#define HSV_STRONG_CHARTREUSE_GREEN                  HSV(090, 0xff, 0xa8) // #54a800
#define HSV_DARK_GRAYISH_CHARTREUSE_GREEN            HSV(088, 0x41, 0x59) // #4e5942
#define HSV_DARK_CHARTREUSE_GREEN                    HSV(090, 0x8f, 0x59) // #405927
#define HSV_DEEP_CHARTREUSE_GREEN                    HSV(089, 0xff, 0x59) // #2d5900
#define HSV_VERY_DARK_CHARTREUSE_GREEN               HSV(090, 0x69, 0x1d) // #171d11
#define HSV_VERY_DEEP_CHARTREUSE_GREEN               HSV(091, 0xff, 0x1d) // #0e1d00
#define HSV_PALE_PISTACHIO                           HSV(097, 0x3d, 0xff) // #d9ffc2
#define HSV_VERY_LIGHT_PISTACHIO                     HSV(097, 0x61, 0xff) // #c2ff9e
#define HSV_LIGHT_BRILLIANT_PISTACHIO                HSV(097, 0x9a, 0xff) // #9fff65
#define HSV_LUMINOUS_VIVID_PISTACHIO                 HSV(097, 0xff, 0xff) // #60ff00
#define HSV_LIGHT_PISTACHIO                          HSV(097, 0x65, 0xe7) // #aee78b
#define HSV_BRILLIANT_PISTACHIO                      HSV(097, 0xa5, 0xe7) // #89e751
#define HSV_VIVID_PISTACHIO                          HSV(097, 0xff, 0xe7) // #57e700
#define HSV_MODERATE_PISTACHIO                       HSV(097, 0x8e, 0xa8) // #6da84a
#define HSV_STRONG_PISTACHIO                         HSV(097, 0xff, 0xa8) // #3fa800
#define HSV_DARK_PISTACHIO                           HSV(097, 0x8f, 0x59) // #3a5927
#define HSV_DEEP_PISTACHIO                           HSV(097, 0xff, 0x59) // #215900
#define HSV_VERY_PALE_HARLEQUIN                      HSV(105, 0x1d, 0xff) // #e9ffe2
#define HSV_PALE_HARLEQUIN                           HSV(105, 0x3d, 0xff) // #d1ffc2
#define HSV_VERY_LIGHT_HARLEQUIN                     HSV(105, 0x61, 0xff) // #b6ff9e
#define HSV_LIGHT_BRILLIANT_HARLEQUIN                HSV(105, 0x9a, 0xff) // #8bff65
#define HSV_LUMINOUS_VIVID_HARLEQUIN                 HSV(104, 0xff, 0xff) // #40ff00
#define HSV_PALE_LIGHT_GRAYISH_HARLEQUIN             HSV(104, 0x33, 0xe7) // #c4e7b8
#define HSV_LIGHT_HARLEQUIN                          HSV(105, 0x65, 0xe7) // #a2e78b
#define HSV_BRILLIANT_HARLEQUIN                      HSV(104, 0xa5, 0xe7) // #77e751
#define HSV_VIVID_HARLEQUIN                          HSV(104, 0xff, 0xe7) // #3ae700
#define HSV_GRAYISH_HARLEQUIN                        HSV(104, 0x41, 0xa8) // #88a87d
#define HSV_MODERATE_HARLEQUIN                       HSV(105, 0x8e, 0xa8) // #61a84a
#define HSV_STRONG_HARLEQUIN                         HSV(105, 0xff, 0xa8) // #2aa800
#define HSV_DARK_GRAYISH_HARLEQUIN                   HSV(104, 0x41, 0x59) // #485942
#define HSV_DARK_HARLEQUIN                           HSV(104, 0x8f, 0x59) // #345927
#define HSV_DEEP_HARLEQUIN                           HSV(105, 0xff, 0x59) // #165900
#define HSV_PALE_SAP_GREEN                           HSV(113, 0x3d, 0xff) // #c9ffc2
#define HSV_VERY_LIGHT_SAP_GREEN                     HSV(112, 0x61, 0xff) // #aaff9e
#define HSV_LIGHT_BRILLIANT_SAP_GREEN                HSV(112, 0x9a, 0xff) // #78ff65
#define HSV_LUMINOUS_VIVID_SAP_GREEN                 HSV(112, 0xff, 0xff) // #20ff00
#define HSV_LIGHT_SAP_GREEN                          HSV(112, 0x65, 0xe7) // #96e78b
#define HSV_BRILLIANT_SAP_GREEN                      HSV(112, 0xa5, 0xe7) // #64e751
#define HSV_VIVID_SAP_GREEN                          HSV(112, 0xff, 0xe7) // #1de700
#define HSV_MODERATE_SAP_GREEN                       HSV(112, 0x8e, 0xa8) // #55a84a
#define HSV_STRONG_SAP_GREEN                         HSV(112, 0xff, 0xa8) // #15a800
#define HSV_DARK_SAP_GREEN                           HSV(112, 0x8f, 0x59) // #2d5927
#define HSV_DEEP_SAP_GREEN                           HSV(112, 0xff, 0x59) // #0b5900
#define HSV_GREENISH_WHITE                           HSV(120, 0x08, 0xff) // #f6fff6
#define HSV_VERY_PALE_GREEN                          HSV(120, 0x1d, 0xff) // #e2ffe2
#define HSV_PALE_GREEN                               HSV(120, 0x3d, 0xff) // #c2ffc2
#define HSV_VERY_LIGHT_GREEN                         HSV(120, 0x61, 0xff) // #9eff9e
#define HSV_LIGHT_BRILLIANT_GREEN                    HSV(120, 0x9a, 0xff) // #65ff65
#define HSV_LUMINOUS_VIVID_GREEN                     HSV(120, 0xff, 0xff) // #00ff00
#define HSV_LIGHT_GREENISH_GRAY                      HSV(120, 0x0e, 0xe7) // #dae7da
#define HSV_PALE__LIGHT_GRAYISH_GREEN                HSV(120, 0x33, 0xe7) // #b8e7b8
#define HSV_LIGHT_GREEN                              HSV(120, 0x65, 0xe7) // #8be78b
#define HSV_BRILLIANT_GREEN                          HSV(120, 0xa5, 0xe7) // #51e751
#define HSV_VIVID_GREEN                              HSV(120, 0xff, 0xe7) // #00e700
#define HSV_GREENISH_GRAY                            HSV(120, 0x12, 0xa8) // #9ca89c
#define HSV_GRAYISH_GREEN                            HSV(120, 0x41, 0xa8) // #7da87d
#define HSV_MODERATE_GREEN                           HSV(120, 0x8e, 0xa8) // #4aa84a
#define HSV_STRONG_GREEN                             HSV(120, 0xff, 0xa8) // #00a800
#define HSV_DARK_GREENISH_GRAY                       HSV(120, 0x11, 0x59) // #535953
#define HSV_DARK_GRAYISH_GREEN                       HSV(120, 0x41, 0x59) // #425942
#define HSV_DARK_GREEN                               HSV(120, 0x8f, 0x59) // #275927
#define HSV_DEEP_GREEN                               HSV(120, 0xff, 0x59) // #005900
#define HSV_GREENISH_BLACK                           HSV(120, 0x1a, 0x1d) // #1a1d1a
#define HSV_VERY_DARK_GREEN                          HSV(120, 0x69, 0x1d) // #111d11
#define HSV_VERY_DEEP_GREEN                          HSV(120, 0xff, 0x1d) // #001d00
#define HSV_PALE_EMERALD_GREEN                       HSV(126, 0x3d, 0xff) // #c2ffc9
#define HSV_VERY_LIGHT_EMERALD_GREEN                 HSV(127, 0x61, 0xff) // #9effaa
#define HSV_LIGHT_BRILLIANT_EMERALD_GREEN            HSV(127, 0x9a, 0xff) // #65ff78
#define HSV_LUMINOUS_VIVID_EMERALD_GREEN             HSV(127, 0xff, 0xff) // #00ff20
#define HSV_LIGHT_EMERALD_GREEN                      HSV(127, 0x65, 0xe7) // #8be796
#define HSV_BRILLIANT_EMERALD_GREEN                  HSV(127, 0xa5, 0xe7) // #51e764
#define HSV_VIVID_EMERALD_GREEN                      HSV(127, 0xff, 0xe7) // #00e71d
#define HSV_MODERATE_EMERALD_GREEN                   HSV(127, 0x8e, 0xa8) // #4aa855
#define HSV_STRONG_EMERALD_GREEN                     HSV(127, 0xff, 0xa8) // #00a815
#define HSV_DARK_EMERALD_GREEN                       HSV(127, 0x8f, 0x59) // #27592d
#define HSV_DEEP_EMERALD_GREEN                       HSV(127, 0xff, 0x59) // #00590b
#define HSV_VERY_PALE_MALACHITE_GREEN                HSV(134, 0x1d, 0xff) // #e2ffe9
#define HSV_PALE_MALACHITE_GREEN                     HSV(134, 0x3d, 0xff) // #c2ffd1
#define HSV_VERY_LIGHT_MALACHITE_GREEN               HSV(134, 0x61, 0xff) // #9effb6
#define HSV_LIGHT_BRILLIANT_MALACHITE_GREEN          HSV(134, 0x9a, 0xff) // #65ff8b
#define HSV_LUMINOUS_VIVID_MALACHITE_GREEN           HSV(135, 0xff, 0xff) // #00ff40
#define HSV_PALE__LIGHT_GRAYISH_MALACHITE_GREEN      HSV(135, 0x33, 0xe7) // #b8e7c4
#define HSV_LIGHT_MALACHITE_GREEN                    HSV(135, 0x65, 0xe7) // #8be7a2
#define HSV_BRILLIANT_MALACHITE_GREEN                HSV(135, 0xa5, 0xe7) // #51e777
#define HSV_VIVID_MALACHITE_GREEN                    HSV(135, 0xff, 0xe7) // #00e73a
#define HSV_GRAYISH_MALACHITE_GREEN                  HSV(135, 0x41, 0xa8) // #7da888
#define HSV_MODERATE_MALACHITE_GREEN                 HSV(134, 0x8e, 0xa8) // #4aa861
#define HSV_STRONG_MALACHITE_GREEN                   HSV(135, 0xff, 0xa8) // #00a82a
#define HSV_DARK_GRAYISH_MALACHITE_GREEN             HSV(135, 0x41, 0x59) // #425948
#define HSV_DARK_MALACHITE_GREEN                     HSV(135, 0x8f, 0x59) // #275934
#define HSV_DEEP_MALACHITE_GREEN                     HSV(134, 0xff, 0x59) // #005916
#define HSV_PALE_SEA_GREEN                           HSV(142, 0x3d, 0xff) // #c2ffd9
#define HSV_VERY_LIGHT_SEA_GREEN                     HSV(142, 0x61, 0xff) // #9effc2
#define HSV_LIGHT_BRILLIANT_SEA_GREEN                HSV(142, 0x9a, 0xff) // #65ff9f
#define HSV_LUMINOUS_VIVID_SEA_GREEN                 HSV(142, 0xff, 0xff) // #00ff60
#define HSV_LIGHT_SEA_GREEN                          HSV(142, 0x65, 0xe7) // #8be7ae
#define HSV_BRILLIANT_SEA_GREEN                      HSV(142, 0xa5, 0xe7) // #51e789
#define HSV_VIVID_SEA_GREEN                          HSV(142, 0xff, 0xe7) // #00e757
#define HSV_MODERATE_SEA_GREEN                       HSV(142, 0x8e, 0xa8) // #4aa86d
#define HSV_STRONG_SEA_GREEN                         HSV(142, 0xff, 0xa8) // #00a83f
#define HSV_DARK_SEA_GREEN                           HSV(142, 0x8f, 0x59) // #27593a
#define HSV_DEEP_SEA_GREEN                           HSV(142, 0xff, 0x59) // #005921
#define HSV_VERY_PALE_SPRING_GREEN                   HSV(148, 0x1d, 0xff) // #e2fff0
#define HSV_PALE_SPRING_GREEN                        HSV(149, 0x3d, 0xff) // #c2ffe0
#define HSV_VERY_LIGHT_SPRING_GREEN                  HSV(150, 0x61, 0xff) // #9effcf
#define HSV_LIGHT_BRILLIANT_SPRING_GREEN             HSV(150, 0x9a, 0xff) // #65ffb2
#define HSV_LUMINOUS_VIVID_SPRING_GREEN              HSV(150, 0xff, 0xff) // #00ff80
#define HSV_PALE__LIGHT_GRAYISH_SPRING_GREEN         HSV(150, 0x33, 0xe7) // #b8e7d0
#define HSV_LIGHT_SPRING_GREEN                       HSV(150, 0x65, 0xe7) // #8be7b9
#define HSV_BRILLIANT_SPRING_GREEN                   HSV(150, 0xa5, 0xe7) // #51e79c
#define HSV_VIVID_SPRING_GREEN                       HSV(150, 0xff, 0xe7) // #00e774
#define HSV_GRAYISH_SPRING_GREEN                     HSV(150, 0x41, 0xa8) // #7da893
#define HSV_MODERATE_SPRING_GREEN                    HSV(150, 0x8e, 0xa8) // #4aa879
#define HSV_STRONG_SPRING_GREEN                      HSV(150, 0xff, 0xa8) // #00a854
#define HSV_DARK_GRAYISH_SPRING_GREEN                HSV(151, 0x41, 0x59) // #42594e
#define HSV_DARK_SPRING_GREEN                        HSV(150, 0x8f, 0x59) // #275940
#define HSV_DEEP_SPRING_GREEN                        HSV(150, 0xff, 0x59) // #00592d
#define HSV_VERY_DARK_SPRING_GREEN                   HSV(150, 0x69, 0x1d) // #111d17
#define HSV_VERY_DEEP_SPRING_GREEN                   HSV(148, 0xff, 0x1d) // #001d0e
#define HSV_PALE_AQUAMARINE                          HSV(157, 0x3d, 0xff) // #c2ffe8
#define HSV_VERY_LIGHT_AQUAMARINE                    HSV(157, 0x61, 0xff) // #9effdb
#define HSV_LIGHT_BRILLIANT_AQUAMARINE               HSV(157, 0x9a, 0xff) // #65ffc5
#define HSV_LUMINOUS_VIVID_AQUAMARINE                HSV(157, 0xff, 0xff) // #00ff9f
#define HSV_LIGHT_AQUAMARINE                         HSV(157, 0x65, 0xe7) // #8be7c5
#define HSV_BRILLIANT_AQUAMARINE                     HSV(157, 0xa5, 0xe7) // #51e7af
#define HSV_VIVID_AQUAMARINE                         HSV(157, 0xff, 0xe7) // #00e791
#define HSV_MODERATE_AQUAMARINE                      HSV(157, 0x8e, 0xa8) // #4aa885
#define HSV_STRONG_AQUAMARINE                        HSV(157, 0xff, 0xa8) // #00a869
#define HSV_DARK_AQUAMARINE                          HSV(157, 0x8f, 0x59) // #275946
#define HSV_DEEP_AQUAMARINE                          HSV(157, 0xff, 0x59) // #005938
#define HSV_VERY_PALE_TURQUOISE                      HSV(165, 0x1d, 0xff) // #e2fff8
#define HSV_PALE_TURQUOISE                           HSV(165, 0x3d, 0xff) // #c2fff0
#define HSV_VERY_LIGHT_TURQUOISE                     HSV(165, 0x61, 0xff) // #9effe7
#define HSV_LIGHT_BRILLIANT_TURQUOISE                HSV(164, 0x9a, 0xff) // #65ffd8
#define HSV_LUMINOUS_VIVID_TURQUOISE                 HSV(164, 0xff, 0xff) // #00ffbf
#define HSV_PALE__LIGHT_GRAYISH_TURQUOISE            HSV(165, 0x33, 0xe7) // #b8e7dc
#define HSV_LIGHT_TURQUOISE                          HSV(165, 0x65, 0xe7) // #8be7d0
#define HSV_BRILLIANT_TURQUOISE                      HSV(165, 0xa5, 0xe7) // #51e7c2
#define HSV_VIVID_TURQUOISE                          HSV(165, 0xff, 0xe7) // #00e7ae
#define HSV_GRAYISH_TURQUOISE                        HSV(166, 0x41, 0xa8) // #7da89e
#define HSV_MODERATE_TURQUOISE                       HSV(165, 0x8e, 0xa8) // #4aa891
#define HSV_STRONG_TURQUOISE                         HSV(165, 0xff, 0xa8) // #00a87e
#define HSV_DARK_GRAYISH_TURQUOISE                   HSV(166, 0x41, 0x59) // #425954
#define HSV_DARK_TURQUOISE                           HSV(165, 0x8f, 0x59) // #27594d
#define HSV_DEEP_TURQUOISE                           HSV(165, 0xff, 0x59) // #005943
#define HSV_PALE_OPAL                                HSV(172, 0x3d, 0xff) // #c2fff7
#define HSV_VERY_LIGHT_OPAL                          HSV(172, 0x61, 0xff) // #9efff3
#define HSV_LIGHT_BRILLIANT_OPAL                     HSV(172, 0x9a, 0xff) // #65ffec
#define HSV_LUMINOUS_VIVID_OPAL                      HSV(172, 0xff, 0xff) // #00ffdf
#define HSV_LIGHT_OPAL                               HSV(172, 0x65, 0xe7) // #8be7dc
#define HSV_BRILLIANT_OPAL                           HSV(172, 0xa5, 0xe7) // #51e7d5
#define HSV_VIVID_OPAL                               HSV(172, 0xff, 0xe7) // #00e7ca
#define HSV_MODERATE_OPAL                            HSV(172, 0x8e, 0xa8) // #4aa89c
#define HSV_STRONG_OPAL                              HSV(172, 0xff, 0xa8) // #00a893
#define HSV_DARK_OPAL                                HSV(172, 0x8f, 0x59) // #275953
#define HSV_DEEP_OPAL                                HSV(172, 0xff, 0x59) // #00594e
#define HSV_CYANISH_WHITE                            HSV(180, 0x08, 0xff) // #f6ffff
#define HSV_VERY_PALE_CYAN                           HSV(180, 0x1d, 0xff) // #e2ffff
#define HSV_PALE_CYAN                                HSV(180, 0x3d, 0xff) // #c2ffff
#define HSV_VERY_LIGHT_CYAN                          HSV(180, 0x61, 0xff) // #9effff
#define HSV_LIGHT_BRILLIANT_CYAN                     HSV(180, 0x9a, 0xff) // #65ffff
#define HSV_LUMINOUS_VIVID_CYAN                      HSV(180, 0xff, 0xff) // #00ffff
#define HSV_LIGHT_CYANISH_GRAY                       HSV(180, 0x0e, 0xe7) // #dae7e7
#define HSV_PALE__LIGHT_GRAYISH_CYAN                 HSV(180, 0x33, 0xe7) // #b8e7e7
#define HSV_LIGHT_CYAN                               HSV(180, 0x65, 0xe7) // #8be7e7
#define HSV_BRILLIANT_CYAN                           HSV(180, 0xa5, 0xe7) // #51e7e7
#define HSV_VIVID_CYAN                               HSV(180, 0xff, 0xe7) // #00e7e7
#define HSV_CYANISH_GRAY                             HSV(180, 0x12, 0xa8) // #9ca8a8
#define HSV_GRAYISH_CYAN                             HSV(180, 0x41, 0xa8) // #7da8a8
#define HSV_MODERATE_CYAN                            HSV(180, 0x8e, 0xa8) // #4aa8a8
#define HSV_STRONG_CYAN                              HSV(180, 0xff, 0xa8) // #00a8a8
#define HSV_DARK_CYANISH_GRAY                        HSV(180, 0x11, 0x59) // #535959
#define HSV_DARK_GRAYISH_CYAN                        HSV(180, 0x41, 0x59) // #425959
#define HSV_DARK_CYAN                                HSV(180, 0x8f, 0x59) // #275959
#define HSV_DEEP_CYAN                                HSV(180, 0xff, 0x59) // #005959
#define HSV_CYANISH_BLACK                            HSV(180, 0x1a, 0x1d) // #1a1d1d
#define HSV_VERY_DARK_CYAN                           HSV(180, 0x69, 0x1d) // #111d1d
#define HSV_VERY_DEEP_CYAN                           HSV(180, 0xff, 0x1d) // #001d1d
#define HSV_PALE_ARCTIC_BLUE                         HSV(187, 0x3d, 0xff) // #c2f7ff
#define HSV_VERY_LIGHT_ARCTIC_BLUE                   HSV(187, 0x61, 0xff) // #9ef3ff
#define HSV_LIGHT_BRILLIANT_ARCTIC_BLUE              HSV(187, 0x9a, 0xff) // #65ecff
#define HSV_LUMINOUS_VIVID_ARCTIC_BLUE               HSV(187, 0xff, 0xff) // #00dfff
#define HSV_LIGHT_ARCTIC_BLUE                        HSV(187, 0x65, 0xe7) // #8bdce7
#define HSV_BRILLIANT_ARCTIC_BLUE                    HSV(187, 0xa5, 0xe7) // #51d5e7
#define HSV_VIVID_ARCTIC_BLUE                        HSV(187, 0xff, 0xe7) // #00cae7
#define HSV_MODERATE_ARCTIC_BLUE                     HSV(187, 0x8e, 0xa8) // #4a9ca8
#define HSV_STRONG_ARCTIC_BLUE                       HSV(187, 0xff, 0xa8) // #0093a8
#define HSV_DARK_ARCTIC_BLUE                         HSV(187, 0x8f, 0x59) // #275359
#define HSV_DEEP_ARCTIC_BLUE                         HSV(187, 0xff, 0x59) // #004e59
#define HSV_VERY_PALE_CERULEAN                       HSV(194, 0x1d, 0xff) // #e2f8ff
#define HSV_PALE_CERULEAN                            HSV(194, 0x3d, 0xff) // #c2f0ff
#define HSV_VERY_LIGHT_CERULEAN                      HSV(194, 0x61, 0xff) // #9ee7ff
#define HSV_LIGHT_BRILLIANT_CERULEAN                 HSV(195, 0x9a, 0xff) // #65d8ff
#define HSV_LUMINOUS_VIVID_CERULEAN                  HSV(195, 0xff, 0xff) // #00bfff
#define HSV_PALE__LIGHT_GRAYISH_CERULEAN             HSV(194, 0x33, 0xe7) // #b8dce7
#define HSV_LIGHT_CERULEAN                           HSV(195, 0x65, 0xe7) // #8bd0e7
#define HSV_BRILLIANT_CERULEAN                       HSV(194, 0xa5, 0xe7) // #51c2e7
#define HSV_VIVID_CERULEAN                           HSV(194, 0xff, 0xe7) // #00aee7
#define HSV_GRAYISH_CERULEAN                         HSV(193, 0x41, 0xa8) // #7d9ea8
#define HSV_MODERATE_CERULEAN                        HSV(194, 0x8e, 0xa8) // #4a91a8
#define HSV_STRONG_CERULEAN                          HSV(195, 0xff, 0xa8) // #007ea8
#define HSV_DARK_GRAYISH_CERULEAN                    HSV(193, 0x41, 0x59) // #425459
#define HSV_DARK_CERULEAN                            HSV(194, 0x8f, 0x59) // #274d59
#define HSV_DEEP_CERULEAN                            HSV(194, 0xff, 0x59) // #004359
#define HSV_PALE_CORNFLOWER_BLUE                     HSV(202, 0x3d, 0xff) // #c2e8ff
#define HSV_VERY_LIGHT_CORNFLOWER_BLUE               HSV(202, 0x61, 0xff) // #9edbff
#define HSV_LIGHT_BRILLIANT_CORNFLOWER_BLUE          HSV(202, 0x9a, 0xff) // #65c5ff
#define HSV_LUMINOUS_VIVID_CORNFLOWER_BLUE           HSV(202, 0xff, 0xff) // #009fff
#define HSV_LIGHT_CORNFLOWER_BLUE                    HSV(202, 0x65, 0xe7) // #8bc5e7
#define HSV_BRILLIANT_CORNFLOWER_BLUE                HSV(202, 0xa5, 0xe7) // #51afe7
#define HSV_VIVID_CORNFLOWER_BLUE                    HSV(202, 0xff, 0xe7) // #0091e7
#define HSV_MODERATE_CORNFLOWER_BLUE                 HSV(202, 0x8e, 0xa8) // #4a85a8
#define HSV_STRONG_CORNFLOWER_BLUE                   HSV(202, 0xff, 0xa8) // #0069a8
#define HSV_DARK_CORNFLOWER_BLUE                     HSV(202, 0x8f, 0x59) // #274659
#define HSV_DEEP_CORNFLOWER_BLUE                     HSV(202, 0xff, 0x59) // #003859
#define HSV_VERY_PALE_AZURE                          HSV(211, 0x1d, 0xff) // #e2f0ff
#define HSV_PALE_AZURE                               HSV(210, 0x3d, 0xff) // #c2e0ff
#define HSV_VERY_LIGHT_AZURE                         HSV(209, 0x61, 0xff) // #9ecfff
#define HSV_LIGHT_BRILLIANT_AZURE                    HSV(210, 0x9a, 0xff) // #65b2ff
#define HSV_LUMINOUS_VIVID_AZURE                     HSV(209, 0xff, 0xff) // #0080ff
#define HSV_PALE__LIGHT_GRAYISH_AZURE                HSV(209, 0x33, 0xe7) // #b8d0e7
#define HSV_LIGHT_AZURE                              HSV(210, 0x65, 0xe7) // #8bb9e7
#define HSV_BRILLIANT_AZURE                          HSV(210, 0xa5, 0xe7) // #519ce7
#define HSV_VIVID_AZURE                              HSV(209, 0xff, 0xe7) // #0074e7
#define HSV_GRAYISH_AZURE                            HSV(209, 0x41, 0xa8) // #7d93a8
#define HSV_MODERATE_AZURE                           HSV(210, 0x8e, 0xa8) // #4a79a8
#define HSV_STRONG_AZURE                             HSV(210, 0xff, 0xa8) // #0054a8
#define HSV_DARK_GRAYISH_AZURE                       HSV(208, 0x41, 0x59) // #424e59
#define HSV_DARK_AZURE                               HSV(210, 0x8f, 0x59) // #274059
#define HSV_DEEP_AZURE                               HSV(209, 0xff, 0x59) // #002d59
#define HSV_VERY_DARK_AZURE                          HSV(210, 0x69, 0x1d) // #11171d
#define HSV_VERY_DEEP_AZURE                          HSV(211, 0xff, 0x1d) // #000e1d
#define HSV_PALE_COBALT_BLUE                         HSV(217, 0x3d, 0xff) // #c2d9ff
#define HSV_VERY_LIGHT_COBALT_BLUE                   HSV(217, 0x61, 0xff) // #9ec2ff
#define HSV_LIGHT_BRILLIANT_COBALT_BLUE              HSV(217, 0x9a, 0xff) // #659fff
#define HSV_LUMINOUS_VIVID_COBALT_BLUE               HSV(217, 0xff, 0xff) // #0060ff
#define HSV_LIGHT_COBALT_BLUE                        HSV(217, 0x65, 0xe7) // #8baee7
#define HSV_BRILLIANT_COBALT_BLUE                    HSV(217, 0xa5, 0xe7) // #5189e7
#define HSV_VIVID_COBALT_BLUE                        HSV(217, 0xff, 0xe7) // #0057e7
#define HSV_MODERATE_COBALT_BLUE                     HSV(217, 0x8e, 0xa8) // #4a6da8
#define HSV_STRONG_COBALT_BLUE                       HSV(217, 0xff, 0xa8) // #003fa8
#define HSV_DARK_COBALT_BLUE                         HSV(217, 0x8f, 0x59) // #273a59
#define HSV_DEEP_COBALT_BLUE                         HSV(217, 0xff, 0x59) // #002159
#define HSV_VERY_PALE_SAPPHIRE_BLUE                  HSV(225, 0x1d, 0xff) // #e2e9ff
#define HSV_PALE_SAPPHIRE_BLUE                       HSV(225, 0x3d, 0xff) // #c2d1ff
#define HSV_VERY_LIGHT_SAPPHIRE_BLUE                 HSV(225, 0x61, 0xff) // #9eb6ff
#define HSV_LIGHT_BRILLIANT_SAPPHIRE_BLUE            HSV(225, 0x9a, 0xff) // #658bff
#define HSV_LUMINOUS_VIVID_SAPPHIRE_BLUE             HSV(224, 0xff, 0xff) // #0040ff
#define HSV_PALE__LIGHT_GRAYISH_SAPPHIRE_BLUE        HSV(224, 0x33, 0xe7) // #b8c4e7
#define HSV_LIGHT_SAPPHIRE_BLUE                      HSV(225, 0x65, 0xe7) // #8ba2e7
#define HSV_BRILLIANT_SAPPHIRE_BLUE                  HSV(224, 0xa5, 0xe7) // #5177e7
#define HSV_VIVID_SAPPHIRE_BLUE                      HSV(224, 0xff, 0xe7) // #003ae7
#define HSV_GRAYISH_SAPPHIRE_BLUE                    HSV(224, 0x41, 0xa8) // #7d88a8
#define HSV_MODERATE_SAPPHIRE_BLUE                   HSV(225, 0x8e, 0xa8) // #4a61a8
#define HSV_STRONG_SAPPHIRE_BLUE                     HSV(225, 0xff, 0xa8) // #002aa8
#define HSV_DARK_GRAYISH_SAPPHIRE_BLUE               HSV(224, 0x41, 0x59) // #424859
#define HSV_DARK_SAPPHIRE_BLUE                       HSV(224, 0x8f, 0x59) // #273459
#define HSV_DEEP_SAPPHIRE_BLUE                       HSV(225, 0xff, 0x59) // #001659
#define HSV_PALE_PHTHALO_BLUE                        HSV(233, 0x3d, 0xff) // #c2c9ff
#define HSV_VERY_LIGHT_PHTHALO_BLUE                  HSV(232, 0x61, 0xff) // #9eaaff
#define HSV_LIGHT_BRILLIANT_PHTHALO_BLUE             HSV(232, 0x9a, 0xff) // #6578ff
#define HSV_LUMINOUS_VIVID_PHTHALO_BLUE              HSV(232, 0xff, 0xff) // #0020ff
#define HSV_LIGHT_PHTHALO_BLUE                       HSV(232, 0x65, 0xe7) // #8b96e7
#define HSV_BRILLIANT_PHTHALO_BLUE                   HSV(232, 0xa5, 0xe7) // #5164e7
#define HSV_VIVID_PHTHALO_BLUE                       HSV(232, 0xff, 0xe7) // #001de7
#define HSV_MODERATE_PHTHALO_BLUE                    HSV(232, 0x8e, 0xa8) // #4a55a8
#define HSV_STRONG_PHTHALO_BLUE                      HSV(232, 0xff, 0xa8) // #0015a8
#define HSV_DARK_PHTHALO_BLUE                        HSV(232, 0x8f, 0x59) // #272d59
#define HSV_DEEP_PHTHALO_BLUE                        HSV(232, 0xff, 0x59) // #000b59
#define HSV_BLUISH_WHITE                             HSV(240, 0x08, 0xff) // #f6f6ff
#define HSV_VERY_PALE_BLUE                           HSV(240, 0x1d, 0xff) // #e2e2ff
#define HSV_PALE_BLUE                                HSV(240, 0x3d, 0xff) // #c2c2ff
#define HSV_VERY_LIGHT_BLUE                          HSV(240, 0x61, 0xff) // #9e9eff
#define HSV_LIGHT_BRILLIANT_BLUE                     HSV(240, 0x9a, 0xff) // #6565ff
#define HSV_LUMINOUS_VIVID_BLUE                      HSV(240, 0xff, 0xff) // #0000ff
#define HSV_LIGHT_BLUISH_GRAY                        HSV(240, 0x0e, 0xe7) // #dadae7
#define HSV_PALE__LIGHT_GRAYISH_BLUE                 HSV(240, 0x33, 0xe7) // #b8b8e7
#define HSV_LIGHT_BLUE                               HSV(240, 0x65, 0xe7) // #8b8be7
#define HSV_BRILLIANT_BLUE                           HSV(240, 0xa5, 0xe7) // #5151e7
#define HSV_VIVID_BLUE                               HSV(240, 0xff, 0xe7) // #0000e7
#define HSV_BLUISH_GRAY                              HSV(240, 0x12, 0xa8) // #9c9ca8
#define HSV_GRAYISH_BLUE                             HSV(240, 0x41, 0xa8) // #7d7da8
#define HSV_MODERATE_BLUE                            HSV(240, 0x8e, 0xa8) // #4a4aa8
#define HSV_STRONG_BLUE                              HSV(240, 0xff, 0xa8) // #0000a8
#define HSV_DARK_BLUISH_GRAY                         HSV(240, 0x11, 0x59) // #535359
#define HSV_DARK_GRAYISH_BLUE                        HSV(240, 0x41, 0x59) // #424259
#define HSV_DARK_BLUE                                HSV(240, 0x8f, 0x59) // #272759
#define HSV_DEEP_BLUE                                HSV(240, 0xff, 0x59) // #000059
#define HSV_BLUISH_BLACK                             HSV(240, 0x1a, 0x1d) // #1a1a1d
#define HSV_VERY_DARK_BLUE                           HSV(240, 0x69, 0x1d) // #11111d
#define HSV_VERY_DEEP_BLUE                           HSV(240, 0xff, 0x1d) // #00001d
#define HSV_PALE_PERSIAN_BLUE                        HSV(246, 0x3d, 0xff) // #c9c2ff
#define HSV_VERY_LIGHT_PERSIAN_BLUE                  HSV(247, 0x61, 0xff) // #aa9eff
#define HSV_LIGHT_BRILLIANT_PERSIAN_BLUE             HSV(247, 0x9a, 0xff) // #7865ff
#define HSV_LUMINOUS_VIVID_PERSIAN_BLUE              HSV(247, 0xff, 0xff) // #2000ff
#define HSV_LIGHT_PERSIAN_BLUE                       HSV(247, 0x65, 0xe7) // #968be7
#define HSV_BRILLIANT_PERSIAN_BLUE                   HSV(247, 0xa5, 0xe7) // #6451e7
#define HSV_VIVID_PERSIAN_BLUE                       HSV(247, 0xff, 0xe7) // #1d00e7
#define HSV_MODERATE_PERSIAN_BLUE                    HSV(247, 0x8e, 0xa8) // #554aa8
#define HSV_STRONG_PERSIAN_BLUE                      HSV(247, 0xff, 0xa8) // #1500a8
#define HSV_DARK_PERSIAN_BLUE                        HSV(247, 0x8f, 0x59) // #2d2759
#define HSV_DEEP_PERSIAN_BLUE                        HSV(247, 0xff, 0x59) // #0b0059
#define HSV_VERY_PALE_INDIGO                         HSV(254, 0x1d, 0xff) // #e9e2ff
#define HSV_PALE_INDIGO                              HSV(254, 0x3d, 0xff) // #d1c2ff
#define HSV_VERY_LIGHT_INDIGO                        HSV(254, 0x61, 0xff) // #b69eff
#define HSV_LIGHT_BRILLIANT_INDIGO                   HSV(254, 0x9a, 0xff) // #8b65ff
#define HSV_LUMINOUS_VIVID_INDIGO                    HSV(255, 0xff, 0xff) // #4000ff
#define HSV_PALE__LIGHT_GRAYISH_INDIGO               HSV(255, 0x33, 0xe7) // #c4b8e7
#define HSV_LIGHT_INDIGO                             HSV(255, 0x65, 0xe7) // #a28be7
#define HSV_BRILLIANT_INDIGO                         HSV(255, 0xa5, 0xe7) // #7751e7
#define HSV_VIVID_INDIGO                             HSV(255, 0xff, 0xe7) // #3a00e7
#define HSV_GRAYISH_INDIGO                           HSV(255, 0x41, 0xa8) // #887da8
#define HSV_MODERATE_INDIGO                          HSV(254, 0x8e, 0xa8) // #614aa8
#define HSV_STRONG_INDIGO                            HSV(255, 0xff, 0xa8) // #2a00a8
#define HSV_DARK_GRAYISH_INDIGO                      HSV(255, 0x41, 0x59) // #484259
#define HSV_DARK_INDIGO                              HSV(255, 0x8f, 0x59) // #342759
#define HSV_DEEP_INDIGO                              HSV(254, 0xff, 0x59) // #160059
#define HSV_PALE_BLUE_VIOLET                         HSV(262, 0x3d, 0xff) // #d9c2ff
#define HSV_VERY_LIGHT_BLUE_VIOLET                   HSV(262, 0x61, 0xff) // #c29eff
#define HSV_LIGHT_BRILLIANT_BLUE_VIOLET              HSV(262, 0x9a, 0xff) // #9f65ff
#define HSV_LUMINOUS_VIVID_BLUE_VIOLET               HSV(262, 0xff, 0xff) // #6000ff
#define HSV_LIGHT_BLUE_VIOLET                        HSV(262, 0x65, 0xe7) // #ae8be7
#define HSV_BRILLIANT_BLUE_VIOLET                    HSV(262, 0xa5, 0xe7) // #8951e7
#define HSV_VIVID_BLUE_VIOLET                        HSV(262, 0xff, 0xe7) // #5700e7
#define HSV_MODERATE_BLUE_VIOLET                     HSV(262, 0x8e, 0xa8) // #6d4aa8
#define HSV_STRONG_BLUE_VIOLET                       HSV(262, 0xff, 0xa8) // #3f00a8
#define HSV_DARK_BLUE_VIOLET                         HSV(262, 0x8f, 0x59) // #3a2759
#define HSV_DEEP_BLUE_VIOLET                         HSV(262, 0xff, 0x59) // #210059
#define HSV_VERY_PALE_VIOLET                         HSV(268, 0x1d, 0xff) // #f0e2ff
#define HSV_PALE_VIOLET                              HSV(269, 0x3d, 0xff) // #e0c2ff
#define HSV_VERY_LIGHT_VIOLET                        HSV(270, 0x61, 0xff) // #cf9eff
#define HSV_LIGHT_BRILLIANT_VIOLET                   HSV(270, 0x9a, 0xff) // #b265ff
#define HSV_LUMINOUS_VIVID_VIOLET                    HSV(270, 0xff, 0xff) // #8000ff
#define HSV_PALE__LIGHT_GRAYISH_VIOLET               HSV(270, 0x33, 0xe7) // #d0b8e7
#define HSV_LIGHT_VIOLET                             HSV(270, 0x65, 0xe7) // #b98be7
#define HSV_BRILLIANT_VIOLET                         HSV(270, 0xa5, 0xe7) // #9c51e7
#define HSV_VIVID_VIOLET                             HSV(270, 0xff, 0xe7) // #7400e7
#define HSV_GRAYISH_VIOLET                           HSV(270, 0x41, 0xa8) // #937da8
#define HSV_MODERATE_VIOLET                          HSV(270, 0x8e, 0xa8) // #794aa8
#define HSV_STRONG_VIOLET                            HSV(270, 0xff, 0xa8) // #5400a8
#define HSV_DARK_GRAYISH_VIOLET                      HSV(271, 0x41, 0x59) // #4e4259
#define HSV_DARK_VIOLET                              HSV(270, 0x8f, 0x59) // #402759
#define HSV_DEEP_VIOLET                              HSV(270, 0xff, 0x59) // #2d0059
#define HSV_VERY_DARK_VIOLET                         HSV(270, 0x69, 0x1d) // #17111d
#define HSV_VERY_DEEP_VIOLET                         HSV(268, 0xff, 0x1d) // #0e001d
#define HSV_PALE_PURPLE                              HSV(277, 0x3d, 0xff) // #e8c2ff
#define HSV_VERY_LIGHT_PURPLE                        HSV(277, 0x61, 0xff) // #db9eff
#define HSV_LIGHT_BRILLIANT_PURPLE                   HSV(277, 0x9a, 0xff) // #c565ff
#define HSV_LUMINOUS_VIVID_PURPLE                    HSV(277, 0xff, 0xff) // #9f00ff
#define HSV_LIGHT_PURPLE                             HSV(277, 0x65, 0xe7) // #c58be7
#define HSV_BRILLIANT_PURPLE                         HSV(277, 0xa5, 0xe7) // #af51e7
#define HSV_VIVID_PURPLE                             HSV(277, 0xff, 0xe7) // #9100e7
#define HSV_MODERATE_PURPLE                          HSV(277, 0x8e, 0xa8) // #854aa8
#define HSV_STRONG_PURPLE                            HSV(277, 0xff, 0xa8) // #6900a8
#define HSV_DARK_PURPLE                              HSV(277, 0x8f, 0x59) // #462759
#define HSV_DEEP_PURPLE                              HSV(277, 0xff, 0x59) // #380059
#define HSV_VERY_PALE_MULBERRY                       HSV(285, 0x1d, 0xff) // #f8e2ff
#define HSV_PALE_MULBERRY                            HSV(285, 0x3d, 0xff) // #f0c2ff
#define HSV_VERY_LIGHT_MULBERRY                      HSV(285, 0x61, 0xff) // #e79eff
#define HSV_LIGHT_BRILLIANT_MULBERRY                 HSV(284, 0x9a, 0xff) // #d865ff
#define HSV_LUMINOUS_VIVID_MULBERRY                  HSV(284, 0xff, 0xff) // #bf00ff
#define HSV_PALE__LIGHT_GRAYISH_MULBERRY             HSV(285, 0x33, 0xe7) // #dcb8e7
#define HSV_LIGHT_MULBERRY                           HSV(285, 0x65, 0xe7) // #d08be7
#define HSV_BRILLIANT_MULBERRY                       HSV(285, 0xa5, 0xe7) // #c251e7
#define HSV_VIVID_MULBERRY                           HSV(285, 0xff, 0xe7) // #ae00e7
#define HSV_GRAYISH_MULBERRY                         HSV(286, 0x41, 0xa8) // #9e7da8
#define HSV_MODERATE_MULBERRY                        HSV(285, 0x8e, 0xa8) // #914aa8
#define HSV_STRONG_MULBERRY                          HSV(285, 0xff, 0xa8) // #7e00a8
#define HSV_DARK_GRAYISH_MULBERRY                    HSV(286, 0x41, 0x59) // #544259
#define HSV_DARK_MULBERRY                            HSV(285, 0x8f, 0x59) // #4d2759
#define HSV_DEEP_MULBERRY                            HSV(285, 0xff, 0x59) // #430059
#define HSV_PALE_HELIOTROPE                          HSV(292, 0x3d, 0xff) // #f7c2ff
#define HSV_VERY_LIGHT_HELIOTROPE                    HSV(292, 0x61, 0xff) // #f39eff
#define HSV_LIGHT_BRILLIANT_HELIOTROPE               HSV(292, 0x9a, 0xff) // #ec65ff
#define HSV_LUMINOUS_VIVID_HELIOTROPE                HSV(292, 0xff, 0xff) // #df00ff
#define HSV_LIGHT_HELIOTROPE                         HSV(292, 0x65, 0xe7) // #dc8be7
#define HSV_BRILLIANT_HELIOTROPE                     HSV(292, 0xa5, 0xe7) // #d551e7
#define HSV_VIVID_HELIOTROPE                         HSV(292, 0xff, 0xe7) // #ca00e7
#define HSV_MODERATE_HELIOTROPE                      HSV(292, 0x8e, 0xa8) // #9c4aa8
#define HSV_STRONG_HELIOTROPE                        HSV(292, 0xff, 0xa8) // #9300a8
#define HSV_DARK_HELIOTROPE                          HSV(292, 0x8f, 0x59) // #532759
#define HSV_DEEP_HELIOTROPE                          HSV(292, 0xff, 0x59) // #4e0059
#define HSV_MAGENTAISH_WHITE                         HSV(300, 0x08, 0xff) // #fff6ff
#define HSV_VERY_PALE_MAGENTA                        HSV(300, 0x1d, 0xff) // #ffe2ff
#define HSV_PALE_MAGENTA                             HSV(300, 0x3d, 0xff) // #ffc2ff
#define HSV_VERY_LIGHT_MAGENTA                       HSV(300, 0x61, 0xff) // #ff9eff
#define HSV_LIGHT_BRILLIANT_MAGENTA                  HSV(300, 0x9a, 0xff) // #ff65ff
#define HSV_LUMINOUS_VIVID_MAGENTA                   HSV(300, 0xff, 0xff) // #ff00ff
#define HSV_LIGHT_MAGENTAISH_GRAY                    HSV(300, 0x0e, 0xe7) // #e7dae7
#define HSV_PALE__LIGHT_GRAYISH_MAGENTA              HSV(300, 0x33, 0xe7) // #e7b8e7
#define HSV_LIGHT_MAGENTA                            HSV(300, 0x65, 0xe7) // #e78be7
#define HSV_BRILLIANT_MAGENTA                        HSV(300, 0xa5, 0xe7) // #e751e7
#define HSV_VIVID_MAGENTA                            HSV(300, 0xff, 0xe7) // #e700e7
#define HSV_MAGENTAISH_GRAY                          HSV(300, 0x12, 0xa8) // #a89ca8
#define HSV_GRAYISH_MAGENTA                          HSV(300, 0x41, 0xa8) // #a87da8
#define HSV_MODERATE_MAGENTA                         HSV(300, 0x8e, 0xa8) // #a84aa8
#define HSV_STRONG_MAGENTA                           HSV(300, 0xff, 0xa8) // #a800a8
#define HSV_DARK_MAGENTAISH_GRAY                     HSV(300, 0x11, 0x59) // #595359
#define HSV_DARK_GRAYISH_MAGENTA                     HSV(300, 0x41, 0x59) // #594259
#define HSV_DARK_MAGENTA                             HSV(300, 0x8f, 0x59) // #592759
#define HSV_DEEP_MAGENTA                             HSV(300, 0xff, 0x59) // #590059
#define HSV_MAGENTAISH_BLACK                         HSV(300, 0x1a, 0x1d) // #1d1a1d
#define HSV_VERY_DARK_MAGENTA                        HSV(300, 0x69, 0x1d) // #1d111d
#define HSV_VERY_DEEP_MAGENTA                        HSV(300, 0xff, 0x1d) // #1d001d
#define HSV_PALE_ORCHID                              HSV(307, 0x3d, 0xff) // #ffc2f7
#define HSV_VERY_LIGHT_ORCHID                        HSV(307, 0x61, 0xff) // #ff9ef3
#define HSV_LIGHT_BRILLIANT_ORCHID                   HSV(307, 0x9a, 0xff) // #ff65ec
#define HSV_LUMINOUS_VIVID_ORCHID                    HSV(307, 0xff, 0xff) // #ff00df
#define HSV_LIGHT_ORCHID                             HSV(307, 0x65, 0xe7) // #e78bdc
#define HSV_BRILLIANT_ORCHID                         HSV(307, 0xa5, 0xe7) // #e751d5
#define HSV_VIVID_ORCHID                             HSV(307, 0xff, 0xe7) // #e700ca
#define HSV_MODERATE_ORCHID                          HSV(307, 0x8e, 0xa8) // #a84a9c
#define HSV_STRONG_ORCHID                            HSV(307, 0xff, 0xa8) // #a80093
#define HSV_DARK_ORCHID                              HSV(307, 0x8f, 0x59) // #592753
#define HSV_DEEP_ORCHID                              HSV(307, 0xff, 0x59) // #59004e
#define HSV_VERY_PALE_FUCHSIA                        HSV(314, 0x1d, 0xff) // #ffe2f8
#define HSV_PALE_FUCHSIA                             HSV(314, 0x3d, 0xff) // #ffc2f0
#define HSV_VERY_LIGHT_FUCHSIA                       HSV(314, 0x61, 0xff) // #ff9ee7
#define HSV_LIGHT_BRILLIANT_FUCHSIA                  HSV(315, 0x9a, 0xff) // #ff65d8
#define HSV_LUMINOUS_VIVID_FUCHSIA                   HSV(315, 0xff, 0xff) // #ff00bf
#define HSV_PALE__LIGHT_GRAYISH_FUCHSIA              HSV(314, 0x33, 0xe7) // #e7b8dc
#define HSV_LIGHT_FUCHSIA                            HSV(315, 0x65, 0xe7) // #e78bd0
#define HSV_BRILLIANT_FUCHSIA                        HSV(314, 0xa5, 0xe7) // #e751c2
#define HSV_VIVID_FUCHSIA                            HSV(314, 0xff, 0xe7) // #e700ae
#define HSV_GRAYISH_FUCHSIA                          HSV(313, 0x41, 0xa8) // #a87d9e
#define HSV_MODERATE_FUCHSIA                         HSV(314, 0x8e, 0xa8) // #a84a91
#define HSV_STRONG_FUCHSIA                           HSV(315, 0xff, 0xa8) // #a8007e
#define HSV_DARK_GRAYISH_FUCHSIA                     HSV(313, 0x41, 0x59) // #594254
#define HSV_DARK_FUCHSIA                             HSV(314, 0x8f, 0x59) // #59274d
#define HSV_DEEP_FUCHSIA                             HSV(314, 0xff, 0x59) // #590043
#define HSV_PALE_CERISE                              HSV(322, 0x3d, 0xff) // #ffc2e8
#define HSV_VERY_LIGHT_CERISE                        HSV(322, 0x61, 0xff) // #ff9edb
#define HSV_LIGHT_BRILLIANT_CERISE                   HSV(322, 0x9a, 0xff) // #ff65c5
#define HSV_LUMINOUS_VIVID_CERISE                    HSV(322, 0xff, 0xff) // #ff009f
#define HSV_LIGHT_CERISE                             HSV(322, 0x65, 0xe7) // #e78bc5
#define HSV_BRILLIANT_CERISE                         HSV(322, 0xa5, 0xe7) // #e751af
#define HSV_VIVID_CERISE                             HSV(322, 0xff, 0xe7) // #e70091
#define HSV_MODERATE_CERISE                          HSV(322, 0x8e, 0xa8) // #a84a85
#define HSV_STRONG_CERISE                            HSV(322, 0xff, 0xa8) // #a80069
#define HSV_DARK_CERISE                              HSV(322, 0x8f, 0x59) // #592746
#define HSV_DEEP_CERISE                              HSV(322, 0xff, 0x59) // #590038
#define HSV_VERY_PALE_ROSE                           HSV(331, 0x1d, 0xff) // #ffe2f0
#define HSV_PALE_ROSE                                HSV(330, 0x3d, 0xff) // #ffc2e0
#define HSV_VERY_LIGHT_ROSE                          HSV(329, 0x61, 0xff) // #ff9ecf
#define HSV_LIGHT_BRILLIANT_ROSE                     HSV(330, 0x9a, 0xff) // #ff65b2
#define HSV_LUMINOUS_VIVID_ROSE                      HSV(329, 0xff, 0xff) // #ff0080
#define HSV_PALE__LIGHT_GRAYISH_ROSE                 HSV(329, 0x33, 0xe7) // #e7b8d0
#define HSV_LIGHT_ROSE                               HSV(330, 0x65, 0xe7) // #e78bb9
#define HSV_BRILLIANT_ROSE                           HSV(330, 0xa5, 0xe7) // #e7519c
#define HSV_VIVID_ROSE                               HSV(329, 0xff, 0xe7) // #e70074
#define HSV_GRAYISH_ROSE                             HSV(329, 0x41, 0xa8) // #a87d93
#define HSV_MODERATE_ROSE                            HSV(330, 0x8e, 0xa8) // #a84a79
#define HSV_STRONG_ROSE                              HSV(330, 0xff, 0xa8) // #a80054
#define HSV_DARK_GRAYISH_ROSE                        HSV(328, 0x41, 0x59) // #59424e
#define HSV_DARK_ROSE                                HSV(330, 0x8f, 0x59) // #592740
#define HSV_DEEP_ROSE                                HSV(329, 0xff, 0x59) // #59002d
#define HSV_VERY_DARK_ROSE                           HSV(330, 0x69, 0x1d) // #1d1117
#define HSV_VERY_DEEP_ROSE                           HSV(331, 0xff, 0x1d) // #1d000e
#define HSV_PALE_RASPBERRY                           HSV(337, 0x3d, 0xff) // #ffc2d9
#define HSV_VERY_LIGHT_RASPBERRY                     HSV(337, 0x61, 0xff) // #ff9ec2
#define HSV_LIGHT_BRILLIANT_RASPBERRY                HSV(337, 0x9a, 0xff) // #ff659f
#define HSV_LUMINOUS_VIVID_RASPBERRY                 HSV(337, 0xff, 0xff) // #ff0060
#define HSV_LIGHT_RASPBERRY                          HSV(337, 0x65, 0xe7) // #e78bae
#define HSV_BRILLIANT_RASPBERRY                      HSV(337, 0xa5, 0xe7) // #e75189
#define HSV_VIVID_RASPBERRY                          HSV(337, 0xff, 0xe7) // #e70057
#define HSV_MODERATE_RASPBERRY                       HSV(337, 0x8e, 0xa8) // #a84a6d
#define HSV_STRONG_RASPBERRY                         HSV(337, 0xff, 0xa8) // #a8003f
#define HSV_DARK_RASPBERRY                           HSV(337, 0x8f, 0x59) // #59273a
#define HSV_DEEP_RASPBERRY                           HSV(337, 0xff, 0x59) // #590021
#define HSV_VERY_PALE_CRIMSON                        HSV(345, 0x1d, 0xff) // #ffe2e9
#define HSV_PALE_CRIMSON                             HSV(345, 0x3d, 0xff) // #ffc2d1
#define HSV_VERY_LIGHT_CRIMSON                       HSV(345, 0x61, 0xff) // #ff9eb6
#define HSV_LIGHT_BRILLIANT_CRIMSON                  HSV(345, 0x9a, 0xff) // #ff658b
#define HSV_LUMINOUS_VIVID_CRIMSON                   HSV(344, 0xff, 0xff) // #ff0040
#define HSV_PALE__LIGHT_GRAYISH_CRIMSON              HSV(344, 0x33, 0xe7) // #e7b8c4
#define HSV_LIGHT_CRIMSON                            HSV(345, 0x65, 0xe7) // #e78ba2
#define HSV_BRILLIANT_CRIMSON                        HSV(344, 0xa5, 0xe7) // #e75177
#define HSV_VIVID_CRIMSON                            HSV(344, 0xff, 0xe7) // #e7003a
#define HSV_GRAYISH_CRIMSON                          HSV(344, 0x41, 0xa8) // #a87d88
#define HSV_MODERATE_CRIMSON                         HSV(345, 0x8e, 0xa8) // #a84a61
#define HSV_STRONG_CRIMSON                           HSV(345, 0xff, 0xa8) // #a8002a
#define HSV_DARK_GRAYISH_CRIMSON                     HSV(344, 0x41, 0x59) // #594248
#define HSV_DARK_CRIMSON                             HSV(344, 0x8f, 0x59) // #592734
#define HSV_DEEP_CRIMSON                             HSV(345, 0xff, 0x59) // #590016
#define HSV_PALE_AMARANTH                            HSV(353, 0x3d, 0xff) // #ffc2c9
#define HSV_VERY_LIGHT_AMARANTH                      HSV(352, 0x61, 0xff) // #ff9eaa
#define HSV_LIGHT_BRILLIANT_AMARANTH                 HSV(352, 0x9a, 0xff) // #ff6578
#define HSV_LUMINOUS_VIVID_AMARANTH                  HSV(352, 0xff, 0xff) // #ff0020
#define HSV_LIGHT_AMARANTH                           HSV(352, 0x65, 0xe7) // #e78b96
#define HSV_BRILLIANT_AMARANTH                       HSV(352, 0xa5, 0xe7) // #e75164
#define HSV_VIVID_AMARANTH                           HSV(352, 0xff, 0xe7) // #e7001d
#define HSV_MODERATE_AMARANTH                        HSV(352, 0x8e, 0xa8) // #a84a55
#define HSV_STRONG_AMARANTH                          HSV(352, 0xff, 0xa8) // #a80015
#define HSV_DARK_AMARANTH                            HSV(352, 0x8f, 0x59) // #59272d
#define HSV_DEEP_AMARANTH                            HSV(352, 0xff, 0x59) // #59000b
