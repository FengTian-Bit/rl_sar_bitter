#pragma once
#include "wl_controller_base.h"

class WLStandUp : public ControllerBase
{
public:
    void starting() override;
    void update() override;
};