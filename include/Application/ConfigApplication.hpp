#pragma once

// Movement uses pixels per second; this cap also applies when VSync is unavailable.
struct ConfigApplication
{
    int maxFps = 120;
};
