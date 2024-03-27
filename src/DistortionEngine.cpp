//
// Created by Tymoteusz Pilarz on 20/09/2023.
//

#include <cmath>

#include "DistortionEngine.h"

std::vector<float> DistortionEngine::PrepareRadDistCoeff() const
{
    std::vector<float> res;

    if (!radDistCoeff.empty())
    {
        res.push_back(0.f);
        for (const auto& coeff : radDistCoeff)
        {
            res.push_back(0.f);
            res.push_back(coeff);
        }
    }

    return res;
}

std::vector<float> DistortionEngine::PrepareTanDistCoeff() const
{
    std::vector<float> res;

    if (tanDistCoeff.empty())
    {
        res = {0.f, 0.f, 1.f};
    }
    else if (tanDistCoeff.size() == 1)
    {
        res = {tanDistCoeff[0], 0.f, 1.f};
    }
    else if (tanDistCoeff.size() == 2)
    {
        res = {tanDistCoeff[0], tanDistCoeff[1], 1.f};
    }
    else
    {
        res = {tanDistCoeff[0], tanDistCoeff[1], 1.f};

        for (int i = 2; i < tanDistCoeff.size(); ++i)
        {
            res.push_back(0.f);
            res.push_back(tanDistCoeff[i]);
        }
    }

    return res;
}

// Horner's method for efficient polynomial evaluation
template<typename Iterator>
float DistortionEngine::PolyVal(Iterator begin, Iterator end, float x)
{
    if (begin == end)
    {
        return 0.f;
    }

    auto result = 0.0f;

    do
    {
        --end;
        result = result * x + *end;
    } while (begin != end);

    return result;
}

[[nodiscard]] cv::Mat DistortionEngine::ImageToMatrix(const wxImage& image)
{
    cv::Mat matrix(image.GetHeight(), image.GetWidth(), image.HasAlpha() ? CV_8UC4 : CV_8UC3);

    for (auto row = 0; row < matrix.rows; ++row)
    {
        for (auto column = 0; column < matrix.cols; ++column)
        {
            if (image.HasAlpha())
            {
                matrix.at<cv::Vec4b>(row, column)[0] = image.GetBlue(column, row);
                matrix.at<cv::Vec4b>(row, column)[1] = image.GetGreen(column, row);
                matrix.at<cv::Vec4b>(row, column)[2] = image.GetRed(column, row);
                matrix.at<cv::Vec4b>(row, column)[3] = image.GetAlpha(column, row);
            }
            else
            {
                matrix.at<cv::Vec3b>(row, column)[0] = image.GetBlue(column, row);
                matrix.at<cv::Vec3b>(row, column)[1] = image.GetGreen(column, row);
                matrix.at<cv::Vec3b>(row, column)[2] = image.GetRed(column, row);
            }
        }
    }

    return matrix;
}

[[nodiscard]] wxImage DistortionEngine::MatrixToImage(const cv::Mat& matrix)
{
    wxImage image(matrix.cols, matrix.rows);

    for (auto row = 0; row < matrix.rows; ++row)
    {
        for (auto column = 0; column < matrix.cols; ++column)
        {
            if (matrix.channels() == 4)
            {
                const auto& pixel = matrix.at<cv::Vec4b>(row, column);
                image.SetRGB(column, row, pixel[2], pixel[1], pixel[0]);
                image.SetAlpha(column, row, pixel[3]);
            }
            else
            {
                const auto& pixel = matrix.at<cv::Vec3b>(row, column);
                image.SetRGB(column, row, pixel[2], pixel[1], pixel[0]);
            }
        }
    }

    return image;
}

DistortionEngine& DistortionEngine::GetInstance()
{
    static DistortionEngine instance;
    return instance;
}

void DistortionEngine::SetImage(std::unique_ptr<wxImage> image)
{
    xCenter = static_cast<float>(image->GetWidth()) / 2;
    yCenter = static_cast<float>(image->GetHeight()) / 2;

    result = std::make_unique<wxImage>(*image);
    this->image = std::move(image);
}

void DistortionEngine::SetDistCenter(float x, float y)
{
    assert(x >= 0);
    assert(y >= 0);

    xCenter = x;
    yCenter = y;
}

void DistortionEngine::PushRadDistCoeff(float value)
{
    radDistCoeff.push_back(value);
}

void DistortionEngine::SetRadDistCoeff(int index, float value)
{
    assert(index >= 0 && index < radDistCoeff.size());

    radDistCoeff[index] = value;
}

void DistortionEngine::PopRadDistCoeff()
{
    assert(!radDistCoeff.empty());

    radDistCoeff.pop_back();
}

void DistortionEngine::PushTanDistCoeff(float value)
{
    tanDistCoeff.push_back(value);
}

void DistortionEngine::SetTanDistCoeff(int index, float value)
{
    assert(index >= 0 && index < tanDistCoeff.size());

    tanDistCoeff[index] = value;
}

void DistortionEngine::PopTanDistCoeff()
{
    assert(!tanDistCoeff.empty());

    tanDistCoeff.pop_back();
}

void DistortionEngine::SetInterp(InterpolationType interpolation)
{
    this->interpolation = interpolation;
}

const wxImage* DistortionEngine::GetResult() const
{
    return result.get();
}

InterpolationType DistortionEngine::GetInterp() const
{
    return interpolation;
}

std::pair<float, float> DistortionEngine::GetDistCenter() const
{
    return {xCenter, yCenter};
}

void DistortionEngine::Apply()
{
    if (image == nullptr)
    {
        return;
    }

    auto preparedRadDistCoeff = PrepareRadDistCoeff();
    auto preparedTanDistCoeff = PrepareTanDistCoeff();

    cv::Mat sourceMatrix = ImageToMatrix(*image);
    cv::Mat destinationMatrix;

    cv::Mat map_x(sourceMatrix.size(), CV_32FC1);
    cv::Mat map_y(sourceMatrix.size(), CV_32FC1);

    for (auto row = 0; row < image->GetHeight(); ++row)
    {
        for (auto column = 0; column < image->GetWidth(); ++column)
        {
            auto xDist = static_cast<float>(column) + 0.5f;
            auto yDist = static_cast<float>(row) + 0.5f;

            auto xDiff = xDist - xCenter;
            auto xDiffSqr = powf(xDiff, 2);

            auto yDiff = yDist - yCenter;
            auto yDiffSqr = powf(yDiff, 2);

            auto r = std::sqrtf(xDiffSqr + yDiffSqr);
            auto rSqr = powf(r, 2);

            auto radDistPolyVal = PolyVal(preparedRadDistCoeff.begin(), preparedRadDistCoeff.end(), r);
            auto tanDistPolyVal = PolyVal(preparedTanDistCoeff.begin() + 2, preparedTanDistCoeff.end(), r);

            auto xUndist = xDist + xDiff * radDistPolyVal + (preparedTanDistCoeff[0] * (rSqr + 2 * xDiffSqr) + 2 * preparedTanDistCoeff[1] * xDiff * yDiff) * tanDistPolyVal;
            auto yUndist = yDist + yDiff * radDistPolyVal + (2 * preparedTanDistCoeff[0] * xDiff * yDiff + preparedTanDistCoeff[1] * (rSqr + 2 * yDiffSqr)) * tanDistPolyVal;

            map_x.at<float>(row, column) = xUndist;
            map_y.at<float>(row, column) = yUndist;
        }
    }

    if (interpolation == InterpolationType::nearest)
    {
        cv::remap(sourceMatrix, destinationMatrix, map_x, map_y, cv::InterpolationFlags::INTER_NEAREST);
    }
    else if (interpolation == InterpolationType::bilinear)
    {
        cv::remap(sourceMatrix, destinationMatrix, map_x, map_y, cv::InterpolationFlags::INTER_LINEAR);
    }
    else
    {
        cv::remap(sourceMatrix, destinationMatrix, map_x, map_y, cv::InterpolationFlags::INTER_CUBIC);
    }

    *result = MatrixToImage(destinationMatrix);
}