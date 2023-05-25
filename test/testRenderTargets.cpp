#include <InputHandler.hpp>
#include <RenderTargets.hpp>

#include <vector>

int main()
{
    std::vector<Body> currentStateOfBodies;
    Vector2D initialPos1(0, -5);
    Vector2D initialPos2(0, 5);
    Vector2D nullVector(0, 0);

    InputHandler inputHandler(currentStateOfBodies);
    inputHandler.addToStateOfBodies(6e3, 1, initialPos1, nullVector, nullVector);
    inputHandler.addToStateOfBodies(6e3, 1, initialPos2, nullVector, nullVector);

    // auto state = StateOfCircles<Identity>(stateOfDataPointsOverTime[0], 100.f, Identity());
    // auto state = StateOfCircles(currentStateOfBodies, 100.f);

    // auto stateOfBodies2 = create_stateOfBodies(9);
    // state.update_state(stateOfBodies2);

    return 0;
}
