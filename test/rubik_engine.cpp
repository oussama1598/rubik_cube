#include "rubik_engine.h"

namespace {
    TEST_CASE("Test the cube movements") {
        SECTION("Test the cube with no movement") {
            Rubik rubik;

            CHECK_THAT(rubik.to_string(),
                       Catch::Equals("UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB"));
        }

        std::map<std::string, std::string> moves{
                {"U",                     "UUUUUUUUUBBBRRRRRRRRRFFFFFFDDDDDDDDDFFFLLLLLLLLLBBBBBB"},
                {"R",                     "UUFUUFUUFRRRRRRRRRFFDFFDFFDDDBDDBDDBLLLLLLLLLUBBUBBUBB"},
                {"F",                     "UUUUUULLLURRURRURRFFFFFFFFFRRRDDDDDDLLDLLDLLDBBBBBBBBB"},
                {"D",                     "UUUUUUUUURRRRRRFFFFFFFFFLLLDDDDDDDDDLLLLLLBBBBBBBBBRRR"},
                {"L",                     "BUUBUUBUURRRRRRRRRUFFUFFUFFFDDFDDFDDLLLLLLLLLBBDBBDBBD"},
                {"B",                     "RRRUUUUUURRDRRDRRDFFFFFFFFFDDDDDDLLLULLULLULLBBBBBBBBB"},
                {"F2'",                   "UUUUUUDDDLRRLRRLRRFFFFFFFFFUUUDDDDDDLLRLLRLLRBBBBBBBBB"},
                {"B' R L U2 U F2 D2 U L", "DLFDUFUUFRRRLRRLLLBFDDFUFBDLRFDDFLBBRLRULFURUUBBUBBDDB"},
                {"B' L2' U2' F2 D B R2",  "DUDUULDDBRBFDRDLLDFFUFFRLLUUUBRDDRLLRRRULRUBFLBBBBFBFF"},
                {"R2' F2' D' R2",         "UUUUUDUDDBBFRRLRRLBFLBFFLRFUUDUDDDDDLLRLLRBFFRBBFBBFLR"}
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
