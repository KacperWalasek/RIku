#include "TileObjectDecorator.h"

#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>

CEREAL_REGISTER_TYPE(TileObjectDecorator);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ITileObject, TileObjectDecorator)