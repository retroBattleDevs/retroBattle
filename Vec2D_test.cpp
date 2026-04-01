#include <iostream>
#include "headers/Vec2D.h"

void runVectorTests() {

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

    // 6. Move Constructor Test
    Vec2d v_temp(10.0f, 20.0f);
    Vec2d v7(std::move(v_temp)); // v_temp -> v7
    std::cout << "v7 (new): (" << v7.x << ", " << v7.y << ")" << std::endl;

    std::cout << "Test completed" << std::endl;

    // 7. Skalarprodukt (Dot Product) Test
    Vec2d v_dot1(1.0f, 0.0f); // Zeigt nach rechts
    Vec2d v_dot2(0.0f, 1.0f); // Zeigt nach oben (Orthogonal/Senkrecht)
    Vec2d v_dot3(2.0f, 0.0f); // Zeigt ebenfalls nach rechts (Gleiche Richtung)

    float result1 = v_dot1.dot(v_dot2); // Erwartet: 0 (Da die Vektoren senkrecht zueinander stehen)
    float result2 = v_dot1.dot(v_dot3); // Erwartet: 2 (Berechnung: 1*2 + 0*0)

    std::cout << "--- Test neuer Funktionen ---" << std::endl;
    std::cout << "Skalarprodukt (orthogonal): " << result1 << " (Erwartet: 0)" << std::endl;
    std::cout << "Skalarprodukt (gleiche Richtung): " << result2 << " (Erwartet: 2)" << std::endl;

    //Zusammengesetzte Zuweisungsoperatoren Test
    Vec2d v_comp(12.0f, 8.0f);
    v_comp += Vec2d(2, 2);  // (14, 10)
    v_comp -= Vec2d(4, 0);  // (10, 10)
    v_comp *= 2.0f;         // (20, 20)
    v_comp /= 4.0f;         // (5, 5)
    std::cout << "v_comp final: (" << v_comp.x << ", " << v_comp.y << std::endl;
    // Sicherheitscheck: Division durch Null
    v_comp /= 0.0f;
    std::cout << "Nach /= 0: (" << v_comp.x << ", " << v_comp.y << ") (No Crash)" << std::endl;

} 