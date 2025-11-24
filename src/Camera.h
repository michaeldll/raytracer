#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include "Vector3.h"

class Camera {
public:
    Camera(double aspectRatio, int imageWidth)
        : aspectRatio(aspectRatio), imageWidth(imageWidth)
    {
        // Calculate image height
        imageHeight = int(imageWidth / aspectRatio);
        if (imageHeight < 1)
        {
            imageHeight = 1;
        }

        // Camera settings
        focalLength = 1.0;
        viewportHeight = 2.0;
        cameraCenter = Vector3(0, 0, 0);

        // Calculate viewport dimensions
        viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);

        // Calculate the vectors across the horizontal and down the vertical viewport edges
        viewportU = Vector3(viewportWidth, 0, 0);
        viewportV = Vector3(0, -viewportHeight, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel
        pixelDeltaU = viewportU / imageWidth;
        pixelDeltaV = viewportV / imageHeight;

        // Calculate the location of the upper left pixel
        Vector3 viewportUpperLeft = cameraCenter - Vector3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
        pixelStartPosition = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
    }

    Ray getRay(int x, int y) const
    {
        // Calculate the position of the pixel center
        Vector3 pixelCenter = pixelStartPosition + (x * pixelDeltaU) + (y * pixelDeltaV);
        Vector3 rayDirection = pixelCenter - cameraCenter;
        return Ray(cameraCenter, rayDirection);
    }

    int getImageWidth() const { return imageWidth; }
    int getImageHeight() const { return imageHeight; }

private:
    // Image dimensions
    double aspectRatio;
    int imageWidth;
    int imageHeight;

    // Camera settings
    double focalLength;
    double viewportHeight;
    double viewportWidth;
    Vector3 cameraCenter;

    // Viewport vectors
    Vector3 viewportU;
    Vector3 viewportV;

    // Pixel deltas
    Vector3 pixelDeltaU;
    Vector3 pixelDeltaV;

    // Pixel start position
    Vector3 pixelStartPosition;
};

#endif