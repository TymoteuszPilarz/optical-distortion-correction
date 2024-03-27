//
// Created by Tymoteusz Pilarz on 20/09/2023.
//

#ifndef OPTICAL_DISTORTION_CORRECTION_DISTORTIONENGINE_H
#define OPTICAL_DISTORTION_CORRECTION_DISTORTIONENGINE_H

#include <utility>
#include <vector>
#include <memory>

#include <wx/image.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

enum class InterpolationType {nearest, bilinear, bicubic};
enum class DistortionType {radial, tangential};

class DistortionEngine
{
private:
    std::unique_ptr<wxImage> image;
    std::unique_ptr<wxImage> result;

    float xCenter = -1.f;
    float yCenter = -1.f;

    std::vector<float> radDistCoeff;
    std::vector<float> tanDistCoeff;

    InterpolationType interpolation = InterpolationType::bilinear;

    DistortionEngine() = default;

    [[nodiscard]] std::vector<float> PrepareRadDistCoeff() const;
    [[nodiscard]] std::vector<float> PrepareTanDistCoeff() const;

    template<typename Iterator>
    [[nodiscard]] static float PolyVal(Iterator begin, Iterator end, float x);

    [[nodiscard]] static cv::Mat ImageToMatrix(const wxImage& image);
    [[nodiscard]] static wxImage MatrixToImage(const cv::Mat& matrix);

public:
    DistortionEngine(const DistortionEngine&) = delete;
    DistortionEngine(DistortionEngine&&) = delete;
    DistortionEngine& operator=(const DistortionEngine&) = delete;
    DistortionEngine& operator=(DistortionEngine&&) = delete;

    static DistortionEngine& GetInstance();

    void SetImage(std::unique_ptr<wxImage> image);
    void SetDistCenter(float x, float y);

    void PushRadDistCoeff(float value);
    void SetRadDistCoeff(int index, float value);
    void PopRadDistCoeff();

    void PushTanDistCoeff(float value);
    void SetTanDistCoeff(int index, float value);
    void PopTanDistCoeff();

    void SetInterp(InterpolationType interpolation);

    /// Result may not be set yet, therefore caller should always check for nullptr value
    [[nodiscard]] const wxImage* GetResult() const;

    [[nodiscard]] InterpolationType GetInterp() const;
    [[nodiscard]] std::pair<float, float> GetDistCenter() const;

    void Apply();
};

#endif //OPTICAL_DISTORTION_CORRECTION_DISTORTIONENGINE_H
