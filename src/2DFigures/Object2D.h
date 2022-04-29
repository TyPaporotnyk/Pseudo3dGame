//
// Created by Даниил on 11.04.2022.
//

#ifndef PSEUDO3DGAME_OBJECT2D_H
#define PSEUDO3DGAME_OBJECT2D_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../IDrawble.h"
#include "../Vector.h"

class Object2D : public virtual IDrawable
{
protected:
    std::vector<Vector>points_;
    Vector position_;

    std::string name_;

    sf::Texture& wallTexture_;

public:
    explicit Object2D(std::string name, sf::Texture& wallTexture, Vector position = {},
                      std::vector<Vector>points = {});

    std::vector<Vector>& getNodes();

    void draw(sf::RenderTarget &window) const override;

    [[nodiscard]]const std::string &getName() const;
    [[nodiscard]]sf::Texture &getWallTexture();

    [[nodiscard]]const std::vector<Vector> &getPoints() const;
    [[nodiscard]]const Vector &getPosition() const;
};


#endif //PSEUDO3DGAME_OBJECT2D_H
