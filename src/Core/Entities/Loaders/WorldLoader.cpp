//
// Created by Даниил on 02.05.2022.
//

#include "WorldLoader.h"

#include "../2DFigures/Circle.h"
#include "../2DFigures/Cube.h"

#include "../../../Precompiler.h"

void Loaders::WorldLoader::loadMap(World &world, const std::string &path)
{
    sf::Image mapImage;
    sf::Color pixel;

    mapImage.loadFromFile(path);

    int cell_height = mapImage.getSize().y;
    int cell_width = mapImage.getSize().x;

    for (size_t i = 0; i < cell_width; i++)
    {
        for (size_t j = 0; j < cell_height; j++)
        {
            if ((i == 1 && j == 1) || (i == 1 && j == cell_width - 1) ||
                (i == cell_height - 1 && j == 1) || (i == cell_height - 1 && j == cell_width - 1))
            {
                std::shared_ptr<Object2D> circle( new Circle(std::to_string(i + 1) + ":" + std::to_string(j + 1) +
                "-Circle",
                              *RESOURCE_MANAGER.loadTexture(std::string(DATA_DIR + std::string("/texture/woodWall1"
                                                                         ".jpg"))),
                              {static_cast<float>(i), static_cast<float>(j)}));
                world.addObject(circle);
            }

            pixel = mapImage.getPixel(i, j);

            if (pixel == sf::Color(0, 0, 0))
            {
                std::shared_ptr<Object2D> cube( new Cube(std::to_string(i + 1) + ":" + std::to_string(j + 1) + "-Cube",
                          *RESOURCE_MANAGER.loadTexture(
                                  std::string(DATA_DIR + std::string("/texture/wall2.png"))),
                          {static_cast<float>(i), static_cast<float>(j)}));
                world.addObject(cube);
            } else if (pixel == sf::Color(0, 0, 255))
            {
//                playerPosition = {static_cast<float>(i), static_cast<float>(j)};
            }
        }
    }
}
