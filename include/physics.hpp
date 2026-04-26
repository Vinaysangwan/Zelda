#pragma once

#include "components.hpp"

PhysicsBody create_rect_body(b2WorldId worldId, b2BodyType type, b2Vec2 pos, float width, float height);
