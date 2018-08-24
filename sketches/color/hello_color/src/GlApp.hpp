#ifndef TETRA_GLAPP_HPP
#define TETRA_GLAPP_HPP

#include <tetra/Color.hpp>
#include <tetra/gl/Buffer.hpp>
#include <tetra/gl/Program.hpp>
#include <tetra/gl/VAO.hpp>
#include <tetra/sdl/SdlEventPump.hpp>

namespace tetra
{
class ColoredQuads
{
  public:
    struct Quad {
        float left, right, bottom, top;
        std::array<float, 4> rgba_color;
    };

  public:
    ColoredQuads();
    ColoredQuads(const ColoredQuads& from) = delete;
    ColoredQuads(ColoredQuads&& from) = default;

    void set_quads(const std::vector<Quad>& quads);
    void draw(const std::array<float, 16>& view_matrix);

  private:
    int vertex_count;
    VAO vao;
    Buffer buffer;
    Program flat_color;

  private:
    struct Vertex {
        std::array<float, 2> pos;
        std::array<float, 4> color;
    };
};

class GlApp final : public IWindowEvents
{
  public:
    GlApp();
    ~GlApp();

    virtual void on_frame_render() override;

    virtual void on_viewport_change(int width, int height) override;
    virtual void on_mouse_move(int x, int y) override;

  private:
    HSL clear_color;
    HSL rect_color;
    float rect_size;
    std::array<float, 16> view;
    ColoredQuads colored_quads;

    struct ScreenDims {
        float width;
        float height;
    } dims;
};
} // namespace tetra

#endif