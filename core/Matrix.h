// Leon Teichroeb - 07.01.2026

#pragma once

#include "MatrixDefines.h"

class Matrix {
public:
    virtual ~Matrix() = default;
    
    /// Initialize the display backend
    /// @return true if initialization successful, false otherwise
    virtual bool init() = 0;
    
    /// Shutdown and cleanup the display backend
    virtual void shutdown() = 0;
    
    /// Render the matrix data to the display
    /// @param matrixData The matrix data to render
    virtual void render(const matrix_t &matrixData) = 0;
    
    /// Set the brightness of the display
    /// @param brightness Brightness value between 0 and 255
    virtual void setBrightness(uint8_t brightness) = 0;
};