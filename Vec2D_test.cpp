#include <iostream>
#include "headers/Vec2D.h"


using namespace std;

int mainVector() {
    std::cout << "--- Vec2d Class Test ---" << std::endl;

    // 1. Constructor Test
    Vec2d v1(3.0f, 4.0f);
    Vec2d v2(1.0f, 2.0f);

    std::cout << "v1: (" << v1.x << ", " << v1.y << ")" << std::endl;
    std::cout << "v2: (" << v2.x << ", " << v2.y << ")" << std::endl;

    // 2. Operator+ Test
    Vec2d v3 = v1 + v2;
    std::cout << "v1 + v2 = v3: (" << v3.x << ", " << v3.y << ")" << std::endl;

    Vec2d diff = v1 - v2;
    std::cout << "v1 - v2 = diff: (" << diff.x << ", " << diff.y << ")" << std::endl;

    // 3. Copy Constructor Test
    Vec2d v4(v1);
    std::cout << "v4 (v1 copy): (" << v4.x << ", " << v4.y << ")" << std::endl;

    // 4. Operator= Test
    Vec2d v5;
    v5 = v2;
    std::cout << "v5 (kommt v2): (" << v5.x << ", " << v5.y << ")" << std::endl;

    // 5. Skaler Test
    Vec2d v6 = v1 * 2.0f;
    std::cout << "v1 * 2 = v6: (" << v6.x << ", " << v6.y << ")" << std::endl;

    /*6. Move Constructor Test, nicht nötig
    Vec2d v_temp(10.0f, 20.0f);
    Vec2d v7(std::move(v_temp)); // v_temp -> v7
    std::cout << "v7 (new): (" << v7.x << ", " << v7.y << ")" << std::endl;*/

    std::cout << "Test completed" << std::endl;

    return 0;
}