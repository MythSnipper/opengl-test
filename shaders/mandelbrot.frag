#version 330 core

out vec4 FragColor;
in vec2 fragCoord;

uniform float xmin;
uniform float xmax;
uniform float ymin;
uniform float ymax;
uniform int maxIterations;

void main() {
    // Map fragment coordinates to complex plane
    float x0 = xmin + fragCoord.x * (xmax - xmin);
    float y0 = ymin + (1.0 - fragCoord.y) * (ymax - ymin);

    float x = 0.0;
    float y = 0.0;
    float x2 = 0.0;
    float y2 = 0.0;

    int iteration;
    for (iteration = 0; iteration < maxIterations; iteration++) {
        y = 2.0 * x * y + y0;
        x = x2 - y2 + x0;

        x2 = x * x;
        y2 = y * y;

        if (x2 + y2 > 4.0) break;
    }

    float color = float(iteration) / float(maxIterations);
    FragColor = vec4(color, color, color, 1.0); // grayscale
}
