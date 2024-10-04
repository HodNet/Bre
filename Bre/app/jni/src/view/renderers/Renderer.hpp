//
// Created by Jonathan on 01/10/2024.
//

#ifndef BRE_RENDERER_HPP
#define BRE_RENDERER_HPP

class Renderer {
public:
    /**
     * Should be called any time you want the render the object.
     */
    virtual void render() = 0;

    /**
     * Should be called when you want to stop rendering (the function render() will do
     * nothing if called)
     */
    virtual void stop() = 0;

    /**
     * Should be called when you want to resume rendering
     */
    virtual void resume() = 0;

    /**
     * Should be called when the renderer get destroyed
     */
    virtual void destroy() = 0;
};

#endif //BRE_RENDERER_HPP
