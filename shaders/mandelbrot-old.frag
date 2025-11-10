#version 330 core

out vec4 FragColor;
in vec2 fragCoord;

uniform float xmin;
uniform float xmax;
uniform float ymin;
uniform float ymax;
uniform int maxIterations;

vec3 hsv2rgb(vec3 c) {
    vec3 rgb = clamp(
        abs(mod(c.x * 6.0 + vec3(0.0, 4.0, 2.0), 6.0) - 3.0) - 1.0,
        0.0,
        1.0
    );
    return c.z * mix(vec3(1.0), rgb, c.y);
}

void main() {
    // Map fragment coordinates to complex plane
    float x0 = xmin + fragCoord.x * (xmax - xmin);
    float y0 = ymin + (1.0 - fragCoord.y) * (ymax - ymin);

    // Mandelbrot iteration
    float x = 0.0;
    float y = 0.0;
    float x2 = 0.0;
    float y2 = 0.0;

    float cache_1x = 0.0;
    float cache_1y = 0.0;

    int iteration;
    for (iteration = 0; iteration < maxIterations; iteration++) {
        y = 2.0 * x * y + y0;
        x = x2 - y2 + x0;

        x2 = x * x;
        y2 = y * y;

        if (iteration == 0) {
            cache_1x = x;
            cache_1y = y;
        }

        if (iteration == 2) {
            if (x == cache_1x && y == cache_1y) {
                iteration = maxIterations - 1;
                break;
            }
        }

        if (x2 + y2 > 4.0) break;
    }

    // Smooth iteration
    float log_zn = log(x * x + y * y) / 2.0;
    float nu = log(log_zn / log(2.0)) / log(2.0);
    float iter = float(iteration) + 1.0 - nu;

    // Smooth t for gradient effect
    float t = pow(float(iteration) / float(maxIterations), 0.3);

    // Map t to a colorful HSV palette
    vec3 color = hsv2rgb(vec3(0.95 + 10.0 * t, 0.6, 1.0)); // hue, saturation, value

    // Inside Mandelbrot set = black
    if (iteration == maxIterations) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        FragColor = vec4(color, 1.0);
    }
}

