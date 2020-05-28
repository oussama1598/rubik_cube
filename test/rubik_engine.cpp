#include "rubik_engine.h"

namespace {
    TEST_CASE("Test the cube movements") {
        SECTION("Test the cube with no movement") {
            Rubik rubik;

            CHECK_THAT(rubik.to_string(),
                       Catch::Equals("UUUUUUUUULLLLLLLLLFFFFFFFFFRRRRRRRRRBBBBBBBBBDDDDDDDDD"));
        }

        std::map<std::string, std::string> moves{
                {"U",                     "UUUUUUUUUFFFLLLLLLRRRFFFFFFBBBRRRRRRLLLBBBBBBDDDDDDDDD"},
                {"R",                     "UUFUUFUUFLLLLLLLLLFFDFFDFFDRRRRRRRRRUBBUBBUBBDDBDDBDDB"},
                {"F",                     "UUUUUULLLLLDLLDLLDFFFFFFFFFURRURRURRBBBBBBBBBRRRDDDDDD"},
                {"D",                     "UUUUUUUUULLLLLLBBBFFFFFFLLLRRRRRRFFFBBBBBBRRRDDDDDDDDD"},
                {"L",                     "BUUBUUBUULLLLLLLLLUFFUFFUFFRRRRRRRRRBBDBBDBBDFDDFDDFDD"},
                {"B",                     "RRRUUUUUUULLULLULLFFFFFFFFFRRDRRDRRDBBBBBBBBBDDDDDDLLL"},

                {"U'",                     "UUUUUUUUUBBBLLLLLLLLLFFFFFFFFFRRRRRRRRRBBBBBBDDDDDDDDD"},
                {"R'",                     "UUBUUBUUBLLLLLLLLLFFUFFUFFURRRRRRRRRDBBDBBDBBDDFDDFDDF"},
                {"F'",                     "UUUUUURRRLLULLULLUFFFFFFFFFDRRDRRDRRBBBBBBBBBLLLDDDDDD"},
                {"D'",                     "UUUUUUUUULLLLLLFFFFFFFFFRRRRRRRRRBBBBBBBBBLLLDDDDDDDDD"},
                {"L'",                     "FUUFUUFUULLLLLLLLLDFFDFFDFFRRRRRRRRRBBUBBUBBUBDDBDDBDD"},
                {"B'",                     "LLLUUUUUUDLLDLLDLLFFFFFFFFFRRURRURRUBBBBBBBBBDDDDDDRRR"},

                {"F2'",                   "UUUUUUDDDLLRLLRLLRFFFFFFFFFLRRLRRLRRBBBBBBBBBUUUDDDDDD"},
                {"B' R L U2 U F2 D2 U L", "DLFDUFUUFRLRULFURUBFDDFUFBDRRRLRRLLLUBBUBBDDBLRFDDFLBB"},
                {"B' L2' U2' F2 D B R2",  "DUDUULDDBRRRULRUBFFFUFFRLLURBFDRDLLDLBBBBFBFFUUBRDDRLL"},
                {"R2' F2' D' R2",         "UUUUUDUDDLLRLLRBFFBFLBFFLRFBBFRRLRRLRBBFBBFLRUUDUDDDDD"}
        };

        for (auto &move: moves) {
            SECTION("Test the rotation with " + move.first) {
                Rubik rubik;

                rubik.apply_moves(move.first);

                CHECK_THAT(rubik.to_string(),
                           Catch::Equals(move.second));
            }
        }
    }
}
