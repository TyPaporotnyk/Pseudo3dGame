//
// Created by Даниил on 02.05.1922.
//

#include "WorldLoader.h"

#include "../../../Precompiler.h"

#include "../2DFigures/Object2D.h"
#include "../2DFigures/Circle.h"
#include "../2DFigures/Cube.h"

void Loaders::WorldLoader::loadMap(World &world, const std::string &path)
{
    sf::Image mapImage;
    sf::Color pixel;

    mapImage.loadFromFile(path);

    unsigned int cell_height = mapImage.getSize().y;
    unsigned int cell_width = mapImage.getSize().x;

    std::shared_ptr<Object2D> cube(new Object2D(std::to_string(0) + ":" + std::to_string(0) + "-Cube",
                                            *RESOURCE_MANAGER.loadTexture(
                                                    std::string(DATA_DIR +
                                                                std::string("/texture/walls/bricks.png"))),
                                                                Entities::CUBE,
                                            {0,0}, {{0,0},{1,0},{1,4},{0,4}}));

    std::shared_ptr<Object2D> cube1(new Object2D(std::to_string(1) + ":" + std::to_string(0) + "-Cube",
                                                *RESOURCE_MANAGER.loadTexture(
                                                        std::string(DATA_DIR +
                                                                    std::string("/texture/walls/bricks.png"))),
                                                Entities::CUBE,
                                                {4,4}, {{1,4},{0,4},{0,0},{1,0}}));

    std::shared_ptr<Object2D> cube2(new Object2D(std::to_string(2) + ":" + std::to_string(0) + "-Cube",
                                                *RESOURCE_MANAGER.loadTexture(
                                                        std::string(DATA_DIR +
                                                                    std::string("/texture/walls/bricks.png"))),
                                                Entities::CUBE,
                                                {7,-2}, {{0,0},{1,0},{1,4},{0,4}}));
    world.addObject(cube);
    world.addObject(cube1);
    world.addObject(cube2);

//    for (size_t i = 1; i < cell_width-1; i++)
//    {
//        for (size_t j = 1; j < cell_height-1; j++)
//        {
//            if ((i == 1 && j == 1) || (i == 1 && j == cell_width - 2) ||
//                (i == cell_height - 2 && j == 1) || (i == cell_height - 2 && j == cell_width - 1))
//            {
//                std::shared_ptr<Object2D> circle( new Circle(std::to_string(i + 1) + ":" + std::to_string(j + 1) +
//                "-Circle",
//                              *RESOURCE_MANAGER.loadTexture(std::string(DATA_DIR + std::string
//                              ("/texture/walls/woodPlanks.png"))),
//                              {static_cast<float>(i), static_cast<float>(j)}));
//                world.addObject(circle);
//            }
//
//            pixel = mapImage.getPixel(i, j);
//
//            if (pixel == sf::Color(0, 0, 0))
//            {
//                std::shared_ptr<Object2D> cube(new Cube(std::to_string(i + 1) + ":" + std::to_string(j + 1) + "-Cube",
//                                                        *RESOURCE_MANAGER.loadTexture(
//                                                                std::string(DATA_DIR +
//                                                                            std::string("/texture/walls/bricks.png"))),
//                                                        {static_cast<float>(i), static_cast<float>(j)}));
//                world.addObject(cube);
//            }
//        }
//    }
}
