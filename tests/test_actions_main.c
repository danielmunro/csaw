#define MOCK 1
#include "header.h"

int main() {
    test_look_describes_room();
    test_mob_moves_north();
    test_mob_moves_south();
    test_invalid_move_does_nothing();
    test_moving_sends_a_room_description_to_mob();
}