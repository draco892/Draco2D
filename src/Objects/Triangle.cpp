#include "../include/Objects/Triangle.hpp"

// Constructor initializes default vertices for a simple triangle.
// The last vertex is equal to the first one so SDL_RenderLines()
// closes the shape automatically.
Triangle::Triangle()
{
    _vertices[0] = {640.0f, 100.0f};   // Top vertex
    _vertices[1] = {240.0f, 520.0f};   // Bottom left vertex
    _vertices[2] = {1040.0f, 520.0f};  // Bottom right vertex
    _vertices[3] = _vertices[0];       // Close the triangle
}

// Render the triangle outline using SDL3 connected lines.
void Triangle::render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderLines(renderer, _vertices, 4);
}