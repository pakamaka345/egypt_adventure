#include "Map.hpp"
#include "interfaces/Interface.hpp"
#include <memory>


class GameView : public Map {
private:
    //std::shared_ptr<Interface> interface;

public:
    explicit GameView(std::string pathToInitFile);
    GameView(int width, int height);
    virtual ~GameView() = default;

    void draw() override;
};

