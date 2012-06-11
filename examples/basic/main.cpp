#include "meh"

using namespace meh;

int main(int argc, char* argv[]) {
    System::init();

    Canvas canvas(640,480);
    canvas.setTitle("Mehllo world.");

    View* backgroundView = new View();
    View* actorsView = new View(backgroundView);
    canvas.setView(backgroundView);

    return 0;
}
